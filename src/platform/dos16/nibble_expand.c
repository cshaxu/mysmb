#include "platform/dos16/nibble_expand.h"
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
        mov cx,count
        shr cx,1
        shr cx,1
        jcxz tail
next_pair:
        mov al,[si]
        mov ah,al
        and al,0fh
        /* SHR AH,4 in a USE16 segment, supported by the486 target. */
        _emit 0xc0
        _emit 0xec
        _emit 0x04
        mov es:[di],ax
        mov al,[si+1]
        mov ah,al
        and al,0fh
        _emit 0xc0
        _emit 0xec
        _emit 0x04
        mov es:[di+2],ax
        add si,2
        add di,4
        loop next_pair
tail:
        test count,2
        jz done
        mov al,[si]
        mov ah,al
        and al,0fh
        _emit 0xc0
        _emit 0xec
        _emit 0x04
        mov es:[di],ax
        jmp done
done:
        pop es
        pop ds
    }
    return 1;
}
