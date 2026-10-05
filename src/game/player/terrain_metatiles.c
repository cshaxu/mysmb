#include "game/player/terrain_children.h"
#include "game/objects.h"
#include "core/area.h"

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

/* ROM $DEBD-$DEC3 ChkInvisibleMTiles. Both callers consume only Z;
 * the metatile argument remains unchanged across this predicate. */
mysmb_u8 mysmb_player_invisible_metatile(mysmb_u8 metatile)
{
    if (metatile == 0x5fU) return 1U;
    return metatile == 0x60U ? 1U : 0U;
}

/* ROM $DEDD-$DEE7 ChkJumpspringMetatiles. The native return carries
 * the source C flag; neither input nor RAM is changed. */
mysmb_u8 mysmb_player_jumpspring_metatile(mysmb_u8 metatile)
{
    if (metatile == 0x67U) return 1U;
    return metatile == 0x68U ? 1U : 0U;
}

/* ROM $DEC4-$DEDC ChkForLandJumpSpring: predicate before all stores. */
void mysmb_player_land_jumpspring(struct mysmb_game *game, mysmb_u8 metatile)
{
    if (mysmb_player_jumpspring_metatile(metatile) == 0U) return;
    game->ram[0x0709U] = 0x70U;
    game->ram[0x06dbU] = 0xf9U;
    game->ram[0x0786U] = 3U;
    game->ram[0x070eU] = 1U;
}
