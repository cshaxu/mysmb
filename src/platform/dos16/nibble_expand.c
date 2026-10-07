#include "platform/dos16/nibble_expand.h"
#include "io/palette_expand.h"
int mysmb_dos16_nibble_expand(const mysmb_io_u8 far *packed,
    mysmb_io_u8 far *pixels,mysmb_io_u16 count)
{
    if(!packed || !pixels || count>256U || (count&1U))return 0;
    _asm {
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
        mov dx,cx
        and dx,3
        shr cx,1
        shr cx,1
        cld
        _emit 0x66
        xor ax,ax
        _emit 0x66
        repe scasw
        jnz scan_end
        mov cx,dx
        repe scasb
scan_end:
        pop es
        mov di,bx
        jnz colored
        mov cx,count
        shr cx,1
        shr cx,1
        _emit 0x66
        rep stosw
        test count,2
        jz done
        stosw
        jmp done
colored:
        /* Bounded128-entry RAM lookup;restore the incoming interrupt state. */
        pushf
        cli
        _emit 0x0f
        _emit 0xa8
        mov dx,SEG mysmb_io_nibble_pairs
        /* MOV GS,DX. */
        _emit 0x8e
        _emit 0xea
        _emit 0x66
        xor dx,dx
        mov dx,OFFSET mysmb_io_nibble_pairs
        _emit 0x66
        xor bx,bx
        mov cx,count
        shr cx,1
        shr cx,1
        jcxz tail
next_pair:
        mov bl,[si]
        /* AX=GS:[EDX+EBX*2],32-bit address calculation in aUSE16 segment. */
        _emit 0x65
        _emit 0x67
        _emit 0x8b
        _emit 0x04
        _emit 0x5a
        mov es:[di],ax
        mov bl,[si+1]
        /* AX=GS:[EDX+EBX*2],32-bit address calculation in aUSE16 segment. */
        _emit 0x65
        _emit 0x67
        _emit 0x8b
        _emit 0x04
        _emit 0x5a
        mov es:[di+2],ax
        add si,2
        add di,4
        loop next_pair
tail:
        test count,2
        jz lookup_done
        mov bl,[si]
        /* AX=GS:[EDX+EBX*2],32-bit address calculation in aUSE16 segment. */
        _emit 0x65
        _emit 0x67
        _emit 0x8b
        _emit 0x04
        _emit 0x5a
        mov es:[di],ax
lookup_done:
        _emit 0x0f
        _emit 0xa9
        popf
done:
        pop es
        pop ds
    }
    return 1;
}
