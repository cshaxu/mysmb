"""Verify the admitted whirlpool chain through controlled original NMI routes."""
import argparse
import csv
import json
from pathlib import Path

from verify_engine_tail_routes import frame


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    directory = parser.parse_args().directory.resolve()
    assert directory.is_relative_to((Path(__file__).resolve().parents[1] / 'build').resolve())
    excluded = set(range(8)) | set(range(256, 512)) | {0x778, 0x779}
    visits = set()
    branches = {pc: [0, 0] for pc in (0xb7bb, 0xb7c3, 0xb7d3, 0xb7e4,
                                      0xb7ef, 0xb7f2, 0xb80d, 0xb818, 0xb82c)}
    for case in range(12):
        original = frame(directory / ('environment-rom-%d.msfr' % case), b'MSFR')
        with (directory / ('environment-pc-%d.csv' % case)).open() as stream:
            for row in csv.DictReader(stream):
                pc = int(row['pc'], 16)
                if int(row['hits']):
                    visits.add(pc)
                if pc in branches:
                    branches[pc][0] += int(row['fallthrough2'])
                    branches[pc][1] += int(row['other'])
        for bits in (32, 64):
            native = frame(directory / ('environment-native%d-%d.msfn' % (bits, case)), b'MSFN')
            assert all(original[4+i] == native[4+i] for i in range(2048)
                       if i not in excluded), (case, bits, 'persistent RAM')
            assert original[2052:] == native[2052:], (case, bits, 'output')
        assert (directory / ('environment-native32-%d.msfn' % case)).read_bytes() == (
            directory / ('environment-native64-%d.msfn' % case)).read_bytes()
    nodes = dict(ProcessWhirlpools=0xb7b8, WhLoop=0xb7c7, NextWh=0xb7f1,
                 ExitWh=0xb7f4, WhirlpoolActivate=0xb7f5, LeftWh=0xb828,
                 SetPWh=0xb839, WhPull=0xb83b)
    assert all(pc in visits for pc in nodes.values())
    assert all(all(counts) for counts in branches.values()), branches
    summary = dict(nodes=list(nodes), originalRoutes=12, nativeRuns=24,
                   persistentBytesPerSample=1782, outputExceptions=[],
                   branchCoverage={hex(k): v for k, v in branches.items()},
                   limits='Controlled PlayerChangeSize idle-return route; no claim of '
                          'ordinary water-level playthrough or whole GameEngine conformance. '
                          'Cannon dependency and combined delivery remain pending.')
    (directory / 'environment-verified.json').write_text(json.dumps(summary, indent=2)+'\n')
    print('Whirlpool: eight labels reached, nine branches both ways; 12 ROM routes match both widths')


if __name__ == '__main__':
    main()
