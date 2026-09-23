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

    /* This neutral flat-ground fixture is the native counterpart of the
     * reference probe's playable entry.  It uses GameTick, rather than a
     * direct player call, so input, audio, object dispatch, and physics stay
     * in their production frame order. */
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0490U] = 0xffU;
    game.ram[0x0033U] = 1U;
    game.ram[0x006dU] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0086U] = 0x28U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x070aU] = 0x28U;
    for (index = 0U; index < 16U; ++index) {
        game.ram[(mysmb_u16)(0x0600U + index)] = 0x61U;
    }
    input.buttons = MYSMB_BUTTON_RIGHT;
    for (index = 0U; index < 8U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x000eU] != 8U) return 31;
    if (game.ram[0x0086U] <= 0x28U) return 32;
    if (game.ram[0x0057U] == 0U) return 33;
    if (frame.operating_mode != 1U) return 34;
    return 0;
}
