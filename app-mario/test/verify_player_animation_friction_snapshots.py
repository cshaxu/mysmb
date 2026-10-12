"""Verify original animation timing and friction entry/return semantics."""
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
                         0xe6,0xc5,0x05,0xc4,0x65,0xe0,0x85,0x86,0x84,0x29,0x09,0x49,0x25,0xe5,0x69)}
lengths.update({x: 3 for x in (0xd9,0xad,0xb9,0xbd,0xac,0xae,0xcd,0x8d,0x8e,0x8c,0x20,0x4c,0xee,0xce,0xed,0x6d,0x2d,0x7d)})
lengths.update({x: 1 for x in (0x88,0xc8,0xe8,0xca,0x0a,0x4a,0x60,0x18,0x98,0xa8,0x38)})
branches = {}
pc = 0xb58f
while pc < 0xb624:
    op = rom[16+pc-0x8000]
    if op in (0x10,0x30,0x50,0x70,0x90,0xb0,0xd0,0xf0):
        branches[pc] = [0,0]
        size = 2
    else:
        assert op in lengths, (hex(pc),hex(op))
        size = lengths[op]
    pc += size
assert pc == 0xb624
assert rom[16+0x358c:16+0x358f] == bytes([2,4,7])
symbols = b/'animation-friction-symbols.json'
nodes = json.loads(symbols.read_text())
admission = json.loads((b/'node-admission.json').read_text())
assert len(nodes) == 12 and set(nodes) == set(admission['scope'])
hits, production = {}, []

for case in range(182,246):
    snapshot = b/('movement-%d.bin'%case)
    assert snapshot.read_bytes() == (b/('coverage-%d.bin'%case)).read_bytes()
    assert (b/('movement-%d.msfr'%case)).read_bytes() == (b/('coverage-%d.msfr'%case)).read_bytes()
    assert (b/('movement-%d.msfr'%case)).read_bytes() == (b/('unobserved-%d.msfr'%case)).read_bytes()
    with (b/('movement-%d.csv'%case)).open() as stream:
        for row in csv.DictReader(stream):
            pc = int(row['pc'],16)
            hits[pc] = hits.get(pc,0)+int(row['hits'])
            if pc in branches:
                branches[pc][0] += int(row['fallthrough2'])
                branches[pc][1] += int(row['other'])
    for bits in (32,64):
        result = subprocess.run([str(b/('animation_friction-check%d.exe'%bits)),
                                 str(b/('movement-%d.calls'%case))],
                                capture_output=True,text=True,timeout=10)
        assert result.returncode == 0, (case,bits,result.stdout,result.stderr)
        production.append(dict(case=case,bits=bits,exit=result.returncode,differences=result.stdout))
assert rom[16+0x35d7] == 0x10 and rom[16+0x35d9] == 0x30
# The preceding BPL has consumed N=0, so BMI cannot fall through.
assert branches[0xb5d9][0] == 0 and branches[0xb5d9][1] > 0
assert all(all(v) for pc,v in branches.items() if pc!=0xb5d9),branches
assert all(hits.get(int(address,16),0)>0 for name,address in nodes.items() if name!='PlayerAnimTmrData')
for i in range(0,len(production),2):
    assert production[i]['exit'] == production[i+1]['exit']
    assert production[i]['differences'] == production[i+1]['differences']
summary = dict(nativeChecks=256,persistentBytes=1784,
               branches={hex(pc):v for pc,v in branches.items()},nodes=nodes,
               unreachable={'0xb5d9:fallthrough':'Preceding BPL at B5D7 already consumes N=0.'},
               tableBytes=3,limits='Separate actual animation and friction calls; not whole-frame parity.')
(b/'animation-friction-verified.json').write_text(json.dumps(summary,indent=2)+'\n')
print('256 original/native animation/friction checks pass; three table bytes match.')
