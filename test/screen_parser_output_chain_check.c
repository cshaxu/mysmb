#include "game/area.h"
#include "game/frame_root.h"

static void setup_parser(struct mysmb_game *game, mysmb_u8 column_sets)
{
    static mysmb_u8 prg[0x1600U];
    unsigned int index;

    for (index = 0U; index < sizeof(prg); ++index) prg[index] = 0U;
    prg[0x0040U] = 0xfdU;
    prg[0x0b0cU] = 0x80U;
    prg[0x0b0dU] = 0x80U;
    prg[0x0b0eU] = 0x80U;
    prg[0x0b0fU] = 0x80U;
    prg[0x13d9U] = 0x69U;
    prg[0x13deU] = 0U;
    prg[0x13dfU] = 0x18U;
    prg[0x1504U] = 0x10U;
    prg[0x1505U] = 0x51U;
    prg[0x1506U] = 0x88U;
    prg[0x1507U] = 0xc0U;
    mysmb_game_initialize(game);
    mysmb_game_bind_area_source(game, prg, (mysmb_u16)sizeof(prg));
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 1U;
    game->ram[0x073cU] = 8U;
    game->ram[0x074eU] = 1U;
    game->ram[0x00e7U] = 0x40U;
    game->ram[0x00e8U] = 0x80U;
    game->ram[0x0725U] = 0U;
    game->ram[0x0726U] = 0U;
    game->ram[0x072aU] = 0U;
    game->ram[0x072bU] = 0U;
    game->ram[0x072cU] = 0U;
    game->ram[0x0730U] = 0xffU;
    game->ram[0x0731U] = 0xffU;
    game->ram[0x0732U] = 0xffU;
    game->ram[0x0720U] = 0x20U;
    game->ram[0x0721U] = 0x80U;
    game->ram[0x071eU] = column_sets;
}

int main(void)
{
    struct mysmb_game game;

    /* Final set: DEC produces $ff, then ScreenRoutineTask advances before
     * OutputCol selects buffer two. */
    setup_parser(&game, 0U);
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x0774U] != 2U) return 11;
    if (game.ram[0x071fU] != 0U) return 12;
    if (game.ram[0x071eU] != 0xffU) return 13;
    if (game.ram[0x073cU] != 9U) return 14;
    if (game.ram[0x0773U] != 6U) return 15;

    /* A remaining set reaches the same OutputCol tail without advancing. */
    setup_parser(&game, 1U);
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x0774U] != 2U) return 21;
    if (game.ram[0x071fU] != 0U) return 22;
    if (game.ram[0x071eU] != 0U) return 23;
    if (game.ram[0x073cU] != 8U) return 24;
    if (game.ram[0x0773U] != 6U) return 25;
    return 0;
}
