#ifndef MYSMB_PLATFORM_DOS16_SLOT_COPY_H
#define MYSMB_PLATFORM_DOS16_SLOT_COPY_H
#include "ppu/frame.h"
/* Physical-only equivalent of the neutral 256-slot-row contract. */
int mysmb_dos16_slot_rows_copy(const mysmb_io_u8 MYSMB_IO_FAR *first,
    const mysmb_io_u8 MYSMB_IO_FAR *second,mysmb_io_u8 MYSMB_IO_FAR *destination,
    mysmb_io_u16 first_count,mysmb_io_u16 second_count,mysmb_io_u16 rows);
#endif
