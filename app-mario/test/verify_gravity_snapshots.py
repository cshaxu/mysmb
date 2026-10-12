"""Verify original gravity routes and separately audit the residual prefix."""
import argparse
import csv
import json
import re
import subprocess
from pathlib import Path

p = argparse.ArgumentParser(description=__doc__)
p.add_argument('directory', type=Path)
p.add_argument('previous', type=Path)
p.add_argument('rom', type=Path)
p.add_argument('listing', type=Path)
a = p.parse_args()
b, previous = a.directory.resolve(), a.previous.resolve()
build = (Path(__file__).resolve().parents[1] / 'build').resolve()
assert b.is_relative_to(build) and previous.is_relative_to(build)
rom = a.rom.read_bytes()
assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
read = lambda pc, size: rom[16 + pc - 0x8000:16 + pc - 0x8000 + size]
nodes = dict(zip(
    ('MaxSpdBlockData', 'ResidualGravityCode', 'ImposeGravityBlock',
     'ImposeGravitySprObj', 'MovePlatformDown', 'MovePlatformUp',
     'SetDplSpd', 'RedPTroopaGrav', 'ImposeGravity', 'AlterYP', 'ChkUpM', 'ExVMove'),
    (0xbf9f, 0xbfa1, 0xbfa4, 0xbfad, 0xbfb4, 0xbfb7,
     0xbfc5, 0xbfd1, 0xbfd7, 0xbfe9, 0xc018, 0xc046)))
assert set(nodes) == set(json.loads((b / 'node-admission.json').read_text())['scope'])
# Data binding and overlapping BIT/LDY entries: residual selects table index
# zero and skips LDY #1. BIT affects flags only; subsequent ADC has explicit CLC.
assert list(read(0xbf9f, 2)) == [6, 8]
assert list(read(0xbfa1, 5)) == [0xa0, 0, 0x2c, 0xa0, 1]
assert list(read(0xbfaa, 4)) == [0xb9, 0x9f, 0xbf, 0x85]
assert list(read(0xbfb4, 5)) == [0xa9, 0, 0x2c, 0xa9, 1]
source = '\n'.join(line.split(';')[0] for line in a.listing.read_text().splitlines())
assert len(re.findall(r'\bResidualGravityCode\b', source)) == 1
assert re.search(r'^ResidualGravityCode:', source, re.M)
# This establishes no symbolic incoming edge in the admitted disassembly;
# it is explicitly not an executed-ROM claim for the residual entry.
hits, branches, results = {}, {}, []
for directory, prefix in ((b, 'gravity'), (previous, 'vertical')):
    for n in range(32):
        root = directory / ('%s-%d.bin' % (prefix, n))
        data = root.read_bytes()
        assert len(data) == 4104
        if directory == b:
            assert data[:5] == b'MS9P\1' and data[5] == n // 8
            assert data == (b / ('observed-%d.bin' % n)).read_bytes()
            assert (b / ('gravity-%d.msfr' % n)).read_bytes() == (
                b / ('observed-%d.msfr' % n)).read_bytes() == (
                b / ('unobserved-%d.msfr' % n)).read_bytes()
        with (directory / ('%s-%d.csv' % (prefix, n))).open() as f:
            for r in csv.DictReader(f):
                pc = int(r['pc'], 16)
                counts = hits.setdefault(pc, [0, 0, 0])
                for i, key in enumerate(('hits', 'fallthrough2', 'other')):
                    counts[i] += int(r[key])
        for bits in (32, 64):
            exe = 'gravity-check%d.exe' if directory == b else 'vertical-actual%d.exe'
            run = subprocess.run([str(b / (exe % bits)), str(root)],
                                 capture_output=True, text=True, timeout=10)
            results.append(dict(route=prefix, case=n, bits=bits,
                                exit=run.returncode, differences=run.stdout))
for pc in (0xbfe6, 0xc006, 0xc00d, 0xc019, 0xc034, 0xc03b):
    assert read(pc, 1)[0] in (0x10, 0x30, 0x90, 0xb0, 0xf0)
    branches[hex(pc)] = hits[pc]
    assert all(hits[pc][1:])
assert hits[0xbfc1][1] == 0 and hits[0xbfc1][2] > 0
for name, pc in nodes.items():
    if name not in ('MaxSpdBlockData', 'ResidualGravityCode'):
        assert hits.get(pc, [0])[0], name
assert hits.get(0xbfa1, [0])[0] == 0
assert all(r['exit'] == 0 for r in results), [r for r in results if r['exit']][:4]
native = []
for bits in (32, 64):
    run = subprocess.run([str(b / ('gravity-smoke%d.exe' % bits))],
                         capture_output=True, text=True, timeout=10)
    assert run.returncode == 0, run.stdout
    native.append(dict(bits=bits, output=run.stdout, exit=run.returncode))
summary = dict(nodes={n: hex(pc) for n, pc in nodes.items()}, actualMatches=128,
               comparedBytes=1799, branches=branches, failures=[], native=native,
               residualProof='ROM prefix/data and no symbolic incoming edge; native entry plus reached common successor, no forced ROM execution',
               platformResidualArm='Native ID29 selection; ordinary ROM paths only take BFC1 branch')
(b / 'gravity-verified.json').write_text(json.dumps(summary, indent=2) + '\n')
print('128 actual gravity matches; six two-outcome branches; residual proof is static/native only')
