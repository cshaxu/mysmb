#!/usr/bin/env python3
"""Extract the owner-local SMB1 title-screen VRAM command stream as C90 data."""

import argparse
from pathlib import Path

from smb_rom_codegen import read_nrom, write_array

TITLE_CHR_OFFSET = 0x1EC0
TITLE_DATA_SIZE = 0x013A
TITLE_ICON_PRG_OFFSET = 0x031D
TITLE_ICON_DATA_SIZE = 7


def generate(rom_path, output_dir):
    prg, chr_data = read_nrom(rom_path)
    data = chr_data[TITLE_CHR_OFFSET:TITLE_CHR_OFFSET + TITLE_DATA_SIZE]
    icon = prg[TITLE_ICON_PRG_OFFSET + 1:TITLE_ICON_PRG_OFFSET + 1 + TITLE_ICON_DATA_SIZE]
    if len(data) != TITLE_DATA_SIZE:
        raise ValueError("title command stream is outside the CHR image")
    if len(icon) != TITLE_ICON_DATA_SIZE:
        raise ValueError("title icon command stream is outside the PRG image")
    output_dir.mkdir(parents=True, exist_ok=True)
    (output_dir / "smb1_local_title.h").write_text(
        "#ifndef MYSMB_LOCAL_TITLE_H\n"
        "#define MYSMB_LOCAL_TITLE_H\n\n"
        "#define MYSMB_LOCAL_TITLE_DATA_SIZE 314U\n"
        "#define MYSMB_LOCAL_TITLE_ICON_DATA_SIZE 7U\n\n"
        "extern const unsigned char mysmb_local_title_data[MYSMB_LOCAL_TITLE_DATA_SIZE];\n\n"
        "extern const unsigned char mysmb_local_title_icon_data[MYSMB_LOCAL_TITLE_ICON_DATA_SIZE];\n\n"
        "#endif\n",
        encoding="ascii",
    )
    with (output_dir / "smb1_local_title.c").open("w", encoding="ascii", newline="\n") as output:
        output.write('#include "smb1_local_title.h"\n\n')
        write_array(output, "mysmb_local_title_data", data)
        output.write("\n")
        write_array(output, "mysmb_local_title_icon_data", icon)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    generate(args.rom, args.output)


if __name__ == "__main__":
    main()
