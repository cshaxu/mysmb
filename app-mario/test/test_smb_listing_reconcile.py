#!/usr/bin/env python3
"""Project-owned signature-reconciliation contract checks."""

import importlib.util
import sys
from pathlib import Path


def load_module():
    path = Path(__file__).resolve().parents[1] / "tools" / "smb_listing_reconcile.py"
    sys.path.insert(0, str(path.parent))
    spec = importlib.util.spec_from_file_location("smb_listing_reconcile", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    module = load_module()
    listing = {"labels": [(0x8000, "Start", 1)],
               "instructions": [(0x8000, 0xA9, 2, "lda", 1),
                                (0x8002, 0x60, 1, "rts", 2),
                                (0x8003, 0xEA, 1, "nop", 3),
                                (0x8004, 0xEA, 1, "nop", 4),
                                (0x8005, 0xEA, 1, "nop", 5),
                                (0x8006, 0xEA, 1, "nop", 6),
                                (0x8007, 0xEA, 1, "nop", 7)]}
    instructions = {}
    address = 0x8020
    for opcode, size in ((0xA9, 2), (0x60, 1), (0xEA, 1), (0xEA, 1),
                         (0xEA, 1), (0xEA, 1), (0xEA, 1)):
        instructions[address] = {"opcode": opcode, "size": size}
        address += size
    anchors = module.reconcile(listing, {"instructions": instructions})
    if anchors != [(0x8000, 0x8020, 0x20, "Start", 1)]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
