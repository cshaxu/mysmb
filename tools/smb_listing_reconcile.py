#!/usr/bin/env python3
"""Reconcile local listing instruction landmarks with direct-ROM CFG metadata."""

import argparse
import hashlib
from collections import Counter
from pathlib import Path

from smb_listing_layout import layout
from smb_rom_codegen import read_nrom
from smb_static_analysis import analyze


def signature_from_listing(instructions, start, count):
    by_address = {address: (opcode, size) for address, opcode, size, _, _ in instructions}
    values = []
    address = start
    for _ in range(count):
        item = by_address.get(address)
        if item is None:
            return ()
        opcode, size = item
        values.append(opcode)
        address += size
    return tuple(values)


def signature_from_rom(instructions, start, count):
    values = []
    address = start
    for _ in range(count):
        item = instructions.get(address)
        if item is None:
            return ()
        values.append(item["opcode"])
        address += item["size"]
    return tuple(values)


def reconcile(listing_layout, analysis, width=7):
    rom_signatures = {}
    for address in analysis["instructions"]:
        signature = signature_from_rom(analysis["instructions"], address, width)
        if len(signature) == width:
            rom_signatures.setdefault(signature, []).append(address)
    anchors = []
    for expected, label, line in listing_layout["labels"]:
        signature = signature_from_listing(listing_layout["instructions"], expected, width)
        candidates = rom_signatures.get(signature, ())
        if len(signature) == width and len(candidates) == 1:
            actual = candidates[0]
            anchors.append((expected, actual, actual - expected, label, line))
    return anchors


def emit(rom_path, listing_path, output):
    prg, _ = read_nrom(rom_path)
    listing = layout(listing_path)
    analysis = analyze(prg, listing_path)
    anchors = reconcile(listing, analysis)
    shifts = Counter(delta for _, _, delta, _, _ in anchors)
    lines = [
        "format=mysmb-listing-reconcile-v1",
        "rom-sha256=%s" % hashlib.sha256(rom_path.read_bytes()).hexdigest(),
        "listing-sha256=%s" % hashlib.sha256(listing_path.read_bytes()).hexdigest(),
        "listing-labels=%d" % len(listing["labels"]),
        "listing-instructions=%d" % len(listing["instructions"]),
        "unique-opcode-anchors=%d" % len(anchors),
        "distinct-address-shifts=%d" % len(shifts)
    ]
    for delta, count in sorted(shifts.items(), key=lambda item: (-item[1], item[0])):
        lines.append("shift=%+d,anchors=%d" % (delta, count))
    for index, (expected, actual, delta, label, line) in enumerate(anchors):
        lines.append("anchor-%04d=listing:%04X,rom:%04X,shift:%+d,label:%s,line:%d" %
                     (index, expected, actual, delta, label, line))
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
