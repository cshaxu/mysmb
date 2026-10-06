#include "platform/dos16/planar_row.h"
/* 486SX real-mode DWORD bulk operations; addressing remains USE16.
 * Neutral row packing:borrow source/destination segments once, restore them
 * before returning to C. Plane stride is bounded by the validated caller. */
void mysmb_dos16_pack_planar_row(const mysmb_io_u8 MYSMB_IO_FAR *source,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 stride)
{
    _asm {
        push ds
        push es
        lds si,source
        les di,pixels
        mov bx,di
        mov ax,[si]
        cmp al,ah
        jne row_mixed
        cmp [si+254],ax
        jne row_mixed
        push es
        push ds
        pop es
        mov di,si
        mov al,[si]
        mov ah,al
        mov dx,ax
        /* SHL EAX,16: explicit operand size in a USE16 segment. */
        _emit 0x66
        _emit 0xc1
        _emit 0xe0
        _emit 0x10
        mov ax,dx
        mov cx,64
        cld
        _emit 0x66
        repe scasw
        pop es
        mov di,bx
        jnz row_mixed
        and al,3fh
        mov ah,al
        mov dx,ax
        /* SHL EAX,16: explicit operand size in a USE16 segment. */
        _emit 0x66
        _emit 0xc1
        _emit 0xe0
        _emit 0x10
        mov ax,dx
        mov bx,stride
        sub bx,80
        mov dx,4
row_uniform:
        mov cx,20
        _emit 0x66
        rep stosw
        add di,bx
        dec dx
        jnz row_uniform
        jmp plane_done
row_mixed:
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

/* One validated band plan is copied to SS before borrowing source DS. */
void mysmb_dos16_pack_planar_band(const mysmb_io_u8 MYSMB_IO_FAR *source,mysmb_io_u8 MYSMB_IO_FAR *pixels,
    mysmb_io_u16 stride,mysmb_io_u16 rows,const mysmb_io_u16 far *plan)
{
    mysmb_io_u16 offsets[16],map_pointer,row_start,source_base,left;
    left=rows;
    _asm {
        push ds
        push es
        lds si,plan
        lea bx,offsets
        mov cx,rows
band_plan_copy:
        mov ax,[si]
        mov ss:[bx],ax
        add si,2
        add bx,2
        loop band_plan_copy
        lds si,source
        les di,pixels
        mov source_base,si
        mov row_start,di
        lea bx,offsets
        mov map_pointer,bx
band_next:
        mov bx,map_pointer
        mov ax,ss:[bx]
        add bx,2
        mov map_pointer,bx
        mov di,row_start
        cmp ax,0ffffh
        je band_repeat
        mov si,source_base
        add si,ax
        call band_pack
        jmp band_advance
band_repeat:
        push ds
        push es
        pop ds
        mov si,di
        sub si,80
        mov bx,stride
        sub bx,80
        mov dx,4
band_copy:
        mov cx,20
        cld
        _emit 0x66
        rep movsw
        add si,bx
        add di,bx
        dec dx
        jnz band_copy
        pop ds
band_advance:
        add row_start,80
        dec left
        jnz band_next
        jmp band_done
band_pack:
        mov bx,di
        mov ax,[si]
        cmp al,ah
        jne row_mixed
        cmp [si+254],ax
        jne row_mixed
        push es
        push ds
        pop es
        mov di,si
        mov al,[si]
        mov ah,al
        mov dx,ax
        /* SHL EAX,16: explicit operand size in a USE16 segment. */
        _emit 0x66
        _emit 0xc1
        _emit 0xe0
        _emit 0x10
        mov ax,dx
        mov cx,64
        cld
        _emit 0x66
        repe scasw
        pop es
        mov di,bx
        jnz row_mixed
        and al,3fh
        mov ah,al
        mov dx,ax
        /* SHL EAX,16: explicit operand size in a USE16 segment. */
        _emit 0x66
        _emit 0xc1
        _emit 0xe0
        _emit 0x10
        mov ax,dx
        mov bx,stride
        sub bx,80
        mov dx,4
row_uniform:
        mov cx,20
        _emit 0x66
        rep stosw
        add di,bx
        dec dx
        jnz row_uniform
        jmp plane_done
row_mixed:
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
        ret
band_done:
        pop es
        pop ds
    }
}
