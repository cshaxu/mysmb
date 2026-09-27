#include "game/enemy/core.h"
#include "game/enemy/stream.h"
#include "game/fireball/fireball.h"
#include "game/objects.h"

enum {
    MYSMB_ENEMY_CORE_OBJECT_OFFSET = 0x0008U,
    MYSMB_ENEMY_CORE_FLAG = 0x000fU,
    MYSMB_ENEMY_CORE_ID = 0x0016U,
    MYSMB_ENEMY_CORE_AREA_PARSER_TASK = 0x071fU
};

/* ROM $c06b EnemiesAndLoopsCore.  This is deliberately one current slot:
 * VictoryMode enters it once with ObjectOffset zero, while GameEngine's
 * ProcELoop supplies all six turns around it. */
void mysmb_enemy_core_step_slot(struct mysmb_game *game,
                                const struct mysmb_area_source *source,
                                mysmb_u8 slot)
{
    /* The C parameter carries X across collaborators, but ObjectOffset is
     * also a source-visible RAM write at each EnemiesAndLoopsCore entry. */
    game->ram[MYSMB_ENEMY_CORE_OBJECT_OFFSET] = slot;
    if (game->ram[MYSMB_ENEMY_CORE_FLAG + slot] != 0U) {
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

/* ROM $a0d7-$a11a GameEngine's actor phase.  The frame root owns the mode
 * route; this module exclusively owns the fireball and six-slot schedule. */
void mysmb_enemy_core_step(struct mysmb_game *game,
                           const struct mysmb_area_source *source)
{
    mysmb_u8 slot;

    mysmb_fireball_step(game);
    for (slot = 0U; slot < 6U; ++slot) {
        mysmb_enemy_core_step_slot(game, source, slot);
        mysmb_objects_step_floatey_number(game, slot);
    }
}
