#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    unsigned int index;

    mysmb_game_initialize(&game);
    input.buttons = 0U;
    for (index = 0U; index < 120U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }

    if (game.frame_number != 120UL || game.ram[0x07feU] != 0U ||
        game.ram[0x07ffU] != 0xffU || game.ram[0x015fU] != 0U ||
        game.ram[0x0160U] != 0xffU || game.ram[0x01feU] != 0xffU ||
        game.ram[0x0200U] != 0xf8U || game.ram[0x0204U] != 0xf8U ||
        game.ram[0x02fcU] != 0xf8U || game.ram[0x0201U] != 0U) {
        return 1;
    }

    game.ram[0x07d7U] = 0xffU;
    mysmb_game_initialize_memory(&game, 0xd6U);
    if (game.ram[0x07d6U] != 0U || game.ram[0x07d7U] != 0xffU) {
        return 1;
    }

    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    return frame.start_pressed == 1U ? 0 : 1;
}
