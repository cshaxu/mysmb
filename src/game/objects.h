#ifndef MYSMB_GAME_OBJECTS_H
#define MYSMB_GAME_OBJECTS_H

#include "game/game.h"

/* ROM $bed4 BlockObjMT_Updater. */
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
/* ROM $bbc5-$bc15 SetupPowerUp/PowerUpObjHandler, emergence phase. */
void mysmb_objects_start_power_up(struct mysmb_game *game, mysmb_u8 block_slot,
                                  mysmb_u8 power_up_type);
void mysmb_objects_step_power_up(struct mysmb_game *game);
void mysmb_objects_finish_power_up(struct mysmb_game *game);
/* RunNormalEnemies for one ObjectOffset; GameEngine uses this with stream parsing. */
void mysmb_objects_step_normal_enemy(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_normal_enemies(struct mysmb_game *game);
/* ROM GetEnemyBoundBox / GetMaskedOffScrBits. */
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_get_enemy_x_offscreen_bits(const struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *game, mysmb_u8 slot);
/* ROM OffscreenBoundsCheck / EraseEnemyObject. */
void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *game, mysmb_u8 slot);
/* ROM EnemiesCollision/ProcEnemyCollisions for regular enemy slots. */
void mysmb_objects_step_enemy_collisions(struct mysmb_game *game);
/* ROM $aa0f-$aa4c InitBulletBill/BulletBillHandler and its OAM output. */
void mysmb_objects_step_bullet_bills(struct mysmb_game *game);
/* ROM $aa9f-$aae8 InitPiranhaPlant/MovePiranhaPlant, sans rendering. */
void mysmb_objects_step_piranha_plants(struct mysmb_game *game);
/* ROM JumpspringHandler / EnemyGfxHandler for object $32. */
void mysmb_objects_step_jumpspring(struct mysmb_game *game, mysmb_u8 slot);
/* ROM $ad7b-$ae04 InitCheepCheep/MoveSwimmingCheepCheep. */
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
/* ROM MoveFlyingCheepCheep, sans rendering. */
void mysmb_objects_step_flying_cheep_cheeps(struct mysmb_game *game);
/* ROM InitEnemyFrenzy/InitFlyingCheepCheep. */
void mysmb_objects_step_flying_cheep_frenzy(struct mysmb_game *game);
/* ROM InitShortFirebar/InitLongFirebar and ProcFirebar, sans drawing. */
void mysmb_objects_step_firebars(struct mysmb_game *game);
/* ROM RunLargePlatform through RunSmallPlatform, excluding OAM ropes. */
void mysmb_objects_step_platforms(struct mysmb_game *game);
/* ROM InitBowser/RunBowser, excluding OAM output. */
void mysmb_objects_step_bowsers(struct mysmb_game *game);
/* ROM $d8aa-$d91d BridgeCollapse, including its VRAM_Buffer1 metatile writes. */
mysmb_u8 mysmb_objects_step_bridge_collapse(struct mysmb_game *game);
/* ROM InitBowserFlame/ProcBowserFlame, excluding OAM output. */
void mysmb_objects_step_bowser_flame_frenzy(struct mysmb_game *game);
void mysmb_objects_step_bowser_flames(struct mysmb_game *game);
/* ROM RunFireworks, InitFireworks, and RunStarFlagObj. */
void mysmb_objects_step_fireworks(struct mysmb_game *game);
void mysmb_objects_step_firework_frenzy(struct mysmb_game *game);
void mysmb_objects_step_star_flags(struct mysmb_game *game);
/* ROM FlagpoleObject, FlagpoleRoutine, and FlagpoleGfxHandler. */
void mysmb_objects_start_flagpole(struct mysmb_game *game, mysmb_u8 page,
                                  mysmb_u8 x);
void mysmb_objects_step_flagpole(struct mysmb_game *game);
/* ROM ProcHammerBro through MoveHammerBroXDir, before hammer misc objects. */
void mysmb_objects_step_hammer_bros(struct mysmb_game *game);
void mysmb_objects_check_hazard_enemy_collision(struct mysmb_game *game);
/* ROM ForceInjury: shared by collision and timer-expiry routes. */
void mysmb_objects_force_injury(struct mysmb_game *game);
void mysmb_objects_check_bullet_bill_stomp(struct mysmb_game *game);
void mysmb_objects_check_bloober_stomp(struct mysmb_game *game);
/* ROM $dcfd-$ddcb EnemyStomped, bounded to Lakitu (ID $11). */
void mysmb_objects_check_lakitu_stomp(struct mysmb_game *game);
/* ROM $dcfd-$ddcb EnemyStomped, bounded to Hammer Bro (ID $05). */
void mysmb_objects_check_hammer_bro_stomp(struct mysmb_game *game);
/* ROM $dcfd-$ddcb / $e06a ChkForDemoteKoopa, IDs $0e-$10. */
void mysmb_objects_check_paratroopa_stomp(struct mysmb_game *game);
/* ROM $dcfd-$ddcb PlayerEnemyCollision, bounded to power-up slot five. */
void mysmb_objects_check_power_up_collision(struct mysmb_game *game);
/* ROM $ddcd HandlePowerUpCollision state effect. */
void mysmb_objects_collect_power_up(struct mysmb_game *game);
/* ROM FloateyNumbersRoutine, excluding OAM output. */
/* ROM SetupFloateyNumber when RelativeEnemyPosition has prepared $03ae. */
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *game,
                                             mysmb_u8 slot, mysmb_u8 control);
void mysmb_objects_step_floatey_number(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_floatey_numbers(struct mysmb_game *game);
/* ROM $ba55-$bad2 Setup_Vine/VineObjectHandler, excluding drawing. */
void mysmb_objects_start_vine(struct mysmb_game *game, mysmb_u8 block_slot);
void mysmb_objects_step_vine(struct mysmb_game *game);
/* ROM HandleCoinMetatile/GiveOneCoin. */
void mysmb_objects_collect_coin(struct mysmb_game *game, mysmb_u8 block_low,
                                mysmb_u8 block_row);

#endif

