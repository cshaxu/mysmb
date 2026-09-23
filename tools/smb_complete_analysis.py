#!/usr/bin/env python3
"""Combine direct CFG and measured listing reconciliation into a PRG ledger."""

import argparse
import hashlib
from pathlib import Path

from smb_listing_layout import layout
from smb_rom_codegen import read_nrom
from smb_static_analysis import analyze, contiguous_ranges


SHIFT_BREAK = 0xAEB8
POST_BREAK_SHIFT = 0x24
ROM_ONLY_DATA = (
    (0xAEB8, 0xAEDB, "revision-inserted-area-data"),
    (0xFF86, 0xFFEF, "revision-extra-audio-data"),
    (0xFFF3, 0xFFF9, "revision-tail-data")
)


def map_listing_address(address):
    return address if address < SHIFT_BREAK else address + POST_BREAK_SHIFT


def reconciled_data(layout_result):
    result = set()
    for start, count, _ in layout_result["data"]:
        for source_address in range(start, start + count):
            address = map_listing_address(source_address)
            if 0x8000 <= address <= 0xffff:
                result.add(address)
    return result


def reconciled_code(prg, layout_result):
    from smb_static_analysis import decode

    result = set()
    for source_address, opcode, size, _, _ in layout_result["instructions"]:
        address = map_listing_address(source_address)
        instruction = decode(prg, address)
        if instruction is not None and instruction["opcode"] == opcode and instruction["size"] == size:
            result.update(range(address, address + size))
    return result


def rom_only_data():
    result = set()
    for start, end, _ in ROM_ONLY_DATA:
        result.update(range(start, end + 1))
    return result


def ledger(prg, listing_path):
    direct = analyze(prg, listing_path)
    source = layout(listing_path)
    vectors = set(range(0xfffa, 0x10000))
    direct_code = set(direct["code"])
    code = set(direct_code)
    shifted_code = reconciled_code(prg, source) - code - vectors
    code.update(shifted_code)
    same_address_data = set(direct["data"]) - code - vectors
    shifted_data = reconciled_data(source) - code - vectors - same_address_data
    revision_data = rom_only_data() - code - vectors - same_address_data - shifted_data
    all_addresses = set(range(0x8000, 0x10000))
    unresolved = all_addresses - code - vectors - same_address_data - shifted_data - revision_data
    return {"direct": direct, "source": source, "direct_code": direct_code,
            "code": code,
            "shifted_code": shifted_code, "same_address_data": same_address_data,
            "shifted_data": shifted_data, "revision_data": revision_data,
            "unresolved": unresolved}


def emit(rom_path, listing_path, output):
    prg, _ = read_nrom(rom_path)
    result = ledger(prg, listing_path)
    direct = result["direct"]
    lines = [
        "format=mysmb-complete-prg-ledger-v1",
        "rom-sha256=%s" % hashlib.sha256(rom_path.read_bytes()).hexdigest(),
        "prg-bytes=32768",
        "direct-cfg-code-bytes=%d" % len(result["direct_code"]),
        "reconciled-code-additions=%d" % len(result["shifted_code"]),
        "same-address-listing-data-bytes=%d" % len(result["same_address_data"]),
        "reconciled-shifted-data-bytes=%d" % len(result["shifted_data"]),
        "rom-only-revision-data-bytes=%d" % len(result["revision_data"]),
        "vector-bytes=6",
        "unresolved-bytes=%d" % len(result["unresolved"]),
        "source-shift-break=%04X" % SHIFT_BREAK,
        "source-post-break-shift=+%d" % POST_BREAK_SHIFT,
        "decoded-instructions=%d" % len(direct["instructions"]),
        "jump-engine-tables=%d" % len(direct["dispatch_tables"]),
        "indirect-jumps=%d" % len(direct["indirect"]),
        "listing-mismatch-sites=%d" % len(direct["listing_mismatch"]),
        "unresolved-ranges=%d" % len(contiguous_ranges(result["unresolved"]))
    ]
    for start, end, category in ROM_ONLY_DATA:
        lines.append("rom-only-data=cpu:%04X-%04X,bytes:%d,category:%s" %
                     (start, end, end - start + 1, category))
    for index, (start, end) in enumerate(contiguous_ranges(result["unresolved"])):
        lines.append("unresolved-range-%03d=cpu:%04X-%04X,bytes:%d" %
                     (index, start, end, end - start + 1))
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text("\n".join(lines) + "\n", encoding="ascii")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--listing", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    emit(args.rom, args.listing, args.output)


if __name__ == "__main__":
    main()
