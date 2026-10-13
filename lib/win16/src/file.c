#include <windows.h>
#include "win16/file.h"
int mygames_win16_executable_path(mygames_kvm_u16 instance,char *path,mygames_kvm_u16 capacity)
{
    unsigned short count;
    if(!path || capacity<2U)return 0;
    count=GetModuleFileName((HINSTANCE)instance,path,capacity);
    if(!count || count>=capacity){path[0]=0;return 0;}
    path[count]=0;return 1;
}
