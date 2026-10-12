#ifndef MYSMB_DOS16_PIT_CLOCK_H
#define MYSMB_DOS16_PIT_CLOCK_H
#include "kvm/types.h"
/* Decode the BIOS-owned 65536-count PIT cycle,without programming the timer. */
mygames_kvm_u16 mysmb_dos16_pit_phase(mygames_kvm_u8 status, mygames_kvm_u16 count);
#endif
