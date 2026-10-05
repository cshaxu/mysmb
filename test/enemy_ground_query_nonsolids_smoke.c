#include "core/world/world.h"
#include "core/objects.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_enemy_terrain terrain;
    static const mysmb_u8 non_solids[5] = {0x26U, 0xc2U, 0xc3U, 0x5fU, 0x60U};
    mysmb_u8 index;

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0xf8U;
    game.ram[0x00cfU] = 0x40U;
    /* $15 adds X=$08 and Y=$18: page carry selects $05d0, row $30. */
    game.ram[0x0600U] = 0x61U;
    if (mysmb_world_query_enemy_under(&game, 0U, &terrain) == 0U ||
        terrain.metatile != 0x61U || terrain.block_address != 0x0600U ||
        terrain.contact_low_nibble != 0U || terrain.block_row_offset != 0x30U)
        return 1;
    for (index = 0U; index < 5U; ++index)
        if (mysmb_world_enemy_metatile_is_non_solid(non_solids[index]) == 0U)
            return 2;
    if (mysmb_world_enemy_metatile_is_non_solid(0U) != 0U ||
        mysmb_world_enemy_metatile_is_non_solid(0x23U) != 0U ||
        mysmb_objects_is_solid_terrain(0x26U) != 0U ||
        mysmb_objects_is_solid_terrain(0x61U) == 0U) return 3;
    return 0;
}
