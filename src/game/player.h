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

struct mysmb_player_terrain {
    mysmb_u8 metatile;
    mysmb_u8 contact_low_nibble;
};
/* ROM BlockBufferCollision/GetBlockBufferAddr coordinate query. */
mysmb_u8 mysmb_player_query_block(const struct mysmb_game *game,
                                  mysmb_u8 x_adder, mysmb_u8 y_adder,
                                  mysmb_u8 horizontal_contact,
                                  struct mysmb_player_terrain *terrain);
mysmb_u8 mysmb_player_land_on_solid(struct mysmb_game *game,
                                    mysmb_u8 metatile, mysmb_u8 contact);
/* ROM $dc64-$dd5a PlayerBGCollision DoFootCheck through LandPlyr. */
mysmb_u8 mysmb_player_check_feet(struct mysmb_game *game);

#endif
