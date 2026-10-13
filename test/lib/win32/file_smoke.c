#include <stdio.h>
#include <windows.h>
#include "win32/file.h"
static int put(const char *name){FILE *f=fopen(name,"wb");if(!f)return 0;fputs("pcm",f);return fclose(f)==0;}
int main(void)
{
 char path[1024],tiny[1];
 if(!mygames_win32_executable_path(path,sizeof(path)) || mygames_win32_executable_path(tiny,1) || tiny[0])return 6;
 DeleteFileA("next.tmp");SetFileAttributesA("slot.dat",FILE_ATTRIBUTE_NORMAL);DeleteFileA("slot.dat");
 if(!put("next.tmp") || !mygames_win32_file_replace("next.tmp","slot.dat"))return 1;
 if(!put("next.tmp") || !mygames_win32_file_replace("next.tmp","slot.dat"))return 2;
 if(mygames_win32_file_replace("missing.tmp","slot.dat") || GetFileAttributesA("slot.dat")==INVALID_FILE_ATTRIBUTES)return 3;
 if(!put("next.tmp") || !SetFileAttributesA("slot.dat",FILE_ATTRIBUTE_READONLY))return 4;
 if(mygames_win32_file_replace("next.tmp","slot.dat"))return 5;
 SetFileAttributesA("slot.dat",FILE_ATTRIBUTE_NORMAL);DeleteFileA("slot.dat");DeleteFileA("next.tmp");return 0;
}
