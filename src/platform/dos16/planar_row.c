#include "platform/dos16/planar_row.h"
/* Neutral row packing:borrow source/destination segments once, restore them
 * before returning to C. Plane stride is bounded by the validated caller. */
void mysmb_dos16_pack_planar_row(const mysmb_io_u8 MYSMB_IO_FAR *source,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 stride)
{
    _asm {
        push ds
        push es
        lds si,source
        les di,pixels
        mov bx,stride
        mov dx,bx
        add dx,bx
        add dx,bx
        mov cx,16
plane_group:
        mov al,[si+0]
        mov ah,[si+3]
        and ax,3f3fh
        mov es:[di+0],ax
        mov al,[si+6]
        mov ah,[si+9]
        and ax,3f3fh
        mov es:[di+2],ax
        mov al,[si+12]
        and al,3fh
        mov es:[di+4],al
        add di,bx
        mov al,[si+0]
        mov ah,[si+4]
        and ax,3f3fh
        mov es:[di+0],ax
        mov al,[si+7]
        mov ah,[si+10]
        and ax,3f3fh
        mov es:[di+2],ax
        mov al,[si+13]
        and al,3fh
        mov es:[di+4],al
        add di,bx
        mov al,[si+1]
        mov ah,[si+4]
        and ax,3f3fh
        mov es:[di+0],ax
        mov al,[si+8]
        mov ah,[si+11]
        and ax,3f3fh
        mov es:[di+2],ax
        mov al,[si+14]
        and al,3fh
        mov es:[di+4],al
        add di,bx
        mov al,[si+2]
        mov ah,[si+5]
        and ax,3f3fh
        mov es:[di+0],ax
        mov al,[si+8]
        mov ah,[si+12]
        and ax,3f3fh
        mov es:[di+2],ax
        mov al,[si+15]
        and al,3fh
        mov es:[di+4],al
        sub di,dx
        add di,5
        add si,16
        dec cx
        jz plane_done
        jmp plane_group
plane_done:
        pop es
        pop ds
    }
}
