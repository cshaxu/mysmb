#include "platform/win16/scheduler.h"
int main(void)
{
    struct mysmb_win16_scheduler clock;
    mysmb_win16_scheduler_reset(&clock,100UL);
    if(mysmb_win16_scheduler_step(&clock,110UL)!=0U || clock.credit!=600UL)return 1;
    if(mysmb_win16_scheduler_step(&clock,150UL)!=3U || clock.credit)return 2;
    if(mysmb_win16_scheduler_step(&clock,300UL)!=4U || clock.credit!=5000UL)return 3;
    if(mysmb_win16_scheduler_step(&clock,300UL)!=4U ||
        mysmb_win16_scheduler_step(&clock,300UL)!=1U || clock.credit)return 4;
    mysmb_win16_scheduler_reset(&clock,0xfffffff0UL);
    if(mysmb_win16_scheduler_step(&clock,0x10UL)!=1U || clock.credit!=920UL)return 5;
    if(mysmb_win16_scheduler_step(&clock,0UL)!=0U || clock.credit)return 6;
    return 0;
}
