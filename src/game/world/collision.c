#include "game/world/world.h"
#include "game/oam/oam.h"
#include "game/objects.h"

enum {
    MYSMB_WORLD_PLAYER_PAGE = 0x006dU,
    MYSMB_WORLD_PLAYER_X = 0x0086U,
    MYSMB_WORLD_PLAYER_Y = 0x00ceU,
    MYSMB_SQUARE2_SOUND = 0x00feU,
    MYSMB_SQUARE1_SOUND = 0x00ffU
};

/* ROM EnemyLanding -> InitVStf. */
void mysmb_world_land_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    if (slot >= 6U) return;
    game->ram[0x00a0U + slot] = 0U;
    game->ram[0x0434U + slot] = 0U;
    game->ram[0x00cfU + slot] = (mysmb_u8)((game->ram[0x00cfU + slot] & 0xf0U) | 8U);
}

/* ROM CheckForSolidMTiles and LandPlyr. */
mysmb_u8 mysmb_world_land_player_on_solid(struct mysmb_game *game,
                                           mysmb_u8 metatile, mysmb_u8 contact)
{
    if (metatile < 0x10U || mysmb_world_is_climbable(game, metatile) != 0U ||
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

/* ROM $E1E0 ClearBounceFlag. */
static void mysmb_world_clear_fireball_bounce(struct mysmb_game *game,
                                              mysmb_u8 slot)
{
    game->ram[(mysmb_u16)(0x003aU + slot)] = 0U;
}

/* ROM $E1E7 InitFireballExplode. */
static void mysmb_world_init_fireball_explode(struct mysmb_game *game,
                                              mysmb_u8 slot)
{
    game->ram[(mysmb_u16)(0x0024U + slot)] = 0x80U;
    game->ram[MYSMB_SQUARE1_SOUND] = 2U;
}

/* ROM $E1C8 FireballBGCollision.  This owns the source bottom probe and
 * bounce/explosion decision; FireballObjCore retains only its call order. */
void mysmb_world_fireball_background_collision(struct mysmb_game *game,
                                                mysmb_u8 slot)
{
    struct mysmb_enemy_terrain terrain;
    mysmb_u8 tile;

    if (game->ram[(mysmb_u16)(0x00d5U + slot)] < 0x18U) {
        mysmb_world_clear_fireball_bounce(game, slot);
        return;
    }
    tile = mysmb_world_query_fireball_block(game, slot, &terrain) != 0U ?
        terrain.metatile : 0U;
    if (tile == 0U || mysmb_world_enemy_metatile_is_non_solid(tile) != 0U) {
        mysmb_world_clear_fireball_bounce(game, slot);
        return;
    }
    if (game->ram[(mysmb_u16)(0x00a6U + slot)] >= 0x80U ||
        game->ram[(mysmb_u16)(0x003aU + slot)] != 0U) {
        mysmb_world_init_fireball_explode(game, slot);
        return;
    }
    game->ram[(mysmb_u16)(0x00a6U + slot)] = 0xfdU;
    game->ram[(mysmb_u16)(0x003aU + slot)] = 1U;
    game->ram[(mysmb_u16)(0x00d5U + slot)] &= 0xf8U;
}
/* ROM GetFireballBoundBox.  GetProperObjOffset makes slot zero/one use
 * controls $04a0/$04a1 and output boxes $04c8/$04cc; the relative source
 * inputs remain the fixed Fireball_Rel_* pair. */
void mysmb_world_get_fireball_bounding_box(struct mysmb_game *game,
                                            mysmb_u8 slot)
{
    mysmb_world_set_bounding_box(
        game, (mysmb_u16)(0x04acU + (7U + slot) * 4U),
        game->ram[0x04a0U + slot],
        game->ram[0x03afU], game->ram[0x03baU]);
    mysmb_world_clip_bounding_box_to_screen(game,
        (mysmb_u16)(0x04acU + (7U + slot) * 4U),
        game->ram[0x0074U + slot],
        game->ram[0x008dU + slot]);
}

/* ROM $DC41 CheckPlayerVertical / ExCPV. LDY/DEY do not change carry:
 * the high-Y exit retains the clear carry from offscreen CMP #$f0. */
mysmb_u8 mysmb_world_player_vertical_carry(struct mysmb_game *game)
{
    if (game->ram[0x03d0U] >= 0xf0U) return 1U;
    if (game->ram[0x00b5U] != 1U) return 0U;
    return game->ram[0x00ceU] >= 0xd0U ? 1U : 0U;
}

/* GetEnemyBoundBoxOfs Y output; A/carry are overwritten by collision core. */
mysmb_u8 mysmb_world_enemy_box_offset(struct mysmb_game *game)
{
    return (mysmb_u8)(game->ram[8U] * 4U + 4U);
}

/* Argument/result seam for the platform caller; S9 owns full preflight proof. */
mysmb_u8 mysmb_world_enemy_box_offset_arg(struct mysmb_game *game,
                                         mysmb_u8 slot, mysmb_u8 *mask)
{
    *mask = (mysmb_u8)(game->ram[0x03d1U] & 0x0fU);
    return (mysmb_u8)(slot * 4U + 4U);
}
