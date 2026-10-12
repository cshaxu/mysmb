"""Verify original head-hit caller branches while retaining child failures."""
import argparse,csv,json,subprocess
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('directory',type=Path);p.add_argument('rom',type=Path);args=p.parse_args()
b=args.directory.resolve();rom=args.rom.read_bytes()
assert b.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
assert rom[:4]==b'NES\x1a' and rom[4]==2 and not rom[6]&4
assert rom[16+0x3ceb:16+0x3ced]==bytes([4,18])
lengths = {x: 2 for x in (0xb6,0xe9,0x69,0xa5,0xa9,0xa0,0xa2,0xa4,0xa6,0xc9,0xc0,
                         0xe6,0xc5,0x05,0xc4,0x65,0xe0,0x85,0x86,0x84,0x29,0x09,0x49,0x25,0xe5,0xb5,0x95,0xd6,0xb4,0xc6,0xb1,0x91,0xa1,0xc1)}
lengths.update({x: 3 for x in (0x99,0xbe,0xcc,0x0d,0xd9,0xad,0xb9,0xbd,0xac,0xae,0xcd,0x8d,0x8e,0x8c,0x20,0x4c,0xee,0xce,0xed,0x9d,0xbc,0x79)})
lengths.update({x: 1 for x in (0x88,0xc8,0xe8,0xca,0x0a,0x4a,0x60,0x18,0x98,0xa8,0x38,0xaa,0x8a)})
lengths[0x2a]=1
lengths.update({0x48:1,0x68:1,0x6a:1,0x94:2,0x7d:3})
pc=0xbced;branches={}
while pc<0xbd9b:
 op=rom[16+pc-0x8000]
 if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):branches[pc]=[0,0];size=2
 else:assert op in lengths,(hex(pc),hex(op));size=lengths[op]
 pc+=size
assert pc==0xbd9b
nodes={'PlayerHeadCollision':0xbced,'DBlockSte':0xbcfa,'ChkBrick':0xbd1a,'StartBTmr':0xbd2c,'ContBTmr':0xbd39,'PutOldMT':0xbd40,'PutMTileB':0xbd41,'SmallBP':0xbd61,'BigBP':0xbd62,'Unbreak':0xbd78,'InvOBit':0xbd7b,'InitBlock_XY_Pos':0xbd84}
assert set(nodes)|{'BlockYPosAdderData'}==set(json.loads((b/'node-admission.json').read_text())['scope'])
hits={};rows=[];children=set()
for n in range(72):
 assert (b/('block-head-%d.bin'%n)).read_bytes()==(b/('coverage-%d.bin'%n)).read_bytes()
 assert (b/('block-head-%d.msfr'%n)).read_bytes()==(b/('coverage-%d.msfr'%n)).read_bytes()==(b/('unobserved-%d.msfr'%n)).read_bytes()
 calls=(b/('block-head-%d.calls'%n)).read_bytes()
 for i in range(calls[5]):children.add(calls[8+i*4098])
 with (b/('block-head-%d.csv'%n)).open() as f:
  for row in csv.DictReader(f):
   pc=int(row['pc'],16);hits[pc]=hits.get(pc,0)+int(row['hits'])
   if pc in branches:branches[pc][0]+=int(row['fallthrough2']);branches[pc][1]+=int(row['other'])
 for bits in (32,64):
  subprocess.run([str(b/('head-caller%d.exe'%bits)),str(b/('block-head-%d.bin'%n)),str(b/('block-head-%d.calls'%n))],check=True,timeout=10)
  x=subprocess.run([str(b/('head-check%d.exe'%bits)),str(b/('block-head-%d.bin'%n))],capture_output=True,text=True,timeout=10)
  assert x.returncode in (0,1),x.stderr
  rows.append(dict(case=n,bits=bits,exit=x.returncode,differences=x.stdout))
assert all(all(v) for v in branches.values()),{hex(k):v for k,v in branches.items()}
assert all(hits.get(pc,0)>0 for pc in nodes.values())
assert children=={1,2,3,4},children
for i in range(0,len(rows),2):assert (rows[i]['exit'],rows[i]['differences'])==(rows[i+1]['exit'],rows[i+1]['differences'])
summary=dict(callerChecks=144,persistentBytes=1791,tables={'BlockYPosAdderData':'0xbceb'},nodes={n:hex(v) for n,v in nodes.items()},branches={hex(k):v for k,v in branches.items()},productionMatches=sum(x['exit']==0 for x in rows),productionFailures=[x for x in rows if x['exit']])
(b/'block-head-verified.json').write_text(json.dumps(summary,indent=2)+'\n');print('144 caller matches;',summary['productionMatches'],'actual matches;',len(summary['productionFailures']),'child failures;',len(branches),'two-outcome branches')
