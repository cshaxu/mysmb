"""Verify entrance caller contracts while retaining production child failures."""
import argparse
import csv
import json
import struct
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
    assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6]&4
    targets = [0x9131,0xb1c7,0xb206,0xb1e5,0xb2a4,0xb2ca,0x91cd,
               0xb069,0xb0e9,0xb233,0xb245,0xb269,0xb27d]
    assert list(struct.unpack_from('<13H',rom,16+0xb04f-0x8000)) == targets
    for selector,target in enumerate(targets):
        with (directory/('vector-%d.csv'%selector)).open() as stream:
            hits = {int(r['pc'],16):int(r['hits']) for r in csv.DictReader(stream)}
        assert hits.get(0xb04a,0)>0 and hits.get(target,0)>0
    nodes = dict(PlayerEntrance=0xb069,ChkBehPipe=0xb083,IntroEntr=0xb08d,
                 EntrMode2=0xb09b,VineEntr=0xb0ac,OffVine=0xb0c7,
                 PlayerRdy=0xb0d3,ExitEntr=0xb0e5,AutoControlPlayer=0xb0e6)
    branches = {p:[0,0] for p in (0xb06e,0xb076,0xb07d,0xb081,0xb086,
                 0xb093,0xb09e,0xb0a9,0xb0b1,0xb0bb,0xb0d1)}
    pcs,production = set(),[]
    for case in range(22):
        snapshot = directory/('entrance-%d.bin'%case)
        assert snapshot.read_bytes() == (directory/('children-%d.bin'%case)).read_bytes()
        frame = (directory/('entrance-%d.msfr'%case)).read_bytes()
        assert frame == (directory/('children-%d.msfr'%case)).read_bytes()
        assert frame == (directory/('unobserved-%d.msfr'%case)).read_bytes()
        with (directory/('entrance-%d.csv'%case)).open() as stream:
            for row in csv.DictReader(stream):
                pc = int(row['pc'],16)
                if not int(row['hits']):continue
                pcs.add(pc)
                if pc in branches:
                    assert rom[16+pc-0x8000] in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0)
                    branches[pc][0] += int(row['fallthrough2'])
                    branches[pc][1] += int(row['other'])
        for bits in (32,64):
            subprocess.run([str(directory/('entrance-caller%d.exe'%bits)),str(snapshot),
                            str(directory/('children-%d.calls'%case))],check=True,timeout=10)
            result = subprocess.run([str(directory/('entrance-check%d.exe'%bits)),str(snapshot)],
                                    capture_output=True,text=True,timeout=10)
            assert result.returncode in (0,1)
            production.append(dict(case=case,bits=bits,exit=result.returncode,differences=result.stdout))
    assert all(p in pcs for p in nodes.values())
    assert all(all(v) for v in branches.values()),branches
    result = dict(nodes=['GameRoutines']+list(nodes),originalSelectors=13,
                  originalEntrances=22,callerChecks=44,persistentBytes=1784,
                  branches={hex(k):v for k,v in branches.items()},
                  productionMatches=sum(x['exit']==0 for x in production),
                  productionFailures=[x for x in production if x['exit']!=0],
                  wholeCallClaim=False,
                  limits='Caller-only proof uses original executed child returns. Native child failures remain failures; no completion credit for those children.')
    (directory/'entrance-verified.json').write_text(json.dumps(result,indent=2)+'\n')
    print('13 original vector targets; 11 branches with both outcomes; 44 caller checks pass.')
    print('Production whole-call:',result['productionMatches'],'matches,',len(result['productionFailures']),'failures retained.')


if __name__ == '__main__':
    main()
