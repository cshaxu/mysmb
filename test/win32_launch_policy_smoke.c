#include <string.h>
#include <windows.h>
#include "platform/win32/launch.h"
int main(int count,char **arguments)
{
    if(count==2) {
        /* Also exercise shell availability after explicit detachment,as on
         * a graphical launch or a subsequent Tab attachment. */
        FreeConsole();
        if(!strcmp(arguments[1],"text"))return mysmb_win32_start_in_text()?0:1;
        if(!strcmp(arguments[1],"graphics"))return mysmb_win32_start_in_text()?2:0;
        return 3;
    }
    if(!mysmb_win32_shell_name("cmd.exe") ||
        !mysmb_win32_shell_name("CMD.EXE") ||
        !mysmb_win32_shell_name("powershell.exe") ||
        !mysmb_win32_shell_name("pwsh.exe"))return 4;
    if(mysmb_win32_shell_name(NULL) || mysmb_win32_shell_name("") ||
        mysmb_win32_shell_name("explorer.exe") ||
        mysmb_win32_shell_name("launcher.exe") ||
        mysmb_win32_shell_name("mycmd.exe"))return 5;
    return 0;
}
