#include "core/area.h"

/* ROM $BED4-$BF01 BlockObjMT_Updater, UpdateLoop and NextBUpd.
 * $0301 is the first VRAM command byte; $0300 is its separate offset. */
void mysmb_area_apply_block_replacements(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u16 address;

    slot = 1U;
    do {
        game->ram[8U] = slot;
        if (game->ram[0x0301U] == 0U && game->ram[0x03ecU + slot] != 0U) {
            game->ram[6U] = game->ram[0x03e6U + slot];
            game->ram[7U] = 5U;
            game->ram[2U] = game->ram[0x03e4U + slot];
            address = (mysmb_u16)(0x0500U + game->ram[6U] + game->ram[2U]);
            game->ram[address] = game->ram[0x03e8U + slot];
            mysmb_area_replace_block_metatile(game, slot);
            game->ram[0x03ecU + slot] = 0U;
        }
        slot = (mysmb_u8)(slot - 1U);
    } while (slot < 0x80U);
}
