from pathlib import Path
import sys
_REPOSITORY = next(p for p in Path(__file__).resolve().parents if (p / "docs/README.md").is_file() and (p / "CMakeLists.txt").is_file())
sys.path.insert(0, str(_REPOSITORY / "test/app-mario/kvm/io"))
import importlib.util
from pathlib import Path
from writable_tempdir import writable_temporary_directory


def load_generator():
    script = _REPOSITORY / "tools" / "smb_rom_codegen.py"
    spec = importlib.util.spec_from_file_location("smb_rom_codegen", script)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    module = load_generator()
    with writable_temporary_directory() as directory:
        root = Path(directory)
        rom = root / "synthetic.nes"
        image = bytearray(16 + 32768 + 8192)
        image[0:4] = b"NES\x1a"
        image[4] = 2
        image[5] = 1
        rom.write_bytes(image)
        output = root / "generated"
        module.generate(rom, output)
        if "mysmb_local_prg" not in (output / "smb1_local_rom.c").read_text():
            return 1
        if "cpu:8000-FFFF" not in (output / "smb1_local_map.txt").read_text():
            return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
