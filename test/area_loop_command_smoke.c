#include <string.h>
#include "game/area.h"

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 data[4];
    unsigned int seed, scenario, i;
    mysmb_u8 increments, cursor;
    for (seed = 0U; seed < 256U; ++seed)
    for (scenario = 0U; scenario < 9U; ++scenario) {
        memset(&game, 0, sizeof(game));
        data[0] = 0x5dU; data[1] = 0x4bU; data[2] = 0xfdU; data[3] = 0xfdU;
        mysmb_game_bind_area_source(&game, data, sizeof(data));
        game.ram[0xe8U] = 0x80U;
        game.ram[0x745U] = (mysmb_u8)seed;
        for (i = 0U; i < 3U; ++i) game.ram[0x730U+i] = 0xffU;
        increments = 3U; cursor = 0U;
        if (scenario == 1U) {
            game.ram[0x726U] = 5U; increments = 1U; cursor = 2U;
        } else if (scenario == 2U) {
            game.ram[0x72aU] = 1U;
        } else if (scenario == 3U) {
            game.ram[0x725U] = 1U; increments = 0U; cursor = 2U;
        } else if (scenario == 4U) {
            data[1] = 0xcbU;
        } else if (scenario == 5U) {
            game.ram[0x728U] = 1U; increments = 1U;
        } else if (scenario >= 6U) {
            game.ram[0x72cU] = 2U;
            game.ram[0x730U+scenario-6U] = 1U;
            game.ram[0x725U] = 9U;
            increments = 1U; cursor = 2U;
        }
        if (!mysmb_area_process_object_state(&game)) return 1;
        if (game.ram[0x745U] != (mysmb_u8)(seed + increments)) return 2;
        if (game.ram[0x72cU] != cursor) return 3;
        if (scenario == 5U && game.ram[0x728U] != 0U) return 4;
        if (scenario >= 6U && game.ram[0x730U+scenario-6U] != 0U) return 5;
    }
    return 0;
}
