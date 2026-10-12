"""Verify fireball core caller proof and retain actual child failures."""
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
lengths = {x: 2 for x in (0x69,0xa5,0xa9,0xa0,0xa2,0xa4,0xa6,0xc9,0xc0,
                         0xe6,0xc5,0x05,0xc4,0x65,0xe0,0x85,0x86,0x84,0x29,0x09,0x49,0x25,0xe5,0xb5,0x95,0xd6,0xb4)}
lengths.update({x: 3 for x in (0xd9,0xad,0xb9,0xbd,0xac,0xae,0xcd,0x8d,0x8e,0x8c,0x20,0x4c,0xee,0xce,0xed,0x9d,0xbc)})
lengths.update({x: 1 for x in (0x88,0xc8,0xe8,0xca,0x0a,0x4a,0x60,0x18,0x98,0xa8,0x38,0xaa,0x8a)})
branches = {}
pc = 0xb689
while pc < 0xb6f9:
    op = rom[16+pc-0x8000]
    if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):
        branches[pc] = [0,0]
        size = 2
    else:
        assert op in lengths, (hex(pc),hex(op))
        size = lengths[op]
    pc += size
assert pc == 0xb6f9
symbols = b/'core-symbols.json'
nodes = json.loads(symbols.read_text())
admission = json.loads((b/'node-admission.json').read_text())
assert len(nodes) == 6 and set(nodes) == set(admission['scope'])
hits, production = {}, []
for case in range(32):
    snapshot = b/('core-%d.bin'%case)
    assert snapshot.read_bytes() == (b/('coverage-%d.bin'%case)).read_bytes()
    assert (b/('core-%d.msfr'%case)).read_bytes() == (b/('coverage-%d.msfr'%case)).read_bytes()
    assert (b/('core-%d.msfr'%case)).read_bytes() == (b/('unobserved-%d.msfr'%case)).read_bytes()
    with (b/('core-%d.csv'%case)).open() as stream:
        for row in csv.DictReader(stream):
            pc = int(row['pc'],16)
            hits[pc] = hits.get(pc,0)+int(row['hits'])
            if pc in branches:
                branches[pc][0] += int(row['fallthrough2'])
                branches[pc][1] += int(row['other'])
    for bits in (32,64):
        subprocess.run([str(b/('core-caller%d.exe'%bits)),str(snapshot),
                        str(b/('core-%d.calls'%case))],check=True,timeout=10)
        result = subprocess.run([str(b/('core-check%d.exe'%bits)),str(snapshot)],
                                capture_output=True,text=True,timeout=10)
        assert result.returncode in (0,1),result.stderr
        production.append(dict(case=case,bits=bits,exit=result.returncode,differences=result.stdout))
assert all(all(outcomes) for outcomes in branches.values()),branches
assert all(hits.get(int(address,16),0)>0 for name,address in nodes.items() if name != 'FireballXSpdData')
assert rom[16+0xb687-0x8000:16+0xb689-0x8000] == bytes((0x40,0xc0))
for i in range(0,len(production),2):
    assert production[i]['exit'] == production[i+1]['exit']
    assert production[i]['differences'] == production[i+1]['differences']
summary = dict(callerChecks=64,persistentBytes=1784,
               branches={hex(pc):v for pc,v in branches.items()},nodes=nodes,
               productionMatches=sum(x['exit']==0 for x in production),
               productionFailures=[x for x in production if x['exit']!=0],
               wholeCallClaim=False,
               limits='Caller checks use observed original child returns; production failures remain failures.')
(b/'core-verified.json').write_text(json.dumps(summary,indent=2)+'\n')
print('64 core caller checks pass; source branch outcomes:', len(branches))
print('Actual production calls:',summary['productionMatches'],'matches,',len(summary['productionFailures']),'failures.')
