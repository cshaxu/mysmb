"""Check local original-ROM parser execution for the T30/S5 cannon chain."""
import argparse
import csv
import json

from verify_castle_column_routes import read_frames
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    root = parser.parse_args().directory
    scope = list(range(0x46a, 0x47d)) + list(range(0x6a1, 0x6b1))
    scope += list(range(0x72c, 0x736))
    summary = []
    for case in range(30):
        shape, slot = divmod(case, 6)
        height = [0, 1, 2, 5, 15][shape]
        row, column = [10, 9, 8, 5, 11][shape], [12, 3, 14, 6, 1][shape]
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        entries = [0x9508, 0x9a69, 0x9a85, 0x9aa1]
        if height >= 1:
            entries += [0x9a77]
        if height >= 2:
            entries += [0x9a80, 0x9b7d]
        assert all(hits.get(pc, 0) for pc in entries), (case, 'missing entry')
        assert rom[0][0x46a] == (slot + 1) % 6, (case, 'offset')
        assert rom[0][0x46b + slot] == 1, (case, 'page')
        assert rom[0][0x471 + slot] == column * 16, (case, 'X')
        assert rom[0][0x477 + slot] == row * 16 + 32, (case, 'Y')
        last = 13 if shape == 4 else min(row + height, 12)
        for i in range(last - row + 1):
            assert rom[0][0x6a1 + row + i] == 0x64 + min(i, 2), (case, 'geometry')
        if shape == 4:
            assert rom[0][0x735] == 13, (case, 'bottom stop')
        residual = set()
        for a, b in zip(rom, native):
            differences = [hex(i) for i in scope if a[i] != b[i]]
            assert not differences, (case, differences)
            residual.update(i for i in range(2048) if a[i] != b[i])
        summary.append(dict(case=case, height=height, slot=slot,
                            chainOutputMismatches=0,
                            otherRamDifferences=[hex(i) for i in sorted(residual)]))
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()
