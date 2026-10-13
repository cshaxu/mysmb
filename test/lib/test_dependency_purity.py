"""Shared-owner dependency gate; no app or ROM required."""
from pathlib import Path
import re
import sys
repository = Path(__file__).resolve().parents[2]
for family in ("kvm", "dos16", "win16", "win32"):
    owner = repository / "src" / "lib" / family
    if not owner.is_dir() or not any(owner.glob("*.[ch]")):
        raise SystemExit("Missing library owner: " + family)
    cmake = (owner / "CMakeLists.txt").read_text()
    if any(token in cmake for token in ("src/app-", "test/app-", "mysmb_core", "mysmb_game", "MYSMB_ROM")):
        raise SystemExit("Library build depends on application: " + family)
kvm = repository / "src" / "lib" / "kvm"
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
win32 = repository / "src" / "lib" / "win32"
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
dos16 = repository / "src" / "lib" / "dos16"
for path in dos16.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)', text, re.M):
        if not include.startswith(("dos16/", "kvm/")) and include not in ("string.h", "dos.h", "conio.h", "stdio.h", "errno.h", "stdlib.h"):
            print(f"{path.relative_to(repository)}: DOS16 host imports {include}")
            sys.exit(1)
    for token in ("MYSMB_", "mysmb_", "struct mysmb_game", "core/", "ppu/"):
        if token in text:
            print(f"{path.relative_to(repository)}: DOS16 host leaks {token}")
            sys.exit(1)
win16 = repository / "src" / "lib" / "win16"
for path in win16.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    for include in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)', text, re.M):
        if not include.startswith(("win16/", "kvm/")) and include not in ("windows.h", "mmsystem.h", "string.h", "stdio.h", "errno.h"):
            print(f"{path.relative_to(repository)}: Win16 host imports {include}")
            sys.exit(1)
    for token in ("MYSMB_", "mysmb_", "core/", "ppu/", "app-mario/", "app-mine/"):
        if token in text:
            print(f"{path.relative_to(repository)}: Win16 contract leaks {token}")
            sys.exit(1)
print("KVM/DOS16/Win16/Win32 dependency purity: passed")
