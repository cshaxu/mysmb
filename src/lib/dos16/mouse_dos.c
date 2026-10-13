#include <dos.h>
#include "dos16/mouse.h"
static int present(void *context)
{
    void (__interrupt __far *vector)();
    const unsigned char __far *entry;
    (void)context;vector=_dos_getvect(0x33);entry=(const unsigned char __far *)vector;
    return entry && *entry!=0xcfU;
}
static void call(void *context,struct mygames_dos16_mouse_registers *r,void __far *buffer)
{
    union REGS regs;
    struct SREGS segments;
    (void)context;regs.x.ax=r->ax;regs.x.bx=r->bx;regs.x.cx=r->cx;regs.x.dx=r->dx;
    segread(&segments);
    if(buffer){segments.es=FP_SEG(buffer);regs.x.dx=FP_OFF(buffer);}
    int86x(0x33,&regs,&regs,&segments);
    r->ax=regs.x.ax;r->bx=regs.x.bx;r->cx=regs.x.cx;r->dx=regs.x.dx;
}
const struct mygames_dos16_mouse_bus mygames_dos16_mouse_native_bus={present,call};
