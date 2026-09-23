#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    unsigned int index;

    /* The route starts through the same title input and task-zero area setup
     * that the Win32 composition root uses. */
    mysmb_game_initialize(&game);
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x0757U] == 0U) return 1;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 1U ||
        game.ram[0x0774U] != 1U) return 2;

    /* Continue through the production entrance path.  This test intentionally
     * does not construct terrain: real area-object rendering owns that state. */
    input.buttons = MYSMB_BUTTON_RIGHT;
    for (index = 0U; index < 3U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x000eU] != 8U) return 31;
    if (game.ram[0x0754U] != 1U) return 32;
    if (game.ram[0x000cU] != MYSMB_BUTTON_RIGHT) return 33;
    if (frame.operating_mode != 1U) return 34;
    return 0;
}
