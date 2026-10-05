#include "ppu/state.h"

void mysmb_ppu_state_submit_oam(struct mysmb_ppu_state *state,
    const mysmb_io_u8 *source)
{
    mysmb_io_u16 offset;
    for(offset=0U;offset<0x0100U;++offset)
        state->visible_oam[offset]=source[offset];
}
