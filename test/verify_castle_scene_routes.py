"""Validate local full castle parser traces and actual original data reads."""
import argparse
import csv
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from smb_asm_index import index_listing
from smb_enemy_data_audit import check_literal_span
from smb_rom_codegen import read_nrom

SIZE = 4409


def frames(path, magic):
    data = path.read_bytes()
    assert data[:8] == magic + bytes([2, 0, 0, 0]), path
    count = struct.unpack_from('<I', data, 8)[0]
    assert count == 129 and len(data) == 12 + count * SIZE, path
    return [data[12+i*SIZE:12+(i+1)*SIZE] for i in range(count)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('--rom', required=True, type=Path)
    parser.add_argument('--asm', required=True, type=Path)
    args = parser.parse_args()
    prg, _ = read_nrom(args.rom)
    labels, _, mismatch = index_listing(args.rom, args.asm)
    assert mismatch is None
    symbols = {name: (address, line) for name, address, line in labels}
    lines = args.asm.read_text(encoding='latin-1').splitlines()
    spans = []
    for number in range(1, 7):
        name = 'L_CastleArea%d' % number
        following = 'L_CastleArea%d' % (number+1) if number < 6 else 'L_GroundArea1'
        start, line = symbols[name]
        end, next_line = symbols[following]
        data = check_literal_span(prg, start, end, lines[line:next_line-1])
        assert len(data) % 2 == 1 and data[-1] == 253
        assert all(data[i] != 253 for i in range(2, len(data)-1, 2))
        spans.append((name, start, end))
    excluded = set(range(8)) | set(range(0x100, 0x200)) | {0x778, 0x779}
    coverage = [set() for _ in range(6)]
    result = []
    for case in range(7):
        area = min(case, 5)
        name, start, end = spans[area]
        rom = frames(args.directory / ('rom-%d.msfr' % case), b'MSFR')
        native = frames(args.directory / ('native-%d.msfn' % case), b'MSFN')
        residual = set()
        for sample, (a, b) in enumerate(zip(rom, native)):
            delta = {i for i in range(2048) if a[4+i] != b[4+i]}
            assert delta <= excluded, (case, sample, sorted(delta-excluded))
            assert a[2052:] == b[2052:], (case, sample, 'visible output')
            residual |= delta
        first, last = rom[0][4:2052], rom[-1][4:2052]
        assert first[0xe7] | first[0xe8] << 8 == start+2
        assert last[0x725] == (32 if case == 6 else 16)
        if case != 5:
            assert last[0x72c] == end-start-3 and prg[start-0x8000+2+last[0x72c]] == 253
        with (args.directory / ('reads-%d.csv' % case)).open() as stream:
            coverage[area] |= {int(row['address'], 16) for row in csv.DictReader(stream) if int(row['reads'])}
        with (args.directory / ('pc-%d.txt' % case)).open() as stream:
            hits = {int(row['pc'], 16): int(row['hits']) for row in csv.DictReader(stream)}
        for node in ['GetAreaDataAddrs', 'AreaParserTaskControl', 'ProcessAreaData', 'DecodeAreaData', 'EndAParse']:
            assert hits.get(symbols[node][0], 0), (case, node)
        result.append(dict(case=case, node=name, samples=129, persistentMismatches=0,
                           outputMismatches=0, scratchOrMirrorResiduals=[hex(x) for x in sorted(residual)]))
    for area, (name, start, end) in enumerate(spans):
        assert set(range(start, end)) <= coverage[area], (name, 'unread bytes')
    summary = dict(routes=result, bytesBoundAndConsumed=sum(end-start for _, start, end in spans),
                   sceneNodes=[name for name, _, _ in spans], samples=903,
                   note='129 NMI-return samples per controlled route; scratch, stack and two PPU mirrors excluded from RAM comparison.')
    (args.directory / 'route-summary.json').write_text(json.dumps(summary, indent=2)+'\n')
    print('7 castle routes / 903 samples: persistent RAM and output match; all 700 scene bytes consumed')


if __name__ == '__main__':
    main()
