#include "game/player/terrain_children.h"
#include "game/objects.h"
#include "game/area.h"

/* ROM $DE1C-$DE24 ErACM. Low/row carry the validated query outputs;
 * the original pointer high byte remains RAM $07. Callers supply an
 * original block-buffer address in RAM, not an invented fixed $05 page. */
static void erase_metatile(struct mysmb_game *game,
    mysmb_u8 block_low, mysmb_u8 block_row)
{
    mysmb_u16 address;
    address = (mysmb_u16)(((mysmb_u16)game->ram[7U] << 8U) +
        block_low + block_row);
    game->ram[address] = 0U;
    mysmb_area_remove_coin_axe(game, block_low, block_row);
}

/* ROM $DE05-$DE0D HandleCoinMetatile. ErACM returns before the tally
 * increment; GiveOneCoin is the final child, including on byte wrap. */
void mysmb_objects_collect_coin(struct mysmb_game *game,
    mysmb_u8 block_low, mysmb_u8 block_row)
{
    erase_metatile(game, block_low, block_row);
    ++game->ram[0x0748U];
    mysmb_objects_give_one_coin(game);
}

/* ROM $DE0E-$DE1B HandleAxeMetatile falls into the common erase tail. */
void mysmb_player_handle_axe_metatile(struct mysmb_game *game,
    mysmb_u8 block_low, mysmb_u8 block_row)
{
    game->ram[0x0772U] = 0U;
    game->ram[0x0770U] = 2U;
    game->ram[0x0057U] = 0x18U;
    erase_metatile(game, block_low, block_row);
}
