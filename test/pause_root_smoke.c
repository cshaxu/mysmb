#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_frame frame;
    struct mysmb_input input;

    mysmb_game_initialize(&game);
    mysmb_game_frame_initialize(&frame);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 3U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0722U] = 1U;
    game.ram[0x0204U] = 0x31U;
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0776U] != 0x81U) return 1;
    if (game.ram[0x0777U] != 0x2bU) return 2;
    if (game.ram[0x00faU] != 1U) return 3;
    if (game.ram[0x0772U] != 3U) return 4;
    if (game.ram[0x0204U] != 0x31U) return 5;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0777U] != 0x2aU) return 6;
    return 0;
}