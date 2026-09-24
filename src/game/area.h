#ifndef MYSMB_GAME_AREA_H
#define MYSMB_GAME_AREA_H

#include "game/game.h"

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
/* ROM VRAM address controls 9-11 select snow and mushroom overrides. */
mysmb_u8 mysmb_area_apply_special_palette(struct mysmb_game *game,
                                          mysmb_u8 address_control);

/* ROM $9c03-$9c2b, pointer tables only; caller owns owner-local data binding. */
mysmb_u8 mysmb_area_load_pointers(struct mysmb_game *game,
                                  const struct mysmb_area_source *source);
/* ROM $9c1c-$9c4a, parse and advance exactly one area header. */
mysmb_u8 mysmb_area_parse_header(struct mysmb_game *game,
                                 const struct mysmb_area_source *source);
/* ROM AreaParserCore terrain pass for the 24 columns prepared before play. */
void mysmb_area_render_initial_terrain(struct mysmb_game *game);
/* ROM AreaParserCore terrain pass when a later circular block page is loaded. */
void mysmb_area_render_terrain_page(struct mysmb_game *game, mysmb_u8 page);
/* ROM $92f7-$9376 AreaParserCore scenery/terrain pass for one physical column.
 * Object-stream processing and VRAM-buffer scheduling remain separate owners. */
mysmb_u8 mysmb_area_render_scenery_terrain_column(struct mysmb_game *game);
/* ROM $92b0-$92e8: execute exactly one AreaParserTaskHandler subtask. */
mysmb_u8 mysmb_area_parser_task_step(struct mysmb_game *game);
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
/* Advance the two-page collision window to the player page. */
void mysmb_area_prepare_player_pages(struct mysmb_game *game, mysmb_u8 player_page);
/* ROM AreaParserCore initial object pass for the two prepared block pages. */
void mysmb_area_render_initial_objects(struct mysmb_game *game);

struct mysmb_area_object {
    mysmb_u8 first;
    mysmb_u8 second;
    mysmb_u8 page;
    mysmb_u8 behind_current_page;
    mysmb_u8 is_page_control;
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u8 dispatch_id;
    mysmb_u8 is_loop_command;
};

/* ROM $9508-$958f stream-selection subset; object decoding remains separate. */
mysmb_u8 mysmb_area_next_object(struct mysmb_game *game,
                                const struct mysmb_area_source *source,
                                struct mysmb_area_object *object);
/* ROM $958f-$961f DecodeAreaData classification before object dispatch. */
void mysmb_area_decode_object(struct mysmb_area_object *object);
mysmb_u8 mysmb_area_emit_next_command(struct mysmb_game *game);
mysmb_u8 mysmb_area_spawn_next_enemy(struct mysmb_game *game,
                                     const struct mysmb_area_source *source);

#endif
