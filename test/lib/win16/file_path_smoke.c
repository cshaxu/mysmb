#include <windows.h>
#include <string.h>
#include "win16/file.h"
static UINT result=12,seen;
UINT GetModuleFileName(HINSTANCE instance,char *path,UINT capacity)
{seen=instance;if(result && result<capacity)memcpy(path,"C:\\GAME.EXE",12);return result;}
int main(void)
{
 char path[32];
 if(mygames_win16_executable_path(42,0,32) || mygames_win16_executable_path(42,path,1))return 1;
 if(!mygames_win16_executable_path(42,path,sizeof(path)) || seen!=42 || strcmp(path,"C:\\GAME.EXE"))return 2;
 result=32;if(mygames_win16_executable_path(42,path,sizeof(path)) || path[0])return 3;
 result=0;if(mygames_win16_executable_path(42,path,sizeof(path)))return 4;
 return 0;
}
