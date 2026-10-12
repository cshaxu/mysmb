"""Verify original-ROM staircase parser routes from local bounded traces."""
import argparse
import csv
import json
from pathlib import Path

from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    root = parser.parse_args().directory
    scope = list(range(0x6a1, 0x6ae)) + list(range(0x72c, 0x736))
    scope += [0x6c1, 0x75c]
    summary = []
    for case in range(12):
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        entries = [0x9508, 0x9ab7, 0x9ac1, 0x9b7d]
        if case == 9:
            entries += [0x9abc]
        assert all(hits.get(pc, 0) for pc in entries), (case, 'missing entry')
        index = case if case < 9 else [8, 9, 255][case - 9]
        assert rom[0][0x734] == index, (case, 'control')
        length = (case - 1) & 255 if case < 9 else (7 if case == 9 else 255)
        assert rom[0][0x732] == length, (case, 'length')
        if index < 9:
            top = [3, 3, 4, 5, 6, 7, 8, 9, 10][index]
            for row in range(top, 11):
                assert rom[0][0x6a1 + row] == 0x61, (case, 'step')
            assert rom[0][0x735] == 0, (case, 'remaining height')
        else:
            target, height = (0x6c1, 3) if index == 9 else (0x75c, 6)
            assert rom[0][target] == 0x61, (case, 'adjacent-ROM row')
            assert rom[0][0x735] == height, (case, 'adjacent-ROM height')
        residual = set()
        for a, b in zip(rom, native):
            differences = [hex(i) for i in scope if a[i] != b[i]]
            assert not differences, (case, differences)
            residual.update(i for i in range(2048) if a[i] != b[i])
        summary.append(dict(case=case, index=index, chainOutputMismatches=0,
                            otherRamDifferences=[hex(i) for i in sorted(residual)]))
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()
