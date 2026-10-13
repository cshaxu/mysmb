#ifndef MYGAMES_DOS16_PIT_CLOCK_H
#define MYGAMES_DOS16_PIT_CLOCK_H

#include "kvm/types.h"

mygames_kvm_u16 mygames_dos16_pit_phase(mygames_kvm_u8 status,
    mygames_kvm_u16 count);

#endif
