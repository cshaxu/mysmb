#include "platform/dos16/executable_path.h"
#include "io/file/executable_path.h"
#include <dos.h>
int mysmb_dos16_executable_path(char *path,mysmb_io_u16 capacity)
{
    union REGS registers;
    unsigned short far *environment_segment;
    const char far *environment;
    unsigned short offset,i;
    if(capacity<4U)return 0;
    registers.h.ah=0x62U;int86(0x21,&registers,&registers);
    environment_segment=(unsigned short far *)(((unsigned long)registers.x.bx<<16U)+0x2cUL);
    if(!*environment_segment)return 0;
    environment=(const char far *)((unsigned long)*environment_segment<<16U);
    /* DOS3+ environment ends with two NULs,then a count word and EXE path. */
    for(offset=0U;offset<65530U;++offset)
        if(environment[offset]=='\0' && environment[offset+1U]=='\0')break;
    if(offset==65530U || environment[offset+2U]==0)return 0;
    offset=(unsigned short)(offset+4U);
    for(i=0U;i<capacity-1U && (unsigned long)offset+i<65536UL;++i){
        path[i]=environment[offset+i];
        if(!path[i])return 1;
    }
    return 0;
}
