#ifndef MYSMB_GAME_AREA_H
#define MYSMB_GAME_AREA_H

#include "core/game.h"
#include "core/area/block_buffer.h"

/* Shared BrickQBlockMetatiles binding, owned by area/block_metatile.c. */
extern const mysmb_u8 mysmb_brick_question_metatiles[14];

/* ROM $92b0/$93fc, GameMode task 0 before area data parsing. */
void mysmb_area_initialize(struct mysmb_game *game);

struct mysmb_area_source {
    const mysmb_u8 *prg;
    mysmb_u16 prg_size;
};

void mysmb_game_bind_area_source(struct mysmb_game *game,
                                 const mysmb_u8 *prg, mysmb_u16 prg_size);
/* Apply one ROM palette stream through the portable PPU snapshot. */
mysmb_u8 mysmb_area_apply_palette(struct mysmb_game *game, mysmb_u8 area_type);
/* ROM VRAM address controls 8-11 select Bowser, snow, and mushroom palettes. */
mysmb_u8 mysmb_area_apply_special_palette(struct mysmb_game *game,
                                          mysmb_u8 address_control);
/* ROM VRAM address controls 12-18 select the victory and world-select text. */
mysmb_u8 mysmb_area_apply_message(struct mysmb_game *game,
                                  mysmb_u8 address_control);

/* ROM $9c03-$9c21 LoadAreaPointer / GetAreaType / FindAreaPointer. Leaves
 * zero-page data pointers untouched: InitializeGame calls it before
 * InitializeArea clears those locations. */
mysmb_u8 mysmb_area_load_area_pointer(struct mysmb_game *game,
                                      const struct mysmb_area_source *source);
mysmb_u8 mysmb_area_find_area_pointer(const struct mysmb_game *game,
                                       const struct mysmb_area_source *source,
                                       mysmb_u8 *pointer);
mysmb_u8 mysmb_area_get_area_type(struct mysmb_game *game, mysmb_u8 pointer);
/* ROM $9c22-$9cb3 GetAreaDataAddrs, including header decode and advance. */
mysmb_u8 mysmb_area_get_data_addresses(struct mysmb_game *game,
                                       const struct mysmb_area_source *source);
/* Original GetAreaDataAddrs header tail; isolated tests may call this seam. */
mysmb_u8 mysmb_area_parse_header(struct mysmb_game *game,
                                 const struct mysmb_area_source *source);
/* ROM $92f7-$9376 AreaParserCore scenery/terrain pass for one physical column.
 * Object-stream processing and VRAM-buffer scheduling remain separate owners. */
mysmb_u8 mysmb_area_render_scenery_terrain_column(struct mysmb_game *game);
/* ROM $92b0-$92e8: execute exactly one AreaParserTaskHandler subtask. */
mysmb_u8 mysmb_area_parser_task_step(struct mysmb_game *game);
/* ROM $88ae-$8969 RenderAreaGraphics.  Expand the staged thirteen
 * metatiles into the source's one vertical VRAM_Buffer2 command and retain
 * the seven attribute bytes for the immediately following source routine. */
mysmb_u8 mysmb_area_render_graphics(struct mysmb_game *game);
/* ROM $896a-$89a6 RenderAttributeTables.  Append and clear the seven
 * source-ordered attribute commands after RenderAreaGraphics. */
mysmb_u8 mysmb_area_render_attribute_tables(struct mysmb_game *game);
/* ROM $86e6-$86ff: finish one two-column parser set while the screen is off. */
mysmb_u8 mysmb_area_parser_task_control(struct mysmb_game *game);
/* ROM $9508-$958f ProcessAreaData selection/state pass.  This owns the three
 * persistent object slots; family-specific metatile handlers remain separate. */
mysmb_u8 mysmb_area_process_object_state(struct mysmb_game *game);
/* ROM $88ae-$8990: expand one physical metatile page into PPU-visible state. */
void mysmb_area_refresh_background_page(struct mysmb_game *game, mysmb_u8 page);
/* ROM $89c3-$8a15: queue the every-eighth-frame palette-3 update. */
void mysmb_area_step_palette_rotation(struct mysmb_game *game);
/* ROM $8752-$883e: queue the fixed portion of the gameplay top status bar. */
mysmb_u8 mysmb_area_queue_top_status_line(struct mysmb_game *game);
/* ROM $85b4-$85e4/$8ebe-$8ef7: queue initial gameplay status numbers. */
mysmb_u8 mysmb_area_queue_bottom_status_line(struct mysmb_game *game);
/* ROM $8ebe-$8ef7, selector $a4: append the three live timer digits. */
mysmb_u8 mysmb_area_queue_timer_status(struct mysmb_game *game);
/* ROM $8ebe-$8ef7, StatusBarNybbles $02/$13: append the current player's
 * live coin and score digits to an existing NMI command list. */
mysmb_u8 mysmb_area_queue_score_coin_status(struct mysmb_game *game);
/* ROM $8ebe-$8ef7, title-only top-score command at PPU $22f0. */
mysmb_u8 mysmb_area_queue_title_score(struct mysmb_game *game);
/* ROM $8808-$889c: queue one GameText selector (0-4, plus Warp variants). */
mysmb_u8 mysmb_area_queue_game_text(struct mysmb_game *game, mysmb_u8 selector);
/* ROM $85f1-$863c: append the current player's sprite-palette command. */
mysmb_u8 mysmb_area_queue_player_palette(struct mysmb_game *game);
/* Queue the player palette only when PPU-visible state differs from the ROM result. */
mysmb_u8 mysmb_area_sync_player_palette(struct mysmb_game *game);

/* ROM BlockObjMT_Updater -> ReplaceBlockMetatile. */
void mysmb_area_apply_block_replacements(struct mysmb_game *game);
/* Existing ROM $8A61 child; block replacement owns the surrounding loop. */
void mysmb_area_replace_block_metatile(struct mysmb_game *game, mysmb_u8 slot);
/* ROM $8a4d RemoveCoin_Axe / $8a69 DestroyBlockMetatile. */
void mysmb_area_remove_coin_axe(struct mysmb_game *game, mysmb_u8 block_low,
                                 mysmb_u8 vertical_high);
void mysmb_area_destroy_block_metatile(struct mysmb_game *game,
                                       mysmb_u8 control, mysmb_u8 block_low,
                                       mysmb_u8 vertical_high);
/* ROM $8A8F MoveVOffset; takes Y, not the live VRAM offset in RAM. */
void mysmb_area_move_v_offset(struct mysmb_game *game, mysmb_u8 buffer_offset);
/* ROM RemBridge, also called by BridgeCollapse. */
void mysmb_area_rem_bridge(struct mysmb_game *game, mysmb_u8 graphics_offset,
                           mysmb_u8 buffer_offset, mysmb_u8 address_low,
                           mysmb_u8 address_high);

/* Shared original-ROM area-object primitives ($9bac-$9bdc).
 * Length checks return carry: one only when a negative slot is initialized. */
mysmb_u8 mysmb_area_get_large_object_attributes(struct mysmb_game *game,
                                                 mysmb_u8 slot);
mysmb_u8 mysmb_area_check_fixed_length(struct mysmb_game *game,
                                        mysmb_u8 slot, mysmb_u8 length);
mysmb_u8 mysmb_area_check_large_length(struct mysmb_game *game,
                                        mysmb_u8 slot, mysmb_u8 *length);
mysmb_u8 mysmb_area_object_x_position(const struct mysmb_game *game);
mysmb_u8 mysmb_area_object_y_position(const struct mysmb_game *game);

/* ROM $9716 KillEnemies; shared by area warp and player flagpole. */
void mysmb_area_kill_enemies(struct mysmb_game *game, mysmb_u8 id);

#endif
