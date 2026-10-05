#include <string.h>

#include "core/area.h"
#include "core/game.h"
#include "smb1_local_rom.h"

enum {
    MYSMB_METATILE_POINTER_LOW = 0x0b08U,
    MYSMB_METATILE_POINTER_HIGH = 0x0b0cU,
    MYSMB_PALETTE0_METATILES = 0x0b10U,
    MYSMB_PALETTE1_METATILES = 0x0bacU,
    MYSMB_PALETTE2_METATILES = 0x0c64U,
    MYSMB_PALETTE3_METATILES = 0x0c8cU,
    MYSMB_WATER_PALETTE = 0x0ca4U,
    MYSMB_GROUND_PALETTE = 0x0cc8U,
    MYSMB_UNDERGROUND_PALETTE = 0x0cecU,
    MYSMB_CASTLE_PALETTE = 0x0d10U,
    MYSMB_DAY_SNOW_PALETTE = 0x0d34U,
    MYSMB_NIGHT_SNOW_PALETTE = 0x0d3cU,
    MYSMB_MUSHROOM_PALETTE = 0x0d44U,
    MYSMB_BOWSER_PALETTE = 0x0d4cU,
    MYSMB_MARIO_THANKS = 0x0d54U,
    MYSMB_LUIGI_THANKS = 0x0d68U,
    MYSMB_RETAINER_SAVED = 0x0d7cU,
    MYSMB_PRINCESS_SAVED1 = 0x0da8U,
    MYSMB_PRINCESS_SAVED2 = 0x0dbfU,
    MYSMB_WORLD_SELECT1 = 0x0ddeU,
    MYSMB_WORLD_SELECT2 = 0x0defU
};

static mysmb_u8 palette_index(mysmb_u8 offset)
{
    if (offset == 0x10U || offset == 0x14U || offset == 0x18U ||
        offset == 0x1cU) {
        return (mysmb_u8)(offset - 0x10U);
    }
    return offset;
}

static int verify_metatile_table(mysmb_u8 palette, mysmb_u16 start,
                                 mysmb_u16 end)
{
    struct mysmb_game game;
    mysmb_u16 pointer;
    mysmb_u16 entry_count;
    mysmb_u16 source;
    mysmb_u16 tile_offset;
    mysmb_u16 block_offset;
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u8 metatile;

    pointer = (mysmb_u16)(mysmb_local_prg[MYSMB_METATILE_POINTER_LOW + palette] |
        ((mysmb_u16)mysmb_local_prg[MYSMB_METATILE_POINTER_HIGH + palette] << 8U));
    if (pointer != (mysmb_u16)(0x8000U + start) || end <= start ||
        (mysmb_u16)(end - start) % 4U != 0U) return 1;
    entry_count = (mysmb_u16)((end - start) / 4U);

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    for (column = 0U; column < 16U; ++column) {
        for (row = 0U; row < 13U; ++row) {
            block_offset = (mysmb_u16)(0x0500U + column + (mysmb_u16)row * 16U);
            metatile = (mysmb_u8)(((mysmb_u16)column +
                (mysmb_u16)row * 16U) % entry_count);
            game.ram[block_offset] = (mysmb_u8)((palette << 6U) | metatile);
        }
    }
    mysmb_area_refresh_background_page(&game, 0U);

    for (column = 0U; column < 16U; ++column) {
        for (row = 0U; row < 13U; ++row) {
            metatile = (mysmb_u8)(((mysmb_u16)column +
                (mysmb_u16)row * 16U) % entry_count);
            source = (mysmb_u16)(start + (mysmb_u16)metatile * 4U);
            tile_offset = (mysmb_u16)(128U + (mysmb_u16)row * 64U +
                (mysmb_u16)column * 2U);
            if (game.ppu.name_table[0U][tile_offset] != mysmb_local_prg[source] ||
                game.ppu.name_table[0U][(mysmb_u16)(tile_offset + 1U)] !=
                    mysmb_local_prg[(mysmb_u16)(source + 2U)] ||
                game.ppu.name_table[0U][(mysmb_u16)(tile_offset + 32U)] !=
                    mysmb_local_prg[(mysmb_u16)(source + 1U)] ||
                game.ppu.name_table[0U][(mysmb_u16)(tile_offset + 33U)] !=
                    mysmb_local_prg[(mysmb_u16)(source + 3U)]) return 1;
        }
    }
    return 0;
}

static int verify_palette_stream(mysmb_u16 offset, mysmb_u8 control)
{
    struct mysmb_game game;
    mysmb_u8 expected[0x20U];
    mysmb_u8 index;
    mysmb_u8 count;

    count = mysmb_local_prg[(mysmb_u16)(offset + 2U)];
    if (mysmb_local_prg[offset] != 0x3fU || count == 0U || count > 0x20U ||
        mysmb_local_prg[(mysmb_u16)(offset + 3U + count)] != 0U) return 1;
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    memcpy(expected, game.ppu.palette, sizeof(expected));
    for (index = 0U; index < count; ++index) {
        expected[palette_index((mysmb_u8)(mysmb_local_prg[(mysmb_u16)(offset + 1U)] +
            index))] = mysmb_local_prg[(mysmb_u16)(offset + 3U + index)];
    }
    if (control < 4U) {
        if (mysmb_area_apply_palette(&game, control) == 0U) return 1;
    }
    else if (mysmb_area_apply_special_palette(&game, control) == 0U) {
        return 1;
    }
    return memcmp(expected, game.ppu.palette, sizeof(expected)) == 0 ? 0 : 1;
}

static int expected_message_output(const mysmb_u8 *stream, mysmb_u16 size,
                                   mysmb_u8 expected[2][0x400U])
{
    mysmb_u16 cursor;
    mysmb_u16 address;
    mysmb_u16 offset;
    mysmb_u8 table;
    mysmb_u8 control;
    mysmb_u8 count;
    mysmb_u8 index;
    mysmb_u8 value;

    cursor = 0U;
    while (cursor < size && stream[cursor] != 0U) {
        if ((mysmb_u16)(size - cursor) < 3U) return 1;
        address = (mysmb_u16)(((mysmb_u16)stream[cursor] << 8U) |
            stream[(mysmb_u16)(cursor + 1U)]);
        control = stream[(mysmb_u16)(cursor + 2U)];
        count = (mysmb_u8)(control & 0x3fU);
        if (address < 0x2000U || address >= 0x2800U || count == 0U ||
            (mysmb_u16)(size - cursor) < (mysmb_u16)(3U + count)) return 1;
        table = (mysmb_u8)((address - 0x2000U) / 0x400U);
        offset = (mysmb_u16)(address & 0x03ffU);
        for (index = 0U; index < count; ++index) {
            value = stream[(mysmb_u16)(cursor + 3U + index)];
            if (offset >= 0x400U) return 1;
            expected[table][offset] = value;
            offset = (mysmb_u16)(offset + ((control & 0x80U) != 0U ? 32U : 1U));
        }
        cursor = (mysmb_u16)(cursor + 3U + count);
    }
    return cursor < size && stream[cursor] == 0U ? 0 : 1;
}

static int verify_message_stream(mysmb_u16 offset, mysmb_u16 size,
                                 mysmb_u8 address_control)
{
    struct mysmb_game game;
    mysmb_u8 expected[2][0x400U];

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    memcpy(expected, game.ppu.name_table, sizeof(expected));
    if (expected_message_output(&mysmb_local_prg[offset], size, expected) != 0 ||
        mysmb_area_apply_message(&game, address_control) == 0U) return 1;
    return memcmp(expected, game.ppu.name_table, sizeof(expected)) == 0 ? 0 : 1;
}

int main(void)
{
    if (verify_metatile_table(0U, MYSMB_PALETTE0_METATILES,
                              MYSMB_PALETTE1_METATILES) != 0 ||
        verify_metatile_table(1U, MYSMB_PALETTE1_METATILES,
                              MYSMB_PALETTE2_METATILES) != 0 ||
        verify_metatile_table(2U, MYSMB_PALETTE2_METATILES,
                              MYSMB_PALETTE3_METATILES) != 0 ||
        verify_metatile_table(3U, MYSMB_PALETTE3_METATILES,
                              MYSMB_WATER_PALETTE) != 0) return 1;

    if (verify_palette_stream(MYSMB_WATER_PALETTE, 0U) != 0 ||
        verify_palette_stream(MYSMB_GROUND_PALETTE, 1U) != 0 ||
        verify_palette_stream(MYSMB_UNDERGROUND_PALETTE, 2U) != 0 ||
        verify_palette_stream(MYSMB_CASTLE_PALETTE, 3U) != 0 ||
        verify_palette_stream(MYSMB_BOWSER_PALETTE, 8U) != 0 ||
        verify_palette_stream(MYSMB_DAY_SNOW_PALETTE, 9U) != 0 ||
        verify_palette_stream(MYSMB_NIGHT_SNOW_PALETTE, 10U) != 0 ||
        verify_palette_stream(MYSMB_MUSHROOM_PALETTE, 11U) != 0) return 1;

    if (verify_message_stream(MYSMB_MARIO_THANKS, 0x14U, 12U) != 0 ||
        verify_message_stream(MYSMB_LUIGI_THANKS, 0x14U, 13U) != 0 ||
        verify_message_stream(MYSMB_RETAINER_SAVED, 0x2cU, 14U) != 0 ||
        verify_message_stream(MYSMB_PRINCESS_SAVED1, 0x17U, 15U) != 0 ||
        verify_message_stream(MYSMB_PRINCESS_SAVED2, 0x1fU, 16U) != 0 ||
        verify_message_stream(MYSMB_WORLD_SELECT1, 0x11U, 17U) != 0 ||
        verify_message_stream(MYSMB_WORLD_SELECT2, 0x15U, 18U) != 0) return 1;
    return 0;
}
