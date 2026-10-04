#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "platform/file/snapshot_files.h"
int mysmb_win32_snapshot_replace(const char *pending,const char *final_name)
{
    return MoveFileExA(pending,final_name,MOVEFILE_REPLACE_EXISTING|
        MOVEFILE_WRITE_THROUGH)!=0;
}
