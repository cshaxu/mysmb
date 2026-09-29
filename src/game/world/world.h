#ifndef MYSMB_GAME_WORLD_WORLD_H
#define MYSMB_GAME_WORLD_WORLD_H

#include "game/game.h"

/* ROM $BFD7 common gravity consumes scratch $00/$01/$02. */
void mysmb_world_impose_gravity(struct mysmb_game *game, mysmb_u8 offset,
                                mysmb_u8 upward);
void mysmb_world_residual_gravity(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_world_move_platform_vertically(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 moving_up);

/* ROM ImposeGravityBlock -> ImposeGravity for the block object array. */
void mysmb_world_impose_gravity_block(struct mysmb_game *game, mysmb_u8 slot);
/* Existing red gravity child; common arithmetic proof remains S9-owned. */
void mysmb_world_red_gravity(struct mysmb_game *game, mysmb_u8 offset,
                             mysmb_u8 moving_up);

void mysmb_world_impose_gravity_misc(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 amount, mysmb_u8 maximum_speed);

/* ROM ImposeGravity/MoveObjectHorizontally with a caller-selected SprObject offset. */
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *game, mysmb_u8 offset,
                                            mysmb_u8 downward_force, mysmb_u8 maximum_speed);
mysmb_u8 mysmb_world_move_spr_object_horizontally(struct mysmb_game *game, mysmb_u8 offset);
/* ROM MoveEnemyHorizontally: increments to the enemy SprObject offset. */
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *game, mysmb_u8 slot);

/* ROM $dc71 BoundingBoxCore and $dcf6 PlayerCollisionCore.  These are
 * shared game-state primitives: actor routes select their boxes and act on
 * the result, while this module only writes/compares the source RAM boxes. */
void mysmb_world_set_bounding_box(struct mysmb_game *game,
                                  mysmb_u16 address, mysmb_u8 control,
                                  mysmb_u8 x, mysmb_u8 y);
/* Original GetFireballBoundBox child boundary. */
void mysmb_world_get_fireball_bounding_box(struct mysmb_game *game, mysmb_u8 slot);
/* ROM CheckRightScreenBBox / CheckLeftScreenBBox. */
void mysmb_world_clip_bounding_box_to_screen(struct mysmb_game *game,
                                               mysmb_u16 address,
                                               mysmb_u8 object_page,
                                               mysmb_u8 object_x);
mysmb_u8 mysmb_world_boxes_collide(const struct mysmb_game *game,
                                   mysmb_u16 first, mysmb_u16 second);
mysmb_u8 mysmb_world_collision_page(mysmb_u8 page, mysmb_u8 object_x,
                                    mysmb_u8 probed_x);
/* ROM BlockBufferCollision/GetBlockBufferAddr coordinate result for the
 * player probe.  PlayerCtrlRoutine chooses every probe-table entry; this
 * world primitive only constructs and reads the block-buffer address. */
struct mysmb_player_terrain {
    mysmb_u8 metatile;
    mysmb_u8 contact_low_nibble;
    mysmb_u8 block_address_low;
    mysmb_u8 block_row_offset;
};
mysmb_u8 mysmb_world_query_player_block(struct mysmb_game *game,
                                        mysmb_u8 x_adder, mysmb_u8 y_adder,
                                        mysmb_u8 horizontal_contact,
                                        struct mysmb_player_terrain *terrain);
/* ROM EnemyLanding -> InitVStf. */
void mysmb_world_land_enemy(struct mysmb_game *game, mysmb_u8 slot);
/* ROM BlockBufferChk_Enemy output. */
struct mysmb_enemy_terrain {
    mysmb_u8 metatile;
    mysmb_u8 contact_low_nibble;
    mysmb_u8 block_address_low;
    mysmb_u8 block_row_offset;
    mysmb_u16 block_address;
};
/* ROM BlockBufferChk_Enemy -> BlockBufferCollision. With valid slot/adder
 * inputs, block_row_offset is available even when the row is out of bounds;
 * other output fields require a successful return. */
mysmb_u8 mysmb_world_query_enemy_block(struct mysmb_game *game,
                                       mysmb_u8 slot, mysmb_u8 adder_index,
                                       mysmb_u8 horizontal_contact,
                                       struct mysmb_enemy_terrain *terrain);
/* ROM FireballBGCollision / BlockBufferChk_FBall / ChkForNonSolids. */
void mysmb_world_fireball_background_collision(struct mysmb_game *game, mysmb_u8 slot);
/* ROM FireballEnemyCollision: scans every source enemy slot, applies each
 * source hit handoff in descending slot order, and sets fireball state. */
void mysmb_world_fireball_enemy_collision(struct mysmb_game *game, mysmb_u8 slot);
/* ROM HandleEnemyFBallCol -> ChkToStunEnemies -> EnemySmackScore. */
void mysmb_world_handle_fireball_enemy_hit(struct mysmb_game *game,
                                          mysmb_u8 enemy_slot);

/* ROM ShellOrBlockDefeat: also entered directly by later contact callers. */
void mysmb_world_shell_or_block_defeat(struct mysmb_game *game, mysmb_u8 slot);
/* Existing ChkToStunEnemies dependency; its body awaits source-order proof. */
void mysmb_world_stun_enemy(struct mysmb_game *game, mysmb_u8 slot,
                            mysmb_u8 source_a);

/* ROM CheckForClimbMTiles and LandPlyr. */
mysmb_u8 mysmb_world_is_climbable(mysmb_u8 metatile);
mysmb_u8 mysmb_world_land_player_on_solid(struct mysmb_game *game,
                                           mysmb_u8 metatile, mysmb_u8 contact);

/* Existing child seams; source-order proof remains with their own nodes. */
void mysmb_world_set_stun(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_world_player_vertical_carry(struct mysmb_game *game);
mysmb_u8 mysmb_world_enemy_box_offset(struct mysmb_game *game);
/* GetEnemyBoundBoxOfsArg dependency: Y offset and A's low offscreen nibble.
 * The S9 node proof remains separate from the platform caller. */
mysmb_u8 mysmb_world_enemy_box_offset_arg(struct mysmb_game *game,
                                         mysmb_u8 slot, mysmb_u8 *mask);

#endif
