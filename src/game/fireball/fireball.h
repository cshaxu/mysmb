#ifndef MYSMB_GAME_FIREBALL_FIREBALL_H
#define MYSMB_GAME_FIREBALL_FIREBALL_H

#include "game/game.h"

/* ROM ProcFireball_Bubble and FireballObjCore. */
void mysmb_fireball_try_spawn(struct mysmb_game *game);
void mysmb_fireball_step(struct mysmb_game *game);
/* Original child seams; extraction does not certify their interiors. */
void mysmb_fireball_step_object(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_fireball_check_bubble(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_fireball_relative_bubble_position(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_fireball_get_bubble_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_fireball_draw_bubble(struct mysmb_game *game, mysmb_u8 slot);
/* ROM $9165 ChkSwimE's direct SetupBubble entry. */
void mysmb_fireball_setup_bubble(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_fireball_step_bubbles(struct mysmb_game *game);

#endif
