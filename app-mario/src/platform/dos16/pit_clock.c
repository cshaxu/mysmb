#include "platform/dos16/pit_clock.h"
mysmb_io_u16 mysmb_dos16_pit_phase(mysmb_io_u8 status, mysmb_io_u16 count)
{
    mysmb_io_u8 mode;
    mysmb_io_u16 elapsed;
    mode=(mysmb_io_u8)((status>>1U)&7U);
    if (mode>=6U) mode=(mysmb_io_u8)(mode-4U);
    elapsed=(mysmb_io_u16)(0U-count);
    /* Intel8254 mode3 decrements twice per clock and reloads every half cycle.
     * Its latched OUT bit distinguishes the two halves. */
    if (mode==3U)
        return (mysmb_io_u16)(elapsed/2U+((status&0x80U)!=0U ? 0U:32768U));
    if (mode==2U) return elapsed;
    return 0U;
}
