"""Check bounded owner-local T30/S3 recorder output; never copy trace bytes."""
import argparse
import csv
import json
import struct
from pathlib import Path

RECORD_SIZE = 4 + 2048 + 2048 + 32 + 256 + 14 + 7
CASES = {
    'axe': (0x06a7, 0xc5, 0xff, [0x9508, 0x9a09, 0x9a0e, 0x9a20]),
    'chain': (0x06a8, 0x0c, 0xff, [0x9508, 0x9a0e, 0x9a20]),
    'bridge': (0x06a9, 0x89, 11, [0x9508, 0x9a01, 0x9a0e, 0x9a20]),
    'empty': (0x06a5, 0xc4, 0xff, [0x9508, 0x9a19, 0x9a20]),
    'bridge-mid': (0x06a9, 0x89, 4, [0x9508, 0x9a01, 0x9a0e, 0x9a20]),
    'bridge-end': (0x06a9, 0x89, 0xff, [0x9508, 0x9a01, 0x9a0e, 0x9a20]),
}


def read_frames(path, magic):
    data = path.read_bytes()
    assert data[:8] == magic + bytes([2, 0, 0, 0]), str(path)
    count = struct.unpack_from('<I', data, 8)[0]
    assert count == 2 and len(data) == 12 + count * RECORD_SIZE, str(path)
    return [data[16+i*RECORD_SIZE:16+i*RECORD_SIZE+2048] for i in range(count)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    args = parser.parse_args()
    summary = {}
    # This is a chain-owned persistent-output comparison, not a full RAM
    # equivalence certificate. Report every remaining RAM address separately.
    owned = list(range(0x06a1, 0x06ae)) + list(range(0x072c, 0x0736)) + [0x0773]
    for name, (row, tile, length, entries) in CASES.items():
        rom = read_frames(args.directory / ('rom-' + name + '.msfr'), b'MSFR')
        native = read_frames(args.directory / ('native-' + name + '.msfn'), b'MSFN')
        with (args.directory / ('pc-' + name + '.txt')).open() as stream:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(stream)}
        assert all(hits.get(pc, 0) > 0 for pc in entries), (name, 'missing ROM entry')
        assert rom[0][row] == tile and rom[0][0x0732] == length, (name, 'vacuous route')
        assert rom[0][0x0735] == 0, (name, 'column height')
        if name == 'axe':
            assert rom[0][0x0773] == 8, (name, 'axe palette control')
        residual = set()
        for a, b in zip(rom, native):
            assert all(a[i] == b[i] for i in owned), (name, 'chain-output mismatch')
            residual.update(i for i in range(2048) if a[i] != b[i])
        summary[name] = {
            'frames': 2, 'chainOutputMismatchCount': 0,
            'romEntryHits': {format(pc, '04x'): hits[pc] for pc in entries},
            'otherRamDifferenceAddresses': [format(i, '04x') for i in sorted(residual)],
        }
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()
