#include <windows.h>
#include <tlhelp32.h>
#include "platform/win32/launch.h"

int mysmb_win32_shell_name(const char *name)
{
    return name && (!lstrcmpiA(name,"cmd.exe") ||
        !lstrcmpiA(name,"powershell.exe") || !lstrcmpiA(name,"pwsh.exe"));
}

int mysmb_win32_start_in_text(void)
{
    HANDLE snapshot;
    PROCESSENTRY32 entry;
    DWORD parent,current;
    int shell;
    current=GetCurrentProcessId();parent=0U;shell=0;
    snapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0U);
    if(snapshot==INVALID_HANDLE_VALUE)return 0;
    ZeroMemory(&entry,sizeof(entry));entry.dwSize=sizeof(entry);
    if(Process32First(snapshot,&entry))do {
        if(entry.th32ProcessID==current) {
            parent=entry.th32ParentProcessID;break;
        }
    } while(Process32Next(snapshot,&entry));
    if(parent && Process32First(snapshot,&entry))do {
        if(entry.th32ProcessID==parent) {
            shell=mysmb_win32_shell_name(entry.szExeFile);break;
        }
    } while(Process32Next(snapshot,&entry));
    CloseHandle(snapshot);
    if(!shell)return 0;
    /* Probe attachment only. Never render into or reconfigure the shell's
     * console: a GUI launch leaves that shell free to continue accepting input. */
    if(!AttachConsole(parent))return 0;
    FreeConsole();return 1;
}
