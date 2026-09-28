#include <string.h>
#include "game/area.h"
#include "smb1_local_rom.h"
#include "water_scene_fixture.h"

int main(void)
{
    static struct mysmb_game game;
    static const mysmb_u8 final_offsets[3] = {60U,120U,24U};
    struct mysmb_input input;
    struct mysmb_frame frame;
    unsigned int scenario, tick;
    mysmb_u16 base;
    if (mysmb_water_scene_argument("--fixture=t30-water-scene=2") != 3) return 1;
    if (mysmb_water_scene_argument("--fixture=t30-water-scene=3") != 0) return 2;
    for (scenario = 0U; scenario < 3U; ++scenario) {
        mysmb_game_initialize(&game);
        mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
        mysmb_water_scene_fixture(game.ram, (mysmb_u8)scenario);
        memset(&input, 0, sizeof(input));
        mysmb_game_tick(&game, &input, &frame);
        mysmb_water_scene_continue(game.ram);
        base = (mysmb_u16)(((mysmb_u16)game.ram[0xe8U] << 8U) + game.ram[0xe7U] - 0x8000U);
        for (tick = 0U; tick < 128U; ++tick)
            mysmb_game_tick(&game, &input, &frame);
        if (game.ram[0x72cU] != final_offsets[scenario]) return 3;
        if (mysmb_local_prg[base + game.ram[0x72cU]] != 0xfdU) return 4;
        if (game.ram[0x725U] != 16U || game.ram[0x74eU] != 0U) return 5;
    }
    return 0;
}
