"""Check pointer/header chain through original mode dispatch, using local ROM tables."""
import argparse
import csv
import json
import struct
from pathlib import Path
from verify_castle_column_routes import RECORD_SIZE, read_frames


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('rom', type=Path)
    args = parser.parse_args()
    raw = args.rom.read_bytes()
    assert raw[:4] == b'NES\x1a' and raw[4] == 2
    offset = 16 + (512 if raw[6] & 4 else 0)
    prg = raw[offset:offset+32768]
    worlds = [5, 5, 4, 5, 4, 4, 5, 4]
    slots = [3, 22, 3, 6]
    excluded = set(range(8)) | set(range(0x100, 0x200)) | {0x778, 0x779}
    results = []
    accessed = set()
    for case in range(70):
        rom = read_frames(args.directory / ('rom-%d.msfr' % case), b'MSFR')
        native = read_frames(args.directory / ('native-%d.msfn' % case), b'MSFN')
        with (args.directory / ('pc-%d.txt' % case)).open() as stream:
            hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(stream)}
        if case < 36:
            world, area = 0, case
            while area >= worlds[world]:
                area -= worlds[world]
                world += 1
            index = (prg[0x1cb4+world] + area) & 255
            pointer = prg[0x1cbc+index]
            for pc in [0x9c03, 0x9c09, 0x9c13, 0x9c16, 0x9c1a, 0x9c1e]:
                assert hits.get(pc, 0), (case, 'missing world pointer call', hex(pc))
            accessed.update([0x1cb4+world, 0x1cbc+index])
            assert rom[0][0x74f] == 0xee and rom[0][0xe7:0xeb] == bytes([0x91, 0x92, 0x93, 0x94]), (case, 'LoadAreaPointer extra writes')
            sample, halfway = 1, 0
        else:
            kind, low = 0, case-36
            while low >= slots[kind]:
                low -= slots[kind]
                kind += 1
            pointer = kind*32 + low + (case % 2)*128
            sample, halfway = 0, case % 4
        kind, low = (pointer >> 5) & 3, pointer & 31
        e = (prg[0x1ce0+kind] + low) & 255
        a = (prg[0x1d28+kind] + low) & 255
        enemy = prg[0x1ce4+e] | prg[0x1d06+e] << 8
        address = prg[0x1d2c+a] | prg[0x1d4e+a] << 8
        accessed.update([0x1ce0+kind, 0x1d28+kind, 0x1ce4+e, 0x1d06+e, 0x1d2c+a, 0x1d4e+a])
        first, second = prg[address-0x8000:address-0x8000+2]
        for pc in [0x9c22, 0x9c31, 0x9c39, 0x9c3e, 0x9c46, 0x9c4e, 0x9c53, 0x9c68, 0x9ca3, 0x9cb3]:
            assert hits.get(pc, 0), (case, 'missing pointer/header path', hex(pc))
        ram = rom[sample]
        expected = {0x750:pointer, 0x74e:kind, 0x74f:low, 0xe9:enemy & 255, 0xea:enemy >> 8,
                    0xe7:(address+2) & 255, 0xe8:(address+2) >> 8,
                    0x741:first & 7 if (first & 7) < 4 else 0,
                    0x744:first & 7 if (first & 7) >= 4 else 0,
                    0x710:2 if halfway else (first >> 3) & 7, 0x715:first >> 6,
                    0x727:second & 15, 0x742:(second >> 4) & 3,
                    0x743:3 if second >> 6 == 3 else 0,
                    0x733:0 if second >> 6 == 3 else second >> 6}
        for i, value in expected.items():
            assert ram[i] == value, (case, hex(i), ram[i], value)
        for frame, (x, y) in enumerate(zip(rom, native)):
            diff = [i for i in range(2048) if x[i] != y[i]]
            assert not [i for i in diff if i not in excluded], (case, frame, [(hex(i),x[i],y[i]) for i in diff if i not in excluded])
            results.append(dict(case=case, sample=frame, pointer=pointer, persistentMismatches=0,
                                residualAddresses=[hex(i) for i in diff]))
    # Every table byte, including the WorldNAreas aliases, has a live consumer.
    assert set(range(0x1cb4, 0x1d70)) <= accessed, sorted(set(range(0x1cb4, 0x1d70))-accessed)
    # TerminateGame's other exit: no player swap, retain ContinueWorld and
    # return to title. One sample stops before the next title initialization.
    last = []
    for name, magic in [('rom-70.msfr', b'MSFR'), ('native-70.msfn', b'MSFN')]:
        data = (args.directory / name).read_bytes()
        assert data[:8] == magic + bytes([2, 0, 0, 0])
        assert struct.unpack_from('<I', data, 8)[0] == 1
        assert len(data) == 12 + RECORD_SIZE
        last.append(data[16:16+2048])
    x, y = last
    assert (x[0xfc], x[0x770], x[0x772], x[0x7a0], x[0x7fd]) == (128, 0, 0, 0, 5)
    diff = [i for i in range(2048) if x[i] != y[i]]
    assert not [i for i in diff if i not in excluded], [(hex(i), x[i], y[i]) for i in diff if i not in excluded]
    with (args.directory / 'pc-70.txt').open() as stream:
        hits = {int(r['pc'], 16): int(r['hits']) for r in csv.DictReader(stream)}
    assert hits.get(0x9248, 0) and hits.get(0x9251, 0) and hits.get(0x9263, 0)
    results.append(dict(case=70, sample=0, persistentMismatches=0,
                        residualAddresses=[hex(i) for i in diff]))
    (args.directory / 'route-summary.json').write_text(json.dumps(results, indent=2)+'\n')
    print('70 pointer/header routes and no-swap TerminateGame match; all 188 table bytes consumed')


if __name__ == '__main__':
    main()
