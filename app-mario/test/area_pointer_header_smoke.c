#include <string.h>
#include "core/area.h"
#include "smb1_local_rom.h"

static struct mysmb_game game;
static mysmb_u8 prg[0x2100U];
static mysmb_u8 before[2048];

static int header_byte(mysmb_u8 first, mysmb_u8 second, mysmb_u16 pointer)
{
    struct mysmb_area_source source;
    unsigned int i;
    mysmb_u16 offset;
    source.prg = prg; source.prg_size = sizeof(prg);
    offset = (mysmb_u16)(pointer - 0x8000U);
    prg[offset] = first; prg[offset + 1U] = second;
    memset(game.ram, 0xa7, sizeof(game.ram));
    game.ram[0xe7U] = (mysmb_u8)pointer;
    game.ram[0xe8U] = (mysmb_u8)(pointer >> 8U);
    memcpy(before, game.ram, sizeof(before));
    if (mysmb_area_parse_header(&game, &source) == 0U) return 1;
    before[0x741U] = (first & 7U) < 4U ? (mysmb_u8)(first & 7U) : 0U;
    if ((first & 7U) >= 4U) before[0x744U] = (mysmb_u8)(first & 7U);
    before[0x710U] = (mysmb_u8)((first / 8U) % 8U);
    before[0x715U] = (mysmb_u8)(first / 64U);
    before[0x727U] = (mysmb_u8)(second % 16U);
    before[0x742U] = (mysmb_u8)((second / 16U) % 4U);
    before[0x733U] = second >= 192U ? 0U : (mysmb_u8)(second / 64U);
    if (second >= 192U) before[0x743U] = 3U;
    pointer = (mysmb_u16)(pointer + 2U);
    before[0xe7U] = (mysmb_u8)pointer; before[0xe8U] = (mysmb_u8)(pointer >> 8U);
    for (i = 0U; i < sizeof(before); ++i)
        if (game.ram[i] != before[i]) return 2;
    return 0;
}

int main(void)
{
    struct mysmb_area_source source;
    unsigned int a, b, world, i, slot, alias;
    mysmb_u8 pointer, expected, type, low, index;
    mysmb_u16 address, enemy;
    static const mysmb_u8 counts[4] = { 3U, 22U, 3U, 6U };
    source.prg = prg; source.prg_size = sizeof(prg);
    for (i = 0U; i < 256U; ++i) prg[0x1cbcU+i] = (mysmb_u8)(i*37U+9U);
    for (world = 0U; world < 8U; ++world) prg[0x1cb4U+world] = (mysmb_u8)(239U+world*9U);
    for (world = 0U; world < 8U; ++world)
    for (a = 0U; a < 256U; ++a) {
        memset(game.ram, 0xa7, sizeof(game.ram));
        game.ram[0x75fU] = (mysmb_u8)world; game.ram[0x760U] = (mysmb_u8)a;
        memcpy(before, game.ram, sizeof(before));
        expected = prg[0x1cbcU + (mysmb_u8)(prg[0x1cb4U+world] + a)];
        if (mysmb_area_find_area_pointer(&game, &source, &pointer) == 0U ||
            pointer != expected || memcmp(before, game.ram, sizeof(before)) != 0) return 1;
        if (mysmb_area_load_area_pointer(&game, &source) == 0U) return 2;
        before[0x750U] = expected; before[0x74eU] = (mysmb_u8)((expected / 32U) % 4U);
        if (memcmp(before, game.ram, sizeof(before)) != 0) return 3;
    }
    for (a = 0U; a < 256U; ++a) {
        if (mysmb_area_get_area_type(&game, (mysmb_u8)a) != (a / 32U) % 4U ||
            game.ram[0x74eU] != (a / 32U) % 4U) return 4;
    }
    for (a = 0U; a < 256U; ++a)
    for (b = 0U; b < 256U; ++b)
        if (header_byte((mysmb_u8)a, (mysmb_u8)b, 0x8040U) != 0) return 5;
    for (a = 0U; a < 256U; ++a)
        if (header_byte((mysmb_u8)a, (mysmb_u8)(255U-a), (mysmb_u16)(0x8000U+a)) != 0) return 6;

    source.prg = mysmb_local_prg; source.prg_size = MYSMB_LOCAL_PRG_SIZE;
    for (type = 0U; type < 4U; ++type)
    for (slot = 0U; slot < counts[type]; ++slot)
    for (alias = 0U; alias < 2U; ++alias) {
        low = (mysmb_u8)slot;
        pointer = (mysmb_u8)(type*32U + low + alias*128U);
        index = (mysmb_u8)(mysmb_local_prg[0x1ce0U+type] + low);
        enemy = (mysmb_u16)(mysmb_local_prg[0x1ce4U+index] | ((mysmb_u16)mysmb_local_prg[0x1d06U+index] << 8U));
        index = (mysmb_u8)(mysmb_local_prg[0x1d28U+type] + low);
        address = (mysmb_u16)(mysmb_local_prg[0x1d2cU+index] | ((mysmb_u16)mysmb_local_prg[0x1d4eU+index] << 8U));
        memset(&game, 0, sizeof(game));
        game.ram[0x750U] = pointer; game.ram[0x74eU] = 0xfeU; game.ram[0x74fU] = 0xffU;
        game.ram[0x744U] = 0xa7U; game.ram[0x743U] = 0xa7U;
        if (mysmb_area_get_data_addresses(&game, &source) == 0U) return 7;
        if (game.ram[0x74eU] != type || game.ram[0x74fU] != low || game.ram[0x750U] != pointer ||
            game.ram[0xe9U] != (mysmb_u8)enemy || game.ram[0xeaU] != (mysmb_u8)(enemy >> 8U) ||
            game.ram[0xe7U] != (mysmb_u8)(address+2U) || game.ram[0xe8U] != (mysmb_u8)((address+2U) >> 8U)) return 8;
        /* The real InitializeArea caller applies halfway entrance override
         * after the header, and consumes exactly one header. */
        mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
        game.ram[0x75bU] = 3U;
        mysmb_area_initialize(&game);
        if (game.ram[0x710U] != 2U || game.ram[0x6a0U] != 0x10U ||
            game.ram[0xe7U] != (mysmb_u8)(address+2U) || game.ram[0xe8U] != (mysmb_u8)((address+2U) >> 8U)) return 9;
    }
    return 0;
}
