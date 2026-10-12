#ifndef MYSMB_DOS16_PIT_CLOCK_H
#define MYSMB_DOS16_PIT_CLOCK_H
#include "io/types.h"
/* Decode the BIOS-owned 65536-count PIT cycle,without programming the timer. */
mysmb_io_u16 mysmb_dos16_pit_phase(mysmb_io_u8 status, mysmb_io_u16 count);
#endif
