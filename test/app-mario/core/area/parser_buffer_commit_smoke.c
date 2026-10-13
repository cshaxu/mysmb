#include "core/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;

    mysmb_game_initialize(&game);
    input.buttons2 = 0U;
    input.buttons = 0U;
    game.ram[0x0340U] = 4U;
    game.ram[0x0341U] = 0x20U;
    game.ram[0x0342U] = 0x80U;
    game.ram[0x0343U] = 1U;
    game.ram[0x0344U] = 0x5aU;
    game.ram[0x0345U] = 0U;
    game.ram[0x0773U] = 6U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ppu.name_table[0][0x0080U] != 0x5aU || game.ram[0x0340U] != 0U ||
        game.ram[0x0341U] != 0U || game.ram[0x0773U] != 0U) return 1;
    game.ram[0x0340U] = 4U;
    game.ram[0x0341U] = 0x20U;
    game.ram[0x0342U] = 0x81U;
    game.ram[0x0343U] = 1U;
    game.ram[0x0344U] = 0x5bU;
    game.ram[0x0345U] = 0U;
    game.ram[0x0773U] = 7U;
    mysmb_game_tick(&game, &input, &frame);
    /* ROM InitBuffer selects Buffer_Offset[1] only for selector six.  The
     * selector-seven route transfers buffer two, then clears buffer one. */
    if (game.ppu.name_table[0][0x0081U] != 0x5bU || game.ram[0x0340U] != 4U ||
        game.ram[0x0341U] != 0x20U || game.ram[0x0773U] != 0U) return 2;
    return 0;
}
