#include "core/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    unsigned int index;

    /* The route starts through the same title input and task-zero area setup
     * that the Win32 composition root uses. */
    mysmb_game_initialize(&game);
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x0757U] == 0U) return 1;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 1U ||
        game.ram[0x0774U] != 1U) return 2;

    /* Without a bound PRG, original LoadAreaPointer cannot advance into the
     * parser/entrance path.  This ROM-free harness therefore proves only the
     * title-to-game handoff; area-entry integration has its own bound-source
     * route. */
    game.ram[0x0715U] = 1U;
    game.ram[0x0757U] = 1U;
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_RIGHT;
    for (index = 0U; index < 3U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x000eU] != 0U || game.ram[0x0772U] != 1U) return 31;
    /* GameEngine clears its transient directional partition after the frame;
     * the next player-control phase latches the current host input again. */
    if (game.ram[0x000cU] != 0U) return 33;
    if (frame.operating_mode != 1U) return 34;
    return 0;
}
