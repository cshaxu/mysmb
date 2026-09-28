"""Verify the original bump/content/lookup chain with actual children."""
import argparse,csv,json,subprocess,struct
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('directory',type=Path);p.add_argument('rom',type=Path);args=p.parse_args()
b=args.directory.resolve();rom=args.rom.read_bytes()
assert b.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
assert rom[:4]==b'NES\x1a' and rom[4]==2 and not rom[6]&4
read=lambda a,n:rom[16+a-0x8000:16+a-0x8000+n]
assert read(0xbde8,14)==bytes([0xc1,0xc0,0x5f,0x60,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e])
assert struct.unpack('<9H',read(0xbdc0,18))==(0xbdd2,0xbb38,0xbb38,0xbdd8,0xbdd2,0xbddf,0xbdd5,0xbb38,0xbdd8)
assert read(0xbdd2,8)==bytes([0xa9,0,0x2c,0xa9,2,0x2c,0xa9,3])
lengths = {x: 2 for x in (0xb6,0xe9,0x69,0xa5,0xa9,0xa0,0xa2,0xa4,0xa6,0xc9,0xc0,
                         0xe6,0xc5,0x05,0xc4,0x65,0xe0,0x85,0x86,0x84,0x29,0x09,0x49,0x25,0xe5,0xb5,0x95,0xd6,0xb4,0xc6,0xb1,0x91,0xa1,0xc1)}
lengths.update({x: 3 for x in (0x99,0xbe,0xcc,0x0d,0xd9,0xad,0xb9,0xbd,0xac,0xae,0xcd,0x8d,0x8e,0x8c,0x20,0x4c,0xee,0xce,0xed,0x9d,0xbc,0x79)})
lengths.update({x: 1 for x in (0x88,0xc8,0xe8,0xca,0x0a,0x4a,0x60,0x18,0x98,0xa8,0x38,0xaa,0x8a)})
lengths[0x2a]=1
lengths.update({0x48:1,0x68:1,0x6a:1,0x94:2,0x7d:3})
lengths[0x2c]=3
branches={}
for first,last in ((0xbd9b,0xbdc0),(0xbdd2,0xbde8),(0xbdf6,0xbe02)):
 pc=first
 while pc<last:
  op=read(pc,1)[0]
  if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):branches[pc]=[0,0];size=2
  else:assert op in lengths,(hex(pc),hex(op));size=lengths[op]
  pc+=size
 assert pc==last
nodes={'BumpBlock':0xbd9b,'BlockCode':0xbdbd,'MushFlowerBlock':0xbdd2,'StarBlock':0xbdd5,'ExtraLifeMushBlock':0xbdd8,'VineBlock':0xbddf,'ExitBlockChk':0xbde7,'BlockBumpedChk':0xbdf6,'BumpChkLoop':0xbdf8,'MatchBump':0xbe01}
assert set(nodes)|{'BrickQBlockMetatiles'}==set(json.loads((b/'node-admission.json').read_text())['scope'])
hits={};rows=[];children=set();coin_above=[]
for n in range(60):
 assert (b/('block-bump-%d.bin'%n)).read_bytes()==(b/('coverage-%d.bin'%n)).read_bytes()
 assert (b/('block-bump-%d.msfr'%n)).read_bytes()==(b/('coverage-%d.msfr'%n)).read_bytes()==(b/('unobserved-%d.msfr'%n)).read_bytes()
 calls=(b/('block-bump-%d.calls'%n)).read_bytes()
 for i in range(calls[5]):children.add(calls[8+i*4098])
 first=calls[8:4106];assert first[0]==1
 if first[2050+0x75e]!=first[2+0x75e]:coin_above.append(n)
 with (b/('block-bump-%d.csv'%n)).open() as f:
  for row in csv.DictReader(f):
   pc=int(row['pc'],16);hits[pc]=hits.get(pc,0)+int(row['hits'])
   if pc in branches:branches[pc][0]+=int(row['fallthrough2']);branches[pc][1]+=int(row['other'])
 for bits in (32,64):
  for kind in ('caller','check','child'):
   files=[str(b/('block-bump-%d.%s'%(n,'calls' if kind=='child' else 'bin')))]
   if kind=='caller':files.append(str(b/('block-bump-%d.calls'%n)))
   x=subprocess.run([str(b/('bump-'+kind+str(bits)+'.exe'))]+files,capture_output=True,text=True,timeout=10)
   rows.append(dict(case=n,bits=bits,kind=kind,exit=x.returncode,differences=x.stdout))
assert all(all(v) for v in branches.values()),{hex(k):v for k,v in branches.items()}
assert all(hits.get(pc,0)>0 for pc in nodes.values())
assert children=={1,2,3,4} and coin_above==list(range(30,60)),coin_above
assert all(x['exit']==0 for x in rows),[x for x in rows if x['exit']][:2]
summary=dict(callerChecks=120,productionMatches=120,childChecks=120,productionFailures=[],tables={'BrickQBlockMetatiles':'0xbde8'},nodes={n:hex(v) for n,v in nodes.items()},branches={hex(k):v for k,v in branches.items()},coinAboveCases=coin_above)
(b/'block-bump-verified.json').write_text(json.dumps(summary,indent=2)+'\n');print('120 caller, 120 actual, 120 independent child matches;',len(branches),'two-outcome branches; 30 coin-above cases')
