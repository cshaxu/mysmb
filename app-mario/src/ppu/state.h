#ifndef MYSMB_PPU_STATE_H
#define MYSMB_PPU_STATE_H
#include "io/types.h"

/* One addressed/visible PPU storage owner. CPU RAM and source NMI decisions
 * remain in core;the compositor borrows this state without copying it. */
struct mysmb_ppu_state {
    /* Addressed nametables2000..27ff;vertical mirrors remain in core writes. */
    mysmb_io_u8 name_table[2][0x0400U];
    /* NMI4014-latched OAM;CPU RAM0200..02ff remains next-frame producer. */
    mysmb_io_u8 visible_oam[0x0100U];
    mysmb_io_u8 palette[0x20U];
    /* Addressed output/mirrors and independently committed NMI-visible phase. */
    mysmb_io_u8 ppu_control_0,ppu_mask,ppu_name_table,scroll_x,scroll_y;
    mysmb_io_u8 visible_ppu_control_0,visible_ppu_mask,visible_ppu_name_table;
    mysmb_io_u8 visible_scroll_x,visible_scroll_y,visible_sprite0_split;
    /* Immutable local pattern binding;borrowed for the game lifetime. */
    const mysmb_io_u8 *chr_data;
    mysmb_io_u16 chr_data_size;
};

/* Original DMA source span is CPU RAM0200..02ff;caller owns commit timing. */
void mysmb_ppu_state_submit_oam(struct mysmb_ppu_state *state,
    const mysmb_io_u8 *source);
#endif
