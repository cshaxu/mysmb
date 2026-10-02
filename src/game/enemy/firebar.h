#ifndef MYSMB_ENEMY_FIREBAR_H
#define MYSMB_ENEMY_FIREBAR_H
#include "game/oam/oam.h"

/* Immutable data binding is required, including adjacent bytes reached by
 * the original residual lookup. These functions never execute ROM bytes. */
mysmb_u8 mysmb_firebar_get_position(struct mysmb_game *game, mysmb_u8 phase);
mysmb_u8 mysmb_firebar_collision(struct mysmb_game *game, mysmb_u8 oam);
mysmb_u8 mysmb_firebar_draw_collision(struct mysmb_game *game);

/* Original child ABI seams. Their nodes retain their later proof owners. */
void mysmb_firebar_offscreen(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_firebar_spin(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 speed);
mysmb_u8 mysmb_firebar_relative(struct mysmb_game *game, mysmb_u8 slot);
#endif
