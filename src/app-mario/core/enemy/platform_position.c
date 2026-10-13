#include "core/enemy/platform.h"

/* ROM $DC23 common positioning tail. The small entry's BIT consumes the
 * vertical entry's LDA bytes; its flag effects are overwritten before use. */
static void position_at_height(struct mysmb_game *game, mysmb_u8 slot,
                               mysmb_u8 height)
{
    if (game->ram[0x000eU] == 11U || game->ram[0x00b6U + slot] != 1U) return;
    game->ram[0x00ceU] = (mysmb_u8)(height - 0x20U);
    game->ram[0x00b5U] = height < 0x20U ? 0U : 1U;
    game->ram[0x009fU] = 0U;
    game->ram[0x0433U] = 0U;
}

/* ROM $DC21 PositionPlayerOnVPlat through $DC40 ExPlPos. */
void mysmb_platform_position_player_vertical(struct mysmb_game *game,
                                             mysmb_u8 slot)
{
    position_at_height(game, slot, game->ram[0x00cfU + slot]);
}

/* ROM $DC17 PlayerPosSPlatData / $DC19 PositionPlayerOnS_Plat.
 * Counter1 selects +$80, counter2 +0. Preserve unmasked source indexing
 * through the bound PRG; resource-free tests support the two legal entries. */
void mysmb_platform_position_player_small(struct mysmb_game *game,
                                          mysmb_u8 slot, mysmb_u8 counter)
{
    mysmb_u16 address;
    mysmb_u8 delta;
    address = (mysmb_u16)(0x5c16U + counter);
    if (game->area_prg != 0 && address < game->area_prg_size)
        delta = game->area_prg[address];
    else delta = counter == 1U ? 0x80U : 0U;
    position_at_height(game, slot, (mysmb_u8)(game->ram[0x00cfU + slot] + delta));
}
