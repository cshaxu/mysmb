#include <windows.h>
#include "platform/win32/launch.h"
int main(int count,char **arguments)
{
    char command[1024];
    STARTUPINFOA startup;
    PROCESS_INFORMATION child;
    DWORD result;
    (void)arguments;
    /* The child has this arbitrary test executable as its console-owning
     * parent. Its name must not affect text selection. */
    if(count==2)return mysmb_win32_start_in_text()?0:1;
    FreeConsole();
    if(!AllocConsole())return 2;
    if(!GetModuleFileNameA(NULL,command,sizeof(command)-16U))return 3;
    lstrcatA(command," child");
    ZeroMemory(&startup,sizeof(startup));startup.cb=sizeof(startup);
    ZeroMemory(&child,sizeof(child));
    if(!CreateProcessA(NULL,command,NULL,NULL,TRUE,0U,NULL,NULL,&startup,&child))return 4;
    WaitForSingleObject(child.hProcess,10000U);
    if(!GetExitCodeProcess(child.hProcess,&result) || result!=0U)return 5;
    CloseHandle(child.hThread);CloseHandle(child.hProcess);
    FreeConsole();
    return 0;
}
