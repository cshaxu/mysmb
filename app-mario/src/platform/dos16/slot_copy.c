#include "platform/dos16/slot_copy.h"
/* The PPU has selected bounded, non-overlapping source slots. The adapter
 * only moves these already-decided bytes;each row uses DWORD bulk copies and
 * no game, PPU-state, palette, or frame-policy decision. */
#ifdef MYSMB_DOS16_TARGET
static void copy_rows(const mysmb_io_u8 MYSMB_IO_FAR *first,
    const mysmb_io_u8 MYSMB_IO_FAR *second,mysmb_io_u8 MYSMB_IO_FAR *destination,
    mysmb_io_u16 first_count,mysmb_io_u16 second_count,mysmb_io_u16 rows)
{
    _asm {
        push ds
        push es
        les di,destination
        cld
        or second_count,0
        jnz split_rows
        /* A complete source span covers every row.  Borrow its segments once
         * for the whole submitted band instead of reloading them per row. */
        lds si,first
        mov cx,rows
        shl cx,1
        shl cx,1
        shl cx,1
        shl cx,1
        shl cx,1
        shl cx,1
        _emit 0x66
        rep movsw
        jmp done
split_rows:
        mov dx,rows
row_part:
        lds si,first
        mov cx,first_count
        shr cx,1
        shr cx,1
        _emit 0x66
        rep movsw
        mov cx,first_count
        and cx,3
        jz next_part
        rep movsb
next_part:
        add word ptr first,256
        adc word ptr first+2,0
        push ds
        lds si,second
        mov cx,second_count
        shr cx,1
        shr cx,1
        _emit 0x66
        rep movsw
        mov cx,second_count
        and cx,3
        rep movsb
        pop ds
        add word ptr second,256
        adc word ptr second+2,0
        dec dx
        jnz row_part
done:
        pop es
        pop ds
    }
}
#endif
int mysmb_dos16_slot_rows_copy(const mysmb_io_u8 MYSMB_IO_FAR *first,
    const mysmb_io_u8 MYSMB_IO_FAR *second,mysmb_io_u8 MYSMB_IO_FAR *destination,
    mysmb_io_u16 first_count,mysmb_io_u16 second_count,mysmb_io_u16 rows)
{
    if(!first || !destination || !rows || rows>16U || first_count+second_count!=256U ||
        (second_count && !second))return 0;
#ifdef MYSMB_DOS16_TARGET
    copy_rows(first,second,destination,first_count,second_count,rows);
    return 1;
#else
    (void)first;(void)second;(void)destination;(void)first_count;
    (void)second_count;(void)rows;
    return 0;
#endif
}
