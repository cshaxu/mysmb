"""Supervise the real root's exceptional exit with a held project-owned driver."""
import subprocess
import sys

run = subprocess.run([sys.argv[1], "--held-exit"], capture_output=True, timeout=4)
assert run.returncode == 0, (run.returncode, run.stdout, run.stderr)
assert b"host-restored; driver-storage-retained; exceptional-exit" in run.stdout
