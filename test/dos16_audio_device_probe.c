/* DOSBox/real-DOS Sound Blaster route witness.  Its exit code proves that the
 * product's DSP/DMA binding stayed live through two seconds of paced source
 * frames; the batch wrapper records the result outside the executable. */
#include "platform/dos16/dos_audio.h"

static unsigned long bios_ticks(void)
{ return *(volatile unsigned long far *)0x0040006cUL; }

int main(void)
{
    struct mysmb_io_audio_frame frame;
    unsigned long tick;
    unsigned short phase=0U,cycle;
    unsigned index;
    for(index=0U;index<sizeof(frame);++index)((unsigned char *)&frame)[index]=0U;
    if(!mysmb_dos16_audio_dos_open() || !mysmb_dos16_audio_dos_prepared())return 1;
    frame.write_count=4U;
    frame.writes[0].index=21U;frame.writes[0].value=1U;
    frame.writes[1].index=0U;frame.writes[1].value=0xdfU;
    frame.writes[2].index=2U;frame.writes[2].value=0x41U;
    frame.writes[3].index=3U;frame.writes[3].value=0xf8U;
    tick=bios_ticks();
    for(cycle=0U;cycle<36U;++cycle) {
        phase=(unsigned short)(phase+60U);
        while(phase>=18U) {
            if(mysmb_dos16_audio_dos_submit(&frame)!=MYSMB_IO_AUDIO_AVAILABLE) {
                mysmb_dos16_audio_dos_close();return 2;
            }
            frame.write_count=0U;phase=(unsigned short)(phase-18U);
        }
        while(bios_ticks()==tick){}
        tick=bios_ticks();
    }
    mysmb_dos16_audio_dos_close();return 0;
}
