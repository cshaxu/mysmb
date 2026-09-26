#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 21U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071dU] = 0U;
    mysmb_objects_draw_bowser_flame(&game, 0U);
    if (game.ram[0x03aeU] != 0x40U || game.ram[0x03b9U] != 0x70U ||
        game.ram[0x0220U] != 0x70U || game.ram[0x0221U] != 0x51U ||
        game.ram[0x0222U] != 0x02U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0x70U || game.ram[0x0225U] != 0x52U ||
        game.ram[0x0227U] != 0x48U || game.ram[0x0228U] != 0x70U ||
        game.ram[0x0229U] != 0x53U || game.ram[0x022bU] != 0x50U) {
        return 1;
    }
    game.ram[0x0009U] = 2U;
    mysmb_objects_draw_bowser_flame(&game, 0U);
    if (game.ram[0x0222U] != 0x82U || game.ram[0x0226U] != 0x82U ||
        game.ram[0x022aU] != 0x82U) {
        return 1;
    }
    game.ram[0x001eU] = 1U;
    game.ram[0x0221U] = 0xaaU;
    mysmb_objects_draw_bowser_flame(&game, 0U);
    if (game.ram[0x0221U] != 0xaaU) return 1;
    game.ram[0x000fU + 2U] = 1U;
    game.ram[0x0016U + 2U] = 21U;
    game.ram[0x001eU + 2U] = 0U;
    game.ram[0x0087U + 2U] = 0x60U;
    game.ram[0x00cfU + 2U] = 0x50U;
    game.ram[0x06e5U + 2U] = 0x40U;
    mysmb_objects_draw_bowser_flame(&game, 2U);
    if (game.ram[0x03aeU] != 0x60U || game.ram[0x03b9U] != 0x50U ||
        game.ram[0x03b0U] != 0U || game.ram[0x03bbU] != 0U) return 1;
    return 0;
}