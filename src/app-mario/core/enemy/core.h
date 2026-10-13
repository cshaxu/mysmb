#ifndef MYSMB_GAME_ENEMY_CORE_H
#define MYSMB_GAME_ENEMY_CORE_H

#include "core/area.h"

/* ROM RunEnemyObjectsCore reloads the current slot from ObjectOffset. */
void mysmb_enemy_run_objects(struct mysmb_game *game);
void mysmb_enemy_run_large_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_run_small_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_run_bowser(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_movement_dispatch(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_warp_zone(struct mysmb_game *game, mysmb_u8 slot);

/* ROM $c047 EnemiesAndLoopsCore for exactly one current ObjectOffset.  The
 * caller owns whether this is GameEngine's six-slot loop or VictoryMode's
 * single slot-zero call. */
void mysmb_enemy_core_step_slot(struct mysmb_game *game,
                                const struct mysmb_area_source *source,
                                mysmb_u8 slot);

#endif
