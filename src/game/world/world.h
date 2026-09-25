#ifndef MYSMB_GAME_WORLD_WORLD_H
#define MYSMB_GAME_WORLD_WORLD_H

#include "game/game.h"

/* ROM ImposeGravityBlock -> ImposeGravity for the block object array. */
void mysmb_world_impose_gravity_block(struct mysmb_game *game, mysmb_u8 slot);

void mysmb_world_impose_gravity_misc(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 amount, mysmb_u8 maximum_speed);

/* ROM ImposeGravity/MoveObjectHorizontally with a caller-selected SprObject offset. */
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *game, mysmb_u8 offset,
                                            mysmb_u8 downward_force, mysmb_u8 maximum_speed);
void mysmb_world_move_spr_object_horizontally(struct mysmb_game *game, mysmb_u8 offset);

/* ROM $dc71 BoundingBoxCore and $dcf6 PlayerCollisionCore.  These are
 * shared game-state primitives: actor routes select their boxes and act on
 * the result, while this module only writes/compares the source RAM boxes. */
void mysmb_world_set_bounding_box(struct mysmb_game *game,
                                  mysmb_u16 address, mysmb_u8 control,
                                  mysmb_u8 x, mysmb_u8 y);
mysmb_u8 mysmb_world_boxes_collide(const struct mysmb_game *game,
                                   mysmb_u16 first, mysmb_u16 second);
mysmb_u8 mysmb_world_collision_page(mysmb_u8 page, mysmb_u8 object_x,
                                    mysmb_u8 probed_x);
/* ROM FireballBGCollision / BlockBufferChk_FBall / ChkForNonSolids. */
void mysmb_world_fireball_background_collision(struct mysmb_game *game, mysmb_u8 slot);

/* ROM CheckForClimbMTiles and LandPlyr. */
mysmb_u8 mysmb_world_is_climbable(mysmb_u8 metatile);
mysmb_u8 mysmb_world_land_player_on_solid(struct mysmb_game *game,
                                           mysmb_u8 metatile, mysmb_u8 contact);

#endif
