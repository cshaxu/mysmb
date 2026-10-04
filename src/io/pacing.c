#include "io/pacing.h"
void mysmb_io_pacing_initialize(struct mysmb_io_pacing *pacing,
    unsigned long now, unsigned long period)
{
    pacing->last=now&0xffffffffUL;
    pacing->period=period;
}
unsigned long mysmb_io_pacing_remaining(struct mysmb_io_pacing *pacing,
    unsigned long now)
{
    unsigned long elapsed;
    now&=0xffffffffUL;
    elapsed=(now-pacing->last)&0xffffffffUL;
    if (pacing->period==0UL || pacing->period>0x7fffffffUL) return 0UL;
    if (elapsed<pacing->period) return pacing->period-elapsed;
    /* Keep ordinary fractional lateness,discard missed-frame backlog. */
    if (elapsed<pacing->period*2UL)
        pacing->last=(pacing->last+pacing->period)&0xffffffffUL;
    else pacing->last=now;
    return 0UL;
}
