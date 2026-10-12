#include "platform/dos16/retained_background.h"
#include <stdio.h>

static int check(mygames_kvm_u16 x,mygames_kvm_u16 y,mygames_kvm_u8 want_plane,
    mygames_kvm_u16 want_offset)
{
    mygames_kvm_u8 plane=0xffU;
    mygames_kvm_u16 offset=0xffffU;
    return mysmb_dos16_retained_address(x,y,&plane,&offset) && plane==want_plane &&
        offset==want_offset;
}
int main(void)
{
    mygames_kvm_u8 plane=0xffU;
    mygames_kvm_u16 offset=0xffffU;
    if(!check(0U,0U,0U,0U) || !check(511U,479U,3U,61439U) ||
        !check(256U,17U,0U,2240U) ||
        !mysmb_dos16_retained_tile_address(1U,29U,31U,1U,&plane,&offset) ||
        plane!=0U || offset!=60542U)return 1;
    if(mysmb_dos16_retained_address(512U,0U,&plane,&offset) ||
        mysmb_dos16_retained_address(0U,480U,&plane,&offset) ||
        mysmb_dos16_retained_tile_address(2U,0U,0U,0U,&plane,&offset))return 2;
    printf("planes=4 stride=%u end=%u tile=%u\n",
        MYSMB_DOS16_RETAINED_STRIDE,MYSMB_DOS16_RETAINED_PLANE_BYTES,offset);
    return 0;
}
