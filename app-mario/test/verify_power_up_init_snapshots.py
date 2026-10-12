"""Verify complete power-up initialization RAM writes against original ROM snapshots."""
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
branches={};pc=0xbc49
while pc<0xbc85:
    op=rom[16+pc-0x8000]
    if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):
        branches[pc]=[0,0];size=2
    else:
        assert op in lengths,(hex(pc),hex(op));size=lengths[op]
    pc+=size
assert pc==0xbc85
nodes={'SetupPowerUp':0xbc49,'PwrUpJmp':0xbc60,'StrType':0xbc79,'PutBehind':0xbc7b}
assert set(nodes)==set(json.loads((b/'node-admission.json').read_text())['scope'])
hits={};rows=[];entries=set();slots=set();types=set();statuses=set()
for case in range(36):
    snapshot=b/('power-up-init-%d.bin'%case);payload=snapshot.read_bytes()
    entries.add(payload[5]);slots.add(payload[6]);types.add(payload[8+0x39]);statuses.add(payload[8+0x756])
    assert payload==(b/('coverage-%d.bin'%case)).read_bytes()
    assert (b/('power-up-init-%d.msfr'%case)).read_bytes()==(b/('coverage-%d.msfr'%case)).read_bytes()==(b/('unobserved-%d.msfr'%case)).read_bytes()
    assert (b/('power-up-init-%d.calls'%case)).read_bytes()==b'MS6C\x01\x00\x00\x00'
    with (b/('power-up-init-%d.csv'%case)).open() as stream:
        for row in csv.DictReader(stream):
            pc=int(row['pc'],16);hits[pc]=hits.get(pc,0)+int(row['hits'])
            if pc in branches:
                branches[pc][0]+=int(row['fallthrough2']);branches[pc][1]+=int(row['other'])
    for bits in (32,64):
        x=subprocess.run([str(b/('power-up-init-check%d.exe'%bits)),str(snapshot)],capture_output=True,text=True,timeout=10)
        rows.append(dict(case=case,bits=bits,exit=x.returncode,differences=x.stdout))
assert entries=={1,2} and slots=={0,1} and types=={0,2,3} and statuses=={0,1,2}
assert all(all(v) for v in branches.values()),branches
assert all(hits.get(pc,0)>0 for pc in nodes.values())
summary=dict(checks=72,ramBytes=2048,nodes={n:hex(pc) for n,pc in nodes.items()},branches={hex(pc):v for pc,v in branches.items()},
             matches=sum(x['exit']==0 for x in rows),failures=[x for x in rows if x['exit']!=0],entries=sorted(entries),slots=sorted(slots),types=sorted(types),statuses=sorted(statuses))
(b/'power-up-init-verified.json').write_text(json.dumps(summary,indent=2)+'\n')
print('Power-up initialization',summary['matches'],'/72 matches;',branches)
assert not summary['failures']
