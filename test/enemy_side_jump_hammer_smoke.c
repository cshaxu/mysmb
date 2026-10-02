#include "game/objects.h"
#include "game/world/world.h"
#include "game/enemy/distance.h"
#include <string.h>

int main(void)
{
    struct mysmb_game game;
    memset(&game, 0, sizeof(game));
    game.ram[0x001eU] = 0x80U;
    game.ram[0x0058U] = 0x10U;
    game.ram[0x0046U] = 1U;
    mysmb_objects_bump_enemy(&game, 0U);
    if (game.ram[0x00ffU] != 2U || game.ram[0x0058U] != 0xf0U ||
        game.ram[0x0046U] != 2U) return 1;
    game.ram[0x00ffU] = 0U;
    game.ram[0x0016U + 5U] = 5U;
    game.ram[0x0058U + 5U] = 0x10U;
    game.ram[0x0046U + 5U] = 1U;
    game.ram[0x07a9U + 5U] = 1U;
    game.ram[0x07a8U + 5U] = 0x12U;
    game.ram[0x06ccU] = 1U;
    mysmb_objects_bump_enemy(&game, 5U);
    /* SetHJ continues through facing and normal movement before returning. */
    if (game.ram[0x00ffU] != 0U || game.ram[0x0058U + 5U] != 0xf8U ||
        game.ram[0x0046U + 5U] != 2U || game.ram[0x00a0U + 5U] != 0xfaU ||
        (game.ram[0x001eU + 5U] & 1U) == 0U || game.ram[0x078aU + 5U] != 0x20U ||
        game.ram[0x003cU + 5U] != 0xd2U) return 2;
    game.ram[0x0087U] = 2U; game.ram[0x0086U] = 3U;
    game.ram[0x006eU] = 4U; game.ram[0x006dU] = 1U;
    if (mysmb_enemy_player_difference(&game, 0U) != 2U || game.ram[0U] != 0xffU)
        return 3;
    game.ram[0x00a0U] = 0x80U; game.ram[0x0434U] = 3U;
    game.ram[0x00cfU] = 0x4fU;
    mysmb_world_land_enemy(&game, 0U);
    if (game.ram[0x00a0U] != 0U || game.ram[0x0434U] != 0U ||
        game.ram[0x00cfU] != 0x48U) return 4;

    /* HammerBroBGColl does not call ChkForNonSolids: every nonzero tile
     * except $23 reaches UnderHammerBro.  A live jump timer falls through
     * NoUnderHammerBro and sets d0. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U; game.ram[0x0016U] = 5U;
    game.ram[0x0046U] = 1U; game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U; game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x50U; game.ram[0x078aU] = 1U;
    game.ram[0x0544U] = 0xc2U;
    mysmb_objects_step_hammer_terrain(&game, 0U);
    if (game.ram[0x001eU] != 1U) return 5;

    /* With no jump timer, the same non-solid-to-other-routes tile lands. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U; game.ram[0x0016U] = 5U;
    game.ram[0x0046U] = 1U; game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U; game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x50U; game.ram[0x00a0U] = 0x80U;
    game.ram[0x078aU] = 0U;
    game.ram[0x0434U] = 3U; game.ram[0x0544U] = 0xc2U;
    mysmb_objects_step_hammer_terrain(&game, 0U);
    if (game.ram[0x001eU] != 0U || game.ram[0x00cfU] != 0x58U ||
        game.ram[0x00a0U] != 0U || game.ram[0x0434U] != 0U) return 6;

    /* Tile $23 takes KillEnemyAboveBlock and forces its $fc speed tail. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U; game.ram[0x0016U] = 5U;
    game.ram[0x006eU] = 0U; game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U; game.ram[0x00cfU] = 0x50U;
    game.ram[0x0544U] = 0x23U;
    mysmb_objects_step_hammer_terrain(&game, 0U);
    if ((game.ram[0x001eU] & 0x20U) == 0U || game.ram[0x00a0U] != 0xfcU)
        return 7;
    return 0;
}
