#include "core/area.h"

enum {
    WORLD_OFFSETS = 0x1cb4U, AREA_OFFSETS = 0x1cbcU,
    ENEMY_BASES = 0x1ce0U, ENEMY_LOW = 0x1ce4U, ENEMY_HIGH = 0x1d06U,
    AREA_BASES = 0x1d28U, AREA_LOW = 0x1d2cU, AREA_HIGH = 0x1d4eU
};

/* ROM $9c13-$9c21 FindAreaPointer. WorldAddrOffsets selects one of the
 * eight WorldNAreas aliases inside AreaAddrOffsets. ADC/TAY truncates. */
mysmb_u8 mysmb_area_find_area_pointer(const struct mysmb_game *game,
                                       const struct mysmb_area_source *source,
                                       mysmb_u8 *pointer)
{
    mysmb_u8 index;
    mysmb_u16 address;
    if (source == 0 || source->prg == 0 || pointer == 0) return 0U;
    address = (mysmb_u16)(WORLD_OFFSETS + game->ram[0x75fU]);
    if (address >= source->prg_size) return 0U;
    index = (mysmb_u8)(source->prg[address] + game->ram[0x760U]);
    address = (mysmb_u16)(AREA_OFFSETS + index);
    if (address >= source->prg_size) return 0U;
    *pointer = source->prg[address];
    return 1U;
}

/* ROM $9c09-$9c12 GetAreaType; writes no low-offset cache. */
mysmb_u8 mysmb_area_get_area_type(struct mysmb_game *game, mysmb_u8 pointer)
{
    mysmb_u8 type;
    type = (mysmb_u8)((pointer & 0x60U) >> 5U);
    game->ram[0x74eU] = type;
    return type;
}

/* ROM $9c03-$9c08 LoadAreaPointer, falling through to GetAreaType. */
mysmb_u8 mysmb_area_load_area_pointer(struct mysmb_game *game,
                                      const struct mysmb_area_source *source)
{
    mysmb_u8 pointer;
    if (mysmb_area_find_area_pointer(game, source, &pointer) == 0U) return 0U;
    game->ram[0x750U] = pointer;
    (void)mysmb_area_get_area_type(game, pointer);
    return 1U;
}

/* ROM $9c58-$9cb3: first/second header, StoreFore, StoreStyle and pointer
 * advance. Conditional stores intentionally preserve the other controls. */
mysmb_u8 mysmb_area_parse_header(struct mysmb_game *game,
                                 const struct mysmb_area_source *source)
{
    mysmb_u16 address;
    mysmb_u16 pointer;
    mysmb_u8 first, second, value;
    if (source == 0 || source->prg == 0 || game->ram[0xe8U] < 0x80U) return 0U;
    pointer = (mysmb_u16)(((mysmb_u16)game->ram[0xe8U] << 8U) | game->ram[0xe7U]);
    address = (mysmb_u16)(pointer - 0x8000U);
    if (address >= source->prg_size || (mysmb_u16)(source->prg_size - address) < 2U) return 0U;
    first = source->prg[address];
    value = (mysmb_u8)(first & 7U);
    if (value >= 4U) {
        game->ram[0x744U] = value;
        value = 0U;
    }
    game->ram[0x741U] = value;
    game->ram[0x710U] = (mysmb_u8)((first >> 3U) & 7U);
    game->ram[0x715U] = (mysmb_u8)(first >> 6U);
    second = source->prg[(mysmb_u16)(address + 1U)];
    game->ram[0x727U] = (mysmb_u8)(second & 15U);
    game->ram[0x742U] = (mysmb_u8)((second >> 4U) & 3U);
    value = (mysmb_u8)(second >> 6U);
    if (value == 3U) {
        game->ram[0x743U] = value;
        value = 0U;
    }
    game->ram[0x733U] = value;
    pointer = (mysmb_u16)(pointer + 2U);
    game->ram[0xe7U] = (mysmb_u8)pointer;
    game->ram[0xe8U] = (mysmb_u8)(pointer >> 8U);
    return 1U;
}

/* ROM $9c22-$9cb3 GetAreaDataAddrs. Type and offset derive from AreaPointer
 * on each call, then both tables and the complete header tail are consumed. */
mysmb_u8 mysmb_area_get_data_addresses(struct mysmb_game *game,
                                       const struct mysmb_area_source *source)
{
    mysmb_u8 type, index;
    if (source == 0 || source->prg == 0 || source->prg_size < 0x1d70U) return 0U;
    type = mysmb_area_get_area_type(game, game->ram[0x750U]);
    game->ram[0x74fU] = (mysmb_u8)(game->ram[0x750U] & 0x1fU);
    index = (mysmb_u8)(source->prg[ENEMY_BASES + type] + game->ram[0x74fU]);
    if ((mysmb_u16)(ENEMY_HIGH + index) >= source->prg_size) return 0U;
    game->ram[0xe9U] = source->prg[ENEMY_LOW + index];
    game->ram[0xeaU] = source->prg[ENEMY_HIGH + index];
    index = (mysmb_u8)(source->prg[AREA_BASES + type] + game->ram[0x74fU]);
    if ((mysmb_u16)(AREA_HIGH + index) >= source->prg_size) return 0U;
    game->ram[0xe7U] = source->prg[AREA_LOW + index];
    game->ram[0xe8U] = source->prg[AREA_HIGH + index];
    return mysmb_area_parse_header(game, source);
}
