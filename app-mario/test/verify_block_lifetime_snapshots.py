"""Verify block lifetime caller logic and retain actual drawing-child differences."""
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
lengths[0xd5]=2
lengths.update({0x48:1,0x68:1,0x6a:1,0x94:2,0x7d:3})
branches={};pc=0xbe70
while pc<0xbed4:
 op=read(pc,1)[0]
 if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):branches[pc]=[0,0];size=2
 else:assert op in lengths,(hex(pc),hex(op));size=lengths[op]
 pc+=size
assert pc==0xbed4
nodes={'BlockObjectsCore':0xbe70,'ChkTop':0xbeaa,'BouncingBlockHandler':0xbeb3,'KillBlock':0xbecf,'UpdSte':0xbed1}
assert set(nodes)==set(json.loads((b/'node-admission.json').read_text())['scope'])
hits={};rows=[];children=set();observed_slots=set()
for n in range(32):
 assert (b/('block-lifetime-%d.bin'%n)).read_bytes()==(b/('coverage-%d.bin'%n)).read_bytes()
 assert (b/('block-lifetime-%d.msfr'%n)).read_bytes()==(b/('coverage-%d.msfr'%n)).read_bytes()==(b/('unobserved-%d.msfr'%n)).read_bytes()
 calls=(b/('block-lifetime-%d.calls'%n)).read_bytes()
 ids=[calls[8+i*4098] for i in range(calls[5])];children.update(ids)
 observed_slots.add((b/('block-lifetime-%d.bin'%n)).read_bytes()[6])
 with (b/('block-lifetime-%d.csv'%n)).open() as f:
  for row in csv.DictReader(f):
   pc=int(row['pc'],16);hits[pc]=hits.get(pc,0)+int(row['hits'])
   if pc in branches:branches[pc][0]+=int(row['fallthrough2']);branches[pc][1]+=int(row['other'])
 for bits in (32,64):
  for kind in ('caller','check','child'):
   files=[str(b/('block-lifetime-%d.%s'%(n,'calls' if kind=='child' else 'bin')))]
   if kind=='caller':files.append(str(b/('block-lifetime-%d.calls'%n)))
   x=subprocess.run([str(b/('lifetime-'+kind+str(bits)+'.exe'))]+files,capture_output=True,text=True,timeout=10)
   assert x.returncode in (0,1),(kind,x.returncode,x.stderr)
   rows.append(dict(case=n,bits=bits,kind=kind,exit=x.returncode,differences=x.stdout))
# BCS KillBlock follows the non-taken BCC with no carry mutation.
assert read(0xbeb1,2)==bytes([0xb0,0x1c])
assert branches[0xbeb1][0]==0 and branches[0xbeb1][1]>0
assert all(all(v) for k,v in branches.items() if k!=0xbeb1),branches
assert all(hits.get(pc,0)>0 for pc in nodes.values())
assert children=={1,2,3,4,5,6} and observed_slots=={0,1}
assert all(x['exit']==0 for x in rows if x['kind']=='caller')
for n in range(32):
 for kind in ('check','child'):
  pair=[x for x in rows if x['case']==n and x['kind']==kind]
  assert pair[0]['differences']==pair[1]['differences']
# No unexplained non-OAM failure may be silently accepted as graphics debt.
failures=[x for x in rows if x['kind']=='check' and x['exit']]
for x in failures:
 assert x['differences'] and all(0x200<=int(line[:4],16)<0x300 for line in x['differences'].splitlines())
child_failures=[x for x in rows if x['kind']=='child' and x['exit']]
for x in child_failures:
 assert all(' id 5 differs' in line or ' id 6 differs' in line for line in x['differences'].splitlines() if line.startswith('child '))
summary=dict(callerChecks=64,comparedBytes=1791,nodes={n:hex(v) for n,v in nodes.items()},branches={hex(k):v for k,v in branches.items()},observedSlots=sorted(observed_slots),productionMatches=sum(x['exit']==0 for x in rows if x['kind']=='check'),productionFailures=failures,childFailures=child_failures)
(b/'block-lifetime-verified.json').write_text(json.dumps(summary,indent=2)+'\n')
print('64 caller matches;',summary['productionMatches'],'actual matches;',len(failures),'retained drawing failures; six two-outcome branches and source-unconditional BCS')
