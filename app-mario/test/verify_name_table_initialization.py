"""Verify the bounded ROM/native InitializeNameTables route.

The reference recorder stops at InitScreen's source successor while the
native recorder samples after its shared C frame completes.  Therefore this
checker compares only the fields owned by InitializeNameTables: both CIRAM
pages, Buffer1 reset and the PPU control/scroll transfer.  It also requires
the original PC coverage to reach every source label in this contiguous chain.
"""

import csv
import sys
from pathlib import Path


HEADER_SIZE = 12
RECORD_SIZE = 4409
CPU_RAM = 4
NAME_TABLE_0 = CPU_RAM + 0x0800
NAME_TABLE_1 = NAME_TABLE_0 + 0x0400
SCALARS = NAME_TABLE_1 + 0x0400 + 0x20 + 0x0100 + 14
REQUIRED_PCS = (0x8E19, 0x8E2D, 0x8E3B, 0x8E4D, 0x8EE6, 0x8EED)


def read_trace(path, magic):
    data = Path(path).read_bytes()
    if data[:8] != magic:
        raise ValueError("unsupported trace magic")
    if len(data) != HEADER_SIZE + RECORD_SIZE:
        raise ValueError("expected exactly one bounded trace record")
    if int.from_bytes(data[8:12], "little") != 1:
        raise ValueError("expected exactly one declared trace record")
    return data[HEADER_SIZE:]


def require_rom_coverage(path):
    hits = {}
    with Path(path).open(newline="", encoding="ascii") as stream:
        for row in csv.DictReader(stream):
            hits[int(row["pc"], 16)] = int(row["hits"])
    missing = [f"${pc:04x}" for pc in REQUIRED_PCS if hits.get(pc, 0) == 0]
    if missing:
        raise ValueError("ROM route missed " + ", ".join(missing))


def require_table_shape(record, offset):
    table = record[offset:offset + 0x0400]
    if table[:0x03C0] != bytes([0x24]) * 0x03C0:
        raise ValueError("name-table tile clear differs from ROM blank tile")
    if table[0x03C0:] != bytes(0x40):
        raise ValueError("attribute-table clear differs from ROM zero fill")


def main(arguments):
    if len(arguments) != 4:
        return 64
    reference = read_trace(arguments[1], b"MSFR\x02\0\0\0")
    native = read_trace(arguments[2], b"MSFN\x02\0\0\0")
    require_rom_coverage(arguments[3])
    for offset in (NAME_TABLE_0, NAME_TABLE_1):
        require_table_shape(reference, offset)
        require_table_shape(native, offset)
        if reference[offset:offset + 0x0400] != native[offset:offset + 0x0400]:
            raise ValueError("ROM/native CIRAM differs")
    if reference[CPU_RAM + 0x0300:CPU_RAM + 0x0302] != b"\0\0":
        raise ValueError("ROM Buffer1 reset is absent")
    if native[CPU_RAM + 0x0300:CPU_RAM + 0x0302] != b"\0\0":
        raise ValueError("native Buffer1 reset is absent")
    # The reference scalar is at the exact source successor, while the native
    # recorder completes the containing NMI and can therefore update PPU
    # control/mask.  Name-table selection and scroll stay owned by this chain.
    for record in (reference, native):
        if record[SCALARS + 2:SCALARS + 5] != b"\0\0\0":
            raise ValueError("final PPU name-table/scroll state differs")
    print("InitializeNameTables ROM/native route: PASS")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv))
    except (OSError, ValueError) as error:
        print(f"InitializeNameTables ROM/native route: FAIL: {error}", file=sys.stderr)
        raise SystemExit(1)
