#include "game/enemy/core.h"
#include "game/enemy/stream.h"
#include "game/fireball/fireball.h"
#include "game/objects.h"

enum {
    MYSMB_ENEMY_CORE_FLAG = 0x000fU,
    MYSMB_ENEMY_CORE_ID = 0x0016U,
    MYSMB_ENEMY_CORE_AREA_PARSER_TASK = 0x071fU
};

/* ROM $a0d7-$a11a GameEngine's actor phase.  The frame root owns the mode
 * route; this module exclusively owns ObjectOffset's fireball and six-slot
 * EnemiesAndLoopsCore schedule. */
void mysmb_enemy_core_step(struct mysmb_game *game,
                           const struct mysmb_area_source *source)
{
    mysmb_u8 slot;

    mysmb_fireball_step(game);
    for (slot = 0U; slot < 6U; ++slot) {
        if (game->ram[MYSMB_ENEMY_CORE_FLAG + slot] != 0U) {
            if (slot < 5U) {
                mysmb_objects_step_normal_enemy(game, slot);
            }
            else if (game->ram[MYSMB_ENEMY_CORE_ID + slot] == 0x2eU) {
                mysmb_objects_step_power_up(game);
                mysmb_objects_finish_power_up(game);
            }
        }
        else if ((game->ram[MYSMB_ENEMY_CORE_AREA_PARSER_TASK] & 7U) != 7U) {
            /* ROM EnemiesAndLoopsCore ChkAreaTsk: parser task seven owns
             * this turn, so ProcessEnemyData must not consume a record. */
            (void)mysmb_enemy_stream_process_current(game, source, slot);
        }
        mysmb_objects_step_floatey_number(game, slot);
    }
}
