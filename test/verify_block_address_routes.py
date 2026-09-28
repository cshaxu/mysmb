"""Verify both physical block buffers through the original area-parser caller."""
import argparse
import csv
import json
from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory')
    from pathlib import Path
    root = Path(parser.parse_args().directory)
    excluded = set(range(8)) | set(range(0x100, 0x200)) | {0x778, 0x779}
    results = []
    for case in range(48):
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as stream:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(stream)}
        path = [0x9508, 0x9925, 0x9be1, 0x9be7, 0x9bea, 0x9bf0, 0x9bf3, 0x9bf5] if case < 32 else [0x8ffe, 0x9012]
        for pc in path:
            assert hits.get(pc, 0), (case, 'missing original address path', hex(pc))
        if case < 32:
            assert hits[0x9be1] == 2, (case, 'two parser columns')
            base = 0x500 + (case // 16) * 0xd0 + case % 16
            expected = [0] * 7 + [0x13, 0x15, 0x15, 0x15, 0x54, 0x54]
            assert list(rom[0][base:base+0xd0:16]) == expected, (case, 'physical column contents')
            assert rom[0][0x6a0] == (case+2) % 32, (case, 'buffer column advance')
        else:
            page = (case - 32) % 8
            base = 0x500 + (page % 2) * 0xd0
            assert hits[0x9012] == 1, (case, 'one initialization')
            for ram in rom:
                assert ram[0x6a0] == (page % 2)*16, (case, 'initial column parity')
                assert ram[0x71a] == page and ram[0x725] == page and ram[0x728] == page, (case, 'selected entrance page')
                assert ram[0x720] == 0x20 + (page % 2)*4 and ram[0x721] == 0x80, (case, 'nametable pointer')
        for sample, (a, b) in enumerate(zip(rom, native)):
            diff = [i for i in range(2048) if a[i] != b[i]]
            assert not [i for i in diff if i not in excluded], (case, sample, diff)
            results.append(dict(column=case, address=hex(base), sample=sample,
                                persistentMismatches=0,
                                residualAddresses=[hex(i) for i in diff]))
    (root / 'route-summary.json').write_text(json.dumps(results, indent=2)+'\n')
    print('48 original-ROM routes pass: 32 physical columns and 16 initialization/parity routes')


if __name__ == '__main__':
    main()
