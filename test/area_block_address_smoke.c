#include <string.h>
#include "core/area.h"
#include "game/world/world.h"

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 before[2048];
    static mysmb_u8 prg[0x1600U];
    struct mysmb_player_terrain player;
    struct mysmb_enemy_terrain enemy;
    unsigned int column, i, page, x, probe;
    mysmb_u16 expected, address;
    mysmb_u8 next_page, next_x;
    static const mysmb_u8 adders[3] = { 0U, 4U, 16U };

    for (column = 0U; column < 32U; ++column) {
        memset(game.ram, 0xa6, sizeof(game.ram));
        memcpy(before, game.ram, sizeof(before));
        expected = (mysmb_u16)(0x500U + (column / 16U) * 0xd0U + column % 16U);
        address = mysmb_area_get_block_buffer_address(&game, (mysmb_u8)column);
        if (address != expected || game.ram[6] != (mysmb_u8)expected ||
            game.ram[7] != 5U) return 1;
        for (i = 0U; i < 2048U; ++i)
            if (i != 6U && i != 7U && game.ram[i] != before[i]) return 2;
    }
    /* RendBBuf must call the helper after object staging and leave the
     * indirect pointer intact. Verify neighboring physical columns too. */
    prg[0x13d9U] = 0x54U;
    prg[0x13ddU] = 0x18U;
    prg[0x1504U] = 0x10U; prg[0x1505U] = 0x51U;
    prg[0x1506U] = 0x88U; prg[0x1507U] = 0xc0U;
    for (column = 0U; column < 32U; ++column) {
        memset(&game, 0, sizeof(game));
        mysmb_game_bind_area_source(&game, prg, sizeof(prg));
        memset(game.ram + 0x500U, 0xa7, 0x1a0U);
        game.ram[0x74eU] = 1U;
        game.ram[0x6a0U] = (mysmb_u8)column;
        expected = (mysmb_u16)(0x500U + (column / 16U) * 0xd0U + column % 16U);
        if (mysmb_area_render_scenery_terrain_column(&game) == 0U ||
            game.ram[6U] != (mysmb_u8)expected || game.ram[7U] != 5U) return 6;
        for (i = 0x500U; i < 0x6a0U; ++i) {
            if (i >= expected && i <= expected + 0xc0U && (i - expected) % 16U == 0U) {
                if (game.ram[i] != (i >= expected + 0xb0U ? 0x54U : 0U)) return 7;
            } else if (game.ram[i] != 0xa7U) return 8;
        }
    }
    memset(&game, 0, sizeof(game));
    for (page = 0U; page < 256U; ++page)
    for (x = 0U; x < 256U; ++x) {
        game.ram[0x6dU] = (mysmb_u8)page;
        game.ram[0x86U] = (mysmb_u8)x;
        game.ram[0xceU] = 0x60U;
        for (probe = 0U; probe < 3U; ++probe) {
            next_x = (mysmb_u8)(x + adders[probe]);
            next_page = (mysmb_u8)(page + (x + adders[probe] > 255U ? 1U : 0U));
            expected = (mysmb_u16)(0x500U + (next_page % 2U) * 0xd0U + next_x / 16U);
            game.ram[expected + 0x40U] = 0x61U;
            game.ram[6U] = 0x77U; game.ram[7U] = 0x88U;
            if (mysmb_world_query_player_block(&game, adders[probe], 0U, 0U, &player) == 0U ||
                player.metatile != 0x61U || player.block_address_low != (mysmb_u8)expected ||
                game.ram[6U] != (mysmb_u8)expected || game.ram[7U] != 5U) return 3;
        }
        next_x = (mysmb_u8)(x + 16U);
        next_page = (mysmb_u8)(page + (x >= 240U ? 1U : 0U));
        expected = (mysmb_u16)(0x500U + (next_page % 2U) * 0xd0U + next_x / 16U);
        game.ram[0x6eU] = (mysmb_u8)page;
        game.ram[0x87U] = (mysmb_u8)x;
        game.ram[0xcfU] = 0x60U;
        game.ram[expected + 0x50U] = 0x62U;
        game.ram[6U] = 0x77U; game.ram[7U] = 0x88U;
        if (mysmb_world_query_enemy_block(&game, 0U, 0x17U, 1U, &enemy) == 0U ||
            enemy.metatile != 0x62U || enemy.block_address != expected + 0x50U ||
            game.ram[6U] != (mysmb_u8)expected || game.ram[7U] != 5U) return 4;
        next_x = (mysmb_u8)(x + 4U);
        next_page = (mysmb_u8)(page + (x >= 252U ? 1U : 0U));
        expected = (mysmb_u16)(0x500U + (next_page % 2U) * 0xd0U + next_x / 16U);
        game.ram[0x74U] = (mysmb_u8)page;
        game.ram[0x8dU] = (mysmb_u8)x;
        game.ram[0xd5U] = 0x60U;
        game.ram[expected + 0x40U] = 0U;
        game.ram[6U] = 0x77U; game.ram[7U] = 0x88U;
        mysmb_world_fireball_background_collision(&game, 0U);
        if (game.ram[6U] != (mysmb_u8)expected || game.ram[7U] != 5U) return 5;
    }
    return 0;
}
