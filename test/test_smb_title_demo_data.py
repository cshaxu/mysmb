"""Verify the two title-demo tables against the admitted local ROM listing."""

from pathlib import Path
import re


def asm_bytes(source, label):
    match = re.search(r"^" + label + r":\s*\n((?:\s*\.byte[^\n]*\n)+)",
                      source, re.MULTILINE)
    if match is None:
        raise AssertionError(label + " is absent")
    return bytes(int(value, 16) for value in re.findall(r"\$([0-9a-fA-F]{2})",
                                                         match.group(1)))


def c_bytes(source, name):
    match = re.search(r"static const mysmb_u8 " + name + r"\[\d+\]\s*=\s*\{(.*?)\};",
                      source, re.DOTALL)
    if match is None:
        raise AssertionError(name + " is absent")
    return bytes(int(value, 16) for value in re.findall(r"0x([0-9a-fA-F]{2})U",
                                                         match.group(1)))


def main():
    asm = Path("build/reference-source/SMBDIS.ASM").read_text(encoding="utf-8")
    native = Path("src/core/title_modes.c").read_text(encoding="utf-8")
    assert asm_bytes(asm, "DemoActionData") == c_bytes(native, "action_data")
    assert asm_bytes(asm, "DemoTimingData") == c_bytes(native, "timing_data")
    assert "if (game->ram[MYSMB_RAM_DEMO_ACTION_TIMER] == 0U)" in native
    assert "game->ram[MYSMB_RAM_SAVED_JOYPAD1] = action_data[action - 1U];" in native
    assert "game->ram[MYSMB_RAM_DEMO_ACTION_TIMER]--;" in native


if __name__ == "__main__":
    main()
