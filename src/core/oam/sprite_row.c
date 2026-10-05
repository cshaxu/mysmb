#include "core/oam/oam.h"
#include "core/objects.h"

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
