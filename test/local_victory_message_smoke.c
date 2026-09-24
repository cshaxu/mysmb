#include "game/game.h"
#include "game/area.h"
#include "smb1_local_rom.h"

static void mysmb_test_start_victory(struct mysmb_game *game)
{
    mysmb_game_initialize(game);
    mysmb_game_bind_area_source(game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    game->ram[0x0770U] = 2U;
    game->ram[0x0772U] = 3U;
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;

    input.buttons = 0U;
    mysmb_test_start_victory(&game);
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0773U] != 12U || game.ram[0x0749U] != 4U ||
        game.ram[0x0719U] != 0U) return 1;
    mysmb_game_tick(&game, &input, &frame);
    if (game.name_table[1U][0x0148U] != mysmb_local_prg[0x0d57U] ||
        game.ram[0x0773U] != 0U) return 1;

    mysmb_test_start_victory(&game);
    game.ram[0x0719U] = 2U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0773U] != 14U) return 1;
    mysmb_game_tick(&game, &input, &frame);
    if (game.name_table[1U][0x01c5U] != mysmb_local_prg[0x0d7fU]) return 1;

    mysmb_test_start_victory(&game);
    game.ram[0x075fU] = 7U;
    game.ram[0x0719U] = 3U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0773U] != 15U || game.ram[0x00fcU] != 4U) return 1;
    mysmb_game_tick(&game, &input, &frame);
    if (game.name_table[1U][0x01a7U] != mysmb_local_prg[0x0dabU]) return 1;

    if (mysmb_area_apply_message(&game, 18U) == 0U ||
        game.name_table[1U][0x0288U] != mysmb_local_prg[0x0df2U] ||
        mysmb_area_apply_message(&game, 19U) != 0U) return 1;
    return 0;
}
