"""Check T31 entry boundaries without certifying pending engine interiors.

Input is ignored, owner-local original/native NMI evidence. All exceptions
are named below and reported, never counted as whole-frame matches.
"""
import argparse
import csv
import json
import struct
from pathlib import Path

SIZE = 4409
SCRATCH = set(range(8)) | set(range(256, 512)) | {0x778, 0x779}


def frames(path, magic, count):
    data = path.read_bytes()
    assert data[:8] == magic + bytes([2, 0, 0, 0]), path
    assert struct.unpack_from('<I', data, 8)[0] == count, path
    assert len(data) == 12 + count * SIZE, path
    return [data[12+i*SIZE:12+(i+1)*SIZE] for i in range(count)]


def coverage(path):
    with path.open() as stream:
        return {int(row['pc'], 16): int(row['hits'])
                for row in csv.DictReader(stream)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('--rom', type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    directory = args.directory.resolve()
    assert directory.is_relative_to((root/'build').resolve())
    rom = args.rom.read_bytes()
    assert rom[:4] == b'NES\x1a' and rom[4] == 2 and not rom[6] & 4
    # Bind the four source vector targets, not a copied resource fixture.
    vector = struct.unpack_from('<4H', rom, 16 + 0xaee2 - 0x8000)
    assert vector == (0x8fe4, 0x8567, 0x9071, 0xaeea), vector
    entry_rows = []
    for case in range(4):
        original = frames(directory/('entry-rom-%d.msfr' % case), b'MSFR', 1)[0]
        pc = coverage(directory/('entry-pc-%d.csv' % case))
        assert all(pc.get(address, 0) for address in
                   [0xaedc, 0xaeea, 0xaeed, 0xaef0, 0xaef3, 0xaef6, 0xaef9, 0xaefb, 0xb04a])
        assert bool(pc.get(0xaefd, 0)) == (case < 2)
        assert bool(pc.get(0xaefe, 0)) == (case >= 2)
        for bits in [32, 64]:
            native = frames(directory/('entry-native%d-%d.msfn' % (bits, case)), b'MSFN', 1)[0]
            delta = {j for j in range(2048) if original[j+4] != native[j+4]} - SCRATCH
            # The former engine-entry residual at $0300-$0307 was removed by
            # the current shared VRAM/palette path.  Keep this route strict:
            # a later change must not silently restore the old eight-byte gap.
            assert delta == set(), (case, bits, delta)
            assert original[2052:] == native[2052:], (case, bits, 'output')
            for address in [0x6fc, 0x6fd, 0x753, 0x770, 0x772]:
                assert original[address+4] == native[address+4]
            assert native[0x772+4] == (0 if case < 2 else 3)
            if case >= 2:
                assert native[0x6fc+4] == (1 if case == 2 else 0)
            entry_rows.append(dict(case=case, bits=bits, persistentResidual=sorted(delta)))
        assert (directory/('entry-native32-%d.msfn' % case)).read_bytes() == (directory/('entry-native64-%d.msfn' % case)).read_bytes()
    # The current shared NMI path also removes the old cold-screen PPU-control
    # residuals on both ordinary routes.  Retain an exact-output assertion.
    for route, expected in [('start', []), ('idle', [])]:
        original = frames(directory/(route+'-rom.msfr'), b'MSFR', 600)
        pc = coverage(directory/(route+'-pc.csv'))
        if route == 'start':
            assert all(pc.get(address, 0) for address in vector)
            assert pc.get(0xaedc, 0)
        for bits in [32, 64]:
            native = frames(directory/(route+'-native%d.msfn' % bits), b'MSFN', 600)
            residual = []
            for index, (a, b) in enumerate(zip(original, native)):
                assert all(a[4+j] == b[4+j] for j in range(0x200, 0x800)
                           if j not in {0x778, 0x779}), (route, bits, index, 'work RAM')
                assert all(a[4+j] == b[4+j] for j in [0x6fc, 0x6fd, 0x753, 0x770, 0x772])
                residual.extend((index, j) for j in range(2052, SIZE) if a[j] != b[j])
            assert residual == expected, (route, bits, residual)
        assert (directory/(route+'-native32.msfn')).read_bytes() == (directory/(route+'-native64.msfn')).read_bytes()
    summary = dict(vectorTargets=[hex(x) for x in vector], entryCases=entry_rows,
                   ordinaryRoutes=2, samplesPerOrdinaryRoute=600,
                   limits='Entry-only credit. All four dispatch fixtures and both ordinary routes are exact outside excluded scratch state; this remains a bounded entry/dispatch proof.')
    (directory/'entry-verified.json').write_text(json.dumps(summary, indent=2)+'\n')
    print('Game entry: four vectors, both post-child branches, both controllers and two 600-frame routes verified within reported boundaries')


if __name__ == '__main__':
    main()
