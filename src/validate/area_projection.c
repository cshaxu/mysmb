#include "validate/area_projection.h"

/* Test-only page projection;not the translated VRAM packet writer. */
enum {
    MYSMB_AREA_METATILE_LOW = 0x0b08U,
    MYSMB_AREA_METATILE_HIGH = 0x0b0cU
};

/* ROM $88ae-$8990 RenderAreaGraphics/RenderAttributeTables.  The collision
 * block buffer stores a 16-by-13 metatile page; the original graphics tables
 * at $8b08 select four CHR tile numbers for each encoded metatile. */
void mysmb_area_refresh_background_page(struct mysmb_game *game,
                                        mysmb_u8 page)
{
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u8 metatile;
    mysmb_u8 palette;
    mysmb_u8 table;
    mysmb_u8 attribute_shift;
    mysmb_u16 block_address;
    mysmb_u16 graphics_address;
    mysmb_u16 tile_offset;
    mysmb_u16 attribute_offset;

    if (game->area_prg == 0 || game->area_prg_size <= MYSMB_AREA_METATILE_HIGH + 3U)
        return;
    table = (mysmb_u8)(page & 1U);
    for (column = 0U; column < 16U; ++column) {
        for (row = 0U; row < 13U; ++row) {
            block_address = (mysmb_u16)((table != 0U ? 0x05d0U : 0x0500U) +
                column + (mysmb_u16)row * 16U);
            metatile = game->ram[block_address];
            palette = (mysmb_u8)(metatile >> 6U);
            graphics_address = (mysmb_u16)(game->area_prg[
                MYSMB_AREA_METATILE_LOW + palette] |
                ((mysmb_u16)game->area_prg[MYSMB_AREA_METATILE_HIGH + palette] << 8U));
            if (graphics_address < 0x8000U) continue;
            graphics_address = (mysmb_u16)(graphics_address - 0x8000U);
            tile_offset = (mysmb_u16)(graphics_address +
                (mysmb_u16)(metatile & 0x3fU) * 4U);
            if ((mysmb_u16)(tile_offset + 3U) >= game->area_prg_size) continue;
            tile_offset = (mysmb_u16)(4U * 32U + (mysmb_u16)row * 2U * 32U +
                (mysmb_u16)column * 2U);
            game->ppu.name_table[table][tile_offset] = game->area_prg[(mysmb_u16)(graphics_address +
                (mysmb_u16)(metatile & 0x3fU) * 4U)];
            game->ppu.name_table[table][(mysmb_u16)(tile_offset + 1U)] = game->area_prg[
                (mysmb_u16)(graphics_address + (mysmb_u16)(metatile & 0x3fU) * 4U + 2U)];
            game->ppu.name_table[table][(mysmb_u16)(tile_offset + 32U)] = game->area_prg[
                (mysmb_u16)(graphics_address + (mysmb_u16)(metatile & 0x3fU) * 4U + 1U)];
            game->ppu.name_table[table][(mysmb_u16)(tile_offset + 33U)] = game->area_prg[
                (mysmb_u16)(graphics_address + (mysmb_u16)(metatile & 0x3fU) * 4U + 3U)];
            attribute_offset = (mysmb_u16)(0x03c0U + ((row >> 1U) + 1U) * 8U +
                (column >> 1U));
            attribute_shift = (mysmb_u8)(((row & 1U) << 2U) | ((column & 1U) << 1U));
            game->ppu.name_table[table][attribute_offset] = (mysmb_u8)(
                (game->ppu.name_table[table][attribute_offset] &
                (mysmb_u8)~(0x03U << attribute_shift)) | (palette << attribute_shift));
        }
    }
}
