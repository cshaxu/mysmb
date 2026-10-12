"""Verify local original-ROM hidden/question/item block parser routes."""
import argparse
import csv
import json
from pathlib import Path

from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    root = parser.parse_args().directory
    table = [0xc1, 0xc0, 0x5f, 0x60, 0x55, 0x56, 0x57,
             0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e]
    rows = [1, 7, 7, 3, 3, 3, 3, 7, 3]
    scope = list(range(0x6a1, 0x6ae)) + list(range(0x72c, 0x736)) + [0x6bc, 0x75d]
    summary = []
    for case in range(72):
        selector, variant = divmod(case, 8)
        area_type, hidden = divmod(variant, 2)
        enabled = selector != 3 or hidden != 0
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        entries = [0x9508, 0x9b3c]
        entries += [0x9b0e if selector < 3 else
                    0x9b01 if selector == 3 else 0x9b14 if selector == 7 else 0x9b19]
        if enabled:
            entries += [0x9b36, 0x9b2c, 0x9a48, 0x9b7d]
            if selector >= 3:
                entries += [0x9b19, 0x9b28]
        assert all(hits.get(pc, 0) for pc in entries), (case, 'entry')
        index = selector + (5 if selector >= 3 and area_type != 1 else 0)
        assert rom[0][0x6a1 + rows[selector]] == (table[index] if enabled else 0), (case, 'metatile')
        assert rom[0][0x75d] == (0 if selector == 3 else hidden), (case, 'hidden flag')
        assert rom[0][0x6bc] == (0 if selector == 7 else 0xa5), (case, 'coin timer')
        residual = set()
        for a, b in zip(rom, native):
            differences = [hex(i) for i in scope if a[i] != b[i]]
            assert not differences, (case, differences)
            residual.update(i for i in range(2048) if a[i] != b[i])
        summary.append(dict(case=case, selector=selector, areaType=area_type,
                            hidden=hidden, chainOutputMismatches=0,
                            otherRamDifferences=[hex(i) for i in sorted(residual)]))
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()
