#ifndef MYSMB_GAME_OAM_OAM_H
#define MYSMB_GAME_OAM_OAM_H

#include "game/game.h"

/* ROM-owned OAM writers.  These consume completed game state and write only
 * the canonical $0200 OAM backing store plus ROM-defined relative/offscreen
 * work bytes.  Motion, collision and mode decisions remain outside this API. */
/* ROM RelativeBlockPosition and GetBlockOffscreenBits. */
void mysmb_oam_relative_player_position(struct mysmb_game *game);
void mysmb_oam_draw_sprite_object(struct mysmb_game *game,
                                  mysmb_u8 *graphics_index,
                                  mysmb_u8 *oam_offset);
void mysmb_oam_draw_one_sprite_row(struct mysmb_game *game,
                                    mysmb_u8 right_tile,
                                    mysmb_u8 *graphics_index,
                                    mysmb_u8 *oam_offset);
void mysmb_oam_sprite_object_offscreen_check(struct mysmb_game *game,
                                              mysmb_u8 oam_offset);
void mysmb_oam_relative_bubble_position(struct mysmb_game *game, mysmb_u8 slot);
/* ROM GetXOffscreenBits.  source_offset is the source X register value;
 * the routine preserves its $04-$07 scratch side effects as well as A. */
mysmb_u8 mysmb_oam_get_x_offscreen_bits(struct mysmb_game *game,
                                       mysmb_u8 source_offset,
                                       mysmb_u8 page, mysmb_u8 x);
/* ROM GetOffScreenBitsSet: common actor source offset and fixed result cell. */
void mysmb_oam_get_offscreen_bits_set(struct mysmb_game *game,
                                     mysmb_u8 source_offset,
                                     mysmb_u8 destination_offset);
void mysmb_oam_get_player_offscreen_bits(struct mysmb_game *game);
void mysmb_oam_get_bubble_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot);
/* ROM ProcessPlayerAction through ExAnimC; returns the graphics table offset. */
mysmb_u8 mysmb_oam_process_player_action(struct mysmb_game *game);
/* ROM HandleChangeSize through ShrPlF; returns graphics table offset. */
mysmb_u8 mysmb_oam_handle_change_size(struct mysmb_game *game);
/* ROM ChkForPlayerAttrib through C_S_IGAtt. */
void mysmb_oam_check_player_attributes(struct mysmb_game *game);
void mysmb_oam_render_player(struct mysmb_game *game);
void mysmb_oam_relative_fireball_position(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_oam_relative_enemy_position(struct mysmb_game *game, mysmb_u8 slot);
/* ROM GetEnemyOffscreenBits, including source $00 and $04-$07 writes. */
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_oam_get_fireball_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_oam_draw_player(struct mysmb_game *game);
void mysmb_oam_draw_intermediate_player(struct mysmb_game *game);
void mysmb_oam_draw_fireball(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_oam_draw_fireball_explosion(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_oam_relative_block_position(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_oam_get_block_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot);
/* ROM RelativeMiscPosition and GetMiscOffscreenBits. */
void mysmb_oam_relative_misc_position(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_oam_get_misc_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_power_up(struct mysmb_game *game);
void mysmb_objects_draw_bouncing_block(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_brick_chunks(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_goombas_mask(struct mysmb_game *game, mysmb_u8 suppress_mask);
void mysmb_objects_draw_goombas(struct mysmb_game *game);
void mysmb_objects_draw_goomba(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_bullet_bill(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_piranha(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_cheep_cheep(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_bloober(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_aquatic_enemy(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_podoboo(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_special_enemy(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_koopa_buzzy(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_spiny(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_hammer_bro(struct mysmb_game *game, mysmb_u8 slot);
mysmb_u8 mysmb_objects_draw_normal_enemy_graphics(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_oam_draw_enemy_object_row(struct mysmb_game *game,
    mysmb_u8 *oam_offset, mysmb_u8 *graphics_index);
mysmb_u8 mysmb_oam_move_column_offscreen(struct mysmb_game *game, mysmb_u8 oam);
void mysmb_oam_move_enemy_column_offscreen(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 column);
void mysmb_oam_move_enemy_row_offscreen(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 row);
void mysmb_objects_draw_retainer(struct mysmb_game *game, mysmb_u8 slot);
/* Existing retainer graphics child; caller owns relative/offscreen work. */
/* Existing EnemyGfxHandler jumpspring branch; actor prepares relative/bits. */

void mysmb_objects_draw_small_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_large_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_bowsers(struct mysmb_game *game);
/* Existing EnemyGfxHandler Bowser rows, selected by BowserGfxFlag. */
void mysmb_objects_draw_bowser_flame(struct mysmb_game *game, mysmb_u8 slot);
/* DrawExplosion_Fireworks child takes source A and Y explicitly. */
void mysmb_oam_draw_fireworks_explosion(struct mysmb_game *game,
                                       mysmb_u8 frame, mysmb_u8 oam);
void mysmb_objects_draw_hammer(struct mysmb_game *game, mysmb_u8 slot);
/* ROM ProcHammerObj prepares relative coordinates and offscreen bits before
 * GetMiscBoundBox; the caller owns the intervening shared collision-box write. */
void mysmb_objects_prepare_hammer(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_objects_draw_vine(struct mysmb_game *game, mysmb_u8 vine_index);
/* ROM SixSpriteStacker; caller owns its saved OAM offset and return state. */
void mysmb_oam_stack_six_sprite_data(struct mysmb_game *game,
                                     mysmb_u8 value, mysmb_u8 oam);
/* ROM $e5b3 MoveSixSpritesOffscreen through $e5c7 ExitDumpSpr. */
void mysmb_oam_move_six_sprites_offscreen(struct mysmb_game *game,
                                          mysmb_u8 oam);
void mysmb_oam_dump_six_sprites(struct mysmb_game *game,
                                 mysmb_u8 value, mysmb_u8 oam);
void mysmb_oam_dump_four_sprites(struct mysmb_game *game,
                                  mysmb_u8 value, mysmb_u8 oam);
void mysmb_oam_dump_three_sprites(struct mysmb_game *game,
                                   mysmb_u8 value, mysmb_u8 oam);
void mysmb_oam_dump_two_sprites(struct mysmb_game *game,
                                 mysmb_u8 value, mysmb_u8 oam);

#endif
