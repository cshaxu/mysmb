#include "game/oam/oam.h"
#include "game/objects.h"

/* ROM $ec4a MoveColOffscreen; Y is a byte, absolute indexed stores are not. */
mysmb_u8 mysmb_oam_move_column_offscreen(struct mysmb_game *game, mysmb_u8 oam)
{
    game->ram[0x0200U + oam] = 0xf8U;
    game->ram[0x0208U + oam] = 0xf8U;
    return 0xf8U;
}

/* ROM $ebc1 MoveESprColOffscreen: wrap the addition once, before the leaf. */
void mysmb_oam_move_enemy_column_offscreen(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 column)
{
    mysmb_u8 oam, value;
    oam = (mysmb_u8)(column + game->ram[0x06e5U + slot]);
    value = mysmb_oam_move_column_offscreen(game, oam);
    game->ram[0x0210U + oam] = value;
}

/* ROM $ebb7 MoveESprRowOffscreen tail-calls DumpTwoSpr. */
void mysmb_oam_move_enemy_row_offscreen(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 row)
{
    mysmb_u8 oam;
    oam = (mysmb_u8)(row + game->ram[0x06e5U + slot]);
    mysmb_oam_dump_two_sprites(game, 0xf8U, oam);
}

/* ROM $eb64 SprObjectOffscrChk calls columns, then rows, in source order. */
void mysmb_oam_sprite_object_offscreen_check(struct mysmb_game *game,
                                              mysmb_u8 oam_offset)
{
    mysmb_u8 slot;
    mysmb_u8 bits;

    slot = game->ram[8U];
    bits = game->ram[0x03d1U];
    (void)oam_offset;
    if ((bits & 4U) != 0U)
        mysmb_oam_move_enemy_column_offscreen(game, slot, 4U);
    if ((bits & 8U) != 0U)
        mysmb_oam_move_enemy_column_offscreen(game, slot, 0U);
    if ((bits & 0x20U) != 0U)
        mysmb_oam_move_enemy_row_offscreen(game, slot, 0x10U);
    if ((bits & 0x40U) != 0U)
        mysmb_oam_move_enemy_row_offscreen(game, slot, 8U);
    if ((bits & 0x80U) != 0U) {
        mysmb_oam_move_enemy_row_offscreen(game, slot, 0U);
        if (game->ram[0x0016U + slot] != 12U &&
            game->ram[0x00b6U + slot] == 2U)
            mysmb_objects_erase_enemy(game, slot);
    }
}

/* ROM $ebb2 DrawOneSpriteRow stores incoming A before its tail call. */
void mysmb_oam_draw_one_sprite_row(struct mysmb_game *game,
                                    mysmb_u8 right_tile,
                                    mysmb_u8 *graphics_index,
                                    mysmb_u8 *oam_offset)
{
    game->ram[1U] = right_tile;
    mysmb_oam_draw_sprite_object(game, graphics_index, oam_offset);
}

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
