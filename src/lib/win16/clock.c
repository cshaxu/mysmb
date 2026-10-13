#include "win16/clock.h"
void mygames_win16_clock_reset(struct mygames_win16_clock *clock,unsigned long now)
{clock->last=now&0xffffffffUL;clock->credit=0UL;}
mygames_kvm_u8 mygames_win16_clock_step(struct mygames_win16_clock *clock,
    unsigned long now)
{
    unsigned long elapsed=(now-clock->last)&0xffffffffUL;
    mygames_kvm_u8 count=0U;
    clock->last=now&0xffffffffUL;
    if(elapsed>0x7fffffffUL){clock->credit=0UL;return 0U;}
    /* Ordinary timer gaps are short; wide arithmetic avoids 16-bit overflow. */
    clock->credit+=elapsed*60UL;
    while(clock->credit>=1000UL && count<4U){clock->credit-=1000UL;++count;}
    return count;
}
