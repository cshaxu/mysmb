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

#define PACK_FOUR(dst,a,b,c,d) \
    _asm mov al,[si+c] \
    _asm mov ah,[si+d] \
    _asm _emit 0x66 \
    _asm _emit 0xc1 \
    _asm _emit 0xe0 \
    _asm _emit 0x10 \
    _asm mov al,[si+a] \
    _asm mov ah,[si+b] \
    _asm _emit 0x66 \
    _asm _emit 0x25 \
    _asm _emit 0x3f \
    _asm _emit 0x3f \
    _asm _emit 0x3f \
    _asm _emit 0x3f \
    _asm _emit 0x66 \
    _asm mov es:[di+dst],ax
#define PACK_TWO(dst,a,b) \
    _asm mov al,[si+a] \
    _asm mov ah,[si+b] \
    _asm and ax,3f3fh \
    _asm mov es:[di+dst],ax
/* Native plane output:no scaling or repeated rows. Fixed word gathers
 * advance each plane sequentially;avoid per-group addressing/32-bit shifts.
 * The bounded code expansion trades instructions for no extra RAM. */
void mysmb_dos16_pack_native_band(const mysmb_io_u8 MYSMB_IO_FAR *source,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 stride,mysmb_io_u16 rows,
    const mysmb_io_u16 MYSMB_IO_FAR *plan)
{
    mysmb_io_u16 left,row_start;
    (void)plan;left=rows;
    _asm {
        push ds
        push es
        lds si,source
        les di,pixels
        mov row_start,di
        mov bx,stride
native_next:
        mov di,row_start
        PACK_TWO(0,0,4) PACK_TWO(2,8,12)
        PACK_TWO(4,16,20) PACK_TWO(6,24,28)
        PACK_TWO(8,32,36) PACK_TWO(10,40,44)
        PACK_TWO(12,48,52) PACK_TWO(14,56,60)
        PACK_TWO(16,64,68) PACK_TWO(18,72,76)
        PACK_TWO(20,80,84) PACK_TWO(22,88,92)
        PACK_TWO(24,96,100) PACK_TWO(26,104,108)
        PACK_TWO(28,112,116) PACK_TWO(30,120,124)
        PACK_TWO(32,128,132) PACK_TWO(34,136,140)
        PACK_TWO(36,144,148) PACK_TWO(38,152,156)
        PACK_TWO(40,160,164) PACK_TWO(42,168,172)
        PACK_TWO(44,176,180) PACK_TWO(46,184,188)
        PACK_TWO(48,192,196) PACK_TWO(50,200,204)
        PACK_TWO(52,208,212) PACK_TWO(54,216,220)
        PACK_TWO(56,224,228) PACK_TWO(58,232,236)
        PACK_TWO(60,240,244) PACK_TWO(62,248,252)
        add di,bx
        PACK_TWO(0,1,5) PACK_TWO(2,9,13)
        PACK_TWO(4,17,21) PACK_TWO(6,25,29)
        PACK_TWO(8,33,37) PACK_TWO(10,41,45)
        PACK_TWO(12,49,53) PACK_TWO(14,57,61)
        PACK_TWO(16,65,69) PACK_TWO(18,73,77)
        PACK_TWO(20,81,85) PACK_TWO(22,89,93)
        PACK_TWO(24,97,101) PACK_TWO(26,105,109)
        PACK_TWO(28,113,117) PACK_TWO(30,121,125)
        PACK_TWO(32,129,133) PACK_TWO(34,137,141)
        PACK_TWO(36,145,149) PACK_TWO(38,153,157)
        PACK_TWO(40,161,165) PACK_TWO(42,169,173)
        PACK_TWO(44,177,181) PACK_TWO(46,185,189)
        PACK_TWO(48,193,197) PACK_TWO(50,201,205)
        PACK_TWO(52,209,213) PACK_TWO(54,217,221)
        PACK_TWO(56,225,229) PACK_TWO(58,233,237)
        PACK_TWO(60,241,245) PACK_TWO(62,249,253)
        add di,bx
        PACK_TWO(0,2,6) PACK_TWO(2,10,14)
        PACK_TWO(4,18,22) PACK_TWO(6,26,30)
        PACK_TWO(8,34,38) PACK_TWO(10,42,46)
        PACK_TWO(12,50,54) PACK_TWO(14,58,62)
        PACK_TWO(16,66,70) PACK_TWO(18,74,78)
        PACK_TWO(20,82,86) PACK_TWO(22,90,94)
        PACK_TWO(24,98,102) PACK_TWO(26,106,110)
        PACK_TWO(28,114,118) PACK_TWO(30,122,126)
        PACK_TWO(32,130,134) PACK_TWO(34,138,142)
        PACK_TWO(36,146,150) PACK_TWO(38,154,158)
        PACK_TWO(40,162,166) PACK_TWO(42,170,174)
        PACK_TWO(44,178,182) PACK_TWO(46,186,190)
        PACK_TWO(48,194,198) PACK_TWO(50,202,206)
        PACK_TWO(52,210,214) PACK_TWO(54,218,222)
        PACK_TWO(56,226,230) PACK_TWO(58,234,238)
        PACK_TWO(60,242,246) PACK_TWO(62,250,254)
        add di,bx
        PACK_TWO(0,3,7) PACK_TWO(2,11,15)
        PACK_TWO(4,19,23) PACK_TWO(6,27,31)
        PACK_TWO(8,35,39) PACK_TWO(10,43,47)
        PACK_TWO(12,51,55) PACK_TWO(14,59,63)
        PACK_TWO(16,67,71) PACK_TWO(18,75,79)
        PACK_TWO(20,83,87) PACK_TWO(22,91,95)
        PACK_TWO(24,99,103) PACK_TWO(26,107,111)
        PACK_TWO(28,115,119) PACK_TWO(30,123,127)
        PACK_TWO(32,131,135) PACK_TWO(34,139,143)
        PACK_TWO(36,147,151) PACK_TWO(38,155,159)
        PACK_TWO(40,163,167) PACK_TWO(42,171,175)
        PACK_TWO(44,179,183) PACK_TWO(46,187,191)
        PACK_TWO(48,195,199) PACK_TWO(50,203,207)
        PACK_TWO(52,211,215) PACK_TWO(54,219,223)
        PACK_TWO(56,227,231) PACK_TWO(58,235,239)
        PACK_TWO(60,243,247) PACK_TWO(62,251,255)
        add si,256
        add row_start,64
        dec left
        jz native_done
        jmp native_next
native_done:
        pop es
        pop ds
    }
}
/* One validated band plan is copied to SS before borrowing source DS. */
void mysmb_dos16_pack_planar_band(const mysmb_io_u8 MYSMB_IO_FAR *source,mysmb_io_u8 MYSMB_IO_FAR *pixels,
    mysmb_io_u16 stride,mysmb_io_u16 rows,const mysmb_io_u16 MYSMB_IO_FAR *plan)
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
        ret
row_mixed:
        mov bx,stride
        PACK_FOUR(0,0,3,6,9)
        PACK_FOUR(4,12,16,19,22)
        PACK_TWO(8,25,28)
        PACK_FOUR(10,32,35,38,41)
        PACK_FOUR(14,44,48,51,54)
        PACK_TWO(18,57,60)
        PACK_FOUR(20,64,67,70,73)
        PACK_FOUR(24,76,80,83,86)
        PACK_TWO(28,89,92)
        PACK_FOUR(30,96,99,102,105)
        PACK_FOUR(34,108,112,115,118)
        PACK_TWO(38,121,124)
        PACK_FOUR(40,128,131,134,137)
        PACK_FOUR(44,140,144,147,150)
        PACK_TWO(48,153,156)
        PACK_FOUR(50,160,163,166,169)
        PACK_FOUR(54,172,176,179,182)
        PACK_TWO(58,185,188)
        PACK_FOUR(60,192,195,198,201)
        PACK_FOUR(64,204,208,211,214)
        PACK_TWO(68,217,220)
        PACK_FOUR(70,224,227,230,233)
        PACK_FOUR(74,236,240,243,246)
        PACK_TWO(78,249,252)
        add di,bx
        PACK_FOUR(0,0,4,7,10)
        PACK_FOUR(4,13,16,20,23)
        PACK_TWO(8,26,29)
        PACK_FOUR(10,32,36,39,42)
        PACK_FOUR(14,45,48,52,55)
        PACK_TWO(18,58,61)
        PACK_FOUR(20,64,68,71,74)
        PACK_FOUR(24,77,80,84,87)
        PACK_TWO(28,90,93)
        PACK_FOUR(30,96,100,103,106)
        PACK_FOUR(34,109,112,116,119)
        PACK_TWO(38,122,125)
        PACK_FOUR(40,128,132,135,138)
        PACK_FOUR(44,141,144,148,151)
        PACK_TWO(48,154,157)
        PACK_FOUR(50,160,164,167,170)
        PACK_FOUR(54,173,176,180,183)
        PACK_TWO(58,186,189)
        PACK_FOUR(60,192,196,199,202)
        PACK_FOUR(64,205,208,212,215)
        PACK_TWO(68,218,221)
        PACK_FOUR(70,224,228,231,234)
        PACK_FOUR(74,237,240,244,247)
        PACK_TWO(78,250,253)
        add di,bx
        PACK_FOUR(0,1,4,8,11)
        PACK_FOUR(4,14,17,20,24)
        PACK_TWO(8,27,30)
        PACK_FOUR(10,33,36,40,43)
        PACK_FOUR(14,46,49,52,56)
        PACK_TWO(18,59,62)
        PACK_FOUR(20,65,68,72,75)
        PACK_FOUR(24,78,81,84,88)
        PACK_TWO(28,91,94)
        PACK_FOUR(30,97,100,104,107)
        PACK_FOUR(34,110,113,116,120)
        PACK_TWO(38,123,126)
        PACK_FOUR(40,129,132,136,139)
        PACK_FOUR(44,142,145,148,152)
        PACK_TWO(48,155,158)
        PACK_FOUR(50,161,164,168,171)
        PACK_FOUR(54,174,177,180,184)
        PACK_TWO(58,187,190)
        PACK_FOUR(60,193,196,200,203)
        PACK_FOUR(64,206,209,212,216)
        PACK_TWO(68,219,222)
        PACK_FOUR(70,225,228,232,235)
        PACK_FOUR(74,238,241,244,248)
        PACK_TWO(78,251,254)
        add di,bx
        PACK_FOUR(0,2,5,8,12)
        PACK_FOUR(4,15,18,21,24)
        PACK_TWO(8,28,31)
        PACK_FOUR(10,34,37,40,44)
        PACK_FOUR(14,47,50,53,56)
        PACK_TWO(18,60,63)
        PACK_FOUR(20,66,69,72,76)
        PACK_FOUR(24,79,82,85,88)
        PACK_TWO(28,92,95)
        PACK_FOUR(30,98,101,104,108)
        PACK_FOUR(34,111,114,117,120)
        PACK_TWO(38,124,127)
        PACK_FOUR(40,130,133,136,140)
        PACK_FOUR(44,143,146,149,152)
        PACK_TWO(48,156,159)
        PACK_FOUR(50,162,165,168,172)
        PACK_FOUR(54,175,178,181,184)
        PACK_TWO(58,188,191)
        PACK_FOUR(60,194,197,200,204)
        PACK_FOUR(64,207,210,213,216)
        PACK_TWO(68,220,223)
        PACK_FOUR(70,226,229,232,236)
        PACK_FOUR(74,239,242,245,248)
        PACK_TWO(78,252,255)
plane_done:
        ret
band_done:
        pop es
        pop ds
    }
}

#undef PACK_FOUR
#undef PACK_TWO
