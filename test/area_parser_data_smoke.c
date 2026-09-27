#include "game/area.h"
#include "game/game.h"
#include "smb1_local_rom.h"

enum {
    BACKGROUND_SCENE_OFFSETS = 0x12f7U,
    BACKGROUND_SCENE_DATA = 0x12faU,
    BACKGROUND_METATILES = 0x138aU,
    FOREGROUND_SCENE_OFFSETS = 0x13aeU,
    FOREGROUND_SCENE_DATA = 0x13b1U,
    TERRAIN_METATILES = 0x13d8U,
    TERRAIN_RENDER_BITS = 0x13dcU,
    BLOCK_BUFFER_LOW_BOUNDS = 0x1504U,
    CURRENT_PAGE = 0x0725U,
    CURRENT_COLUMN = 0x0726U,
    TERRAIN_CONTROL = 0x0727U,
    BLOCK_COLUMN = 0x0720U,
    AREA_TYPE = 0x074eU,
    FOREGROUND_SCENERY = 0x0741U,
    BACKGROUND_SCENERY = 0x0742U,
    CLOUD_OVERRIDE = 0x0743U,
    WORLD_NUMBER = 0x075fU,
    AREA_DATA_HIGH = 0x00e8U,
    BLOCK_BUFFER = 0x0500U
};

/* Independent source-order model of the seven admitted scenery/terrain data
 * labels.  It consumes the owner-local PRG only and checks the shared C
 * renderer's staged collision result; it does not embed ROM data. */
static void expected_column(mysmb_u8 expected[13], mysmb_u8 background,
                            mysmb_u8 foreground, mysmb_u8 page,
                            mysmb_u8 column, mysmb_u8 terrain_control,
                            mysmb_u8 area_type, mysmb_u8 cloud,
                            mysmb_u8 world)
{
    mysmb_u16 source;
    mysmb_u8 index;
    mysmb_u8 scene;
    mysmb_u8 row;
    mysmb_u8 terrain;
    mysmb_u8 bits;
    mysmb_u8 bound;

    for (index = 0U; index < 13U; ++index) expected[index] = 0U;

    if (background != 0U) {
        source = (mysmb_u16)(BACKGROUND_SCENE_DATA +
            (mysmb_u16)(page % 3U) * 16U +
            mysmb_local_prg[(mysmb_u16)(BACKGROUND_SCENE_OFFSETS + background - 1U)] +
            column);
        scene = mysmb_local_prg[source];
        if ((scene & 0x0fU) != 0U) {
            source = (mysmb_u16)(BACKGROUND_METATILES +
                (mysmb_u16)((scene & 0x0fU) - 1U) * 3U);
            row = (mysmb_u8)(scene >> 4U);
            for (index = 0U; index < 3U && row < 11U; ++index, ++row)
                expected[row] = mysmb_local_prg[(mysmb_u16)(source + index)];
        }
    }

    if (foreground != 0U) {
        source = (mysmb_u16)(FOREGROUND_SCENE_DATA +
            mysmb_local_prg[(mysmb_u16)(FOREGROUND_SCENE_OFFSETS + foreground - 1U)]);
        for (index = 0U; index < 13U; ++index) {
            scene = mysmb_local_prg[(mysmb_u16)(source + index)];
            if (scene != 0U) expected[index] = scene;
        }
    }

    terrain = mysmb_local_prg[(mysmb_u16)(TERRAIN_METATILES + area_type)];
    if (area_type == 0U && world == 7U) terrain = 0x62U;
    if (cloud != 0U) terrain = 0x88U;
    for (row = 0U; row < 13U; ++row) {
        bits = mysmb_local_prg[(mysmb_u16)(TERRAIN_RENDER_BITS +
            (mysmb_u16)terrain_control * 2U + (row >> 3U))];
        if (cloud != 0U && row >= 8U) bits &= 0x08U;
        if (area_type == 2U && row == 11U) terrain = 0x54U;
        if ((bits & (mysmb_u8)(1U << (row & 7U))) != 0U)
            expected[row] = terrain;
    }

    for (row = 0U; row < 13U; ++row) {
        bound = (mysmb_u8)(expected[row] >> 6U);
        if (expected[row] < mysmb_local_prg[(mysmb_u16)(BLOCK_BUFFER_LOW_BOUNDS + bound)])
            expected[row] = 0U;
    }
}

static int verify_case(mysmb_u8 background, mysmb_u8 foreground,
                       mysmb_u8 page, mysmb_u8 column,
                       mysmb_u8 terrain_control, mysmb_u8 area_type,
                       mysmb_u8 cloud, mysmb_u8 world)
{
    struct mysmb_game game;
    mysmb_u8 expected[13];
    mysmb_u8 row;

    expected_column(expected, background, foreground, page, column,
                    terrain_control, area_type, cloud, world);
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    game.ram[CURRENT_PAGE] = page;
    game.ram[CURRENT_COLUMN] = column;
    game.ram[TERRAIN_CONTROL] = terrain_control;
    game.ram[BLOCK_COLUMN] = 0U;
    game.ram[AREA_TYPE] = area_type;
    game.ram[FOREGROUND_SCENERY] = foreground;
    game.ram[BACKGROUND_SCENERY] = background;
    game.ram[CLOUD_OVERRIDE] = cloud;
    game.ram[WORLD_NUMBER] = world;
    /* The admitted data chain is tested without claiming ProcessAreaData,
     * whose nonzero-area-pointer path is received by the next S. */
    game.ram[AREA_DATA_HIGH] = 0U;
    if (mysmb_area_render_scenery_terrain_column(&game) == 0U) return 1;
    for (row = 0U; row < 13U; ++row) {
        if (game.ram[(mysmb_u16)(BLOCK_BUFFER + (mysmb_u16)row * 16U)] !=
            expected[row]) return 1;
    }
    return 0;
}

int main(void)
{
    mysmb_u8 background;
    mysmb_u8 foreground;
    mysmb_u8 page;
    mysmb_u8 column;
    mysmb_u8 terrain_control;
    mysmb_u8 area_type;
    mysmb_u8 cloud;

    for (background = 1U; background <= 3U; ++background) {
        for (page = 0U; page < 3U; ++page) {
            for (column = 0U; column < 16U; ++column) {
                if (verify_case(background, 0U, page, column, 0U, 1U,
                                0U, 0U) != 0) return 1;
            }
        }
    }
    for (foreground = 1U; foreground <= 3U; ++foreground) {
        if (verify_case(0U, foreground, 0U, 0U, 0U, 1U, 0U, 0U) != 0)
            return 1;
    }
    for (area_type = 0U; area_type < 4U; ++area_type) {
        for (terrain_control = 0U; terrain_control < 16U; ++terrain_control) {
            for (cloud = 0U; cloud < 2U; ++cloud) {
                if (verify_case(0U, 0U, 0U, 0U, terrain_control, area_type,
                                cloud, 0U) != 0) return 1;
            }
        }
    }
    for (terrain_control = 0U; terrain_control < 16U; ++terrain_control) {
        if (verify_case(0U, 0U, 0U, 0U, terrain_control, 0U, 0U, 7U) != 0)
            return 1;
    }
    return 0;
}
