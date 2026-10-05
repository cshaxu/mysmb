#include "game/world/world.h"
#include "core/area/block_buffer.h"

/* ROM $e3ad-$e3c7: BlockBufferAdderData and its two adjacent adder tables. */
static const mysmb_u8 mysmb_block_x_adder[28] = {
    8U,3U,12U,2U,2U,13U,13U,8U,3U,12U,2U,2U,13U,13U,
    8U,3U,12U,2U,2U,13U,13U,8U,0U,16U,4U,20U,4U,4U
};
static const mysmb_u8 mysmb_block_y_adder[28] = {
    4U,32U,32U,8U,24U,8U,24U,2U,32U,32U,8U,24U,8U,24U,
    18U,32U,32U,24U,24U,24U,24U,24U,20U,20U,6U,6U,8U,16U
};

/* Bound original data is authoritative in production.  The fallback keeps
 * resource-free unit tests local to the reviewed 28-entry source domain. */
static mysmb_u8 mysmb_block_adder(const struct mysmb_game *game, mysmb_u16 address,
    mysmb_u8 index, const mysmb_u8 *fallback)
{
    mysmb_u16 offset;
    offset = (mysmb_u16)(address - 0x8000U + index);
    if (game->area_prg != 0 && offset < game->area_prg_size)
        return game->area_prg[offset];
    return fallback[index];
}
/* ROM BlockBufferCollision.  It owns source scratch $02-$07 and returns the
 * queried metatile; callers choose the source entry and inspect its result. */
static mysmb_u8 mysmb_world_block_buffer_collision(struct mysmb_game *game,
    mysmb_u8 object_x, mysmb_u8 object_page, mysmb_u8 object_y,
    mysmb_u8 adder, mysmb_u8 x_adder, mysmb_u8 y_adder, mysmb_u8 horizontal)
{
    mysmb_u8 x;
    mysmb_u8 page;
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u16 address;

    game->ram[4U] = adder;
    x = (mysmb_u8)(object_x + x_adder);
    game->ram[5U] = x;
    page = (mysmb_u8)(object_page + (x < object_x ? 1U : 0U));
    column = (mysmb_u8)(((page & 1U) << 4U) | (x >> 4U));
    address = mysmb_area_get_block_buffer_address(game, column);
    row = (mysmb_u8)(((object_y + y_adder) & 0xf0U) - 0x20U);
    game->ram[2U] = row;
    game->ram[3U] = game->ram[(mysmb_u16)(address + row)];
    game->ram[4U] = horizontal != 0U ? (mysmb_u8)(object_x & 0x0fU) :
        (mysmb_u8)(object_y & 0x0fU);
    return game->ram[3U];
}

static mysmb_u8 mysmb_world_finish_enemy_terrain(struct mysmb_game *game,
    struct mysmb_enemy_terrain *terrain)
{
    terrain->contact_low_nibble = game->ram[4U];
    terrain->block_address_low = game->ram[6U];
    terrain->block_row_offset = game->ram[2U];
    terrain->block_address = (mysmb_u16)((((mysmb_u16)game->ram[7U] << 8U) |
        game->ram[6U]) + game->ram[2U]);
    return terrain->metatile != 0U ? 1U : 0U;
}

/* ROM BlockBufferCollision page construction, retained for direct callers. */
mysmb_u8 mysmb_world_collision_page(mysmb_u8 page, mysmb_u8 object_x,
                                    mysmb_u8 probed_x)
{
    return (mysmb_u8)(page + (probed_x < object_x ? 1U : 0U));
}

mysmb_u8 mysmb_world_query_player_block(struct mysmb_game *game,
    mysmb_u8 x_adder, mysmb_u8 y_adder, mysmb_u8 horizontal_contact,
    struct mysmb_player_terrain *terrain)
{
    if (terrain == 0) return 0U;
    terrain->metatile = mysmb_world_block_buffer_collision(game,
        game->ram[0x0086U], game->ram[0x006dU], game->ram[0x00ceU], 0U,
        x_adder, y_adder, horizontal_contact);
    terrain->contact_low_nibble = game->ram[4U];
    terrain->block_address_low = game->ram[6U];
    terrain->block_row_offset = game->ram[2U];
    return terrain->metatile != 0U ? 1U : 0U;
}

mysmb_u8 mysmb_world_query_player_probe(struct mysmb_game *game,
    mysmb_u8 *index, mysmb_u8 entry, struct mysmb_player_terrain *terrain)
{
    if (index == 0 || terrain == 0) return 0U;
    if (entry == MYSMB_TERRAIN_FEET) ++*index;
    terrain->metatile = mysmb_world_block_buffer_collision(game,
        game->ram[0x0086U], game->ram[0x006dU], game->ram[0x00ceU], *index,
        mysmb_block_adder(game, 0xe3b0U, *index, mysmb_block_x_adder),
        mysmb_block_adder(game, 0xe3ccU, *index, mysmb_block_y_adder),
        entry == MYSMB_TERRAIN_SIDE ? 1U : 0U);
    terrain->contact_low_nibble = game->ram[4U];
    terrain->block_address_low = game->ram[6U];
    terrain->block_row_offset = game->ram[2U];
    return terrain->metatile != 0U ? 1U : 0U;
}

/* ROM BlockBufferChk_Enemy -> BBChk_E. */
mysmb_u8 mysmb_world_query_enemy_block(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 adder, mysmb_u8 horizontal_contact,
    struct mysmb_enemy_terrain *terrain)
{
    mysmb_u8 object_offset;
    if (terrain == 0) return 0U;
    object_offset = (mysmb_u8)(slot + 1U);
    terrain->metatile = mysmb_world_block_buffer_collision(game,
        game->ram[0x0086U + object_offset], game->ram[0x006dU + object_offset],
        game->ram[0x00ceU + object_offset], adder,
        mysmb_block_adder(game, 0xe3b0U, adder, mysmb_block_x_adder),
        mysmb_block_adder(game, 0xe3ccU, adder, mysmb_block_y_adder), horizontal_contact);
    return mysmb_world_finish_enemy_terrain(game, terrain);
}

/* ROM ResidualMiscObjectCode -> ResJmpM -> BBChk_E. */
mysmb_u8 mysmb_world_query_misc_block(struct mysmb_game *game, mysmb_u8 slot,
    struct mysmb_enemy_terrain *terrain)
{
    mysmb_u8 object_offset;
    if (terrain == 0) return 0U;
    object_offset = (mysmb_u8)(slot + 0x0dU);
    terrain->metatile = mysmb_world_block_buffer_collision(game,
        game->ram[0x0086U + object_offset], game->ram[0x006dU + object_offset],
        game->ram[0x00ceU + object_offset], 0x1bU,
        mysmb_block_adder(game, 0xe3b0U, 0x1bU, mysmb_block_x_adder),
        mysmb_block_adder(game, 0xe3ccU, 0x1bU, mysmb_block_y_adder), 0U);
    return mysmb_world_finish_enemy_terrain(game, terrain);
}

/* ROM BlockBufferChk_FBall. */
mysmb_u8 mysmb_world_query_fireball_block(struct mysmb_game *game,
    mysmb_u8 slot, struct mysmb_enemy_terrain *terrain)
{
    if (terrain == 0) return 0U;
    terrain->metatile = mysmb_world_block_buffer_collision(game,
        game->ram[0x008dU + slot], game->ram[0x0074U + slot],
        game->ram[0x00d5U + slot], 0x1aU, mysmb_block_adder(game, 0xe3b0U, 0x1aU, mysmb_block_x_adder),
        mysmb_block_adder(game, 0xe3ccU, 0x1aU, mysmb_block_y_adder), 0U);
    return mysmb_world_finish_enemy_terrain(game, terrain);
}
/* ROM ChkUnderEnemy: A=0 and Y=$15 before the enemy entry. */
mysmb_u8 mysmb_world_query_enemy_under(struct mysmb_game *game, mysmb_u8 slot,
    struct mysmb_enemy_terrain *terrain)
{
    (void)mysmb_world_query_enemy_block(game, slot, 0x15U, 0U, terrain);
    /* The tail-called BBChk_E returns the queried metatile in A, rather than
     * a normalized boolean.  Existing callers intentionally use zero/nonzero
     * tests, while this boundary preserves the direct ROM result. */
    return terrain != 0 ? terrain->metatile : 0U;
}
