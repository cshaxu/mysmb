"""Bounded, matched DOSBox ISA benchmark; no persistent emulator changes."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import statistics
import subprocess
import time


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--directory', type=Path, required=True)
    parser.add_argument('--dosbox', type=Path, required=True)
    parser.add_argument('--config', type=Path, required=True)
    parser.add_argument('--runs', type=int, default=3)
    args = parser.parse_args()
    assert 1 <= args.runs <= 3
    root = args.directory.resolve()
    repository = Path(__file__).resolve().parents[1]
    root.relative_to(repository / 'build')
    config_hash = hashlib.sha256(args.config.read_bytes()).hexdigest()
    records = []
    hashes = {}
    for repeat in range(1, args.runs + 1):
        output = root / ('run-' + str(repeat))
        output.mkdir(exist_ok=True)
        commands = []
        for variant in ('current', 'i86'):
            shutil.copyfile(root / variant / 'mysmb-dos16.exe', output / (variant + '.exe'))
        # Reverse order on alternate repetitions; identical fixed cycle budget.
        order = ('current', 'i86') if repeat & 1 else ('i86', 'current')
        for mask in (3, 7):
            for variant in order:
                tag = variant[0].upper() + str(mask)
                commands.extend([variant + '.exe ' + str(mask),
                    'ren TIME.LOG ' + tag + '.LOG', 'ren FRAME.BIN ' + tag + '.BIN'])
        (output / 'boot.conf').write_text('[cpu]\ncycles=fixed 3000\n[autoexec]\n'
            'mount c "' + str(output) + '"\nc:\nSET BLASTER=\n' + '\n'.join(commands) + '\nexit\n')
        startup = subprocess.STARTUPINFO()
        startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        startup.wShowWindow = 0
        start = time.perf_counter()
        with (output / 'host.log').open('w') as log:
            process = subprocess.Popen([str(args.dosbox), '-conf', str(args.config),
                '-conf', str(output / 'boot.conf'), '-noconsole'], cwd=output,
                env=dict(os.environ, SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy'),
                startupinfo=startup, stdout=log, stderr=subprocess.STDOUT)
            try:
                assert process.wait(timeout=180) == 0
            finally:
                if process.poll() is None:
                    process.terminate()
                    process.wait(timeout=5)
        for mask in (3, 7):
            current = (output / ('C' + str(mask) + '.BIN')).read_bytes()
            candidate = (output / ('I' + str(mask) + '.BIN')).read_bytes()
            assert len(current) == 16 * (32 + 2048 + 61440), len(current)
            assert candidate == current, ('RAM/palette/pixels differ', repeat, mask)
            digest = hashlib.sha256(current).hexdigest()
            assert hashes.setdefault(str(mask), digest) == digest, 'Non-deterministic repeat'
            for variant in ('current', 'i86'):
                lines = (output / (variant[0].upper() + str(mask) + '.LOG')).read_text().splitlines()
                assert lines[-1].startswith('done title=8 gameplay=8'), lines[-1]
                for line in lines:
                    if line.startswith('phase='):
                        sample = {k: int(v) for k, v in (x.split('=') for x in line.split())}
                        records.append(dict(sample, variant=variant, mask=mask, repeat=repeat))
        assert config_hash == hashlib.sha256(args.config.read_bytes()).hexdigest()
        print('repeat', repeat, 'AB/ABC RAM/palette/pixels match; wall seconds',
              round(time.perf_counter() - start, 3), flush=True)
    summaries = []
    for mask in (3, 7):
        for phase in (0, 1):
            for variant in ('current', 'i86'):
                samples = [r for r in records if r['mask'] == mask and r['phase'] == phase and r['variant'] == variant]
                fields = {}
                for name in ('logic', 'prepare', 'compose', 'publish', 'whole_raw'):
                    values = [r[name] * 1000 / 1193182 for r in samples]
                    fields[name] = dict(medianMs=statistics.median(values),
                        meanMs=statistics.mean(values), minimumMs=min(values), maximumMs=max(values))
                summaries.append(dict(mask=mask, phase=phase, variant=variant,
                                      samples=len(samples), stages=fields))
    receipt = dict(configUnchanged=True, cycles=3000, runs=args.runs,
        hashes=hashes, samples=records, summaries=summaries,
        scope='fixed-budget instruction-cost comparison; not cycle-accurate 8088 hardware timing')
    (root / 'benchmark.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(json.dumps(summaries, indent=2))


if __name__ == '__main__':
    main()
