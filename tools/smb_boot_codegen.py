#!/usr/bin/env python3
"""Statically translate the SMB1 reset-vector slice into owner-local C90."""

import argparse
from pathlib import Path

from smb_rom_codegen import read_nrom


def word(data, offset):
    return data[offset] | (data[offset + 1] << 8)


def byte_literal(value):
    return "0x%02XU" % value


def word_literal(value):
    return "0x%04XU" % value


def branch_target(address, offset):
    signed = offset if offset < 0x80 else offset - 0x100
    return (address + 2 + signed) & 0xFFFF


def emit_header(path):
    path.write_text(
        "#ifndef MYSMB_STATIC_BOOT_H\n"
        "#define MYSMB_STATIC_BOOT_H\n\n"
        "typedef unsigned char mysmb_static_u8;\n"
        "typedef unsigned short mysmb_static_u16;\n\n"
        "struct mysmb_static_boot {\n"
        "    mysmb_static_u8 a;\n"
        "    mysmb_static_u8 x;\n"
        "    mysmb_static_u8 y;\n"
        "    mysmb_static_u8 stack_pointer;\n"
        "    mysmb_static_u8 carry;\n"
        "    mysmb_static_u8 zero;\n"
        "    mysmb_static_u8 negative;\n"
        "    mysmb_static_u8 interrupt_mask;\n"
        "    mysmb_static_u8 decimal_mode;\n"
        "};\n\n"
        "mysmb_static_u8 mysmb_static_read(struct mysmb_static_boot *state, mysmb_static_u16 address);\n"
        "void mysmb_static_write(struct mysmb_static_boot *state, mysmb_static_u16 address, mysmb_static_u8 value);\n"
        "void mysmb_static_call_8220(struct mysmb_static_boot *state);\n"
        "void mysmb_static_call_8e19(struct mysmb_static_boot *state);\n"
        "void mysmb_static_call_90cc(struct mysmb_static_boot *state);\n"
        "void mysmb_static_call_8eed(struct mysmb_static_boot *state);\n"
        "void mysmb_static_reset(struct mysmb_static_boot *state);\n\n"
        "#endif\n",
        encoding="ascii",
    )


def emit_reset(prg, path):
    start = word(prg, 0x7FFC)
    if start != 0x8000:
        raise ValueError("this bootstrap expects reset vector $8000")
    pc = start
    output = [
        '#include "smb1_static_boot.h"',
        "",
        "void mysmb_static_reset(struct mysmb_static_boot *state)",
        "{",
        "    mysmb_static_u8 value;",
    ]
    while True:
        offset = pc - 0x8000
        opcode = prg[offset]
        output.append("label_%04X:" % pc)
        output.append("    /* $%04X: opcode $%02X */" % (pc, opcode))
        if opcode == 0x78:
            output.append("    state->interrupt_mask = 1U;")
            pc += 1
        elif opcode == 0xD8:
            output.append("    state->decimal_mode = 0U;")
            pc += 1
        elif opcode == 0xA9:
            output.append("    state->a = %s;" % byte_literal(prg[offset + 1]))
            output.append("    state->zero = state->a == 0U;")
            output.append("    state->negative = (state->a & 0x80U) != 0U;")
            pc += 2
        elif opcode == 0xA2:
            output.append("    state->x = %s;" % byte_literal(prg[offset + 1]))
            output.append("    state->zero = state->x == 0U;")
            output.append("    state->negative = (state->x & 0x80U) != 0U;")
            pc += 2
        elif opcode == 0xA0:
            output.append("    state->y = %s;" % byte_literal(prg[offset + 1]))
            output.append("    state->zero = state->y == 0U;")
            output.append("    state->negative = (state->y & 0x80U) != 0U;")
            pc += 2
        elif opcode == 0x9A:
            output.append("    state->stack_pointer = state->x;")
            pc += 1
        elif opcode == 0xAD:
            address = word(prg, offset + 1)
            output.append("    state->a = mysmb_static_read(state, %s);" % word_literal(address))
            output.append("    state->zero = state->a == 0U;")
            output.append("    state->negative = (state->a & 0x80U) != 0U;")
            pc += 3
        elif opcode == 0xBD:
            address = word(prg, offset + 1)
            output.append("    state->a = mysmb_static_read(state, (mysmb_static_u16)(%s + state->x));" % word_literal(address))
            output.append("    state->zero = state->a == 0U;")
            output.append("    state->negative = (state->a & 0x80U) != 0U;")
            pc += 3
        elif opcode == 0x8D:
            address = word(prg, offset + 1)
            output.append("    mysmb_static_write(state, %s, state->a);" % word_literal(address))
            pc += 3
        elif opcode == 0xC9:
            value = prg[offset + 1]
            output.append("    state->carry = state->a >= %s;" % byte_literal(value))
            output.append("    state->zero = state->a == %s;" % byte_literal(value))
            output.append("    state->negative = ((mysmb_static_u8)(state->a - %s) & 0x80U) != 0U;" % byte_literal(value))
            pc += 2
        elif opcode == 0xCA:
            output.append("    state->x = (mysmb_static_u8)(state->x - 1U);")
            output.append("    state->zero = state->x == 0U;")
            output.append("    state->negative = (state->x & 0x80U) != 0U;")
            pc += 1
        elif opcode == 0xEE:
            address = word(prg, offset + 1)
            output.append("    value = (mysmb_static_u8)(mysmb_static_read(state, %s) + 1U);" % word_literal(address))
            output.append("    mysmb_static_write(state, %s, value);" % word_literal(address))
            output.append("    state->zero = value == 0U;")
            output.append("    state->negative = (value & 0x80U) != 0U;")
            pc += 3
        elif opcode == 0x09:
            output.append("    state->a = (mysmb_static_u8)(state->a | %s);" % byte_literal(prg[offset + 1]))
            output.append("    state->zero = state->a == 0U;")
            output.append("    state->negative = (state->a & 0x80U) != 0U;")
            pc += 2
        elif opcode == 0x20:
            address = word(prg, offset + 1)
            output.append("    mysmb_static_call_%04x(state);" % address)
            pc += 3
        elif opcode in (0x10, 0xB0, 0xD0):
            target = branch_target(pc, prg[offset + 1])
            if opcode == 0x10:
                condition = "state->negative == 0U"
            elif opcode == 0xB0:
                condition = "state->carry != 0U"
            else:
                condition = "state->zero == 0U"
            output.append("    if (%s) {" % condition)
            output.append("        goto label_%04X;" % target)
            output.append("    }")
            pc += 2
        elif opcode == 0x4C:
            address = word(prg, offset + 1)
            if address == pc:
                output.append("    return;")
                break
            output.append("    goto label_%04X;" % address)
            break
        else:
            raise ValueError("unsupported reset opcode $%02X at $%04X" % (opcode, pc))
    output.append("}")
    output.append("")
    targets = set()
    for line in output:
        marker = "goto label_"
        if marker in line:
            targets.add(("label_" + line.split(marker, 1)[1].rstrip(";")).upper())
    filtered = []
    for line in output:
        if line.startswith("label_") and line.endswith(":") and line[:-1].upper() not in targets:
            continue
        filtered.append(line)
    path.write_text("\n".join(filtered), encoding="ascii")


def generate(rom_path, output_dir):
    prg, _ = read_nrom(rom_path)
    output_dir.mkdir(parents=True, exist_ok=True)
    emit_header(output_dir / "smb1_static_boot.h")
    emit_reset(prg, output_dir / "smb1_static_boot.c")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    generate(args.rom, args.output)


if __name__ == "__main__":
    main()
