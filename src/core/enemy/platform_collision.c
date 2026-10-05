#include "core/enemy/platform.h"
#include "core/world/world.h"
#include "core/player.h"

/* ROM $DBBC ProcLPlatCollisions through $DC14 NoSideC. Box Y is
 * preserved by PlayerCollisionCore; X is the saved platform slot. */
static void platform_response(struct mysmb_game *game, mysmb_u8 slot,
                              mysmb_u8 box)
{
    mysmb_u8 delta;
    mysmb_u8 flag;
    mysmb_u8 id;
    delta = (mysmb_u8)(game->ram[0x04afU + box] - game->ram[0x04adU]);
    if (delta < 4U && (game->ram[0x009fU] & 0x80U) != 0U)
        game->ram[0x009fU] = 1U;
    delta = (mysmb_u8)(game->ram[0x04afU] - game->ram[0x04adU + box]);
    if (delta < 6U && (game->ram[0x009fU] & 0x80U) == 0U) {
        flag = game->ram[0U];
        id = game->ram[0x0016U + slot];
        if (id != 43U && id != 44U) flag = slot;
        game->ram[0x03a2U + game->ram[8U]] = flag;
        game->ram[0x001dU] = 0U;
        return;
    }
    game->ram[0U] = 1U;
    delta = (mysmb_u8)(game->ram[0x04aeU] - game->ram[0x04acU + box]);
    if (delta >= 8U) {
        ++game->ram[0U];
        /* Original CLC/SBC subtracts an additional one. */
        delta = (mysmb_u8)(game->ram[0x04aeU + box] - game->ram[0x04acU] - 1U);
        if (delta >= 9U) return;
    }
    mysmb_player_impede_move(game, game->ram[0U]);
}

/* ROM $DB5F ChkForPlayerC_LargeP / $DB78 ExLPC. */
static void check_large_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 box;
    mysmb_u8 mask;
    if (mysmb_world_player_vertical_carry(game) != 0U) return;
    box = mysmb_world_enemy_box_offset_arg(game, slot, &mask);
    game->ram[0U] = game->ram[0x00cfU + slot];
    if (mysmb_world_boxes_collide(game, 0x04acU,
                                 (mysmb_u16)(0x04acU + box)) != 0U)
        platform_response(game, slot, box);
}

/* ROM $DB45 LargePlatformCollision. Balance platforms visit the partner
 * first, then ExLPC reloads ObjectOffset for the fall-through second check. */
void mysmb_platform_collision_large(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[0x03a2U + slot] = 0xffU;
    if (game->ram[0x0747U] != 0U ||
        (game->ram[0x001eU + slot] & 0x80U) != 0U) return;
    if (game->ram[0x0016U + slot] == 36U) {
        check_large_platform(game, game->ram[0x001eU + slot]);
        slot = game->ram[8U];
    }
    check_large_platform(game, slot);
}

/* ROM $DB7B SmallPlatformCollision through $DBBA ProcSPlatCollisions.
 * On two misses the byte-wrapped +$80 shifts restore both Y coordinates. */
void mysmb_platform_collision_small(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 box;
    mysmb_u8 mask;
    if (game->ram[0x0747U] != 0U) return;
    game->ram[0x03a2U + slot] = 0U;
    if (mysmb_world_player_vertical_carry(game) != 0U) return;
    game->ram[0U] = 2U;
    do {
        box = mysmb_world_enemy_box_offset_arg(game, game->ram[8U], &mask);
        if ((mask & 2U) != 0U) return;
        if (game->ram[0x04adU + box] >= 0x20U &&
            mysmb_world_boxes_collide(game, 0x04acU,
                                     (mysmb_u16)(0x04acU + box)) != 0U) {
            platform_response(game, game->ram[8U], box);
            return;
        }
        game->ram[0x04adU + box] += 0x80U;
        game->ram[0x04afU + box] += 0x80U;
        --game->ram[0U];
    } while (game->ram[0U] != 0U);
}
