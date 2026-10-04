#include "io/pacing.h"
int main(void)
{
    struct mysmb_io_pacing clock;
    mysmb_io_pacing_initialize(&clock,1000UL,100UL);
    if (mysmb_io_pacing_remaining(&clock,1030UL)!=70UL) return 1;
    if (mysmb_io_pacing_remaining(&clock,1107UL)!=0UL || clock.last!=1100UL) return 2;
    if (mysmb_io_pacing_remaining(&clock,1140UL)!=60UL) return 3;
    if (mysmb_io_pacing_remaining(&clock,1700UL)!=0UL || clock.last!=1700UL) return 4;
    if (mysmb_io_pacing_remaining(&clock,1720UL)!=80UL) return 5;
    mysmb_io_pacing_initialize(&clock,0xfffffff0UL,32UL);
    if (mysmb_io_pacing_remaining(&clock,0UL)!=16UL) return 6;
    if (mysmb_io_pacing_remaining(&clock,0x11UL)!=0UL || clock.last!=0x10UL) return 7;
    if (mysmb_io_pacing_remaining(&clock,0x15UL)!=27UL) return 8;
    /* BIOS midnight/reset is a discontinuity,not a huge catch-up loop. */
    if (mysmb_io_pacing_remaining(&clock,0UL)!=0UL || clock.last!=0UL) return 9;
    mysmb_io_pacing_initialize(&clock,1UL,0UL);
    return mysmb_io_pacing_remaining(&clock,1UL)==0UL ? 0:10;
}
