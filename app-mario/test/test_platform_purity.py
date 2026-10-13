"""Architecture gate: platform code may adapt host I/O only, never inspect game state."""
from pathlib import Path
import re
import sys

root = Path(__file__).resolve().parents[1]
platform = root / "src" / "platform"
components = {p.name for p in platform.iterdir() if p.is_dir()}
if components != {"dos16", "win32", "win16"}:
    print(f"platform components must be dos16/win16/win32 only: {sorted(components)}")
    sys.exit(1)
for path in platform.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    host = path.relative_to(platform).parts[0]
    includes = re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)', text, re.M)
    if any(any(x.startswith(f"platform/{other}/") for other in components - {host}) or
           (host == "dos16" and x == "windows.h") or
           (host in ("win32", "win16") and x in ("dos.h", "conio.h")) for x in includes):
        print(f"{path.relative_to(root)}: imports the other host")
        sys.exit(1)
    if path.parent == platform:
        print(f"{path.relative_to(root)}: platform code outside a host component")
        sys.exit(1)
    if path.name in ("planar_row.c", "planar_row.h", "keyboard.c", "keyboard.h", "devices.c", "devices.h"):
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
        stdio_service = path.parent == root / "src" / "io" / "file" and include == "stdio.h"
        if not include.startswith(("io/", "kvm/")) and include != "string.h" and not stdio_service:
            print(f"{path.relative_to(root)}: IO contract imports {include}")
            sys.exit(1)
    for token in ("struct mysmb_game", "HWND", "int86(", "waveOut", "->ram[",
                  "_asm", "mysmb_dos16_", "mysmb_win32_"):
        if token in text:
            print(f"{path.relative_to(root)}: IO contract leaks {token}")
            sys.exit(1)
for path in (root / "src" / "ppu").rglob("*.[ch]"):
    text=path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)',text,re.M):
        if not include.startswith(("ppu/", "io/", "kvm/")) and include != "string.h":
            print(f"{path.relative_to(root)}: PPU imports {include}")
            sys.exit(1)
    for token in ("struct mysmb_game", "->ram[", "HWND", "int86(", "waveOut"):
        if token in text:
            print(f"{path.relative_to(root)}: PPU leaks {token}")
            sys.exit(1)
for path in (root / "src" / "core").rglob("*.[ch]"):
    text=path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)',text,re.M):
        if include.startswith(("text/", "game/presentation/", "platform/",
                "app/", "validate/")) or include == "ppu/frame.h":
            print(f"{path.relative_to(root)}: core imports downstream {include}")
            sys.exit(1)
repository = root.parent
kvm = repository / "lib" / "kvm"
for path in kvm.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)', text, re.M):
        if not include.startswith("kvm/"):
            print(f"{path.relative_to(repository)}: KVM imports {include}")
            sys.exit(1)
    for token in ("MYSMB_", "mysmb_", "HWND", "int86(", "waveOut", "struct mysmb_game"):
        if token in text:
            print(f"{path.relative_to(repository)}: KVM leaks {token}")
            sys.exit(1)
win32 = repository / "lib" / "win32"
allowed_win32_includes = ("win32/", "kvm/", "windows.h", "mmsystem.h",
                          "tlhelp32.h", "string.h", "stddef.h")
for path in win32.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)', text, re.M):
        if include not in allowed_win32_includes and not include.startswith(("win32/", "kvm/")):
            print(f"{path.relative_to(repository)}: Win32 host imports {include}")
            sys.exit(1)
    for token in ("MYSMB_", "mysmb_", "struct mysmb_game", "core/", "ppu/"):
        if token in text:
            print(f"{path.relative_to(repository)}: Win32 host leaks {token}")
            sys.exit(1)
dos16 = repository / "lib" / "dos16"
for path in dos16.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)', text, re.M):
        if not include.startswith(("dos16/", "kvm/")) and include not in ("string.h", "dos.h", "conio.h"):
            print(f"{path.relative_to(repository)}: DOS16 host imports {include}")
            sys.exit(1)
    for token in ("MYSMB_", "mysmb_", "struct mysmb_game", "core/", "ppu/"):
        if token in text:
            print(f"{path.relative_to(repository)}: DOS16 host leaks {token}")
            sys.exit(1)
win16 = repository / "lib" / "win16"
for path in win16.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)', text, re.M):
        if not include.startswith(("win16/", "kvm/")) and include not in ("windows.h", "string.h"):
            print(f"{path.relative_to(repository)}: Win16 host imports {include}")
            sys.exit(1)
    for token in ("MYSMB_", "mysmb_", "core/", "ppu/", "app-mario/", "app-mine/"):
        if token in text:
            print(f"{path.relative_to(repository)}: Win16 contract leaks {token}")
            sys.exit(1)
print("platform, IO, PPU, core, KVM and host dependency purity: passed")
