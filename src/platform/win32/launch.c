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
    DWORD ids[64],count,i;
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
    if(GetConsoleWindow()!=NULL) {
        count=GetConsoleProcessList(ids,64U);
        for(i=0U;i<count && i<64U;++i)if(ids[i]==parent)return 1;
        /* START may allocate an unrelated initial console. Prefer the shell's
         * console;detached shells still correctly select graphical startup. */
        FreeConsole();
    }
    /* Detached launch probes availability;the text device acquires it later.
     * Console-subsystem direct launches already inherit their shell console. */
    if(!AttachConsole(parent))return 0;
    FreeConsole();return 1;
}
