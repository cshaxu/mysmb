#include "win32/file.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
int mygames_win32_file_replace(const char *pending,const char *final_name)
{
    return MoveFileExA(pending,final_name,MOVEFILE_REPLACE_EXISTING|
        MOVEFILE_WRITE_THROUGH)!=0;
}

unsigned long mygames_win32_executable_path(char *path,unsigned short capacity)
{
    DWORD count;
    if(!path || !capacity)return 0;
    count=GetModuleFileNameA(NULL,path,capacity);
    if(!count || count>=capacity){path[0]=0;return 0;}
    return count;
}
