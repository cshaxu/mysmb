#include "ppu/state.h"

void mysmb_ppu_state_submit_oam(struct mysmb_ppu_state *state,
    const mygames_kvm_u8 *source)
{
    mygames_kvm_u16 offset;
    for(offset=0U;offset<0x0100U;++offset)
        state->visible_oam[offset]=source[offset];
}
