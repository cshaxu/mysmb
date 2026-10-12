"""Check original-ROM parser index-wrap routes and their persistent outputs."""
import argparse
import csv
import json
from pathlib import Path
from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    root = parser.parse_args().directory
    excluded = set(range(8)) | set(range(0x100, 0x200)) | {0x778, 0x779}
    rows = [1, 2, 5, 3, 9, 6]
    lengths = [7, 0, 6, 6, 7, 6]
    results = []
    for case in range(24):
        shape, variant = divmod(case, 4)
        slot = 2 if variant == 0 else variant - 1
        expected_length = ((lengths[shape] - 2) & 255) if variant == 0 and lengths[shape] else (125 if variant == 3 else 255)
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        for pc in [0x9508, 0x9571, 0x9588, 0x9595, 0x959d, 0x95e2, 0x965f]:
            assert hits.get(pc, 0), (case, 'missing source path', hex(pc))
        assert hits[0x9595] == 6, (case, 'two columns, three slots each')
        assert rom[0][0x500 + 16 * rows[shape]] == (0xc2 if shape in (0, 4) else 0x51), (case, 'decoded tile')
        for sample, (a, b) in enumerate(zip(rom, native)):
            assert a[0x72c] == 1 and a[0x72a] == 1 and a[0x72b] == 0, (case, 'cursor/page')
            assert a[0x72d + slot] == 255 and a[0x730 + slot] == expected_length, (case, 'saved slot')
            diff = [i for i in range(2048) if a[i] != b[i]]
            assert not [i for i in diff if i not in excluded], (case, sample, diff)
            results.append(dict(case=case, sample=sample, persistentMismatches=0,
                                residualAddresses=[hex(i) for i in diff]))
    (root / 'route-summary.json').write_text(json.dumps(results, indent=2) + '\n')
    print('24 parser wrap routes pass; exact tile/cursor/page/slot witnesses and 1782 persistent bytes per sample match')


if __name__ == '__main__':
    main()
