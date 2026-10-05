"""Bind the enemy graphics data used by shared C to an owner-local SMB1 ROM.

Usage: python tools/Verify-EnemyGraphicsTables.py --rom PATH --listing PATH
No ROM bytes or generated output are written to the repository.
"""

import argparse
import re
from pathlib import Path


def listing_bytes(text, start, end):
    section = text.split(start + ":", 1)[1].split(end + ":", 1)[0]
    return bytes(
        int(value, 16)
        for line in section.splitlines()
        for value in re.findall(r"\$([0-9a-fA-F]{2})", line.split(";")[0])
    )


def c_table_bytes(text, name):
    body = text.split(name + "[", 1)[1].split("{", 1)[1].split("}", 1)[0]
    return bytes(
        int(value, 16) if value.lower().startswith("0x") else int(value)
        for value in re.findall(r"(0x[0-9a-fA-F]+|\d+)U", body)
    )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--listing", type=Path, required=True)
    args = parser.parse_args()

    root = Path(__file__).resolve().parents[1]
    source = (root / "src/core/oam/normal_enemy_gfx.c").read_text()
    listing = args.listing.read_text()
    rom = args.rom.read_bytes()
    if len(rom) < 16 + 32768 or rom[:4] != b"NES\x1a":
        raise ValueError("expected owner-local 32 KiB PRG iNES image")
    names = [
        "EnemyGraphicsTable", "EnemyGfxTableOffsets", "EnemyAttributeData",
        "EnemyAnimTimingBMask", "JumpspringFrameOffsets", "EnemyGfxHandler",
    ]
    tables = {
        name: listing_bytes(listing, name, successor)
        for name, successor in zip(names, names[1:])
    }
    span = b"".join(tables[name] for name in names[:-1])
    image = rom[16:16 + 32768]
    offset = image.find(span)
    if offset < 0 or image.find(span, offset + 1) >= 0:
        raise AssertionError("graphics table span is absent or ambiguous")

    expected = {
        "mysmb_enemy_graphics_table": (
            tables["EnemyGraphicsTable"] + tables["EnemyGfxTableOffsets"][:4]
        ),
        "mysmb_enemy_graphics_offsets": image[
            offset + len(tables["EnemyGraphicsTable"]):
            offset + len(tables["EnemyGraphicsTable"]) + 54
        ],
        "mysmb_enemy_attribute_data": image[
            offset + len(tables["EnemyGraphicsTable"]) +
            len(tables["EnemyGfxTableOffsets"]):
            offset + len(tables["EnemyGraphicsTable"]) +
            len(tables["EnemyGfxTableOffsets"]) + 54
        ],
    }
    for name, data in expected.items():
        if c_table_bytes(source, name) != data:
            raise AssertionError(name + " differs from owner ROM")
        print(name, len(data), "bytes match")
    print("ROM graphics span", len(span), "bytes match")


if __name__ == "__main__":
    main()
