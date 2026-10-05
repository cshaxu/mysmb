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
    parser.add_argument("--parent", type=Path)
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
        if args.parent:
            handle=start('cmd.exe /d /c ""%s" "%s""' % (args.parent.resolve(),output / 'parent-diagnostic.txt'),name,output)
            handles.append(handle);completed(handle)
            rows.append(dict(route="borrowed-buffer/settings/Tab/error-restore",exitCode=0))
            handle=start('cmd.exe /d /c ""%s" "%s" maximized"' % (args.parent.resolve(),output / 'parent-max-diagnostic.txt'),name,output)
            handles.append(handle);completed(handle)
            rows.append(dict(route="maximized-parent/settings/error-restore",exitCode=0))
            for variant in ("borrowed-null","borrowed-foreign"):
                fixture_output=output/variant;fixture_output.mkdir(exist_ok=True)
                marker=fixture_output/"root-result.txt";marker.unlink(missing_ok=True)
                handle=start('cmd.exe /d /c start "" /wait /b "%s" borrowed "%s"' %
                             (args.switch.resolve(),fixture_output),name,fixture_output)
                handles.append(handle);completed(handle)
                require(marker.exists() and marker.read_text().strip()=="0",
                        "Actual borrowed fixture result: "+(marker.read_text().strip() if marker.exists() else "missing"))
                rows.append(dict(route=variant+"/event-input/Tab/one-instance",exitCode=0))
        if args.switch:
            for variant in ("owned-null","owned-foreign"):
                fixture_output=output/variant;fixture_output.mkdir(exist_ok=True)
                marker=fixture_output/"root-result.txt";marker.unlink(missing_ok=True)
                handle=start('"%s" "%s"' % (args.switch.resolve(),fixture_output),name,fixture_output)
                handles.append(handle);completed(handle)
                require(marker.exists() and marker.read_text().strip()=="0","Owned root fixture result missing")
                rows.append(dict(route=variant+"/input/snapshot/focus/Unicode/recovery",exitCode=0))
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
            require(bool(console) == text, "Wrong presenter for " + source+": "+repr(windows(desktop)))
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
            if console and not args.parent:
                state = u.GetMenuState(u.GetSystemMenu(console[0], False), 0xf060, 0)
                require(state != 0xffffffff and not state & 3, "Console close disabled")
                require(u.PostMessageW(console[0], 0x112, 0xf060, 0), "Close owned console")
            else:
                require(u.PostMessageW(root[0], 0x10, 0, 0), "Close owned GUI")
            completed(child)
            completed(handle)
            rows.append(dict(source=source, presenter="text" if console else "graphics",
                             close="console" if console and not args.parent else "root", exitCode=0))
        # Actual interactive CMD has different GUI wait semantics than /c.
        # Deliver records only into this isolated console,never global input.
        handle=start('cmd.exe /d /q /k',name,output);handles.append(handle)
        k.GetProcessId.argtypes=[w.HANDLE];k.GetProcessId.restype=w.DWORD
        k.AttachConsole.argtypes=[w.DWORD]
        k.CreateFileW.argtypes=[w.LPCWSTR,w.DWORD,w.DWORD,c.c_void_p,w.DWORD,w.DWORD,w.HANDLE]
        k.CreateFileW.restype=w.HANDLE
        class Key(c.Structure):
            _fields_=[("down",w.BOOL),("repeat",w.WORD),("vk",w.WORD),
                      ("scan",w.WORD),("char",w.WCHAR),("state",w.DWORD)]
        class Record(c.Structure):
            _fields_=[("kind",w.WORD),("key",Key)]
        k.WriteConsoleInputW.argtypes=[w.HANDLE,c.POINTER(Record),w.DWORD,c.POINTER(w.DWORD)]
        u.IsWindowVisible.argtypes=[w.HWND]
        u.IsWindowVisible.restype=w.BOOL
        # Detach this probe's inherited console only;its stdout remains a pipe.
        k.FreeConsole()
        deadline=time.monotonic()+4
        while not k.AttachConsole(k.GetProcessId(handle)):
            require(time.monotonic()<deadline,"Attach isolated interactive CMD")
            time.sleep(.02)
        console_input=k.CreateFileW("CONIN$",0xc0000000,3,None,3,0,None)
        try:
            deadline=time.monotonic()+5
            console=None
            while time.monotonic()<deadline:
                console=next((x for x in windows(desktop) if x[2]=="ConsoleWindowClass"),None)
                if console:break
                time.sleep(.02)
            require(console,"Interactive console missing")
            console_hwnd=console[0]
            def send_line(line):
                for char in line+"\r":
                    for down in (True,False):
                        event=Record();event.kind=1;event.key=Key(down,1,13 if char=="\r" else 0,0,char,0)
                        written=w.DWORD()
                        require(k.WriteConsoleInputW(console_input,c.byref(event),1,c.byref(written)) and written.value==1,"Owned CMD input")
            def send_key(vk,down,scan=0):
                event=Record();event.kind=1;event.key=Key(down,1,vk,scan,"\0",0)
                written=w.DWORD()
                require(k.WriteConsoleInputW(console_input,c.byref(event),1,c.byref(written)) and written.value==1,"Owned console key record")
            returned=output/"cmd-returned.txt";usable=output/"cmd-usable.txt"
            returned.unlink(missing_ok=True);usable.unlink(missing_ok=True)
            send_line('"%s" & echo RETURNED>"%s"' % (product,returned))
            deadline=time.monotonic()+8;root=None
            while time.monotonic()<deadline:
                root=next((x for x in windows(desktop) if x[2]=="MySMBWindow"),None)
                active=next((x for x in windows(desktop) if x[0]==console_hwnd and x[3]=="MySMB"),None)
                if root and active:break
                time.sleep(.02)
            require(root and active,"Direct CMD must reuse its existing console")
            require(not returned.exists(),"Interactive CMD returned while game owns input")
            require(sum(x[2]=="ConsoleWindowClass" for x in windows(desktop))==1,"Extra console created")
            child=k.OpenProcess(0x101001,False,root[1]);require(child,"Open interactive game");handles.append(child)
            # Target only this private console input and this game's window.
            # Foreground belongs to the user's desktop;it cannot be a gate here.
            send_key(9,True,15)
            deadline=time.monotonic()+4
            while not u.IsWindowVisible(root[0]) and time.monotonic()<deadline:time.sleep(.02)
            require(u.IsWindowVisible(root[0]),"Delivered CONIN Tab must enter graphics")
            require(u.PostMessageW(root[0],0x1c,1,0),"Owned window activation")
            require(u.PostMessageW(root[0],0x7,0,0),"Owned window focus")
            require(u.PostMessageW(root[0],0x101,9,0),"Owned Tab release")
            require(u.PostMessageW(root[0],0x100,9,0),"Owned window Tab")
            deadline=time.monotonic()+4
            while u.IsWindowVisible(root[0]) and time.monotonic()<deadline:time.sleep(.02)
            require(not u.IsWindowVisible(root[0]),"Delivered window Tab must reenter text")
            time.sleep(.1)
            require(not returned.exists(),"Interactive CMD must keep waiting")
            send_key(9,False,15);send_key(27,True,1)
            completed(child)
            deadline=time.monotonic()+4
            while not returned.exists() and time.monotonic()<deadline:time.sleep(.02)
            require(returned.exists(),"Interactive shell must resume after game")
            send_line('echo USABLE>"%s"' % usable)
            deadline=time.monotonic()+4
            while not usable.exists() and time.monotonic()<deadline:time.sleep(.02)
            require(usable.exists(),"Restored CMD must accept input")
            send_line('exit');completed(handle)
            rows.append(dict(route="interactive-CMD/CONIN-Tab/window-Tab/CONIN-Escape/wait/prompt",exitCode=0))
        finally:
            k.CloseHandle(console_input);k.FreeConsole()
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
