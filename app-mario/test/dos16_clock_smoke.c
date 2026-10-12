#include "platform/dos16/pit_clock.h"
int main(void)
{
    unsigned long t;
    mysmb_io_u16 count, expected;
    mysmb_io_u8 status;
    for (t=0UL;t<65536UL;++t) {
        expected=(mysmb_io_u16)t;
        count=(mysmb_io_u16)(0UL-2UL*(t%32768UL));
        status=(mysmb_io_u8)(0x36U|(t<32768UL ? 0x80U:0U));
        if (mysmb_dos16_pit_phase(status,count)!=expected) return 1;
        if (mysmb_dos16_pit_phase((mysmb_io_u8)(status|8U),count)!=expected) return 2;
        count=(mysmb_io_u16)(0UL-t);
        if (mysmb_dos16_pit_phase(0x34U,count)!=expected) return 3;
    }
    return 0;
}
