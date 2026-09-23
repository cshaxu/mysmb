#!/usr/bin/env python3
"""Contract checks for listing address reconciliation."""

import importlib.util
import sys
from pathlib import Path


def load_module():
    path = Path(__file__).resolve().parents[1] / "tools" / "smb_complete_analysis.py"
    sys.path.insert(0, str(path.parent))
    spec = importlib.util.spec_from_file_location("smb_complete_analysis", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    module = load_module()
    if module.map_listing_address(0xAEB7) != 0xAEB7:
        raise SystemExit(1)
    if module.map_listing_address(0xAEB8) != 0xAEDC:
        raise SystemExit(1)
    result = module.reconciled_data({"data": [(0xAEB7, 3, 1)]})
    if result != {0xAEB7, 0xAEDC, 0xAEDD}:
        raise SystemExit(1)
    if module.rom_only_data() != set(range(0xAEB8, 0xAEDC)) | set(range(0xFF86, 0xFFF0)) | set(range(0xFFF3, 0xFFFA)):
        raise SystemExit(1)


if __name__ == "__main__":
    main()
