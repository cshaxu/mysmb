#!/usr/bin/env python3
"""Index an owner-local SMBDIS listing against an owner-local NROM image."""

import argparse
import hashlib
import re
from pathlib import Path

from smb_rom_codegen import read_nrom

OPCODE_SIZES = [1] * 256
TWO_BYTE_OPCODES = (
    0x01, 0x05, 0x06, 0x09, 0x10, 0x11, 0x15, 0x16, 0x19, 0x1D,
    0x21, 0x24, 0x25, 0x26, 0x29, 0x30, 0x31, 0x35, 0x36, 0x39, 0x3D, 0x41, 0x45,
    0x46, 0x49, 0x50, 0x51, 0x55, 0x56, 0x59, 0x5D, 0x61, 0x65, 0x66, 0x69,
    0x70, 0x71, 0x75, 0x76, 0x79, 0x7D, 0x81, 0x84, 0x85, 0x86, 0x89, 0x90,
    0x91, 0x94, 0x95, 0x96, 0x99, 0x9D, 0xA0, 0xA1, 0xA2, 0xA4, 0xA5, 0xA6,
    0xA9, 0xB0, 0xB1, 0xB4, 0xB5, 0xB6, 0xB9, 0xBD, 0xC0, 0xC1, 0xC4, 0xC5,
    0xC6, 0xC9, 0xD0, 0xD1, 0xD5, 0xD6, 0xD9, 0xDD, 0xE0, 0xE1, 0xE4, 0xE5,
    0xE6, 0xE9, 0xF0, 0xF1, 0xF5, 0xF6, 0xF9, 0xFD,
)
THREE_BYTE_OPCODES = (
    0x0D, 0x0E, 0x19, 0x1D, 0x20, 0x2C, 0x2D, 0x2E, 0x39, 0x3D, 0x3E, 0x4C,
    0x4D, 0x4E, 0x59, 0x5D, 0x5E, 0x6C, 0x6D, 0x6E, 0x79, 0x7D, 0x7E, 0x8C, 0x8D, 0x8E, 0x99,
    0x9D, 0xAC, 0xAD, 0xAE, 0xB9, 0xBC, 0xBD, 0xBE, 0xCC, 0xCD, 0xCE, 0xD9,
    0xDD, 0xDE, 0xEC, 0xED, 0xEE, 0xF9, 0xFD, 0xFE,
)
for opcode in TWO_BYTE_OPCODES:
    OPCODE_SIZES[opcode] = 2
for opcode in THREE_BYTE_OPCODES:
    OPCODE_SIZES[opcode] = 3

MNEMONIC_OPCODES = {
    "adc": (0x61, 0x65, 0x69, 0x6D, 0x71, 0x75, 0x79, 0x7D),
    "and": (0x21, 0x25, 0x29, 0x2D, 0x31, 0x35, 0x39, 0x3D),
    "asl": (0x06, 0x0A, 0x0E, 0x16, 0x1E), "bcc": (0x90,), "bcs": (0xB0,),
    "beq": (0xF0,), "bit": (0x24, 0x2C), "bmi": (0x30,), "bne": (0xD0,),
    "bpl": (0x10,), "brk": (0x00,), "bvc": (0x50,), "bvs": (0x70,),
    "clc": (0x18,), "cld": (0xD8,), "cli": (0x58,), "clv": (0xB8,),
    "cmp": (0xC1, 0xC5, 0xC9, 0xCD, 0xD1, 0xD5, 0xD9, 0xDD),
    "cpx": (0xE0, 0xE4, 0xEC), "cpy": (0xC0, 0xC4, 0xCC),
    "dec": (0xC6, 0xCE, 0xD6, 0xDE), "dex": (0xCA,), "dey": (0x88,),
    "eor": (0x41, 0x45, 0x49, 0x4D, 0x51, 0x55, 0x59, 0x5D),
    "inc": (0xE6, 0xEE, 0xF6, 0xFE), "inx": (0xE8,), "iny": (0xC8,),
    "jmp": (0x4C, 0x6C), "jsr": (0x20,),
    "lda": (0xA1, 0xA5, 0xA9, 0xAD, 0xB1, 0xB5, 0xB9, 0xBD),
    "ldx": (0xA2, 0xA6, 0xAE, 0xB6, 0xBE), "ldy": (0xA0, 0xA4, 0xAC, 0xB4, 0xBC),
    "lsr": (0x46, 0x4A, 0x4E, 0x56, 0x5E), "nop": (0xEA,),
    "ora": (0x01, 0x05, 0x09, 0x0D, 0x11, 0x15, 0x19, 0x1D),
    "pha": (0x48,), "php": (0x08,), "pla": (0x68,), "plp": (0x28,),
    "rol": (0x26, 0x2A, 0x2E, 0x36, 0x3E), "ror": (0x66, 0x6A, 0x6E, 0x76, 0x7E),
    "rti": (0x40,), "rts": (0x60,),
    "sbc": (0xE1, 0xE5, 0xE9, 0xED, 0xF1, 0xF5, 0xF9, 0xFD),
    "sec": (0x38,), "sed": (0xF8,), "sei": (0x78,),
    "sta": (0x81, 0x85, 0x8D, 0x91, 0x95, 0x99, 0x9D), "stx": (0x86, 0x8E, 0x96),
    "sty": (0x84, 0x8C, 0x94), "tax": (0xAA,), "tay": (0xA8,), "tsx": (0xBA,),
    "txa": (0x8A,), "txs": (0x9A,), "tya": (0x98,),
}


def data_count(text, unit):
    count = 0
    for token in text.split(","):
        token = token.strip()
        if token.startswith('"') and token.endswith('"'):
            count += len(token[1:-1]) * unit
        elif token:
            count += unit
    return count


def parse_org(text):
    match = re.search(r"\$([0-9a-fA-F]+)", text)
    if not match:
        raise ValueError("unsupported .org directive: %s" % text)
    return int(match.group(1), 16)


def index_listing(rom_path, asm_path):
    prg, _ = read_nrom(rom_path)
    pc = None
    labels = []
    unknown = []
    mismatch = None
    label_pattern = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*):")
    directive_pattern = re.compile(r"^\s*\.(\w+)\s*(.*)$")
    instruction_pattern = re.compile(r"^\s+([A-Za-z]{3})(?:\s+.*)?$")
    for line_number, raw_line in enumerate(asm_path.read_text(encoding="latin-1").splitlines(), 1):
        source = raw_line.split(";", 1)[0].rstrip()
        if not source.strip():
            continue
        continuation = source.strip()
        if pc is not None and continuation.startswith("+"):
            count = len(re.findall(r"\$[0-9a-fA-F]{2}", continuation))
            if count == 0:
                unknown.append((line_number, source))
            else:
                pc += count
            continue
        label = label_pattern.match(source)
        if label:
            if pc is None:
                continue
            labels.append((label.group(1), pc, line_number))
            source = source[label.end():]
            if not source.strip():
                continue
        directive = directive_pattern.match(source)
        if directive:
            name = directive.group(1).lower()
            argument = directive.group(2)
            if name == "org":
                pc = parse_org(argument)
            elif pc is not None and name in ("db", "byte"):
                pc += data_count(argument, 1)
            elif pc is not None and name in ("dw", "word"):
                pc += data_count(argument, 2)
            elif pc is not None and name == "hex":
                pc += len(re.sub(r"[^0-9a-fA-F]", "", argument)) // 2
            elif name not in ("index", "mem"):
                unknown.append((line_number, source))
            continue
        instruction = instruction_pattern.match(source)
        if instruction:
            if pc is None or pc < 0x8000 or pc > 0xFFFF:
                raise ValueError("instruction outside NROM PRG at line %d" % line_number)
            opcode = prg[pc - 0x8000]
            mnemonic = instruction.group(1).lower()
            if mnemonic not in MNEMONIC_OPCODES or opcode not in MNEMONIC_OPCODES[mnemonic]:
                mismatch = (line_number, pc, mnemonic, opcode)
                break
            pc += OPCODE_SIZES[opcode]
    return labels, unknown, mismatch


def generate(rom_path, asm_path, output_path):
    labels, unknown, mismatch = index_listing(rom_path, asm_path)
    digest = hashlib.sha256(asm_path.read_bytes()).hexdigest()
    lines = ["format=mysmb-smbdis-index-v1", "listing-sha256=%s" % digest]
    for name, address, line_number in labels:
        lines.append("%04X %s line=%d" % (address, name, line_number))
    if unknown:
        lines.append("unknown-directives=%d" % len(unknown))
    if mismatch:
        lines.append("mismatch=line=%d,cpu=%04X,mnemonic=%s,opcode=%02X" % mismatch)
    output_path.write_text("\n".join(lines) + "\n", encoding="ascii")
    return labels, unknown, mismatch


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--asm", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    generate(args.rom, args.asm, args.output)


if __name__ == "__main__":
    main()
