#include "dos16/host.h"
#include <dos.h>

void mygames_dos16_video_restore(const struct mygames_dos16_video_state *state)
{
    union REGS registers;
    if(state->mode<=3U || state->mode==7U) {
        /* 43 eight-pixel rows occupy344 of the350 scanlines. */
        registers.x.ax=(unsigned short)((state->rows+1U)*state->font>350U?0x1202U:
            (state->rows+1U)*state->font>200U?0x1201U:0x1200U);
        registers.x.bx=0x30U;int86(0x10,&registers,&registers);
    }
    registers.h.ah=0U;registers.h.al=state->mode;
    int86(0x10,&registers,&registers);
    if(state->mode<=3U || state->mode==7U) {
        if(state->font==8U || state->font==14U || state->font==16U) {
            registers.x.ax=state->font==8U?0x1112U:state->font==14U?0x1111U:0x1114U;
            registers.x.bx=0U;int86(0x10,&registers,&registers);
        }
        registers.h.ah=1U;registers.x.cx=state->cursor;
        int86(0x10,&registers,&registers);
    }
}
void mygames_dos16_video_capture(struct mygames_dos16_video_state *state)
{
    union REGS registers;
    registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
    state->mode=registers.h.al;
    state->rows=*(volatile unsigned char far *)0x00400084UL;
    state->font=*(volatile unsigned char far *)0x00400085UL;
    registers.h.ah=3U;registers.h.bh=0U;
    int86(0x10,&registers,&registers);state->cursor=registers.x.cx;
}

int mygames_dos16_text_mode(mygames_kvm_u16 rows)
{
    union REGS registers;
    if(rows!=25U && rows!=50U)return 0;

    registers.x.ax=0x1202U;registers.x.bx=0x30U;
    int86(0x10,&registers,&registers);
    registers.x.ax=3U;int86(0x10,&registers,&registers);
    registers.x.ax=rows==50U?0x1112U:0x1114U;registers.x.bx=0U;
    int86(0x10,&registers,&registers);
    registers.x.ax=0x1003U;registers.x.bx=0U;
    int86(0x10,&registers,&registers);
    registers.h.ah=1U;registers.h.ch=0x20U;registers.h.cl=0U;
    int86(0x10,&registers,&registers);
    registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
    return registers.h.al==3U && registers.h.ah==80U &&
        *(volatile unsigned char far *)0x00400084UL==(unsigned char)(rows-1U);
}
