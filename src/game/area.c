#include "game/area.h"

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
    MYSMB_AREA_BLOCK_COLUMN = 0x06a0U
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
    MYSMB_AREA_BACKGROUND_COLOR = 0x0744U
};

enum {
    MYSMB_AREA_PARSER_BEHIND = 0x0729U,
    MYSMB_AREA_OBJECT_PAGE = 0x072aU,
    MYSMB_AREA_OBJECT_PAGE_SELECT = 0x072bU,
    MYSMB_AREA_DATA_OFFSET = 0x072cU
};

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
    address = (mysmb_u16)(address + 2U);
    game->ram[MYSMB_AREA_DATA_LOW] = (mysmb_u8)address;
    game->ram[MYSMB_AREA_DATA_HIGH] = (mysmb_u8)(0x80U + (address >> 8U));
    return 1U;
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
