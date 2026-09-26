#ifndef MYSMB_GAME_PLAYER_H
#define MYSMB_GAME_PLAYER_H

#include "game/game.h"

/* ROM $e? MovePlayerHorizontally through MoveObjectHorizontally. */
mysmb_u8 mysmb_player_move_horizontally(struct mysmb_game *game);
/* ROM ImposeGravity, with the caller-supplied force and speed limit. */
void mysmb_player_impose_gravity(struct mysmb_game *game, mysmb_u8 downward,
                                 mysmb_u8 upward, mysmb_u8 maximum,
                                 mysmb_u8 apply_upward);
/* ROM PlayerPhysicsSub ProcJumping/InitJS and PJumpSnd queue output. */
void mysmb_player_start_jump(struct mysmb_game *game, mysmb_u8 whirlpool);
/* ROM ImposeFriction. Physics setup supplies friction and directional limits. */
void mysmb_player_impose_friction(struct mysmb_game *game);
/* ROM PlayerCtrlRoutine controller split before movement dispatch. */
void mysmb_player_latch_input(struct mysmb_game *game, mysmb_u8 buttons);
/* ROM PlayerPhysicsSub climbing parameters and ClimbingSub movement. */
void mysmb_player_configure_climb(struct mysmb_game *game);
void mysmb_player_climb(struct mysmb_game *game);
/* ROM $b50b-$b5cb X_Physics setup for friction and horizontal speed limits. */
void mysmb_player_configure_horizontal(struct mysmb_game *game);
/* ROM GetPlayerAnimSpeed, including running and low-speed skid state. */
void mysmb_player_update_animation_speed(struct mysmb_game *game,
                                         mysmb_u8 buttons);
void mysmb_player_step(struct mysmb_game *game, mysmb_u8 buttons);
/* ROM $b069-$b07c Vine_AutoClimb. */
void mysmb_player_step_auto_climb(struct mysmb_game *game);
/* ROM $b0f4-$b138 PlayerChangeSize and $b139-$b154 PlayerFireFlower. */
void mysmb_player_step_change_size(struct mysmb_game *game);
/* ROM $b114-$b138 PlayerInjuryBlink, excluding palette upload. */
void mysmb_player_step_injury_blink(struct mysmb_game *game, mysmb_u8 buttons);
void mysmb_player_step_fire_flower(struct mysmb_game *game);

/* Neutral fixed-input checkpoint for the translated player route. */
struct mysmb_player_checkpoint {
    mysmb_u32 frame_number;
    mysmb_u8 engine_subroutine;
    mysmb_u8 state;
    mysmb_u8 page;
    mysmb_u8 x;
    mysmb_u8 y_high;
    mysmb_u8 y;
    mysmb_u8 x_speed;
    mysmb_u8 y_speed;
    mysmb_u8 x_force;
    mysmb_u8 y_force;
    mysmb_u8 screen_left_page;
    mysmb_u8 screen_left_x;
};
void mysmb_player_checkpoint(const struct mysmb_game *game,
                             struct mysmb_player_checkpoint *checkpoint);

mysmb_u8 mysmb_player_handle_vertical_pipe(struct mysmb_game *game,
                                           mysmb_u8 left, mysmb_u8 right);
void mysmb_player_step_vertical_pipe(struct mysmb_game *game);
void mysmb_player_step_side_pipe(struct mysmb_game *game);
/* Internal C control result for ChkFootMTile's terminal JMP ImpedePlayerMove. */
#define MYSMB_PLAYER_FEET_TERMINAL_IMPEDE 3U

/* ROM $dc64-$dd5a PlayerBGCollision DoFootCheck through LandPlyr. */
mysmb_u8 mysmb_player_check_feet(struct mysmb_game *game);
/* ROM $9131-$9196 Entrance_GameTimerSetup, excluding palette/object owners. */
void mysmb_player_initialize_entrance(struct mysmb_game *game);
/* ROM $b069-$b0e5 PlayerEntrance normal-entry completion. */
void mysmb_player_finish_normal_entrance(struct mysmb_game *game);
/* ROM $af93-$b068 ScrollHandler including player offscreen-edge clamping. */
void mysmb_player_update_scroll(struct mysmb_game *game);
/* ROM ScrollScreen: apply a caller-owned explicit horizontal scroll amount. */
void mysmb_player_scroll_screen(struct mysmb_game *game, mysmb_u8 amount);
/* ROM $df4b-$df7d ImpedePlayerMove, with SideCheckLoop's physical side counter. */
void mysmb_player_impede_move(struct mysmb_game *game, mysmb_u8 collision_side);
/* ROM $dd5e-$de46 side samples, restricted to solid metatile blocking. */
mysmb_u8 mysmb_player_check_sides(struct mysmb_game *game);
/* ROM $dcba-$dcf5 head sample, restricted to solid-metatile velocity stop. */
mysmb_u8 mysmb_player_check_head(struct mysmb_game *game);

#endif
