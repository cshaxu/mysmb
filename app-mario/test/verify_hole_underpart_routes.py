"""Verify original-ROM hole registration and UnderPart parser routes."""
import argparse
import csv
import json
from pathlib import Path

from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    root = parser.parse_args().directory
    scope = list(range(0x46a, 0x47d)) + list(range(0x6a1, 0x6ae))
    scope += list(range(0x72c, 0x736))
    summary = []
    for case in range(98):
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        entries = [0x9508, 0x9b7d, 0x9b9d, 0x9ba0, 0x9bab]
        if case < 96:
            area_type = case // 24
            slot = (case // 4) % 6
            continuation = (case // 2) % 2
            shape = case % 2
            initial_water = area_type == 0 and continuation == 0
            entries += [0x9b41, 0x9b73]
            if initial_water:
                entries += [0x9b70]
            expected_offset = (slot + 1 if slot < 4 else 0) if initial_water else slot
            assert rom[0][0x46a] == expected_offset, (case, 'offset')
            for i in range(6):
                page, left, length = 0xa5, 0xa5, 0xa5
                if initial_water and i == slot:
                    page, left, length = (0, 0xf0, 0x30) if shape == 0 else (1, 0xb0, 0x50)
                assert [rom[0][base+i] for base in [0x46b, 0x471, 0x477]] == [page, left, length], (case, i, 'registration')
            assert rom[0][0x735] == 11, (case, 'height')
            for row in range(8, 13):
                assert rom[0][0x6a1 + row] == (0x87 if area_type == 0 else 0), (case, 'hole')
        elif case == 96:
            entries += [0x9ac1]
            assert rom[0][0x6a8] == 0x61, 'signed-exit first row'
            assert rom[0][0x6a9] != 0x61, 'signed-exit must not draw second row'
            assert rom[0][0x735] == 0x90, 'height preserved on signed exit'
        else:
            assert rom[0][0x6a8] == 0x50, 'mushroom stem drawn'
            assert rom[0][0x6ac] == 0x54 and rom[0][0x6ad] == 0x54, 'rock preserved'
            assert rom[0][0x735] == 10, 'stem height'
        assert all(hits.get(pc, 0) for pc in entries), (case, 'entry')
        residual = set()
        for a, b in zip(rom, native):
            differences = [hex(i) for i in scope if a[i] != b[i]]
            assert not differences, (case, differences)
            residual.update(i for i in range(2048) if a[i] != b[i])
        summary.append(dict(case=case, chainOutputMismatches=0,
                            otherRamDifferences=[hex(i) for i in sorted(residual)]))
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()
