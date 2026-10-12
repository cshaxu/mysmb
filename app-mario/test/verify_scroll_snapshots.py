"""Verify the admitted ScrollHandler chain at original natural boundaries."""
import argparse
import csv
import hashlib
import json
import subprocess
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('rom', type=Path)
    args = parser.parse_args()
    directory = args.directory.resolve()
    assert directory.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
    rom = args.rom.read_bytes()
    assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
    assert rom[16+0xb034-0x8000:16+0xb038-0x8000] == bytes([0, 16, 1, 2])
    nodes = dict(ScrollHandler=0xaf93, ChkNearMid=0xafba, ScrollScreen=0xafc4,
                 InitScrlAmt=0xaffb, ChkPOffscr=0xb000, KeepOnscr=0xb013,
                 InitPlatScrl=0xb02e, GetScreenPosition=0xb038)
    branches = {pc: [0, 0] for pc in (0xafa0, 0xafa7, 0xafac, 0xafb2,
                0xafb7, 0xafbf, 0xb00a, 0xb011, 0xb028)}
    pcs, snapshots = set(), []
    for case in range(24):
        snapshot = directory/('scroll-%d.bin' % case)
        data = snapshot.read_bytes()
        assert len(data) == 4104 and data[:8] == b'MSSC\1\0\0\0'
        assert (directory/('scroll-%d.msfr' % case)).read_bytes() == (
            directory/('unobserved-%d.msfr' % case)).read_bytes()
        with (directory/('scroll-%d.csv' % case)).open() as stream:
            for row in csv.DictReader(stream):
                pc = int(row['pc'], 16)
                if not int(row['hits']):
                    continue
                pcs.add(pc)
                if pc in branches:
                    assert rom[16+pc-0x8000] in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0)
                    branches[pc][0] += int(row['fallthrough2'])
                    branches[pc][1] += int(row['other'])
        for bits in (32,64):
            subprocess.run([str(directory/('scroll-check%d.exe' % bits)),str(snapshot)],
                           check=True,timeout=10)
        if case in (4,5):
            assert data[8+0x6ff] == 0x80
            assert data[2056+0x775] == (0x7f if case == 4 else 0x80)
        if case >= 20:
            assert data[2056] == 0x7f
            assert data[2056+0x6d] == 0xff and data[2056+0x86] == 0xff
        snapshots.append(dict(case=case,sha256=hashlib.sha256(data).hexdigest()))
    assert all(pc in pcs for pc in nodes.values())
    assert all(all(counts) for counts in branches.values()), branches
    result = dict(nodes=list(nodes)+['X_SubtracterData','OffscrJoypadBitsData'],
                  originalEntries=24,nativeChecks=48,persistentBytes=1784,
                  branches={hex(k):v for k,v in branches.items()},snapshots=snapshots,
                  wholeFrameClaim=False,
                  limits='Scroll chain only; upstream player physics and GetXOffscreenBits family retain separate proof status.')
    (directory/'scroll-verified.json').write_text(json.dumps(result,indent=2)+'\n')
    print('Ten labels: original tables and both outcomes of all nine branches; 48 native matches.')


if __name__ == '__main__':
    main()
