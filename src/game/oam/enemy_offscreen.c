#include "game/oam/oam.h"

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
