"""Verify the admitted cannon chain and exact child corrections against local ROM evidence."""
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
    assert directory.is_relative_to((Path(__file__).resolve().parents[1] / 'build').resolve())
    rom = args.rom.read_bytes()
    assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
    assert rom[16+0x39ba:16+0x39bc] == bytes((15, 7))
    assert rom[16+0x3a31:16+0x3a33] == bytes((24, 232))
    no_run = (0x17, 0x18, 0x19, 0x1a, 0x23, 0x30, 0x33)
    for enemy in no_run:
        offset = 16 + 0x4892 + (enemy-0x14)*2
        assert int.from_bytes(rom[offset:offset+2], 'little') == 0xc8d6
    excluded = set(range(8)) | set(range(256, 512)) | {0x778, 0x779}
    branch_addresses = (0xb9bf, 0xb9c7, 0xb9d4, 0xb9da, 0xb9df, 0xb9ec,
                        0xba1e, 0xba25, 0xba2e, 0xba36, 0xba3a, 0xba43,
                        0xba4a, 0xba5b, 0xba6e, 0xe8c0, 0xe8c9)
    branches = {pc: [0, 0] for pc in branch_addresses}
    visits = set()
    for case in range(25):
        original = frame(directory / ('cannon-rom-%d.msfr' % case), b'MSFR')
        with (directory / ('cannon-pc-%d.csv' % case)).open() as stream:
            pcs = {int(row['pc'], 16): row for row in csv.DictReader(stream)}
        visits.update(pc for pc, row in pcs.items() if int(row['hits']))
        for pc, row in pcs.items():
            if pc in branches:
                branches[pc][0] += int(row['fallthrough2'])
                branches[pc][1] += int(row['other'])
        if case >= 18:
            assert int(pcs[0xc8d6]['hits']) == 1, (case, 'NoRunCode')
        if case in (16, 17):
            assert int(pcs[0xc998]['hits']) == 1
            assert original[4+0x78a] == 0 and original[4+0x78e] != 0
        for bits in (32, 64):
            native = frame(directory / ('cannon-native%d-%d.msfn' % (bits, case)), b'MSFN')
            assert all(original[4+i] == native[4+i] for i in range(2048)
                       if i not in excluded), (case, bits, 'persistent RAM')
            assert original[2052:] == native[2052:], (case, bits, 'output')
        assert (directory / ('cannon-native32-%d.msfn' % case)).read_bytes() == (
            directory / ('cannon-native64-%d.msfn' % case)).read_bytes()
    code_nodes = dict(ProcessCannons=0xb9bc, ThreeSChk=0xb9c3, FireCannon=0xb9e9,
                      Chk_BB=0xba1a, Next3Slt=0xba2d, ExCannon=0xba30,
                      BulletBillHandler=0xba33, SetupBB=0xba4d, ChkDSte=0xba6a,
                      BBFly=0xba73, RunBBSubs=0xba76, KillBB=0xba85,
                      NoRunCode=0xc8d6, EraseEnemyObject=0xc998,
                      CheckForBulletBillCV=0xe8be, SBBAt=0xe8cd)
    assert all(pc in visits for pc in code_nodes.values())
    for pc in branch_addresses[:15]:
        assert all(branches[pc]), (hex(pc), branches[pc])
    # Cannon graphics branch accepts cannon and regular IDs; the cannon
    # priority timer takes both outcomes within these controlled routes.
    assert all(branches[0xe8c9]), branches
    summary = dict(codeNodes=list(code_nodes), dataNodes=['CannonBitmasks', 'BulletBillXSpdData'],
                   originalRoutes=25, widthRuns=50, persistentBytesPerSample=1782,
                   outputExceptions=[], branchCoverage={hex(k): v for k, v in branches.items()},
                   limits='Source-valid hard-mode selector 0/1. Player collision uses an '
                          'existing child and is inactive in these controlled routes; '
                          'no certification of its contact semantics, other graphics '
                          'branches, full enemy dispatch or GameEngine is implied.')
    (directory / 'cannon-verified.json').write_text(json.dumps(summary, indent=2)+'\n')
    print('Cannon and child correction: 25 original routes, 50 native runs; persistent RAM and full output match')


if __name__ == '__main__':
    main()
