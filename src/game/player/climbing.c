#include "game/player/terrain_children.h"
#include "core/area.h"

/* ROM $DE25-$DE2D: ClimbXPosAdder, ClimbPLocAdder, FlagpoleYPosData.
 * Bound PRG preserves the original absolute-indexed reads. The local
 * entries support resource-free native tests at the defined table bytes. */
static mysmb_u8 climbing_byte(const struct mysmb_game *game, mysmb_u16 address)
{
    static const mysmb_u8 table[9] = {
        0xf9U, 0x07U, 0xffU, 0U, 0x18U, 0x22U, 0x50U, 0x68U, 0x90U
    };
    mysmb_u16 offset;
    offset = (mysmb_u16)(address - 0x8000U);
    if (game->area_prg != 0 && offset < game->area_prg_size)
        return game->area_prg[offset];
    if (address >= 0xde25U && address <= 0xde2dU)
        return table[address - 0xde25U];
    return 0U;
}

/* ROM $DE2E-$DEBC HandleClimbing through ExPVne. Terrain metadata is the
 * caller's original A/$04/$06. KillEnemies retains its separate owner. */
mysmb_u8 mysmb_player_handle_climbing(struct mysmb_game *game,
    const struct mysmb_player_terrain *terrain)
{
    mysmb_u8 score, facing, relative_x;
    if (terrain->contact_low_nibble < 6U ||
        terrain->contact_low_nibble >= 0x0aU) return 0U;

    if (terrain->metatile == 0x24U || terrain->metatile == 0x25U) {
        if (game->ram[0x000eU] == 5U) goto put_player_on_vine;
        game->ram[0x0033U] = 1U;
        ++game->ram[0x0723U];
        if (game->ram[0x000eU] != 4U) {
            mysmb_area_kill_enemies(game, 0x33U);
            game->ram[0x00fcU] = 0x80U;
            game->ram[0x0713U] = 0x40U;
            game->ram[0x070fU] = game->ram[0x00ceU];
            score = 4U;
            while (game->ram[0x00ceU] <
                climbing_byte(game, (mysmb_u16)(0xde29U + score))) {
                --score;
                if (score == 0U) break;
            }
            game->ram[0x010fU] = score;
        }
        game->ram[0x000eU] = 4U;
    } else if (terrain->metatile == 0x26U && game->ram[0x00ceU] < 0x20U) {
        game->ram[0x000eU] = 1U;
    }

put_player_on_vine:
    game->ram[0x001dU] = 3U;
    game->ram[0x0057U] = 0U;
    game->ram[0x0705U] = 0U;
    relative_x = (mysmb_u8)(game->ram[0x0086U] - game->ram[0x071cU]);
    if (relative_x < 0x10U) game->ram[0x0033U] = 2U;
    facing = game->ram[0x0033U];
    game->ram[0x0086U] = (mysmb_u8)((terrain->block_address_low << 4U) +
        climbing_byte(game, (mysmb_u16)(0xde24U + facing)));
    if (terrain->block_address_low == 0U)
        game->ram[0x006dU] = (mysmb_u8)(game->ram[0x071bU] +
            climbing_byte(game, (mysmb_u16)(0xde26U + facing)));
    return 1U;
}
