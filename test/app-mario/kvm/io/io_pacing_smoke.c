#include "io/pacing.h"
int main(void)
{
    struct mysmb_io_pacing clock;
    struct mysmb_io_pacing publication;
    unsigned long tick;
    unsigned int published=0U;
    mysmb_io_pacing_initialize(&publication,1000UL,100UL);
    if(mysmb_io_pacing_video_due(&publication,1099UL,0))return 11;
    if(!mysmb_io_pacing_video_due(&publication,1100UL,0))return 12;
    if(!mysmb_io_pacing_video_due(&publication,1101UL,1))return 13;
    /* Persistent lateness still publishes the latest available state. */
    for(tick=1102UL;tick<=1601UL;++tick)
        published+=(unsigned int)mysmb_io_pacing_video_due(&publication,tick,0);
    if(published!=5U || publication.last!=1601UL)return 14;
    mysmb_io_pacing_initialize(&publication,0xfffffff0UL,32UL);
    if(mysmb_io_pacing_video_due(&publication,0UL,0) ||
        !mysmb_io_pacing_video_due(&publication,0x10UL,0))return 15;
    if(!mysmb_io_pacing_video_due(&publication,0UL,0))return 16;
    mysmb_io_pacing_initialize(&clock,1000UL,100UL);
    if (mysmb_io_pacing_remaining(&clock,1030UL)!=70UL) return 1;
    if (mysmb_io_pacing_remaining(&clock,1107UL)!=0UL || clock.last!=1100UL) return 2;
    if (mysmb_io_pacing_remaining(&clock,1140UL)!=60UL) return 3;
    if (!mysmb_io_pacing_late(&clock,1200UL)) return 4;
    mysmb_io_pacing_advance(&clock,1200UL);
    if (clock.last!=1200UL || mysmb_io_pacing_late(&clock,1250UL)) return 5;
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
