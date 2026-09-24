#include "game/area.h"
#include "game/objects.h"

enum {
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
    MYSMB_AREA_SCROLL_X = 0x073fU,
    MYSMB_AREA_SCROLL_Y = 0x0740U,
    MYSMB_AREA_TIMERS = 0x0780U,
    MYSMB_AREA_DISABLE_SCREEN = 0x0774U,
    MYSMB_AREA_OPER_MODE_TASK = 0x0772U,
    MYSMB_AREA_BLOCK_COLUMN = 0x06a0U,
    MYSMB_AREA_METATILE_LOW = 0x0b08U,
    MYSMB_AREA_METATILE_HIGH = 0x0b0cU,
    MYSMB_AREA_WATER_PALETTE = 0x0ca4U,
    MYSMB_AREA_GROUND_PALETTE = 0x0cc8U,
    MYSMB_AREA_UNDERGROUND_PALETTE = 0x0cecU,
    MYSMB_AREA_CASTLE_PALETTE = 0x0d10U,
    MYSMB_AREA_COLOR_ROTATE_PALETTE = 0x09c3U,
    MYSMB_AREA_PALETTE3_DATA = 0x09d1U,
    MYSMB_AREA_GAME_TEXT = 0x0752U,
    MYSMB_AREA_GAME_TEXT_OFFSETS = 0x07feU,
    MYSMB_AREA_LUIGI_NAME = 0x07e1U,
    MYSMB_AREA_WARP_ZONE_NUMBERS = 0x07f2U,
    MYSMB_AREA_BACKGROUND_COLORS = 0x05cfU,
    MYSMB_AREA_PLAYER_COLORS = 0x05d7U
};

enum {
    MYSMB_AREA_POINTER = 0x0750U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_AREA_LOW_OFFSET = 0x074fU,
    MYSMB_AREA_DATA_LOW = 0x00e7U,
    MYSMB_AREA_DATA_HIGH = 0x00e8U,
    MYSMB_ENEMY_DATA_LOW = 0x00e9U,
    MYSMB_ENEMY_DATA_HIGH = 0x00eaU,
    MYSMB_WORLD_NUMBER = 0x075fU,
    MYSMB_AREA_NUMBER = 0x0760U,
    MYSMB_ROM_WORLD_OFFSETS = 0x1cb4U,
    MYSMB_ROM_AREA_OFFSETS = 0x1cbcU,
    MYSMB_ROM_ENEMY_HIGH_OFFSETS = 0x1ce0U,
    MYSMB_ROM_ENEMY_LOW = 0x1ce4U,
    MYSMB_ROM_ENEMY_HIGH = 0x1d06U,
    MYSMB_ROM_AREA_HIGH_OFFSETS = 0x1d28U,
    MYSMB_ROM_AREA_LOW = 0x1d2cU,
    MYSMB_ROM_AREA_HIGH = 0x1d4eU
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
    MYSMB_AREA_MUSHROOM_HALF_LENGTH = 0x0736U
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

/* Translation of ROM InitializeArea within the $92b0 area task route.
 * Header and stream reads are deliberately owned by the following T3 part. */
void mysmb_area_initialize(struct mysmb_game *game)
{
    mysmb_u8 index;

    mysmb_game_initialize_memory(game, 0x4bU);
    for (index = 0U; index < 0x22U; ++index) {
        game->ram[(mysmb_u16)(MYSMB_AREA_TIMERS + index)] = 0U;
    }
    game->ram[MYSMB_AREA_SCREEN_LEFT_PAGE] = 0U;
    game->ram[MYSMB_AREA_CURRENT_PAGE] = 0U;
    game->ram[MYSMB_AREA_BACKLOADING] = 0U;
    game->ram[MYSMB_AREA_SCREEN_LEFT_X] = 0U;
    game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] = 1U;
    game->ram[MYSMB_AREA_SCREEN_RIGHT_X] = 0U;
    game->ram[MYSMB_AREA_NT_HIGH] = 0x20U;
    game->ram[MYSMB_AREA_NT_LOW] = 0x80U;
    game->ram[MYSMB_AREA_BLOCK_COLUMN] = 0U;
    game->ram[MYSMB_AREA_OBJECT_LENGTH] = 0xffU;
    game->ram[(mysmb_u16)(MYSMB_AREA_OBJECT_LENGTH + 1U)] = 0xffU;
    game->ram[(mysmb_u16)(MYSMB_AREA_OBJECT_LENGTH + 2U)] = 0xffU;
    game->ram[MYSMB_AREA_COLUMN_SETS] = 0x0bU;
    game->ram[MYSMB_AREA_SCROLL_X] = 0U;
    game->ram[MYSMB_AREA_SCROLL_Y] = 0U;
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

    if ((game->ram[MYSMB_AREA_FRAME_COUNTER] & 7U) != 0U) return;
    buffer_offset = game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET];
    if (buffer_offset >= 0x31U || game->area_prg == 0) return;
    area_type = game->ram[MYSMB_AREA_TYPE];
    if (area_type >= 4U || game->area_prg_size <= MYSMB_AREA_PALETTE3_DATA +
        (mysmb_u16)area_type * 4U + 3U) return;
    rotation_offset = game->ram[MYSMB_AREA_COLOR_ROTATE_OFFSET];
    if (rotation_offset >= 6U || game->area_prg_size <=
        MYSMB_AREA_COLOR_ROTATE_PALETTE + rotation_offset) return;
    palette_offset = (mysmb_u8)(area_type * 4U);
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset)] = 0x3fU;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 1U)] = 0x0cU;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 2U)] = 4U;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 3U)] =
        game->area_prg[(mysmb_u16)(MYSMB_AREA_PALETTE3_DATA + palette_offset)];
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 4U)] =
        game->area_prg[(mysmb_u16)(MYSMB_AREA_COLOR_ROTATE_PALETTE + rotation_offset)];
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 5U)] =
        game->area_prg[(mysmb_u16)(MYSMB_AREA_PALETTE3_DATA + palette_offset + 2U)];
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 6U)] =
        game->area_prg[(mysmb_u16)(MYSMB_AREA_PALETTE3_DATA + palette_offset + 3U)];
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + buffer_offset + 7U)] = 0U;
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
    mysmb_u16 source;
    mysmb_u8 offset;

    if (game->area_prg == 0 || game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] != 0U ||
        game->area_prg_size <= MYSMB_AREA_GAME_TEXT_OFFSETS) return 0U;
    source = MYSMB_AREA_GAME_TEXT;
    offset = 0U;
    while (source < MYSMB_AREA_GAME_TEXT_OFFSETS &&
           game->area_prg[source] != 0xffU) {
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset)] =
            game->area_prg[source];
        source++;
        offset++;
    }
    if (source == MYSMB_AREA_GAME_TEXT_OFFSETS || offset == 0U) return 0U;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset)] = 0U;
    game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] = offset;
    return 1U;
}

/* Translation of ROM WriteBottomStatusLine plus PrintStatusBarNumbers. */
mysmb_u8 mysmb_area_queue_bottom_status_line(struct mysmb_game *game)
{
    mysmb_u8 offset;
    mysmb_u8 index;
    mysmb_u8 player;
    mysmb_u8 score_offset;

    if (game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] != 0U) return 0U;
    player = (mysmb_u8)(game->ram[MYSMB_AREA_CURRENT_PLAYER] & 1U);
    offset = 0U;
    game->ram[0x0301U + offset++] = 0x20U;
    game->ram[0x0301U + offset++] = 0x62U;
    game->ram[0x0301U + offset++] = 6U;
    score_offset = offset;
    index = (mysmb_u8)(player != 0U ? 12U : 6U);
    while (index < (mysmb_u8)(player != 0U ? 18U : 12U)) {
        game->ram[0x0301U + offset++] = game->ram[MYSMB_AREA_DISPLAY_DIGITS + index++];
    }
    /* GetSBNybbles reaches UpdateNumber before this route.  Its leading
     * score zero is emitted as blank tile $24 in both initial and live
     * status-bar output. */
    if (game->ram[0x0301U + score_offset] == 0U) {
        game->ram[0x0301U + score_offset] = 0x24U;
    }
    game->ram[0x0301U + offset++] = 0x20U;
    game->ram[0x0301U + offset++] = 0x6dU;
    game->ram[0x0301U + offset++] = 2U;
    /* StatusBarOffset selector 3/4 points at DisplayDigits 22/28. */
    index = (mysmb_u8)(player != 0U ? 28U : 22U);
    game->ram[0x0301U + offset++] = game->ram[MYSMB_AREA_DISPLAY_DIGITS + index++];
    game->ram[0x0301U + offset++] = game->ram[MYSMB_AREA_DISPLAY_DIGITS + index];
    game->ram[0x0301U + offset++] = 0x20U;
    game->ram[0x0301U + offset++] = 0x73U;
    game->ram[0x0301U + offset++] = 3U;
    game->ram[0x0301U + offset++] = (mysmb_u8)(game->ram[MYSMB_AREA_WORLD_NUMBER] + 1U);
    game->ram[0x0301U + offset++] = 0x28U;
    game->ram[0x0301U + offset++] = (mysmb_u8)(game->ram[MYSMB_AREA_LEVEL_NUMBER] + 1U);
    game->ram[0x0301U + offset] = 0U;
    game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] = offset;
    return 1U;
}

/* Translation of RunGameTimer's PrintStatusBarNumbers($a4).  Unlike the
 * initial screen writers, the ROM appends this command to any pending NMI
 * list, then lets the following NMI consume the whole list. */
mysmb_u8 mysmb_area_queue_timer_status(struct mysmb_game *game)
{
    mysmb_u8 offset;

    offset = game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET];
    if (offset > 0xf8U) return 0U;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] = 0x20U;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] = 0x7aU;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] = 3U;
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] =
        game->ram[MYSMB_AREA_GAME_TIMER_DISPLAY];
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] =
        game->ram[MYSMB_AREA_GAME_TIMER_DISPLAY + 1U];
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] =
        game->ram[MYSMB_AREA_GAME_TIMER_DISPLAY + 2U];
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset)] = 0U;
    game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] = offset;
    return 1U;
}

/* Translation of ROM $8ebe-$8ef7 PrintStatusBarNumbers, invoked through
 * StatusBarNybbles $02/$13 by GiveOneCoin and AddToScore.  Unlike the
 * initial status writer, this appends to a command list already waiting for
 * NMI.  The source changes the first score digit to blank after emitting it
 * when it is zero; retain that byte-level rule in the queued command. */
mysmb_u8 mysmb_area_queue_score_coin_status(struct mysmb_game *game)
{
    static const mysmb_u8 status_low[6] = {
        0xf0U, 0x62U, 0x62U, 0x6dU, 0x6dU, 0x7aU
    };
    static const mysmb_u8 status_length[6] = {
        6U, 6U, 6U, 2U, 2U, 3U
    };
    static const mysmb_u8 status_offset[6] = {
        6U, 12U, 18U, 24U, 30U, 36U
    };
    mysmb_u8 player;
    mysmb_u8 coin_selector;
    mysmb_u8 score_selector;
    mysmb_u8 selector;
    mysmb_u8 offset;
    mysmb_u8 digit;
    mysmb_u8 index;

    offset = game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET];
    if (offset > 0xf1U) return 0U;
    player = (mysmb_u8)(game->ram[MYSMB_AREA_CURRENT_PLAYER] & 1U);
    coin_selector = player != 0U ? 4U : 3U;
    score_selector = player != 0U ? 2U : 1U;
    for (index = 0U; index < 2U; ++index) {
        selector = index == 0U ? coin_selector : score_selector;
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] = 0x20U;
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] =
            status_low[selector];
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] =
            status_length[selector];
        digit = (mysmb_u8)(status_offset[selector] - status_length[selector]);
        while (digit < status_offset[selector]) {
            game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset++)] =
                game->ram[(mysmb_u16)(MYSMB_AREA_DISPLAY_DIGITS + digit)];
            digit++;
        }
    }
    if (game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset - 6U)] == 0U) {
        game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset - 6U)] = 0x24U;
    }
    game->ram[(mysmb_u16)(MYSMB_AREA_VRAM_BUFFER1 + offset)] = 0U;
    game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] = offset;
    return 1U;
}

/* Translation of WriteGameText.  The selector chooses a ROM-authored command
 * stream; mutable numbers occupy the exact byte offsets patched by the ROM. */
mysmb_u8 mysmb_area_queue_game_text(struct mysmb_game *game, mysmb_u8 selector)
{
    mysmb_u8 offset_index;
    mysmb_u16 source;
    mysmb_u8 offset;
    mysmb_u8 index;

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
        if (offset <= 21U) return 0U;
        game->ram[MYSMB_AREA_VRAM_BUFFER1 + 8U] =
            (mysmb_u8)(game->ram[0x075aU] + 1U);
        game->ram[MYSMB_AREA_VRAM_BUFFER1 + 19U] =
            (mysmb_u8)(game->ram[MYSMB_AREA_WORLD_NUMBER] + 1U);
        game->ram[MYSMB_AREA_VRAM_BUFFER1 + 21U] =
            (mysmb_u8)(game->ram[MYSMB_AREA_LEVEL_NUMBER] + 1U);
    }
    if ((selector == 2U && game->ram[0x077aU] != 0U &&
         game->ram[MYSMB_AREA_CURRENT_PLAYER] == 0U) ||
        (selector == 3U && game->ram[0x077aU] != 0U &&
         game->ram[MYSMB_AREA_CURRENT_PLAYER] != 0U)) {
        if (offset <= 7U || game->area_prg_size <= MYSMB_AREA_LUIGI_NAME + 4U)
            return 0U;
        for (index = 0U; index < 5U; ++index) {
            game->ram[MYSMB_AREA_VRAM_BUFFER1 + 3U + index] =
                game->area_prg[MYSMB_AREA_LUIGI_NAME + index];
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
    }
    game->ram[MYSMB_AREA_VRAM_BUFFER1_OFFSET] = offset;
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
    static const mysmb_u8 question[3] = { 0xc1U, 0xc0U, 0x5fU };
    static const mysmb_u8 ground_brick[5] = { 0x55U, 0x56U, 0x57U, 0x58U, 0x59U };
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
        value = question[(mysmb_u8)(object->dispatch_id - 0x16U)];
    }
    else if (object->dispatch_id >= 0x1aU && object->dispatch_id <= 0x1eU) {
        value = ground_brick[(mysmb_u8)(object->dispatch_id - 0x1aU)];
        if (game->ram[MYSMB_AREA_TYPE] != 1U) value = (mysmb_u8)(value + 5U);
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

/* ROM $c0f7-$c1f4 ProcessEnemyData through InitNormalEnemy, limited to
 * ordinary enemy IDs.  Special objects retain their dedicated initializers. */
mysmb_u8 mysmb_area_spawn_next_enemy(struct mysmb_game *game,
                                     const struct mysmb_area_source *source)
{
    mysmb_u16 address;
    mysmb_u16 world;
    mysmb_u16 right;
    mysmb_u8 first;
    mysmb_u8 second;
    mysmb_u8 slot;
    mysmb_u8 row;

    if (source == 0 || source->prg == 0 || game->ram[MYSMB_ENEMY_DATA_HIGH] < 0x80U) return 0U;
    address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_ENEMY_DATA_HIGH] - 0x80U) << 8U) |
                          game->ram[MYSMB_ENEMY_DATA_LOW]);
    address = (mysmb_u16)(address + game->ram[MYSMB_ENEMY_DATA_OFFSET]);
    while (address < source->prg_size && source->prg[address] != 0xffU) {
        first = source->prg[address];
        if ((first & 0x0fU) == 0x0fU && game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] == 0U) {
            if ((mysmb_u16)(address + 1U) >= source->prg_size) return 0U;
            game->ram[MYSMB_ENEMY_OBJECT_PAGE] = (mysmb_u8)(source->prg[address + 1U] & 0x3fU);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 1U;
            game->ram[MYSMB_ENEMY_DATA_OFFSET] = (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            address = (mysmb_u16)(address + 2U);
            continue;
        }
        if ((mysmb_u16)(address + 1U) >= source->prg_size) return 0U;
        second = source->prg[address + 1U];
        if ((second & 0x80U) != 0U && game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] == 0U) game->ram[MYSMB_ENEMY_OBJECT_PAGE]++;
        row = (mysmb_u8)(first & 0x0fU);
        if (row >= 0x0eU || ((second & 0x40U) != 0U && game->ram[MYSMB_SECONDARY_HARD] == 0U)) {
            game->ram[MYSMB_ENEMY_DATA_OFFSET] = (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + (row == 0x0eU ? 3U : 2U));
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 0U;
        }
        world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_OBJECT_PAGE] << 8U) | (first & 0xf0U));
        right = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] << 8U) | game->ram[MYSMB_AREA_SCREEN_RIGHT_X]);
        if (world > (mysmb_u16)(right + 0x30U)) return 0U;
        if (world < right) return 0U;
        /* ROM InitEnemyFrenzy routes IDs $12 and $14 to persistent frenzy
         * controllers.  Neither byte denotes an ordinary stream enemy. */
        if ((second & 0x3fU) == 18U || (second & 0x3fU) == 20U) {
            game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = (mysmb_u8)(second & 0x3fU);
            game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 1U;
        }
        for (slot = 0U; slot < 5U && game->ram[MYSMB_ENEMY_FLAG + slot] != 0U; ++slot) {}
        if (slot == 5U) return 0U;
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_OBJECT_PAGE];
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(first & 0xf0U);
        game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
        game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)((row << 4U) + 8U);
        game->ram[MYSMB_ENEMY_ID + slot] = (mysmb_u8)(second & 0x3fU);
        game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
        game->ram[MYSMB_ENEMY_STATE + slot] = game->ram[MYSMB_ENEMY_ID + slot] == 3U ? 1U : 0U;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = game->ram[MYSMB_PRIMARY_HARD] != 0U ? 0xf4U : 0xf8U;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        /* ROM InitHammerBro.  Its independent movement route owns the
         * jump/throw timers after this source-side object initialization. */
        if (game->ram[MYSMB_ENEMY_ID + slot] == 5U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[0x03a2U + slot] = 0U;
            game->ram[0x0796U + slot] =
                game->ram[MYSMB_SECONDARY_HARD] != 0U ? 0x50U : 0x80U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 0x0bU;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 8U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 13U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 1U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
            game->ram[MYSMB_ENEMY_Y_DUMMY + slot] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 0x18U);
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 10U ||
            game->ram[MYSMB_ENEMY_ID + slot] == 11U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_X_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 12U) {
            game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 2U;
            game->ram[MYSMB_ENEMY_Y + slot] = 2U;
            game->ram[0x0796U + slot] = 1U;
            game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 7U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 14U) {
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0xf8U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 15U) {
            game->ram[MYSMB_ENEMY_X_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = (mysmb_u8)(
                game->ram[MYSMB_ENEMY_Y + slot] +
                (game->ram[MYSMB_ENEMY_Y + slot] < 0x80U ? 0x30U : 0xe0U));
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 16U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        /* ROM InitLakitu -> SetupLakitu -> InitHorizFlySwimEnemy/TallBBox2. */
        if (game->ram[MYSMB_ENEMY_ID + slot] == 17U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[0x06d1U] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        /* ROM InitShortFirebar/InitLongFirebar.  The long variant's
         * duplicate slot is OAM-only; its physical balls share this anchor. */
        if (game->ram[MYSMB_ENEMY_ID + slot] >= 27U &&
            game->ram[MYSMB_ENEMY_ID + slot] <= 31U) {
            static const mysmb_u8 spin_speed[5] = { 0x28U, 0x38U, 0x28U, 0x38U, 0x28U };
            static const mysmb_u8 spin_direction[5] = { 0U, 0U, 0x10U, 0x10U, 0U };
            mysmb_u8 old_x = game->ram[MYSMB_ENEMY_X + slot];
            mysmb_u8 index = (mysmb_u8)(game->ram[MYSMB_ENEMY_ID + slot] - 27U);
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_FIREBAR_SPIN_SPEED + slot] = spin_speed[index];
            game->ram[MYSMB_FIREBAR_SPIN_DIRECTION + slot] = spin_direction[index];
            game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + 4U);
            game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + 4U);
            if (game->ram[MYSMB_ENEMY_X + slot] < old_x) game->ram[MYSMB_ENEMY_PAGE + slot]++;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        /* ROM InitBalPlatform through InitSmallPlatform.  The drawing-only
         * rope partner is absent; each physical deck keeps its 6502 state. */
        if (game->ram[MYSMB_ENEMY_ID + slot] >= 36U &&
            game->ram[MYSMB_ENEMY_ID + slot] <= 44U) {
            mysmb_u8 platform_id;
            mysmb_u8 old_x;

            platform_id = game->ram[MYSMB_ENEMY_ID + slot];
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = 0U;
            game->ram[MYSMB_ENEMY_X_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] =
                (platform_id == 43U || platform_id == 44U) ? 4U : 5U;
            if (platform_id != 43U && platform_id != 44U &&
                game->ram[MYSMB_AREA_TYPE] != 3U &&
                game->ram[MYSMB_SECONDARY_HARD] == 0U) {
                game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 6U;
            }
            if (platform_id == 38U || platform_id == 39U) {
                game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 5U;
            }
            if (platform_id == 36U) {
                old_x = game->ram[MYSMB_ENEMY_X + slot];
                game->ram[MYSMB_ENEMY_Y + slot] =
                    (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
                if (game->ram[MYSMB_SECONDARY_HARD] == 0U) {
                    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x - 8U);
                    if (old_x < 8U) game->ram[MYSMB_ENEMY_PAGE + slot]--;
                    old_x = game->ram[MYSMB_ENEMY_X + slot];
                }
                game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + 8U);
                if (game->ram[MYSMB_ENEMY_X + slot] < old_x) game->ram[MYSMB_ENEMY_PAGE + slot]++;
                game->ram[MYSMB_ENEMY_STATE + slot] = game->ram[MYSMB_BALANCE_PLATFORM_ALIGNMENT];
                game->ram[MYSMB_BALANCE_PLATFORM_ALIGNMENT] =
                    game->ram[MYSMB_BALANCE_PLATFORM_ALIGNMENT] >= 0x80U ? slot : 0xffU;
                game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 0U;
            }
            else if (platform_id == 37U) {
                game->ram[MYSMB_PLATFORM_TOP_Y + slot] = game->ram[MYSMB_ENEMY_Y + slot];
                game->ram[MYSMB_PLATFORM_CENTER_Y + slot] =
                    (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + 0x40U);
                if (game->ram[MYSMB_ENEMY_Y + slot] >= 0x80U) {
                    game->ram[MYSMB_ENEMY_Y + slot] = 0xc0U;
                }
            }
            else if (platform_id == 38U || platform_id == 43U) {
                game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0x10U;
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xffU;
            }
            else if (platform_id == 39U || platform_id == 44U) {
                game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0xf0U;
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            }
            else if (platform_id == 40U || platform_id == 42U) {
                game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0x10U;
                game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
            }
            else if (platform_id == 41U) {
                game->ram[MYSMB_PLATFORM_COLLISION_FLAG + slot] = 0xffU;
            }
        }
        /* ROM InitBowser, excluding its OAM-only duplicate rear half. */
        if (game->ram[MYSMB_ENEMY_ID + slot] == 45U) {
            game->ram[MYSMB_BOWSER_BODY_CONTROLS] = 0U;
            game->ram[MYSMB_BOWSER_ORIGIN_X] = game->ram[MYSMB_ENEMY_X + slot];
            game->ram[MYSMB_BOWSER_FLAME_TIMER] = 0U;
            game->ram[MYSMB_BOWSER_BREATH_TIMER] = 0xdfU;
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 0xdfU;
            game->ram[MYSMB_BOWSER_FEET_TIMER] = 0x20U;
            game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] = 0x20U;
            game->ram[MYSMB_BOWSER_HIT_POINTS] = 5U;
            game->ram[MYSMB_BOWSER_MOVE_SPEED] = 2U;
            game->ram[MYSMB_BOWSER_FRONT_SLOT] = slot;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 10U;
        }
        game->ram[MYSMB_ENEMY_DATA_OFFSET] = (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
        game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
        return 1U;
    }
    return 0U;
}

/* Translation of ROM $9c03-$9c2b (LoadAreaPointer/GetAreaDataAddrs).
 * ROM CPU addresses are converted to NROM PRG offsets at this owner boundary. */
mysmb_u8 mysmb_area_load_pointers(struct mysmb_game *game,
                                  const struct mysmb_area_source *source)
{
    mysmb_u16 table_index;
    mysmb_u8 area_pointer;
    mysmb_u8 area_type;

    if (source == 0 || source->prg == 0 || source->prg_size < 0x1d70U ||
        game->ram[MYSMB_WORLD_NUMBER] >= 8U) {
        return 0U;
    }
    table_index = (mysmb_u16)(source->prg[(mysmb_u16)(MYSMB_ROM_WORLD_OFFSETS +
                                                       game->ram[MYSMB_WORLD_NUMBER])] +
                               game->ram[MYSMB_AREA_NUMBER]);
    if (table_index >= 0x0041U) {
        return 0U;
    }
    area_pointer = source->prg[(mysmb_u16)(MYSMB_ROM_AREA_OFFSETS + table_index)];
    area_type = (mysmb_u8)((area_pointer & 0x60U) >> 5U);
    table_index = (mysmb_u16)(source->prg[(mysmb_u16)(MYSMB_ROM_ENEMY_HIGH_OFFSETS +
                                                       area_type)] +
                               (area_pointer & 0x1fU));
    if (table_index >= 0x0022U) {
        return 0U;
    }
    game->ram[MYSMB_AREA_POINTER] = area_pointer;
    game->ram[MYSMB_AREA_TYPE] = area_type;
    game->ram[MYSMB_AREA_LOW_OFFSET] = (mysmb_u8)(area_pointer & 0x1fU);
    game->ram[MYSMB_ENEMY_DATA_LOW] = source->prg[(mysmb_u16)(MYSMB_ROM_ENEMY_LOW + table_index)];
    game->ram[MYSMB_ENEMY_DATA_HIGH] = source->prg[(mysmb_u16)(MYSMB_ROM_ENEMY_HIGH + table_index)];
    table_index = (mysmb_u16)(source->prg[(mysmb_u16)(MYSMB_ROM_AREA_HIGH_OFFSETS +
                                                       area_type)] +
                               game->ram[MYSMB_AREA_LOW_OFFSET]);
    if (table_index >= 0x0022U) {
        return 0U;
    }
    game->ram[MYSMB_AREA_DATA_LOW] = source->prg[(mysmb_u16)(MYSMB_ROM_AREA_LOW + table_index)];
    game->ram[MYSMB_AREA_DATA_HIGH] = source->prg[(mysmb_u16)(MYSMB_ROM_AREA_HIGH + table_index)];
    return 1U;
}

/* Translation of the area-header tail of ROM $9c1c-$9c4a. */
mysmb_u8 mysmb_area_parse_header(struct mysmb_game *game,
                                 const struct mysmb_area_source *source)
{
    mysmb_u16 address;
    mysmb_u8 first;
    mysmb_u8 second;
    mysmb_u8 value;

    if (source == 0 || source->prg == 0 || game->ram[MYSMB_AREA_DATA_HIGH] < 0x80U) {
        return 0U;
    }
    address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_AREA_DATA_HIGH] - 0x80U) << 8) |
                           game->ram[MYSMB_AREA_DATA_LOW]);
    if (address >= source->prg_size || (mysmb_u16)(source->prg_size - address) < 2U) {
        return 0U;
    }
    first = source->prg[address];
    second = source->prg[(mysmb_u16)(address + 1U)];
    value = (mysmb_u8)(first & 0x07U);
    game->ram[MYSMB_AREA_BACKGROUND_COLOR] = value >= 4U ? value : 0U;
    game->ram[MYSMB_AREA_FOREGROUND] = value < 4U ? value : 0U;
    game->ram[MYSMB_AREA_ENTRANCE] = (mysmb_u8)((first & 0x38U) >> 3U);
    game->ram[MYSMB_AREA_TIMER_SETTING] = (mysmb_u8)(first >> 6U);
    game->ram[MYSMB_AREA_TERRAIN] = (mysmb_u8)(second & 0x0fU);
    game->ram[MYSMB_AREA_BACKGROUND] = (mysmb_u8)((second & 0x30U) >> 4U);
    value = (mysmb_u8)(second >> 6U);
    game->ram[MYSMB_AREA_CLOUD_OVERRIDE] = value == 3U ? value : 0U;
    game->ram[MYSMB_AREA_STYLE] = value == 3U ? 0U : value;
    (void)mysmb_area_apply_palette(game, game->ram[MYSMB_AREA_TYPE]);
    address = (mysmb_u16)(address + 2U);
    game->ram[MYSMB_AREA_DATA_LOW] = (mysmb_u8)address;
    game->ram[MYSMB_AREA_DATA_HIGH] = (mysmb_u8)(0x80U + (address >> 8U));
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
    for (index = 0U; index < 13U; ++index) metatiles[index] = 0U;

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

    column = (mysmb_u8)(game->ram[MYSMB_AREA_BLOCK_COLUMN] & 0x1fU);
    address = (mysmb_u16)(column < 16U ? 0x0500U + column :
                          0x05d0U + (column - 16U));
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
static mysmb_u8 mysmb_area_queue_graphics_column(struct mysmb_game *game)
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
static mysmb_u8 mysmb_area_queue_attribute_tables(struct mysmb_game *game)
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
        if (mysmb_area_queue_graphics_column(game) == 0U) return 0U;
    }
    else if (mysmb_area_render_scenery_terrain_column(game) == 0U) {
        return 0U;
    }
    game->ram[MYSMB_AREA_PARSER_TASK] = task;
    if (task == 0U) return mysmb_area_queue_attribute_tables(game);
    return 1U;
}

/* ROM $86e6-$86ff AreaParserTaskControl.  One call completes exactly the
 * eight task slots that produce a two-column set; NMI owns its later transfer. */
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
    game->ram[MYSMB_AREA_VRAM_ADDRESS_CONTROL] = 6U;
    return (game->ram[MYSMB_AREA_COLUMN_SETS] & 0x80U) != 0U ? 1U : 0U;
}

/* Translation of the stream/slot-control part of ROM $9508-$958f
 * ProcessAreaData. It intentionally stops before JumpEngine: each object
 * family must own its own metatile writes. The result is the original three
 * slot state ($072d/$0730), page selector, and stream offset. */
/* ROM $4247-$4273 RenderUnderPart.  A foreground object may fill downward,
 * but the source preserves ledge centers, palette-three objects, and the
 * mushroom stem/top interaction in the metatile staging column. */
static void mysmb_area_render_under_part(struct mysmb_game *game,
                                         mysmb_u8 row,
                                         mysmb_u8 height,
                                         mysmb_u8 metatile)
{
    mysmb_u8 existing;

    do {
        existing = game->ram[MYSMB_AREA_METATILE_BUFFER + row];
        if (existing == 0U || existing == 0xc0U ||
            (existing != 0x17U && existing != 0x1aU && existing < 0xc0U &&
             (existing != 0x54U || metatile != 0x50U))) {
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = metatile;
        }
        if (row == 12U || height == 0U) break;
        row++;
        height--;
    } while (1);
}

/* ROM $4014-$4091 static object handlers. The caller has already admitted the
 * object to a persistent parser slot and filled the terrain column; these
 * handlers overwrite only its selected metatile rows. */
static void mysmb_area_apply_parser_object(struct mysmb_game *game,
                                           mysmb_u8 slot,
                                           mysmb_u8 first,
                                           mysmb_u8 second)
{
    static const mysmb_u8 brick[5] = { 0x22U, 0x51U, 0x52U, 0x52U, 0x88U };
    static const mysmb_u8 solid[4] = { 0x69U, 0x61U, 0x61U, 0x62U };
    static const mysmb_u8 coin[4] = { 0xc3U, 0xc2U, 0xc2U, 0xc2U };
    static const mysmb_u8 question[3] = { 0xc1U, 0xc0U, 0x5fU };
    static const mysmb_u8 block[10] = {
        0U, 0U, 0U, 0U, 0x55U, 0x56U, 0x57U, 0x58U, 0x59U, 0U
    };
    static const mysmb_u8 pipe[8] = {
        0x11U, 0x10U, 0x15U, 0x14U, 0x13U, 0x12U, 0x15U, 0x14U
    };
    static const mysmb_u8 hole[4] = { 0x87U, 0U, 0U, 0U };
    static const mysmb_u8 staircase_row[9] = {
        3U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U
    };
    static const mysmb_u8 staircase_height[9] = {
        7U, 7U, 6U, 5U, 4U, 3U, 2U, 1U, 0U
    };
    static const mysmb_u8 side_pipe_shaft[4] = { 0x15U, 0x14U, 0U, 0U };
    static const mysmb_u8 side_pipe_top[4] = { 0x15U, 0x1eU, 0x1dU, 0x1cU };
    static const mysmb_u8 side_pipe_bottom[4] = { 0x15U, 0x21U, 0x20U, 0x1fU };
    mysmb_u8 row;
    mysmb_u8 kind;
    mysmb_u8 area_type;
    mysmb_u8 value;
    mysmb_u8 height;

    row = (mysmb_u8)(first & 0x0fU);
    kind = (mysmb_u8)((second & 0x70U) >> 4U);
    if (row == 13U) {
        /* Row 13 has a dedicated low-six-bit object table.  Dynamic flag,
         * victory, and warp state remains outside this static renderer. */
        value = (mysmb_u8)(second & 0x3fU);
        if (value == 0U) {
            if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
                game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = 3U;
            value = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
            if (value > 3U) return;
            if (side_pipe_shaft[value] != 0U) {
                mysmb_area_render_under_part(game, 0U, 8U, side_pipe_shaft[value]);
                for (row = 0U; row < 7U; ++row)
                    game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0U;
                game->ram[MYSMB_AREA_METATILE_BUFFER + 7U] = pipe[value];
            }
            game->ram[MYSMB_AREA_METATILE_BUFFER + 9U] = side_pipe_top[value];
            game->ram[MYSMB_AREA_METATILE_BUFFER + 10U] = side_pipe_bottom[value];
        }
        else if (value == 1U) {
            game->ram[MYSMB_AREA_METATILE_BUFFER] = 0x24U;
            for (row = 1U; row < 10U; ++row)
                game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x25U;
            game->ram[MYSMB_AREA_METATILE_BUFFER + 10U] = 0x61U;
        }
        else if (value >= 2U && value <= 4U) {
            if (value == 4U && game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
                game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = 12U;
            if (value == 2U) game->ram[MYSMB_AREA_VRAM_ADDRESS_CONTROL] = 8U;
            row = value == 2U ? 6U : (value == 3U ? 7U : 8U);
            height = value == 2U ? 0xc5U : (value == 3U ? 0x0cU : 0x89U);
            mysmb_area_render_under_part(game, row, 0U, height);
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
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
        for (row = 8U; row < 13U; ++row)
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = hole[area_type];
        return;
    }
    if (row == 12U && kind == 1U) {
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U) {
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
            game->ram[MYSMB_AREA_METATILE_BUFFER] = 0x42U;
        }
        else if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] == 0U) {
            game->ram[MYSMB_AREA_METATILE_BUFFER] = 0x43U;
        }
        else {
            game->ram[MYSMB_AREA_METATILE_BUFFER] = 0x41U;
        }
        return;
    }
    if (row == 12U && kind == 5U) {
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
        game->ram[MYSMB_AREA_METATILE_BUFFER + 10U] = 0x86U;
        game->ram[MYSMB_AREA_METATILE_BUFFER + 11U] = 0x87U;
        game->ram[MYSMB_AREA_METATILE_BUFFER + 12U] = 0x87U;
        return;
    }
    if (row == 12U && (kind == 2U || kind == 3U || kind == 4U)) {
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
        row = kind == 2U ? 6U : (kind == 3U ? 7U : 9U);
        game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x0bU;
        if (row < 12U) game->ram[MYSMB_AREA_METATILE_BUFFER + row + 1U] = 0x63U;
        return;
    }
    if (row == 12U && (kind == 6U || kind == 7U)) {
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
        game->ram[MYSMB_AREA_METATILE_BUFFER + (kind == 6U ? 3U : 7U)] = 0xc0U;
        return;
    }
    if (row == 15U && kind == 0U) {
        for (row = 0U; row < 13U; ++row)
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x40U;
        return;
    }
    if (row == 15U && kind == 1U) {
        height = (mysmb_u8)(second & 0x0fU);
        for (row = 1U; row < 13U; ++row)
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x44U;
        row = 1U;
        do {
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x40U;
            if (row == 12U || height == 0U) break;
            row++;
            height--;
        } while (1);
        return;
    }
    if (row == 15U && kind == 3U) {
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U) {
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
            game->ram[MYSMB_AREA_STAIRCASE_CONTROL] = 9U;
        }
        game->ram[MYSMB_AREA_STAIRCASE_CONTROL]--;
        value = game->ram[MYSMB_AREA_STAIRCASE_CONTROL];
        if (value >= 9U) return;
        row = staircase_row[value];
        height = staircase_height[value];
        do {
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x61U;
            if (row == 12U || height == 0U) break;
            row++;
            height--;
        } while (1);
        return;
    }
    if (row == 15U && kind == 4U) {
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = 3U;
        value = game->ram[MYSMB_AREA_OBJECT_LENGTH + slot];
        height = (mysmb_u8)(second & 0x0fU);
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
        mysmb_area_render_under_part(game, 2U, (mysmb_u8)(second & 0x0fU), 0x6dU);
        return;
    }
    if (kind == 1U) {
        value = game->ram[MYSMB_AREA_STYLE];
        if (value == 0U) {
            if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U) {
                game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
                game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x16U;
            }
            else if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] == 0U) {
                game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x18U;
            }
            else {
                game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x17U;
                if (row < 12U) game->ram[MYSMB_AREA_METATILE_BUFFER + row + 1U] = 0x4cU;
            }
            return;
        }
        if (value == 1U) {
            if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U) {
                game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
                game->ram[MYSMB_AREA_MUSHROOM_HALF_LENGTH + slot] =
                    (mysmb_u8)(game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >> 1U);
                game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x19U;
            }
            else if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] == 0U) {
                game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x1bU;
            }
            else {
                game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x1aU;
                if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] ==
                    game->ram[MYSMB_AREA_MUSHROOM_HALF_LENGTH + slot] && row < 11U) {
                    game->ram[MYSMB_AREA_METATILE_BUFFER + row + 1U] = 0x4fU;
                    game->ram[MYSMB_AREA_METATILE_BUFFER + row + 2U] = 0x50U;
                }
            }
            return;
        }
        if (value == 2U) {
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x64U;
            if (row < 12U) game->ram[MYSMB_AREA_METATILE_BUFFER + row + 1U] = 0x65U;
            if (row < 11U) game->ram[MYSMB_AREA_METATILE_BUFFER + row + 2U] = 0x66U;
        }
        return;
    }
    if (kind == 0U) {
        value = (mysmb_u8)(second & 0x0fU);
        if (value <= 2U) game->ram[MYSMB_AREA_METATILE_BUFFER + row] = question[value];
        else if (value >= 4U && value <= 8U) {
            value = block[value];
            if (area_type != 1U) value = (mysmb_u8)(value + 5U);
            game->ram[MYSMB_AREA_METATILE_BUFFER + row] = value;
        }
        else if (value == 10U) game->ram[MYSMB_AREA_METATILE_BUFFER + row] = 0x60U;
        return;
    }
    if (kind == 2U || kind == 3U || kind == 4U) {
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = (mysmb_u8)(second & 0x0fU);
        if (kind == 2U && game->ram[MYSMB_AREA_CLOUD_OVERRIDE] != 0U)
            area_type = 4U;
        if (kind == 2U) game->ram[MYSMB_AREA_METATILE_BUFFER + row] = brick[area_type];
        else if (kind == 3U) game->ram[MYSMB_AREA_METATILE_BUFFER + row] = solid[area_type];
        else game->ram[MYSMB_AREA_METATILE_BUFFER + row] = coin[area_type];
        return;
    }
    if (kind == 7U) {
        if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U)
            game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] = 1U;
        value = (mysmb_u8)(second & 0x07U);
        if ((second & 0x08U) == 0U) value = (mysmb_u8)(value + 4U);
        if (value > 5U) return;
        game->ram[MYSMB_AREA_METATILE_BUFFER + row] = pipe[value];
        if (row == 12U) return;
        row++;
        value = pipe[(mysmb_u8)(value + 2U)];
        height = (mysmb_u8)(second & 0x07U);
        if (height == 0U) height = (mysmb_u8)(12U - row);
        else height--;
        mysmb_area_render_under_part(game, row, height, value);
        return;
    }
    if (kind != 5U && kind != 6U) return;
    value = kind == 5U ? brick[area_type] : solid[area_type];
    height = (mysmb_u8)(second & 0x0fU);
    mysmb_area_render_under_part(game, row, height, value);
}

mysmb_u8 mysmb_area_process_object_state(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 first;
    mysmb_u8 second;
    mysmb_u8 row;
    mysmb_u8 column;
    mysmb_u8 offset;
    mysmb_u16 address;
    mysmb_u8 rerun;
    mysmb_u8 passes;
    mysmb_u8 run_object;

    if (game == 0 || game->area_prg == 0 ||
        game->ram[MYSMB_AREA_DATA_HIGH] < 0x80U) return 0U;
    passes = 0U;
    do {
        rerun = 0U;
        slot = 2U;
        for (;;) {
            run_object = 0U;
            game->ram[MYSMB_AREA_PARSER_BEHIND] = 0U;
            offset = game->ram[MYSMB_AREA_DATA_OFFSET];
            if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] < 0x80U)
                offset = game->ram[MYSMB_AREA_OBJECT_OFFSET_BUFFER + slot];
            address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_AREA_DATA_HIGH] - 0x80U) << 8U) |
                game->ram[MYSMB_AREA_DATA_LOW]);
            address = (mysmb_u16)(address + offset);
            if (address >= game->area_prg_size ||
                (mysmb_u16)(game->area_prg_size - address) < 2U) return 0U;
            first = game->area_prg[address];
            if (first == 0xfdU) return 1U;
            second = game->area_prg[(mysmb_u16)(address + 1U)];
            row = (mysmb_u8)(first & 0x0fU);

            if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] >= 0x80U) {
                if ((second & 0x80U) != 0U &&
                    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] == 0U) {
                    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 1U;
                    game->ram[MYSMB_AREA_OBJECT_PAGE]++;
                }
                if (row == 0x0dU && (second & 0x40U) == 0U &&
                    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] == 0U) {
                    game->ram[MYSMB_AREA_OBJECT_PAGE] = (mysmb_u8)(second & 0x1fU);
                    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 1U;
                    game->ram[MYSMB_AREA_DATA_OFFSET] =
                        (mysmb_u8)(game->ram[MYSMB_AREA_DATA_OFFSET] + 2U);
                    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 0U;
                }
                else if ((row != 0x0eU || game->ram[MYSMB_AREA_BACKLOADING] == 0U) &&
                    game->ram[MYSMB_AREA_OBJECT_PAGE] < game->ram[MYSMB_AREA_CURRENT_PAGE]) {
                    game->ram[MYSMB_AREA_PARSER_BEHIND] = 1U;
                    rerun = 1U;
                    game->ram[MYSMB_AREA_DATA_OFFSET] =
                        (mysmb_u8)(game->ram[MYSMB_AREA_DATA_OFFSET] + 2U);
                    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 0U;
                }
                else if (game->ram[MYSMB_AREA_OBJECT_PAGE] ==
                    game->ram[MYSMB_AREA_CURRENT_PAGE]) {
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
                run_object = 1U;
            }
            if (run_object != 0U) {
                mysmb_area_apply_parser_object(game, slot, first, second);
                if (game->ram[MYSMB_AREA_OBJECT_LENGTH + slot] < 0x80U)
                    game->ram[MYSMB_AREA_OBJECT_LENGTH + slot]--;
            }
            if (slot == 0U) break;
            slot--;
        }
        passes++;
    } while (rerun != 0U && passes != 0xffU);
    return rerun == 0U ? 1U : 0U;
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
