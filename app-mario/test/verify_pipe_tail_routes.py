"""Verify original DrawPipe extent and table selection through ordinary parser routes."""
import argparse
import csv
import json
from pathlib import Path
from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    root = parser.parse_args().directory
    rows = [10, 9, 8, 7, 8, 2, 4, 0, 2, 4, 8, 9, 6, 10, 8, 1]
    excluded = set(range(8)) | set(range(0x100, 0x200)) | {0x778, 0x779}
    results = []
    for case in range(32):
        shape, side = divmod(case, 2)
        height, row, usage = shape % 8, rows[shape], shape // 8
        count = min(max(height, 1), 12 - row)
        expected = [0] * 11 + [0x54, 0x54]
        expected[row] = (0x10 if usage else 0x12) + side
        expected[row+1:row+count+1] = [0x14 + side] * count
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        for pc in [0x9508, 0x9925, 0x992f, 0x9935, 0x9936, 0x9b7d, 0x9bab]:
            assert hits.get(pc, 0), (case, 'missing original path', hex(pc))
        assert hits[0x9925] == (2 if side == 0 else 1), (case, 'pipe column count')
        assert list(rom[0][0x500:0x5d0:16]) == expected, (case, 'complete first column')
        assert rom[0][0x732] == 255, (case, 'expired fixed slot')
        for sample, (a, b) in enumerate(zip(rom, native)):
            diff = [i for i in range(2048) if a[i] != b[i]]
            assert not [i for i in diff if i not in excluded], (case, sample, diff)
            results.append(dict(case=case, sample=sample, persistentMismatches=0,
                                residualAddresses=[hex(i) for i in diff]))
    (root / 'route-summary.json').write_text(json.dumps(results, indent=2) + '\n')
    print('32 original-ROM pipe routes pass: every first-column tile and persistent state match')


if __name__ == '__main__':
    main()
