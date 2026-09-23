#include "game/objects.h"

enum {
    MYSMB_VRAM_BUFFER1 = 0x0301U,
    MYSMB_BLOCK_ORIGINAL_Y = 0x03e4U,
    MYSMB_BLOCK_BUFFER_LOW = 0x03e6U,
    MYSMB_BLOCK_METATILE = 0x03e8U,
    MYSMB_BLOCK_REPLACE_FLAG = 0x03ecU
};

/* Translation of BlockObjMT_Updater's two block-object replacement slots.
 * ReplaceBlockMetatile's name-table write belongs to the later renderer. */
void mysmb_objects_apply_block_replacements(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u16 address;

    if (game->ram[MYSMB_VRAM_BUFFER1] != 0U) return;
    for (slot = 2U; slot != 0U; --slot) {
        mysmb_u8 index = (mysmb_u8)(slot - 1U);
        if (game->ram[MYSMB_BLOCK_REPLACE_FLAG + index] == 0U) continue;
        address = (mysmb_u16)(0x0500U + game->ram[MYSMB_BLOCK_BUFFER_LOW + index] +
                              game->ram[MYSMB_BLOCK_ORIGINAL_Y + index]);
        if (address < 0x0800U) game->ram[address] =
            game->ram[MYSMB_BLOCK_METATILE + index];
        game->ram[MYSMB_BLOCK_REPLACE_FLAG + index] = 0U;
    }
}
