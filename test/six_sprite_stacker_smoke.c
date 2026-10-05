#include "core/game.h"
#include "game/oam/oam.h"
#include <string.h>

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 row;

    memset(&game, 0, sizeof(game));
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_oam_stack_six_sprite_data(&game, 0xe8U, 0xf4U);
    for (row = 0U; row < 6U; ++row) {
        if (game.ram[(mysmb_u16)(0x0200U +
                                  (mysmb_u8)(0xf4U + row * 4U))] !=
            (mysmb_u8)(0xe8U + row * 8U)) return 1;
    }
    return 0;
}
