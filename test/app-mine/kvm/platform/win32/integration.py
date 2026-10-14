"""Actual Mine product on an isolated desktop; no global input injection."""
import argparse
import ctypes as c
from ctypes import wintypes as w
import importlib.util
import json
import struct
import sys
from pathlib import Path
import time

ROOT = Path(__file__).resolve().parents[5]
sys.dont_write_bytecode = True
spec = importlib.util.spec_from_file_location("host", ROOT / "tools/Verify-Win32StartupConsole.py")
host = importlib.util.module_from_spec(spec)
spec.loader.exec_module(host)
u, k = host.u, host.k
g = c.WinDLL("gdi32", use_last_error=True)
u.IsWindowVisible.argtypes = [w.HWND]
u.GetClientRect.argtypes = [w.HWND, c.POINTER(w.RECT)]
u.GetDC.argtypes = [w.HWND]
u.GetDC.restype = w.HDC
u.PrintWindow.argtypes = [w.HWND, w.HDC, w.UINT]
u.SetThreadDesktop.argtypes = [w.HANDLE]
u.GetThreadDesktop.argtypes = [w.DWORD]
u.GetThreadDesktop.restype = w.HANDLE
u.ReleaseDC.argtypes = [w.HWND, w.HDC]
g.CreateCompatibleDC.argtypes = [w.HDC]
g.CreateCompatibleDC.restype = w.HDC
g.CreateCompatibleBitmap.argtypes = [w.HDC, c.c_int, c.c_int]
g.CreateCompatibleBitmap.restype = w.HANDLE
g.SelectObject.argtypes = [w.HDC, w.HANDLE]
g.SelectObject.restype = w.HANDLE
g.DeleteObject.argtypes = [w.HANDLE]
g.DeleteDC.argtypes = [w.HDC]
g.GetDIBits.argtypes = [w.HDC, w.HANDLE, w.UINT, w.UINT, c.c_void_p, c.c_void_p, w.UINT]
k.AttachConsole.argtypes = [w.DWORD]
k.CreateFileW.argtypes = [w.LPCWSTR, w.DWORD, w.DWORD, c.c_void_p, w.DWORD, w.DWORD, w.HANDLE]
k.CreateFileW.restype = w.HANDLE


class Coord(c.Structure):
    _fields_ = [("x", w.SHORT), ("y", w.SHORT)]


class ConsoleInfo(c.Structure):
    _fields_ = [("size", Coord), ("cursor", Coord), ("attributes", w.WORD),
                ("left", w.SHORT), ("top", w.SHORT), ("right", w.SHORT),
                ("bottom", w.SHORT), ("maximum", Coord)]


class Key(c.Structure):
    _fields_ = [("down", w.BOOL), ("repeat", w.WORD), ("vk", w.WORD),
                ("scan", w.WORD), ("char", w.WCHAR), ("state", w.DWORD)]


class Record(c.Structure):
    _fields_ = [("kind", w.WORD), ("key", Key)]


class Header(c.Structure):
    _fields_ = [("size", w.DWORD), ("width", w.LONG), ("height", w.LONG),
                ("planes", w.WORD), ("bits", w.WORD), ("compression", w.DWORD),
                ("bytes", w.DWORD), ("xppm", w.LONG), ("yppm", w.LONG),
                ("colors", w.DWORD), ("important", w.DWORD)]


k.WriteConsoleInputW.argtypes = [w.HANDLE, c.POINTER(Record), w.DWORD, c.POINTER(w.DWORD)]
k.ReadConsoleOutputCharacterW.argtypes = [w.HANDLE, w.LPWSTR, w.DWORD, Coord, c.POINTER(w.DWORD)]
k.GetConsoleScreenBufferInfo.argtypes = [w.HANDLE, c.POINTER(ConsoleInfo)]


def until(fn, label, seconds=10):
    end = time.monotonic() + seconds
    while time.monotonic() < end:
        result = fn()
        if result:
            return result
        time.sleep(.025)
    raise RuntimeError(label)


def capture(hwnd, path):
    rect = w.RECT()
    host.require(u.GetClientRect(hwnd, c.byref(rect)), "Get client")
    width, height = rect.right, rect.bottom
    dc = u.GetDC(hwnd)
    memory = g.CreateCompatibleDC(dc)
    bitmap = g.CreateCompatibleBitmap(dc, width, height)
    old = g.SelectObject(memory, bitmap)
    try:
        host.require(u.PrintWindow(hwnd, memory, 1), "Print client")
        header = Header(40, width, -height, 1, 32, 0, width*height*4, 0, 0, 0, 0)
        data = c.create_string_buffer(width*height*4)
        host.require(g.GetDIBits(memory, bitmap, 0, height, data, c.byref(header), 0), "Capture pixels")
        path.with_suffix(".bmp").write_bytes(struct.pack("<2sIHHI", b"BM", 54+len(data.raw), 0, 0, 54)+bytes(header)+data.raw)
        host.require(len(set(struct.iter_unpack("<I", data.raw))) >= 5, "Nonblank indexed art")
        return data.raw
    finally:
        g.SelectObject(memory, old)
        g.DeleteObject(bitmap)
        g.DeleteDC(memory)
        u.ReleaseDC(hwnd, dc)


def console_key(handle, vk, down):
    record, written = Record(), w.DWORD()
    record.kind = 1
    record.key.down, record.key.repeat, record.key.vk = down, 1, vk
    record.key.char = chr(vk) if vk < 128 else "\0"
    host.require(k.WriteConsoleInputW(handle, c.byref(record), 1, c.byref(written)), "Console key")


def start(command, desktop_name, output, flags):
    info, process = host.Startup(), host.Process()
    info.cb = c.sizeof(info)
    info.desktop = "WinSta0\\" + desktop_name
    # A hidden startup hint would override the app's first ShowWindow call.
    # Visibility on this isolated desktop never exposes a user-facing window.
    info.flags, info.show = 1, 1
    host.require(k.CreateProcessW(None, c.create_unicode_buffer(command), None, None,
                                 False, flags, None, str(output), c.byref(info), c.byref(process)), "Start Mine")
    k.CloseHandle(process.thread)
    return process.handle


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--product", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    name = "MineAcceptance%d" % int(time.time()*1000)
    desktop = u.CreateDesktopW(name, None, None, 0, 0x1ff, None)
    host.require(desktop, "Create private desktop")
    original_desktop = u.GetThreadDesktop(k.GetCurrentThreadId())
    host.require(u.SetThreadDesktop(desktop), "Bind test thread to its private desktop")
    u.SetProcessDPIAware()
    receipts = []
    try:
        for route in ("detached", "owned", "borrowed"):
            borrowed = route == "borrowed"
            k.FreeConsole()  # This test launcher is the graphical parent route.
            command = '"%s"' % args.product.resolve()
            if borrowed:
                command = 'cmd.exe /d /c "' + command + '"'
            handle = start(command, name, output, 0x10 if borrowed else 8 if route == "detached" else 0)
            child = None
            try:
                root = until(lambda: next((x for x in host.windows(desktop) if x[2] == "MyGamesMine"), None), "Mine root")
                hwnd, pid = root[0], root[1]
                child = k.OpenProcess(0x101001, False, pid)
                if borrowed:
                    until(lambda: not u.IsWindowVisible(hwnd), "Borrowed console initial view")
                else:
                    until(lambda: u.IsWindowVisible(hwnd), "Graphical launch")
                    time.sleep(.3)
                    before = capture(hwnd, output/"window.png")
                    # Left release on the first board cell, scaled to the client.
                    rect = w.RECT();u.GetClientRect(hwnd, c.byref(rect))
                    x, y = 20*rect.right//168, 64*rect.bottom//220
                    u.PostMessageW(hwnd, 0x201, 1, x|(y<<16))
                    u.PostMessageW(hwnd, 0x202, 0, x|(y<<16))
                    time.sleep(.25)
                    host.require(capture(hwnd, output/"revealed.png") != before, "Graphical reveal changes board")
                    u.PostMessageW(hwnd, 0x100, 9, 0)
                    until(lambda: not u.IsWindowVisible(hwnd), "Tab to text")
                k.FreeConsole()
                until(lambda: k.AttachConsole(pid), "Attach only test child console")
                console_input = k.CreateFileW("CONIN$", 0xc0000000, 3, None, 3, 0, None)
                console_output = k.CreateFileW("CONOUT$", 0xc0000000, 3, None, 3, 0, None)
                try:
                    console_key(console_input, 9, False)
                    def contents():
                        # Borrowed startup changes the active screen buffer;
                        # opening before that point must not pin the parent's buffer.
                        active = k.CreateFileW("CONOUT$", 0xc0000000, 3, None, 3, 0, None)
                        info = ConsoleInfo()
                        if not k.GetConsoleScreenBufferInfo(active, c.byref(info)):
                            k.CloseHandle(active)
                            return ""
                        lines=[]
                        for row in range(min(25,info.size.y-info.top)):
                            data, read = c.create_unicode_buffer(81), w.DWORD()
                            if k.ReadConsoleOutputCharacterW(active, data, min(80,info.size.x-info.left),
                                                             Coord(info.left, info.top+row), c.byref(read)):
                                lines.append(data.value)
                        k.CloseHandle(active)
                        result="\n".join(lines)
                        (output/"console-last.txt").write_text(repr((info.size.x,info.size.y,info.top,info.bottom))+"\n"+result,encoding="utf-8")
                        return result
                    def board_visible():
                        text=contents()
                        # A small RDP monitor can clip the centered title.
                        # The menu, counter and face remain visible together.
                        return "MINE" in text or ("Game" in text and
                            "Help" in text and "010" in text and "[\u263a]" in text)
                    def expert_visible():
                        text=contents()
                        # Expert changes the mine counter from010to099 even
                        # when its right-hand dimensions caption is clipped.
                        return "30x16" in text or "099" in text
                    until(board_visible, "Mine text content")
                    console_key(console_input, ord('3'), True);console_key(console_input, ord('3'), False)
                    until(expert_visible, "Console level key")
                    (output/("borrowed.txt" if borrowed else "owned.txt")).write_text(contents(), encoding="utf-8")
                    console_key(console_input, 9, True);console_key(console_input, 9, False)
                    until(lambda: u.IsWindowVisible(hwnd), "Console to graphics")
                    time.sleep(.2)
                    capture(hwnd, output/("borrowed-return.png" if borrowed else "owned-return.png"))
                    # Switch back into the same retained attachment.
                    u.PostMessageW(hwnd, 0x100, 9, 0)
                    until(lambda: not u.IsWindowVisible(hwnd), "Graphics to retained console")
                    console_key(console_input, 9, False)
                    until(expert_visible, "Retained board")
                    console_key(console_input, ord('Q'), True);console_key(console_input, ord('Q'), False)
                finally:
                    k.CloseHandle(console_input);k.CloseHandle(console_output);k.FreeConsole()
                host.completed(child);host.completed(handle)
                receipts.append(dict(route=route, launch=True,
                                     text=True, level=True, retainedTab=True, exitCode=0))
            finally:
                for process in (child, handle):
                    if process:
                        if k.WaitForSingleObject(process, 0) != 0:k.TerminateProcess(process, 99)
                        k.CloseHandle(process)
        (output/"result.json").write_text(json.dumps(receipts, indent=2)+"\n")
        print(json.dumps(receipts))
    finally:
        u.SetThreadDesktop(original_desktop)
        u.CloseDesktop(desktop)


if __name__ == "__main__":
    main()
