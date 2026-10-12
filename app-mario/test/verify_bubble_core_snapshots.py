"""Verify actual BubbleCheck and SetupBubble results at original NMI entries."""
import argparse,csv,json,subprocess
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('directory',type=Path);p.add_argument('rom',type=Path);a=p.parse_args()
b=a.directory.resolve();assert b.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
rom=a.rom.read_bytes();assert rom[:4]==b'NES\x1a' and rom[4]==2 and not rom[6]&4
lengths={x:2 for x in (0xa9,0x29,0x85,0xb5,0xc9,0xa0,0xa5,0x65,0x95,0x69,0xa4,0xe9)}
lengths.update({x:3 for x in (0xbd,0xad,0x9d,0xac,0xb9,0x8d,0xf9)})
lengths.update({x:1 for x in (0x4a,0x98,0x18,0x38,0x60)})
branches={};pc=0xb6f9
while pc<0xb74b:
    op=rom[16+pc-0x8000]
    if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):branches[pc]=[0,0];size=2
    else:assert op in lengths,(hex(pc),hex(op));size=lengths[op]
    pc+=size
assert pc==0xb74b and rom[16+0xb74b-0x8000:16+0xb74f-0x8000]==bytes((0xff,0x50,0x40,0x20))
symbols=json.loads((b/'bubble-symbols.json').read_text());admission=json.loads((b/'node-admission.json').read_text())
assert len(symbols)==8 and set(symbols)==set(admission['scope'])
hits={};rows=[];entries=set();randoms=set()
for case in range(30):
    snap=b/('bubble-%d.bin'%case);data=snap.read_bytes()
    assert len(data)==4104 and data[:5]==b'MSBP\1'
    entries.add((data[5],data[6]));randoms.add(data[8+2048+7])
    assert data==(b/('coverage-%d.bin'%case)).read_bytes()
    assert (b/('bubble-%d.msfr'%case)).read_bytes()==(b/('coverage-%d.msfr'%case)).read_bytes()==(b/('unobserved-%d.msfr'%case)).read_bytes()
    with (b/('bubble-%d.csv'%case)).open() as f:
        for row in csv.DictReader(f):
            pc=int(row['pc'],16);hits[pc]=hits.get(pc,0)+int(row['hits'])
            if pc in branches:
                branches[pc][0]+=int(row['fallthrough2']);branches[pc][1]+=int(row['other'])
    for bits in (32,64):
        result=subprocess.run([str(b/('bubble-check%d.exe'%bits)),str(snap)],capture_output=True,text=True,timeout=10)
        assert result.returncode==0,(case,bits,result.stdout,result.stderr)
        rows.append(dict(case=case,bits=bits,exit=0))
assert entries=={(entry,slot) for entry in (1,2) for slot in range(3)}
assert randoms=={0,1}
assert all(all(x) for x in branches.values()),branches
assert all(hits.get(int(v,16),0)>0 for k,v in symbols.items() if k not in ('Bubble_MForceData','BubbleTimerData'))
raw=sum(f.stat().st_size for f in b.iterdir() if f.suffix in ('.bin','.csv','.msfr'));assert raw<4000000
summary=dict(actualChecks=len(rows),persistentBytes=1785,branches={hex(k):v for k,v in branches.items()},nodes=symbols,rawBytes=raw,childSubstitution=False)
(b/'bubble-verified.json').write_text(json.dumps(summary,indent=2)+'\n');print(summary)
