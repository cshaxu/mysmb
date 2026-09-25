#include "game/area.h"

enum {
    MYSMB_VRAM_BUFFER1 = 0x0300U,
    MYSMB_VRAM_BUFFER1_DATA = 0x0301U,
    MYSMB_BLOCK_ORIGINAL_Y = 0x03e4U,
    MYSMB_BLOCK_BUFFER_LOW = 0x03e6U,
    MYSMB_BLOCK_METATILE = 0x03e8U,
    MYSMB_BLOCK_REPLACE_FLAG = 0x03ecU
};
/* Translation of ROM $bed4 BlockObjMT_Updater together with the static
 * WriteBlockMetatile/PutBlockMetatile command encoding at $2027-$209d.
 * One pending VRAM_Buffer1 command prevents the source loop from processing
 * its other block slot until the following NMI has consumed this update. */
void mysmb_area_apply_block_replacements(struct mysmb_game *game)
{
    static const mysmb_u8 block_graphics[20] = {
        0x45U, 0x45U, 0x47U, 0x47U,
        0x47U, 0x47U, 0x47U, 0x47U,
        0x57U, 0x58U, 0x59U, 0x5aU,
        0x24U, 0x24U, 0x24U, 0x24U,
        0x26U, 0x26U, 0x26U, 0x26U
    };
    mysmb_u8 slot;
    mysmb_u8 index;
    mysmb_u8 buffer_offset;
    mysmb_u8 graphics_index;
    mysmb_u8 low;
    mysmb_u8 high;
    mysmb_u16 address;

    for (slot = 2U; slot != 0U; --slot) {
        index = (mysmb_u8)(slot - 1U);
        if (game->ram[MYSMB_VRAM_BUFFER1_DATA] != 0U) continue;
        if (game->ram[MYSMB_BLOCK_REPLACE_FLAG + index] == 0U) continue;
        address = (mysmb_u16)(0x0500U + game->ram[MYSMB_BLOCK_BUFFER_LOW + index] +
                              game->ram[MYSMB_BLOCK_ORIGINAL_Y + index]);
        if (address < 0x0800U) game->ram[address] =
            game->ram[MYSMB_BLOCK_METATILE + index];
        buffer_offset = game->ram[MYSMB_VRAM_BUFFER1];
        if (buffer_offset > 0xf5U) return;
        if (game->ram[MYSMB_BLOCK_METATILE + index] == 0U) {
            graphics_index = 3U;
        }
        else if (game->ram[MYSMB_BLOCK_METATILE + index] == 0x58U ||
                 game->ram[MYSMB_BLOCK_METATILE + index] == 0x51U) {
            graphics_index = 0U;
        }
        else if (game->ram[MYSMB_BLOCK_METATILE + index] == 0x5dU ||
                 game->ram[MYSMB_BLOCK_METATILE + index] == 0x52U) {
            graphics_index = 1U;
        }
        else {
            graphics_index = 2U;
        }
        low = (mysmb_u8)((game->ram[MYSMB_BLOCK_BUFFER_LOW + index] & 0x0fU) << 1U);
        address = (mysmb_u16)(((mysmb_u16)(mysmb_u8)(
            game->ram[MYSMB_BLOCK_ORIGINAL_Y + index] + 0x20U) << 2U) + low);
        high = game->ram[MYSMB_BLOCK_BUFFER_LOW + index] < 0xd0U ? 0x20U : 0x24U;
        high = (mysmb_u8)(high + (address >> 8U));
        low = (mysmb_u8)address;
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset] = high;
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 1U] = low;
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 2U] = 2U;
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 3U] =
            block_graphics[(mysmb_u8)(graphics_index * 4U)];
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 4U] =
            block_graphics[(mysmb_u8)(graphics_index * 4U + 1U)];
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 5U] = high;
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 6U] =
            (mysmb_u8)(low + 0x20U);
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 7U] = 2U;
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 8U] =
            block_graphics[(mysmb_u8)(graphics_index * 4U + 2U)];
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 9U] =
            block_graphics[(mysmb_u8)(graphics_index * 4U + 3U)];
        game->ram[MYSMB_VRAM_BUFFER1_DATA + buffer_offset + 10U] = 0U;
        game->ram[MYSMB_VRAM_BUFFER1] = (mysmb_u8)(buffer_offset + 10U);
        game->ram[MYSMB_BLOCK_REPLACE_FLAG + index] = 0U;
    }
}
