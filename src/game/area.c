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
