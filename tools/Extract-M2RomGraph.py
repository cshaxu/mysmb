"""Extract a neutral, source-addressed control graph from the reviewed SMB1 ASM.

The output is an audit input, never ROM-derived program material: it contains
only inventory labels, assembly line numbers and control-edge classifications.
"""
import argparse
import json
import re
from pathlib import Path


LABEL_ROW = re.compile(r"^\|\s*(\d+)\s*\|\s*`([^`]+)`\s*\|")
LABEL_DEF = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*):")
INSTRUCTION = re.compile(r"^\s*([A-Za-z]{3})(?:\s+([^\s,]+))?")
TARGET = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)$")
CONTROL = {
    "jsr": "call", "jmp": "jump", "bcc": "branch", "bcs": "branch",
    "beq": "branch", "bne": "branch", "bmi": "branch", "bpl": "branch",
    "bvc": "branch", "bvs": "branch"
}
BRANCHES = {"bcc", "bcs", "beq", "bne", "bmi", "bpl", "bvc", "bvs"}


def inventory(path):
    result = []
    for line in path.read_text(encoding="utf-8").splitlines():
        match = LABEL_ROW.match(line)
        if match:
            result.append((match.group(2), int(match.group(1))))
    return result


def blocks(path, known):
    result = []
    current = None
    for number, raw in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        code = raw.split(";", 1)[0]
        label = LABEL_DEF.match(code)
        if label and label.group(1) in known:
            if current:
                result.append(current)
            current = {"label": label.group(1), "line": number, "instructions": []}
        if not current:
            continue
        code = LABEL_DEF.sub("", code, count=1)
        instruction = INSTRUCTION.match(code)
        if instruction:
            current["instructions"].append(
                (number, instruction.group(1).lower(), instruction.group(2) or ""))
    if current:
        result.append(current)
    return result


def add(edges, seen, source, target, kind, line, instruction, selector=None):
    if not target:
        return
    key = (source, target, kind, line, selector)
    if key in seen:
        return
    seen.add(key)
    edge = {"from": source, "to": target, "type": kind,
            "asmLine": line, "instruction": instruction}
    if selector is not None:
        edge["selector"] = selector
    edges.append(edge)


def jump_engine_edges(rows, known, owners):
    result = []
    for index, raw in enumerate(rows):
        code = raw.split(";", 1)[0]
        if not re.search(r"\bjsr\s+JumpEngine\b", code):
            continue
        source = owners[index]
        selector = 0
        probe = index + 1
        while probe < len(rows):
            candidate = rows[probe].split(";", 1)[0].strip()
            if not candidate:
                probe += 1
                continue
            word = re.match(r"^\.word\s+([A-Za-z_][A-Za-z0-9_]*)", candidate)
            if not word:
                break
            if source and word.group(1) in known:
                result.append((source, word.group(1), index + 1, selector))
            selector += 1
            probe += 1
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--asm", type=Path, required=True)
    parser.add_argument("--inventory", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    labels = inventory(args.inventory)
    known = {name for name, _ in labels}
    block_list = blocks(args.asm, known)
    edges, seen, calls = [], set(), []
    for index, block in enumerate(block_list):
        for line, opcode, operand in block["instructions"]:
            target = TARGET.match(operand)
            if opcode in CONTROL and target and target.group(1) in known:
                add(edges, seen, block["label"], target.group(1), CONTROL[opcode], line, opcode)
                if opcode == "jsr":
                    calls.append((block["label"], target.group(1), line))
        if not block["instructions"]:
            continue
        line, opcode, _ = block["instructions"][-1]
        successor = block_list[index + 1]["label"] if index + 1 < len(block_list) else None
        if opcode in BRANCHES or opcode not in {"jmp", "rts", "rti", "brk"}:
            add(edges, seen, block["label"], successor, "fallthrough", line, opcode)
    for caller, callee, line in calls:
        add(edges, seen, callee, caller, "return", line, "rts/rti")
    add(edges, seen, "<vector>", "Start", "vector", 0, "vector")
    add(edges, seen, "<vector>", "NonMaskableInterrupt", "vector", 0, "vector")
    rows = args.asm.read_text(encoding="utf-8").splitlines()
    owners = []
    current = None
    for raw in rows:
        match = LABEL_DEF.match(raw.split(";", 1)[0])
        if match and match.group(1) in known:
            current = match.group(1)
        owners.append(current)
    for source, target, line, selector in jump_engine_edges(rows, known, owners):
        add(edges, seen, source, target, "jump-engine-dispatch", line,
            "jsr JumpEngine", selector)
    counts = {kind: sum(edge["type"] == kind for edge in edges)
              for kind in sorted({edge["type"] for edge in edges})}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps({"schema": 1, "inventoryNodes": len(labels),
        "edges": edges, "counts": counts, "totalEdges": len(edges)}, indent=2) + "\n",
        encoding="utf-8")
    print(json.dumps({"total": len(edges), **counts}, indent=2))


if __name__ == "__main__":
    main()
