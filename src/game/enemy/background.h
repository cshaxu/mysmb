#ifndef MYSMB_ENEMY_BACKGROUND_H
#define MYSMB_ENEMY_BACKGROUND_H
#include "game/game.h"
struct mysmb_enemy_terrain;

/* Original EnemyBGCStateData; caller owns its state-transition decision. */
mysmb_u8 mysmb_enemy_background_state_data(const struct mysmb_game *game,
    mysmb_u8 index);

void mysmb_enemy_handle_background(struct mysmb_game *game, mysmb_u8 slot,
    const struct mysmb_enemy_terrain *terrain);
/* Existing unproved S9/S10 dependency interiors, exposed at source calls. */
void mysmb_objects_enemy_no_ground(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_enemy_land_from_probe(struct mysmb_game *game, mysmb_u8 slot,
    const struct mysmb_enemy_terrain *terrain);
void mysmb_objects_kill_enemy_above_block(struct mysmb_game *game, mysmb_u8 slot);

#endif
