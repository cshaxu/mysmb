#include "win16/clock.h"
int main(void)
{
    struct mygames_win16_clock clock;
    mygames_win16_clock_reset(&clock,100UL);
    if(mygames_win16_clock_step(&clock,110UL)!=0U || clock.credit!=600UL)return 1;
    if(mygames_win16_clock_step(&clock,150UL)!=3U || clock.credit)return 2;
    if(mygames_win16_clock_step(&clock,300UL)!=4U || clock.credit!=5000UL)return 3;
    if(mygames_win16_clock_step(&clock,300UL)!=4U ||
        mygames_win16_clock_step(&clock,300UL)!=1U || clock.credit)return 4;
    mygames_win16_clock_reset(&clock,0xfffffff0UL);
    if(mygames_win16_clock_step(&clock,0x10UL)!=1U || clock.credit!=920UL)return 5;
    if(mygames_win16_clock_step(&clock,0UL)!=0U || clock.credit)return 6;
    return 0;
}
