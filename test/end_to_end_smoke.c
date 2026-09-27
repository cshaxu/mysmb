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

    /* Continue through the production entrance path.  This test intentionally
     * does not construct terrain or an area header.  Supply the header-owned
     * timer state that a ROM-bound area parse normally provides. */
    game.ram[0x0715U] = 1U;
    game.ram[0x0757U] = 1U;
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_RIGHT;
    for (index = 0U; index < 3U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x000eU] != 8U) return 31;
    /* The fixture deliberately has no area header, so PrimaryGameSetup is
     * outside this entrance-only path.  PlayerSize is verified separately
     * by the title-bootstrap route that supplies the parsed area owner. */
    /* GameEngine clears its transient directional partition after the frame;
     * the next player-control phase latches the current host input again. */
    if (game.ram[0x000cU] != 0U) return 33;
    if (frame.operating_mode != 1U) return 34;
    return 0;
}
