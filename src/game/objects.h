#ifndef MYSMB_GAME_OBJECTS_H
#define MYSMB_GAME_OBJECTS_H

#include "game/game.h"

/* ROM $bed4 BlockObjMT_Updater. */
void mysmb_objects_apply_block_replacements(struct mysmb_game *game);
/* ROM $be70 BlockObjectsCore, bounded to the bouncing-block state. */
void mysmb_objects_step_blocks(struct mysmb_game *game);
/* ROM $bced-$bd9b PlayerHeadCollision through BumpBlock, for matched blocks. */
mysmb_u8 mysmb_objects_start_head_bump(struct mysmb_game *game,
                                       mysmb_u8 metatile,
                                       mysmb_u8 block_low,
                                       mysmb_u8 block_row);
/* ROM $bb51-$bbd0 jumping-coin misc-object route. */
void mysmb_objects_start_jump_coin(struct mysmb_game *game, mysmb_u8 page,
                                   mysmb_u8 x, mysmb_u8 y);
void mysmb_objects_step_misc(struct mysmb_game *game);
/* ROM $98?? ProcFireball_Bubble through $98?? FireballObjCore, sans rendering. */
void mysmb_objects_step_fireballs(struct mysmb_game *game);
/* ROM $bbc5-$bc15 SetupPowerUp/PowerUpObjHandler, emergence phase. */
void mysmb_objects_start_power_up(struct mysmb_game *game, mysmb_u8 block_slot,
                                  mysmb_u8 power_up_type);
void mysmb_objects_step_power_up(struct mysmb_game *game);
/* ROM $dcfd-$ddcb PlayerEnemyCollision, bounded to power-up slot five. */
void mysmb_objects_check_power_up_collision(struct mysmb_game *game);
/* ROM $ddcd HandlePowerUpCollision state effect. */
void mysmb_objects_collect_power_up(struct mysmb_game *game);
/* ROM $ba55-$bad2 Setup_Vine/VineObjectHandler, excluding drawing. */
void mysmb_objects_start_vine(struct mysmb_game *game, mysmb_u8 block_slot);
void mysmb_objects_step_vine(struct mysmb_game *game);
/* ROM HandleCoinMetatile/GiveOneCoin. */
void mysmb_objects_collect_coin(struct mysmb_game *game, mysmb_u8 block_low,
                                mysmb_u8 block_row);

#endif
