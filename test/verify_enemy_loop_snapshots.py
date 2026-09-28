"""Recheck bounded owner-local T38 loop evidence without hiding child failures."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

b = Path(sys.argv[1]).resolve()
rom = Path(sys.argv[2]).read_bytes()
assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
expected_tables = {
    0xc06b: [3, 3, 6, 6, 6, 6, 6, 6, 7, 7, 7],
    0xc076: [5, 9, 4, 5, 6, 8, 9, 10, 6, 11, 16],
    0xc081: [64, 176, 176, 128, 64, 64, 128, 64, 240, 240, 240],
    0x9bf8: [18, 54, 14, 14, 14, 50, 50, 50, 10, 38, 64],
}
for address, values in expected_tables.items():
    assert rom[16 + address - 0x8000:16 + address - 0x8000 + 11] == bytes(values)
branches = json.loads((b / 'loop-branch-audit.json').read_text())
assert len(branches) == 18
for address, (hits, fallthrough, taken) in branches.items():
    assert hits and taken and (fallthrough or address == '0xc113'), address
caller_matches = actual_matches = actual_failures = 0
for bits in ('32', '64'):
    for name in ('loop', 'dispatch', 'cannon'):
        subprocess.run([str(b / (name + bits + '.exe'))], check=True, timeout=20)
    for n in range(96):
        snapshot = b / ('loop-%d.bin' % n)
        calls = b / ('loop-%d.calls' % n)
        caller = subprocess.run([str(b / ('check-loop' + bits + '.exe')),
                                 str(snapshot), str(calls)], capture_output=True, timeout=20)
        assert caller.returncode == (1 if n in (93, 95) else 0), (bits, n, caller.stdout)
        caller_matches += caller.returncode == 0
        actual = subprocess.run([str(b / ('actual-loop' + bits + '.exe')),
                                 str(snapshot)], capture_output=True, timeout=20)
        assert actual.returncode in (0, 1)
        actual_matches += actual.returncode == 0
        actual_failures += actual.returncode == 1
        if actual.returncode:
            assert {line.split()[0] for line in actual.stdout.splitlines()} <= {
                b'0004', b'0005', b'0006', b'0007'}
            child = subprocess.run([str(b / ('actual-loop' + bits + '.exe')),
                                    str(b / ('child-%d.bin' % n))], capture_output=True, timeout=20)
            assert (child.returncode, child.stdout) == (actual.returncode, actual.stdout)
for artifact in json.loads((b / 'artifacts.json').read_text()):
    data = Path('assets/mysmb%d.exe' % artifact['bits']).read_bytes()
    assert len(data) == artifact['bytes']
    assert hashlib.sha256(data).hexdigest() == artifact['sha256']
assert (caller_matches, actual_matches, actual_failures) == (188, 12, 180)
assert sum(p.stat().st_size for p in b.iterdir()
           if p.suffix in ('.bin', '.calls', '.msfr', '.csv')) < 4000000
print('Caller checks 188/192; actual checks 12/192; 180 exact child differences retained.')
print('Seventeen two-outcome branches, unconditional branch, four tables, native checks and artifacts verified.')
