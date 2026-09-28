#include "game/enemy/core.h"
#include "game/enemy/stream.h"
#include "game/enemy/loop.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"

enum {
    MYSMB_ENEMY_CORE_FLAG = 0x000fU,
    MYSMB_ENEMY_CORE_ID = 0x0016U,
    MYSMB_ENEMY_CORE_AREA_PARSER_TASK = 0x071fU
};

/* ROM $b7a4 WarpZoneObject: preserve the source bitwise Y test, including
 * noncanonical high-byte inputs. EraseEnemyObject owns the eight clears. */
void mysmb_enemy_warp_zone(struct mysmb_game *game, mysmb_u8 slot)
{
    if (game->ram[0x0723U] == 0U) return;
    if ((game->ram[0x00ceU] & game->ram[0x00b5U]) != 0U) return;
    game->ram[0x0723U] = 0U;
    game->ram[0x06d6U] = (mysmb_u8)(game->ram[0x06d6U] + 1U);
    mysmb_objects_erase_enemy(game, slot);
}

/* ROM $c882 RunEnemyObjectsCore / $c88f JmpEO, valid IDs $00-$35.
 * Select the source family at the current slot, never scan other actors.
 * Existing child interiors remain under recovery: in particular the platform
 * child still combines RunLargePlatform/RunSmallPlatform, and Bowser's two
 * entries do not yet reproduce the duplicate-slot source state. */
void mysmb_enemy_run_objects(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 id;

    slot = game->ram[0x0008U];
    id = game->ram[MYSMB_ENEMY_CORE_ID + slot];
    if (id < 0x15U) {
        mysmb_objects_step_normal_enemy(game, slot);
        return;
    }
    switch (id) {
    case 0x15U:
        mysmb_objects_step_bowser_flames_slot(game, slot);
        break;
    case 0x16U:
        mysmb_objects_step_fireworks_slot(game, slot);
        break;
    case 0x1bU: case 0x1cU: case 0x1dU: case 0x1eU:
    case 0x1fU: case 0x20U: case 0x21U: case 0x22U:
        (void)mysmb_objects_step_firebars_slot(game, slot);
        break;
    case 0x24U: case 0x25U: case 0x26U: case 0x27U:
    case 0x28U: case 0x29U: case 0x2aU:
    case 0x2bU: case 0x2cU:
        mysmb_objects_step_platforms_slot(game, slot);
        break;
    case 0x2dU:
        mysmb_objects_step_bowsers_slot(game, slot);
        mysmb_objects_draw_bowsers_slot(game, slot);
        break;
    case 0x2eU:
        mysmb_objects_step_power_up(game);
        break;
    case 0x2fU:
        mysmb_objects_step_vine(game, slot);
        break;
    case 0x31U:
        mysmb_objects_step_star_flags_slot(game, slot);
        break;
    case 0x32U:
        mysmb_objects_step_jumpspring(game, slot);
        break;
    case 0x34U:
        mysmb_enemy_warp_zone(game, slot);
        break;
    case 0x35U:
        mysmb_objects_draw_retainer(game, slot);
        break;
    /* Source NoRunCode targets, including the separately handled cannon. */
    case 0x17U: case 0x18U: case 0x19U: case 0x1aU:
    case 0x23U: case 0x30U: case 0x33U:
        break;
    }
}

/* ROM $c047 EnemiesAndLoopsCore.  This is deliberately one current slot:
 * VictoryMode enters it once with ObjectOffset zero, while GameEngine's
 * ProcELoop supplies all six turns around it. */
void mysmb_enemy_core_step_slot(struct mysmb_game *game,
                                const struct mysmb_area_source *source,
                                mysmb_u8 slot)
{
    /* The source caller supplies X and has already stored ObjectOffset. */
    mysmb_u8 flag;
    flag = game->ram[MYSMB_ENEMY_CORE_FLAG + slot];
    if ((flag & 0x80U) != 0U) {
        if (game->ram[MYSMB_ENEMY_CORE_FLAG + (flag & 0x0fU)] == 0U)
            game->ram[MYSMB_ENEMY_CORE_FLAG + slot] = 0U;
        return;
    }
    if (flag != 0U) {
        mysmb_enemy_run_objects(game);
    }
    else if ((game->ram[MYSMB_ENEMY_CORE_AREA_PARSER_TASK] & 7U) != 7U) {
        /* ChkAreaTsk: parser task seven owns this turn, so ProcessEnemyData
         * must not consume a record. */
        mysmb_enemy_process_loop_command(game, source, slot);
    }
}
