#include "game/game.h"
#include "game/area.h"

static int check_music(mysmb_u8 area_type, mysmb_u8 entrance,
                       mysmb_u8 alternate, mysmb_u8 cloud,
                       mysmb_u8 expected)
{
    static const mysmb_u8 area_data[1] = { 0U };
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, area_data, 1U);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 2U;
    game.ram[0x074eU] = area_type;
    game.ram[0x0710U] = entrance;
    game.ram[0x0769U] = alternate;
    game.ram[0x0743U] = cloud;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    return game.ram[0x00fbU] == expected ? 0 : 1;
}

int main(void)
{
    if (check_music(1U, 0U, 0U, 0U, 0x01U) != 0) return 1;
    if (check_music(3U, 0U, 0U, 1U, 0x10U) != 0) return 2;
    if (check_music(2U, 6U, 0U, 0U, 0x20U) != 0) return 3;
    if (check_music(3U, 6U, 2U, 0U, 0x08U) != 0) return 4;
    return 0;
}