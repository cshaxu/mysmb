#include "platform/dos16/palette_expand.h"
#include <dos.h>
/* 486SX real-mode DWORD bulk operations; addressing remains USE16.
 * Platform-private implementation; palette preparation is neutral IO. */
int mysmb_dos16_palette_expand(void *context,const mysmb_io_u8 far *packed,
    mysmb_io_u8 far *pixels,mysmb_io_u16 count,
    const mysmb_io_u8 far *palette)
{
    struct mysmb_io_palette_pairs near *w;
    mysmb_io_u16 data_segment,stack_segment,table_offset,zero_pair,last;
    _asm {mov data_segment,ds
          mov stack_segment,ss}
    if(!context || !packed || !pixels || count>256U || (count&1U) ||
        FP_SEG(context)!=data_segment || stack_segment!=data_segment)return 0;
    w=(struct mysmb_io_palette_pairs near *)context;
    mysmb_io_palette_pairs_prepare(w,palette);
    table_offset=(mysmb_io_u16)w->pairs;
    zero_pair=w->pairs[0];
    _asm {
        push bp
        push ds
        push es
        lds si,packed
        les di,pixels
        mov bx,di
        push es
        push ds
        pop es
        mov di,si
        xor ax,ax
        mov cx,count
        shr cx,1
        cld
        test cx,3
        jnz scan_bytes
        shr cx,1
        shr cx,1
        _emit 0x66
        xor ax,ax
        _emit 0x66
        repe scasw
        jmp scan_done
scan_bytes:
        repe scasb
scan_done:
        pop es
        mov di,bx
        jnz span_mixed
        mov ax,ss:zero_pair
        mov cx,count
        shr cx,1
        test cx,1
        jnz fill_words
        mov dx,ax
        /* SHL EAX,16: explicit operand size in a USE16 segment. */
        _emit 0x66
        _emit 0xc1
        _emit 0xe0
        _emit 0x10
        mov ax,dx
        shr cx,1
        _emit 0x66
        rep stosw
        jmp fill_done
fill_words:
        rep stosw
fill_done:
        jmp pairs_done
span_mixed:
        mov di,bx
        mov dx,ss:table_offset
        mov cx,count
        shr cx,1
        shr cx,1
        mov bp,zero_pair
        jcxz pairs_done
pairs_next:
        mov ax,[si]
        or ax,ax
        jnz pairs_colored
        mov es:[di],bp
        mov es:[di+2],bp
        jmp pairs_advance
pairs_colored:
        mov bl,al
        xor bh,bh
        shl bx,1
        add bx,dx
        mov bx,ss:[bx]
        mov es:[di],bx
        mov bl,ah
        xor bh,bh
        shl bx,1
        add bx,dx
        mov ax,ss:[bx]
        mov es:[di+2],ax
pairs_advance:
        add si,2
        add di,4
        loop pairs_next
pairs_done:
        pop es
        pop ds
        pop bp
    }
    if(count&2U){
        last=w->pairs[packed[count/2U-1U]];
        pixels[count-2U]=(mysmb_io_u8)last;
        pixels[count-1U]=(mysmb_io_u8)(last>>8U);
    }
    return 1;
}
