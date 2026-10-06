"""Bounded actual-product DPI/owned-console checks on an isolated desktop."""
import argparse
import ctypes as c
from ctypes import wintypes as w
import importlib
import sys
sys.dont_write_bytecode = True
import json
from pathlib import Path
import time

host = importlib.import_module("Verify-Win32StartupConsole")
u, k = host.u, host.k
u.SetProcessDpiAwarenessContext.argtypes = [w.HANDLE]
u.GetClientRect.argtypes = [w.HWND, c.POINTER(w.RECT)]
u.GetDpiForWindow.argtypes = [w.HWND]
u.GetDpiForWindow.restype = w.UINT
u.IsWindowVisible.argtypes = [w.HWND]
u.GetWindowLongW.argtypes = [w.HWND,c.c_int]
u.GetParent.argtypes = [w.HWND]
u.GetParent.restype = w.HWND
u.MonitorFromWindow.argtypes = [w.HWND,w.DWORD]
u.MonitorFromWindow.restype = w.HANDLE
k.AttachConsole.argtypes = [w.DWORD]
k.GetProcessId.argtypes = [w.HANDLE]
k.GetConsoleWindow.restype = w.HWND
k.CreateFileW.argtypes = [w.LPCWSTR,w.DWORD,w.DWORD,c.c_void_p,w.DWORD,w.DWORD,w.HANDLE]
k.CreateFileW.restype = w.HANDLE

class Monitor(c.Structure):
    _fields_ = [("size",w.DWORD),("screen",w.RECT),("work",w.RECT),("flags",w.DWORD)]

u.GetMonitorInfoW.argtypes = [w.HANDLE,c.POINTER(Monitor)]

def initial_units(hwnd,dpi):
    """Honor the DPI request within the documented 16:15 work-area limit."""
    monitor=Monitor();monitor.size=c.sizeof(monitor)
    host.require(u.GetMonitorInfoW(u.MonitorFromWindow(hwnd,2),c.byref(monitor)),"Window monitor")
    margins=w.RECT();style=u.GetWindowLongW(hwnd,-16)&0xffffffff
    ex=u.GetWindowLongW(hwnd,-20)&0xffffffff
    adjust=getattr(u,"AdjustWindowRectExForDpi",None)
    if adjust:
        adjust.argtypes=[c.POINTER(w.RECT),w.DWORD,w.BOOL,w.DWORD,w.UINT]
        host.require(adjust(c.byref(margins),style,False,ex,dpi),"DPI window margins")
    else:
        u.AdjustWindowRectEx.argtypes=[c.POINTER(w.RECT),w.DWORD,w.BOOL,w.DWORD]
        host.require(u.AdjustWindowRectEx(c.byref(margins),style,False,ex),"Window margins")
    width=monitor.work.right-monitor.work.left
    height=monitor.work.bottom-monitor.work.top
    fit=max(1,min((width-margins.right+margins.left)//16,
                  (height-margins.bottom+margins.top)//15))
    wanted=(32*dpi+48)//96
    return min(wanted,fit),[width,height],[wanted*16,wanted*15]

class Coord(c.Structure):
    _fields_ = [("x",w.SHORT),("y",w.SHORT)]
class Small(c.Structure):
    _fields_ = [("left",w.SHORT),("top",w.SHORT),("right",w.SHORT),("bottom",w.SHORT)]
class Buffer(c.Structure):
    _fields_ = [("size",Coord),("cursor",Coord),("attributes",w.WORD),("view",Small),("maximum",Coord)]
class Cell(c.Structure):
    _fields_ = [("character",w.WCHAR),("attributes",w.WORD)]
class Key(c.Structure):
    _fields_ = [("down",w.BOOL),("repeat",w.WORD),("key",w.WORD),("scan",w.WORD),("character",w.WCHAR),("controls",w.DWORD)]
class Record(c.Structure):
    _fields_ = [("kind",w.WORD),("key",Key)]
k.GetConsoleScreenBufferInfo.argtypes = [w.HANDLE,c.POINTER(Buffer)]
k.ReadConsoleOutputW.argtypes = [w.HANDLE,c.POINTER(Cell),Coord,Coord,c.POINTER(Small)]
k.WriteConsoleInputW.argtypes = [w.HANDLE,c.POINTER(Record),w.DWORD,c.POINTER(w.DWORD)]

RUN_DEADLINE = float("inf")

def wait_for(predicate, label, seconds=8):
    deadline = min(time.monotonic()+seconds, RUN_DEADLINE)
    while time.monotonic()<deadline:
        value=predicate()
        if value:return value
        time.sleep(.03)
    raise RuntimeError(label)

def main():
    global RUN_DEADLINE
    RUN_DEADLINE = time.monotonic()+60
    args=argparse.ArgumentParser(description=__doc__)
    args.add_argument("--product",type=Path,required=True)
    args.add_argument("--output",type=Path,required=True)
    args.add_argument("--pending-exit",action="store_true")
    a=args.parse_args();output=a.output.resolve()
    host.require("build" in output.parts,"Ignored build output required")
    output.mkdir(parents=True,exist_ok=True)
    u.SetProcessDpiAwarenessContext(c.c_void_p(-4))
    name="mysmb-owned-"+str(k.GetCurrentProcessId())
    desktop=u.CreateDesktopW(name,None,None,0,0x1ff,None)
    host.require(desktop,"Private desktop")
    info,process=host.Startup(),host.Process()
    info.cb=c.sizeof(info);info.desktop="WinSta0\\"+name;info.flags=1;info.show=1
    rows=[];handles=[]
    try:
        host.require(k.CreateProcessW(None,c.create_unicode_buffer('"'+str(a.product.resolve())+'"'),None,None,
            False,0x10,None,str(output),c.byref(info),c.byref(process)),"Owned product")
        k.CloseHandle(process.thread)
        root=wait_for(lambda:next((x for x in host.windows(desktop) if x[1]==process.pid and x[2]=="MySMBWindow"),None),"Product root",12)
        hwnd=root[0];rect=w.RECT()
        wait_for(lambda:bool(u.IsWindowVisible(hwnd)),"Product initial show",12)
        host.require(u.GetClientRect(hwnd,c.byref(rect)),"Initial client rectangle")
        dpi=u.GetDpiForWindow(hwnd);units,work,wanted=initial_units(hwnd,dpi)
        host.require((rect.right,rect.bottom)==(units*16,units*15),"DPI-scaled initial client")
        rows.append(dict(route="startup",dpi=dpi,client=[rect.right,rect.bottom],workArea=work,requestedClient=wanted))
        def message(kind,key=0):
            result=c.c_size_t()
            host.require(u.SendMessageTimeoutW(hwnd,kind,key,0,2,1500,c.byref(result)),"Root message responsiveness")
        def event(key,down):
            r=Record();r.kind=1;r.key=Key(down,1,key,15 if key==9 else 1,"\0",0)
            written=w.DWORD();host.require(k.WriteConsoleInputW(handles[0],c.byref(r),1,c.byref(written)) and written.value==1,"Owned console event")
        if a.pending_exit:
            message(7);message(0x100,9);time.sleep(.05);message(0)
            message(0x10)
            host.require(k.WaitForSingleObject(process.handle,8000)==0,"Exit during console transfer")
            code=w.DWORD();k.GetExitCodeProcess(process.handle,c.byref(code))
            host.require(code.value==0,"Pending-transfer exit status")
            rows.append(dict(route="pending-transfer/root-close",exitCode=0))
            print(json.dumps(rows));return
        for cycle in range(3):
            message(7);message(0x100,9)
            def switched():
                if not u.IsWindowVisible(hwnd):return True
                message(0)
                return False
            wait_for(switched,"Tab did not retain text mode")
            k.FreeConsole();host.require(k.AttachConsole(process.pid),"Attach owned test console")
            for device in ("CONIN$","CONOUT$"):
                h=k.CreateFileW(device,0xc0000000,3,None,3,0,None)
                host.require(h and h!=c.c_void_p(-1).value,"Console device")
                handles.append(h)
            try:
                time.sleep(.15);message(0)
                host.require(not u.IsWindowVisible(hwnd),"Unexpected graphics fallback")
                state=Buffer();host.require(k.GetConsoleScreenBufferInfo(handles[1],c.byref(state)),"Output state")
                kind=c.create_unicode_buffer(80)
                u.GetClassNameW(k.GetConsoleWindow(),kind,80)
                classic=kind.value=="ConsoleWindowClass" and (u.GetWindowLongW(k.GetConsoleWindow(),-16)&0xc00000)==0xc00000 and u.GetParent(k.GetConsoleWindow())!=c.c_void_p(-3).value
                if classic:host.require(state.size.x==80 and state.size.y==50,"Classic80x50 buffer")
                width=min(80,state.view.right-state.view.left+1)
                height=min(50,state.view.bottom-state.view.top+1)
                host.require(width>0 and height>0,"Visible text viewport")
                cells=(Cell*(width*height))()
                def read_content():
                    view=Small(state.view.left,state.view.top,state.view.left+width-1,state.view.top+height-1)
                    host.require(k.ReadConsoleOutputW(handles[1],cells,Coord(width,height),Coord(0,0),c.byref(view)),"Actual authored output readback")
                    return any(x.character not in (" ","\0") for x in cells)
                wait_for(read_content,"Text content missing",3)
                rows.append(dict(route="classic" if classic else "native-Terminal",visibleCells=width*height,viewport=[width,height]))
                event(9,False)
                if cycle==2:
                    event(27,True)
                    host.require(k.WaitForSingleObject(process.handle,min(8000,max(0,int((RUN_DEADLINE-time.monotonic())*1000))))==0,"Console Escape exit")
                else:
                    event(9,True)
                    wait_for(lambda:bool(u.IsWindowVisible(hwnd)),"Console Tab did not restore graphics")
                    message(0x101,9);message(0)
                    u.GetClientRect(hwnd,c.byref(rect))
                    host.require((rect.right,rect.bottom)==(units*16,units*15),"Graphics size changed across Tab")
                rows.append(dict(route="owned-text-input-return" if cycle<2 else "owned-text-Escape",cycle=cycle))
            finally:
                for h in handles:k.CloseHandle(h)
                handles.clear();k.FreeConsole()
        code=w.DWORD();k.GetExitCodeProcess(process.handle,c.byref(code));host.require(code.value==0,"Product exit status")
    finally:
        for h in handles:k.CloseHandle(h)
        k.FreeConsole()
        if process.handle:
            if k.WaitForSingleObject(process.handle,0)!=0:k.TerminateProcess(process.handle,99)
            k.CloseHandle(process.handle)
        u.CloseDesktop(desktop)
        (output/"owned-console.json").write_text(json.dumps(rows,indent=2)+"\n")
    print(json.dumps(rows))

if __name__=="__main__":main()
