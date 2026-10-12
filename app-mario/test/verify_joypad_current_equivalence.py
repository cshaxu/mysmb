"""Verify the bounded current ROM/native joypad chain route."""

import csv
import sys
from pathlib import Path


HEADER_SIZE = 12
RECORD_SIZE = 4409
RAM = 4
SCALARS = RAM + 0x0800 + 0x0400 + 0x0400 + 0x20 + 0x0100 + 14
JOY_OFFSETS = (0x06FC, 0x06FD, 0x074A, 0x074B)
REQUIRED_PCS = (0x8E5C, 0x8E66, 0x8E6A, 0x8E79, 0x8E7B, 0x8E8D)


def read_trace(path, magic):
    data = Path(path).read_bytes()
    if data[:8] != magic:
        raise ValueError("unexpected trace magic")
    count = int.from_bytes(data[8:12], "little")
    if count != 120 or len(data) != HEADER_SIZE + count * RECORD_SIZE:
        raise ValueError("expected the bounded 120-frame route")
    return data, count


def require_coverage(path):
    rows = {}
    with Path(path).open(newline="", encoding="ascii") as stream:
        for row in csv.DictReader(stream):
            rows[int(row["pc"], 16)] = row
    missing = ["${:04x}".format(pc) for pc in REQUIRED_PCS
               if pc not in rows or int(rows[pc]["hits"]) == 0]
    if missing:
        raise ValueError("ROM route missed " + ", ".join(missing))
    branch = rows[0x8E79]
    if int(branch["fallthrough2"]) == 0 or int(branch["other"]) == 0:
        raise ValueError("ROM route missed a Select/Start debounce outcome")


def compare_fields(reference, native, count):
    for frame in range(count):
        base = HEADER_SIZE + frame * RECORD_SIZE
        for offset in JOY_OFFSETS:
            if reference[base + RAM + offset] != native[base + RAM + offset]:
                raise ValueError("joypad RAM differs at frame {} ${:04x}".format(
                    frame, offset))
        for offset in range(7):
            if reference[base + SCALARS + offset] != native[base + SCALARS + offset]:
                raise ValueError("PPU scalar differs at frame {} index {}".format(
                    frame, offset))


def main(arguments):
    if len(arguments) != 5:
        return 64
    reference, count = read_trace(Path(arguments[1]), b"MSFR\x02\0\0\0")
    native_x86, x86_count = read_trace(Path(arguments[2]), b"MSFN\x02\0\0\0")
    native_x64, x64_count = read_trace(Path(arguments[3]), b"MSFN\x02\0\0\0")
    if x86_count != count or x64_count != count:
        raise ValueError("trace frame counts differ")
    require_coverage(arguments[4])
    compare_fields(reference, native_x86, count)
    compare_fields(reference, native_x64, count)
    compare_fields(native_x86, native_x64, count)
    print("joypad ROM/native current-equivalence route: PASS")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv))
    except (OSError, ValueError) as error:
        print("joypad ROM/native current-equivalence route: FAIL: {}".format(error),
              file=sys.stderr)
        raise SystemExit(1)
