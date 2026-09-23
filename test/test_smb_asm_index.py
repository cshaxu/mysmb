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
    with tempfile.TemporaryDirectory() as directory:
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
            ".db $00, $00\n"
            "AfterData: rts\n",
            encoding="ascii",
        )
        labels, unknown, mismatch = indexer.generate(rom, asm, output)
        addresses = {name: address for name, address, _ in labels}
        if mismatch or unknown or addresses != {"Start": 0x8000, "Loop": 0x8001, "AfterData": 0x8005}:
            return 1
        if "8001 Loop" not in output.read_text(encoding="ascii"):
            return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
