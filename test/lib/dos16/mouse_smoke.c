#include <string.h>
#include "dos16/mouse.h"
struct device {int present,reset_ok;unsigned short bytes,calls,saves,restores,show,hide,x,y,buttons;};
static int present(void *context){return ((struct device *)context)->present;}
static void call(void *context,struct mygames_dos16_mouse_registers *r,void MYGAMES_KVM_FAR *buffer)
{
    struct device *d=(struct device *)context;
    ++d->calls;
    switch(r->ax) {
    case 0x15:r->bx=d->bytes;break;
    case 0x16:++d->saves;((unsigned char *)buffer)[0]=42;break;
    case 0x17:if(((unsigned char *)buffer)[0]==42)++d->restores;break;
    case 0:r->ax=d->reset_ok?0xffffU:0;break;
    case 1:++d->show;break;
    case 2:++d->hide;break;
    case 3:r->bx=d->buttons;r->cx=d->x;r->dx=d->y;break;
    case 4:d->x=r->cx;d->y=r->dx;break;
    }
}
int main(void)
{
    const struct mygames_dos16_mouse_bus bus={present,call};
    struct mygames_dos16_mouse mouse;
    struct device d;
    struct mygames_kvm_input_event event;
    unsigned char saved[32];
    memset(&mouse,0,sizeof(mouse));memset(&d,0,sizeof(d));
    if(mygames_dos16_mouse_storage(0,&d) || mygames_dos16_mouse_open(&mouse,&bus,&d,saved,32) || d.calls)return 1;
    d.present=1;d.bytes=33;
    if(mygames_dos16_mouse_open(&mouse,&bus,&d,saved,32) || d.saves)return 2;
    d.bytes=32;d.reset_ok=0;
    if(mygames_dos16_mouse_open(&mouse,&bus,&d,saved,32) || d.restores!=1)return 3;
    d.reset_ok=1;
    if(!mygames_dos16_mouse_open(&mouse,&bus,&d,saved,32) ||
        mygames_dos16_mouse_open(&mouse,&bus,&d,saved,32))return 4;
    if(mygames_dos16_mouse_poll(&mouse,&event) || mygames_dos16_mouse_position(&mouse,1,1))return 5;
    if(mygames_dos16_mouse_range(&mouse,639,199,0,8,MYGAMES_KVM_COORD_TEXT_CELLS) ||
        mygames_dos16_mouse_range(&mouse,32768U,199,8,8,MYGAMES_KVM_COORD_TEXT_CELLS) ||
        !mygames_dos16_mouse_range(&mouse,639,199,8,8,MYGAMES_KVM_COORD_TEXT_CELLS))return 6;
    if(!mygames_dos16_mouse_poll(&mouse,&event) || event.kind!=MYGAMES_KVM_INPUT_CANCEL)return 7;
    if(!mygames_dos16_mouse_position(&mouse,12,9) || d.x!=96 || d.y!=72 ||
        mygames_dos16_mouse_position(&mouse,80,25))return 8;
    d.buttons=3;
    if(!mygames_dos16_mouse_poll(&mouse,&event) || event.x!=12 || event.y!=9 || event.buttons!=1 ||
        !mygames_dos16_mouse_poll(&mouse,&event) || event.buttons!=3 ||
        mygames_dos16_mouse_poll(&mouse,&event))return 9;
    mygames_dos16_mouse_visible(&mouse,1);mygames_dos16_mouse_visible(&mouse,1);
    mygames_dos16_mouse_visible(&mouse,0);
    if(d.show!=1 || d.hide!=1)return 10;
    mygames_dos16_mouse_close(&mouse);mygames_dos16_mouse_close(&mouse);
    if(d.restores!=2 || mouse.opened || mygames_dos16_mouse_poll(&mouse,&event))return 11;
    return 0;
}
