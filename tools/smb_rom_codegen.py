#!/usr/bin/env python3
"""Generate owner-local C90 ROM data and a neutral NROM address map."""

import argparse
import hashlib
from pathlib import Path

HEADER_SIZE = 16
PRG_SIZE = 32 * 1024
CHR_SIZE = 8 * 1024


def write_array(output, name, data):
    output.write("const unsigned char %s[%d] = {\n" % (name, len(data)))
    for offset in range(0, len(data), 12):
        row = ", ".join("0x%02X" % value for value in data[offset:offset + 12])
        output.write("    %s%s\n" % (row, "," if offset + 12 < len(data) else ""))
    output.write("};\n\n")


def read_nrom(path):
    image = path.read_bytes()
    if len(image) != HEADER_SIZE + PRG_SIZE + CHR_SIZE:
        raise ValueError("expected a 32 KiB PRG plus 8 KiB CHR iNES image")
    if image[:4] != b"NES\x1a":
        raise ValueError("missing iNES signature")
    if image[4] != 2 or image[5] != 1:
        raise ValueError("expected iNES PRG=2 and CHR=1")
    if (image[6] >> 4) != 0 or (image[7] & 0xF0) != 0:
        raise ValueError("only Mapper 0/NROM is supported")
    return image[HEADER_SIZE:HEADER_SIZE + PRG_SIZE], image[HEADER_SIZE + PRG_SIZE:]


def generate(rom_path, output_dir):
    prg, chr_data = read_nrom(rom_path)
    output_dir.mkdir(parents=True, exist_ok=True)
    header_path = output_dir / "smb1_local_rom.h"
    source_path = output_dir / "smb1_local_rom.c"
    map_path = output_dir / "smb1_local_map.txt"
    digest = hashlib.sha256(rom_path.read_bytes()).hexdigest()

    header_path.write_text(
        "#ifndef MYSMB_LOCAL_ROM_H\n"
        "#define MYSMB_LOCAL_ROM_H\n\n"
        "#define MYSMB_LOCAL_PRG_SIZE 32768U\n"
        "#define MYSMB_LOCAL_CHR_SIZE 8192U\n\n"
        "extern const unsigned char mysmb_local_prg[MYSMB_LOCAL_PRG_SIZE];\n"
        "extern const unsigned char mysmb_local_chr[MYSMB_LOCAL_CHR_SIZE];\n\n"
        "#endif\n",
        encoding="ascii",
    )
    with source_path.open("w", encoding="ascii", newline="\n") as output:
        output.write("#include \"smb1_local_rom.h\"\n\n")
        write_array(output, "mysmb_local_prg", prg)
        write_array(output, "mysmb_local_chr", chr_data)
    map_path.write_text(
        "format=mysmb-local-nrom-map-v1\n"
        "sha256=%s\n"
        "cpu:8000-FFFF=prg[0000-7FFF]\n"
        "ppu:0000-1FFF=chr[0000-1FFF]\n"
        "vector:nmi=prg[7FFA-7FFB]\n"
        "vector:reset=prg[7FFC-7FFD]\n"
        "vector:irq=prg[7FFE-7FFF]\n" % digest,
        encoding="ascii",
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    generate(args.rom, args.output)


if __name__ == "__main__":
    main()
