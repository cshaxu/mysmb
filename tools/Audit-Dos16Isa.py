"""Inspect original link-map CODE ranges for post-8086 instruction candidates.

Linear disassembly can encounter inline tables; candidates require review.
This is an instruction inventory, not an all-control-path execution proof.
"""
import argparse
import json
from pathlib import Path
import re
import struct
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--directory', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    repository = Path(__file__).resolve().parents[1]
    args.output.resolve().relative_to(repository / 'build')
    binary = args.directory / 'mysmb-dos16.exe'
    data = binary.read_bytes()
    header = struct.unpack_from('<H', data, 8)[0] * 16
    segments = []
    for match in re.finditer(r'^\s*([0-9A-F]+)H\s+([0-9A-F]+)H\s+([0-9A-F]+)H\s+(\S+)\s+CODE\s*$',
                            (args.directory / 'mysmb-dos16.map').read_text(), re.M):
        if int(match[3], 16):
            segments.append((int(match[1], 16), int(match[3], 16), match[4]))
    assert segments, 'No CODE segments in map'
    candidates = []
    instructions = 0
    tables = []
    for start, length, name in segments:
        begin, end = header + start, header + start + length
        # CL /G0 switch: range-check AX, double it, indirect jump through
        # the immediately following CS word table. Prove extent and targets;
        # never discard an opcode merely because its value resembles data.
        spans = []
        patterns = (
            rb'\x3d(..)\x76\x03\xe9..\xd1\xe0\x8b\xd8\x2e\xff\xa7(..)',
            rb'\x3d(..)\x76\x03\xe9..\x03\xc0\x93\x2e\xff\xa7(..)')
        matches = [(kind, match) for kind, pattern in enumerate(patterns)
                   for match in re.finditer(pattern, data[begin:end], re.S)]
        for kind, match in matches:
            maximum = struct.unpack('<H', match[1])[0]
            offset = struct.unpack('<H', match[2])[0]
            base = begin - (start & 15)
            first = base + offset
            last = first + (maximum + 1) * 2
            if maximum > 511 or first < begin or last > end:
                continue
            if kind == 0 and first != begin + match.end():
                continue
            if kind == 1:
                # CRT places the table after case code, protected by a short
                # unconditional jump and one alignment NOP.
                if data[first - 3] != 0xeb or data[first - 1] != 0x90:
                    continue
                target = first - 1 + struct.unpack_from('<b', data, first - 2)[0]
                if not begin <= target < end or first <= target < last:
                    continue
            targets = struct.unpack_from('<' + 'H' * (maximum + 1), data, first)
            if not all(begin <= base + t < end and not first <= base + t < last for t in targets):
                continue
            spans.append((first, last))
            tables.append(dict(segment=name, first=first, end=last, entries=maximum + 1))
        cursor = begin
        chunks = []
        for first, last in sorted(spans):
            if first > cursor:
                chunks.append((cursor, first))
            cursor = max(cursor, last)
        if cursor < end:
            chunks.append((cursor, end))
        for first, last in chunks:
            result = subprocess.run(['objdump', '-D', '-b', 'binary', '-m', 'i386',
            '-M', 'addr16,data16', '--insn-width=16',
            '--start-address=' + str(first),
            '--stop-address=' + str(last), str(binary)],
            capture_output=True, text=True, check=True)
            for line in result.stdout.splitlines():
                inspect_line(line, name, candidates)
            instructions += sum(bool(re.match(r'\s*[0-9a-f]+:\s+', line)) for line in result.stdout.splitlines())
    report = dict(codeSegments=len(segments), codeBytes=sum(s[1] for s in segments),
                  decodedInstructions=instructions, candidateCount=len(candidates),
                  candidates=candidates, provenSwitchTables=tables,
                  scope='CODE scan excluding range/target-proven switch tables; not dynamic execution coverage')
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k not in ('candidates', 'provenSwitchTables')}))


def inspect_line(line, name, candidates):
    match = re.match(r'\s*([0-9a-f]+):\s+((?:[0-9a-f]{2}\s+)+)\s*(.*)', line)
    if not match or not match[3]:
        return
    code = bytes.fromhex(match[2])
    opcode = 0
    while opcode < len(code) and code[opcode] in (0x26, 0x2e, 0x36, 0x3e, 0xf0, 0xf2, 0xf3):
        opcode += 1
    if opcode == len(code):
        return
    op = code[opcode]
    if op in (0x0f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
              0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
              0xc0, 0xc1, 0xc8, 0xc9, 0xf1) or 0xd8 <= op <= 0xdf or '(bad)' in match[3]:
        candidates.append(dict(segment=name, fileOffset=int(match[1], 16),
                               instruction=match[3]))

if __name__ == '__main__':
    main()
