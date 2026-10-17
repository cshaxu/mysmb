#include "dos16/command_line.h"
int mygames_dos16_command_tail_copy(
    const mygames_kvm_u8 MYGAMES_KVM_FAR *tail,char *output,
    unsigned short capacity)
{
    unsigned short length,i;
    if(!output || capacity==0U)return 0;
    output[0]='\0';
    if(!tail)return 0;
    length=tail[0];
    if(length>126U || length>=capacity)return 0;
    for(i=0U;i<length;++i)output[i]=(char)tail[i+1U];
    output[length]='\0';
    return 1;
}
