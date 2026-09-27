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
    if (verify_renderer(0U, 0U) != 0) return 1;
    if (verify_renderer(1U, 1U) != 0) return 1;
    return 0;
}
