#include "game/world/world.h"
#include "game/player/terrain_children.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char prg[32768], before[2048];

int main(void)
{
    static const unsigned char solid[4] = { 0x10U, 0x61U, 0x88U, 0xc4U };
    static const unsigned char climb[4] = { 0x24U, 0x6dU, 0x8aU, 0xc6U };
    unsigned int mode, tile, group, i, count, failures;
    unsigned char s, c, coin;
    count = failures = 0U;
    for (mode = 0U; mode < 3U; ++mode) {
        game.area_prg = mode ? prg : 0;
        game.area_prg_size = mode ? sizeof(prg) : 0U;
        for (i = 0U; i < 4U; ++i) {
            prg[0x5f8bU + i] = mode == 2U ? (unsigned char)(i * 64U + 31U) : solid[i];
            prg[0x5f96U + i] = mode == 2U ? (unsigned char)(i * 64U + 47U) : climb[i];
        }
        for (tile = 0U; tile < 256U; ++tile) {
            memset(game.ram, 0xa5, sizeof(game.ram));
            memcpy(before, game.ram, sizeof(before));
            group = tile / 64U;
            s = mode ? prg[0x5f8bU + group] : solid[group];
            c = mode ? prg[0x5f96U + group] : climb[group];
            if (mysmb_world_metatile_attribute((mysmb_u8)tile) != group ||
                mysmb_world_is_solid(&game, (mysmb_u8)tile) != (tile >= s) ||
                mysmb_world_is_climbable(&game, (mysmb_u8)tile) != (tile >= c) ||
                memcmp(before, game.ram, sizeof(before))) ++failures;
            coin = mysmb_player_coin_metatile(&game, (mysmb_u8)tile);
            if (tile == 194U || tile == 195U) before[0xfeU] = 1U;
            if (coin != (tile == 194U || tile == 195U) ||
                memcmp(before, game.ram, sizeof(before))) ++failures;
            ++count;
        }
    }
    printf("metatile cases=%u failures=%u\n", count, failures);
    return failures ? 1 : 0;
}
