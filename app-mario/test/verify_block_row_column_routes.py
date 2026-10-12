"""Validate local original-ROM consumer routes for the T30/S4 block chain."""
import argparse
import csv
import json
from pathlib import Path

from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    args = parser.parse_args()
    rows = [3, 5, 1, 4]
    entries = [0x9a2e, 0x9a3e, 0x9a50, 0x9a59]
    summary = []
    scope = list(range(0x6a1, 0x6ae)) + list(range(0x72c, 0x736))
    for case in range(32):
        kind, variant = divmod(case, 8)
        area_type, cloud = divmod(variant, 2)
        rom = read_frames(args.directory / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(args.directory / ('native-%d.msfn' % case), b'MSFN')
        with (args.directory / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        expected_entries = [0x9508, entries[kind]]
        expected_entries += [0x9a44, 0x9a48] if kind < 2 else [0x9a5f]
        if kind == 0:
            expected_entries += [0x9a38]
            if cloud:
                expected_entries += [0x9a36]
        assert all(hits.get(pc, 0) for pc in expected_entries), (case, 'missing entry')
        table = [0x22, 0x51, 0x52, 0x52] if kind in (0, 2) else [0x69, 0x61, 0x61, 0x62]
        tile = 0x88 if kind == 0 and cloud else table[area_type]
        assert rom[0][0x6a1 + rows[kind]] == tile, (case, 'missing selected tile')
        assert rom[0][0x732] == [4, 1, 255, 255][kind], (case, 'length')
        if kind >= 2:
            for row in range(rows[kind], rows[kind] + [0, 0, 3, 4][kind]):
                assert rom[0][0x6a1 + row] == tile, (case, 'height')
        residual = set()
        for a, b in zip(rom, native):
            differences = [hex(i) for i in scope if a[i] != b[i]]
            assert not differences, (case, differences)
            residual.update(i for i in range(2048) if a[i] != b[i])
        summary.append(dict(case=case, kind=kind, areaType=area_type, cloud=cloud,
                            chainOutputMismatches=0,
                            otherRamDifferences=[hex(i) for i in sorted(residual)]))
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()
