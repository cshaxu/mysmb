"""Verify actual horizontal entries, branch coverage, scratch and return A."""
import argparse,csv,json,subprocess
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('directory',type=Path);p.add_argument('rom',type=Path);args=p.parse_args()
b=args.directory.resolve();rom=args.rom.read_bytes()
assert b.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
assert rom[:4]==b'NES\x1a' and rom[4]==2 and not rom[6]&4
read=lambda a,n:rom[16+a-0x8000:16+a-0x8000+n]
lengths = {x: 2 for x in (0xb6,0xe9,0x69,0xa5,0xa9,0xa0,0xa2,0xa4,0xa6,0xc9,0xc0,
                         0xe6,0xc5,0x05,0xc4,0x65,0xe0,0x85,0x86,0x84,0x29,0x09,0x49,0x25,0xe5,0xb5,0x95,0xd6,0xb4,0xc6,0xb1,0x91,0xa1,0xc1)}
lengths.update({x: 3 for x in (0x99,0xbe,0xcc,0x0d,0xd9,0xad,0xb9,0xbd,0xac,0xae,0xcd,0x8d,0x8e,0x8c,0x20,0x4c,0xee,0xce,0xed,0x9d,0xbc,0x79)})
lengths.update({x: 1 for x in (0x88,0xc8,0xe8,0xca,0x0a,0x4a,0x60,0x18,0x98,0xa8,0x38,0xaa,0x8a)})
lengths[0x2a]=1
lengths.update({0x48:1,0x68:1,0x6a:1,0x94:2,0x7d:3})
branches={};pc=0xbf02
while pc<0xbf4d:
 op=read(pc,1)[0]
 if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):branches[pc]=[0,0];size=2
 else:assert op in lengths,(hex(pc),hex(op));size=lengths[op]
 pc+=size
assert pc==0xbf4d
nodes={'MoveEnemyHorizontally':0xbf02,'MovePlayerHorizontally':0xbf09,'MoveObjectHorizontally':0xbf0f,'SaveXSpd':0xbf23,'UseAdder':0xbf2c,'ExXMove':0xbf4c}
assert set(nodes)==set(json.loads((b/'node-admission.json').read_text())['scope'])
hits={};rows=[];entries={};gates=set();returns=set()
for n in range(96):
 data=(b/('horizontal-%d.bin'%n)).read_bytes();assert len(data)==4104
 assert data==(b/('coverage-%d.bin'%n)).read_bytes()
 assert (b/('horizontal-%d.msfr'%n)).read_bytes()==(b/('coverage-%d.msfr'%n)).read_bytes()==(b/('unobserved-%d.msfr'%n)).read_bytes()
 entries[data[5]]=entries.get(data[5],0)+1;returns.add(data[7])
 if data[5]==1:gates.add(data[8+0x70e]!=0)
 with (b/('horizontal-%d.csv'%n)).open() as f:
  for row in csv.DictReader(f):
   pc=int(row['pc'],16);hits[pc]=hits.get(pc,0)+int(row['hits'])
   if pc in branches:branches[pc][0]+=int(row['fallthrough2']);branches[pc][1]+=int(row['other'])
 for bits in (32,64):
  x=subprocess.run([str(b/('horizontal-check%d.exe'%bits)),str(b/('horizontal-%d.bin'%n))],capture_output=True,text=True,timeout=10)
  rows.append(dict(case=n,bits=bits,exit=x.returncode,differences=x.stdout))
assert entries=={1:32,2:32,3:32} and gates=={False,True}
assert any(v>=128 for v in returns) and 0 in returns and any(0<v<128 for v in returns)
assert all(hits.get(pc,0)>0 for pc in nodes.values())
assert all(all(v) for v in branches.values()),branches
assert all(x['exit']==0 for x in rows),[x for x in rows if x['exit']][:4]
summary=dict(actualMatches=len(rows),comparedBytes=1799,returnAMatches=len(rows),nodes={k:hex(v) for k,v in nodes.items()},branches={hex(k):v for k,v in branches.items()},entries=entries,jumpspringBothOutcomes=True,failures=[])
(b/'horizontal-verified.json').write_text(json.dumps(summary,indent=2)+'\n');print('192 actual RAM/return-A matches;',len(branches),'two-outcome branches; all six nodes reached')
