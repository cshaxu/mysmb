#ifndef MYSMB_GAME_ENEMY_FRENZY_H
#define MYSMB_GAME_ENEMY_FRENZY_H

#include "game/game.h"

/* ROM MoveLakitu, LakituAndSpinyHandler and the Spiny egg landing route. */
void mysmb_enemy_step_lakitus(struct mysmb_game *game);
void mysmb_enemy_step_lakitu_frenzy(struct mysmb_game *game);
void mysmb_enemy_step_spiny_eggs(struct mysmb_game *game);
void mysmb_enemy_init_flying_cheep_frenzy(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_step_bowser_flame_frenzy(struct mysmb_game *game);
void mysmb_enemy_step_firework_frenzy(struct mysmb_game *game);
void mysmb_enemy_end_frenzy(struct mysmb_game *game, mysmb_u8 controller_slot);
void mysmb_enemy_step_bullet_bill_cheep_frenzy(struct mysmb_game *game, mysmb_u8 slot);

#endif
