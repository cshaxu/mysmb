#include "game/game.h"
#include "game/frame_root.h"

static const mysmb_u8 table_low[19] = {
    0x01U, 0xa4U, 0xc8U, 0xecU, 0x10U, 0x00U, 0x41U, 0x41U, 0x4cU,
    0x34U, 0x3cU, 0x44U, 0x54U, 0x68U, 0x7cU, 0xa8U, 0xbfU, 0xdeU,
    0xefU
};
static const mysmb_u8 table_high[19] = {
    0x03U, 0x8cU, 0x8cU, 0x8cU, 0x8dU, 0x03U, 0x03U, 0x03U, 0x8dU,
    0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU,
    0x8dU
};

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 selector;

    for (selector = 0U; selector < 19U; ++selector) {
        mysmb_game_initialize(&game);
        game.ram[0x0300U] = 0x44U;
        game.ram[0x0301U] = 0U;
        game.ram[0x0340U] = 0x55U;
        game.ram[0x0341U] = 0U;
        game.ram[0x0773U] = selector;
        mysmb_game_commit_vram_buffer(&game);
        if (game.ram[0x0000U] != table_low[selector] ||
            game.ram[0x0001U] != table_high[selector] ||
            game.ram[0x0773U] != 0U) return 1;
        if (selector == 6U) {
            if (game.ram[0x0340U] != 0U || game.ram[0x0341U] != 0U ||
                game.ram[0x0300U] != 0x44U) return 2;
        }
        else if (game.ram[0x0300U] != 0U || game.ram[0x0301U] != 0U) {
            return 3;
        }
    }
    return 0;
}
