#include "game/player.h"
#include "game/player/terrain_children.h"
#include "game/objects.h"
#include "game/world/world.h"

/* ROM $DC64-$DE02 PlayerBGCollision and its head/feet/side control chain.
 * Child conformance remains separately owned; full S1 proof is pending. */
enum {
    MYSMB_PLAYER_X = 0x0086U,
    MYSMB_JUMPSPRING_ANIM = 0x070eU,
    MYSMB_PLAYER_Y_SPEED = 0x009fU,
    MYSMB_PLAYER_Y_HIGH = 0x00b5U,
    MYSMB_PLAYER_Y = 0x00ceU,
    MYSMB_PLAYER_STATE = 0x001dU,
    MYSMB_SWIMMING = 0x0704U,
    MYSMB_PLAYER_COLLISION_BITS = 0x0490U,
    MYSMB_PLAYER_CROUCHING = 0x0714U,
    MYSMB_SQUARE1_SOUND_QUEUE = 0x00ffU,
    MYSMB_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_PLAYER_FACING = 0x0033U,
    MYSMB_PLAYER_ATTRIBUTES = 0x03c4U,
    MYSMB_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_DISABLE_COLLISION = 0x0716U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_PLAYER_MOVING_DIRECTION = 0x0045U,
    MYSMB_PLAYER_SIZE = 0x0754U,
    MYSMB_CHANGE_AREA_TIMER = 0x06deU
};

/* Bound original data is authoritative. The fallback supports resource-free
 * native tests at the documented table entries only. */
static mysmb_u8 terrain_byte(const struct mysmb_game *game,
    mysmb_u16 address, mysmb_u8 fallback)
{
    mysmb_u16 offset;
    offset = (mysmb_u16)(address - 0x8000U);
    if (game->area_prg != 0 && offset < game->area_prg_size)
        return game->area_prg[offset];
    return fallback;
}

/* ROM PlayerBGCollision selects BlockBufferAdderData before entering the
 * head, feet, and side probes.  The bases are normal big=$00, swimming
 * big=$07, and small or crouching=$0e.  The $0e selection is required for
 * small Mario's shorter collision body; using $07 makes his head probe the
 * swimming-big one and lets him pass through bricks, including hidden $5f
 * blocks. */
static mysmb_u8 mysmb_player_collision_base(const struct mysmb_game *game)
{
    mysmb_u8 index;
    index = 2U;
    if (game->ram[MYSMB_PLAYER_CROUCHING] == 0U &&
        game->ram[MYSMB_PLAYER_SIZE] == 0U)
        index = game->ram[MYSMB_SWIMMING] != 0U ? 1U : 0U;
    return terrain_byte(game, (mysmb_u16)(0xe3adU + index),
        (mysmb_u8)(index * 7U));
}

/* PlayerBGCollision owns all entry guards and initializes the shared cursor. */
void mysmb_player_background_collision(struct mysmb_game *game)
{
    mysmb_u8 collision_result;
    /* PlayerBGCollision is disabled for the control/pipe routines below 4,
     * player death (0x0b), and explicit collision suppression. */
    if (game->ram[MYSMB_DISABLE_COLLISION] == 0U &&
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] >= 4U &&
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 0x0bU) {
        /* PlayerBGCollision establishes falling/swimming before its
         * on-screen guard, so an eligible player leaving the visible
         * vertical range cannot retain the ground state. */
        if (game->ram[MYSMB_SWIMMING] != 0U) {
            game->ram[MYSMB_PLAYER_STATE] = 1U;
        }
        else if (game->ram[MYSMB_PLAYER_STATE] == 0U ||
                 game->ram[MYSMB_PLAYER_STATE] == 3U) {
            game->ram[MYSMB_PLAYER_STATE] = 2U;
        }
        if (game->ram[MYSMB_PLAYER_Y_HIGH] == 1U) {
            game->ram[MYSMB_PLAYER_COLLISION_BITS] = 0xffU;
            if (game->ram[MYSMB_PLAYER_Y] < 0xcfU) {
                game->ram[0xebU] = mysmb_player_collision_base(game);
                collision_result = mysmb_player_check_head(game);
                if (collision_result != 2U) {
                    collision_result = mysmb_player_check_feet(game);
                    if (collision_result != 2U &&
                        collision_result != MYSMB_PLAYER_FEET_TERMINAL_IMPEDE) {
                        (void)mysmb_player_check_sides(game);
                    }
                }
            }
        }
    }
}

/* DoFootCheck through InitSteP. A left coin returns before the right probe;
 * otherwise left selects the tile but right supplies the last query state.
 * The full root/query ABI migration remains part of the open T43 S1. */
mysmb_u8 mysmb_player_check_feet(struct mysmb_game *game)
{
    struct mysmb_player_terrain left;
    struct mysmb_player_terrain right;
    mysmb_u8 tile;
    mysmb_u8 base;

    /* DoFootCheck: the root has already established state/high-Y guards. */
    if (game->ram[MYSMB_PLAYER_Y] >= 0xcfU) return 0U;
    base = game->ram[0xebU];
    left.metatile = 0U;
    if (mysmb_world_query_player_probe(game, &base, MYSMB_TERRAIN_FEET, &left) == 0U)
        left.metatile = 0U;
    /* A left coin tail-returns before the right probe can overwrite scratch. */
    if (mysmb_player_coin_metatile(game, left.metatile) != 0U) {
        mysmb_objects_collect_coin(game, left.block_address_low,
            left.block_row_offset);
        return 2U;
    }
    right.metatile = 0U;
    right.contact_low_nibble = 0U;
    right.block_address_low = 0U;
    right.block_row_offset = 0U;
    if (mysmb_world_query_player_probe(game, &base, MYSMB_TERRAIN_FEET, &right) == 0U)
        right.metatile = 0U;
    game->ram[0U] = right.metatile;
    game->ram[1U] = left.metatile;
    tile = left.metatile;
    if (tile == 0U) {
        tile = game->ram[0U];
        if (tile == 0U) return 0U;
        if (mysmb_player_coin_metatile(game, tile) != 0U) {
            mysmb_objects_collect_coin(game, right.block_address_low,
                right.block_row_offset);
            return 2U;
        }
    }
    /* ChkFootMTile has one shared decision path, regardless of selected foot.
     * Probe metadata is from the last (right) call, as in the original RAM. */
    if (mysmb_world_is_climbable(tile) != 0U ||
        game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U) return 0U;
    if (tile == 0xc5U) {
        mysmb_player_handle_axe_metatile(game, right.block_address_low,
            right.block_row_offset);
        return 2U;
    }
    if (tile == 0x5fU || tile == 0x60U) return 0U;
    if (game->ram[MYSMB_JUMPSPRING_ANIM] != 0U) {
        game->ram[MYSMB_PLAYER_STATE] = 0U;
        return 1U;
    }
    if (right.contact_low_nibble >= 5U) {
        game->ram[0U] = game->ram[MYSMB_PLAYER_MOVING_DIRECTION];
        mysmb_player_impede_move(game, game->ram[0U]);
        return MYSMB_PLAYER_FEET_TERMINAL_IMPEDE;
    }
    /* LandPlyr: no extra solid-tile threshold, and pipe child precedes resets. */
    mysmb_player_land_jumpspring(game, tile);
    game->ram[MYSMB_PLAYER_Y] &= 0xf0U;
    (void)mysmb_player_handle_vertical_pipe(game, game->ram[1U], game->ram[0U]);
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0U;
    game->ram[0x0433U] = 0U;
    game->ram[0x0484U] = 0U;
    game->ram[MYSMB_PLAYER_STATE] = 0U;
    return 1U;
}


/* Translation of CheckSideMTiles.  Coins and jumpsprings have their own
 * object route, but they still consume this collision without a wall stop. */
static mysmb_u8 mysmb_player_handle_side_metatile(
    struct mysmb_game *game, const struct mysmb_player_terrain *terrain,
    mysmb_u8 collision_side)
{
    if (terrain->metatile == 0x5fU || terrain->metatile == 0x60U) {
        return 1U;
    }
    if (mysmb_world_is_climbable(terrain->metatile) != 0U) {
        (void)mysmb_player_handle_climbing(game, terrain);
        return 1U;
    }
    if (mysmb_player_coin_metatile(game, terrain->metatile) != 0U) {
        mysmb_objects_collect_coin(game, terrain->block_address_low,
                                   terrain->block_row_offset);
        return 1U;
    }
    if (terrain->metatile == 0x67U || terrain->metatile == 0x68U) {
        /* ChkJumpspringMetatiles reaches StopPlayerMove unless animation
         * has already claimed this metatile. */
        if (game->ram[MYSMB_JUMPSPRING_ANIM] != 0U) return 1U;
        mysmb_player_impede_move(game, collision_side);
        return 1U;
    }
    if (game->ram[MYSMB_PLAYER_STATE] != 0U ||
        game->ram[MYSMB_PLAYER_FACING] != MYSMB_BUTTON_RIGHT) {
        mysmb_player_impede_move(game, collision_side);
        return 1U;
    }
    if (terrain->metatile == 0x6cU || terrain->metatile == 0x1fU) {
        /* PipeDwnS queues the sound only when Player_SprAttrib was clear. */
        if (game->ram[MYSMB_PLAYER_ATTRIBUTES] == 0U) {
            game->ram[MYSMB_SQUARE1_SOUND_QUEUE] = 0x10U;
        }
        game->ram[MYSMB_PLAYER_ATTRIBUTES] |= 0x20U;
        if ((game->ram[MYSMB_PLAYER_X] & 0x0fU) != 0U) {
            game->ram[MYSMB_CHANGE_AREA_TIMER] = terrain_byte(game,
                game->ram[MYSMB_SCREEN_LEFT_PAGE] == 0U ? 0xde03U : 0xde04U,
                game->ram[MYSMB_SCREEN_LEFT_PAGE] == 0U ? 0xa0U : 0x34U);
        }
        if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 8U) {
            game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 2U;
        }
        return 1U;
    }
    mysmb_player_impede_move(game, collision_side);
    return 1U;
}

/* ROM DoPlayerSideCheck / SideCheckLoop.  Each upper sample can
 * defer to the lower half, which prevents a thin vine or pipe cap from
 * producing a side collision on its own. */
mysmb_u8 mysmb_player_check_sides(struct mysmb_game *game)
{
    struct mysmb_player_terrain terrain;
    mysmb_u8 index;
    mysmb_u8 base;

    base = game->ram[0xebU];
    game->ram[0U] = 2U;
    for (index = 0U; index < 2U; ++index) {
        mysmb_u8 top;

        top = (mysmb_u8)(base + 3U + index * 2U);
        game->ram[0xebU] = top;
        if (game->ram[MYSMB_PLAYER_Y] >= 0xe4U) return 0U;
        if (game->ram[MYSMB_PLAYER_Y] >= 0x20U &&
            mysmb_world_query_player_probe(game, &top, MYSMB_TERRAIN_SIDE,
                                     &terrain) != 0U && terrain.metatile != 0U &&
            terrain.metatile != 0x1cU && terrain.metatile != 0x6bU &&
            mysmb_world_is_climbable(terrain.metatile) == 0U) {
            return mysmb_player_handle_side_metatile(game, &terrain, game->ram[0U]);
        }
        if (game->ram[MYSMB_PLAYER_Y] < 8U ||
            game->ram[MYSMB_PLAYER_Y] >= 0xd0U) return 0U;
        top++;
        if (mysmb_world_query_player_probe(game, &top, MYSMB_TERRAIN_SIDE,
                                     &terrain) != 0U && terrain.metatile != 0U) {
            return mysmb_player_handle_side_metatile(game, &terrain, game->ram[0U]);
        }
        --game->ram[0U];
    }
    return 0U;
}

/* Translation of ROM $dcba-$dcf5 HeadChk through NYSpd.  Matched bumpable
 * blocks hand their original collision coordinates to the object owner. */
mysmb_u8 mysmb_player_check_head(struct mysmb_game *game)
{
    static const mysmb_u8 solid_upper[4] = { 0x10U, 0x61U, 0x88U, 0xc4U };
    struct mysmb_player_terrain terrain;
    mysmb_u8 extent_index;
    mysmb_u8 group;
    mysmb_u8 base;

    extent_index = game->ram[MYSMB_PLAYER_SIZE];
    if (game->ram[MYSMB_PLAYER_CROUCHING] != 0U) ++extent_index;
    if (game->ram[MYSMB_PLAYER_Y] < terrain_byte(game,
        (mysmb_u16)(0xdc62U + extent_index),
        extent_index == 0U ? 0x20U : (extent_index == 1U ? 0x10U : 0U))) {
        return 0U;
    }
    base = game->ram[0xebU];
    if (mysmb_world_query_player_probe(game, &base, MYSMB_TERRAIN_HEAD, &terrain) == 0U || terrain.metatile == 0U) {
        return 0U;
    }
    if (mysmb_player_coin_metatile(game, terrain.metatile) != 0U) {
        mysmb_objects_collect_coin(game, terrain.block_address_low,
                                   terrain.block_row_offset);
        return 2U;
    }
    if (game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U ||
        terrain.contact_low_nibble < 4U) {
        return 0U;
    }
    group = (mysmb_u8)(terrain.metatile >> 6U);
    if (terrain.metatile >= solid_upper[group]) {
        /* SolidOrClimb suppresses only the climbing metatile bump sound. */
        if (terrain.metatile != 0x26U) {
            game->ram[MYSMB_SQUARE1_SOUND_QUEUE] = 0x02U;
        }
        game->ram[MYSMB_PLAYER_Y_SPEED] = 1U;
        return 1U;
    }
    /* ROM HeadChk tests AreaType before PlayerHeadCollision.  In water,
     * NYSpd consumes a non-solid head hit without changing the block. */
    if (game->ram[MYSMB_AREA_TYPE] == 0U) {
        game->ram[MYSMB_PLAYER_Y_SPEED] = 1U;
        return 1U;
    }
    if (game->ram[0x0784U] != 0U) {
        /* HeadChk takes NYSpd while a previous block is bouncing. */
        game->ram[MYSMB_PLAYER_Y_SPEED] = 1U;
        return 1U;
    }
    if (mysmb_objects_start_head_bump(game, terrain.metatile,
                                      terrain.block_address_low,
                                      terrain.block_row_offset) != 0U) {
        return 1U;
    }
    return 0U;
}
