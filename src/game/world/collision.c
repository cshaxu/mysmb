#include "game/world/world.h"
#include "game/oam/oam.h"
#include "game/objects.h"

enum {
    MYSMB_SQUARE2_SOUND = 0x00feU,
    MYSMB_SQUARE1_SOUND = 0x00ffU
};

/* ROM BlockBufferCollision: add the X probe with ADC, then use the carry
 * to select the page-local block buffer. */
mysmb_u8 mysmb_world_collision_page(mysmb_u8 page, mysmb_u8 object_x,
                                    mysmb_u8 probed_x)
{
    return (mysmb_u8)(page + (probed_x < object_x ? 1U : 0U));
}

/* ROM $e2a5 BoundBoxCtrlData and $dc71 BoundingBoxCore. */
void mysmb_world_set_bounding_box(struct mysmb_game *game,
                                    mysmb_u16 address, mysmb_u8 control,
                                    mysmb_u8 x, mysmb_u8 y)
{
    static const mysmb_u8 bounds[48] = {
        0x02U, 0x08U, 0x0eU, 0x20U, 0x03U, 0x14U, 0x0dU, 0x20U,
        0x02U, 0x14U, 0x0eU, 0x20U, 0x02U, 0x09U, 0x0eU, 0x15U,
        0x00U, 0x00U, 0x18U, 0x06U, 0x00U, 0x00U, 0x20U, 0x0dU,
        0x00U, 0x00U, 0x30U, 0x0dU, 0x00U, 0x00U, 0x08U, 0x08U,
        0x06U, 0x04U, 0x0aU, 0x08U, 0x03U, 0x0eU, 0x0dU, 0x14U,
        0x00U, 0x02U, 0x10U, 0x15U, 0x04U, 0x04U, 0x0cU, 0x1cU
    };
    mysmb_u8 offset;

    if (control >= 12U) control = 0U;
    offset = (mysmb_u8)(control * 4U);
    game->ram[address] = (mysmb_u8)(x + bounds[offset]);
    game->ram[address + 1U] = (mysmb_u8)(y + bounds[offset + 1U]);
    game->ram[address + 2U] = (mysmb_u8)(x + bounds[offset + 2U]);
    game->ram[address + 3U] = (mysmb_u8)(y + bounds[offset + 3U]);
}

/* ROM $dcf6 PlayerCollisionCore, for same-screen power-up boxes. */
/* ROM CheckRightScreenBBox / CheckLeftScreenBBox.  BoundingBoxCore writes
 * relative corners first; this source helper only replaces horizontal
 * corners that lie beyond the current 256-pixel screen. */
void mysmb_world_clip_bounding_box_to_screen(struct mysmb_game *game,
                                               mysmb_u16 address,
                                               mysmb_u8 object_page,
                                               mysmb_u8 object_x)
{
    mysmb_u8 middle_x;
    mysmb_u8 middle_page;
    mysmb_u8 carry;

    middle_x = (mysmb_u8)(game->ram[0x071cU] + 0x80U);
    carry = game->ram[0x071cU] >= 0x80U ? 1U : 0U;
    middle_page = (mysmb_u8)(game->ram[0x071aU] + carry);
    if (((mysmb_u16)object_page << 8U | object_x) >=
        ((mysmb_u16)middle_page << 8U | middle_x)) {
        if ((game->ram[address + 2U] & 0x80U) == 0U) {
            if ((game->ram[address] & 0x80U) == 0U) {
                game->ram[address] = 0xffU;
            }
            game->ram[address + 2U] = 0xffU;
        }
        return;
    }
    if ((game->ram[address] & 0x80U) != 0U &&
        game->ram[address] >= 0xa0U) {
        if ((game->ram[address + 2U] & 0x80U) != 0U) {
            game->ram[address + 2U] = 0U;
        }
        game->ram[address] = 0U;
    }
}
mysmb_u8 mysmb_world_boxes_collide(const struct mysmb_game *game,
                                            mysmb_u16 first, mysmb_u16 second)
{
    mysmb_u8 coordinate;

    /* `first` is the player box (X in PlayerCollisionCore) and `second`
     * is the sprite box (Y).  Preserve the 6502 comparisons, including
     * their intentional one-byte-wrap branches. */
    for (coordinate = 0U; coordinate < 2U; ++coordinate) {
        mysmb_u8 player_upper;
        mysmb_u8 player_lower;
        mysmb_u8 enemy_upper;
        mysmb_u8 enemy_lower;

        player_upper = game->ram[(mysmb_u16)(first + coordinate)];
        player_lower = game->ram[(mysmb_u16)(first + coordinate + 2U)];
        enemy_upper = game->ram[(mysmb_u16)(second + coordinate)];
        enemy_lower = game->ram[(mysmb_u16)(second + coordinate + 2U)];

        if (enemy_upper >= player_upper) {
            /* FirstBoxGreater. */
            if (enemy_upper == player_upper) continue;
            if (enemy_upper < player_lower) continue;
            if (enemy_upper == player_lower) continue;
            if (enemy_upper <= enemy_lower) return 0U;
            if (enemy_lower >= player_upper) continue;
            return 0U;
        }

        if (enemy_upper < player_lower) {
            /* SecondBoxVerticalChk. */
            if (player_lower < player_upper) continue;
            if (enemy_lower >= player_upper) continue;
            return 0U;
        }
        if (enemy_upper == player_lower) continue;
        if (enemy_lower < enemy_upper) continue;
        if (enemy_lower >= player_upper) continue;
        return 0U;
    }
    return 1U;
}
/* ROM CheckForClimbMTiles. */
mysmb_u8 mysmb_world_is_climbable(mysmb_u8 metatile)
{
    static const mysmb_u8 upper[4] = { 0x24U, 0x6dU, 0x8aU, 0xc6U };

    return metatile >= upper[(mysmb_u8)(metatile >> 6U)] ? 1U : 0U;
}

/* ROM CheckForSolidMTiles and LandPlyr. */
mysmb_u8 mysmb_world_land_player_on_solid(struct mysmb_game *game,
                                           mysmb_u8 metatile, mysmb_u8 contact)
{
    if (metatile < 0x10U || mysmb_world_is_climbable(metatile) != 0U ||
        game->ram[0x009fU] >= 0x80U || contact >= 5U) {
        return 0U;
    }
    game->ram[0x00ceU] = (mysmb_u8)(game->ram[0x00ceU] & 0xf0U);
    game->ram[0x009fU] = 0U;
    game->ram[0x0433U] = 0U;
    game->ram[0x0484U] = 0U;
    game->ram[0x001dU] = 0U;
    return 1U;
}

/* ROM $cdbf FireballBGCollision.  This owns the source bottom probe and
 * bounce/explosion decision; FireballObjCore retains only its call order. */
void mysmb_world_fireball_background_collision(struct mysmb_game *game,
                                                mysmb_u8 slot)
{
    mysmb_u8 x;
    mysmb_u8 page;
    mysmb_u8 row;
    mysmb_u16 address;
    mysmb_u8 tile;

    if (game->ram[(mysmb_u16)(0x00d5U + slot)] < 0x18U) {
        game->ram[(mysmb_u16)(0x003aU + slot)] = 0U;
        return;
    }
    x = (mysmb_u8)(game->ram[(mysmb_u16)(0x008dU + slot)] + 4U);
    page = mysmb_world_collision_page(game->ram[(mysmb_u16)(0x0074U + slot)],
                                      game->ram[(mysmb_u16)(0x008dU + slot)], x);
    row = (mysmb_u8)(((game->ram[(mysmb_u16)(0x00d5U + slot)] + 8U) & 0xf0U) -
                     0x20U);
    address = (mysmb_u16)(((page & 1U) != 0U ? 0x05d0U : 0x0500U) +
                          (x >> 4U) + row);
    tile = address < 0x0800U ? game->ram[address] : 0U;
    if (tile == 0U || tile == 0x26U || tile == 0xc2U || tile == 0xc3U ||
        tile == 0x5fU || tile == 0x60U) {
        game->ram[(mysmb_u16)(0x003aU + slot)] = 0U;
        return;
    }
    if (game->ram[(mysmb_u16)(0x00a6U + slot)] >= 0x80U ||
        game->ram[(mysmb_u16)(0x003aU + slot)] != 0U) {
        game->ram[(mysmb_u16)(0x0024U + slot)] = 0x80U;
        game->ram[MYSMB_SQUARE1_SOUND] = 2U;
        return;
    }
    game->ram[(mysmb_u16)(0x00a6U + slot)] = 0xfdU;
    game->ram[(mysmb_u16)(0x003aU + slot)] = 1U;
    game->ram[(mysmb_u16)(0x00d5U + slot)] &= 0xf8U;
}
/* ROM $d644 FireballEnemyCollision.  The frame route owns the immediately
 * following HandleEnemyFBallCol effect; this collision owner returns its
 * source $01 enemy-slot handoff after setting Fireball_State. */
mysmb_u8 mysmb_world_fireball_enemy_collision(struct mysmb_game *game,
                                               mysmb_u8 slot,
                                               mysmb_u8 *enemy_slot)
{
    mysmb_u8 scan_slot;
    mysmb_u16 enemy_box;
    mysmb_u16 fireball_box;

    if (game->ram[(mysmb_u16)(0x0024U + slot)] == 0U ||
        (game->ram[(mysmb_u16)(0x0024U + slot)] & 0x80U) != 0U ||
        (game->ram[0x0009U] & 1U) != 0U) {
        return 0U;
    }
    fireball_box = (mysmb_u16)(0x04acU + (7U + slot) * 4U);
    scan_slot = 5U;
    while (scan_slot != 0U) {
        --scan_slot;
        if ((game->ram[(mysmb_u16)(0x001eU + scan_slot)] & 0x20U) != 0U ||
            game->ram[(mysmb_u16)(0x000fU + scan_slot)] == 0U ||
            (game->ram[(mysmb_u16)(0x0016U + scan_slot)] >= 0x24U &&
             game->ram[(mysmb_u16)(0x0016U + scan_slot)] < 0x2bU) ||
            (game->ram[(mysmb_u16)(0x0016U + scan_slot)] == 0U &&
             game->ram[(mysmb_u16)(0x001eU + scan_slot)] >= 2U) ||
            game->ram[(mysmb_u16)(0x03d8U + scan_slot)] != 0U) {
            continue;
        }
        enemy_box = (mysmb_u16)(0x04b0U + scan_slot * 4U);
        if (mysmb_world_boxes_collide(game, enemy_box, fireball_box) == 0U) {
            continue;
        }
        game->ram[(mysmb_u16)(0x0024U + slot)] = 0x80U;
        *enemy_slot = scan_slot;
        return 1U;
    }
    return 0U;
}

/* ROM ChkToStunEnemies.  A is the source identifier except on the piranha
 * path, where the preceding ADC has deliberately made it the adjusted Y. */
static void mysmb_world_stun_enemy(struct mysmb_game *game, mysmb_u8 slot,
                                   mysmb_u8 source_a)
{
    mysmb_u8 id;
    mysmb_u8 direction;

    if (source_a >= 9U && source_a < 17U &&
        (source_a == 9U || source_a >= 13U)) {
        game->ram[(mysmb_u16)(0x0016U + slot)] &= 1U;
    }
    game->ram[(mysmb_u16)(0x001eU + slot)] =
        (mysmb_u8)((game->ram[(mysmb_u16)(0x001eU + slot)] & 0xf0U) | 2U);
    game->ram[(mysmb_u16)(0x00cfU + slot)] =
        (mysmb_u8)(game->ram[(mysmb_u16)(0x00cfU + slot)] - 2U);
    id = game->ram[(mysmb_u16)(0x0016U + slot)];
    game->ram[(mysmb_u16)(0x00a0U + slot)] =
        id == 7U || game->ram[0x074eU] == 0U ? 0xffU : 0xfdU;
    direction = (mysmb_u8)(game->ram[(mysmb_u16)(0x006eU + slot)] -
        game->ram[0x006dU] -
        (game->ram[(mysmb_u16)(0x0087U + slot)] < game->ram[0x0086U] ? 1U : 0U));
    if (id != 8U && id != 9U) {
        game->ram[(mysmb_u16)(0x0046U + slot)] =
            (direction & 0x80U) == 0U ? 1U : 2U;
    }
    game->ram[(mysmb_u16)(0x0058U + slot)] =
        (direction & 0x80U) == 0U ? 0x10U : 0xf0U;
}

/* ROM $d747 HandleEnemyFBallCol through EnemySmackScore.  This source node
 * owns the collision result's actor-state decisions; the only collaborators
 * are T16's fixed relative scratch and the Floatey consumer of that scratch. */
void mysmb_world_handle_fireball_enemy_hit(struct mysmb_game *game,
                                           mysmb_u8 enemy_slot)
{
    static const mysmb_u8 bowser_identities[8] =
        { 6U, 0U, 2U, 18U, 17U, 7U, 5U, 45U };
    mysmb_u8 current_slot;
    mysmb_u8 target_slot;
    mysmb_u8 id;
    mysmb_u8 score;

    current_slot = enemy_slot;
    mysmb_oam_relative_enemy_position(game, current_slot);
    target_slot = current_slot;
    if ((game->ram[(mysmb_u16)(0x000fU + current_slot)] & 0x80U) != 0U) {
        target_slot = (mysmb_u8)(game->ram[(mysmb_u16)(0x000fU + current_slot)] & 0x0fU);
        if (game->ram[(mysmb_u16)(0x0016U + target_slot)] != 45U) {
            target_slot = current_slot;
        }
    }
    id = game->ram[(mysmb_u16)(0x0016U + target_slot)];
    if (id == 2U) return;
    if (id == 45U) {
        game->ram[0x0483U]--;
        if (game->ram[0x0483U] != 0U) return;
        game->ram[(mysmb_u16)(0x00a0U + target_slot)] = 0U;
        game->ram[(mysmb_u16)(0x0434U + target_slot)] = 0U;
        game->ram[(mysmb_u16)(0x0058U + target_slot)] = 0U;
        game->ram[0x06cbU] = 0U;
        game->ram[(mysmb_u16)(0x00a0U + target_slot)] = 0xfeU;
        game->ram[(mysmb_u16)(0x0016U + target_slot)] =
            bowser_identities[game->ram[0x075fU] & 7U];
        game->ram[(mysmb_u16)(0x001eU + target_slot)] =
            game->ram[0x075fU] < 3U ? 0x23U : 0x20U;
        game->ram[MYSMB_SQUARE2_SOUND] = 0x80U;
        mysmb_objects_setup_floatey_from_relative(game, current_slot, 9U);
        game->ram[MYSMB_SQUARE1_SOUND] = 8U;
        return;
    }
    if (id == 8U || id == 12U || id >= 0x15U) return;
    if (id == 13U) {
        /* CMP #PiranhaPlant left carry set before ADC #$18. */
        game->ram[(mysmb_u16)(0x00cfU + current_slot)] =
            (mysmb_u8)(game->ram[(mysmb_u16)(0x00cfU + current_slot)] + 0x19U);
        id = game->ram[(mysmb_u16)(0x00cfU + current_slot)];
    }
    mysmb_world_stun_enemy(game, current_slot, id);
    game->ram[(mysmb_u16)(0x001eU + current_slot)] =
        (mysmb_u8)((game->ram[(mysmb_u16)(0x001eU + current_slot)] & 0x1fU) | 0x20U);
    id = game->ram[(mysmb_u16)(0x0016U + current_slot)];
    score = id == 5U ? 6U : (id == 0U ? 1U : 2U);
    mysmb_objects_setup_floatey_from_relative(game, current_slot, score);
    game->ram[MYSMB_SQUARE1_SOUND] = 8U;
}