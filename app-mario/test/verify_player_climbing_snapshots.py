"""Verify original climbing chain, table bindings and native entry/return results."""
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
lengths = {x: 2 for x in (0xa5,0xa9,0xa0,0xa2,0xa4,0xa6,0xc9,0xc0,
                         0xe6,0xc5,0x05,0xc4,0x65,0xe0,0x85,0x86,0x84,0x29,0x09,0x49,0x25,0xe5)}
lengths.update({x: 3 for x in (0xd9,0xad,0xb9,0xbd,0xac,0xae,0xcd,0x8d,0x8e,0x8c,0x20,0x4c,0xee,0xce,0xed,0x6d,0x2d,0x7d)})
lengths.update({x: 1 for x in (0x88,0xc8,0xe8,0xca,0x0a,0x4a,0x60,0x18,0x98,0xa8,0x38)})
branches = {}
pc = 0xb3cf
while pc < 0xb424:
    op = rom[16+pc-0x8000]
    if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):
        branches[pc] = [0,0]
        size = 2
    else:
        assert op in lengths, (hex(pc),hex(op))
        size = lengths[op]
    pc += size
assert pc == 0xb424 and len(branches) == 5
assert rom[16+0x33c7:16+0x33cf] == bytes([14,4,252,242,0,0,255,255])
symbols = b/'climbing-symbols.json'
nodes = json.loads(symbols.read_text())
admission = json.loads((b/'node-admission.json').read_text())
assert len(nodes) == 8 and set(nodes) == set(admission['scope'])
hits, production = {}, []
side_indices = set()
for case in range(37,109):
    snapshot = b/('movement-%d.bin'%case)
    assert snapshot.read_bytes() == (b/('coverage-%d.bin'%case)).read_bytes()
    assert (b/('movement-%d.msfr'%case)).read_bytes() == (b/('coverage-%d.msfr'%case)).read_bytes()
    assert (b/('movement-%d.msfr'%case)).read_bytes() == (b/('unobserved-%d.msfr'%case)).read_bytes()
    calls = (b/('movement-%d.calls'%case)).read_bytes()
    assert calls[:5] == b'MSWC\1' and len(calls) == 8+calls[5]*4098
    for offset in range(8,len(calls),4098):
        if calls[offset] != 6:
            continue
        entry = calls[offset+2:offset+2050]
        allowed = entry[0xc] & entry[0x490]
        if allowed and entry[0x789] == 0:
            side_indices.add((0 if allowed & 1 else 2)+(entry[0x33] != 1))
    with (b/('movement-%d.csv'%case)).open() as stream:
        for row in csv.DictReader(stream):
            pc = int(row['pc'],16)
            hits[pc] = hits.get(pc,0)+int(row['hits'])
            if pc in branches:
                branches[pc][0] += int(row['fallthrough2'])
                branches[pc][1] += int(row['other'])
    for bits in (32,64):
        result = subprocess.run([str(b/('climbing-check%d.exe'%bits)),
                                 str(b/('movement-%d.calls'%case))],
                                capture_output=True,text=True,timeout=10)
        assert result.returncode == 0, (case,bits,result.stdout,result.stderr)
        production.append(dict(case=case,bits=bits,exit=result.returncode,differences=result.stdout))
assert all(all(outcomes) for outcomes in branches.values()),branches
assert side_indices == {0,1,2,3},side_indices
assert all(hits.get(int(address,16),0)>0 for name,address in nodes.items() if not name.startswith('ClimbAdder'))
for i in range(0,len(production),2):
    assert production[i]['exit'] == production[i+1]['exit']
    assert production[i]['differences'] == production[i+1]['differences']
summary = dict(nativeChecks=144,persistentBytes=1784,
               branches={hex(pc):v for pc,v in branches.items()},nodes=nodes,
               tableBytes=8,limits='ClimbingSub entry/return proof; preceding physics remains separate.')
(b/'climbing-verified.json').write_text(json.dumps(summary,indent=2)+'\n')
print('144 original/native climbing checks pass; five branches both outcomes; eight table bytes match.')
