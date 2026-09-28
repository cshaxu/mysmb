"""Verify original-NMI engine-tail evidence, with no output exceptions."""
import argparse
import csv
import json
import struct
from pathlib import Path


def frame(path, magic):
    data = path.read_bytes()
    assert data[:8] == magic + bytes([2, 0, 0, 0])
    assert struct.unpack_from('<I', data, 8)[0] == 1
    assert len(data) == 4421
    return data[12:]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    args = parser.parse_args()
    directory = args.directory.resolve()
    assert directory.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
    excluded = set(range(8)) | set(range(256, 512)) | {0x778, 0x779}
    visits = set()
    branches = {}
    for case in range(15):
        original = frame(directory/('tail-rom-%d.msfr' % case), b'MSFR')
        with (directory/('tail-pc-%d.csv' % case)).open() as stream:
            for row in csv.DictReader(stream):
                address = int(row['pc'], 16)
                if int(row['hits']):
                    visits.add(address)
                if 0xaf3b <= address <= 0xaf92:
                    old = branches.setdefault(hex(address), [0, 0])
                    old[0] += int(row['fallthrough2'])
                    old[1] += int(row['other'])
        for bits in [32, 64]:
            native = frame(directory/('tail-native%d-%d.msfn' % (bits, case)), b'MSFN')
            assert all(original[4+j] == native[4+j] for j in range(2048) if j not in excluded), (case, bits, 'persistent RAM')
            assert original[2052:] == native[2052:], (case, bits, 'output')
        assert (directory/('tail-native32-%d.msfn' % case)).read_bytes() == (directory/('tail-native64-%d.msfn' % case)).read_bytes()
    nodes = dict(NoChgMus=0xaf52, CycleTwo=0xaf5d, ClrPlrPal=0xaf64,
                 SaveAB=0xaf67, UpdScrollVar=0xaf6f, RunParser=0xaf8f, ExitEng=0xaf92)
    assert all(address in visits for address in nodes.values())
    # Original branch coverage supplements the source audit and exhaustive
    # call-boundary test. The buffer-controller-six early exit is tested at
    # the independent caller seam; NMI clears its input before this fixture.
    for address in [0xaf3f, 0xaf44, 0xaf48, 0xaf4d, 0xaf59, 0xaf79, 0xaf80]:
        assert all(branches[hex(address)]), (hex(address), branches[hex(address)])
    summary = dict(nodes=list(nodes), routes=15, widthRuns=30,
                   persistentBytesPerSample=1782, outputExceptions=[],
                   branchCoverage=branches,
                   limits='GameEngine/ProcELoop incomplete: actor/cannon/whirlpool and block call boundaries are not certified. Controller-six parser early return is covered by source audit and isolated unit tests, not these NMI fixtures.')
    (directory/'tail-verified.json').write_text(json.dumps(summary, indent=2)+'\n')
    print('Engine tail: seven nodes, 15 original NMI routes, 30 width runs; persistent RAM and full output match')


if __name__ == '__main__':
    main()
