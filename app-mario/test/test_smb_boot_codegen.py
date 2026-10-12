import importlib.util
import sys
from pathlib import Path
from writable_tempdir import writable_temporary_directory


def load_module():
    tool_dir = Path(__file__).parents[1] / "tools"
    if str(tool_dir) not in sys.path:
        sys.path.insert(0, str(tool_dir))
    script = tool_dir / "smb_boot_codegen.py"
    spec = importlib.util.spec_from_file_location("smb_boot_codegen", script)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    codegen = load_module()
    with writable_temporary_directory() as directory:
        root = Path(directory)
        rom = root / "synthetic.nes"
        output = root / "static"
        image = bytearray(16 + 32768 + 8192)
        image[0:4] = b"NES\x1a"
        image[4] = 2
        image[5] = 1
        image[16:21] = bytes((0x78, 0xD8, 0x4C, 0x02, 0x80))
        image[16 + 0x7FFC] = 0x00
        image[16 + 0x7FFD] = 0x80
        rom.write_bytes(image)
        codegen.generate(rom, output)
        source = (output / "smb1_static_boot.c").read_text(encoding="ascii")
        header = (output / "smb1_static_boot.h").read_text(encoding="ascii")
        if "state->interrupt_mask = 1U;" not in source:
            return 1
        if "state->decimal_mode = 0U;" not in source:
            return 1
        if "mysmb_static_u8 negative;" not in header:
            return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
