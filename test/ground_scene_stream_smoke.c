#include <string.h>
#include "game/area.h"
#include "smb1_local_rom.h"
#include "ground_scene_fixture.h"

int main(void)
{
    static struct mysmb_game game;
    static const mysmb_u8 final_offsets[23] = {
        96U,102U,80U,140U,114U,98U,82U,130U,98U,6U,60U,
        18U,100U,98U,112U,46U,94U,112U,118U,86U,40U,48U,144U
    };
    struct mysmb_input input;
    struct mysmb_frame frame;
    unsigned int scenario, tick, ticks;
    mysmb_u16 base;
    if (mysmb_ground_scene_argument("--fixture=t30-ground-scene=22") != 23) return 1;
    if (mysmb_ground_scene_argument("--fixture=t30-ground-scene=23") != 0) return 2;
    for (scenario = 0U; scenario < 23U; ++scenario) {
        mysmb_game_initialize(&game);
        mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
        mysmb_ground_scene_fixture(game.ram, (mysmb_u8)scenario);
        memset(&input, 0, sizeof(input));
        mysmb_game_tick(&game, &input, &frame);
        mysmb_ground_scene_continue(game.ram);
        base = (mysmb_u16)(((mysmb_u16)game.ram[0xe8U] << 8U) + game.ram[0xe7U] - 0x8000U);
        ticks = scenario == 22U ? 256U : 128U;
        for (tick = 0U; tick < ticks; ++tick) {
            if (tick == 128U) mysmb_ground_scene_continue(game.ram);
            mysmb_game_tick(&game, &input, &frame);
        }
        if (game.ram[0x72cU] != final_offsets[scenario]) return 3;
        if (scenario != 16U && mysmb_local_prg[base + game.ram[0x72cU]] != 0xfdU) return 4;
        if (game.ram[0x725U] != (scenario == 22U ? 32U : 16U)) return 5;
    }
    return 0;
}
