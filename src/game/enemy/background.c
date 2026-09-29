#include "game/objects.h"
#include "game/world/world.h"
#include "game/enemy/distance.h"
#include "game/enemy/background.h"

/* ROM $dfc1-$dff2 EnemyToBGCollisionDet entry, with ExEBG/ExEBGChk
 * return paths. Walking and hammer child interiors are not owned here. */
void mysmb_objects_enemy_background_current(struct mysmb_game *game,
                                             mysmb_u8 slot)
{
    mysmb_u8 id;
    if ((game->ram[0x001eU + slot] & 0x20U) != 0U ||
        (mysmb_u8)(game->ram[0x00cfU + slot] + 0x3eU) < 0x44U) return;
    id = game->ram[0x0016U + slot];
    if (id == 18U && game->ram[0x00cfU + slot] < 0x25U) return;
    if (id == 14U) mysmb_objects_step_enemy_jump_terrain(game, slot);
    else if (id == 5U) mysmb_objects_step_hammer_terrain(game, slot);
    else if (id < 7U || id == 18U || id == 0x2eU)
        mysmb_objects_step_normal_enemy_terrain(game, slot);
}

/* ROM EnemyBGCStateData / EnemyBGCXSpdData. Later landing consumers
 * keep their own control-flow proof; this owner supplies original bytes. */
static mysmb_u8 background_data(const struct mysmb_game *game,
    mysmb_u16 address, mysmb_u8 index, const mysmb_u8 *fallback,
    mysmb_u8 length)
{
    mysmb_u16 offset;
    offset = (mysmb_u16)(address - 0x8000U + index);
    if (game->area_prg != 0 && offset < game->area_prg_size)
        return game->area_prg[offset];
    return index < length ? fallback[index] : 0U;
}
mysmb_u8 mysmb_enemy_background_state_data(const struct mysmb_game *game,
    mysmb_u8 index)
{
    static const mysmb_u8 states[6] = { 1U, 1U, 2U, 2U, 2U, 5U };
    return background_data(game, 0xdfb9U, index, states, 6U);
}

/* ROM ChkToStunEnemies / Demote. Source A can differ from Enemy_ID,
 * notably after SetupFloateyNumber or the Piranha Y adjustment. */
void mysmb_world_stun_enemy(struct mysmb_game *game, mysmb_u8 slot,
    mysmb_u8 source_a)
{
    if (source_a >= 9U && source_a < 17U &&
        (source_a == 9U || source_a >= 13U))
        game->ram[0x0016U + slot] = (mysmb_u8)(source_a & 1U);
    mysmb_world_set_stun(game, slot);
}

/* ROM SetStun through ExEBGChk. PlayerEnemyDiff owns its RAM00 store.
 * Cannon Bullet Bill is $33; $09 is not a direction-preserving bullet. */
void mysmb_world_set_stun(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 speeds[2] = { 0x10U, 0xf0U };
    mysmb_u8 id, direction;
    game->ram[0x001eU + slot] =
        (mysmb_u8)((game->ram[0x001eU + slot] & 0xf0U) | 2U);
    --game->ram[0x00cfU + slot];
    --game->ram[0x00cfU + slot];
    id = game->ram[0x0016U + slot];
    game->ram[0x00a0U + slot] =
        id == 7U || game->ram[0x074eU] == 0U ? 0xffU : 0xfdU;
    direction = (mysmb_enemy_player_difference(game, slot) & 0x80U) ? 2U : 1U;
    id = game->ram[0x0016U + slot];
    if (id != 0x33U && id != 8U)
        game->ram[0x0046U + slot] = direction;
    game->ram[0x0058U + slot] = background_data(game, 0xdfbfU,
        (mysmb_u8)(direction - 1U), speeds, 2U);
}

/* ROM $DFFA HandleEToBGCollision through GiveOEPoints. The terrain
 * argument represents the original query A, pointer and row outputs. */
void mysmb_enemy_handle_background(struct mysmb_game *game, mysmb_u8 slot,
    const struct mysmb_enemy_terrain *terrain)
{
    mysmb_u8 source_a;
    if (mysmb_objects_is_solid_terrain(terrain->metatile) == 0U) {
        mysmb_objects_enemy_no_ground(game, slot);
        return;
    }
    if (terrain->metatile != 0x23U) {
        mysmb_objects_enemy_land_from_probe(game, slot, terrain);
        return;
    }
    game->ram[terrain->block_address] = 0U;
    source_a = game->ram[0x0016U + slot];
    if (source_a < 0x15U) {
        if (source_a == 6U) mysmb_objects_kill_enemy_above_block(game, slot);
        mysmb_objects_setup_floatey_from_relative(game, slot, 1U);
        source_a = game->ram[0x03aeU];
    }
    mysmb_world_stun_enemy(game, slot, source_a);
}

/* YesIn / NoEToBGCollision. The leading guards preserve the legacy
 * direct-call ABI; the canonical dispatch has already checked them. */
void mysmb_objects_step_normal_enemy_terrain(struct mysmb_game *game,
    mysmb_u8 slot)
{
    struct mysmb_enemy_terrain terrain;
    mysmb_u8 tile;
    if ((game->ram[0x001eU + slot] & 0x20U) != 0U ||
        (mysmb_u8)(game->ram[0x00cfU + slot] + 0x3eU) < 0x44U) return;
    tile = mysmb_world_query_enemy_block(game, slot, 0x15U, 0U, &terrain) != 0U ?
        terrain.metatile : 0U;
    if (tile == 0U) {
        mysmb_objects_enemy_no_ground(game, slot);
        return;
    }
    mysmb_enemy_handle_background(game, slot, &terrain);
}

/* ROM $E067-$E0FF LandEnemyProperly through SetD6Ste. Side-check, bump and
 * physical landing bodies remain explicit S10 dependencies. */
static void background_land_init(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 state;
    mysmb_world_land_enemy(game, slot);
    state = game->ram[0x001eU + slot];
    if ((state & 0x80U) != 0U)
        game->ram[0x001eU + slot] = (mysmb_u8)(state & 0xbfU);
    else
        game->ram[0x001eU + slot] = 0U;
}

static void background_enemy_direction(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 direction;
    if (game->ram[0x0016U + slot] == 6U) {
        background_land_init(game, slot);
        return;
    }
    if (game->ram[0x0016U + slot] == 18U) {
        game->ram[0x0046U + slot] = 1U;
        game->ram[0x0058U + slot] = 8U;
        if ((game->ram[9U] & 7U) == 0U) {
            background_land_init(game, slot);
            return;
        }
    }
    direction = (mysmb_enemy_player_difference(game, slot) & 0x80U) != 0U ? 2U : 1U;
    if (direction != game->ram[0x0046U + slot])
        background_land_init(game, slot);
    else
        mysmb_objects_bump_enemy(game, slot);
}

void mysmb_objects_enemy_land_from_probe(struct mysmb_game *game,
    mysmb_u8 slot, const struct mysmb_enemy_terrain *terrain)
{
    mysmb_u8 state;
    if (terrain->contact_low_nibble >= 0x0dU) {
        mysmb_objects_enemy_no_ground(game, slot);
        return;
    }
    state = game->ram[0x001eU + slot];
    if ((state & 0x40U) != 0U) {
        background_land_init(game, slot);
        return;
    }
    if ((state & 0x80U) != 0U) {
        mysmb_objects_check_enemy_side(game, slot);
        return;
    }
    if (state == 0U) {
        mysmb_objects_check_enemy_side(game, slot);
        return;
    }
    if (state == 5U) {
        background_enemy_direction(game, slot);
        return;
    }
    if (state >= 3U) return;
    if (state == 2U) {
        game->ram[0x0796U + slot] = game->ram[0x0016U + slot] == 18U ? 0U : 0x10U;
        game->ram[0x001eU + slot] = 3U;
        mysmb_world_land_enemy(game, slot);
        return;
    }
    background_enemy_direction(game, slot);
}

void mysmb_objects_enemy_no_ground(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 state;
    state = game->ram[0x001eU + slot];
    if (game->ram[0x0016U + slot] == 3U && state == 0U) {
        mysmb_objects_bump_enemy(game, slot);
        return;
    }
    if ((state & 0x80U) != 0U)
        game->ram[0x001eU + slot] = (mysmb_u8)(state | 0x40U);
    else
        game->ram[0x001eU + slot] = mysmb_enemy_background_state_data(game, state);
    mysmb_objects_check_enemy_side(game, slot);
}
