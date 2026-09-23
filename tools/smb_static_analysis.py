#!/usr/bin/env python3
"""Analyze an owner-local NROM PRG without emitting ROM bytes or assembly."""

import argparse
import hashlib
import re
from collections import Counter, defaultdict, deque
from pathlib import Path

from smb_rom_codegen import read_nrom


# Official 6502 opcodes used by the 2A03 CPU.  The table is project-owned
# decoder metadata, not a listing or derivative of any particular ROM.
MNEMONICS = {
    "adc": (0x61, 0x65, 0x69, 0x6D, 0x71, 0x75, 0x79, 0x7D),
    "and": (0x21, 0x25, 0x29, 0x2D, 0x31, 0x35, 0x39, 0x3D),
    "asl": (0x06, 0x0A, 0x0E, 0x16, 0x1E), "bcc": (0x90,),
    "bcs": (0xB0,), "beq": (0xF0,), "bit": (0x24, 0x2C),
    "bmi": (0x30,), "bne": (0xD0,), "bpl": (0x10,), "brk": (0x00,),
    "bvc": (0x50,), "bvs": (0x70,), "clc": (0x18,), "cld": (0xD8,),
    "cli": (0x58,), "clv": (0xB8,),
    "cmp": (0xC1, 0xC5, 0xC9, 0xCD, 0xD1, 0xD5, 0xD9, 0xDD),
    "cpx": (0xE0, 0xE4, 0xEC), "cpy": (0xC0, 0xC4, 0xCC),
    "dec": (0xC6, 0xCE, 0xD6, 0xDE), "dex": (0xCA,), "dey": (0x88,),
    "eor": (0x41, 0x45, 0x49, 0x4D, 0x51, 0x55, 0x59, 0x5D),
    "inc": (0xE6, 0xEE, 0xF6, 0xFE), "inx": (0xE8,), "iny": (0xC8,),
    "jmp": (0x4C, 0x6C), "jsr": (0x20,),
    "lda": (0xA1, 0xA5, 0xA9, 0xAD, 0xB1, 0xB5, 0xB9, 0xBD),
    "ldx": (0xA2, 0xA6, 0xAE, 0xB6, 0xBE),
    "ldy": (0xA0, 0xA4, 0xAC, 0xB4, 0xBC),
    "lsr": (0x46, 0x4A, 0x4E, 0x56, 0x5E), "nop": (0xEA,),
    "ora": (0x01, 0x05, 0x09, 0x0D, 0x11, 0x15, 0x19, 0x1D),
    "pha": (0x48,), "php": (0x08,), "pla": (0x68,), "plp": (0x28,),
    "rol": (0x26, 0x2A, 0x2E, 0x36, 0x3E),
    "ror": (0x66, 0x6A, 0x6E, 0x76, 0x7E), "rti": (0x40,), "rts": (0x60,),
    "sbc": (0xE1, 0xE5, 0xE9, 0xED, 0xF1, 0xF5, 0xF9, 0xFD),
    "sec": (0x38,), "sed": (0xF8,), "sei": (0x78,),
    "sta": (0x81, 0x85, 0x8D, 0x91, 0x95, 0x99, 0x9D),
    "stx": (0x86, 0x8E, 0x96), "sty": (0x84, 0x8C, 0x94),
    "tax": (0xAA,), "tay": (0xA8,), "tsx": (0xBA,), "txa": (0x8A,),
    "txs": (0x9A,), "tya": (0x98,)
}

MODE_BY_OPCODE = {}


def assign(mode, opcodes):
    for opcode in opcodes:
        MODE_BY_OPCODE[opcode] = mode


assign("imp", (0x00, 0x08, 0x18, 0x28, 0x38, 0x40, 0x48, 0x58, 0x60,
               0x68, 0x78, 0x88, 0x8A, 0x98, 0x9A, 0xA8, 0xAA, 0xB8,
               0xBA, 0xC8, 0xCA, 0xD8, 0xE8, 0xEA, 0xF8))
assign("acc", (0x0A, 0x2A, 0x4A, 0x6A))
assign("rel", (0x10, 0x30, 0x50, 0x70, 0x90, 0xB0, 0xD0, 0xF0))
assign("imm", (0x09, 0x29, 0x49, 0x69, 0x89, 0xA0, 0xA2, 0xA9,
               0xC0, 0xC9, 0xE0, 0xE9))
assign("zp", (0x05, 0x06, 0x24, 0x25, 0x26, 0x45, 0x46, 0x65, 0x66,
              0x84, 0x85, 0x86, 0xA4, 0xA5, 0xA6, 0xC4, 0xC5, 0xC6,
              0xE4, 0xE5, 0xE6))
assign("zp_x", (0x15, 0x16, 0x35, 0x36, 0x55, 0x56, 0x75, 0x76,
                0x94, 0x95, 0xB4, 0xB5, 0xD5, 0xD6, 0xF5, 0xF6))
assign("zp_y", (0x96, 0xB6))
assign("abs", (0x0D, 0x0E, 0x20, 0x2C, 0x2D, 0x2E, 0x4C, 0x4D, 0x4E,
               0x6C, 0x6D, 0x6E, 0x8C, 0x8D, 0x8E, 0xAC, 0xAD, 0xAE,
               0xCC, 0xCD, 0xCE, 0xEC, 0xED, 0xEE))
assign("abs_x", (0x1D, 0x1E, 0x3D, 0x3E, 0x5D, 0x5E, 0x7D, 0x7E,
                  0x9D, 0xBC, 0xBD, 0xDD, 0xDE, 0xFD, 0xFE))
assign("abs_y", (0x19, 0x39, 0x59, 0x79, 0x99, 0xB9, 0xBE, 0xD9,
                  0xF9))
assign("ind", (0x6C,))
assign("ind_x", (0x01, 0x21, 0x41, 0x61, 0x81, 0xA1, 0xC1, 0xE1))
assign("ind_y", (0x11, 0x31, 0x51, 0x71, 0x91, 0xB1, 0xD1, 0xF1))

OPCODE_TO_MNEMONIC = {}
for _name, _opcodes in MNEMONICS.items():
    for _opcode in _opcodes:
        OPCODE_TO_MNEMONIC[_opcode] = _name

SIZE_BY_MODE = {
    "imp": 1, "acc": 1, "imm": 2, "rel": 2, "zp": 2, "zp_x": 2,
    "zp_y": 2, "ind_x": 2, "ind_y": 2, "abs": 3, "abs_x": 3,
    "abs_y": 3, "ind": 3
}
BRANCHES = set((0x10, 0x30, 0x50, 0x70, 0x90, 0xB0, 0xD0, 0xF0))
TERMINALS = set((0x00, 0x40, 0x60))
WRITE_MNEMONICS = set(("sta", "stx", "sty"))
RMW_MNEMONICS = set(("asl", "dec", "inc", "lsr", "rol", "ror"))


def cpu_offset(address):
    if address < 0x8000 or address > 0xffff:
        return None
    return address - 0x8000


def u16(prg, offset):
    return prg[offset] | (prg[offset + 1] << 8)


def decode(prg, address):
    offset = cpu_offset(address)
    if offset is None or offset >= len(prg):
        return None
    opcode = prg[offset]
    mnemonic = OPCODE_TO_MNEMONIC.get(opcode)
    mode = MODE_BY_OPCODE.get(opcode)
    if mnemonic is None or mode is None:
        return None
    size = SIZE_BY_MODE[mode]
    if offset + size > len(prg):
        return None
    operand = None
    if size == 2:
        operand = prg[offset + 1]
    elif size == 3:
        operand = u16(prg, offset + 1)
    if mode == "rel":
        operand = (address + 2 + (operand if operand < 0x80 else operand - 0x100)) & 0xffff
    return {"address": address, "opcode": opcode, "mnemonic": mnemonic,
            "mode": mode, "size": size, "operand": operand}


def direct_successors(instruction):
    address = instruction["address"]
    next_address = address + instruction["size"]
    opcode = instruction["opcode"]
    if opcode in TERMINALS:
        return []
    if opcode in BRANCHES:
        return [instruction["operand"], next_address]
    if opcode == 0x4C:
        return [instruction["operand"]]
    if opcode == 0x6C:
        return []
    return [next_address]


def control_flow(prg, seeds):
    work = deque(sorted(set(seeds)))
    seen = {}
    edges = set()
    indirect_jumps = []
    invalid = set()
    while work:
        address = work.popleft()
        if address in seen or cpu_offset(address) is None:
            continue
        instruction = decode(prg, address)
        if instruction is None:
            invalid.add(address)
            continue
        seen[address] = instruction
        if instruction["opcode"] == 0x6C:
            indirect_jumps.append(address)
        if instruction["opcode"] == 0x20:
            target = instruction["operand"]
            edges.add((address, target, "call"))
            work.append(target)
        for target in direct_successors(instruction):
            if cpu_offset(target) is not None:
                edge_kind = "branch" if instruction["opcode"] in BRANCHES else "flow"
                edges.add((address, target, edge_kind))
                work.append(target)
    return seen, edges, indirect_jumps, invalid


def jump_engine_targets(prg, instructions, jump_engine=0x8e04):
    """Resolve the ROM's stack-return-address dispatch idiom conservatively.

    A JSR to JumpEngine is followed by a contiguous little-endian table.  The
    accumulator selects one entry at runtime, so every in-PRG word before the
    first non-PRG word is a reachable candidate.  The resulting edges are
    marked separately from ordinary direct branches in the local report.
    """
    targets = set()
    edges = set()
    tables = []
    for instruction in instructions.values():
        if instruction["opcode"] != 0x20 or instruction["operand"] != jump_engine:
            continue
        table = instruction["address"] + instruction["size"]
        entries = []
        for index in range(64):
            offset = cpu_offset(table + index * 2)
            if offset is None or offset + 1 >= len(prg):
                break
            target = u16(prg, offset)
            if cpu_offset(target) is None:
                break
            entries.append(target)
            targets.add(target)
            edges.add((instruction["address"], target, "jump_engine"))
        if entries:
            tables.append((instruction["address"], tuple(entries)))
    return targets, edges, tables


def contiguous_ranges(addresses):
    if not addresses:
        return []
    ordered = sorted(addresses)
    ranges = []
    start = previous = ordered[0]
    for address in ordered[1:]:
        if address != previous + 1:
            ranges.append((start, previous))
            start = address
        previous = address
    ranges.append((start, previous))
    return ranges


def classify_access(instruction):
    mode = instruction["mode"]
    if mode not in ("zp", "zp_x", "zp_y", "abs", "abs_x", "abs_y"):
        return None
    address = instruction["operand"]
    if mode.startswith("zp"):
        space = "ram"
    elif 0x2000 <= address <= 0x2007:
        space = "ppu"
    elif 0x4000 <= address <= 0x4017:
        space = "apu_io"
    elif address < 0x0800:
        space = "ram"
    elif address >= 0x8000:
        space = "prg"
    else:
        space = "other"
    mnemonic = instruction["mnemonic"]
    direction = "write" if mnemonic in WRITE_MNEMONICS else (
        "read_write" if mnemonic in RMW_MNEMONICS else "read")
    return space, direction, address, mode


def listing_claims(prg, path):
    """Read an optional local listing as a claim source, never as ROM input."""
    pc = None
    labels = []
    claimed_code = set()
    claimed_data = set()
    mismatch = []
    unknown = []
    trusted = True
    label_re = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*):")
    directive_re = re.compile(r"^\s*\.(\w+)\s*(.*)$")
    instruction_re = re.compile(r"^\s+([A-Za-z]{3})(?:\s+.*)?$")
    for line_number, raw in enumerate(path.read_text(encoding="latin-1").splitlines(), 1):
        source = raw.split(";", 1)[0].rstrip()
        if not source.strip():
            continue
        directive = directive_re.match(source)
        if directive:
            name, argument = directive.group(1).lower(), directive.group(2)
            if name == "org":
                match = re.search(r"\$([0-9a-fA-F]+)", argument)
                pc = int(match.group(1), 16) if match else None
                trusted = True
            elif pc is not None and name in ("db", "byte"):
                count = len([item for item in argument.split(",") if item.strip()])
                if trusted and cpu_offset(pc) is not None:
                    claimed_data.update(range(pc, min(pc + count, 0x10000)))
                pc += count
            elif pc is not None and name in ("dw", "word"):
                count = 2 * len([item for item in argument.split(",") if item.strip()])
                if trusted and cpu_offset(pc) is not None:
                    claimed_data.update(range(pc, min(pc + count, 0x10000)))
                pc += count
            elif pc is not None and name == "hex":
                count = len(re.sub(r"[^0-9a-fA-F]", "", argument)) // 2
                if trusted and cpu_offset(pc) is not None:
                    claimed_data.update(range(pc, min(pc + count, 0x10000)))
                pc += count
            elif name not in ("index", "mem"):
                unknown.append(line_number)
            continue
        label = label_re.match(source)
        if label:
            if trusted and pc is not None and cpu_offset(pc) is not None:
                labels.append((pc, label.group(1)))
            source = source[label.end():]
            if not source.strip():
                continue
        instruction = instruction_re.match(source)
        if instruction and pc is not None and cpu_offset(pc) is not None:
            decoded = decode(prg, pc)
            expected = instruction.group(1).lower()
            if decoded is None or decoded["mnemonic"] != expected:
                mismatch.append((pc, line_number))
                trusted = False
                if decoded is None:
                    pc += 1
                else:
                    pc += decoded["size"]
            elif trusted:
                for address in range(pc, pc + decoded["size"]):
                    claimed_code.add(address)
                pc += decoded["size"]
            else:
                pc += decoded["size"]
    return labels, claimed_code, claimed_data, mismatch, unknown


def analyze(prg, listing=None):
    vectors = {
        "nmi": u16(prg, 0x7ffa),
        "reset": u16(prg, 0x7ffc),
        "irq": u16(prg, 0x7ffe)
    }
    labels = []
    claims = set()
    data_claims = set()
    listing_mismatch = []
    listing_unknown = []
    if listing is not None:
        labels, claims, data_claims, listing_mismatch, listing_unknown = listing_claims(prg, listing)
    seeds = list(vectors.values()) + [address for address, _ in labels
                                      if address in claims]
    instructions, edges, indirect, invalid = control_flow(prg, seeds)
    dispatch_edges = set()
    dispatch_tables = []
    while True:
        dispatch_targets, new_edges, tables = jump_engine_targets(prg, instructions)
        new_seeds = dispatch_targets - set(instructions)
        dispatch_edges.update(new_edges)
        dispatch_tables = tables
        if not new_seeds:
            break
        instructions, edges, indirect, invalid = control_flow(
            prg, list(instructions) + list(new_seeds))
    edges.update(dispatch_edges)
    code = set()
    for instruction in instructions.values():
        code.update(range(instruction["address"],
                          instruction["address"] + instruction["size"]))
    code.update(claims)
    all_addresses = set(range(0x8000, 0x10000))
    vector_bytes = set(range(0xfffa, 0x10000))
    data = data_claims - code - vector_bytes
    unresolved = all_addresses - code - data - vector_bytes
    access = Counter()
    operand_bases = defaultdict(set)
    call_targets = Counter()
    for instruction in instructions.values():
        entry = classify_access(instruction)
        if entry is not None:
            space, direction, address, mode = entry
            access[(space, direction)] += 1
            operand_bases[space].add(address)
        if instruction["opcode"] == 0x20:
            call_targets[instruction["operand"]] += 1
    label_map = defaultdict(list)
    for address, label in labels:
        label_map[address].append(label)
    return {
        "vectors": vectors, "instructions": instructions, "edges": edges,
        "indirect": indirect, "invalid": invalid, "code": code, "data": data,
        "unresolved": unresolved,
        "access": access, "operand_bases": operand_bases,
        "call_targets": call_targets, "labels": label_map,
        "dispatch_tables": dispatch_tables,
        "listing_claim_count": len(claims),
        "listing_mismatch": listing_mismatch,
        "listing_unknown": listing_unknown
    }


def emit(result, rom_sha256, output):
    code_ranges = contiguous_ranges(result["code"])
    data_ranges = contiguous_ranges(result["data"])
    unresolved_ranges = contiguous_ranges(result["unresolved"])
    lines = [
        "format=mysmb-static-analysis-v1",
        "rom-sha256=%s" % rom_sha256,
        "prg-bytes=32768",
        "vector-nmi=%04X" % result["vectors"]["nmi"],
        "vector-reset=%04X" % result["vectors"]["reset"],
        "vector-irq=%04X" % result["vectors"]["irq"],
        "code-bytes=%d" % len(result["code"]),
        "data-bytes=%d" % len(result["data"]),
        "vector-bytes=6",
        "unclassified-bytes=%d" % len(result["unresolved"]),
        "decoded-instructions=%d" % len(result["instructions"]),
        "cfg-edges=%d" % len(result["edges"]),
        "jump-engine-tables=%d" % len(result["dispatch_tables"]),
        "jump-engine-targets=%d" % len({target for _, entries in result["dispatch_tables"] for target in entries}),
        "indirect-jumps=%d" % len(result["indirect"]),
        "invalid-opcode-frontiers=%d" % len(result["invalid"]),
        "listing-matched-code-bytes=%d" % result["listing_claim_count"],
        "listing-mismatch-sites=%d" % len(result["listing_mismatch"]),
        "listing-unknown-directives=%d" % len(result["listing_unknown"]),
        "code-ranges=%d" % len(code_ranges),
        "data-ranges=%d" % len(data_ranges),
        "unclassified-ranges=%d" % len(unresolved_ranges)
    ]
    for space, direction in sorted(result["access"]):
        lines.append("access-%s-%s=%d" % (space, direction,
                                            result["access"][(space, direction)]))
    for space in sorted(result["operand_bases"]):
        lines.append("operand-bases-%s=%d" % (space,
                                                 len(result["operand_bases"][space])))
    for index, target in enumerate(sorted(result["call_targets"],
                                          key=lambda item: (-result["call_targets"][item], item))[:64]):
        names = ",".join(sorted(result["labels"].get(target, ())))
        lines.append("call-target-%02d=%04X,count=%d,label=%s" % (
            index, target, result["call_targets"][target], names or "none"))
    for index, address in enumerate(sorted(result["indirect"])):
        names = ",".join(sorted(result["labels"].get(address, ())))
        lines.append("indirect-jump-%02d=%04X,label=%s" %
                     (index, address, names or "none"))
    for index, (callsite, entries) in enumerate(result["dispatch_tables"]):
        lines.append("jump-engine-table-%02d=callsite:%04X,entries:%d" %
                     (index, callsite, len(entries)))
    for index, (address, line) in enumerate(result["listing_mismatch"][:128]):
        lines.append("listing-mismatch-%03d=cpu:%04X,line:%d" %
                     (index, address, line))
    for index, (start, end) in enumerate(unresolved_ranges):
        lines.append("unclassified-range-%03d=cpu:%04X-%04X,bytes:%d" %
                     (index, start, end, end - start + 1))
    output.write_text("\n".join(lines) + "\n", encoding="ascii")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--listing", type=Path)
    args = parser.parse_args()
    prg, _ = read_nrom(args.rom)
    result = analyze(prg, args.listing)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    emit(result, hashlib.sha256(args.rom.read_bytes()).hexdigest(), args.output)


if __name__ == "__main__":
    main()
