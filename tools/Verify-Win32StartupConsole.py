"""Run bounded host checks on an isolated desktop; never activate user windows."""
import argparse
import ctypes as c
from ctypes import wintypes as w
import json
from pathlib import Path
import shutil
import time

u = c.WinDLL("user32", use_last_error=True)
k = c.WinDLL("kernel32", use_last_error=True)


class Startup(c.Structure):
    _fields_ = [("cb", w.DWORD), ("reserved", w.LPWSTR),
                ("desktop", w.LPWSTR), ("title", w.LPWSTR),
                ("x", w.DWORD), ("y", w.DWORD), ("width", w.DWORD),
                ("height", w.DWORD), ("chars_x", w.DWORD),
                ("chars_y", w.DWORD), ("fill", w.DWORD),
                ("flags", w.DWORD), ("show", w.WORD),
                ("reserved_size", w.WORD), ("reserved_bytes", c.c_void_p),
                ("stdin", w.HANDLE), ("stdout", w.HANDLE), ("stderr", w.HANDLE)]


class Process(c.Structure):
    _fields_ = [("handle", w.HANDLE), ("thread", w.HANDLE),
                ("pid", w.DWORD), ("tid", w.DWORD)]


callback = c.WINFUNCTYPE(w.BOOL, w.HWND, w.LPARAM)
u.CreateDesktopW.argtypes = [w.LPCWSTR, w.LPCWSTR, c.c_void_p,
                            w.DWORD, w.DWORD, c.c_void_p]
u.CreateDesktopW.restype = w.HANDLE
u.EnumDesktopWindows.argtypes = [w.HANDLE, callback, w.LPARAM]
u.GetWindowTextW.argtypes = [w.HWND, w.LPWSTR, c.c_int]
u.GetClassNameW.argtypes = [w.HWND, w.LPWSTR, c.c_int]
u.GetWindowThreadProcessId.argtypes = [w.HWND, c.POINTER(w.DWORD)]
u.GetSystemMenu.argtypes = [w.HWND, w.BOOL]
u.GetSystemMenu.restype = w.HANDLE
u.GetMenuState.argtypes = [w.HANDLE, w.UINT, w.UINT]
u.PostMessageW.argtypes = [w.HWND, w.UINT, w.WPARAM, w.LPARAM]
u.SendMessageTimeoutW.argtypes = [w.HWND,w.UINT,w.WPARAM,w.LPARAM,
                                w.UINT,w.UINT,c.POINTER(c.c_size_t)]
u.SendMessageTimeoutW.restype = c.c_size_t
u.CloseDesktop.argtypes = [w.HANDLE]
k.CreateProcessW.argtypes = [w.LPCWSTR, w.LPWSTR, c.c_void_p, c.c_void_p,
                            w.BOOL, w.DWORD, c.c_void_p, w.LPCWSTR,
                            c.POINTER(Startup), c.POINTER(Process)]
k.OpenProcess.argtypes = [w.DWORD, w.BOOL, w.DWORD]
k.OpenProcess.restype = w.HANDLE
k.WaitForSingleObject.argtypes = [w.HANDLE, w.DWORD]
k.GetExitCodeProcess.argtypes = [w.HANDLE, c.POINTER(w.DWORD)]
k.TerminateProcess.argtypes = [w.HANDLE, w.UINT]
k.CloseHandle.argtypes = [w.HANDLE]


def require(condition, message):
    if not condition:
        raise RuntimeError(message + " (Windows error %d)" % c.get_last_error())


def windows(desktop):
    found = []

    @callback
    def visit(hwnd, unused):
        title, kind, pid = c.create_unicode_buffer(256), c.create_unicode_buffer(80), w.DWORD()
        u.GetWindowTextW(hwnd, title, 256)
        u.GetClassNameW(hwnd, kind, 80)
        u.GetWindowThreadProcessId(hwnd, c.byref(pid))
        found.append((hwnd, pid.value, kind.value, title.value))
        return True

    c.set_last_error(0)
    result = u.EnumDesktopWindows(desktop, visit, 0)
    # A newly created desktop can have no windows yet (FALSE,last-error zero).
    require(result or c.get_last_error() == 0, "Enumerate owned desktop")
    return found


def start(command, desktop_name, directory, flags=0x10):
    info, process = Startup(), Process()
    info.cb = c.sizeof(info)
    info.desktop = "WinSta0\\" + desktop_name
    info.flags, info.show = 1, 0
    require(k.CreateProcessW(None, c.create_unicode_buffer(command), None, None,
                            False, flags, None, str(directory),
                            c.byref(info), c.byref(process)), "Create owned child")
    k.CloseHandle(process.thread)
    return process.handle


def completed(handle):
    require(k.WaitForSingleObject(handle, 8000) == 0, "Owned child did not exit")
    code = w.DWORD()
    require(k.GetExitCodeProcess(handle, c.byref(code)), "Read exit code")
    require(code.value == 0, "Child exit code %d" % code.value)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--product", type=Path, required=True)
    parser.add_argument("--policy", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--switch", type=Path)
    args = parser.parse_args()
    output = args.output.resolve()
    require("build" in output.parts, "Evidence must remain below build")
    output.mkdir(parents=True, exist_ok=True)
    name = "mysmb-startup-%d" % k.GetCurrentProcessId()
    desktop = u.CreateDesktopW(name, None, None, 0, 0x1ff, None)
    require(desktop, "Create isolated desktop")
    handles, rows = [], []
    try:
        policy, product = args.policy.resolve(), args.product.resolve()
        if args.switch:
            handle = start('"%s" %s' % (args.switch.resolve(), output.as_posix()),
                           name, output)
            handles.append(handle)
            completed(handle)
            rows.append(dict(route="Tab/snapshot/focus/audio/Unicode/recovery", exitCode=0))
        sources = ["other", "other-console", "cmd-detached", "cmd", "powershell"]
        if shutil.which("pwsh.exe"):
            sources.append("pwsh")
        for source in sources:
            print("Checking launch/close route: " + source, flush=True)
            text = source in ("cmd", "powershell", "pwsh")
            flags = 8 if source == "cmd-detached" else 0 if source == "other" else 0x10

            def command(exe, suffix=""):
                invocation = '"%s" %s' % (exe, suffix)
                if source.startswith("cmd"):
                    return 'cmd.exe /d /c start "" /wait ' + invocation
                if source in ("powershell", "pwsh"):
                    return ('%s.exe -NoProfile -Command "& \'%s\' %s; exit $LASTEXITCODE"'
                            % (source, exe, suffix))
                return invocation

            # An arbitrary console-bearing parent must not imply text mode.
            handle = start(command(policy, "text" if text else "graphics"), name, output, flags)
            handles.append(handle)
            completed(handle)
            launch = command(product)
            if source in ("powershell", "pwsh"):
                launch = ('%s.exe -NoProfile -Command "Start-Process -FilePath \'%s\' '
                          '-Wait; exit 0"' % (source, product))
            handle = start(launch, name, output, flags)
            handles.append(handle)
            deadline, root, console = time.monotonic() + 8, None, None
            while time.monotonic() < deadline:
                visible = windows(desktop)
                root = next((x for x in visible if x[2] == "MySMBWindow"), None)
                console = next((x for x in visible if x[2] == "ConsoleWindowClass"
                                and x[3] == "MySMB"), None)
                if root and (not text or console):
                    break
                time.sleep(0.02)
            require(root, "Product root missing for " + source)
            require(bool(console) == text, "Wrong presenter for " + source)
            # Window creation precedes device startup. Wait for its message
            # owner rather than treating HWND visibility as application ready.
            deadline, result = time.monotonic() + 8, c.c_size_t()
            while time.monotonic() < deadline:
                if u.SendMessageTimeoutW(root[0],0,0,0,3,250,c.byref(result)):
                    break
            else:
                raise RuntimeError("Root message owner unresponsive: " + source)
            child = k.OpenProcess(0x101001, False, root[1])
            require(child, "Open exact product child")
            handles.append(child)
            if console:
                state = u.GetMenuState(u.GetSystemMenu(console[0], False), 0xf060, 0)
                require(state != 0xffffffff and not state & 3, "Console close disabled")
                require(u.PostMessageW(console[0], 0x112, 0xf060, 0), "Close owned console")
            else:
                require(u.PostMessageW(root[0], 0x10, 0, 0), "Close owned GUI")
            completed(child)
            completed(handle)
            rows.append(dict(source=source, presenter="text" if console else "graphics",
                             close="console" if console else "GUI", exitCode=0))
        (output / "startup-close.json").write_text(json.dumps(rows, indent=2) + "\n")
        print(json.dumps(rows))
    finally:
        # Preserve completed routes on failure;never infer the missing ones.
        (output / "startup-close-progress.json").write_text(
            json.dumps(dict(completedRoutes=rows), indent=2) + "\n")
        for window in windows(desktop):
            if window[2] == "MySMBWindow":
                handle = k.OpenProcess(0x101001, False, window[1])
                if handle:
                    handles.append(handle)
        # Only handles created/opened for this isolated probe are touched.
        for handle in handles:
            if k.WaitForSingleObject(handle, 0) == 0x102:
                k.TerminateProcess(handle, 99)
                k.WaitForSingleObject(handle, 2000)
            k.CloseHandle(handle)
        u.CloseDesktop(desktop)


if __name__ == "__main__":
    main()
