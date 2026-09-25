#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;

    mysmb_game_initialize(&game);
    input.buttons = 0U;
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0U;
    game.ram[0x0717U] = 0U;
    game.ram[0x0718U] = 0U;

    mysmb_game_title_step(&game, &input);
    if (game.ram[0x06fcU] != MYSMB_BUTTON_RIGHT ||
        game.ram[0x0717U] != 1U || game.ram[0x0718U] != 0x9aU ||
        game.ram[0x0719U] != 0U) {
        return 1;
    }

    game.ram[0x0718U] = 0U;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x06fcU] != MYSMB_BUTTON_A ||
        game.ram[0x0717U] != 2U || game.ram[0x0718U] != 0x0fU) {
        return 1;
    }

    game.ram[0x0717U] = 20U;
    game.ram[0x0718U] = 0U;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x06fcU] != 0U || game.ram[0x0717U] != 21U ||
        game.ram[0x0718U] != 0xfeU) {
        return 1;
    }

    game.ram[0x0717U] = 21U;
    game.ram[0x0718U] = 0U;
    game.ram[0x0722U] = 1U;
    game.ram[0x0774U] = 0U;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x0722U] != 0U || game.ram[0x0774U] != 1U) {
        return 1;
    }
    return 0;
}
