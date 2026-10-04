#include "platform/file/executable_path.h"
int mysmb_file_executable_directory(const char *path,char *directory,
    mysmb_io_u16 capacity)
{
    mysmb_io_u16 i,last;
    if(capacity<4U || !path || path[0]=='\0' || path[1]!=':' ||
        (path[2]!='\\' && path[2]!='/'))return 0;
    last=0U;
    for(i=0U;i<capacity && path[i];++i)
        if(path[i]=='\\' || path[i]=='/')last=(mysmb_io_u16)(i+1U);
    if(i==capacity || !last || last==i)return 0;
    for(i=0U;i<last;++i)directory[i]=path[i];
    directory[last]='\0';return 1;
}
