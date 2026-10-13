#include <dos.h>
#include <stdio.h>
#include "dos16/mouse.h"
static unsigned char saved[4096];
static struct mygames_dos16_mouse mouse;
int main(void)
{
    struct mygames_dos16_mouse_registers before={0},after={0};
    struct mygames_kvm_input_event event;
    void (__interrupt __far *vector)();
    unsigned short bytes;
    int result=0;
    FILE *file;
    bytes=mygames_dos16_mouse_storage(&mygames_dos16_mouse_native_bus,0);
    if(!bytes || bytes>sizeof(saved))return 1;
    before.ax=3;mygames_dos16_mouse_native_bus.call(0,&before,0);
    if(!mygames_dos16_mouse_open(&mouse,&mygames_dos16_mouse_native_bus,0,saved,sizeof(saved)))return 2;
    if(!mygames_dos16_mouse_range(&mouse,639,199,8,8,MYGAMES_KVM_COORD_TEXT_CELLS))result=3;
    if(!mygames_dos16_mouse_poll(&mouse,&event) || event.kind!=MYGAMES_KVM_INPUT_CANCEL)result=4;
    if(!mygames_dos16_mouse_position(&mouse,12,9) ||
        !mygames_dos16_mouse_poll(&mouse,&event) || event.x!=12 || event.y!=9)result=5;
    mygames_dos16_mouse_visible(&mouse,1);mygames_dos16_mouse_visible(&mouse,0);
    mygames_dos16_mouse_close(&mouse);
    after.ax=3;mygames_dos16_mouse_native_bus.call(0,&after,0);
    if(before.cx!=after.cx || before.dx!=after.dx || before.bx!=after.bx)result=6;
    vector=_dos_getvect(0x33);_dos_setvect(0x33,0);
    bytes=mygames_dos16_mouse_storage(&mygames_dos16_mouse_native_bus,0);
    _dos_setvect(0x33,vector);
    if(bytes)result=7;
    file=fopen(result?"mouse.bad":"mouse.ok","w");
    if(!file)return 8;
    fprintf(file,"result=%d saved=%u position=%u,%u restored=%u,%u absent=%u\n",result,
        mygames_dos16_mouse_storage(&mygames_dos16_mouse_native_bus,0),event.x,event.y,after.cx,after.dx,bytes);
    fclose(file);return result;
}
