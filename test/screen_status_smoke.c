#include "game/area.h"
#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    static mysmb_u8 prg[0x0600U];

    prg[0x05cfU + 1U] = 0x41U;
    prg[0x05cfU + 2U] = 0x42U;
    prg[0x05cfU + 5U] = 0x45U;
    prg[0x05d7U] = 0x22U;
    prg[0x05d8U] = 0x16U;
    prg[0x05d9U] = 0x27U;
    prg[0x05daU] = 0x18U;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));

    game.ram[0x073cU] = 0U;
    game.ram[0x0770U] = 0U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x073cU] != 1U || game.ram[0x0773U] != 0U) return 1;

    game.ram[0x073cU] = 0U;
    game.ram[0x0770U] = 1U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x073cU] != 1U || game.ram[0x0773U] != 3U) return 1;

    game.ram[0x073cU] = 1U;
    game.ram[0x0300U] = 0U;
    game.ram[0x0744U] = 5U;
    game.ram[0x0756U] = 1U;
    game.ram[0x0753U] = 0U;
    game.ram[0x074eU] = 1U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x073cU] != 2U || game.ram[0x0744U] != 5U ||
        game.ram[0x0756U] != 1U || game.ram[0x0300U] != 7U ||
        game.ram[0x0301U] != 0x3fU || game.ram[0x0302U] != 0x10U ||
        game.ram[0x0303U] != 4U || game.ram[0x0304U] != 0x42U ||
        game.ram[0x0305U] != 0x16U || game.ram[0x0306U] != 0x27U ||
        game.ram[0x0307U] != 0x18U || game.ram[0x0308U] != 0U) return 1;

    /* ROM DisplayTimeUp clears its latch and OutputInter restores screen
     * output before the later ResetSpritesAndScreenTimer task. */
    game.ram[0x073cU] = 4U;
    game.ram[0x0759U] = 1U;
    game.ram[0x0774U] = 1U;
    game.ram[0x07a0U] = 0U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x0759U] != 0U || game.ram[0x0774U] != 0U ||
        game.ram[0x07a0U] != 7U || game.ram[0x073cU] != 5U) return 1;

    game.ram[0x073cU] = 9U;
    game.ram[0x074eU] = 3U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x073cU] != 10U || game.ram[0x0773U] != 4U) return 1;

    game.ram[0x073cU] = 10U;
    game.ram[0x0744U] = 5U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x073cU] != 11U || game.ram[0x0773U] != 9U) return 1;

    /* ROM DisplayIntermediate checks castle AreaType before it checks
     * DisableIntermediate.  The missing text source keeps task six in place,
     * proving it did not take NoInter's task-eight branch. */
    game.ram[0x073cU] = 6U;
    game.ram[0x0770U] = 1U;
    game.ram[0x0752U] = 0U;
    game.ram[0x074eU] = 3U;
    game.ram[0x0769U] = 1U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x073cU] != 6U) return 1;

    game.ram[0x073cU] = 11U;
    game.ram[0x0733U] = 1U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x073cU] != 12U || game.ram[0x0773U] != 11U) return 1;
    return 0;
}
