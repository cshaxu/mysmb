#include "platform/dos16/pit_clock.h"
mygames_kvm_u16 mysmb_dos16_pit_phase(mygames_kvm_u8 status, mygames_kvm_u16 count)
{
    mygames_kvm_u8 mode;
    mygames_kvm_u16 elapsed;
    mode=(mygames_kvm_u8)((status>>1U)&7U);
    if (mode>=6U) mode=(mygames_kvm_u8)(mode-4U);
    elapsed=(mygames_kvm_u16)(0U-count);
    /* Intel8254 mode3 decrements twice per clock and reloads every half cycle.
     * Its latched OUT bit distinguishes the two halves. */
    if (mode==3U)
        return (mygames_kvm_u16)(elapsed/2U+((status&0x80U)!=0U ? 0U:32768U));
    if (mode==2U) return elapsed;
    return 0U;
}
