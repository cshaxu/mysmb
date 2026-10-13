#include "dos16/pit_clock.h"
int main(void)
{
    unsigned long t;
    mygames_kvm_u16 count, expected;
    mygames_kvm_u8 status;
    for (t=0UL;t<65536UL;++t) {
        expected=(mygames_kvm_u16)t;
        count=(mygames_kvm_u16)(0UL-2UL*(t%32768UL));
        status=(mygames_kvm_u8)(0x36U|(t<32768UL ? 0x80U:0U));
        if (mygames_dos16_pit_phase(status,count)!=expected) return 1;
        if (mygames_dos16_pit_phase((mygames_kvm_u8)(status|8U),count)!=expected) return 2;
        count=(mygames_kvm_u16)(0UL-t);
        if (mygames_dos16_pit_phase(0x34U,count)!=expected) return 3;
    }
    if(mygames_dos16_pit_phase(0U,100U)!=0U)return 4;
    if(mygames_dos16_pit_phase(0x3eU,0xfffeU)!=32769U)return 5;
    return 0;
}
