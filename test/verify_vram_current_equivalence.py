"""Verify the bounded ROM/native S8 VRAM packet routes.

The reference stops at InitScroll immediately after UpdateScreen, while the
native recorder reaches the equivalent shared NMI prefix from its title
baseline.  The reference PPU core does not expose the immediate `$2007`
writes at that stop boundary, so it proves the source packet bytes, pointer
and control-flow PCs.  The native record proves the corresponding CIRAM
destinations.  Both native widths must remain byte-identical.
"""

import csv
import sys
from pathlib import Path


HEADER = 12
RECORD = 4409
RAM = 4
NAME_TABLE_0 = RAM + 0x0800
PACKET = RAM + 0x0301

CASES = {
    "repeat": ((0x0000, 0x0001, 0x0002), 0x29, bytes((0x20, 0x00, 0x43, 0x29, 0)),
               (0x8E92, 0x8EA7, 0x8EAD, 0x8EB2, 0x8EB5, 0x8EED)),
    "vertical": ((0x0010, 0x0030, 0x0050), (0x11, 0x22, 0x33),
                 bytes((0x20, 0x10, 0x83, 0x11, 0x22, 0x33, 0)),
                 (0x8E92, 0x8EAD, 0x8EB5, 0x8EED)),
}


def record(path, magic):
    data = Path(path).read_bytes()
    if data[:8] != magic or int.from_bytes(data[8:12], "little") != 1:
        raise ValueError("invalid bounded trace: {}".format(path))
    if len(data) != HEADER + RECORD:
        raise ValueError("wrong trace size: {}".format(path))
    return data[HEADER:]


def coverage(path, required):
    rows = {int(row["pc"], 16): int(row["hits"])
            for row in csv.DictReader(Path(path).open(encoding="ascii"))}
    missing = ["${:04x}".format(pc) for pc in required if rows.get(pc, 0) == 0]
    if missing:
        raise ValueError("ROM packet route missed " + ", ".join(missing))


def expected_values(value, count):
    if isinstance(value, int):
        return (value,) * count
    return value


def verify_case(name, rom, native32, native64, pcs):
    offsets, value, packet, required = CASES[name]
    coverage(pcs, required)
    if rom[PACKET:PACKET + len(packet)] != packet:
        raise ValueError("ROM {} packet fixture differs".format(name))
    if rom[RAM] != len(packet) or rom[RAM + 1] != 3:
        raise ValueError("ROM {} packet pointer differs".format(name))
    expected = expected_values(value, len(offsets))
    for trace_name, trace in (("x86", native32), ("x64", native64)):
        actual = tuple(trace[NAME_TABLE_0 + offset] for offset in offsets)
        if actual != expected:
            raise ValueError("{} {} packet bytes differ: {}".format(
                trace_name, name, actual))
    if native32 != native64:
        raise ValueError("native x86/x64 {} packet snapshots differ".format(name))


def main(args):
    if len(args) != 9:
        return 64
    verify_case("repeat", record(args[1], b"MSFR\x02\0\0\0"),
                record(args[2], b"MSFN\x02\0\0\0"),
                record(args[3], b"MSFN\x02\0\0\0"), args[4])
    verify_case("vertical", record(args[5], b"MSFR\x02\0\0\0"),
                record(args[6], b"MSFN\x02\0\0\0"),
                record(args[7], b"MSFN\x02\0\0\0"), args[8])
    print("VRAM packet ROM/native current-equivalence routes: PASS")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv))
    except (OSError, ValueError) as error:
        print("VRAM packet ROM/native current-equivalence routes: FAIL: {}".format(
            error), file=sys.stderr)
        raise SystemExit(1)
