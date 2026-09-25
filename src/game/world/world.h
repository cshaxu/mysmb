#ifndef MYSMB_GAME_WORLD_WORLD_H
#define MYSMB_GAME_WORLD_WORLD_H

#include "game/game.h"

/* ROM ImposeGravityBlock -> ImposeGravity for the block object array. */
void mysmb_world_impose_gravity_block(struct mysmb_game *game, mysmb_u8 slot);

void mysmb_world_impose_gravity_misc(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 amount, mysmb_u8 maximum_speed);

#endif
