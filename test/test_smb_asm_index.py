import importlib.util
import sys
import tempfile
from pathlib import Path


def load_module(name):
    tool_dir = Path(__file__).parents[1] / "tools"
    if str(tool_dir) not in sys.path:
        sys.path.insert(0, str(tool_dir))
    script = tool_dir / (name + ".py")
    spec = importlib.util.spec_from_file_location(name, script)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    indexer = load_module("smb_asm_index")
    build = Path(__file__).resolve().parents[1] / "build"
    build.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=build, prefix="asm-index-") as directory:
        root = Path(directory)
        rom = root / "synthetic.nes"
        asm = root / "synthetic.asm"
        output = root / "symbols.txt"
        image = bytearray(16 + 32768 + 8192)
        image[0:4] = b"NES\x1a"
        image[4] = 2
        image[5] = 1
        image[16:22] = bytes((0x78, 0x10, 0xFE, 0x00, 0x00, 0x60))
        rom.write_bytes(image)
        asm.write_text(
            ".org $8000\n"
            "Start: sei\n"
            "Loop: bpl Loop\n"
            ".db $00\n"
            "+ $00\n"
            "AfterData: rts\n",
            encoding="ascii",
        )
        labels, unknown, mismatch = indexer.generate(rom, asm, output)
        addresses = {name: address for name, address, _ in labels}
        if mismatch or unknown or addresses != {"Start": 0x8000, "Loop": 0x8001, "AfterData": 0x8005}:
            return 1
        if "8001 Loop" not in output.read_text(encoding="ascii"):
            return 1
        # Data sharing its label's line must advance PC before aliases and
        # subsequent instructions, just as standalone directives do.
        image[16:26] = bytes((1, 2, 3, 4, 5, 6, 7, 8, 9, 0x60))
        rom.write_bytes(image)
        asm.write_text(
            ".org $8000\n"
            "First: .byte $01,$02\n"
            "Alias:\n"
            "Second: .db $03\n"
            "Words: .word $0504\n"
            "More: .dw $0706\n"
            "Hex: .hex 0809\n"
            "End: rts\n", encoding="ascii")
        labels, unknown, mismatch = indexer.generate(rom, asm, output)
        addresses = {name: address for name, address, _ in labels}
        if mismatch or unknown or addresses != {
            "First": 0x8000, "Alias": 0x8002, "Second": 0x8002,
            "Words": 0x8003, "More": 0x8005, "Hex": 0x8007,
            "End": 0x8009,
        }:
            return 2
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
