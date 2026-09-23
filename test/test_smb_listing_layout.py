#!/usr/bin/env python3
"""Synthetic layout checks for the local listing-layout parser."""

import importlib.util
import sys
import tempfile
from pathlib import Path


def load_module():
    path = Path(__file__).resolve().parents[1] / "tools" / "smb_listing_layout.py"
    sys.path.insert(0, str(path.parent))
    spec = importlib.util.spec_from_file_location("smb_listing_layout", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    module = load_module()
    with tempfile.TemporaryDirectory() as temporary:
        listing = Path(temporary) / "synthetic.asm"
        listing.write_text(
            "RAM = $04\n.org $8000\nStart: lda RAM\n jsr Target\n.db $01,$02\n"
            "Target: rts\n", encoding="ascii")
        result = module.layout(listing)
    if result["labels"] != [(0x8000, "Start", 3), (0x8007, "Target", 6)]:
        raise SystemExit(1)
    if [(item[0], item[1], item[2]) for item in result["instructions"]] != [
            (0x8000, 0xA5, 2), (0x8002, 0x20, 3), (0x8007, 0x60, 1)]:
        raise SystemExit(1)
    if result["data"] != [(0x8005, 2, 5)]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
