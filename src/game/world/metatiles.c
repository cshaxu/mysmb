#include "game/world/world.h"
#include "game/player/terrain_children.h"

/* ROM $dfb0-$dfb8 GetMTileAttrib / ExEBG. The native result carries X;
 * callers keep the original metatile argument (the source A and Y). */
mysmb_u8 mysmb_world_metatile_attribute(mysmb_u8 metatile)
{
    return (mysmb_u8)(metatile >> 6U);
}

static mysmb_u8 threshold(const struct mysmb_game *game, mysmb_u16 address,
                          mysmb_u8 index, const mysmb_u8 *unbound)
{
    mysmb_u16 offset;
    offset = (mysmb_u16)(address - 0x8000U + index);
    if (game->area_prg != 0 && offset < game->area_prg_size)
        return game->area_prg[offset];
    return unbound[index];
}

/* ROM $df8b SolidMTileUpperExt / $df8f CheckForSolidMTiles.
 * Return the source CMP carry; no RAM or input-metatile changes. */
mysmb_u8 mysmb_world_is_solid(const struct mysmb_game *game, mysmb_u8 tile)
{
    static const mysmb_u8 unbound[4] = { 0x10U, 0x61U, 0x88U, 0xc4U };
    mysmb_u8 group;
    group = mysmb_world_metatile_attribute(tile);
    return tile >= threshold(game, 0xdf8bU, group, unbound) ? 1U : 0U;
}

/* ROM $df96 ClimbMTileUpperExt / $df9a CheckForClimbMTiles. */
mysmb_u8 mysmb_world_is_climbable(const struct mysmb_game *game, mysmb_u8 tile)
{
    static const mysmb_u8 unbound[4] = { 0x24U, 0x6dU, 0x8aU, 0xc6U };
    mysmb_u8 group;
    group = mysmb_world_metatile_attribute(tile);
    return tile >= threshold(game, 0xdf96U, group, unbound) ? 1U : 0U;
}

/* ROM $dfa1-$dfaf CheckForCoinMTiles / CoinSd. Callers consume C;
 * a match loads A=1, stores Square2SoundQueue and retains comparison C=1. */
mysmb_u8 mysmb_player_coin_metatile(struct mysmb_game *game, mysmb_u8 tile)
{
    if (tile != 0xc2U && tile != 0xc3U) return 0U;
    game->ram[0xfeU] = 1U;
    return 1U;
}
