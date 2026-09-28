#include "game/enemy/core.h"
#include "game/enemy/stream.h"
#include "game/objects.h"

enum {
    MYSMB_ENEMY_CORE_FLAG = 0x000fU,
    MYSMB_ENEMY_CORE_ID = 0x0016U,
    MYSMB_ENEMY_CORE_AREA_PARSER_TASK = 0x071fU
};

/* ROM $c047 EnemiesAndLoopsCore.  This is deliberately one current slot:
 * VictoryMode enters it once with ObjectOffset zero, while GameEngine's
 * ProcELoop supplies all six turns around it. */
void mysmb_enemy_core_step_slot(struct mysmb_game *game,
                                const struct mysmb_area_source *source,
                                mysmb_u8 slot)
{
    mysmb_u8 id;

    /* The source caller supplies X and has already stored ObjectOffset. */
    if (game->ram[MYSMB_ENEMY_CORE_FLAG + slot] != 0U) {
        id = game->ram[MYSMB_ENEMY_CORE_ID + slot];
        /* Original RunEnemyObjectsCore vector targets NoRunCode for these
         * seven IDs. In particular, $33 is processed only by ProcessCannons.
         * The remaining vector adapters are still under structural recovery. */
        if ((id >= 0x17U && id <= 0x1aU) || id == 0x23U ||
            id == 0x30U || id == 0x33U) return;
        /* RunEnemyObjectsCore dispatches RetainerObject ($35) directly to
         * RunRetainerObj; it must not first borrow RunNormalEnemies, whose
         * attribute initialization is absent from that source branch. */
        if (slot < 5U && game->ram[MYSMB_ENEMY_CORE_ID + slot] == 0x35U) {
            mysmb_objects_draw_retainer(game, slot);
        }
        else if (slot < 5U) {
            mysmb_objects_step_normal_enemy(game, slot);
        }
        else if (game->ram[MYSMB_ENEMY_CORE_ID + slot] == 0x2eU) {
            mysmb_objects_step_power_up(game);
            mysmb_objects_finish_power_up(game);
        }
    }
    else if ((game->ram[MYSMB_ENEMY_CORE_AREA_PARSER_TASK] & 7U) != 7U) {
        /* ChkAreaTsk: parser task seven owns this turn, so ProcessEnemyData
         * must not consume a record. */
        (void)mysmb_enemy_stream_process_current(game, source, slot);
    }
}
