#include "dos16/vga.h"
#include <dos.h>
#include <conio.h>

void mygames_dos16_copy_bytes(unsigned char far *video,
    const unsigned char far *pixels,unsigned short count)
{
    _asm {
        push ds
        push es
        push bx
        lds si,pixels
        les di,video
        mov cx,count
        mov bx,cx
        shr cx,1
#if !defined(MYGAMES_DOS16_8086)
        shr cx,1
#endif
        cld
#if !defined(MYGAMES_DOS16_8086)
        _emit 0x66
#endif
        rep movsw
        mov cx,bx
#if defined(MYGAMES_DOS16_8086)
        and cx,1
#else
        and cx,3
#endif
        rep movsb
        pop bx
        pop es
        pop ds
    }
}

void mygames_dos16_copy_dwords(unsigned char far *video,
    const unsigned char far *pixels,unsigned short count)
{
    _asm {
        push ds
        push es
        lds si,pixels
        les di,video
        mov cx,count
        shr cx,1
#if !defined(MYGAMES_DOS16_8086)
        shr cx,1
#endif
        cld
#if !defined(MYGAMES_DOS16_8086)
        _emit 0x66
#endif
        rep movsw
        pop es
        pop ds
    }
}

void mygames_dos16_vga_register(unsigned short port,unsigned char index,unsigned char value)
{ outp(port,index);outp((unsigned short)(port+1U),value); }

void mygames_dos16_vga_native(void)
{
    unsigned char protect;
    mygames_dos16_vga_register(0x3c4,0,1);
    outp(0x3c2,0xe3);
    mygames_dos16_vga_register(0x3c4,4,14);
    outp(0x3d4,17);protect=(unsigned char)inp(0x3d5);
    mygames_dos16_vga_register(0x3d4,17,(unsigned char)(protect&0x7fU));
    mygames_dos16_vga_register(0x3d4,1,63);mygames_dos16_vga_register(0x3d4,2,64);
    mygames_dos16_vga_register(0x3d4,6,13);mygames_dos16_vga_register(0x3d4,7,62);
    mygames_dos16_vga_register(0x3d4,9,65);
    mygames_dos16_vga_register(0x3d4,16,234);mygames_dos16_vga_register(0x3d4,17,44);
    mygames_dos16_vga_register(0x3d4,18,223);mygames_dos16_vga_register(0x3d4,19,32);
    mygames_dos16_vga_register(0x3d4,20,64);
    mygames_dos16_vga_register(0x3d4,21,231);mygames_dos16_vga_register(0x3d4,22,6);
    mygames_dos16_vga_register(0x3d4,23,0xa3);
    mygames_dos16_vga_register(0x3c4,2,15);
    mygames_dos16_vga_register(0x3c4,0,3);
}

void mygames_dos16_vga_planar512(void)
{
    unsigned char protect;
    mygames_dos16_vga_register(0x3c4,0,1);outp(0x3c2,0xe3);mygames_dos16_vga_register(0x3c4,4,6);
    outp(0x3d4,17);protect=(unsigned char)inp(0x3d5);
    mygames_dos16_vga_register(0x3d4,17,(unsigned char)(protect&0x7fU));
    mygames_dos16_vga_register(0x3d4,1,63);mygames_dos16_vga_register(0x3d4,2,64);
    mygames_dos16_vga_register(0x3d4,6,13);mygames_dos16_vga_register(0x3d4,7,62);
    mygames_dos16_vga_register(0x3d4,9,65);mygames_dos16_vga_register(0x3d4,16,234);
    mygames_dos16_vga_register(0x3d4,17,44);mygames_dos16_vga_register(0x3d4,18,223);
    mygames_dos16_vga_register(0x3d4,19,64);mygames_dos16_vga_register(0x3d4,20,64);
    mygames_dos16_vga_register(0x3d4,21,231);mygames_dos16_vga_register(0x3d4,22,6);
    mygames_dos16_vga_register(0x3d4,23,0xa3);mygames_dos16_vga_register(0x3d4,24,255);
    mygames_dos16_vga_register(0x3d4,12,0);mygames_dos16_vga_register(0x3d4,13,0);
    (void)inp(0x3da);outp(0x3c0,19);outp(0x3c0,0);outp(0x3c0,0x20);
    mygames_dos16_vga_register(0x3c4,2,15);mygames_dos16_vga_register(0x3c4,0,3);
}

void mygames_dos16_vga_plane(unsigned char plane)
{mygames_dos16_vga_register(0x3c4,2,(unsigned char)(1U<<plane));}

void mygames_dos16_vga_planar264(unsigned short start)
{
    unsigned char protect;
    mygames_dos16_vga_register(0x3c4,0,1);outp(0x3c2,0xe3);mygames_dos16_vga_register(0x3c4,4,6);
    outp(0x3d4,17);protect=(unsigned char)inp(0x3d5);
    mygames_dos16_vga_register(0x3d4,17,(unsigned char)(protect&0x7fU));
    mygames_dos16_vga_register(0x3d4,1,63);mygames_dos16_vga_register(0x3d4,2,64);
    mygames_dos16_vga_register(0x3d4,6,13);mygames_dos16_vga_register(0x3d4,7,62);
    mygames_dos16_vga_register(0x3d4,9,65);mygames_dos16_vga_register(0x3d4,16,234);
    mygames_dos16_vga_register(0x3d4,17,44);mygames_dos16_vga_register(0x3d4,18,223);
    /* CRTC offset is word-addressed.  A compact page row is 66 bytes per
     * plane, so its display stride is 33 words. */
    mygames_dos16_vga_register(0x3d4,19,33);mygames_dos16_vga_register(0x3d4,20,64);
    mygames_dos16_vga_register(0x3d4,21,231);mygames_dos16_vga_register(0x3d4,22,6);
    mygames_dos16_vga_register(0x3d4,23,0xa3);mygames_dos16_vga_register(0x3d4,24,255);
    mygames_dos16_vga_register(0x3d4,12,(unsigned char)(start>>9U));
    mygames_dos16_vga_register(0x3d4,13,(unsigned char)(start>>1U));
    (void)inp(0x3da);outp(0x3c0,19);outp(0x3c0,0);outp(0x3c0,0x20);
    mygames_dos16_vga_register(0x3ce,5,0);mygames_dos16_vga_register(0x3c4,2,15);mygames_dos16_vga_register(0x3c4,0,3);
}

int mygames_dos16_vga_bios_mode(unsigned char mode)
{
    union REGS registers;
    registers.x.ax=mode;int86(0x10,&registers,&registers);
    registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
    return registers.h.al==mode;
}
void mygames_dos16_vga_color(unsigned char index,unsigned long rgb)
{
    outp(0x3c8,index);
    outp(0x3c9,(unsigned char)((rgb>>18U)&63UL));
    outp(0x3c9,(unsigned char)((rgb>>10U)&63UL));
    outp(0x3c9,(unsigned char)((rgb>>2U)&63UL));
}
void mygames_dos16_vga_viewport(unsigned short start,unsigned char pan)
{
    mygames_dos16_vga_register(0x3d4,12,(unsigned char)(start>>8U));
    mygames_dos16_vga_register(0x3d4,13,(unsigned char)start);
    (void)inp(0x3da);outp(0x3c0,19);outp(0x3c0,(unsigned char)(pan&7U));outp(0x3c0,0x20);
}

