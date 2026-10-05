#ifndef MYSMB_GAME_OBJECTS_H
#define MYSMB_GAME_OBJECTS_H

#include "core/game.h"

/* ROM $BA89-$BB37: hammer allocation and actor caller chain. */
extern const mysmb_u8 mysmb_hammer_enemy_offsets[9];
extern const mysmb_u8 mysmb_hammer_x_speeds[2];
mysmb_u8 mysmb_objects_spawn_hammer(struct mysmb_game *game);
void mysmb_objects_step_hammer(struct mysmb_game *game, mysmb_u8 slot);
/* Existing children exposed without claiming their internal equivalence. */
void mysmb_objects_check_hammer_collision(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_get_hammer_bounding_box(struct mysmb_game *game, mysmb_u8 slot);

/* ROM $bed4 BlockObjMT_Updater. */
/* ROM $be70 BlockObjectsCore, bounded to the bouncing-block state. */
void mysmb_objects_step_block(struct mysmb_game *game, mysmb_u8 slot);
/* ROM $bced-$bd9b PlayerHeadCollision through BumpBlock, for matched blocks. */
mysmb_u8 mysmb_objects_start_head_bump(struct mysmb_game *game,
                                       mysmb_u8 metatile,
                                       mysmb_u8 block_low,
                                       mysmb_u8 block_row);
/* ROM $bb51-$bbd0 jumping-coin misc-object route. */
mysmb_u8 mysmb_objects_find_empty_misc_slot(struct mysmb_game *game, mysmb_u8 *carry);
void mysmb_objects_coin_block(struct mysmb_game *game, mysmb_u8 block_slot, mysmb_u8 carry);
void mysmb_objects_setup_jump_coin(struct mysmb_game *game, mysmb_u8 block_slot);
/* Existing score child; original caller owns CoinTallyFor1Ups. */
void mysmb_objects_give_one_coin(struct mysmb_game *game);
void mysmb_objects_step_misc(struct mysmb_game *game);
/* Existing misc children exposed without new child equivalence credit. */
void mysmb_objects_get_coin_bounding_box(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_jump_coin(struct mysmb_game *game, mysmb_u8 slot);
/* ROM $BC49 SetupPowerUp; the caller supplies PowerUpType in RAM. */
void mysmb_objects_start_power_up(struct mysmb_game *game, mysmb_u8 block_slot);
/* ROM $BC60 PwrUpJmp: initialize the fixed slot-five tail only. */
void mysmb_objects_initialize_power_up(struct mysmb_game *game);
void mysmb_objects_step_power_up(struct mysmb_game *game);
/* RunNormalEnemies for one ObjectOffset; GameEngine uses this with stream parsing. */
/* ROM EnemyToBGCollisionDet through DoEnemySideCheck. */
void mysmb_objects_step_normal_enemy_terrain(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_normal_enemy(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_enemy_background_current(struct mysmb_game *game, mysmb_u8 slot);
/* Shared EnemyJump entry and legacy child seams used by enemy/background.c.
 * Exposing a child boundary does not certify its internal ROM equivalence. */
void mysmb_objects_step_enemy_jump_terrain(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_check_enemy_side(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_bump_enemy(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_hammer_terrain(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_is_solid_terrain(mysmb_u8 tile);
/* ROM $D853 PlayerEnemyCollision; consumes prepared boxes. The final
 * parameter is retained only for existing caller ABI compatibility. */
void mysmb_objects_player_enemy_current(struct mysmb_game *game, mysmb_u8 slot,
                                        mysmb_u8 preserve_collision_boxes);
void mysmb_objects_step_normal_enemies(struct mysmb_game *game);
/* ROM RunRetainerObj through EnemyGfxHandler. */
void mysmb_objects_draw_retainer(struct mysmb_game *game, mysmb_u8 slot);
/* ROM GetEnemyBoundBox / GetMaskedOffScrBits. */
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_get_enemy_x_offscreen_bits(const struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *game, mysmb_u8 slot);
/* ROM OffscreenBoundsCheck / EraseEnemyObject. */
void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_erase_enemy(struct mysmb_game *game, mysmb_u8 slot);
/* Legacy cannon/test adapter to the same PlayerEnemyCollision owner. */
mysmb_u8 mysmb_objects_check_normal_enemy_collision(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 preserve_collision_boxes);
/* ROM EnemiesCollision/ProcEnemyCollisions for the current ObjectOffset. */
void mysmb_objects_step_enemy_collisions_current(struct mysmb_game *game,
                                                 mysmb_u8 slot);
/* ROM $aa0f-$aa4c InitBulletBill/BulletBillHandler and its OAM output. */
void mysmb_objects_step_bullet_bills(struct mysmb_game *game);
/* ROM $aa9f-$aae8 InitPiranhaPlant/MovePiranhaPlant, sans rendering. */
void mysmb_objects_step_piranha_plants(struct mysmb_game *game);
/* ROM $B8BA JumpspringHandler for object $32; shared actor state owner. */
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
/* ROM InitShortFirebar/InitLongFirebar and ProcFirebar, sans drawing. */
void mysmb_objects_step_firebars(struct mysmb_game *game);
/* ROM RunLargePlatform through RunSmallPlatform, excluding OAM ropes. */
void mysmb_objects_step_platforms(struct mysmb_game *game);
/* ROM InitBowser/RunBowser, excluding OAM output. */
void mysmb_objects_step_bowsers(struct mysmb_game *game);
/* ROM $d8aa-$d91d BridgeCollapse, including its VRAM_Buffer1 metatile writes. */
mysmb_u8 mysmb_objects_step_bridge_collapse(struct mysmb_game *game);
/* ROM ProcBowserFlame, excluding OAM output. */
void mysmb_objects_step_bowser_flames(struct mysmb_game *game);
/* ROM RunFireworks and RunStarFlagObj. */
void mysmb_objects_step_fireworks(struct mysmb_game *game);
void mysmb_objects_step_star_flags(struct mysmb_game *game);
/* ROM FlagpoleObject, FlagpoleRoutine, and FlagpoleGfxHandler. */
void mysmb_objects_start_flagpole(struct mysmb_game *game, mysmb_u8 page,
                                  mysmb_u8 x);
void mysmb_objects_step_flagpole(struct mysmb_game *game);
void mysmb_objects_draw_flagpole_graphics(struct mysmb_game *game);
/* ROM ProcHammerBro through MoveHammerBroXDir, before hammer misc objects. */
void mysmb_objects_step_hammer_bros(struct mysmb_game *game);
void mysmb_objects_check_hazard_enemy_collision(struct mysmb_game *game);
/* ROM $D92C InjurePlayer, guarded by InjuryTimer; historical API name. */
void mysmb_objects_force_injury(struct mysmb_game *game);
void mysmb_objects_check_bullet_bill_stomp(struct mysmb_game *game);
void mysmb_objects_check_bloober_stomp(struct mysmb_game *game);
/* Legacy aggregate test adapter for Lakitu (ID $11). */
void mysmb_objects_check_lakitu_stomp(struct mysmb_game *game);
/* Legacy aggregate test adapter for Hammer Bro (ID $05). */
void mysmb_objects_check_hammer_bro_stomp(struct mysmb_game *game);
/* Legacy aggregate test adapter for paratroopas, IDs $0e-$10. */
void mysmb_objects_check_paratroopa_stomp(struct mysmb_game *game);
/* Legacy slot-five test adapter to PlayerEnemyCollision. */
void mysmb_objects_check_power_up_collision(struct mysmb_game *game);
/* ROM $D800 HandlePowerUpCollision, with original enemy-slot input. */
void mysmb_objects_collect_power_up(struct mysmb_game *game, mysmb_u8 slot);
/* ROM $D948 SetPRout; caller passes source A/Y. */
void mysmb_objects_set_player_routine(struct mysmb_game *game,
                                       mysmb_u8 routine, mysmb_u8 state);
/* ROM $DA11 SetupFloateyNumber consumes prepared $03ae. */
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *game,
                                             mysmb_u8 slot, mysmb_u8 control);
/* ROM FloateyNumbersRoutine, excluding OAM output. */
void mysmb_objects_step_floatey_number(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_step_floatey_numbers(struct mysmb_game *game);
/* ROM $B91E Setup_Vine and $B949 VineHeightData. */
extern const mysmb_u8 mysmb_vine_height_data[2];
void mysmb_objects_start_vine(struct mysmb_game *game, mysmb_u8 enemy_slot,
                              mysmb_u8 block_slot);
/* ROM $9180-$918b ChkOverR's InitBlock_XY_Pos/Setup_Vine call sequence. */
void mysmb_objects_start_entrance_vine(struct mysmb_game *game);
/* ROM $B94B VineObjectHandler; the actor owns its slot-five gate. */
void mysmb_objects_step_vine(struct mysmb_game *game, mysmb_u8 enemy_slot);
/* ROM HandleCoinMetatile/GiveOneCoin. */
void mysmb_objects_collect_coin(struct mysmb_game *game, mysmb_u8 block_low,
                                mysmb_u8 block_row);
/* ROM $D931 ForceInjury with source A, bypassing the InjuryTimer guard. */
void mysmb_objects_force_injury_entry(struct mysmb_game *game, mysmb_u8 a);
/* ROM $D895, $D969, $DA05 shared contact-chain entries. */
void mysmb_objects_handle_player_enemy_contact(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 id);
void mysmb_objects_enemy_stomped(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_enemy_face_player(struct mysmb_game *game, mysmb_u8 slot);
/* ROM $DB1C EnemyTurnAround; shared enemy-pair collision owner. */
void mysmb_objects_turn_enemy(struct mysmb_game *game, mysmb_u8 slot);
extern const mysmb_u8 mysmb_residual_x_speeds[2];

#endif

