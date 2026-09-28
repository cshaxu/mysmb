"""Check original WarpZoneObject NMI routes and the source enemy vector."""
import argparse
import csv
import json
from pathlib import Path
from verify_engine_tail_routes import frame


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('rom', type=Path)
    args = parser.parse_args()
    directory = args.directory.resolve()
    assert directory.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
    rom = args.rom.read_bytes()
    assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
    targets = [0xc8e0, 0xc935, 0xd295] + [0xc8d6]*4 + [0xc947]*8
    targets += [0xc8d6] + [0xc965]*7 + [0xc94d]*2
    targets += [0xd065, 0xbc85, 0xb94b, 0xc8d6, 0xd2d9,
                0xb8ba, 0xc8d6, 0xb7a4, 0xc8d7]
    assert len(targets) == 34
    base = 16+0xc892-0x8000
    assert [int.from_bytes(rom[base+i*2:base+i*2+2], 'little')
            for i in range(34)] == targets
    movement = [0xca77]*5 + [0xc9d8,0xca77,0xcb89,0xcc36,0xc934,
        0xcc4a,0xcc4a,0xc9b0,0xd3b0,0xcaf9,0xcaff,0xcb25,0xcf28,
        0xca77,0xc934,0xcedf]
    base = 16+0xc90a-0x8000
    assert [int.from_bytes(rom[base+i*2:base+i*2+2], 'little')
            for i in range(21)] == movement
    excluded = set(range(8)) | set(range(256,512)) | {0x778,0x779}
    branches = {0xb7a7: [0,0], 0xb7ad: [0,0]}
    for case in range(10):
        original = frame(directory/('warp-rom-%d.msfr'%case), b'MSFR')
        with (directory/('warp-pc-%d.csv'%case)).open() as stream:
            pcs = {int(row['pc'],16): row for row in csv.DictReader(stream)}
        assert int(pcs[0xb7a4]['hits']) == 1
        for pc, counts in branches.items():
            if pc in pcs:
                counts[0] += int(pcs[pc]['fallthrough2'])
                counts[1] += int(pcs[pc]['other'])
        erased = case < 6 or case == 9
        assert int(pcs.get(0xc998, {'hits':0})['hits']) == int(erased)
        slot = case if case < 6 else 0
        assert original[4+0xf+slot] == (0 if erased else 1)
        assert original[4+0x6d6] == (0 if case == 5 else (0x80 if erased else 0x7f))
        for bits in (32,64):
            native = frame(directory/('warp-native%d-%d.msfn'%(bits,case)), b'MSFN')
            assert all(original[4+i] == native[4+i] for i in range(2048)
                       if i not in excluded), (case,bits,'persistent RAM')
            assert original[2052:] == native[2052:], (case,bits,'output')
    assert all(all(counts) for counts in branches.values()), branches
    result = dict(nodes=['WarpZoneObject'],originalRoutes=10,nativeRuns=20,
                  vectorEntries=34,movementVectorEntries=21,persistentBytesPerSample=1782,
                  branchCoverage={hex(k):v for k,v in branches.items()},
                  outputExceptions=[],limits='Controlled NMI input; other vector '
                  'targets and GameEngine are not certified by these routes.')
    (directory/'warp-verified.json').write_text(json.dumps(result,indent=2)+'\n')
    print('Warp: ten original routes match both widths; both branches covered; 34 ROM vector entries bound')


if __name__ == '__main__':
    main()
