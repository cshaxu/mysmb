#include <string.h>
#include "game/area.h"

static void setup(struct mysmb_game *game, mysmb_u8 *prg)
{
    mysmb_game_initialize(game);
    mysmb_game_bind_area_source(game, prg, 0x1c00U);
    game->ram[0xe7U] = 0x40U;
    game->ram[0xe8U] = 0x80U;
    game->ram[0x730U] = 0xffU;
    game->ram[0x731U] = 0xffU;
    game->ram[0x732U] = 0xffU;
}

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 prg[0x1c00];
    static const mysmb_u8 backgrounds[6] = {0U, 0x17U, 0x1aU, 0xc0U, 0xc1U, 0x54U};
    static const mysmb_u8 heights[7] = {0U, 1U, 127U, 128U, 129U, 144U, 255U};
    static const mysmb_u8 counts[7] = {1U, 2U, 13U, 13U, 1U, 1U, 1U};
    mysmb_u8 type, length, slot, edge, continuation, variant, i, expected;
    mysmb_u8 column, page, active, row, height, count, start;
    for (type = 0U; type < 4U; ++type)
    for (length = 0U; length < 16U; ++length)
    for (slot = 0U; slot < 6U; ++slot)
    for (edge = 0U; edge < 2U; ++edge)
    for (continuation = 0U; continuation < 2U; ++continuation)
    for (variant = 0U; variant < 6U; ++variant) {
        column = edge == 0U ? 0U : 15U;
        page = edge;
        prg[0x40U] = (mysmb_u8)((column << 4U) | 12U);
        prg[0x41U] = length;
        prg[0x42U] = 0xfdU;
        setup(&game, prg);
        game.ram[0x725U] = page;
        game.ram[0x726U] = column;
        game.ram[0x72aU] = page;
        game.ram[0x74eU] = type;
        if (continuation) {
            game.ram[0x732U] = 1U;
            game.ram[0x72cU] = 2U;
        }
        memset(&game.ram[0x46bU], 0xa5, 24U);
        game.ram[0x46aU] = slot;
        memset(&game.ram[0x6a1U], backgrounds[variant], 13U);
        if (!mysmb_area_process_object_state(&game)) return 1;
        active = type == 0U && continuation == 0U;
        if (game.ram[7U] != 12U || game.ram[0x735U] != 11U) return 2;
        expected = active ? (slot >= 4U ? 0U : (mysmb_u8)(slot + 1U)) : slot;
        if (game.ram[0x46aU] != expected) return 3;
        for (i = 0U; i < 6U; ++i) {
            expected = active && i == slot ? (edge == 0U ? 0xf0U : 0xe0U) : 0xa5U;
            if (game.ram[0x471U + i] != expected) return 4;
            expected = active && i == slot ? (edge == 0U ? 0xffU : 1U) : 0xa5U;
            if (game.ram[0x46bU + i] != expected) return 5;
            expected = active && i == slot ? (mysmb_u8)((length + 2U) << 4U) : 0xa5U;
            if (game.ram[0x477U + i] != expected || game.ram[0x47dU + i] != 0xa5U) return 6;
        }
        for (i = 0U; i < 13U; ++i) {
            expected = backgrounds[variant];
            if (i >= 8U && variant != 1U && variant != 2U && variant != 4U)
                expected = type == 0U ? 0x87U : 0U;
            if (game.ram[0x6a1U + i] != expected) return 7;
        }
        expected = continuation ? 0U : (mysmb_u8)(length - 1U);
        if (game.ram[0x732U] != expected) return 8;
    }
    /* A controlled staircase data lookup supplies exact byte-height/row
     * boundaries to its existing UnderPart tail, without a test-only API. */
    prg[0x40U] = 0x0fU;
    prg[0x41U] = 0x38U;
    for (start = 0U; start < 3U; ++start)
    for (height = 0U; height < 7U; ++height) {
        row = start == 0U ? 0U : (start == 1U ? 12U : 255U);
        prg[0x1ab7U] = row;
        prg[0x1aaeU] = heights[height];
        setup(&game, prg);
        game.ram[0x732U] = 0U;
        game.ram[0x72cU] = 2U;
        game.ram[0x734U] = 10U;
        memset(&game.ram[0x6a1U], 0, 13U);
        game.ram[0x7a0U] = 0U;
        if (!mysmb_area_process_object_state(&game)) return 9;
        count = start == 1U ? 1U : counts[height];
        if (start == 2U && (height == 2U || height == 3U)) count++;
        for (i = 0U; i < 13U; ++i) {
            expected = start == 0U ? (i < count ? 0x61U : 0U) :
                (start == 1U ? (i == 12U ? 0x61U : 0U) :
                 (i < count - 1U ? 0x61U : 0U));
            if (game.ram[0x6a1U + i] != expected) return 10;
        }
        if (game.ram[0x7a0U] != (start == 2U ? 0x61U : 0U)) return 11;
        if (game.ram[0x735U] != (mysmb_u8)(heights[height] - (count - 1U))) return 12;
    }
    /* The $50 mushroom stem must preserve cracked rock as well as ledge
     * centers/palette-three objects; other UnderPart callers overwrite rock. */
    prg[0x40U] = 0x65U;
    prg[0x41U] = 0x15U;
    for (variant = 0U; variant < 6U; ++variant) {
        setup(&game, prg);
        game.ram[0x726U] = 6U;
        game.ram[0x72cU] = 2U;
        game.ram[0x732U] = 2U;
        game.ram[0x733U] = 1U;
        game.ram[0x738U] = 2U;
        memset(&game.ram[0x6a1U], backgrounds[variant], 13U);
        if (!mysmb_area_process_object_state(&game)) return 13;
        for (i = 7U; i < 13U; ++i) {
            expected = variant == 0U || variant == 3U ? 0x50U : backgrounds[variant];
            if (game.ram[0x6a1U + i] != expected) return 14;
        }
        if (game.ram[0x735U] != 10U) return 15;
    }
    return 0;
}
