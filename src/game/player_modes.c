#include "game/player.h"

/* ROM $b273-$b27c DonePlayerTask, shared by size, injury and flower. */
static void mysmb_player_done_task(struct mysmb_game *game)
{
    game->ram[0x0747U] = 0U;
    game->ram[0x000eU] = 8U;
}

/* ROM $b255-$b268 InitChangeSize/ExitBoth; injury's F0 path also enters here. */
static void mysmb_player_init_change_size(struct mysmb_game *game)
{
    if (game->ram[0x070bU] != 0U) return;
    game->ram[0x070dU] = 0U;
    ++game->ram[0x070bU];
    game->ram[0x0754U] ^= 1U;
}

/* ROM $b233-$b244 PlayerChangeSize/EndChgSize/ExitChgSize. */
void mysmb_player_step_change_size(struct mysmb_game *game)
{
    if (game->ram[0x0747U] == 0xf8U) {
        mysmb_player_init_change_size(game);
        return;
    }
    if (game->ram[0x0747U] == 0xc4U) mysmb_player_done_task(game);
}

/* ROM $b245-$b254 PlayerInjuryBlink/ExitBlink. */
void mysmb_player_step_injury_blink(struct mysmb_game *game, mysmb_u8 buttons)
{
    if (game->ram[0x0747U] >= 0xf0U) {
        /* CMP F0 -> BCS ExitBlink -> BNE ExitBoth. Equality falls
         * through into InitChangeSize with the original Z flag set. */
        if (game->ram[0x0747U] == 0xf0U) mysmb_player_init_change_size(game);
        return;
    }
    if (game->ram[0x0747U] == 0xc8U) {
        mysmb_player_done_task(game);
        return;
    }
    mysmb_player_step(game, buttons);
}

/* ROM $b269-$b272 PlayerDeath, $b2a3 ExitDeath. */
void mysmb_player_step_death(struct mysmb_game *game)
{
    if (game->ram[0x0747U] < 0xf0U)
        mysmb_player_step(game, game->ram[0x06fcU]);
}

/* ROM $b288-$b296 CyclePlayerPalette: shared flower/star leaf. */
void mysmb_player_cycle_palette(struct mysmb_game *game, mysmb_u8 color)
{
    game->ram[0x0000U] = (mysmb_u8)(color & 3U);
    game->ram[0x03c4U] = (mysmb_u8)((game->ram[0x03c4U] & 0xfcU) |
                                   game->ram[0x0000U]);
}

/* ROM $b29a-$b2a2 ResetPalStar. */
void mysmb_player_reset_palette(struct mysmb_game *game)
{
    game->ram[0x03c4U] &= 0xfcU;
}

/* ROM $b27d PlayerFireFlower and $b297 ResetPalFireFlower. */
void mysmb_player_step_fire_flower(struct mysmb_game *game)
{
    if (game->ram[0x0747U] == 0xc0U) {
        mysmb_player_done_task(game);
        mysmb_player_reset_palette(game);
        return;
    }
    mysmb_player_cycle_palette(game, (mysmb_u8)(game->ram[0x0009U] >> 2U));
}
