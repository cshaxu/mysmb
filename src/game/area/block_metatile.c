#include "game/area.h"

enum {
    MYSMB_VRAM_BUFFER1 = 0x0300U,
    MYSMB_VRAM_BUFFER1_DATA = 0x0301U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_BLOCK_ORIGINAL_Y = 0x03e4U,
    MYSMB_BLOCK_BUFFER_LOW = 0x03e6U,
    MYSMB_BLOCK_METATILE = 0x03e8U,
    MYSMB_BLOCK_REPLACE_FLAG = 0x03ecU,
    MYSMB_BLOCK_RESIDUAL_COUNTER = 0x03f0U,
    MYSMB_BLOCK_GFX_DATA = 0x0a39U
};

/* ROM $8a39 BlockGfxData.  This remains source-owned data rather than a
 * duplicate C literal: area_prg is the admitted local copy of the PRG. */
static mysmb_u8 mysmb_area_block_gfx(struct mysmb_game *game, mysmb_u8 index)
{
    if (game->area_prg == 0 || game->area_prg_size < MYSMB_BLOCK_GFX_DATA + 20U)
        return 0U;
    return game->area_prg[MYSMB_BLOCK_GFX_DATA + index];
}

/* ROM $8ab1-$8adf PutBlockMetatile -> RemBridge.  The temporary zero-page
 * cells are part of the ROM routine's observable machine state, so preserve
 * the source stores instead of using private C-only temporaries. */
static void mysmb_area_put_block_metatile(struct mysmb_game *game,
                                          mysmb_u8 graphics_set,
                                          mysmb_u8 buffer_offset,
                                          mysmb_u8 control,
                                          mysmb_u8 block_low,
                                          mysmb_u8 vertical_high)
{
    mysmb_u8 graphics_offset;
    mysmb_u8 address_low;
    mysmb_u8 address_high;
    mysmb_u16 address;

    if (game->area_prg == 0 || game->area_prg_size < MYSMB_BLOCK_GFX_DATA + 20U)
        return;
    game->ram[0x0000U] = control;
    game->ram[0x0001U] = buffer_offset;
    game->ram[0x0002U] = vertical_high;
    game->ram[0x0006U] = block_low;
    graphics_offset = (mysmb_u8)(graphics_set << 2U);
    game->ram[0x0003U] = block_low < 0xd0U ? 0x20U : 0x24U;
    address_low = (mysmb_u8)((block_low & 0x0fU) << 1U);
    game->ram[0x0004U] = address_low;
    game->ram[0x0005U] = 0U;
    address = (mysmb_u16)(((mysmb_u16)(vertical_high + 0x20U) << 2U) +
                          address_low);
    address_low = (mysmb_u8)address;
    address_high = (mysmb_u8)(game->ram[0x0003U] + (address >> 8U));
    game->ram[0x0004U] = address_low;
    game->ram[0x0005U] = address_high;
    mysmb_area_rem_bridge(game, graphics_offset, buffer_offset, address_low,
                          address_high);
}

/* ROM $8a6d-$8ab0 WriteBlockMetatile/UseBOffset/MoveVOffset. */
static void mysmb_area_write_block_metatile(struct mysmb_game *game,
                                            mysmb_u8 metatile,
                                            mysmb_u8 control,
                                            mysmb_u8 block_low,
                                            mysmb_u8 vertical_high)
{
    mysmb_u8 graphics_set;
    mysmb_u8 buffer_offset;

    if (game->ram[MYSMB_VRAM_BUFFER1] > 0xf5U) return;
    graphics_set = 2U;
    if (metatile == 0U) graphics_set = 3U;
    else if (metatile == 0x58U || metatile == 0x51U) graphics_set = 0U;
    else if (metatile == 0x5dU || metatile == 0x52U) graphics_set = 1U;
    buffer_offset = (mysmb_u8)(game->ram[MYSMB_VRAM_BUFFER1] + 1U);
    mysmb_area_put_block_metatile(game, graphics_set, buffer_offset, control,
                                  block_low, vertical_high);
    mysmb_area_move_v_offset(game, buffer_offset);
}

/* ROM $8A8F MoveVOffset -> SetVRAMOffset; input is the preserved Y byte. */
void mysmb_area_move_v_offset(struct mysmb_game *game, mysmb_u8 buffer_offset)
{
    --buffer_offset;
    game->ram[MYSMB_VRAM_BUFFER1] = (mysmb_u8)(buffer_offset + 10U);
}

/* ROM $8a4d-$8a60 RemoveCoin_Axe -> WriteBlankMT. */
void mysmb_area_remove_coin_axe(struct mysmb_game *game, mysmb_u8 block_low,
                                 mysmb_u8 vertical_high)
{
    mysmb_u8 graphics_set;

    graphics_set = game->ram[MYSMB_AREA_TYPE] == 0U ? 4U : 3U;
    mysmb_area_put_block_metatile(game, graphics_set, 0x41U, 0U, block_low,
                                  vertical_high);
    game->ram[0x0773U] = 6U;
}

/* ROM $8a69-$8a6c DestroyBlockMetatile. */
void mysmb_area_destroy_block_metatile(struct mysmb_game *game,
                                       mysmb_u8 control, mysmb_u8 block_low,
                                       mysmb_u8 vertical_high)
{
    mysmb_area_write_block_metatile(game, 0U, control, block_low, vertical_high);
}

/* ROM $8a61-$8a68 ReplaceBlockMetatile. */
void mysmb_area_replace_block_metatile(struct mysmb_game *game,
                                              mysmb_u8 slot)
{
    mysmb_area_write_block_metatile(game, game->ram[MYSMB_BLOCK_METATILE + slot],
                                    slot, game->ram[MYSMB_BLOCK_BUFFER_LOW + slot],
                                    game->ram[MYSMB_BLOCK_ORIGINAL_Y + slot]);
    game->ram[MYSMB_BLOCK_RESIDUAL_COUNTER]++;
    game->ram[MYSMB_BLOCK_REPLACE_FLAG + slot]--;
}

/* ROM $8ad0 RemBridge.  BridgeCollapse supplies $04/$05 directly, while
 * PutBlockMetatile supplies them through its preceding address calculation. */
void mysmb_area_rem_bridge(struct mysmb_game *game, mysmb_u8 graphics_offset,
                           mysmb_u8 buffer_offset, mysmb_u8 address_low,
                           mysmb_u8 address_high)
{
    if (game->area_prg == 0 || game->area_prg_size < MYSMB_BLOCK_GFX_DATA + 20U)
        return;
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset] = address_high;
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 1U] = address_low;
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 2U] = 2U;
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 3U] =
        mysmb_area_block_gfx(game, graphics_offset);
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 4U] =
        mysmb_area_block_gfx(game, (mysmb_u8)(graphics_offset + 1U));
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 5U] = address_high;
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 6U] =
        (mysmb_u8)(address_low + 0x20U);
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 7U] = 2U;
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 8U] =
        mysmb_area_block_gfx(game, (mysmb_u8)(graphics_offset + 2U));
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 9U] =
        mysmb_area_block_gfx(game, (mysmb_u8)(graphics_offset + 3U));
    game->ram[MYSMB_VRAM_BUFFER1 + buffer_offset + 10U] = 0U;
}
