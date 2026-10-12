"""Compare source-reachable area-helper consumers and require branch witnesses."""
import argparse
import csv
import json
from pathlib import Path
from verify_castle_column_routes import read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    root = parser.parse_args().directory
    # These scratch bytes are overwritten after parser helpers by name-table
    # output. Record them explicitly, never treat the complete frame as equal.
    excluded = set(range(8)) | set(range(0x100, 0x200)) | {0x778, 0x779}
    results = []
    for case in range(20):
        rom = read_frames(root / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(root / ('native-%d.msfn' % case), b'MSFN')
        with (root / ('pc-%d.txt' % case)).open() as source:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(source)}
        required = [0x9508, 0x9bbb, 0x9bca]
        if case < 4:
            required += [0x9bac, 0x9baf, 0x9bba]
            assert hits.get(0x9bb5, 0) == (1 if case % 2 == 0 else 0), (case, 'initialization gate')
            assert hits[0x9bba] == 2, (case, 'both length columns')
            if case == 0:
                required += [0x9bcb, 0x9bd2]
                assert [rom[0][a] for a in [0x46a, 0x46b, 0x471, 0x477]] == [1, 0, 0xf0, 0x30]
            else:
                assert rom[0][0x46a] == 0 and all(v == 0xa5 for v in rom[0][0x46b:0x47d])
        elif case < 8:
            required += [0x9bcb, 0x9bd2, 0x9bd3, 0x9bdc]
            expected = [(0xc0, 0xc0), (0x30, 0xb0), (0xe0, 0xa0), (0x60, 0x70)][case - 4]
            assert [rom[0][a] for a in [0x46a, 0x46b, 0x471, 0x477]] == [1, 1, *expected]
        elif case < 16:
            required += [0x9bcb, 0x9bd2, 0x9bd3, 0x9bdc]
            slot = min(case - 8, 5)
            assert [rom[0][a + slot] for a in [0x16, 0x58, 0x6e, 0x87, 0xcf, 0xb6]] == [0x32, 0xb0, 1, 0x70, 0xb0, 1]
            assert [rom[0][0x590], rom[0][0x5a0]] == [0x67, 0x68]
        else:
            required += [0x9baf, 0x9bba]
            assert hits.get(0x9bb5, 0) == (1 if case in (16, 19) else 0), (case, 'fixed length gate')
            if case in (16, 17):
                required += [0x9bcb, 0x9bd2, 0x9bd3, 0x9bdc]
                assert [rom[0][a] for a in [0xf, 0x16, 0x58, 0x6e, 0x87, 0xcf, 0x417, 0x434]] == [1, 13, 1, 1, 0x68, 0xa0, 0x88, 0xa0]
            else:
                assert rom[0][0x16] == 0x32 and hits.get(0x9bd3, 0) == 0, (case, 'no creation')
            tiles = [0x13, 0x15, 0x15] if case == 18 else [0x12, 0x14, 0x14]
            assert [rom[0][a] for a in [0x580, 0x590, 0x5a0]] == tiles
        assert all(hits.get(pc, 0) for pc in required), (case, 'missing PC', required)
        residuals = []
        for sample, (a, b) in enumerate(zip(rom, native)):
            diff = [i for i in range(2048) if a[i] != b[i]]
            assert not [i for i in diff if i not in excluded], (case, sample, 'persistent mismatch', diff)
            residuals.append([hex(i) for i in diff])
        results.append(dict(case=case, scopedMismatches=0, residualAddresses=residuals))
    (root / 'route-summary.json').write_text(json.dumps(results, indent=2) + '\n')
    print('20 original-ROM helper routes: zero persistent mismatches; scratch/stack/PPU residuals recorded')


if __name__ == '__main__':
    main()
