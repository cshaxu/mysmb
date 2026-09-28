#ifndef MYSMB_GAME_ENEMY_ACTOR_SLOTS_H
#define MYSMB_GAME_ENEMY_ACTOR_SLOTS_H

#include "game/game.h"

/* Current-slot entries extracted from existing actor bodies. Child semantic
 * proof remains with each original owner; these declarations grant no credit. */
void mysmb_objects_step_bullet_bills_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_piranha_plants_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_swimming_cheep_cheeps_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_podoboos_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_bloobers_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_hammer_bros_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_red_paratroopas_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_flying_green_paratroopas_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_flying_cheep_cheeps_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_platforms_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_bowser_flames_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_fireworks_slot(struct mysmb_game *game, mysmb_u8 slot);
/* Existing EndAreaPoints tail; its source-order proof belongs to S6. */
void mysmb_objects_end_area_points(struct mysmb_game *game);
void mysmb_objects_step_star_flags_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_step_lakitus_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_step_spiny_eggs_slot(struct mysmb_game *game, mysmb_u8 slot);

/* Proc children keep their separate source-order conformance status. */
void mysmb_enemy_proc_bowser_flame(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_enemy_proc_firebar(struct mysmb_game *game, mysmb_u8 slot);

/* Nonzero retains the old aggregate injury exit until caller replacement. */
mysmb_u8 mysmb_objects_step_firebars_slot(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_bowsers_slot(struct mysmb_game *game, mysmb_u8 slot);

#endif
