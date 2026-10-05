#include "core/game.h"

int main(void)
{
    static const mysmb_u8 expected[5][2] = {
        { 0x52U, 0x80U }, { 0xa9U, 0x40U }, { 0x54U, 0xa0U },
        { 0x2aU, 0x50U }, { 0x95U, 0x28U }
    };
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    mysmb_u8 index;

    mysmb_game_initialize(&game);
    if (game.ram[0x07ffU] != 0xa5U) return 1;
    input.buttons2 = 0U;
    input.buttons = 0U;
    for (index = 0U; index < 5U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
        if (game.ram[0x07a7U] != expected[index][0] ||
            game.ram[0x07a8U] != expected[index][1]) return 1;
    }
    for (; index < 48U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }
    return game.ram[0x07aeU] == 0U ? 0 : 1;
}