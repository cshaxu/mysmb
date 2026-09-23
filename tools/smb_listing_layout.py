#!/usr/bin/env python3
"""Construct a local address layout from a local 6502 source listing.

This utility does not emit source text or ROM bytes.  It supplies local
address claims that must be reconciled by smb_static_analysis.py before they
can inform translation work.
"""

import re
from pathlib import Path

from smb_static_analysis import MNEMONICS, MODE_BY_OPCODE, SIZE_BY_MODE


BRANCHES = set(("bcc", "bcs", "beq", "bmi", "bne", "bpl", "bvc", "bvs"))
OPCODE_BY_NAME_MODE = {}
for name, opcodes in MNEMONICS.items():
    for opcode in opcodes:
        OPCODE_BY_NAME_MODE[(name, MODE_BY_OPCODE[opcode])] = opcode


def strip_comment(line):
    return line.split(";", 1)[0].rstrip()


def parse_value(text, constants):
    text = text.strip()
    if not text:
        return None
    match = re.match(r"^(.+?)([+-])\s*(\$[0-9a-fA-F]+|%[01]+|\d+)$", text)
    if match:
        base = parse_value(match.group(1), constants)
        delta = parse_value(match.group(3), constants)
        if base is None or delta is None:
            return None
        return base + delta if match.group(2) == "+" else base - delta
    if text.startswith("$"):
        try:
            return int(text[1:], 16)
        except ValueError:
            return None
    if text.startswith("%") and all(bit in "01" for bit in text[1:]):
        return int(text[1:], 2)
    if text.isdigit():
        return int(text, 10)
    return constants.get(text)


def data_count(argument, unit):
    count = 0
    for token in argument.split(","):
        token = token.strip()
        if not token:
            continue
        if len(token) >= 2 and token[0] == '"' and token[-1] == '"':
            count += len(token[1:-1]) * unit
        else:
            count += unit
    return count


def operand_mode(mnemonic, operand, constants):
    operand = operand.strip()
    if mnemonic in BRANCHES:
        return "rel"
    if not operand:
        return "acc" if mnemonic in ("asl", "lsr", "rol", "ror") else "imp"
    if operand.lower() == "a":
        return "acc"
    if operand.startswith("#"):
        return "imm"
    if operand.startswith("(") and operand.endswith("),y"):
        return "ind_y"
    if operand.startswith("(") and operand.endswith(",x)"):
        return "ind_x"
    if operand.startswith("(") and operand.endswith(")"):
        return "ind"
    suffix = None
    if operand.lower().endswith(",x"):
        suffix = "x"
        operand = operand[:-2].strip()
    elif operand.lower().endswith(",y"):
        suffix = "y"
        operand = operand[:-2].strip()
    value = parse_value(operand, constants)
    zero_page = value is not None and 0 <= value <= 0xff
    if suffix == "x":
        return "zp_x" if zero_page and (mnemonic, "zp_x") in OPCODE_BY_NAME_MODE else "abs_x"
    if suffix == "y":
        return "zp_y" if zero_page and (mnemonic, "zp_y") in OPCODE_BY_NAME_MODE else "abs_y"
    return "zp" if zero_page and (mnemonic, "zp") in OPCODE_BY_NAME_MODE else "abs"


def constants_from(lines):
    constants = {}
    definition = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.+)$")
    for _ in range(4):
        changed = False
        for raw in lines:
            source = strip_comment(raw).strip()
            match = definition.match(source)
            if not match:
                continue
            value = parse_value(match.group(2), constants)
            if value is not None and constants.get(match.group(1)) != value:
                constants[match.group(1)] = value
                changed = True
        if not changed:
            break
    return constants


def layout(path):
    lines = path.read_text(encoding="latin-1").splitlines()
    constants = constants_from(lines)
    pc = None
    labels = []
    instructions = []
    data = []
    unknown = []
    label_re = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*):")
    definition_re = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*\s*=")
    directive_re = re.compile(r"^\s*\.(\w+)\s*(.*)$")
    instruction_re = re.compile(r"^\s+([A-Za-z]{3})(?:\s+(.*?))?$" )
    for line_number, raw in enumerate(lines, 1):
        source = strip_comment(raw)
        if not source.strip() or definition_re.match(source.strip()):
            continue
        if pc is not None and source.strip().startswith("+"):
            count = len(re.findall(r"\$[0-9a-fA-F]{2}", source))
            if count == 0:
                unknown.append(line_number)
            else:
                data.append((pc, count, line_number))
                pc += count
            continue
        directive = directive_re.match(source)
        if directive:
            name, argument = directive.group(1).lower(), directive.group(2)
            if name == "org":
                pc = parse_value(argument, constants)
            elif pc is not None and name in ("db", "byte"):
                count = data_count(argument, 1)
                data.append((pc, count, line_number))
                pc += count
            elif pc is not None and name in ("dw", "word"):
                count = data_count(argument, 2)
                data.append((pc, count, line_number))
                pc += count
            elif pc is not None and name == "hex":
                count = len(re.sub(r"[^0-9a-fA-F]", "", argument)) // 2
                data.append((pc, count, line_number))
                pc += count
            elif name not in ("index", "mem"):
                unknown.append(line_number)
            continue
        label = label_re.match(source)
        if label:
            if pc is not None:
                labels.append((pc, label.group(1), line_number))
                constants[label.group(1)] = pc
            source = source[label.end():]
            if not source.strip():
                continue
        instruction = instruction_re.match(source)
        if instruction and pc is not None:
            mnemonic = instruction.group(1).lower()
            operand = instruction.group(2) or ""
            if mnemonic not in MNEMONICS:
                unknown.append(line_number)
                continue
            mode = operand_mode(mnemonic, operand, constants)
            opcode = OPCODE_BY_NAME_MODE.get((mnemonic, mode))
            if opcode is None:
                unknown.append(line_number)
                continue
            instructions.append((pc, opcode, SIZE_BY_MODE[mode], mnemonic, line_number))
            pc += SIZE_BY_MODE[mode]
    return {"labels": labels, "instructions": instructions, "data": data,
            "unknown": unknown, "constants": constants}
