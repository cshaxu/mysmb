#include "game/game.h"
#include "game/player.h"

int main(void)
{
    struct mysmb_game game;
    unsigned int index;

    mysmb_game_initialize(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0490U] = 0xffU;
    game.ram[0x0033U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x070aU] = 0x28U;
    for (index = 0U; index < 16U; ++index) {
        game.ram[(mysmb_u16)(0x0600U + index)] = 0x61U;
    }
    for (index = 0U; index < 8U; ++index) {
        mysmb_player_step(&game, MYSMB_BUTTON_RIGHT);
    }
    if (game.ram[0x0086U] <= 0x20U || game.ram[0x0057U] == 0U ||
        game.ram[0x001dU] != 0U || game.ram[0x00ceU] != 0x30U) {
        return 1;
    }
    mysmb_player_step(&game, (mysmb_u8)(MYSMB_BUTTON_A | MYSMB_BUTTON_RIGHT));
    if (game.ram[0x001dU] != 1U || game.ram[0x00ceU] >= 0x30U ||
        game.ram[0x009fU] < 0x80U || game.ram[0x0782U] != 0x20U) {
        return 1;
    }
    mysmb_player_step(&game, (mysmb_u8)(MYSMB_BUTTON_A | MYSMB_BUTTON_RIGHT));
    if (game.ram[0x0709U] == game.ram[0x070aU] ||
        game.ram[0x0433U] != 0x40U) {
        return 1;
    }
    mysmb_player_step(&game, MYSMB_BUTTON_RIGHT);
    if (game.ram[0x0709U] != game.ram[0x070aU]) {
        return 1;
    }
    return 0;
}
