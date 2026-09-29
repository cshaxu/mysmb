#include "game/world/world.h"
#include "game/enemy/background.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048], prg[32768];

int main(void)
{
    static const unsigned char ids[8] = { 0U, 1U, 6U, 7U, 8U, 9U, 0x33U, 0xffU };
    unsigned int source, slot, kind, edge, mode, page, low, direction, id;
    unsigned long cases;
    unsigned int failures;
    cases = 0UL; failures = 0U;
    prg[0x5fbfU] = 0x21U; prg[0x5fc0U] = 0xdfU;
    for (mode = 0U; mode < 2U; ++mode) {
        game.area_prg = mode ? prg : 0;
        game.area_prg_size = mode ? sizeof(prg) : 0U;
        for (source = 0U; source < 256U; ++source) {
            for (slot = 0U; slot < 6U; ++slot) {
                for (kind = 0U; kind < 8U; ++kind) {
                    for (edge = 0U; edge < 4U; ++edge) {
                        memset(game.ram, 0xa5, sizeof(game.ram));
                        game.ram[0x16U + slot] = ids[kind];
                        game.ram[0x1eU + slot] = (mysmb_u8)source;
                        game.ram[0xcfU + slot] = (mysmb_u8)edge;
                        game.ram[0x74eU] = (mysmb_u8)(edge & 1U);
                        game.ram[0x6eU + slot] = (edge & 2U) ? 0U : 255U;
                        game.ram[0x6dU] = (edge & 1U) ? 255U : 0U;
                        game.ram[0x87U + slot] = (edge & 2U) ? 255U : 0U;
                        game.ram[0x86U] = (edge & 1U) ? 0U : 255U;
                        memcpy(expected, game.ram, sizeof(expected));
                        id = ids[kind];
                        if (source == 9U || (source >= 13U && source <= 16U)) id = source % 2U;
                        expected[0x16U + slot] = (unsigned char)id;
                        expected[0x1eU + slot] = (unsigned char)((source / 16U) * 16U + 2U);
                        expected[0xcfU + slot] = (unsigned char)(edge - 2U);
                        expected[0xa0U + slot] = id == 7U || !(edge & 1U) ? 255U : 253U;
                        low = (unsigned char)(expected[0x87U + slot] - expected[0x86U]);
                        page = (unsigned char)(expected[0x6eU + slot] - expected[0x6dU] -
                            (expected[0x87U + slot] < expected[0x86U] ? 1U : 0U));
                        expected[0U] = (unsigned char)low;
                        direction = page >= 128U ? 2U : 1U;
                        if (id != 8U && id != 51U) expected[0x46U + slot] = (unsigned char)direction;
                        expected[0x58U + slot] = mode ? prg[0x5fbfU + direction - 1U] :
                            (direction == 1U ? 16U : 240U);
                        mysmb_world_stun_enemy(&game, (mysmb_u8)slot, (mysmb_u8)source);
                        if (memcmp(expected, game.ram, sizeof(expected))) ++failures;
                        ++cases;
                    }
                }
            }
        }
    }
    printf("enemy stun cases=%lu failures=%u\n", cases, failures);
    return failures ? 1 : 0;
}
