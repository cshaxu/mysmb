"""Verify coin-allocation caller proof and retain actual child failures."""
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
branches = {}
pc = 0xbb38
while pc < 0xbb96:
    op = rom[16+pc-0x8000]
    if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):
        branches[pc] = [0,0]
        size = 2
    else:
        assert op in lengths, (hex(pc),hex(op))
        size = lengths[op]
    pc += size
assert pc == 0xbb96
symbols = b/'coin-allocation-symbols.json'
nodes = json.loads(symbols.read_text())
admission = json.loads((b/'node-admission.json').read_text())
assert len(nodes) == 6 and set(nodes) == set(admission['scope'])
hits, production = {}, []
entry_variants, allocated_slots, setup_carries = set(), set(), set()
for case in range(48):
    snapshot = b/('coin-allocation-%d.bin'%case)
    payload = snapshot.read_bytes()
    entry_variants.add((payload[5],payload[6],payload[7]))
    allocated_slots.add(payload[2056+0x6b7])
    if payload[5]==2: setup_carries.add((payload[8+6]>>4)&1)
    assert snapshot.read_bytes() == (b/('coverage-%d.bin'%case)).read_bytes()
    assert (b/('coin-allocation-%d.msfr'%case)).read_bytes() == (b/('coverage-%d.msfr'%case)).read_bytes()
    assert (b/('coin-allocation-%d.msfr'%case)).read_bytes() == (b/('unobserved-%d.msfr'%case)).read_bytes()
    with (b/('coin-allocation-%d.csv'%case)).open() as stream:
        for row in csv.DictReader(stream):
            pc = int(row['pc'],16)
            hits[pc] = hits.get(pc,0)+int(row['hits'])
            if pc in branches:
                branches[pc][0] += int(row['fallthrough2'])
                branches[pc][1] += int(row['other'])
    for bits in (32,64):
        subprocess.run([str(b/('coin-allocation-caller%d.exe'%bits)),str(snapshot),
                        str(b/('coin-allocation-%d.calls'%case))],check=True,timeout=10)
        result = subprocess.run([str(b/('coin-allocation-check%d.exe'%bits)),str(snapshot)],
                                capture_output=True,text=True,timeout=10)
        assert result.returncode in (0,1),result.stderr
        production.append(dict(case=case,bits=bits,exit=result.returncode,differences=result.stdout))
assert entry_variants == {(1,0,0),(1,1,0),(2,0,0),(2,1,0)}
assert allocated_slots == {6,7,8} and setup_carries == {0,1}
assert all(all(v) for v in branches.values()),branches
assert all(hits.get(int(address,16),0)>0 for address in nodes.values())
for i in range(0,len(production),2):
    assert production[i]['exit'] == production[i+1]['exit']
    assert production[i]['differences'] == production[i+1]['differences']
summary = dict(callerChecks=96,persistentBytes=1791,
               branches={hex(pc):v for pc,v in branches.items()},nodes=nodes,
               productionMatches=sum(x['exit']==0 for x in production),
               productionFailures=[x for x in production if x['exit']!=0],
               wholeCallClaim=False,
               limits='Caller checks use observed original child returns; production failures remain failures.')
(b/'coin-allocation-verified.json').write_text(json.dumps(summary,indent=2)+'\n')
print('96 coin-allocation caller checks pass; source branch outcomes:', len(branches))
print('Actual production calls:',summary['productionMatches'],'matches,',len(summary['productionFailures']),'failures.')
