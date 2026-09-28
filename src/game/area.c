#include "game/area.h"
#include "game/enemy/init.h"
#include "game/objects.h"
#include "game/status.h"

enum {
    MYSMB_AREA_CANNON_OFFSET = 0x046aU,
    MYSMB_AREA_CANNON_PAGE = 0x046bU,
    MYSMB_AREA_CANNON_X = 0x0471U,
    MYSMB_AREA_CANNON_Y = 0x0477U,
    MYSMB_AREA_OBJECT_OFFSET = 0x0008U,
    MYSMB_AREA_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_AREA_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_AREA_SCREEN_LEFT_X = 0x071cU,
    MYSMB_AREA_SCREEN_RIGHT_X = 0x071dU,
    MYSMB_AREA_COLUMN_SETS = 0x071eU,
    MYSMB_AREA_NT_HIGH = 0x0720U,
    MYSMB_AREA_NT_LOW = 0x0721U,
    MYSMB_AREA_CURRENT_PAGE = 0x0725U,
    MYSMB_AREA_BACKLOADING = 0x0728U,
    MYSMB_AREA_OBJECT_LENGTH = 0x0730U,
    MYSMB_AREA_SCROLL_LOCK = 0x0723U,
    MYSMB_AREA_SCROLL_X = 0x073fU,
    MYSMB_AREA_SCROLL_Y = 0x0740U,
    MYSMB_AREA_TIMERS = 0x0780U,
    MYSMB_AREA_DISABLE_SCREEN = 0x0774U,
    MYSMB_AREA_SCREEN_ROUTINE_TASK = 0x073cU,
    MYSMB_AREA_OPER_MODE_TASK = 0x0772U,
    MYSMB_AREA_BLOCK_COLUMN = 0x06a0U,
    MYSMB_AREA_METATILE_LOW = 0x0b08U,
    MYSMB_AREA_METATILE_HIGH = 0x0b0cU,
    MYSMB_AREA_WATER_PALETTE = 0x0ca4U,
    MYSMB_AREA_GROUND_PALETTE = 0x0cc8U,
    MYSMB_AREA_UNDERGROUND_PALETTE = 0x0cecU,
    MYSMB_AREA_CASTLE_PALETTE = 0x0d10U,
    MYSMB_AREA_DAY_SNOW_PALETTE = 0x0d34U,
    MYSMB_AREA_NIGHT_SNOW_PALETTE = 0x0d3cU,
    MYSMB_AREA_MUSHROOM_PALETTE = 0x0d44U,
    MYSMB_AREA_BOWSER_PALETTE = 0x0d4cU,
    MYSMB_AREA_MARIO_THANKS = 0x0d54U,
    MYSMB_AREA_LUIGI_THANKS = 0x0d68U,
    MYSMB_AREA_RETAINER_SAVED = 0x0d7cU,
    MYSMB_AREA_PRINCESS_SAVED1 = 0x0da8U,
    MYSMB_AREA_PRINCESS_SAVED2 = 0x0dbfU,
    MYSMB_AREA_WORLD_SELECT1 = 0x0ddeU,
    MYSMB_AREA_WORLD_SELECT2 = 0x0defU,
    MYSMB_AREA_COLOR_ROTATE_PALETTE = 0x09c3U,
    MYSMB_AREA_PALETTE3_DATA = 0x09d1U,
    MYSMB_AREA_GAME_TEXT = 0x0752U,
    MYSMB_AREA_ALT_ENTRANCE = 0x0752U,
    MYSMB_AREA_HALFWAY_PAGE = 0x075bU,
    MYSMB_AREA_GAME_TEXT_OFFSETS = 0x07feU,
    MYSMB_AREA_LUIGI_NAME = 0x07edU,
    MYSMB_AREA_WARP_ZONE_NUMBERS = 0x07f2U,
    MYSMB_AREA_BACKGROUND_COLORS = 0x05cfU,
    MYSMB_AREA_PLAYER_COLORS = 0x05d7U
};

enum {
    MYSMB_AREA_POINTER = 0x0750U,
    MYSMB_AREA_ENTRANCE_PAGE = 0x0751U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_AREA_LOW_OFFSET = 0x074fU,
    MYSMB_AREA_DATA_LOW = 0x00e7U,
    MYSMB_AREA_DATA_HIGH = 0x00e8U,
    MYSMB_ENEMY_DATA_LOW = 0x00e9U,
    MYSMB_ENEMY_DATA_HIGH = 0x00eaU,
    MYSMB_WORLD_NUMBER = 0x075fU,
    MYSMB_AREA_NUMBER = 0x0760U,
    MYSMB_AREA_PLAYER_ENTRANCE = 0x0710U,
    MYSMB_AREA_MUSIC_QUEUE = 0x00fbU
};

enum {
    MYSMB_AREA_ENTRANCE = 0x0710U,
    MYSMB_AREA_TIMER_SETTING = 0x0715U,
    MYSMB_AREA_TERRAIN = 0x0727U,
    MYSMB_AREA_STYLE = 0x0733U,
    MYSMB_AREA_FOREGROUND = 0x0741U,
    MYSMB_AREA_BACKGROUND = 0x0742U,
    MYSMB_AREA_CLOUD_OVERRIDE = 0x0743U,
    MYSMB_AREA_BACKGROUND_COLOR = 0x0744U,
    MYSMB_AREA_LOOP_COMMAND = 0x0745U,
    MYSMB_AREA_COLOR_ROTATE_OFFSET = 0x06d4U,
    MYSMB_AREA_FRAME_COUNTER = 0x0009U,
    MYSMB_AREA_VRAM_BUFFER1_OFFSET = 0x0300U,
    MYSMB_AREA_VRAM_BUFFER1 = 0x0301U
    ,MYSMB_AREA_CURRENT_PLAYER = 0x0753U
    ,MYSMB_AREA_WORLD_NUMBER = 0x075fU
    ,MYSMB_AREA_LEVEL_NUMBER = 0x075cU
    ,MYSMB_AREA_DISPLAY_DIGITS = 0x07d7U
    ,MYSMB_AREA_GAME_TIMER_DISPLAY = 0x07f8U
};

enum {
    /* NROM PRG offsets for ROM $92f7-$9507 AreaParserCore data. */
    MYSMB_AREA_BACKGROUND_SCENE_OFFSETS = 0x12f7U,
    MYSMB_AREA_BACKGROUND_SCENE_DATA = 0x12faU,
    MYSMB_AREA_BACKGROUND_METATILES = 0x138aU,
    MYSMB_AREA_FOREGROUND_SCENE_OFFSETS = 0x13aeU,
    MYSMB_AREA_FOREGROUND_SCENE_DATA = 0x13b1U,
    MYSMB_AREA_TERRAIN_METATILES = 0x13d8U,
    MYSMB_AREA_TERRAIN_RENDER_BITS = 0x13dcU,
    MYSMB_AREA_BLOCK_BUFFER_LOW_BOUNDS = 0x1504U,
    MYSMB_AREA_CURRENT_COLUMN = 0x0726U,
    MYSMB_AREA_PARSER_TASK = 0x071fU,
    MYSMB_AREA_HIDDEN_1UP_FLAG = 0x075dU,
    MYSMB_AREA_METATILE_BUFFER = 0x06a1U,
    MYSMB_AREA_ATTRIBUTE_BUFFER = 0x03f9U,
    MYSMB_AREA_VRAM_BUFFER2_OFFSET = 0x0340U,
    MYSMB_AREA_VRAM_BUFFER2 = 0x0341U,
    MYSMB_AREA_VRAM_ADDRESS_CONTROL = 0x0773U
};

enum {
    MYSMB_AREA_PARSER_BEHIND = 0x0729U,
    MYSMB_AREA_OBJECT_PAGE = 0x072aU,
    MYSMB_AREA_OBJECT_PAGE_SELECT = 0x072bU,
    MYSMB_AREA_DATA_OFFSET = 0x072cU,
    MYSMB_AREA_OBJECT_OFFSET_BUFFER = 0x072dU,
    MYSMB_AREA_STAIRCASE_CONTROL = 0x0734U,
    MYSMB_AREA_OBJECT_HEIGHT = 0x0735U,
    MYSMB_AREA_MUSHROOM_HALF_LENGTH = 0x0736U
    ,MYSMB_AREA_WARP_ZONE_CONTROL = 0x06d6U
    ,MYSMB_AREA_ENEMY_FRENZY_QUEUE = 0x06cdU
};

enum {
    MYSMB_ENEMY_DATA_OFFSET = 0x0739U,
    MYSMB_ENEMY_OBJECT_PAGE = 0x073aU,
    MYSMB_ENEMY_OBJECT_PAGE_SELECT = 0x073bU,
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_MOVING_DIRECTION = 0x0046U,
    MYSMB_ENEMY_X_SPEED = 0x0058U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_Y_SPEED = 0x00a0U,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_X_FORCE = 0x0401U,
    MYSMB_ENEMY_Y_DUMMY = 0x0417U,
    MYSMB_ENEMY_Y_FORCE = 0x0434U,
    MYSMB_ENEMY_BOUND_BOX = 0x049aU,
    MYSMB_FIREBAR_SPIN_SPEED = 0x0388U,
    MYSMB_FIREBAR_SPIN_DIRECTION = 0x0034U,
    MYSMB_BOWSER_BODY_CONTROLS = 0x0363U,
    MYSMB_BOWSER_FEET_TIMER = 0x0364U,
    MYSMB_BOWSER_MOVE_SPEED = 0x0365U,
    MYSMB_BOWSER_ORIGIN_X = 0x0366U,
    MYSMB_BOWSER_FLAME_TIMER = 0x0367U,
    MYSMB_BOWSER_BREATH_TIMER = 0x0790U,
    MYSMB_BOWSER_FRONT_SLOT = 0x0368U,
    MYSMB_BOWSER_HIT_POINTS = 0x0483U,
    MYSMB_ENEMY_INTERVAL_TIMER = 0x078aU,
    MYSMB_BALANCE_PLATFORM_ALIGNMENT = 0x03a0U,
    MYSMB_PLATFORM_COLLISION_FLAG = 0x03a2U,
    MYSMB_PLATFORM_TOP_Y = 0x0401U,
    MYSMB_PLATFORM_CENTER_Y = 0x0058U,
    MYSMB_PRIMARY_HARD = 0x076aU,
    MYSMB_SECONDARY_HARD = 0x06ccU,
    MYSMB_ENEMY_FRENZY_BUFFER = 0x06cbU
};

static void mysmb_area_apply_parser_object(struct mysmb_game *game,
                                           mysmb_u8 slot,
                                           mysmb_u8 first,
                                           mysmb_u8 second);
static void mysmb_area_render_under_part(struct mysmb_game *game,
                                         mysmb_u8 row,
                                         mysmb_u8 height,
                                         mysmb_u8 metatile);
static void mysmb_area_col_obj(struct mysmb_game *game, mysmb_u8 row,
                               mysmb_u8 metatile);
static void mysmb_area_chain_obj(struct mysmb_game *game);
static void mysmb_area_castle_bridge_obj(struct mysmb_game *game,
                                         mysmb_u8 slot);
static void mysmb_area_axe_obj(struct mysmb_game *game);
static void mysmb_area_empty_block(struct mysmb_game *game);

static mysmb_u8 mysmb_area_find_empty_enemy_slot(const struct mysmb_game *game,
                                                  mysmb_u8 *slot)
{
    *slot = 0U;
    while (*slot < 5U && game->ram[MYSMB_ENEMY_FLAG + *slot] != 0U) (*slot)++;
    return *slot < 5U ? 1U : 0U;
}

/* Translation of ROM InitializeArea within the $92b0 area task route.
 * Header and stream reads are deliberately owned by the following T3 part. */
void mysmb_area_initialize(struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u8 start_page;
    struct mysmb_area_source source;

    mysmb_game_initialize_memory(game, 0x4bU);
    for (index = 0U; index < 0x22U; ++index) {
        game->ram[(mysmb_u16)(MYSMB_AREA_TIMERS + index)] = 0U;
    }
    /* ROM InitializeArea selects the saved halfway page unless an alternate
     * entrance requests the stream's saved entrance page. */
    start_page = game->ram[MYSMB_AREA_HALFWAY_PAGE];
    if (game->ram[MYSMB_AREA_ALT_ENTRANCE] != 0U) {
        start_page = game->ram[MYSMB_AREA_ENTRANCE_PAGE];
    }
    game->ram[MYSMB_AREA_SCREEN_LEFT_PAGE] = start_page;
    game->ram[MYSMB_AREA_CURRENT_PAGE] = start_page;
    game->ram[MYSMB_AREA_BACKLOADING] = start_page;
    game->ram[MYSMB_AREA_SCREEN_LEFT_X] = 0U;
    /* GetScreenPosition: left X plus $ff, and the resulting carry advances
     * the right page.  A fresh page therefore has right edge $xxff. */
    game->ram[MYSMB_AREA_SCREEN_RIGHT_X] =
        (mysmb_u8)(game->ram[MYSMB_AREA_SCREEN_LEFT_X] + 0xffU);
    game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] = start_page;
    if (game->ram[MYSMB_AREA_SCREEN_RIGHT_X] <
        game->ram[MYSMB_AREA_SCREEN_LEFT_X]) {
        game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE]++;
    }
    game->ram[MYSMB_AREA_NT_HIGH] = (start_page & 1U) != 0U ? 0x24U : 0x20U;
    game->ram[MYSMB_AREA_NT_LOW] = 0x80U;
    /* SetInitNTHigh shifts the parity already selected by StartPage. */
    game->ram[MYSMB_AREA_BLOCK_COLUMN] = (mysmb_u8)((start_page & 1U) << 4U);
    game->ram[MYSMB_AREA_OBJECT_LENGTH] = 0xffU;
    game->ram[(mysmb_u16)(MYSMB_AREA_OBJECT_LENGTH + 1U)] = 0xffU;
    game->ram[(mysmb_u16)(MYSMB_AREA_OBJECT_LENGTH + 2U)] = 0xffU;
    game->ram[MYSMB_AREA_COLUMN_SETS] = 0x0bU;
    /* InitializeArea calls the complete GetAreaDataAddrs before the
     * hard-mode/halfway overrides and final task advance. */
    if (game->area_prg != 0) {
        source.prg = game->area_prg;
        source.prg_size = game->area_prg_size;
        (void)mysmb_area_get_data_addresses(game, &source);
    }
    game->ram[MYSMB_AREA_SCROLL_X] = 0U;
    game->ram[MYSMB_AREA_SCROLL_Y] = 0U;
    if (game->ram[MYSMB_PRIMARY_HARD] != 0U ||
        game->ram[MYSMB_WORLD_NUMBER] > 4U ||
        (game->ram[MYSMB_WORLD_NUMBER] == 4U &&
         game->ram[MYSMB_AREA_LEVEL_NUMBER] >= 2U)) {
        game->ram[MYSMB_SECONDARY_HARD]++;
    }
    if (game->ram[MYSMB_AREA_HALFWAY_PAGE] != 0U) {
        game->ram[MYSMB_AREA_PLAYER_ENTRANCE] = 2U;
    }
    game->ram[MYSMB_AREA_MUSIC_QUEUE] = 0x80U;
    game->ram[MYSMB_AREA_DISABLE_SCREEN] = 1U;
    game->ram[MYSMB_AREA_OPER_MODE_TASK]++;
}

void mysmb_game_bind_area_source(struct mysmb_game *game,
                                 const mysmb_u8 *prg, mysmb_u16 prg_size)
{
    game->area_prg = prg;
    game->area_prg_size = prg_size;
}

/* ROM $88ae-$8990 RenderAreaGraphics/RenderAttributeTables.  The collision
 * block buffer stores a 16-by-13 metatile page; the original graphics tables
 * at $8b08 select four CHR tile numbers for each encoded metatile. */
void mysmb_area_refresh_background_page(struct mysmb_game *game,
                                        mysmb_u8 page)
{
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u8 metatile;
    mysmb_u8 palette;
    mysmb_u8 table;
    mysmb_u8 attribute_shift;
    mysmb_u16 block_address;
    mysmb_u16 graphics_address;
    mysmb_u16 tile_offset;
    mysmb_u16 attribute_offset;

    if (game->area_prg == 0 || game->area_prg_size <= MYSMB_AREA_METATILE_HIGH + 3U)
        return;
    table = (mysmb_u8)(page & 1U);
    for (column = 0U; column < 16U; ++column) {
        for (row = 0U; row < 13U; ++row) {
            block_address = (mysmb_u16)((table != 0U ? 0x05d0U : 0x0500U) +
                column + (mysmb_u16)row * 16U);
            metatile = game->ram[block_address];
            palette = (mysmb_u8)(metatile >> 6U);
            graphics_address = (mysmb_u16)(game->area_prg[
                MYSMB_AREA_METATILE_LOW + palette] |
                ((mysmb_u16)game->area_prg[MYSMB_AREA_METATILE_HIGH + palette] << 8U));
            if (graphics_address < 0x8000U) continue;
            graphics_address = (mysmb_u16)(graphics_address - 0x8000U);
            tile_offset = (mysmb_u16)(graphics_address +
                (mysmb_u16)(metatile & 0x3fU) * 4U);
            if ((mysmb_u16)(tile_offset + 3U) >= game->area_prg_size) continue;
            tile_offset = (mysmb_u16)(4U * 32U + (mysmb_u16)row * 2U * 32U +
                (mysmb_u16)column * 2U);
            game->name_table[table][tile_offset] = game->area_prg[(mysmb_u16)(graphics_address +
                (mysmb_u16)(metatile & 0x3fU) * 4U)];
            game->name_table[table][(mysmb_u16)(tile_offset + 1U)] = game->area_prg[
                (mysmb_u16)(graphics_address + (mysmb_u16)(metatile & 0x3fU) * 4U + 2U)];
            game->name_table[table][(mysmb_u16)(tile_offset + 32U)] = game->area_prg[
                (mysmb_u16)(graphics_address + (mysmb_u16)(metatile & 0x3fU) * 4U + 1U)];
            game->name_table[table][(mysmb_u16)(tile_offset + 33U)] = game->area_prg[
                (mysmb_u16)(graphics_address + (mysmb_u16)(metatile & 0x3fU) * 4U + 3U)];
            attribute_offset = (mysmb_u16)(0x03c0U + ((row >> 1U) + 1U) * 8U +
                (column >> 1U));
            attribute_shift = (mysmb_u8)(((row & 1U) << 2U) | ((column & 1U) << 1U));
            game->name_table[table][attribute_offset] = (mysmb_u8)(
                (game->name_table[table][attribute_offset] &
                (mysmb_u8)~(0x03U << attribute_shift)) | (palette << attribute_shift));
        }
    }
}

/* Translation of ROM $89d9-$8a15 (ColorRotation).  The original leaves the
 * completed command in VRAM_Buffer1 for the following NMI UpdateScreen;
 * this function therefore queues data and does not change the palette. */
void mysmb_area_step_palette_rotation(struct mysmb_game *game)
{
    mysmb_u8 buffer_offset;
    mysmb_u8 palette_offset;
    mysmb_u8 rotation_offset;
    mysmb_u8 area_type;
    mysmb_u8 source_offset;
    mysmb_u8 counter;

    if ((game->ram[MYSMB_AREA_FRAME_COUNTER] & 7U) != 0U) return;
    buffer_offset = game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET];
    if (buffer_offset >= 0x31U || game->area_prg == 0) return;
    area_type = game->ram[MYSMB_AREA_TYPE];
    if (area_type >= 4U || game->area_prg_size <= MYSMB_AREA_PALETTE3_DATA +
        (mysmb_u16)area_type * 4U + 3U) return;
    rotation_offset = game->ram[MYSMB_AREA_COLOR_ROTATE_OFFSET];
    if (rotation_offset >= 6U || game->area_prg_size <=
        MYSMB_AREA_COLOR_ROTATE_PALETTE + rotation_offset) return;
    /* ROM GetBlankPal copies the complete eight-byte command from $89c9. */
    source_offset = 0U;
    do {
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset)] =
            game->area_prg[MYSMB_AREA_COLOR_ROTATE_PALETTE + 6U + source_offset];
        buffer_offset++;
        source_offset++;
    } while (source_offset != 8U);

    /* ROM GetAreaPal then overwrites positions +3 through +6.  X advances
     * while each store remains indexed by the original buffer position. */
    buffer_offset = game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET];
    palette_offset = (mysmb_u8)(area_type * 4U);
    counter = 3U;
    do {
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 3U)] =
            game->area_prg[MYSMB_AREA_PALETTE3_DATA + palette_offset];
        palette_offset++;
        buffer_offset++;
        counter--;
    } while ((counter & 0x80U) == 0U);
    buffer_offset = game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET];
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 4U)] =
        game->area_prg[MYSMB_AREA_COLOR_ROTATE_PALETTE + rotation_offset];
    game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] =
        (mysmb_u8)(buffer_offset + 7U);
    rotation_offset++;
    game->ram[MYSMB_AREA_COLOR_ROTATE_OFFSET] =
        rotation_offset < 6U ? rotation_offset : 0U;
}

/* Translation of ROM $8752-$882e (TopStatusBarLine/WriteGameText).  The
 * status-text stream is ROM-owned data but remains local through area_prg.
 * Score and coin placeholders retain their source tiles until their number
 * writers are translated; this routine owns only the fixed command stream. */
mysmb_u8 mysmb_area_queue_top_status_line(struct mysmb_game *game)
{
    /* WriteTopStatusLine loads selector zero and enters WriteGameText; retain
     * its shared player-name branch instead of duplicating only the data loop. */
    return mysmb_area_queue_game_text(game, 0U);
}

/* StatusBarData through NoTopSc are owned by status.c; these retained area
 * entry points preserve their source callers without duplicating the chain. */
mysmb_u8 mysmb_area_queue_bottom_status_line(struct mysmb_game *game)
{ return mysmb_status_queue_bottom_line(game); }

mysmb_u8 mysmb_area_queue_timer_status(struct mysmb_game *game)
{ return mysmb_status_queue_timer(game); }

mysmb_u8 mysmb_area_queue_score_coin_status(struct mysmb_game *game)
{ return mysmb_status_queue_score_coin(game); }

mysmb_u8 mysmb_area_queue_title_score(struct mysmb_game *game)
{ return mysmb_status_queue_title_score(game); }

/* Translation of WriteGameText.  The selector chooses a ROM-authored command
 * stream; mutable numbers occupy the exact byte offsets patched by the ROM. */
mysmb_u8 mysmb_area_queue_game_text(struct mysmb_game *game, mysmb_u8 selector)
{
    mysmb_u8 offset_index;
    mysmb_u16 source;
    mysmb_u8 offset;
    mysmb_u8 index;
    mysmb_u8 name_player;

    if (game->area_prg == 0 || game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] != 0U ||
        game->area_prg_size <= MYSMB_AREA_GAME_TEXT_OFFSETS + 9U) return 0U;
    if (selector < 2U) {
        offset_index = (mysmb_u8)(selector << 1U);
    }
    else if (selector < 4U) {
        offset_index = (mysmb_u8)(selector << 1U);
        if (game->ram[0x077aU] == 0U) offset_index++;
    }
    else {
        offset_index = 8U;
    }
    source = (mysmb_u16)(MYSMB_AREA_GAME_TEXT +
        game->area_prg[MYSMB_AREA_GAME_TEXT_OFFSETS + offset_index]);
    offset = 0U;
    while (source < game->area_prg_size && game->area_prg[source] != 0xffU) {
        if (offset == 0xffU) return 0U;
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset)] =
            game->area_prg[source];
        source++;
        offset++;
    }
    if (source >= game->area_prg_size) return 0U;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset)] = 0U;
    if (selector == 1U) {
        mysmb_u8 lives;

        if (offset <= 21U) return 0U;
        /* ROM EndGameText adds one to NumberofLives, and for ten or more
         * writes a crown at Buffer1+7 before placing the remaining digit. */
        lives = (mysmb_u8)(game->ram[0x075aU] + 1U);
        if (lives >= 10U) {
            lives = (mysmb_u8)(lives - 10U);
            game->ram[MYSMB_AREA_VRAM_BUFFER1 + 7U] = 0x9fU;
        }
        game->ram[MYSMB_AREA_VRAM_BUFFER1 + 8U] = lives;
        game->ram[MYSMB_AREA_VRAM_BUFFER1 + 19U] =
            (mysmb_u8)(game->ram[MYSMB_AREA_WORLD_NUMBER] + 1U);
        game->ram[MYSMB_AREA_VRAM_BUFFER1 + 21U] =
            (mysmb_u8)(game->ram[MYSMB_AREA_LEVEL_NUMBER] + 1U);
    }
    /* EndGameText routes selectors 0, 2 and 3 through CheckPlayerName.
     * TIME UP flips the current player unless this is Game Over; the other
     * two selectors use CurrentPlayer unchanged. */
    if (selector != 1U && selector < 4U && game->ram[0x077aU] != 0U) {
        name_player = game->ram[MYSMB_AREA_CURRENT_PLAYER];
        if (selector == 2U && game->ram[0x0770U] != 3U)
            name_player ^= 1U;
        if (name_player != 0U) {
            if (offset <= 7U || game->area_prg_size <= MYSMB_AREA_LUIGI_NAME + 4U)
                return 0U;
            for (index = 0U; index < 5U; ++index) {
                game->ram[MYSMB_AREA_VRAM_BUFFER1 + 3U + index] =
                    game->area_prg[MYSMB_AREA_LUIGI_NAME + index];
            }
        }
    }
    if (selector >= 4U) {
        if (selector > 6U || offset <= 38U ||
            game->area_prg_size <= MYSMB_AREA_WARP_ZONE_NUMBERS +
            (mysmb_u16)(selector - 4U) * 4U + 2U) return 0U;
        for (index = 0U; index < 3U; ++index) {
            game->ram[MYSMB_AREA_VRAM_BUFFER1 + 27U + (mysmb_u16)index * 4U] =
                game->area_prg[MYSMB_AREA_WARP_ZONE_NUMBERS +
                    (mysmb_u16)(selector - 4U) * 4U + index];
        }
        offset = 0x2cU;
        game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset] = 0U;
        /* WriteGameText calls SetVRAMOffset only after it patches a warp
         * zone.  Other text streams leave $0300 unchanged; NMI consumes
         * their terminator from $0301. */
        game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] = offset;
    }
    return 1U;
}

/* Translation of GetPlayerColors.  The original writes one `$3f10`, length
 * four command into VRAM_Buffer1 and leaves the terminator just after it. */
mysmb_u8 mysmb_area_queue_player_palette(struct mysmb_game *game)
{
    mysmb_u8 offset;
    mysmb_u8 color_offset;
    mysmb_u8 background_index;

    offset = game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET];
    if (offset > 0xf8U || game->area_prg == 0 ||
        game->area_prg_size <= MYSMB_AREA_PLAYER_COLORS + 11U) return 0U;
    color_offset = game->ram[MYSMB_AREA_CURRENT_PLAYER] == 0U ? 0U : 4U;
    if (game->ram[0x0756U] == 2U) color_offset = 8U;
    background_index = game->ram[MYSMB_AREA_BACKGROUND_COLOR] != 0U ?
        game->ram[MYSMB_AREA_BACKGROUND_COLOR] : game->ram[MYSMB_AREA_TYPE];
    if (background_index >= 8U || game->area_prg_size <=
        MYSMB_AREA_BACKGROUND_COLORS + background_index) return 0U;
    game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset++] = 0x3fU;
    game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset++] = 0x10U;
    game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset++] = 4U;
    game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset++] =
        game->area_prg[MYSMB_AREA_BACKGROUND_COLORS + background_index];
    game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset++] =
        game->area_prg[MYSMB_AREA_PLAYER_COLORS + color_offset + 1U];
    game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset++] =
        game->area_prg[MYSMB_AREA_PLAYER_COLORS + color_offset + 2U];
    game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset++] =
        game->area_prg[MYSMB_AREA_PLAYER_COLORS + color_offset + 3U];
    game->ram[MYSMB_AREA_VRAM_BUFFER1 + offset] = 0U;
    game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] = offset;
    return 1U;
}

/* The main game path uses this after a player-state update.  It avoids
 * host-invented timing by emitting the same command only when the canonical
 * PPU palette still differs from the ROM-selected four bytes. */
mysmb_u8 mysmb_area_sync_player_palette(struct mysmb_game *game)
{
    mysmb_u8 color_offset;
    mysmb_u8 background_index;

    if (game->area_prg == 0 || game->area_prg_size <= MYSMB_AREA_PLAYER_COLORS + 11U)
        return 0U;
    color_offset = game->ram[MYSMB_AREA_CURRENT_PLAYER] == 0U ? 0U : 4U;
    if (game->ram[0x0756U] == 2U) color_offset = 8U;
    background_index = game->ram[MYSMB_AREA_BACKGROUND_COLOR] != 0U ?
        game->ram[MYSMB_AREA_BACKGROUND_COLOR] : game->ram[MYSMB_AREA_TYPE];
    if (background_index >= 8U || game->area_prg_size <=
        MYSMB_AREA_BACKGROUND_COLORS + background_index) return 0U;
    if (game->palette[0U] ==
        game->area_prg[MYSMB_AREA_BACKGROUND_COLORS + background_index] &&
        game->palette[0x11U] == game->area_prg[MYSMB_AREA_PLAYER_COLORS + color_offset + 1U] &&
        game->palette[0x12U] == game->area_prg[MYSMB_AREA_PLAYER_COLORS + color_offset + 2U] &&
        game->palette[0x13U] == game->area_prg[MYSMB_AREA_PLAYER_COLORS + color_offset + 3U])
        return 0U;
    return mysmb_area_queue_player_palette(game);
}

/* ROM QuestionBlock/BrickWithItem and the horizontal brick-row subset. */
static void mysmb_area_apply_single_block(struct mysmb_game *game,
                                          const struct mysmb_area_object *object)
{
    static const mysmb_u8 row_brick[4] = { 0x22U, 0x51U, 0x52U, 0x52U };
    mysmb_u8 value;
    mysmb_u8 column;
    mysmb_u8 length;
    mysmb_u8 offset;
    mysmb_u8 target;
    mysmb_u16 address;

    if (object->row >= 13U) return;
    column = (mysmb_u8)(object->column + ((object->page & 1U) << 4U));
    if (object->dispatch_id == 2U) {
        value = row_brick[game->ram[MYSMB_AREA_TYPE] & 3U];
        if (game->ram[MYSMB_AREA_CLOUD_OVERRIDE] != 0U) value = 0x88U;
        length = (mysmb_u8)(object->second & 0x0fU);
        for (offset = 0U; offset < length; ++offset) {
            target = (mysmb_u8)(column + offset);
            if (target >= 32U) break;
            address = (mysmb_u16)(target < 16U ? 0x0500U + target :
                                  0x05d0U + (target - 16U));
            game->ram[(mysmb_u16)(address + (mysmb_u16)object->row * 16U)] = value;
        }
        return;
    }
    if (object->dispatch_id >= 0x16U && object->dispatch_id <= 0x18U) {
        value = mysmb_brick_question_metatiles[(mysmb_u8)(object->dispatch_id - 0x16U)];
    }
    else if (object->dispatch_id >= 0x1aU && object->dispatch_id <= 0x1eU) {
        value = (mysmb_u8)(object->dispatch_id - 0x16U);
        if (game->ram[MYSMB_AREA_TYPE] != 1U) value = (mysmb_u8)(value + 5U);
        value = mysmb_brick_question_metatiles[value];
    }
    else if (object->dispatch_id == 0x20U) {
        value = 0x60U;
    }
    else return;
    address = (mysmb_u16)(column < 16U ? 0x0500U + column :
                          0x05d0U + (column - 16U));
    game->ram[(mysmb_u16)(address + (mysmb_u16)object->row * 16U)] = value;
}

/* One neutral command per game frame, derived from the original area stream. */
mysmb_u8 mysmb_area_emit_next_command(struct mysmb_game *game)
{
    struct mysmb_area_source source;
    struct mysmb_area_object object;
    struct mysmb_area_command *command;

    if (game->area_prg == 0) {
        return 0U;
    }
    source.prg = game->area_prg;
    source.prg_size = game->area_prg_size;
    if (mysmb_area_next_object(game, &source, &object) == 0U) {
        return 0U;
    }
    if (game->area_command_count < 16U) {
        command = &game->area_commands[game->area_command_count];
        command->column = object.column;
        command->row = object.row;
        command->page = object.page;
        command->dispatch_id = object.dispatch_id;
        game->area_command_count++;
    }
    mysmb_area_apply_single_block(game, &object);
    mysmb_area_refresh_background_page(game, object.page);
    return 1U;
}

/* ROM $8567 SetVRAMAddr_A selects one of the four static area palette streams.
 * The bound owner-local PRG is the source; no palette bytes enter tracked C. */
mysmb_u8 mysmb_area_apply_palette(struct mysmb_game *game, mysmb_u8 area_type)
{
    static const mysmb_u16 palette_offsets[4] = {
        MYSMB_AREA_WATER_PALETTE, MYSMB_AREA_GROUND_PALETTE,
        MYSMB_AREA_UNDERGROUND_PALETTE, MYSMB_AREA_CASTLE_PALETTE
    };
    mysmb_u16 offset;

    if (game->area_prg == 0 || area_type >= 4U) return 0U;
    offset = palette_offsets[area_type];
    if (offset >= game->area_prg_size) return 0U;
    return mysmb_game_apply_vram_commands(game, &game->area_prg[offset],
        (mysmb_u16)(game->area_prg_size - offset));
}

mysmb_u8 mysmb_area_apply_special_palette(struct mysmb_game *game,
                                          mysmb_u8 address_control)
{
    mysmb_u16 offset;

    if (address_control == 8U) offset = MYSMB_AREA_BOWSER_PALETTE;
    else if (address_control == 9U) offset = MYSMB_AREA_DAY_SNOW_PALETTE;
    else if (address_control == 10U) offset = MYSMB_AREA_NIGHT_SNOW_PALETTE;
    else if (address_control == 11U) offset = MYSMB_AREA_MUSHROOM_PALETTE;
    else return 0U;
    if (game->area_prg == 0 || offset >= game->area_prg_size) return 0U;
    return mysmb_game_apply_vram_commands(game, &game->area_prg[offset],
                                          (mysmb_u16)(game->area_prg_size - offset));
}

/* ROM $805a VRAM_AddrTable entries 12--18.  The NMI owns their transfer;
 * these streams remain in the admitted owner-local PRG. */
mysmb_u8 mysmb_area_apply_message(struct mysmb_game *game,
                                  mysmb_u8 address_control)
{
    static const mysmb_u16 message_offsets[7] = {
        MYSMB_AREA_MARIO_THANKS, MYSMB_AREA_LUIGI_THANKS,
        MYSMB_AREA_RETAINER_SAVED, MYSMB_AREA_PRINCESS_SAVED1,
        MYSMB_AREA_PRINCESS_SAVED2, MYSMB_AREA_WORLD_SELECT1,
        MYSMB_AREA_WORLD_SELECT2
    };
    mysmb_u16 offset;

    if (address_control < 12U || address_control > 18U) return 0U;
    offset = message_offsets[(mysmb_u8)(address_control - 12U)];
    if (game->area_prg == 0 || offset >= game->area_prg_size) return 0U;
    return mysmb_game_apply_vram_commands(game, &game->area_prg[offset],
                                          (mysmb_u16)(game->area_prg_size - offset));
}

/* ROM AreaParserCore RenderSceneryTerrain through RendBBuf, restricted to the
 * initial 24 columns completed before normal player control.  The two terrain
 * bytes describe the upper eight and lower five metatile rows respectively;
 * their least-significant-bit-first scan is preserved here. */
void mysmb_area_render_initial_terrain(struct mysmb_game *game)
{
    static const mysmb_u8 terrain_metatiles[4] = { 0x69U, 0x54U, 0x52U, 0x62U };
    static const mysmb_u8 terrain_render_bits[32] = {
        0x00U, 0x00U, 0x00U, 0x18U, 0x01U, 0x18U, 0x07U, 0x18U,
        0x0fU, 0x18U, 0xffU, 0x18U, 0x01U, 0x1fU, 0x07U, 0x1fU,
        0x0fU, 0x1fU, 0x81U, 0x1fU, 0x01U, 0x00U, 0x8fU, 0x1fU,
        0xf1U, 0x18U, 0xf9U, 0x18U, 0xf1U, 0x18U, 0xffU, 0x1fU
    };
    mysmb_u8 terrain;
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u8 bits;
    mysmb_u16 address;

    terrain = terrain_metatiles[game->ram[MYSMB_AREA_TYPE] & 3U];
    if (game->ram[MYSMB_AREA_CLOUD_OVERRIDE] != 0U) terrain = 0x88U;
    for (column = 0U; column < 24U; ++column) {
        for (row = 0U; row < 13U; ++row) {
            bits = terrain_render_bits[(mysmb_u16)((game->ram[MYSMB_AREA_TERRAIN] & 0x0fU) * 2U +
                                                    (row < 8U ? 0U : 1U))];
            address = (mysmb_u16)(column < 16U ? 0x0500U + column :
                                  0x05d0U + (column - 16U));
            address = (mysmb_u16)(address + (mysmb_u16)row * 16U);
            if ((bits & (mysmb_u8)(1U << (row & 7U))) != 0U) {
                game->ram[address] = terrain;
            }
        }
    }
}

/* The original keeps two physical block-buffer pages and rewrites the page
 * that has just moved ahead of the camera.  The initial pass has a 24-column
 * lead-in; later pages always replace one full physical page. */
void mysmb_area_render_terrain_page(struct mysmb_game *game, mysmb_u8 page)
{
    static const mysmb_u8 terrain_metatiles[4] = { 0x69U, 0x54U, 0x52U, 0x62U };
    static const mysmb_u8 terrain_render_bits[32] = {
        0x00U, 0x00U, 0x00U, 0x18U, 0x01U, 0x18U, 0x07U, 0x18U,
        0x0fU, 0x18U, 0xffU, 0x18U, 0x01U, 0x1fU, 0x07U, 0x1fU,
        0x0fU, 0x1fU, 0x81U, 0x1fU, 0x01U, 0x00U, 0x8fU, 0x1fU,
        0xf1U, 0x18U, 0xf9U, 0x18U, 0xf1U, 0x18U, 0xffU, 0x1fU
    };
    mysmb_u8 terrain;
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u8 bits;
    mysmb_u16 address;

    terrain = terrain_metatiles[game->ram[MYSMB_AREA_TYPE] & 3U];
    if (game->ram[MYSMB_AREA_CLOUD_OVERRIDE] != 0U) terrain = 0x88U;
    for (column = 0U; column < 16U; ++column) {
        for (row = 0U; row < 13U; ++row) {
            bits = terrain_render_bits[(mysmb_u16)((game->ram[MYSMB_AREA_TERRAIN] & 0x0fU) * 2U +
                                                    (row < 8U ? 0U : 1U))];
            address = (mysmb_u16)((page & 1U) != 0U ? 0x05d0U + column :
                                  0x0500U + column);
            address = (mysmb_u16)(address + (mysmb_u16)row * 16U);
            game->ram[address] = (bits & (mysmb_u8)(1U << (row & 7U))) != 0U ? terrain : 0U;
        }
    }
}

/* Translation of the RenderSceneryTerrain portion of ROM AreaParserCore
 * ($92f7-$9376).  It builds exactly one 13-metatile column, runs the original
 * ProcessAreaData owner over that staging column, then copies its
 * collision-qualified values into the physical 32-column block buffer. */
mysmb_u8 mysmb_area_render_scenery_terrain_column(struct mysmb_game *game)
{
    mysmb_u8 metatiles[13];
    mysmb_u8 index;
    mysmb_u8 scene;
    mysmb_u8 row;
    mysmb_u8 terrain;
    mysmb_u8 bits;
    mysmb_u8 bound_index;
    mysmb_u8 column;
    mysmb_u16 source;
    mysmb_u16 address;

    if (game->area_prg == 0 || game->area_prg_size <=
        MYSMB_AREA_BLOCK_BUFFER_LOW_BOUNDS + 3U ||
        game->ram[MYSMB_AREA_TYPE] >= 4U) return 0U;
    /* ClrMTBuf: X descends from $0c through zero in the source. */
    for (index = 0U; index < 13U; ++index) metatiles[index] = 0U;

    /* ThirdP/RendBack/SceLoop1: reduce to the three-page scenery phase,
     * select one packed entry, then overlay no more than three rows. */
    scene = game->ram[MYSMB_AREA_BACKGROUND];
    if (scene != 0U && scene <= 3U) {
        source = (mysmb_u16)(MYSMB_AREA_BACKGROUND_SCENE_DATA +
            (mysmb_u16)(game->ram[MYSMB_AREA_CURRENT_PAGE] % 3U) * 16U +
            game->area_prg[(mysmb_u16)(MYSMB_AREA_BACKGROUND_SCENE_OFFSETS + scene - 1U)] +
            (game->ram[MYSMB_AREA_CURRENT_COLUMN] & 0x0fU));
        if (source < game->area_prg_size) {
            scene = game->area_prg[source];
            if ((scene & 0x0fU) != 0U) {
                source = (mysmb_u16)(MYSMB_AREA_BACKGROUND_METATILES +
                    (mysmb_u16)((scene & 0x0fU) - 1U) * 3U);
                row = (mysmb_u8)(scene >> 4U);
                for (index = 0U; index < 3U && row < 11U; ++index, ++row) {
                    if ((mysmb_u16)(source + index) >= game->area_prg_size) return 0U;
                    metatiles[row] = game->area_prg[(mysmb_u16)(source + index)];
                }
            }
        }
    }

    /* RendFore/SceLoop2/NoFore: nonzero foreground bytes replace the
     * existing staged row; zero bytes deliberately leave it intact. */
    scene = game->ram[MYSMB_AREA_FOREGROUND];
    if (scene != 0U && scene <= 3U) {
        source = (mysmb_u16)(MYSMB_AREA_FOREGROUND_SCENE_DATA +
            game->area_prg[(mysmb_u16)(MYSMB_AREA_FOREGROUND_SCENE_OFFSETS + scene - 1U)]);
        for (index = 0U; index < 13U; ++index) {
            if ((mysmb_u16)(source + index) >= game->area_prg_size) return 0U;
            scene = game->area_prg[(mysmb_u16)(source + index)];
            if (scene != 0U) metatiles[index] = scene;
        }
    }

    /* RendTerr/TerMTile/StoreMT/TerrLoop through EndUChk: preserve the
     * source's two-byte, least-significant-bit-first terrain scan. */
    terrain = game->area_prg[(mysmb_u16)(MYSMB_AREA_TERRAIN_METATILES +
        game->ram[MYSMB_AREA_TYPE])];
    if (game->ram[MYSMB_AREA_TYPE] == 0U && game->ram[MYSMB_AREA_WORLD_NUMBER] == 7U)
        terrain = 0x62U;
    if (game->ram[MYSMB_AREA_CLOUD_OVERRIDE] != 0U) terrain = 0x88U;
    for (row = 0U; row < 13U; ++row) {
        bits = game->area_prg[(mysmb_u16)(MYSMB_AREA_TERRAIN_RENDER_BITS +
            (mysmb_u16)(game->ram[MYSMB_AREA_TERRAIN] & 0x0fU) * 2U + (row >> 3U))];
        if (game->ram[MYSMB_AREA_CLOUD_OVERRIDE] != 0U && row >= 8U) bits &= 0x08U;
        if (game->ram[MYSMB_AREA_TYPE] == 2U && row == 11U) terrain = 0x54U;
        if ((bits & (mysmb_u8)(1U << (row & 7U))) != 0U) metatiles[row] = terrain;
    }

    for (row = 0U; row < 13U; ++row)
        game->ram[MYSMB_AREA_METATILE_BUFFER + row] = metatiles[row];
    /* Unit routes may exercise scenery without an admitted area pointer.
     * A loaded area always has a $80-$ff PRG high byte and therefore follows
     * the source's unconditional ProcessAreaData call. */
    if (game->ram[MYSMB_AREA_DATA_HIGH] >= 0x80U &&
        mysmb_area_process_object_state(game) == 0U) return 0U;

    /* RendBBuf/ChkMTLow/StrBlock: ProcessAreaData has changed the staging
     * column, so qualify that resulting value against BlockBuffLowBounds. */
    column = game->ram[MYSMB_AREA_BLOCK_COLUMN];
    address = mysmb_area_get_block_buffer_address(game, column);
    for (row = 0U; row < 13U; ++row) {
        metatiles[row] = game->ram[MYSMB_AREA_METATILE_BUFFER + row];
        bound_index = (mysmb_u8)(metatiles[row] >> 6U);
        game->ram[(mysmb_u16)(address + (mysmb_u16)row * 16U)] =
            metatiles[row] < game->area_prg[(mysmb_u16)(
                MYSMB_AREA_BLOCK_BUFFER_LOW_BOUNDS + bound_index)] ?
            0U : metatiles[row];
    }
    return 1U;
}

/* ROM $88ae-$889c RenderAreaGraphics.  The original writes two vertical
 * tiles for every metatile into VRAM_Buffer2, then accumulates seven
 * attribute bytes for RenderAttributeTables. */
mysmb_u8 mysmb_area_render_graphics(struct mysmb_game *game)
{
    mysmb_u8 buffer_offset;
    mysmb_u8 row;
    mysmb_u8 metatile;
    mysmb_u8 palette;
    mysmb_u8 side;
    mysmb_u8 attribute_shift;
    mysmb_u16 graphics;
    mysmb_u16 source;

    if (game->area_prg == 0 || game->area_prg_size <= MYSMB_AREA_METATILE_HIGH + 3U)
        return 0U;
    buffer_offset = game->ram[MYSMB_AREA_VRAM_BUFFER2_OFFSET];
    if (buffer_offset > 0xd6U) return 0U;
    side = (game->ram[MYSMB_AREA_PARSER_TASK] & 1U) != 0U ? 0U : 2U;
    game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset] = game->ram[MYSMB_AREA_NT_HIGH];
    game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset + 1U] = game->ram[MYSMB_AREA_NT_LOW];
    game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset + 2U] = 0x9aU;
    for (row = 0U; row < 13U; ++row) {
        metatile = game->ram[MYSMB_AREA_METATILE_BUFFER + row];
        palette = (mysmb_u8)(metatile >> 6U);
        graphics = (mysmb_u16)(game->area_prg[MYSMB_AREA_METATILE_LOW + palette] |
            ((mysmb_u16)game->area_prg[MYSMB_AREA_METATILE_HIGH + palette] << 8U));
        if (graphics < 0x8000U) return 0U;
        source = (mysmb_u16)(graphics - 0x8000U +
            (mysmb_u16)(metatile & 0x3fU) * 4U + side);
        if ((mysmb_u16)(source + 1U) >= game->area_prg_size) return 0U;
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER2 + buffer_offset + 3U +
            (mysmb_u16)row * 2U)] = game->area_prg[source];
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER2 + buffer_offset + 4U +
            (mysmb_u16)row * 2U)] = game->area_prg[(mysmb_u16)(source + 1U)];
        attribute_shift = (mysmb_u8)(((row & 1U) << 2U) |
            ((game->ram[MYSMB_AREA_CURRENT_COLUMN] & 1U) << 1U));
        game->ram[MYSMB_AREA_ATTRIBUTE_BUFFER + (row >> 1U)] |=
            (mysmb_u8)(palette << attribute_shift);
    }
    buffer_offset = (mysmb_u8)(buffer_offset + 29U);
    game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset] = 0U;
    game->ram[MYSMB_AREA_VRAM_BUFFER2_OFFSET] = buffer_offset;
    game->ram[MYSMB_AREA_NT_LOW]++;
    if ((game->ram[MYSMB_AREA_NT_LOW] & 0x1fU) == 0U) {
        game->ram[MYSMB_AREA_NT_LOW] = 0x80U;
        game->ram[MYSMB_AREA_NT_HIGH] ^= 0x04U;
    }
    game->ram[MYSMB_AREA_VRAM_ADDRESS_CONTROL] = 6U;
    return 1U;
}

/* ROM $896a-$89a6 RenderAttributeTables. */
mysmb_u8 mysmb_area_render_attribute_tables(struct mysmb_game *game)
{
    mysmb_u8 buffer_offset;
    mysmb_u8 row;
    mysmb_u8 low;
    mysmb_u8 high;
    mysmb_u8 borrow;

    buffer_offset = game->ram[MYSMB_AREA_VRAM_BUFFER2_OFFSET];
    if (buffer_offset > 0xdeU) return 0U;
    low = (mysmb_u8)(game->ram[MYSMB_AREA_NT_LOW] & 0x1fU);
    borrow = low < 4U ? 1U : 0U;
    low = (mysmb_u8)((low - 4U) & 0x1fU);
    high = game->ram[MYSMB_AREA_NT_HIGH];
    if (borrow != 0U) high ^= 0x04U;
    high = (mysmb_u8)((high & 0x04U) | 0x23U);
    low = (mysmb_u8)(0xc0U + (low >> 2U) + ((low & 0x02U) != 0U ? 1U : 0U));
    for (row = 0U; row < 7U; ++row) {
        /* ROM $8985-$898c reloads the prior attribute low byte and adds
         * eight for each row.  These writes are vertically spaced in the
         * attribute table; advancing by one misaddresses rows two through
         * seven while leaving the first command deceptively correct. */
        low = (mysmb_u8)(low + 8U);
        game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset++] = high;
        game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset++] = low;
        game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset++] = 1U;
        game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset++] =
            game->ram[MYSMB_AREA_ATTRIBUTE_BUFFER + row];
        game->ram[MYSMB_AREA_ATTRIBUTE_BUFFER + row] = 0U;
    }
    game->ram[MYSMB_AREA_VRAM_BUFFER2 + buffer_offset] = 0U;
    game->ram[MYSMB_AREA_VRAM_BUFFER2_OFFSET] = buffer_offset;
    game->ram[MYSMB_AREA_VRAM_ADDRESS_CONTROL] = 6U;
    return 1U;
}

/* ROM $92b0-$92e8 AreaParserTaskHandler.  The scenery task calls
 * RenderSceneryTerrain, whose source order includes ProcessAreaData before
 * the physical block-buffer write; this handler owns the graphics/attribute
 * cadence around those two output columns. */
mysmb_u8 mysmb_area_parser_task_step(struct mysmb_game *game)
{
    mysmb_u8 task;

    task = game->ram[MYSMB_AREA_PARSER_TASK];
    if (task == 0U) task = 8U;
    game->ram[MYSMB_AREA_PARSER_TASK] = task;
    task--;
    if (task == 4U || task == 0U) {
        game->ram[MYSMB_AREA_CURRENT_COLUMN]++;
        if ((game->ram[MYSMB_AREA_CURRENT_COLUMN] & 0x0fU) == 0U) {
            game->ram[MYSMB_AREA_CURRENT_COLUMN] = 0U;
            game->ram[MYSMB_AREA_CURRENT_PAGE]++;
        }
        game->ram[MYSMB_AREA_BLOCK_COLUMN] =
            (mysmb_u8)((game->ram[MYSMB_AREA_BLOCK_COLUMN] + 1U) & 0x1fU);
    }
    else if (task == 6U || task == 5U || task == 2U || task == 1U) {
        if (mysmb_area_render_graphics(game) == 0U) return 0U;
    }
    else {
        /* ROM AreaParserCore runs ProcessAreaData before RenderSceneryTerrain
         * while backloading.  RenderSceneryTerrain itself performs the second
         * source call immediately before its block-buffer commit. */
        if (game->ram[MYSMB_AREA_BACKLOADING] != 0U &&
            mysmb_area_process_object_state(game) == 0U) return 0U;
        if (mysmb_area_render_scenery_terrain_column(game) == 0U) return 0U;
    }
    game->ram[MYSMB_AREA_PARSER_TASK] = task;
    if (task == 0U) return mysmb_area_render_attribute_tables(game);
    return 1U;
}

/* ROM $86e6-$86ff AreaParserTaskControl.  One call completes exactly the
 * eight task slots that produce a two-column set.  On the final set, the ROM
 * advances ScreenRoutineTask before it selects VRAM buffer control six. */
mysmb_u8 mysmb_area_parser_task_control(struct mysmb_game *game)
{
    /* ROM $86e6 disables output before every two-column parser set.  The
     * pending buffer is still consumed by the following NMI, but its mask
     * remains in the source's screen-off state until later screen tasks. */
    game->ram[MYSMB_AREA_DISABLE_SCREEN]++;
    do {
        if (mysmb_area_parser_task_step(game) == 0U) return 0U;
    } while (game->ram[MYSMB_AREA_PARSER_TASK] != 0U);
    game->ram[MYSMB_AREA_COLUMN_SETS]--;
    if ((game->ram[MYSMB_AREA_COLUMN_SETS] & 0x80U) != 0U)
        game->ram[MYSMB_AREA_SCREEN_ROUTINE_TASK]++;
    game->ram[MYSMB_AREA_VRAM_ADDRESS_CONTROL] = 6U;
    return 1U;
}

/* Translation of the stream/slot-control part of ROM $9508-$958f
 * ProcessAreaData. It intentionally stops before JumpEngine: each object
 * family must own its own metatile writes. The result is the original three
 * slot state ($072d/$0730), page selector, and stream offset. */
/* ROM $9bbb-$9bca GetLrgObjAttrib. INY wraps the offset, not the
 * effective address. The low nibble of the first byte belongs to $07. */
mysmb_u8 mysmb_area_get_large_object_attributes(struct mysmb_game *game,
                                                 mysmb_u8 slot)
{
    mysmb_u16 base, first, second;
    mysmb_u8 offset;

    base = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_AREA_DATA_HIGH] << 8U) |
                       game->ram[MYSMB_AREA_DATA_LOW]);
    base = (mysmb_u16)(base - 0x8000U);
    offset = game->ram[MYSMB_AREA_OBJECT_OFFSET_BUFFER + slot];
    first = (mysmb_u16)(base + offset);
    second = (mysmb_u16)(base + (mysmb_u8)(offset + 1U));
    if (game->area_prg == 0 || first >= game->area_prg_size ||
        second >= game->area_prg_size) return 0U;
    game->ram[7U] = (mysmb_u8)(game->area_prg[first] & 0x0fU);
    return (mysmb_u8)(game->area_prg[second] & 0x0fU);
}

/* ROM $9baf-$9bba ChkLrgObjFixedLength / LenSet. Return original carry. */
mysmb_u8 mysmb_area_check_fixed_length(struct mysmb_game *game,
                                        mysmb_u8 slot, mysmb_u8 length)
{
    if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] < 0x80U) return 0U;
    game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = length;
    return 1U;
}

/* ROM $9bac ChkLrgObjLength retains decoded Y even if the slot is set. */
mysmb_u8 mysmb_area_check_large_length(struct mysmb_game *game,
                                        mysmb_u8 slot, mysmb_u8 *length)
{
    *length = mysmb_area_get_large_object_attributes(game, slot);
    return mysmb_area_check_fixed_length(game, slot, *length);
}

/* ROM $9bcb-$9bd2 GetAreaObjXPosition. */
mysmb_u8 mysmb_area_object_x_position(const struct mysmb_game *game)
{
    return (mysmb_u8)(game->ram[MYSMB_AREA_CURRENT_COLUMN] << 4U);
}

/* ROM $9bd3-$9bdc GetAreaObjYPosition. */
mysmb_u8 mysmb_area_object_y_position(const struct mysmb_game *game)
{
    return (mysmb_u8)((game->ram[7U] << 4U) + 32U);
}

/* ROM $9b7d-$9bab RenderUnderPart. A foreground object may fill downward,
 * but the source preserves ledge centers, palette-three objects, and the
 * mushroom stem/top interaction in the metatile staging column. */
static void mysmb_area_render_under_part(struct mysmb_game *game,
                                         mysmb_u8 row,
                                         mysmb_u8 height,
                                         mysmb_u8 metatile)
{
    mysmb_u8 existing;

    do {
        /* ROM re-enters RenderUnderPart with the decremented Y value. */
        game->ram[MYSMB_AREA_OBJECT_HEIGHT] = height;
        existing = game->ram[MYSMB_AREA_METATILE_BUFFER + row];
        if (existing == 0U || existing == 0xc0U ||
            (existing != 0x17U && existing != 0x1aU && existing < 0xc0U &&
             (existing != 0x54U || metatile != 0x50U))) {
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = metatile;
        }
        row++;
        if (row >= 13U) break;
        height = (mysmb_u8)(game->ram[MYSMB_AREA_OBJECT_HEIGHT] - 1U);
    } while (height < 0x80U);
}

/* ROM $9b3d HoleMetatiles through $9b73 NoWhirlP. Cannon and whirlpool
 * arrays alias the same RAM; whirlpool registration wraps after five slots. */
static const mysmb_u8 mysmb_area_hole_metatiles[4] = {0x87U, 0U, 0U, 0U};

static void mysmb_area_hole_empty(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 length, offset, x;

    if (mysmb_area_check_large_length(game, slot, &length) != 0U) {
        if (game->ram[MYSMB_AREA_TYPE] == 0U) {
            offset = game->ram[MYSMB_AREA_CANNON_OFFSET];
            x = mysmb_area_object_x_position(game);
            game->ram[MYSMB_AREA_CANNON_X + offset] = (mysmb_u8)(x - 16U);
            game->ram[MYSMB_AREA_CANNON_PAGE + offset] =
                (mysmb_u8)(game->ram[MYSMB_AREA_CURRENT_PAGE] - (x < 16U ? 1U : 0U));
            game->ram[MYSMB_AREA_CANNON_Y + offset] =
                (mysmb_u8)((length + 2U) << 4U);
            offset++;
            if (offset >= 5U) offset = 0U;
            /* StrWOffset. */
            game->ram[MYSMB_AREA_CANNON_OFFSET] = offset;
        }
    }
    /* NoWhirlP: drawing is independent of the water/initialization gates. */
    mysmb_area_render_under_part(game, 8U, 15U,
        mysmb_area_hole_metatiles[game->ram[MYSMB_AREA_TYPE]]);
}

/* ROM BulletBillCannon -> SetupCannon -> StrCOffset ($9a69-$9aa4).
 * The top/middle stores are unconditional; only the base uses UnderPart's
 * overlap rules. GetAreaObjYPosition retains the original attribute row. */
static void mysmb_area_setup_cannon(struct mysmb_game *game)
{
    mysmb_u8 slot;

    slot = game->ram[MYSMB_AREA_CANNON_OFFSET];
    game->ram[MYSMB_AREA_CANNON_Y + slot] =
        mysmb_area_object_y_position(game);
    game->ram[MYSMB_AREA_CANNON_PAGE + slot] =
        game->ram[MYSMB_AREA_CURRENT_PAGE];
    game->ram[MYSMB_AREA_CANNON_X + slot] =
        mysmb_area_object_x_position(game);
    slot++;
    if (slot >= 6U) slot = 0U;
    /* StrCOffset: the six-entry cannon/whirlpool ring has one offset. */
    game->ram[MYSMB_AREA_CANNON_OFFSET] = slot;
}

static void mysmb_area_bullet_bill_cannon(struct mysmb_game *game)
{
    mysmb_u8 row;
    mysmb_u8 height;

    height = mysmb_area_get_large_object_attributes(game,
        game->ram[MYSMB_AREA_OBJECT_OFFSET]);
    row = game->ram[7U];
    game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x64U;
    row++;
    height--;
    if (height < 0x80U) {
        game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x65U;
        row++;
        height--;
        if (height < 0x80U)
            mysmb_area_render_under_part(game, row, height, 0x66U);
    }
    mysmb_area_setup_cannon(game);
}

/* ROM $96f2-$9737 ScrollLockObject_Warp through AreaFrenzy.  These entries
 * are selected from the row-13 JumpEngine after DecodeAreaData has placed
 * the low-six-bit selector in $00. */
static void mysmb_area_kill_enemies(struct mysmb_game *game, mysmb_u8 id)
{
    mysmb_u8 slot;

    slot = 5U;
    do {
        slot--;
        if (game->ram[MYSMB_ENEMY_ID + slot] == id)
            game->ram[MYSMB_ENEMY_FLAG + slot] = 0U;
    } while (slot != 0U);
}

static void mysmb_area_scroll_lock_warp(struct mysmb_game *game)
{
    mysmb_u8 selector;

    selector = 4U;
    if (game->ram[MYSMB_AREA_WORLD_NUMBER] != 0U) {
        selector++;
        if (game->ram[MYSMB_AREA_TYPE] == 1U) selector++;
    }
    game->ram[MYSMB_AREA_WARP_ZONE_CONTROL] = selector;
    (void)mysmb_area_queue_game_text(game, selector);
    mysmb_area_kill_enemies(game, 13U);
    game->ram[MYSMB_AREA_SCROLL_LOCK] ^= 1U;
}

static void mysmb_area_queue_frenzy(struct mysmb_game *game, mysmb_u8 selector)
{
    static const mysmb_u8 frenzy_ids[3] = { 20U, 23U, 24U };
    mysmb_u8 id;
    mysmb_u8 slot;

    id = frenzy_ids[(mysmb_u8)(selector - 8U)];
    slot = 5U;
    do {
        slot--;
        if (game->ram[MYSMB_ENEMY_ID + slot] == id) {
            id = 0U;
            break;
        }
    } while (slot != 0U);
    game->ram[MYSMB_AREA_ENEMY_FRENZY_QUEUE] = id;
}

/* ROM TreeLedge through MushLExit. Attribute decoding belongs to the
 * original helper; ProcessAreaData owns the post-handler length decrement. */
static void mysmb_area_style_ledge(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 style)
{
    mysmb_u8 row, length;
    mysmb_u8 object_length, initialized;

    object_length = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
    initialized = 0U;
    if (style == 0U) length = mysmb_area_get_large_object_attributes(game, slot);
    else initialized = mysmb_area_check_large_length(game, slot, &length);
    row = game->ram[7U];
    if (style == 0U) {
        if (object_length == 0U) {
            mysmb_area_render_under_part(game, row, 0U, 0x18U);
            return;
        }
        if (object_length >= 0x80U) {
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = length;
            if ((game->ram[MYSMB_AREA_CURRENT_PAGE] |
                 game->ram[MYSMB_AREA_CURRENT_COLUMN]) != 0U) {
                mysmb_area_render_under_part(game, row, 0U, 0x16U);
                return;
            }
        }
        game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x17U;
        mysmb_area_render_under_part(game, (mysmb_u8)(row + 1U), 15U, 0x4cU);
        return;
    }

    game->ram[0x0006U] = length;
    if (initialized != 0U) {
        game->ram[MYSMB_AREA_MUSHROOM_HALF_LENGTH + slot] =
            (mysmb_u8)(length >> 1U);
        mysmb_area_render_under_part(game, row, 0U, 0x19U);
        return;
    }
    if (object_length == 0U) {
        mysmb_area_render_under_part(game, row, 0U, 0x1bU);
        return;
    }
    game->ram[0x0006U] = game->ram[MYSMB_AREA_MUSHROOM_HALF_LENGTH + slot];
    game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x1aU;
    if (object_length != game->ram[0x0006U]) return;
    game->ram[MYSMB_AREA_METATILE_BUFFER + row + 1U] = 0x4fU;
    mysmb_area_render_under_part(game, (mysmb_u8)(row + 2U), 15U, 0x50U);
}

static void mysmb_area_pulley_rope(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 length;
    mysmb_u8 object_length;
    mysmb_u8 metatile;

    object_length = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
    if (mysmb_area_check_large_length(game, slot, &length) != 0U) {
        metatile = 0x42U;
    }
    else if (object_length != 0U) {
        metatile = 0x41U;
    }
    else {
        metatile = 0x43U;
    }
    game->ram[MYSMB_AREA_METATILE_BUFFER] = metatile;
}

/* ROM $99bb-$99cc.  The row-15 JumpEngine entries deliberately share the
 * DrawRope tail route.  Keep the two callers distinct: BalancePlatRope
 * clears its lower staging rows before it reloads the decoded low nibble. */
static void mysmb_area_draw_rope(struct mysmb_game *game, mysmb_u8 row,
                                 mysmb_u8 height)
{
    /* DrawRope: LDA #$40; JMP RenderUnderPart. */
    mysmb_area_render_under_part(game, row, height, 0x40U);
}

static void mysmb_area_endless_rope(struct mysmb_game *game)
{
    /* EndlessRope: LDX #$00; LDY #$0f; JMP DrawRope. */
    mysmb_area_draw_rope(game, 0U, 15U);
}

static void mysmb_area_balance_platform_rope(struct mysmb_game *game)
{
    mysmb_u8 height;

    /* BalancePlatRope saves X across the blanking call, then GetLrgObjAttrib
     * supplies the second-byte low nibble in Y before it enters DrawRope
     * with X=$01.  This native route has parameters rather than CPU X/Y, so
     * only the exact RAM-visible effects are represented here. */
    mysmb_area_render_under_part(game, 1U, 15U, 0x44U);
    height = mysmb_area_get_large_object_attributes(game,
        game->ram[MYSMB_AREA_OBJECT_OFFSET]);
    mysmb_area_draw_rope(game, 1U, height);
}

/* ROM $99ed-$99f5 CoinMetatileData and RowOfCoins.  The four entries are
 * selected only by AreaType; GetRow remains the separately owned common
 * length/row renderer that this selector tail-calls in the original. */
static const mysmb_u8 mysmb_area_coin_metatile_data[4] = {
    0xc3U, 0xc2U, 0xc2U, 0xc2U
};

/* ROM $99fb-$9a24 C_ObjectRow through ColObj.  The decoder's row-13
 * selector is 2, 3 or 4, so the source deliberately indexes both tables at
 * selector minus two. */
static const mysmb_u8 mysmb_area_c_object_row[3] = { 0x06U, 0x07U, 0x08U };
static const mysmb_u8 mysmb_area_c_object_metatile[3] = {
    0xc5U, 0x0cU, 0x89U
};

/* ROM $9a25/$9a29 SolidBlockMetatiles / BrickMetatiles. */
static const mysmb_u8 mysmb_area_solid_block_metatiles[4] = {
    0x69U, 0x61U, 0x61U, 0x62U
};
static const mysmb_u8 mysmb_area_brick_metatiles[5] = {
    0x22U, 0x51U, 0x52U, 0x52U, 0x88U
};

/* ROM $9a48 DrawRow: reload the attribute row and discard vertical extent.
 * The metatile argument preserves the value held by PHA/PLA in the source. */
static void mysmb_area_draw_row(struct mysmb_game *game, mysmb_u8 metatile)
{
    mysmb_area_render_under_part(game, game->ram[0x0007U], 0U, metatile);
}

/* ROM $9a44 GetRow -> ChkLrgObjLength -> DrawRow. */
static void mysmb_area_get_row(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 metatile)
{
    mysmb_u8 second;
    (void)mysmb_area_check_large_length(game, slot, &second);
    mysmb_area_draw_row(game, metatile);
}

/* ROM $9a38 DrawBricks retains the caller's selected table index. */
static void mysmb_area_draw_bricks(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 index)
{
    mysmb_area_get_row(game, slot, mysmb_area_brick_metatiles[index]);
}

/* ROM $9a2e RowOfBricks: only this entry has CloudTypeOverride. */
static void mysmb_area_row_of_bricks(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 index;
    index = game->ram[MYSMB_AREA_TYPE];
    if (game->ram[MYSMB_AREA_CLOUD_OVERRIDE] != 0U) index = 4U;
    mysmb_area_draw_bricks(game, slot, index);
}

/* ROM $9a3e RowOfSolidBlocks falls through to GetRow. */
static void mysmb_area_row_of_solid_blocks(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_area_get_row(game, slot, mysmb_area_solid_block_metatiles[game->ram[MYSMB_AREA_TYPE]]);
}

/* ROM $9a5f GetRow2 keeps the decoded low-nibble vertical extent. */
static void mysmb_area_get_row2(struct mysmb_game *game, mysmb_u8 metatile)
{
    mysmb_u8 second;
    second = mysmb_area_get_large_object_attributes(game,
        game->ram[MYSMB_AREA_OBJECT_OFFSET]);
    mysmb_area_render_under_part(game, game->ram[7U], second, metatile);
}

/* ROM $9a50 ColumnOfBricks: no cloud override. */
static void mysmb_area_column_of_bricks(struct mysmb_game *game)
{
    mysmb_area_get_row2(game, mysmb_area_brick_metatiles[game->ram[MYSMB_AREA_TYPE]]);
}

/* ROM $9a59 ColumnOfSolidBlocks falls through to GetRow2. */
static void mysmb_area_column_of_solid_blocks(struct mysmb_game *game)
{
    mysmb_area_get_row2(game, mysmb_area_solid_block_metatiles[game->ram[MYSMB_AREA_TYPE]]);
}

static void mysmb_area_row_of_coins(struct mysmb_game *game, mysmb_u8 slot)
{
    /* RowOfCoins: LDY AreaType; LDA CoinMetatileData,Y; JMP GetRow. */
    mysmb_area_get_row(game, slot, mysmb_area_coin_metatile_data[game->ram[MYSMB_AREA_TYPE]]);
}

/* ROM $9a20 ColObj: LDY #$00; JMP RenderUnderPart. */
static void mysmb_area_col_obj(struct mysmb_game *game, mysmb_u8 row,
                               mysmb_u8 metatile)
{
    mysmb_area_render_under_part(game, row, 0U, metatile);
}

/* ROM $9a0e ChainObj: the row-13 decoder selector chooses the paired
 * row/metatile table entries before tail-entering ColObj. */
static void mysmb_area_chain_obj(struct mysmb_game *game)
{
    mysmb_u8 index;

    index = (mysmb_u8)(game->ram[0x0000U] - 2U);
    mysmb_area_col_obj(game, mysmb_area_c_object_row[index],
                        mysmb_area_c_object_metatile[index]);
}

/* ROM $9a01 CastleBridgeObj: LDY #$0c; JSR ChkLrgObjFixedLength;
 * JMP ChainObj.  The generic parser owns the helper's persistent slot and
 * post-handler decrement; this entry supplies its fixed initial length. */
static void mysmb_area_castle_bridge_obj(struct mysmb_game *game,
                                         mysmb_u8 slot)
{
    (void)mysmb_area_check_fixed_length(game, slot, 12U);
    mysmb_area_chain_obj(game);
}

/* ROM $9a09 AxeObj falls through to ChainObj after selecting address
 * control eight. */
static void mysmb_area_axe_obj(struct mysmb_game *game)
{
    game->ram[MYSMB_AREA_VRAM_ADDRESS_CONTROL] = 8U;
    mysmb_area_chain_obj(game);
}

/* ROM $9a19 EmptyBlock obtains the decoded row through GetLrgObjAttrib,
 * loads $c4 and falls into the common one-column ColObj tail. */
static void mysmb_area_empty_block(struct mysmb_game *game)
{
    mysmb_u8 row;
    (void)mysmb_area_get_large_object_attributes(game,
        game->ram[MYSMB_AREA_OBJECT_OFFSET]);
    row = game->ram[7U];
    mysmb_area_col_obj(game, row, 0xc4U);
}

/* ROM $4014-$4091 static object handlers. The caller has already admitted the
 * object to a persistent parser slot and filled the terrain column; these
 * handlers overwrite only its selected metatile rows. */
/* ROM $9b36 GetAreaObjectID -> $9b3c ExitDecBlock. SEC/SBC #0 preserves
 * the decoded byte; the return is also the hidden-disabled exit. */
static mysmb_u8 mysmb_area_get_object_id(const struct mysmb_game *game)
{
    return game->ram[0U];
}

/* ROM $9b2c DrawQBlk: retain the selected tile across row decode, then
 * use DrawRow so existing foreground and height state obey UnderPart. */
static void mysmb_area_draw_question_block(struct mysmb_game *game, mysmb_u8 index)
{
    mysmb_u8 metatile;
    metatile = mysmb_brick_question_metatiles[index];
    (void)mysmb_area_get_large_object_attributes(game,
        game->ram[MYSMB_AREA_OBJECT_OFFSET]);
    mysmb_area_draw_row(game, metatile);
}

/* ROM $9b19 BrickWithItem -> $9b28 BWithL -> DrawQBlk. */
static void mysmb_area_brick_with_item(struct mysmb_game *game)
{
    mysmb_u8 adder;
    game->ram[7U] = mysmb_area_get_object_id(game);
    adder = game->ram[MYSMB_AREA_TYPE] == 1U ? 0U : 5U;
    mysmb_area_draw_question_block(game, (mysmb_u8)(adder + game->ram[7U]));
}

/* ROM $9b01 Hidden1UpBlock, including its ExitDecBlock branch. */
static void mysmb_area_hidden_1up_block(struct mysmb_game *game)
{
    if (game->ram[MYSMB_AREA_HIDDEN_1UP_FLAG] == 0U) return;
    game->ram[MYSMB_AREA_HIDDEN_1UP_FLAG] = 0U;
    mysmb_area_brick_with_item(game);
}

/* ROM $9b0e QuestionBlock. */
static void mysmb_area_question_block(struct mysmb_game *game)
{
    mysmb_area_draw_question_block(game, mysmb_area_get_object_id(game));
}

/* ROM $9b14 BrickWithCoins falls through to BrickWithItem. */
static void mysmb_area_brick_with_coins(struct mysmb_game *game)
{
    game->ram[0x06bcU] = 0U;
    mysmb_area_brick_with_item(game);
}

/* ROM $9ad3-$9b00 Jumpspring. The caller does not branch on allocation
 * carry: a full ordinary pool uses slot five, including flag INC/wrap. */
static void mysmb_area_jumpspring(struct mysmb_game *game)
{
    mysmb_u8 row;
    mysmb_u8 slot;

    (void)mysmb_area_get_large_object_attributes(game,
        game->ram[MYSMB_AREA_OBJECT_OFFSET]);
    row = game->ram[7U];
    (void)mysmb_area_find_empty_enemy_slot(game, &slot);
    game->ram[MYSMB_ENEMY_X + slot] =
        mysmb_area_object_x_position(game);
    game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_AREA_CURRENT_PAGE];
    game->ram[MYSMB_ENEMY_Y + slot] = mysmb_area_object_y_position(game);
    game->ram[0x58U + slot] = game->ram[MYSMB_ENEMY_Y + slot];
    game->ram[MYSMB_ENEMY_ID + slot] = 0x32U;
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_FLAG + slot]++;
    game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x67U;
    game->ram[MYSMB_AREA_METATILE_BUFFER + row + 1U] = 0x68U;
}

/* ROM $9aa5/$9aae: both tables are consumed after the control decrement. */
static const mysmb_u8 mysmb_area_staircase_height[9] = {
    7U, 7U, 6U, 5U, 4U, 3U, 2U, 1U, 0U
};
static const mysmb_u8 mysmb_area_staircase_row[9] = {
    3U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U
};

/* ROM $9ab7 StaircaseObject -> $9ac1 NextStair. */
static void mysmb_area_staircase_object(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 second;
    mysmb_u8 index, row, height;

    /* ChkLrgObjLength always decodes the row, including continuation. */
    if (mysmb_area_check_large_length(game, slot, &second) != 0U) {
        game->ram[MYSMB_AREA_STAIRCASE_CONTROL] = 9U;
    }
    /* NextStair: DEC precedes both indexed reads. */
    game->ram[MYSMB_AREA_STAIRCASE_CONTROL]--;
    index = game->ram[MYSMB_AREA_STAIRCASE_CONTROL];
    if (index < 9U) {
        row = mysmb_area_staircase_row[index];
        height = mysmb_area_staircase_height[index];
    } else {
        /* Preserve original adjacent-ROM reads for a nonstandard index;
         * no host out-of-bounds access or invented clamp to the last step. */
        if (game->area_prg == 0 || game->area_prg_size <= 0x1aaeU + index)
            return;
        row = game->area_prg[0x1aaeU + index];
        height = game->area_prg[0x1aa5U + index];
    }
    mysmb_area_render_under_part(game, row, height, 0x61U);
}

/* ROM $98dd VerticalPipeData is shared by vertical and intro pipes. */
static const mysmb_u8 mysmb_area_vertical_pipe_data[8] = {
    0x11U, 0x10U, 0x15U, 0x14U, 0x13U, 0x12U, 0x15U, 0x14U
};

/* ROM $9925-$9938 DrawPipe: restore the saved selector, write the top,
 * then tail-enter UnderPart with the byte-decremented vertical extent. */
static void mysmb_area_draw_pipe(struct mysmb_game *game, mysmb_u8 selector)
{
    mysmb_u8 row, height;

    row = game->ram[7U];
    game->ram[MYSMB_AREA_METATILE_BUFFER + row] =
        mysmb_area_vertical_pipe_data[selector];
    row++;
    height = (mysmb_u8)(game->ram[6U] - 1U);
    mysmb_area_render_under_part(game, row, height,
        mysmb_area_vertical_pipe_data[(mysmb_u8)(selector + 2U)]);
}

static void mysmb_area_apply_parser_object(struct mysmb_game *game,
                                           mysmb_u8 slot,
                                           mysmb_u8 first,
                                           mysmb_u8 second)
{
    static const mysmb_u8 side_pipe_shaft[4] = { 0x15U, 0x14U, 0U, 0U };
    static const mysmb_u8 side_pipe_top[4] = { 0x15U, 0x1eU, 0x1dU, 0x1cU };
    static const mysmb_u8 side_pipe_bottom[4] = { 0x15U, 0x21U, 0x20U, 0x1fU };
    static const mysmb_u8 castle_metatiles[55] = {
        0U,0x45U,0x45U,0x45U,0U, 0U,0x48U,0x47U,0x46U,0U,
        0x45U,0x49U,0x49U,0x49U,0x45U, 0x47U,0x47U,0x4aU,0x47U,0x47U,
        0x47U,0x47U,0x4bU,0x47U,0x47U, 0x49U,0x49U,0x49U,0x49U,0x49U,
        0x47U,0x4aU,0x47U,0x4aU,0x47U, 0x47U,0x4bU,0x47U,0x4bU,0x47U,
        0x47U,0x47U,0x47U,0x47U,0x47U, 0x4aU,0x47U,0x4aU,0x47U,0x4aU,
        0x4bU,0x47U,0x4bU,0x47U,0x4bU
    };
    mysmb_u8 row;
    mysmb_u8 kind;
    mysmb_u8 area_type;
    mysmb_u8 value;
    mysmb_u8 height;
    mysmb_u8 continuation;

    row = (mysmb_u8)(first & 0x0fU);
    kind = (mysmb_u8)((second & 0x70U) >> 4U);
    if (row == 13U) {
        /* Row 13 has a dedicated low-six-bit object table.  Dynamic flag,
         * victory, and warp state remains outside this static renderer. */
        value = (mysmb_u8)(second & 0x3fU);
        if (value == 0U) {
            (void)mysmb_area_check_fixed_length(game, slot, 3U);
            value = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
            if (value > 3U) return;
            if (side_pipe_shaft[value] != 0U) {
                mysmb_area_render_under_part(game, 0U, 8U, side_pipe_shaft[value]);
                for (row = 0U; row < 7U; ++row)
                    game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0U;
                game->ram[MYSMB_AREA_METATILE_BUFFER + 7U] =
                    mysmb_area_vertical_pipe_data[value];
            }
            game->ram[MYSMB_AREA_METATILE_BUFFER + 9U] = side_pipe_top[value];
            game->ram[MYSMB_AREA_METATILE_BUFFER + 10U] = side_pipe_bottom[value];
        }
        else if (value == 1U) {
            game->ram[MYSMB_AREA_METATILE_BUFFER] = 0x24U;
            for (row = 1U; row < 10U; ++row)
                game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x25U;
            game->ram[MYSMB_AREA_METATILE_BUFFER + 10U] = 0x61U;
            mysmb_objects_start_flagpole(game,
                game->ram[MYSMB_AREA_CURRENT_PAGE],
                mysmb_area_object_x_position(game));
        }
        else if (value == 2U) mysmb_area_axe_obj(game);
        else if (value == 3U) mysmb_area_chain_obj(game);
        else if (value == 4U) mysmb_area_castle_bridge_obj(game, slot);
        else if (value == 5U) {
            mysmb_area_scroll_lock_warp(game);
        }
        else if (value == 6U || value == 7U) {
            game->ram[MYSMB_AREA_SCROLL_LOCK] ^= 1U;
        }
        else if (value >= 8U && value <= 10U) {
            mysmb_area_queue_frenzy(game, value);
        }
        return;
    }
    if (row == 14U) {
        if ((second & 0x40U) == 0U) {
            game->ram[MYSMB_AREA_TERRAIN] = (mysmb_u8)(second & 0x0fU);
            game->ram[MYSMB_AREA_BACKGROUND] = (mysmb_u8)((second & 0x30U) >> 4U);
        }
        else {
            value = (mysmb_u8)(second & 0x07U);
            if (value >= 4U) {
                game->ram[MYSMB_AREA_BACKGROUND_COLOR] = value;
                game->ram[MYSMB_AREA_FOREGROUND] = 0U;
            }
            else {
                game->ram[MYSMB_AREA_FOREGROUND] = value;
            }
        }
        return;
    }
    area_type = game->ram[MYSMB_AREA_TYPE];
    if (area_type >= 4U) return;
    /* Rows 12-15 select a different JumpEngine table.  In particular, the
     * two question-block rows use selector 6/7 and must not enter the
     * large-object vertical-pipe family. */
    if (row == 12U && kind == 0U) {
        mysmb_area_hole_empty(game, slot);
        return;
    }
    if (row == 12U && kind == 1U) {
        mysmb_area_pulley_rope(game, slot);
        return;
    }
    if (row == 12U && kind == 5U) {
        (void)mysmb_area_check_large_length(game, slot, &height);
        game->ram[MYSMB_AREA_METATILE_BUFFER + 10U] = 0x86U;
        game->ram[MYSMB_AREA_METATILE_BUFFER + 11U] = 0x87U;
        game->ram[MYSMB_AREA_METATILE_BUFFER + 12U] = 0x87U;
        return;
    }
    if (row == 12U && (kind == 2U || kind == 3U || kind == 4U)) {
        (void)mysmb_area_check_large_length(game, slot, &height);
        row = kind == 2U ? 6U : (kind == 3U ? 7U : 9U);
        game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x0bU;
        if (row < 12U) game->ram[MYSMB_AREA_METATILE_BUFFER + row + 1U] = 0x63U;
        return;
    }
    if (row == 12U && (kind == 6U || kind == 7U)) {
        (void)mysmb_area_check_large_length(game, slot, &height);
        game->ram[MYSMB_AREA_METATILE_BUFFER + (kind == 6U ? 3U : 7U)] = 0xc0U;
        return;
    }
    if (row == 15U && kind == 0U) {
        mysmb_area_endless_rope(game);
        return;
    }
    if (row == 15U && kind == 1U) {
        mysmb_area_balance_platform_rope(game);
        return;
    }
    if (row == 15U && kind == 2U) {
        /* ROM CastleObject: GetLrgObjAttrib returns the second-byte low
         * nibble in Y. The following STY $07 intentionally replaces the row
         * saved by that helper, so the render-buffer index is this nibble. */
        height = mysmb_area_get_large_object_attributes(game, slot);
        game->ram[7U] = height;
        (void)mysmb_area_check_fixed_length(game, slot, 4U);
        value = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
        row = height;
        continuation = 11U;
        do {
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] =
                castle_metatiles[value];
            row++;
            if (continuation == 0U) break;
            value = (mysmb_u8)(value + 5U);
            continuation--;
        } while (row != 11U);
        if (game->ram[MYSMB_AREA_CURRENT_PAGE] == 0U) return;
        value = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
        if (value == 1U || (height == 0U && value == 3U)) {
            game->ram[MYSMB_AREA_METATILE_BUFFER + 10U] = 0x52U;
            return;
        }
        if (value != 2U) return;
        /* ROM GetAreaObjXPosition -> FindEmptyEnemySlot. The source scans
         * slots 0..4 and deliberately continues with slot 5 if all regular
         * slots are occupied. CastleObject then creates StarFlagObject. */
        /* CastleObject calls FindEmptyEnemySlot but intentionally ignores
         * carry: the source continues with slot five when all five regular
         * slots are occupied.  VerticalPipe below takes the same primitive's
         * carry result and branches around its creation path. */
        (void)mysmb_area_find_empty_enemy_slot(game, &value);
        game->ram[MYSMB_ENEMY_X + value] =
            mysmb_area_object_x_position(game);
        game->ram[MYSMB_ENEMY_PAGE + value] =
            game->ram[MYSMB_AREA_CURRENT_PAGE];
        game->ram[MYSMB_ENEMY_Y_HIGH + value] = 1U;
        game->ram[MYSMB_ENEMY_FLAG + value] = 1U;
        game->ram[MYSMB_ENEMY_Y + value] = 0x90U;
        game->ram[MYSMB_ENEMY_ID + value] = 0x31U;
        return;
    }
    if (row == 15U && kind == 3U) {
        mysmb_area_staircase_object(game, slot);
        return;
    }
    if (row == 15U && kind == 4U) {
        (void)mysmb_area_check_fixed_length(game, slot, 3U);
        height = mysmb_area_get_large_object_attributes(game, slot);
        value = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
        if (value > 3U || height < 2U) return;
        height = (mysmb_u8)(height - 1U);
        if (side_pipe_shaft[value] != 0U)
            mysmb_area_render_under_part(game, 0U, (mysmb_u8)(height - 1U),
                                         side_pipe_shaft[value]);
        game->ram[MYSMB_AREA_METATILE_BUFFER + height] = side_pipe_top[value];
        if (height < 12U)
            game->ram[MYSMB_AREA_METATILE_BUFFER + height + 1U] =
                side_pipe_bottom[value];
        return;
    }
    if (row == 15U && kind == 5U) {
        /* FlagBalls_Residual ($3958-$3964) starts at the fixed third
         * metatile row and uses the low nibble as its downward extent. */
        height = mysmb_area_get_large_object_attributes(game, slot);
        mysmb_area_render_under_part(game, 2U, height, 0x6dU);
        return;
    }
    if (kind == 1U) {
        value = game->ram[MYSMB_AREA_STYLE];
        if (value == 0U) {
            mysmb_area_style_ledge(game, slot, value);
            return;
        }
        if (value == 1U) {
            mysmb_area_style_ledge(game, slot, value);
            return;
        }
        if (value == 2U) {
            mysmb_area_bullet_bill_cannon(game);
        }
        return;
    }
    if (kind == 0U) {
        value = (mysmb_u8)(second & 0x0fU);
        if (value <= 2U) mysmb_area_question_block(game);
        else if (value == 3U) mysmb_area_hidden_1up_block(game);
        else if (value == 7U) mysmb_area_brick_with_coins(game);
        else if (value <= 8U) mysmb_area_brick_with_item(game);
        /* ROM WaterPipe ($986f): small-object selector nine does not use
         * its lower nibble as a length.  GetLrgObjAttrib reloads the row,
         * then writes the two water-pipe metatiles at that row and below. */
        else if (value == 9U) {
            (void)mysmb_area_get_large_object_attributes(game, slot);
            row = game->ram[7U];
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x6bU;
            if (row < 12U)
                game->ram[MYSMB_AREA_METATILE_BUFFER + row + 1U] = 0x6cU;
        }
        else if (value == 10U) mysmb_area_empty_block(game);
        else if (value == 11U) mysmb_area_jumpspring(game);
        return;
    }
    if (kind == 4U) {
        mysmb_area_row_of_coins(game, slot);
        return;
    }
    if (kind == 2U || kind == 3U) {
        if (kind == 2U) mysmb_area_row_of_bricks(game, slot);
        else mysmb_area_row_of_solid_blocks(game, slot);
        return;
    }
    if (kind == 7U) {
        (void)mysmb_area_check_fixed_length(game, slot, 1U);
        height = mysmb_area_get_large_object_attributes(game, slot);
        game->ram[6U] = (mysmb_u8)(height & 7U);
        row = game->ram[7U];
        /* GetPipeHeight preserves the three-bit vertical extent separately,
         * then reloads Y from the fixed one-column length slot.  That slot,
         * not the object height, selects the left/right pipe-table entry. */
        value = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
        if ((second & 0x08U) == 0U)
            value = (mysmb_u8)(value + 4U);
        if (value > 5U) return;
        /* ROM VerticalPipe -> WarpPipe spawns once, before DrawPipe, when
         * this is not 1-1 and the fixed two-column object has a free slot. */
        if ((game->ram[MYSMB_AREA_NUMBER] | game->ram[MYSMB_WORLD_NUMBER]) != 0U &&
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] != 0U) {
            mysmb_u8 enemy_slot;
            if (mysmb_area_find_empty_enemy_slot(game, &enemy_slot) != 0U) {
                game->ram[MYSMB_ENEMY_X + enemy_slot] =
                    (mysmb_u8)(mysmb_area_object_x_position(game) + 8U);
                game->ram[MYSMB_ENEMY_PAGE + enemy_slot] = game->ram[MYSMB_AREA_CURRENT_PAGE];
                if (game->ram[MYSMB_ENEMY_X + enemy_slot] < 8U) game->ram[MYSMB_ENEMY_PAGE + enemy_slot]++;
                game->ram[MYSMB_ENEMY_Y_HIGH + enemy_slot] = 1U;
                game->ram[MYSMB_ENEMY_FLAG + enemy_slot] = 1U;
                game->ram[MYSMB_ENEMY_Y + enemy_slot] =
                    mysmb_area_object_y_position(game);
                game->ram[MYSMB_ENEMY_ID + enemy_slot] = 13U;
                mysmb_enemy_init_piranha_plant(game, enemy_slot);
            }
        }
        mysmb_area_draw_pipe(game, value);
        return;
    }
    if (kind == 5U) mysmb_area_column_of_bricks(game);
    else if (kind == 6U) mysmb_area_column_of_solid_blocks(game);
}

mysmb_u8 mysmb_area_process_object_state(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 first;
    mysmb_u8 second;
    mysmb_u8 row;
    mysmb_u8 column;
    mysmb_u8 offset;
    mysmb_u8 dispatch_offset;
    mysmb_u8 object_id;
    mysmb_u16 base;
    mysmb_u16 address;
    mysmb_u8 rerun;
    mysmb_u8 run_object;

    if (game == 0 || game->area_prg == 0 ||
        game->ram[MYSMB_AREA_DATA_HIGH] < 0x80U) return 0U;
    do {
        rerun = 0U;
        slot = 2U;
        for (;;) {
            game->ram[MYSMB_AREA_OBJECT_OFFSET] = slot;
            run_object = 0U;
            /* ProcADLoop clears this byte for every slot. Only the final
             * slot's SetBehind result reaches the ProcessAreaData loopback. */
            rerun = 0U;
            game->ram[MYSMB_AREA_PARSER_BEHIND] = 0U;
            offset = game->ram[MYSMB_AREA_DATA_OFFSET];
            if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] < 0x80U)
                offset = game->ram[MYSMB_AREA_OBJECT_OFFSET_BUFFER + slot];
            base = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_AREA_DATA_HIGH] - 0x80U) << 8U) |
                game->ram[MYSMB_AREA_DATA_LOW]);
            address = (mysmb_u16)(base + offset);
            if (address >= game->area_prg_size) return 0U;
            first = game->area_prg[address];
            /* DecodeAreaData returns through EndAParse on $fd.  The caller
             * still reaches ChkLength for this slot and then continues its
             * descending three-slot ProcADLoop; it is not a ProcessAreaData
             * return. */
            if (first == 0xfdU) {
                if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] < 0x80U)
                    game->ram[MYSMB_AREA_OBJECT_LENGTH + slot]--;
            }
            else {
                /* ProcessAreaData / DecodeAreaData use INY then (AreaData),Y.
                 * Y wraps before pointer addition; $fd never reads this byte. */
                address = (mysmb_u16)(base + (mysmb_u8)(offset + 1U));
                if (address >= game->area_prg_size) return 0U;
                second = game->area_prg[address];
                row = (mysmb_u8)(first & 0x0fU);

                if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U) {
                    if ((second & 0x80U) != 0U &&
                        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] == 0U) {
                        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 1U;
                        game->ram[MYSMB_AREA_OBJECT_PAGE]++;
                    }
                    /* CheckRear skips behind-page records before decoding.
                     * Otherwise ChkRow13 recognizes the loop command before
                     * NormObj/BackColC can reject its page or column. */
                    if (row == 0x0dU && (second & 0x7fU) == 0x4bU &&
                        game->ram[MYSMB_AREA_OBJECT_PAGE] >=
                            game->ram[MYSMB_AREA_CURRENT_PAGE])
                        game->ram[MYSMB_AREA_LOOP_COMMAND]++;
                    if (row == 0x0dU && (second & 0x40U) == 0U &&
                        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] == 0U) {
                        game->ram[MYSMB_AREA_OBJECT_PAGE] = (mysmb_u8)(second & 0x1fU);
                        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 1U;
                        game->ram[MYSMB_AREA_DATA_OFFSET] =
                            (mysmb_u8)(game->ram[MYSMB_AREA_DATA_OFFSET] + 2U);
                        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 0U;
                    }
                    else if (row == 0x0eU &&
                        game->ram[MYSMB_AREA_BACKLOADING] != 0U) {
                    /* Chk1Row14 branches directly to RdyDecode while
                     * backloading. DecodeAreaData then reaches StrAObj even
                     * when this row-14 control object belongs to an earlier
                     * page, so its attributes affect this staging column. */
                    game->ram[MYSMB_AREA_OBJECT_OFFSET_BUFFER + slot] =
                        game->ram[MYSMB_AREA_DATA_OFFSET];
                    game->ram[MYSMB_AREA_DATA_OFFSET] =
                        (mysmb_u8)(game->ram[MYSMB_AREA_DATA_OFFSET] + 2U);
                    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 0U;
                    run_object = 1U;
                    }
                    else if (game->ram[MYSMB_AREA_OBJECT_PAGE] <
                        game->ram[MYSMB_AREA_CURRENT_PAGE]) {
                    game->ram[MYSMB_AREA_PARSER_BEHIND] = 1U;
                    rerun = 1U;
                    game->ram[MYSMB_AREA_DATA_OFFSET] =
                        (mysmb_u8)(game->ram[MYSMB_AREA_DATA_OFFSET] + 2U);
                    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 0U;
                    }
                    else if (game->ram[MYSMB_AREA_OBJECT_PAGE] ==
                        game->ram[MYSMB_AREA_CURRENT_PAGE]) {
                        /* InitRear returns immediately after the first
                         * current-page object ends the preload. It must not
                         * fall through BackColC or advance this object's
                         * cursor. */
                        if (game->ram[MYSMB_AREA_BACKLOADING] != 0U) {
                            game->ram[MYSMB_AREA_BACKLOADING] = 0U;
                            game->ram[MYSMB_AREA_PARSER_BEHIND] = 0U;
                            game->ram[MYSMB_AREA_OBJECT_OFFSET] = 0U;
                            return 1U;
                        }
                        column = (mysmb_u8)(first >> 4U);
                        if (column == game->ram[MYSMB_AREA_CURRENT_COLUMN]) {
                            game->ram[MYSMB_AREA_OBJECT_OFFSET_BUFFER + slot] =
                                game->ram[MYSMB_AREA_DATA_OFFSET];
                            game->ram[MYSMB_AREA_DATA_OFFSET] =
                                (mysmb_u8)(game->ram[MYSMB_AREA_DATA_OFFSET] + 2U);
                            game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 0U;
                            run_object = 1U;
                        }
                    }
                }
                else {
                    /* A resident slot enters DecodeAreaData directly. */
                    if (row == 0x0dU && (second & 0x7fU) == 0x4bU)
                        game->ram[MYSMB_AREA_LOOP_COMMAND]++;
                    run_object = 1U;
                }
                if (run_object != 0U) {
                    /* Preserve DecodeAreaData's two zero-page handoff
                     * registers.  The object renderer has native C
                     * parameters, but the translated shared RAM still owns
                     * the JumpEngine addend ($07) and selected object ID
                     * ($00) at RunAObj. */
                    dispatch_offset = 0U;
                    object_id = 0U;
                    if (row == 0x0fU) {
                        dispatch_offset = 0x10U;
                        object_id = (mysmb_u8)((second & 0x70U) >> 4U);
                    }
                    else if (row == 0x0cU) {
                        dispatch_offset = 0x08U;
                        object_id = (mysmb_u8)((second & 0x70U) >> 4U);
                    }
                    else if (row == 0x0eU) {
                        object_id = 0x2eU;
                    }
                    else if (row == 0x0dU) {
                        dispatch_offset = 0x22U;
                        object_id = (mysmb_u8)(second & 0x3fU);
                    }
                    else if ((second & 0x70U) == 0U) {
                        dispatch_offset = 0x16U;
                        object_id = (mysmb_u8)(second & 0x0fU);
                    }
                    else {
                        object_id = (mysmb_u8)((second & 0x70U) >> 4U);
                        if (object_id == 7U && (second & 0x08U) != 0U)
                            object_id = 0U;
                    }
                    game->ram[0x0007U] = dispatch_offset;
                    game->ram[0x0000U] = object_id;
                    mysmb_area_apply_parser_object(game, slot, first, second);
                    if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] < 0x80U)
                        game->ram[MYSMB_AREA_OBJECT_LENGTH + slot]--;
                }
            }
            if (slot == 0U) break;
            slot--;
        }
    } while (rerun != 0U || game->ram[MYSMB_AREA_BACKLOADING] != 0U);
    return 1U;
}

void mysmb_area_prepare_player_pages(struct mysmb_game *game, mysmb_u8 player_page)
{
    while (game->ram[MYSMB_AREA_CURRENT_PAGE] < player_page) {
        game->ram[MYSMB_AREA_CURRENT_PAGE]++;
        mysmb_area_render_terrain_page(game, game->ram[MYSMB_AREA_CURRENT_PAGE]);
        mysmb_area_refresh_background_page(game, game->ram[MYSMB_AREA_CURRENT_PAGE]);
        if (game->ram[MYSMB_AREA_CURRENT_PAGE] == 1U) {
            mysmb_area_render_initial_objects(game);
        }
        mysmb_area_render_terrain_page(game,
                                       (mysmb_u8)(game->ram[MYSMB_AREA_CURRENT_PAGE] + 1U));
        mysmb_area_refresh_background_page(game,
            (mysmb_u8)(game->ram[MYSMB_AREA_CURRENT_PAGE] + 1U));
    }
}

/* ROM AreaParserCore's pre-play look-ahead is represented here by a
 * side-effect-free scan of the ordered stream.  Only small one-column
 * metatiles plus horizontal brick rows are admitted until the persistent
 * large-object parser arrives;
 * scanning a copy preserves the live stream cursor for the game loop. */
void mysmb_area_render_initial_objects(struct mysmb_game *game)
{
    struct mysmb_game scan;
    struct mysmb_area_source source;
    struct mysmb_area_object object;
    mysmb_u8 count;

    if (game->area_prg == 0) return;
    scan = *game;
    source.prg = game->area_prg;
    source.prg_size = game->area_prg_size;
    count = 0U;
    while (count < 128U && mysmb_area_next_object(&scan, &source, &object) != 0U) {
        count++;
        if (object.page > 1U) break;
        if (object.page == 1U && object.column > 8U) continue;
        mysmb_area_apply_single_block(game, &object);
    }
    mysmb_area_refresh_background_page(game, 0U);
    mysmb_area_refresh_background_page(game, 1U);
}

/* Translation of the selection/control portion of ROM $9508-$958f.
 * Each successful call consumes one two-byte stream entry. */
mysmb_u8 mysmb_area_next_object(struct mysmb_game *game,
                                const struct mysmb_area_source *source,
                                struct mysmb_area_object *object)
{
    mysmb_u16 address;
    mysmb_u8 first;
    mysmb_u8 second;

    if (source == 0 || source->prg == 0 || object == 0 ||
        game->ram[MYSMB_AREA_DATA_HIGH] < 0x80U) {
        return 0U;
    }
    address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_AREA_DATA_HIGH] - 0x80U) << 8) |
                           game->ram[MYSMB_AREA_DATA_LOW]);
    address = (mysmb_u16)(address + game->ram[MYSMB_AREA_DATA_OFFSET]);
    if (address >= source->prg_size || (mysmb_u16)(source->prg_size - address) < 2U) {
        return 0U;
    }
    first = source->prg[address];
    if (first == 0xfdU) {
        return 0U;
    }
    second = source->prg[(mysmb_u16)(address + 1U)];
    if ((second & 0x80U) != 0U && game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] == 0U) {
        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT]++;
        game->ram[MYSMB_AREA_OBJECT_PAGE]++;
    }
    object->first = first;
    object->second = second;
    object->is_page_control = 0U;
    object->is_loop_command = 0U;
    if ((first & 0x0fU) == 0x0dU && (second & 0x40U) == 0U &&
        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] == 0U) {
        game->ram[MYSMB_AREA_OBJECT_PAGE] = (mysmb_u8)(second & 0x1fU);
        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT]++;
        object->is_page_control = 1U;
    }
    object->page = game->ram[MYSMB_AREA_OBJECT_PAGE];
    object->behind_current_page = object->page < game->ram[MYSMB_AREA_CURRENT_PAGE] ? 1U : 0U;
    mysmb_area_decode_object(object);
    game->ram[MYSMB_AREA_PARSER_BEHIND] = object->behind_current_page;
    game->ram[MYSMB_AREA_DATA_OFFSET] =
        (mysmb_u8)(game->ram[MYSMB_AREA_DATA_OFFSET] + 2U);
    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 0U;
    return 1U;
}

/* Translation of ROM DecodeAreaData's object-ID selection, before JumpEngine. */
void mysmb_area_decode_object(struct mysmb_area_object *object)
{
    mysmb_u8 code;

    object->column = (mysmb_u8)(object->first >> 4U);
    object->row = (mysmb_u8)(object->first & 0x0fU);
    object->dispatch_id = 0xffU;
    if (object->row == 0x0dU) {
        if ((object->second & 0x40U) == 0U) {
            object->is_page_control = 1U;
            return;
        }
        code = (mysmb_u8)(object->second & 0x3fU);
        object->is_loop_command = (object->second & 0x7fU) == 0x4bU ? 1U : 0U;
        object->dispatch_id = (mysmb_u8)(code + 0x22U);
        return;
    }
    if (object->row == 0x0eU) {
        object->dispatch_id = 0x2eU;
        return;
    }
    if (object->row == 0x0cU) {
        object->dispatch_id = (mysmb_u8)(((object->second & 0x70U) >> 4U) + 0x08U);
        return;
    }
    if (object->row == 0x0fU) {
        object->dispatch_id = (mysmb_u8)(((object->second & 0x70U) >> 4U) + 0x10U);
        return;
    }
    code = (mysmb_u8)((object->second & 0x70U) >> 4U);
    if (code == 0U) {
        object->dispatch_id = (mysmb_u8)((object->second & 0x0fU) + 0x16U);
    }
    else {
        if (code == 7U && (object->second & 0x08U) != 0U) {
            code = 0U;
        }
        object->dispatch_id = code;
    }
}
