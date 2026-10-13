#include <string.h>
#include "dos16/mouse.h"
unsigned short mygames_dos16_mouse_storage(const struct mygames_dos16_mouse_bus *bus,void *context)
{
    struct mygames_dos16_mouse_registers r={0};
    if(!bus || !bus->present || !bus->call || !bus->present(context))return 0;
    r.ax=0x15U;bus->call(context,&r,0);return r.bx;
}
int mygames_dos16_mouse_open(struct mygames_dos16_mouse *mouse,
    const struct mygames_dos16_mouse_bus *bus,void *context,
    void MYGAMES_KVM_FAR *saved,unsigned short capacity)
{
    struct mygames_dos16_mouse_registers r={0};
    unsigned short bytes;
    if(!mouse || mouse->opened)return 0;
    bytes=mygames_dos16_mouse_storage(bus,context);
    if(!bytes || !saved || bytes>capacity)return 0;
    memset(mouse,0,sizeof(*mouse));mouse->bus=bus;mouse->context=context;
    mouse->saved=saved;mouse->bytes=bytes;
    r.ax=0x16U;bus->call(context,&r,saved);
    r.ax=0U;bus->call(context,&r,0);
    if(r.ax!=0xffffU){r.ax=0x17U;bus->call(context,&r,saved);return 0;}
    mouse->opened=1U;mouse->div_x=mouse->div_y=1U;
    mouse->space=MYGAMES_KVM_COORD_CLIENT_PIXELS;return 1;
}
int mygames_dos16_mouse_range(struct mygames_dos16_mouse *mouse,
    unsigned short max_x,unsigned short max_y,unsigned short div_x,unsigned short div_y,
    unsigned char space)
{
    struct mygames_dos16_mouse_registers r={0};
    if(!mouse || !mouse->opened || max_x>32767U || max_y>32767U || !div_x || !div_y ||
        (space!=MYGAMES_KVM_COORD_CLIENT_PIXELS && space!=MYGAMES_KVM_COORD_TEXT_CELLS))return 0;
    r.ax=7U;r.dx=max_x;mouse->bus->call(mouse->context,&r,0);
    r.ax=8U;r.cx=0U;r.dx=max_y;mouse->bus->call(mouse->context,&r,0);
    mouse->max_x=max_x;mouse->max_y=max_y;mouse->div_x=div_x;mouse->div_y=div_y;
    mouse->space=space;mouse->configured=1U;mouse->pending=0U;mouse->count=1U;
    mygames_kvm_pointer_cancel(&mouse->pointer,mouse->events);return 1;
}
void mygames_dos16_mouse_visible(struct mygames_dos16_mouse *mouse,unsigned char visible)
{
    struct mygames_dos16_mouse_registers r={0};
    if(!mouse || !mouse->opened || mouse->visible==(visible!=0U))return;
    r.ax=visible?1U:2U;mouse->bus->call(mouse->context,&r,0);
    mouse->visible=(unsigned char)(visible!=0U);
}
int mygames_dos16_mouse_position(struct mygames_dos16_mouse *mouse,unsigned short x,unsigned short y)
{
    struct mygames_dos16_mouse_registers r={0};
    unsigned long raw_x,raw_y;
    if(!mouse || !mouse->opened || !mouse->configured)return 0;
    raw_x=(unsigned long)x*mouse->div_x;raw_y=(unsigned long)y*mouse->div_y;
    if(raw_x>mouse->max_x || raw_y>mouse->max_y)return 0;
    r.ax=4U;r.cx=(unsigned short)raw_x;r.dx=(unsigned short)raw_y;
    mouse->bus->call(mouse->context,&r,0);return 1;
}
int mygames_dos16_mouse_poll(struct mygames_dos16_mouse *mouse,struct mygames_kvm_input_event *event)
{
    struct mygames_dos16_mouse_registers r={0};
    if(!mouse || !mouse->opened || !mouse->configured || !event)return 0;
    if(mouse->pending>=mouse->count) {
        r.ax=3U;mouse->bus->call(mouse->context,&r,0);mouse->pending=0U;
        mouse->count=mygames_kvm_pointer_update(&mouse->pointer,(short)(r.cx/mouse->div_x),
            (short)(r.dx/mouse->div_y),r.bx,0U,mouse->space,mouse->events);
    }
    if(mouse->pending>=mouse->count)return 0;
    *event=mouse->events[mouse->pending++];return 1;
}
void mygames_dos16_mouse_close(struct mygames_dos16_mouse *mouse)
{
    struct mygames_dos16_mouse_registers r={0};
    if(!mouse || !mouse->opened)return;
    r.ax=0x17U;mouse->bus->call(mouse->context,&r,mouse->saved);
    memset(mouse,0,sizeof(*mouse));
}
