"""Extract neutral, source-addressed data-access atoms for the M2 audit.

This reports reads/writes to RAM and table labels.  It deliberately does not
invent producer-consumer edges: those require a feasible original control path
and are entered into the current-equivalence ledger by a cohort audit.
"""
import argparse
import json
import re
from collections import Counter
from pathlib import Path

from BuildM2CurrentAuditRegistry import cohort_for, load_inventory


LABEL = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*):")
EQUATE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*\$([0-9a-fA-F]+)")
INSTRUCTION = re.compile(r"^\s*([A-Za-z]{3})\s+(.+?)\s*$")
TOKEN = re.compile(r"([A-Za-z_][A-Za-z0-9_]*|\$[0-9a-fA-F]+)")

READS = {"adc", "and", "bit", "cmp", "cpx", "cpy", "eor", "lda", "ldx",
         "ldy", "ora", "sbc"}
WRITES = {"sta", "stx", "sty"}
READ_WRITES = {"asl", "dec", "inc", "lsr", "rol", "ror"}


def symbol_definitions(rows):
    definitions = {}
    for raw in rows:
        match = EQUATE.match(raw.split(";", 1)[0])
        if match:
            definitions[match.group(1)] = int(match.group(2), 16)
    return definitions


def storage_for(token, definitions, known):
    if token.startswith("$"):
        address = int(token[1:], 16)
        if address < 0x2000:
            return "ram:%04x" % address, "ram"
        if address <= 0x401f:
            return "hardware:%04x" % address, "hardware"
        return None, None
    if token in definitions:
        address = definitions[token]
        if address < 0x2000:
            return "ram:%04x" % address, "ram"
        if address <= 0x401f:
            return "hardware:%04x" % address, "hardware"
        return None, None
    if token in known:
        return "table:%s" % token, "table"
    return None, None


def modes(opcode):
    if opcode in READS:
        return ("read",)
    if opcode in WRITES:
        return ("write",)
    if opcode in READ_WRITES:
        return ("read", "write")
    return ()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--asm", required=True, type=Path)
    parser.add_argument("--inventory", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    nodes = load_inventory(args.inventory)
    known = {node["label"] for node in nodes}
    lines = args.asm.read_text(encoding="utf-8").splitlines()
    definitions = symbol_definitions(lines)
    current = None
    accesses = []
    for line_number, raw in enumerate(lines, 1):
        code = raw.split(";", 1)[0]
        label = LABEL.match(code)
        if label and label.group(1) in known:
            current = label.group(1)
        if current is None:
            continue
        code = LABEL.sub("", code, count=1)
        instruction = INSTRUCTION.match(code)
        if not instruction:
            continue
        opcode = instruction.group(1).lower()
        operand = instruction.group(2).strip()
        if operand.startswith("#"):
            continue
        access_modes = modes(opcode)
        if not access_modes:
            continue
        token_match = TOKEN.search(operand)
        if not token_match:
            continue
        storage, storage_kind = storage_for(token_match.group(1), definitions, known)
        if not storage:
            continue
        for mode in access_modes:
            accesses.append({
                "node": current,
                "cohort": cohort_for(next(n["asmLine"] for n in nodes
                                           if n["label"] == current)),
                "storage": storage,
                "storageKind": storage_kind,
                "mode": mode,
                "asmLine": line_number,
                "instruction": opcode,
                "indirect": operand.startswith("("),
            })
    counts = Counter(access["storageKind"] for access in accesses)
    material = [a for a in accesses if a["storageKind"] in {"ram", "table"}]
    output = {
        "schemaVersion": 1,
        "purpose": "M2 data-edge audit atoms; not producer-consumer edges",
        "accesses": accesses,
        "accessCount": len(accesses),
        "materialAccessCount": len(material),
        "storageKindCounts": dict(sorted(counts.items())),
        "materialStorageCount": len({a["storage"] for a in material}),
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: output[key] for key in (
        "accessCount", "materialAccessCount", "storageKindCounts",
        "materialStorageCount")}, indent=2))


if __name__ == "__main__":
    main()
