#include <string.h>

#include "game/area.h"
#include "game/game.h"
#include "smb1_local_rom.h"

/* Exercise the exact $88ae renderer entry independently of the later parser
 * owner.  The two calls cover both source tile sides, all four attribute
 * quadrants, the low-name-table wrap and the seven-command attribute tail. */
static int verify_renderer(mysmb_u8 parser_task, mysmb_u8 column)
{
    static const mysmb_u8 metatiles[13] = {
        0x00U, 0x41U, 0x82U, 0xc3U, 0x04U, 0x45U, 0x86U,
        0xc7U, 0x08U, 0x49U, 0x8aU, 0xcbU, 0x0cU
    };
    struct mysmb_game game;
    mysmb_u8 expected_attributes[7];
    mysmb_u8 index;
    mysmb_u8 row;
    mysmb_u8 palette;
    mysmb_u8 shift;
    mysmb_u8 side;
    mysmb_u16 graphics;
    mysmb_u16 source;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    memset(expected_attributes, 0, sizeof(expected_attributes));
    game.ram[0x0340U] = 0U;
    game.ram[0x071fU] = parser_task;
    game.ram[0x0726U] = column;
    game.ram[0x0721U] = 0x9fU;
    game.ram[0x0720U] = 0x20U;
    for (row = 0U; row < 13U; ++row)
        game.ram[(mysmb_u16)(0x06a1U + row)] = metatiles[row];

    if (mysmb_area_render_graphics(&game) == 0U) return 1;
    if (game.ram[0x0341U] != 0x20U || game.ram[0x0342U] != 0x9fU ||
        game.ram[0x0343U] != 0x9aU || game.ram[0x035eU] != 0U ||
        game.ram[0x0340U] != 29U || game.ram[0x0721U] != 0x80U ||
        game.ram[0x0720U] != 0x24U || game.ram[0x0773U] != 6U) return 1;
    if (game.ram[0U] != 26U || game.ram[1U] != 12U ||
        game.ram[2U] != 0x30U || game.ram[3U] != 0U ||
        game.ram[4U] != 6U || game.ram[5U] != (column & 1U) ||
        game.ram[6U] != mysmb_local_prg[0x0b08U] ||
        game.ram[7U] != mysmb_local_prg[0x0b0cU]) return 1;

    side = (parser_task & 1U) != 0U ? 0U : 2U;
    for (row = 0U; row < 13U; ++row) {
        palette = (mysmb_u8)(metatiles[row] >> 6U);
        graphics = (mysmb_u16)(mysmb_local_prg[0x0b08U + palette] |
            ((mysmb_u16)mysmb_local_prg[0x0b0cU + palette] << 8U));
        if (graphics < 0x8000U) return 1;
        source = (mysmb_u16)(graphics - 0x8000U +
            (mysmb_u16)(metatiles[row] & 0x3fU) * 4U + side);
        if (game.ram[(mysmb_u16)(0x0344U + (mysmb_u16)row * 2U)] !=
                mysmb_local_prg[source] ||
            game.ram[(mysmb_u16)(0x0345U + (mysmb_u16)row * 2U)] !=
                mysmb_local_prg[(mysmb_u16)(source + 1U)]) return 1;

        if ((column & 1U) != 0U)
            shift = (row & 1U) != 0U ? 6U : 2U;
        else
            shift = (row & 1U) != 0U ? 4U : 0U;
        expected_attributes[row >> 1U] |= (mysmb_u8)(palette << shift);
    }
    for (index = 0U; index < 7U; ++index) {
        if (game.ram[(mysmb_u16)(0x03f9U + index)] != expected_attributes[index])
            return 1;
    }

    if (mysmb_area_render_attribute_tables(&game) == 0U) return 1;
    if (game.ram[0x0340U] != 57U || game.ram[0x037aU] != 0U ||
        game.ram[0x0773U] != 6U) return 1;
    if (game.ram[0U] != 0x23U || game.ram[1U] != 0xffU) return 1;
    for (index = 0U; index < 7U; ++index) {
        if (game.ram[(mysmb_u16)(0x035eU + (mysmb_u16)index * 4U)] != 0x23U ||
            game.ram[(mysmb_u16)(0x035fU + (mysmb_u16)index * 4U)] !=
                (mysmb_u8)(0xcfU + (mysmb_u8)(index * 8U)) ||
            game.ram[(mysmb_u16)(0x0360U + (mysmb_u16)index * 4U)] != 1U ||
            game.ram[(mysmb_u16)(0x0361U + (mysmb_u16)index * 4U)] !=
                expected_attributes[index] ||
            game.ram[(mysmb_u16)(0x03f9U + index)] != 0U) return 1;
    }
    return 0;
}

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 row;
    mysmb_u16 graphics;
    if (verify_renderer(0U, 0U) != 0) return 1;
    if (verify_renderer(1U, 1U) != 0) return 1;
    /* Controlled alias from the original $896a entry: an early payload
     * overwrites a later attribute source. Reading after the length write
     * would replace this value with one. */
    mysmb_game_initialize(&game);
    game.ram[0x0340U] = 0xb6U;
    game.ram[0x0721U] = 0x80U;
    game.ram[0x0720U] = 0x20U;
    game.ram[0x03f9U] = 0x5aU;
    if (mysmb_area_render_attribute_tables(&game) == 0U ||
        game.ram[0x040eU] != 0x5aU) return 1;
    /* Original DrawMTLoop wraps its byte X cursor, while absolute-X
     * displacements remain outside the wrap. Row eight resumes at $0344,
     * not $0444; the header itself still uses the incoming $f0 offset. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    game.ram[0x0340U] = 0xf0U;
    game.ram[0x0720U] = 0x20U;
    game.ram[0x0721U] = 0x80U;
    game.ram[0x0444U] = 0xa5U;
    for (row = 0U; row < 13U; ++row) game.ram[0x06a1U + row] = 0U;
    graphics = (mysmb_u16)(mysmb_local_prg[0x0b08U] |
        ((mysmb_u16)mysmb_local_prg[0x0b0cU] << 8U));
    if (mysmb_area_render_graphics(&game) == 0U ||
        game.ram[0x0340U] != 0x0dU || game.ram[0x034eU] != 0U ||
        game.ram[0x0431U] != 0x20U || game.ram[0x0433U] != 0x9aU ||
        game.ram[0x0344U] != mysmb_local_prg[graphics - 0x8000U + 2U] ||
        game.ram[0x0444U] != 0xa5U) return 2;
    /* AttribLoop uses absolute-Y displacements before incrementing Y.
     * At Y=$ff, the low/length/payload remain at $0441-$0443. */
    mysmb_game_initialize(&game);
    game.ram[0x0340U] = 0xffU;
    game.ram[0x0720U] = 0x20U;
    game.ram[0x0721U] = 0x80U;
    game.ram[0x0341U] = 0xa5U;
    for (row = 0U; row < 7U; ++row)
        game.ram[0x03f9U + row] = (mysmb_u8)(row + 1U);
    if (mysmb_area_render_attribute_tables(&game) == 0U ||
        game.ram[0x0340U] != 0x1bU || game.ram[0x035cU] != 0U ||
        game.ram[0x0441U] != 0xcfU || game.ram[0x0442U] != 1U ||
        game.ram[0x0443U] != 1U || game.ram[0x0347U] != 2U ||
        game.ram[0x0341U] != 0xa5U) return 3;
    return 0;
}
