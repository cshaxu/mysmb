#include "core/oam/oam.h"

/* ROM DrawSpriteObject / NoHFlip / SetHFAt.  X is the caller's graphics
 * table index and Y is its OAM byte offset.  They are CPU registers, so
 * the C caller owns their variables; $00-$05 and OAM are game RAM. */
void mysmb_oam_draw_sprite_object(struct mysmb_game *game,
                                  mysmb_u8 *graphics_index,
                                  mysmb_u8 *oam_offset)
{
    mysmb_u16 first;
    mysmb_u16 second;
    mysmb_u8 attributes;
    mysmb_u8 left_tile;
    mysmb_u8 right_tile;

    first = (mysmb_u16)(0x0200U + *oam_offset);
    second = (mysmb_u16)(first + 4U);
    left_tile = game->ram[0U];
    right_tile = game->ram[1U];
    attributes = game->ram[4U];
    if ((game->ram[3U] & 2U) != 0U) {
        game->ram[(mysmb_u16)(second + 1U)] = left_tile;
        game->ram[(mysmb_u16)(first + 1U)] = right_tile;
        attributes = (mysmb_u8)(attributes | 0x40U);
    }
    else {
        game->ram[(mysmb_u16)(first + 1U)] = left_tile;
        game->ram[(mysmb_u16)(second + 1U)] = right_tile;
    }
    game->ram[(mysmb_u16)(first + 2U)] = attributes;
    game->ram[(mysmb_u16)(second + 2U)] = attributes;
    game->ram[first] = game->ram[2U];
    game->ram[second] = game->ram[2U];
    game->ram[(mysmb_u16)(first + 3U)] = game->ram[5U];
    game->ram[(mysmb_u16)(second + 3U)] = (mysmb_u8)(game->ram[5U] + 8U);
    game->ram[2U] = (mysmb_u8)(game->ram[2U] + 8U);
    *oam_offset = (mysmb_u8)(*oam_offset + 8U);
    *graphics_index = (mysmb_u8)(*graphics_index + 2U);
}
