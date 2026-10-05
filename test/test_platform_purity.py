"""Architecture gate: platform code may adapt host I/O only, never inspect game state."""
from pathlib import Path
import re
import sys

root = Path(__file__).resolve().parents[1]
platform = root / "src" / "platform"
for path in platform.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    if path.parent.name == "vga" or path.name in ("keyboard.c", "keyboard.h", "devices.c", "devices.h"):
        if "struct mysmb_game" in text or '"game/' in text or '"core/' in text:
            print(f"{path.relative_to(root)}: device adapter imports whole game")
            sys.exit(1)
    if path.name in ("audio_renderer.c", "audio_renderer.h", "audio_output.c", "audio_output.h"):
        if "struct mysmb_game" in text or '"game/' in text or '"core/' in text:
            print(f"{path.relative_to(root)}: audio adapter imports whole game")
            sys.exit(1)
    forbidden = (
        "->ram[", ".ram[", "->name_table", "->palette", "->visible_oam",
        "->visible_scroll", "->visible_ppu_", "->ppu_control_", "->scroll_",
        "mysmb_game_begin_title_bootstrap",
    )
    ppu_fields=("name_table", "palette", "visible_oam", "visible_scroll_x",
        "visible_scroll_y", "visible_ppu_control_0", "visible_ppu_mask",
        "visible_ppu_name_table", "visible_sprite0_split", "ppu_control_0",
        "ppu_mask", "ppu_name_table", "scroll_x", "scroll_y")
    forbidden += tuple(prefix+field for prefix in ("->ppu.", ".ppu.")
        for field in ppu_fields)
    for token in forbidden:
        if token in text:
            print(f"{path.relative_to(root)}: forbidden game-state access {token}")
            sys.exit(1)
for path in (root / "src" / "io").rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)', text, re.M):
        if not include.startswith("io/") and include != "string.h":
            print(f"{path.relative_to(root)}: IO contract imports {include}")
            sys.exit(1)
    for token in ("struct mysmb_game", "HWND", "int86(", "waveOut", "->ram["):
        if token in text:
            print(f"{path.relative_to(root)}: IO contract leaks {token}")
            sys.exit(1)
for path in (root / "src" / "ppu").rglob("*.[ch]"):
    text=path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)',text,re.M):
        if not include.startswith(("ppu/", "io/")) and include != "string.h":
            print(f"{path.relative_to(root)}: PPU imports {include}")
            sys.exit(1)
    for token in ("struct mysmb_game", "->ram[", "HWND", "int86(", "waveOut"):
        if token in text:
            print(f"{path.relative_to(root)}: PPU leaks {token}")
            sys.exit(1)
print("platform, IO and PPU purity: passed")
