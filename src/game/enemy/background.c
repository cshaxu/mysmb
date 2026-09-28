#include "game/objects.h"
#include "game/world/world.h"

/* ROM $e163-$e182 EnemyJump/DoSide. Both normal-enemy and star callers
 * reach this body. Existing terrain children retain separate proof status. */
void mysmb_objects_step_enemy_jump_terrain(struct mysmb_game *game,
                                           mysmb_u8 slot)
{
    struct mysmb_enemy_terrain terrain;
    mysmb_u8 tile;

    /* SubtEnemyYPos compares the wrapped ADC byte, not a host-width sum. */
    if ((mysmb_u8)(game->ram[0x00cfU + slot] + 0x3eU) >= 0x44U &&
        (mysmb_u8)(game->ram[0x00a0U + slot] + 2U) >= 3U) {
        tile = mysmb_world_query_enemy_block(game, slot, 0x15U, 0U, &terrain) != 0U ?
            terrain.metatile : 0U;
        if (tile != 0U && mysmb_objects_is_solid_terrain(tile) != 0U) {
            mysmb_world_land_enemy(game, slot);
            game->ram[0x00a0U + slot] = 0xfdU;
        }
    }
    mysmb_objects_check_enemy_side(game, slot);
}

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
