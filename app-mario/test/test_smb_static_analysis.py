#!/usr/bin/env python3
"""Synthetic contract checks for the project-owned 2A03 static analyzer."""

import importlib.util
import sys
from pathlib import Path
from writable_tempdir import writable_temporary_directory


def load_module():
    path = Path(__file__).resolve().parents[1] / "tools" / "smb_static_analysis.py"
    sys.path.insert(0, str(path.parent))
    spec = importlib.util.spec_from_file_location("smb_static_analysis", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    analyzer = load_module()
    prg = bytearray(32768)
    start = 0x8000 - 0x8000
    prg[start:start + 9] = bytes((0xA9, 0x01, 0x20, 0x08, 0x80, 0x4C, 0x05, 0x80, 0x60))
    prg[0x7FFA:0x8000] = bytes((0x00, 0x80, 0x00, 0x80, 0x00, 0x80))
    result = analyzer.analyze(bytes(prg))
    if result["vectors"] != {"nmi": 0x8000, "reset": 0x8000, "irq": 0x8000}:
        raise SystemExit(1)
    if 0x8000 not in result["instructions"] or 0x8008 not in result["instructions"]:
        raise SystemExit(1)
    if (0x8002, 0x8008, "call") not in result["edges"]:
        raise SystemExit(1)
    with writable_temporary_directory() as temporary:
        output = Path(temporary) / "analysis.txt"
        analyzer.emit(result, "0" * 64, output)
        text = output.read_text(encoding="ascii")
        if "vector-reset=8000" not in text or "decoded-instructions=" not in text:
            raise SystemExit(1)


if __name__ == "__main__":
    main()
