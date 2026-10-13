#ifndef MYGAMES_WIN16_CLOCK_H
#define MYGAMES_WIN16_CLOCK_H
#include "kvm/types.h"
struct mygames_win16_clock {unsigned long last,credit;};
void mygames_win16_clock_reset(struct mygames_win16_clock *clock,unsigned long now);
/* At most four 60-Hz ticks per dispatch; remaining debt is retained. */
mygames_kvm_u8 mygames_win16_clock_step(struct mygames_win16_clock *clock,
    unsigned long now);
#endif
