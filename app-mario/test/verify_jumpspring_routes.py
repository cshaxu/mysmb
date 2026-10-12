"""Check jumpspring creation in original-ROM screen-building routes."""
import argparse
import csv
import json
from pathlib import Path

from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    root = parser.parse_args().directory
    fields = [0x87, 0x6e, 0xcf, 0x58, 0x16, 0xb6, 0x0f]
    scope = [base + slot for base in fields for slot in range(6)]
    scope += list(range(0x500, 0x6ae)) + list(range(0x72c, 0x736))
    summary = []
    for case in range(8):
        slot = min(case, 5)
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        assert all(hits.get(pc, 0) for pc in [0x8567, 0x86e6, 0x9508, 0x994a, 0x9ad3,
                                             0x9bbb, 0x9bcb, 0x9bd3]), (case, 'entry')
        flag = 0 if case == 7 else (2 if case == 6 else 1)
        expected = [0x70, 1, 0xb0, 0xb0, 0x32, 1, flag]
        assert [rom[0][base + slot] for base in fields] == expected, (case, 'creation')
        assert rom[0][0x590] == 0x67 and rom[0][0x5a0] == 0x68, (case, 'metatiles')
        residual = set()
        for a, b in zip(rom, native):
            differences = [hex(i) for i in scope if a[i] != b[i]]
            assert not differences, (case, differences)
            residual.update(i for i in range(2048) if a[i] != b[i])
        summary.append(dict(case=case, slot=slot, chainOutputMismatches=0,
                            otherRamDifferences=[hex(i) for i in sorted(residual)]))
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()
