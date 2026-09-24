import importlib.util
import sys
import tempfile
from pathlib import Path


def main():
    tool_dir = Path(__file__).parents[1] / "tools"
    sys.path.insert(0, str(tool_dir))
    spec = importlib.util.spec_from_file_location("smb_title_codegen", tool_dir / "smb_title_codegen.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    with tempfile.TemporaryDirectory() as directory:
        root = Path(directory)
        rom = root / "synthetic.nes"
        output = root / "title"
        image = bytearray(16 + 32768 + 8192)
        image[0:4] = b"NES\x1a"
        image[4] = 2
        image[5] = 1
        for index in range(module.TITLE_DATA_SIZE):
            image[16 + 32768 + module.TITLE_CHR_OFFSET + index] = index & 0xff
        for index in range(module.TITLE_ICON_DATA_SIZE):
            image[16 + module.TITLE_ICON_PRG_OFFSET + 1 + index] = (0xa0 + index) & 0xff
        rom.write_bytes(image)
        module.generate(rom, output)
        source = (output / "smb1_local_title.c").read_text(encoding="ascii")
        if ("mysmb_local_title_data[314]" not in source or
                "mysmb_local_title_icon_data[7]" not in source or
                "0xA0" not in source or "0x39" not in source):
            return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
