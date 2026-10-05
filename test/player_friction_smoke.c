#include "core/game.h"
#include "game/player.h"

static int expect_friction(struct mysmb_game *game, mysmb_u8 buttons,
                           mysmb_u8 speed, mysmb_u8 force,
                           mysmb_u8 expected_speed, mysmb_u8 expected_force,
                           mysmb_u8 expected_absolute)
{
    game->ram[0x000cU] = buttons;
    game->ram[0x0490U] = (mysmb_u8)(MYSMB_BUTTON_LEFT | MYSMB_BUTTON_RIGHT);
    game->ram[0x0057U] = speed;
    game->ram[0x0705U] = force;
    game->ram[0x0701U] = 0U;
    game->ram[0x0702U] = 0x20U;
    game->ram[0x0450U] = 0xd8U;
    game->ram[0x0456U] = 0x28U;
    mysmb_player_impose_friction(game);
    if (game->ram[0x0057U] != expected_speed) return 1;
    if (game->ram[0x0705U] != expected_force) return 2;
    if (game->ram[0x0700U] != expected_absolute) return 3;
    return 0;
}

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0U);
    /* ROM RghtFrict: released positive speed subtracts toward zero. */
    if (expect_friction(&game, 0U, 5U, 0x10U, 4U, 0xf0U, 4U) != 0) return 1;
    /* ROM LeftFrict: released negative speed adds toward zero. */
    if (expect_friction(&game, 0U, 0xfbU, 0xf0U, 0xfcU, 0x10U, 4U) != 0) return 2;
    /* A held right direction follows LeftFrict and accelerates right. */
    if (expect_friction(&game, MYSMB_BUTTON_RIGHT, 0U, 0xf0U,
                        1U, 0x10U, 1U) != 0) return 3;
    /* A held left direction follows RghtFrict and accelerates left. */
    if (expect_friction(&game, MYSMB_BUTTON_LEFT, 0U, 0x10U,
                        0xffU, 0xf0U, 1U) != 0) return 4;
    return 0;
}