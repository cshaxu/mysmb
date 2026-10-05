#include <string.h>
#include "core/area.h"
#include "smb1_local_rom.h"
#include "castle_scene_fixture.h"

int main(void)
{
    static struct mysmb_game game;
    static const mysmb_u8 terminal_offsets[7] = {94U,124U,112U,106U,136U,86U,110U};
    struct mysmb_input input;
    struct mysmb_frame frame;
    unsigned int scenario, tick;
    mysmb_u16 base;
    if (mysmb_castle_scene_argument("--fixture=t30-castle-scene=6") != 7) return 1;
    for (scenario = 0U; scenario < 7U; ++scenario) {
        mysmb_game_initialize(&game);
        mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
        mysmb_castle_scene_fixture(game.ram, (mysmb_u8)scenario);
        memset(&input, 0, sizeof(input));
        mysmb_game_tick(&game, &input, &frame);
        mysmb_castle_scene_continue(game.ram);
        base = (mysmb_u16)(((mysmb_u16)game.ram[0xe8U] << 8U) + game.ram[0xe7U] - 0x8000U);
        for (tick = 0U; tick < 128U; ++tick)
            mysmb_game_tick(&game, &input, &frame);
        if (game.ram[0x72cU] != terminal_offsets[scenario]) return 2;
        if (scenario != 5U && mysmb_local_prg[base + game.ram[0x72cU]] != 0xfdU) return 3;
        if (game.ram[0x725U] != (scenario == 6U ? 32U : 16U)) return 4;
    }
    return 0;
}
