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
void mysmb_objects_step_normal_enemies(struct mysmb_game *game);
/* ROM $aa0f-$aa4c InitBulletBill/BulletBillHandler, sans rendering. */
void mysmb_objects_step_bullet_bills(struct mysmb_game *game);
/* ROM $aa9f-$aae8 InitPiranhaPlant/MovePiranhaPlant, sans rendering. */
void mysmb_objects_step_piranha_plants(struct mysmb_game *game);
/* ROM $ad7b-$ae04 InitCheepCheep/MoveSwimmingCheepCheep, sans rendering. */
void mysmb_objects_step_swimming_cheep_cheeps(struct mysmb_game *game);
/* ROM $ad5a-$ad79 InitPodoboo and $af13-$af25 MovePodoboo, sans rendering. */
void mysmb_objects_step_podoboos(struct mysmb_game *game);
/* ROM $ad3e-$ad59 InitBloober and $b004-$b09a MoveBloober, sans rendering. */
void mysmb_objects_step_bloobers(struct mysmb_game *game);
/* ROM $aea4-$aeb0 InitJumpGPTroopa and $afbd-$afc2 MoveJumpingEnemy. */
void mysmb_objects_step_jumping_paratroopas(struct mysmb_game *game);
/* ROM $ad6c-$ad95 InitRedPTroopa and $afc3-$afe1 ProcMoveRedPTroopa. */
void mysmb_objects_step_red_paratroopas(struct mysmb_game *game);
/* ROM $afe2-$b003 MoveFlyGreenPTroopa, sans rendering. */
void mysmb_objects_step_flying_green_paratroopas(struct mysmb_game *game);
void mysmb_objects_check_hazard_enemy_collision(struct mysmb_game *game);
void mysmb_objects_check_bullet_bill_stomp(struct mysmb_game *game);
void mysmb_objects_check_bloober_stomp(struct mysmb_game *game);
/* ROM $dcfd-$ddcb EnemyStomped, bounded to Lakitu (ID $11). */
void mysmb_objects_check_lakitu_stomp(struct mysmb_game *game);
/* ROM $dcfd-$ddcb / $e06a ChkForDemoteKoopa, IDs $0e-$10. */
void mysmb_objects_check_paratroopa_stomp(struct mysmb_game *game);
/* ROM $dcfd-$ddcb PlayerEnemyCollision, bounded to power-up slot five. */
void mysmb_objects_check_power_up_collision(struct mysmb_game *game);
/* ROM $ddcd HandlePowerUpCollision state effect. */
void mysmb_objects_collect_power_up(struct mysmb_game *game);
/* ROM FloateyNumbersRoutine, excluding OAM output. */
void mysmb_objects_step_floatey_numbers(struct mysmb_game *game);
/* ROM $ba55-$bad2 Setup_Vine/VineObjectHandler, excluding drawing. */
void mysmb_objects_start_vine(struct mysmb_game *game, mysmb_u8 block_slot);
void mysmb_objects_step_vine(struct mysmb_game *game);
/* ROM HandleCoinMetatile/GiveOneCoin. */
void mysmb_objects_collect_coin(struct mysmb_game *game, mysmb_u8 block_low,
                                mysmb_u8 block_row);

#endif
