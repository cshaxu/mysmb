#ifndef MYSMB_WIN16_SCHEDULER_H
#define MYSMB_WIN16_SCHEDULER_H
#include "kvm/types.h"
struct mysmb_win16_scheduler {unsigned long last,credit;};
void mysmb_win16_scheduler_reset(struct mysmb_win16_scheduler *clock,unsigned long now);
/* At most four 60-Hz ticks per dispatch; remaining debt is retained. */
mygames_kvm_u8 mysmb_win16_scheduler_step(struct mysmb_win16_scheduler *clock,
    unsigned long now);
#endif
