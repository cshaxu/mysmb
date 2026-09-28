#ifndef MYSMB_GAME_ENEMY_CORE_H
#define MYSMB_GAME_ENEMY_CORE_H

#include "game/area.h"

/* ROM $c047 EnemiesAndLoopsCore for exactly one current ObjectOffset.  The
 * caller owns whether this is GameEngine's six-slot loop or VictoryMode's
 * single slot-zero call. */
void mysmb_enemy_core_step_slot(struct mysmb_game *game,
                                const struct mysmb_area_source *source,
                                mysmb_u8 slot);

#endif
