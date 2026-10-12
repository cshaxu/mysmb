"""Verify power-up actor caller proof and retain actual child failures."""
import argparse
import csv
import json
import subprocess
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('directory', type=Path)
parser.add_argument('rom', type=Path)
args = parser.parse_args()
b = args.directory.resolve()
assert b.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
rom = args.rom.read_bytes()
assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
lengths = {x: 2 for x in (0xb6,0xe9,0x69,0xa5,0xa9,0xa0,0xa2,0xa4,0xa6,0xc9,0xc0,
                         0xe6,0xc5,0x05,0xc4,0x65,0xe0,0x85,0x86,0x84,0x29,0x09,0x49,0x25,0xe5,0xb5,0x95,0xd6,0xb4,0xc6,0xb1,0x91,0xa1,0xc1)}
lengths.update({x: 3 for x in (0x99,0xbe,0xcc,0x0d,0xd9,0xad,0xb9,0xbd,0xac,0xae,0xcd,0x8d,0x8e,0x8c,0x20,0x4c,0xee,0xce,0xed,0x9d,0xbc,0x79)})
lengths.update({x: 1 for x in (0x88,0xc8,0xe8,0xca,0x0a,0x4a,0x60,0x18,0x98,0xa8,0x38,0xaa,0x8a)})
lengths[0x2a]=1
branches={};pc=0xbc85
while pc<0xbceb:
    op=rom[16+pc-0x8000]
    if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):
        branches[pc]=[0,0];size=2
    else:
        assert op in lengths,(hex(pc),hex(op));size=lengths[op]
    pc+=size
assert pc==0xbceb
nodes={'PowerUpObjHandler':0xbc85,'ShroomM':0xbcaa,'GrowThePowerUp':0xbcb3,'ChkPUSte':0xbcd2,'RunPUSubs':0xbcd8,'ExitPUp':0xbcea}
assert set(nodes)==set(json.loads((b/'node-admission.json').read_text())['scope'])
hits={};rows=[];child_ids=set();collected=[];retired=[]
for case in range(50):
    snapshot=b/('power-up-actor-%d.bin'%case);payload=snapshot.read_bytes()
    assert payload==(b/('coverage-%d.bin'%case)).read_bytes()
    assert (b/('power-up-actor-%d.msfr'%case)).read_bytes()==(b/('coverage-%d.msfr'%case)).read_bytes()==(b/('unobserved-%d.msfr'%case)).read_bytes()
    children=(b/('power-up-actor-%d.calls'%case)).read_bytes()
    for k in range(children[5]): child_ids.add(children[8+k*4098])
    if 44<=case<48 and payload[2056+0x14]==0: collected.append(case)
    if case>=48 and payload[2056+0x14]==0: retired.append(case)
    with (b/('power-up-actor-%d.csv'%case)).open() as stream:
        for row in csv.DictReader(stream):
            pc=int(row['pc'],16);hits[pc]=hits.get(pc,0)+int(row['hits'])
            if pc in branches:
                branches[pc][0]+=int(row['fallthrough2']);branches[pc][1]+=int(row['other'])
    for bits in (32,64):
        subprocess.run([str(b/('power-up-actor-caller%d.exe'%bits)),str(snapshot),str(b/('power-up-actor-%d.calls'%case))],check=True,timeout=10)
        x=subprocess.run([str(b/('power-up-actor-check%d.exe'%bits)),str(snapshot)],capture_output=True,text=True,timeout=10)
        assert x.returncode in (0,1),x.stderr
        rows.append(dict(case=case,bits=bits,exit=x.returncode,differences=x.stdout))
assert all(all(v) for v in branches.values()),branches
assert all(hits.get(pc,0)>0 for pc in nodes.values())
assert child_ids==set(range(1,11)),child_ids
assert collected==[44,45,46,47] and retired==[48,49],(collected,retired)
for i in range(0,len(rows),2):
    assert (rows[i]['exit'],rows[i]['differences'])==(rows[i+1]['exit'],rows[i+1]['differences'])
summary=dict(callerChecks=100,persistentBytes=1791,nodes={n:hex(pc) for n,pc in nodes.items()},branches={hex(pc):v for pc,v in branches.items()},
             productionMatches=sum(x['exit']==0 for x in rows),productionFailures=[x for x in rows if x['exit']!=0],collected=collected,retired=retired)
(b/'power-up-actor-verified.json').write_text(json.dumps(summary,indent=2)+'\n')
print('100 caller checks passed; actual-child',summary['productionMatches'],'matches,',len(summary['productionFailures']),'failures; branches',len(branches))
