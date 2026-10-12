"""Verify S8 original-entry evidence; actual gravity failures stay explicit."""
import argparse
import csv
import json
import subprocess
from pathlib import Path

p = argparse.ArgumentParser(description=__doc__)
p.add_argument('directory', type=Path)
p.add_argument('rom', type=Path)
a = p.parse_args()
b = a.directory.resolve()
assert b.is_relative_to((Path(__file__).resolve().parents[1] / 'build').resolve())
rom = a.rom.read_bytes()
assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
nodes = dict(zip(
    ('MovePlayerVertically', 'NoJSChk', 'MoveD_EnemyVertically',
     'MoveFallingPlatform', 'ContVMove', 'MoveRedPTroopaDown',
     'MoveRedPTroopaUp', 'MoveRedPTroopa', 'MoveDropPlatform',
     'MoveEnemySlowVert', 'SetMdMax', 'MoveJ_EnemyVertically',
     'SetHiMax', 'SetXMoveAmt'),
    (0xbf4d, 0xbf59, 0xbf63, 0xbf6b, 0xbf6d, 0xbf70, 0xbf75,
     0xbf77, 0xbf88, 0xbf8c, 0xbf8e, 0xbf92, 0xbf94, 0xbf96)))
assert set(nodes) == set(json.loads((b / 'node-admission.json').read_text())['scope'])
branches = {x: [0, 0] for x in (0xbf52, 0xbf57, 0xbf69, 0xbf8a, 0xbf90)}
# Resolve original control transfers from the supplied ROM, not C outcomes.
edges = {0xbf52: 0xbf59, 0xbf57: 0xbf4c, 0xbf69: 0xbf6d,
         0xbf8a: 0xbf8e, 0xbf90: 0xbf96}
for pc, target in edges.items():
    op, delta = rom[16 + pc - 0x8000:18 + pc - 0x8000]
    assert op == 0xd0 and pc + 2 + (delta if delta < 128 else delta - 256) == target
for pc, op, target in ((0xbf60, 0x4c, 0xbfad), (0xbf6d, 0x4c, 0xbf94),
                       (0xbf72, 0x4c, 0xbf77), (0xbf85, 0x4c, 0xbfd1),
                       (0xbf99, 0x20, 0xbfad)):
    raw = rom[16 + pc - 0x8000:19 + pc - 0x8000]
    assert raw[0] == op and raw[1] + 256 * raw[2] == target
hits, results, gates, child_counts = {}, [], set(), []
for n in range(32):
    root = b / ('vertical-%d.bin' % n)
    calls = b / ('vertical-%d.calls' % n)
    data, children = root.read_bytes(), calls.read_bytes()
    assert len(data) == 4104 and data[:5] == b'MSVP\1' and data[5] == n // 4
    assert children[:5] == b'MSVC\1' and children[5] <= 1
    assert len(children) == 8 + children[5] * 4098
    child_counts.append(children[5])
    if n < 4:
        gates.add((data[8 + 0x747] != 0, data[8 + 0x70e] != 0))
    assert data == (b / ('coverage-%d.bin' % n)).read_bytes()
    assert (b / ('vertical-%d.msfr' % n)).read_bytes() == (
        b / ('coverage-%d.msfr' % n)).read_bytes() == (
        b / ('unobserved-%d.msfr' % n)).read_bytes()
    with (b / ('vertical-%d.csv' % n)).open() as f:
        for r in csv.DictReader(f):
            pc = int(r['pc'], 16)
            hits[pc] = hits.get(pc, 0) + int(r['hits'])
            if pc in branches:
                branches[pc][0] += int(r['fallthrough2'])
                branches[pc][1] += int(r['other'])
    for bits in (32, 64):
        for mode in ('caller', 'actual'):
            cmd = [str(b / ('vertical-%s%d.exe' % (mode, bits))), str(root)]
            if mode == 'caller':
                cmd.append(str(calls))
            run = subprocess.run(cmd, capture_output=True, text=True, timeout=10)
            results.append(dict(case=n, bits=bits, mode=mode,
                                exit=run.returncode, differences=run.stdout))
assert gates == {(False, False), (False, True), (True, False), (True, True)}
assert sum(child_counts) == 31 and child_counts[2] == 0
assert all(hits.get(pc, 0) for pc in nodes.values())
assert all(all(branches[pc]) for pc in (0xbf52, 0xbf57, 0xbf69))
assert all(branches[pc][0] == 0 and branches[pc][1] for pc in (0xbf8a, 0xbf90))
assert all(r['exit'] == 0 for r in results if r['mode'] == 'caller')
summary = dict(nodes={n: hex(pc) for n, pc in nodes.items()}, comparedBytes=1799,
               callerMatches=64, actualMatches=sum(r['exit'] == 0 for r in results
                                                  if r['mode'] == 'actual'),
               failures=[r for r in results if r['exit']],
               branches={hex(pc): counts for pc, counts in branches.items()})
(b / 'vertical-verified.json').write_text(json.dumps(summary, indent=2) + '\n')
print('64 caller matches; actual matches:', summary['actualMatches'],
      '; actual failures:', len(summary['failures']))
