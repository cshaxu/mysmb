#ifndef MYSMB_GAME_FRAME_SNAPSHOT_H
#define MYSMB_GAME_FRAME_SNAPSHOT_H

#include "core/game.h"

/*
 * M2 T9 canonical output record.  This is deliberately a record of the
 * translated game's visible state, not an NES PPU interface.  captured_fields
 * says which bytes were copied into this record.  verified_fields is reserved
 * for a source-owned route that has passed the owner-local reference oracle;
 * a populated byte array never implies output equivalence by itself.
 */
enum {
    MYSMB_FRAME_SNAPSHOT_CPU_RAM = 0x0001U,
    MYSMB_FRAME_SNAPSHOT_NAME_TABLES = 0x0002U,
    MYSMB_FRAME_SNAPSHOT_PALETTE = 0x0004U,
    MYSMB_FRAME_SNAPSHOT_OAM = 0x0008U,
    MYSMB_FRAME_SNAPSHOT_PPU_STATE = 0x0010U,
    MYSMB_FRAME_SNAPSHOT_AUDIO = 0x0020U,
    MYSMB_FRAME_SNAPSHOT_REQUIRED = 0x003fU,
    MYSMB_FRAME_SNAPSHOT_AUDIO_BYTES = 14
};

struct mysmb_frame_snapshot {
    mysmb_u32 sequence;
    mysmb_u16 captured_fields;
    mysmb_u16 verified_fields;
    mysmb_u8 cpu_ram[0x0800U];
    mysmb_u8 name_table[2][0x0400U];
    mysmb_u8 palette[0x20U];
    mysmb_u8 oam[0x0100U];
    mysmb_u8 ppu_control_0;
    mysmb_u8 ppu_control_1;
    mysmb_u8 ppu_name_table;
    mysmb_u8 scroll_x;
    mysmb_u8 scroll_y;
    mysmb_u8 ppu_mask;
    /* PPU v after the committed scroll/name-table transfer. */
    mysmb_u16 ppu_address;
    mysmb_u8 audio[MYSMB_FRAME_SNAPSHOT_AUDIO_BYTES];
};

void mysmb_frame_snapshot_capture(const struct mysmb_game *game,
                                  struct mysmb_frame_snapshot *snapshot);
mysmb_u8 mysmb_frame_snapshot_is_complete(
    const struct mysmb_frame_snapshot *snapshot);

#endif
