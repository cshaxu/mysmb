#ifndef MYSMB_GAME_OAM_ENEMY_OFFSCREEN_TAIL_H
#define MYSMB_GAME_OAM_ENEMY_OFFSCREEN_TAIL_H

#include "game/oam/oam.h"

/* ROM SprObjectOffscrChk: d2/d3 hide a column in all three rows;
 * MoveESprRowOffscreen -> DumpTwoSpr hides exactly one row for each of
 * d5, d6 and d7 (third, second and first respectively). */
static void mysmb_oam_enemy_offscreen_tail(struct mysmb_game *game,
                                           mysmb_u8 oam, mysmb_u8 bits)
{
    mysmb_u8 row, offset, row_bit;
    for (row = 0U; row < 3U; ++row) {
        offset = (mysmb_u8)(oam + row * 8U);
        row_bit = (mysmb_u8)(0x80U >> row);
        if ((bits & row_bit) != 0U) {
            game->ram[0x0200U + offset] = 0xf8U;
            game->ram[0x0204U + offset] = 0xf8U;
        }
        if ((bits & 0x08U) != 0U)
            game->ram[0x0200U + offset] = 0xf8U;
        if ((bits & 0x04U) != 0U)
            game->ram[0x0204U + offset] = 0xf8U;
    }
}

#endif
