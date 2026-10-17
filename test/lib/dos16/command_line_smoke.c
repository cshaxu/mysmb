#include "dos16/command_line.h"
#include <string.h>
int main(void)
{
    mygames_kvm_u8 tail[128];
    char output[128];
    unsigned short i;
    memset(tail,0,sizeof(tail));
    if(mygames_dos16_command_tail_copy(tail,0,128U) ||
        mygames_dos16_command_tail_copy(tail,output,0U))return 1;
    output[0]='x';
    if(mygames_dos16_command_tail_copy(0,output,128U) || output[0])return 2;
    if(!mygames_dos16_command_tail_copy(tail,output,1U) || output[0])return 3;
    tail[0]=8U;memcpy(tail+1," --turbo",8U);
    if(!mygames_dos16_command_tail_copy(tail,output,9U) ||
        strcmp(output," --turbo"))return 4;
    if(mygames_dos16_command_tail_copy(tail,output,8U) || output[0])return 5;
    tail[0]=126U;for(i=1U;i<=126U;++i)tail[i]='a';
    if(!mygames_dos16_command_tail_copy(tail,output,128U) ||
        strlen(output)!=126U)return 6;
    tail[0]=127U;
    if(mygames_dos16_command_tail_copy(tail,output,128U) || output[0])return 7;
    return 0;
}
