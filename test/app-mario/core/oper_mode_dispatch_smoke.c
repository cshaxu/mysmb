#include "core/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;

    input.buttons2 = 0U;

    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    /* DecTimers runs before GameMenuRoutine.  Keep the source demo timer
     * nonzero through this NMI so Start reaches ChkContinue rather than the
     * title-reset branch. */
    game.ram[0x07a2U] = 2U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x07a2U] != 0U) return 1;

    input.buttons2 = 0U;

    input.buttons = 0U;
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 0U;
    game.ram[0x075bU] = 3U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 1U ||
        game.ram[0x071aU] != 3U || game.ram[0x00fbU] != 0x80U) return 2;

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 2U;
    game.ram[0x0772U] = 1U;
    game.ram[0x071bU] = 5U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 2U || game.ram[0x0772U] != 2U ||
        game.ram[0x0034U] != 6U || game.ram[0x00fcU] != 8U) return 3;

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 3U;
    game.ram[0x0772U] = 0U;
    game.ram[0x0722U] = 1U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 3U || game.ram[0x0772U] != 1U ||
        game.ram[0x073cU] != 0U || game.ram[0x0722U] != 0U ||
        /* The compatibility fixture begins after ColdBoot's screen-disable
         * increment; SetupGameOver performs the source's second increment. */
        game.ram[0x00fcU] != 2U || game.ram[0x0774U] != 2U) return 4;
    return 0;
}
