"""Verify naturally reached original movement boundaries, not whole-game fidelity."""
import argparse
import csv
import hashlib
import json
import subprocess
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('prior', type=Path)
    parser.add_argument('rom', type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1] / 'build'
    directory, prior = args.directory.resolve(), args.prior.resolve()
    assert directory.is_relative_to(root.resolve())
    assert prior.is_relative_to(root.resolve())
    rom = args.rom.read_bytes()
    assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
    assert rom[16+0xc9d0-0x8000:16+0xc9d8-0x8000] == bytes(
        [0, 0xe8, 0, 0x18, 8, 0xf8, 12, 0xf4])
    nodes = dict(MoveD_EnemyVertically=0xbf63, MoveFallingPlatform=0xbf6b,
                 ContVMove=0xbf6d, MoveNormalEnemy=0xca77, FallE=0xca98,
                 MEHor=0xcaaf, SlowM=0xcab2, SteadM=0xcab4, AddHS=0xcabb,
                 ReviveStunned=0xcac8, SetRSpd=0xcadf,
                 MoveDefeatedEnemy=0xcae5, ChkKillGoomba=0xcaeb, NKGmba=0xcaf8)
    pcs, branches, snapshots = set(), {}, []
    for case in list(range(32)) + list(range(56, 60)):
        snapshot = directory / ('normal-%d.bin' % case)
        data = snapshot.read_bytes()
        assert len(data) == 4104 and data[:8] == b'MSNM\1\0\0\0'
        if case < 32:
            assert (directory / ('normal-%d.msfr' % case)).read_bytes() == (
                prior / ('normal-rom-%d.msfr' % case)).read_bytes()
            coverage = prior / ('normal-pc-%d.csv' % case)
        else:
            assert data[8+8] == 5 and data[8+0x1b] == 0x2e
            coverage = directory / ('normal-%d.csv' % case)
        with coverage.open() as stream:
            for row in csv.DictReader(stream):
                pc = int(row['pc'], 16)
                if not int(row['hits']):
                    continue
                pcs.add(pc)
                if (0xca77 <= pc <= 0xcaf8 or 0xbf63 <= pc <= 0xbf6d) and (
                        rom[16+pc-0x8000] in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0)):
                    counts = branches.setdefault(hex(pc), [0, 0])
                    counts[0] += int(row['fallthrough2'])
                    counts[1] += int(row['other'])
        for bits in (32, 64):
            subprocess.run([str(directory / ('movement-check%d.exe' % bits)),
                            str(snapshot)], check=True, timeout=10)
        snapshots.append(dict(case=case, sha256=hashlib.sha256(data).hexdigest()))
    assert all(pc in pcs for pc in nodes.values())
    for pc, counts in branches.items():
        # The preceding failed BEQ leaves Z clear: this BNE cannot fall through.
        assert all(counts) or (pc == '0xcaad' and counts[0] == 0 and counts[1] > 0), (pc, counts)
    result = dict(nodes=list(nodes) + ['XSpeedAdderData', 'RevivedXSpeed'],
                  originalEntries=36, nativeChecks=72, persistentBytes=1782,
                  branches=branches, snapshots=snapshots, wholeFrameClaim=False,
                  limits='Entry-to-natural-return proof of received movement nodes; '
                         'graphics, callers and complete game execution remain separate.')
    (directory / 'movement-verified.json').write_text(json.dumps(result, indent=2)+'\n')
    print('Sixteen nodes: 36 original entries, 72 native boundary checks; source tables and branches verified.')


if __name__ == '__main__':
    main()
