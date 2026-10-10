#include <windows.h>
#include <tlhelp32.h>
#include "platform/win32/launch.h"

int mysmb_win32_start_in_text(void)
{
    HANDLE snapshot;
    PROCESSENTRY32 entry;
    DWORD parent,current;
    DWORD ids[64],count,i;
    current=GetCurrentProcessId();parent=0U;
    snapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0U);
    if(snapshot==INVALID_HANDLE_VALUE)return 0;
    ZeroMemory(&entry,sizeof(entry));entry.dwSize=sizeof(entry);
    if(Process32First(snapshot,&entry))do {
        if(entry.th32ProcessID==current) {
            parent=entry.th32ParentProcessID;break;
        }
    } while(Process32Next(snapshot,&entry));
    CloseHandle(snapshot);
    if(!parent)return 0;
    /* The parent process identity,not its image name,defines initial text
     * selection. This also works for terminal/ConPTY hosts without a HWND. */
    count=GetConsoleProcessList(ids,64U);
    for(i=0U;i<count && i<64U;++i)if(ids[i]==parent)return 1;
    /* A console-subsystem child can have an unrelated startup console. */
    if(count!=0U)FreeConsole();
    /* Detached launch probes a real parent console;the text device acquires it
     * after policy succeeds. */
    if(!AttachConsole(parent))return 0;
    FreeConsole();return 1;
}
