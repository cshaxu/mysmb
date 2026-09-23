#ifndef MYSMB_GAME_PLAYER_H
#define MYSMB_GAME_PLAYER_H

#include "game/game.h"

/* ROM $e? MovePlayerHorizontally through MoveObjectHorizontally. */
void mysmb_player_move_horizontally(struct mysmb_game *game);
/* ROM ImposeGravity, with the caller-supplied force and speed limit. */
void mysmb_player_impose_gravity(struct mysmb_game *game, mysmb_u8 downward,
                                 mysmb_u8 upward, mysmb_u8 maximum,
                                 mysmb_u8 apply_upward);
/* ROM PlayerPhysicsSub ProcJumping/InitJS, excluding audio output. */
void mysmb_player_start_jump(struct mysmb_game *game, mysmb_u8 whirlpool);
/* ROM ImposeFriction. Physics setup supplies friction and directional limits. */
void mysmb_player_impose_friction(struct mysmb_game *game);
/* ROM PlayerCtrlRoutine controller split before movement dispatch. */
void mysmb_player_latch_input(struct mysmb_game *game, mysmb_u8 buttons);
void mysmb_player_step(struct mysmb_game *game, mysmb_u8 buttons);

#endif
