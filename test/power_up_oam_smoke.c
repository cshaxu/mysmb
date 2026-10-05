#include "core/game.h"
#include "core/oam/oam.h"

static void prepare(struct mysmb_game *game, mysmb_u8 type,
                    mysmb_u8 frame, mysmb_u8 offscreen)
{
    mysmb_game_initialize_memory(game, 0U);
    game->ram[0x0039U] = type;
    game->ram[8U] = 5U;
    game->ram[0x0009U] = frame;
    game->ram[0x03aeU] = 0x40U;
    game->ram[0x03b9U] = 0x50U;
    game->ram[0x03c5U + 5U] = 0x20U;
    game->ram[0x03d1U] = offscreen;
    game->ram[0x06e5U + 5U] = 0x20U;
}

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 third_left, third_right;

    prepare(&game, 2U, 2U, 0U);
    mysmb_objects_draw_power_up(&game);
    if (game.ram[0x0220U] != 0x58U || game.ram[0x0221U] != 0x8dU ||
        game.ram[0x0222U] != 0x21U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0x58U || game.ram[0x0225U] != 0x8dU ||
        game.ram[0x0226U] != 0x61U || game.ram[0x0227U] != 0x48U ||
        game.ram[0x0228U] != 0x60U || game.ram[0x0229U] != 0xe4U ||
        game.ram[0x022aU] != 0x21U || game.ram[0x022bU] != 0x40U ||
        game.ram[0x022cU] != 0x60U || game.ram[0x022dU] != 0xe4U ||
        game.ram[0x022eU] != 0x61U || game.ram[0x022fU] != 0x48U) return 1;

    prepare(&game, 1U, 2U, 0U);
    mysmb_objects_draw_power_up(&game);
    if (game.ram[0x0221U] != 0xd6U || game.ram[0x0225U] != 0xd6U ||
        game.ram[0x0229U] != 0xd9U || game.ram[0x022dU] != 0xd9U ||
        game.ram[0x0222U] != 0x21U || game.ram[0x0226U] != 0x61U ||
        game.ram[0x022aU] != 0x21U || game.ram[0x022eU] != 0x61U) return 2;

    /* PUpOfs enters the three-row SprObjectOffscrChk tail. */
    prepare(&game, 3U, 0U, 0x80U);
    third_left = game.ram[0x0230U];
    third_right = game.ram[0x0234U];
    mysmb_objects_draw_power_up(&game);
    if (game.ram[0x0220U] != 0xf8U || game.ram[0x0224U] != 0xf8U ||
        game.ram[0x0228U] != 0x60U || game.ram[0x022cU] != 0x60U ||
        game.ram[0x0230U] != third_left || game.ram[0x0234U] != third_right ||
        game.ram[0x0221U] != 0x76U || game.ram[0x022dU] != 0x79U) return 3;
    return 0;
}
