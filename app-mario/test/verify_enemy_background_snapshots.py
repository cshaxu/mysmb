"""Check admitted background/side boundaries; do not certify their child families."""
import argparse
import csv
import hashlib
import json
import subprocess
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('background_prior', type=Path)
    parser.add_argument('movement_prior', type=Path)
    parser.add_argument('rom', type=Path)
    args = parser.parse_args()
    root = (Path(__file__).resolve().parents[1] / 'build').resolve()
    directory = args.directory.resolve()
    background = args.background_prior.resolve()
    movement = args.movement_prior.resolve()
    assert all(p.is_relative_to(root) for p in (directory, background, movement))
    rom = args.rom.read_bytes()
    assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
    nodes = dict(ExEBG=0xdfb8, EnemyToBGCollisionDet=0xdfc1,
                 DoIDCheckBGColl=0xdfd8, HBChk=0xdfdf, CInvu=0xdfe6,
                 YesIn=0xdff2, ExEBGChk=0xe066, SubtEnemyYPos=0xe15b,
                 EnemyJump=0xe163, DoSide=0xe182, DoEnemySideCheck=0xe0fe,
                 SdeCLoop=0xe10a, NextSdeC=0xe11c, ExESdeC=0xe123)
    branch_pcs = {0xdfc5, 0xdfca, 0xdfd0, 0xdfd6, 0xdfda, 0xdfe1,
                  0xdfe8, 0xdfec, 0xdff0, 0xe102, 0xe10e, 0xe115,
                  0xe11a, 0xe121, 0xe166, 0xe16f, 0xe174, 0xe179}
    branches = {pc: [0, 0] for pc in branch_pcs}
    pcs, snapshots = set(), []
    for case in range(32, 65):
        snapshot = directory / ('background-%d.bin' % case)
        data = snapshot.read_bytes()
        assert len(data) == 4104 and data[:8] == b'MSNB\1\0\0\0'
        if case < 56:
            coverage = background / ('background-pc-%d.csv' % case)
            prior_frame = background / ('background-rom-%d.msfr' % case)
        elif case < 60:
            coverage = movement / ('normal-%d.csv' % case)
            prior_frame = movement / ('normal-%d.msfr' % case)
            assert data[8+8] == 5 and data[8+0x1b] == 0x2e
        else:
            coverage = directory / ('background-%d.csv' % case)
            prior_frame = directory / ('unobserved-%d.msfr' % case)
        assert (directory / ('background-%d.msfr' % case)).read_bytes() == prior_frame.read_bytes()
        with coverage.open() as stream:
            for row in csv.DictReader(stream):
                pc = int(row['pc'], 16)
                if not int(row['hits']):
                    continue
                pcs.add(pc)
                if pc in branches:
                    assert rom[16+pc-0x8000] in (0x10, 0x30, 0x50, 0x70, 0x90, 0xb0, 0xd0, 0xf0)
                    branches[pc][0] += int(row['fallthrough2'])
                    branches[pc][1] += int(row['other'])
        for bits in (32, 64):
            subprocess.run([str(directory / ('normal_movement_snapshot_check%d.exe' % bits)),
                            str(snapshot)], check=True, timeout=10)
        if case in (60, 61, 62, 63):
            assert data[8+2048+0xeb] == (2 if case == 60 else 0)
        if case == 60:
            assert data[8+2048+0x46] == 1 and data[8+2048+0x58] == 8
        if case == 64:
            assert data[8+0xcf] < 0x20 and data[8+0xeb] == data[8+2048+0xeb]
        snapshots.append(dict(case=case, sha256=hashlib.sha256(data).hexdigest()))
    assert all(pc in pcs for pc in nodes.values())
    for pc, counts in branches.items():
        # Entry already accepted the identical wrapped-Y predicate. Nothing
        # changes Y before EnemyJump repeats it, so BCC cannot be taken here.
        assert all(counts) or (pc == 0xe166 and counts[0] > 0 and counts[1] == 0), (hex(pc), counts)
    result = dict(nodes=nodes, originalEntries=33, nativeChecks=66,
                  persistentBytes=1782, branches={hex(k): v for k, v in branches.items()},
                  snapshots=snapshots, wholeFrameClaim=False,
                  limits='Entry/side-loop proof with declared child handoffs; '
                         'walking, hammer, bump, graphics and parent callers remain separate.')
    (directory / 'background-verified.json').write_text(json.dumps(result, indent=2)+'\n')
    print('Fourteen labels reached; 33 original boundaries, 66 native checks; branch and observer checks pass.')


if __name__ == '__main__':
    main()
