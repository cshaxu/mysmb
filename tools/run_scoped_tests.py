"""Build only targets of explicitly named CTests and run that exact scope."""
import argparse
import json
from pathlib import Path
import re
import subprocess
import time


def execute(command, log, timeout):
    started = time.perf_counter()
    result = subprocess.run(command, capture_output=True, text=True,
                            timeout=timeout)
    log.write_text(result.stdout + result.stderr, encoding='utf-8')
    if result.returncode:
        raise RuntimeError('Command failed; inspect ' + str(log))
    return time.perf_counter() - started, result.stdout


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-tree', required=True, type=Path)
    parser.add_argument('--output', required=True, type=Path)
    parser.add_argument('--test', required=True, action='append')
    parser.add_argument('--target', action='append', default=[],
                        help='Additional explicitly required build target')
    parser.add_argument('--jobs', type=int, default=1,
                        help='Use more than one only for independent tests')
    parser.add_argument('--timeout', type=int, default=120)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    build_root = (root / 'build').resolve()
    tree = args.build_tree.resolve()
    output = args.output.resolve()
    if not (tree.is_relative_to(build_root) and
            output.is_relative_to(build_root) and output != build_root):
        raise ValueError('Build tree and log directory must be below build/')
    if not 1 <= args.jobs <= 8 or not 1 <= args.timeout <= 120:
        raise ValueError('Jobs must be 1..8; per-command budget must be 1..120s')
    if len(set(args.test)) != len(args.test):
        raise ValueError('Duplicate test names are not separate coverage')
    output.mkdir(parents=True, exist_ok=True)
    pattern = '^(' + '|'.join(re.escape(name) for name in args.test) + ')$'
    _, listing = execute(['ctest', '--test-dir', str(tree),
                          '--show-only=json-v1', '-R', pattern],
                         output / 'listing.log', args.timeout)
    tests = json.loads(listing)['tests']
    if {t['name'] for t in tests} != set(args.test) or len(tests) != len(args.test):
        raise ValueError('Exact test selection failed; no build or run accepted')
    targets = set(args.target)
    for test in tests:
        if not test.get('command'):
            raise ValueError('Test has no configured command: ' + test['name'])
        executable = Path(test['command'][0]).resolve()
        # Script-only checks need no native target. Configured in-tree
        # executables retain their actual CMake target names.
        if executable.is_relative_to(tree):
            targets.add(executable.stem)
    timings = {}
    if targets:
        timings['buildSeconds'], _ = execute(
            ['cmake', '--build', str(tree), '--target'] + sorted(targets) +
            ['--parallel', str(args.jobs)], output / 'build.log', args.timeout)
    timings['testSeconds'], test_output = execute(
        ['ctest', '--test-dir', str(tree), '-R', pattern, '--output-on-failure',
         '-j', str(args.jobs), '--timeout', str(args.timeout)],
        output / 'ctest.log', args.timeout)
    # Fail a zero-test or incomplete run even when CTest itself returns zero.
    expected = '0 tests failed out of %d' % len(tests)
    if expected not in test_output:
        raise ValueError('CTest did not report the complete selected scope')
    report = dict(scopeOnly=True, tests=[t['name'] for t in tests],
                  targets=sorted(targets), jobs=args.jobs, timings=timings,
                  productRefresh=False, nodeOrEdgeCredit=0)
    (output / 'summary.json').write_text(json.dumps(report, indent=2) + '\n',
                                       encoding='utf-8')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
