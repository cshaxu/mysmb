#include "core/world/world.h"

static int check_box(const struct mysmb_game *game, mysmb_u16 address,
                     mysmb_u8 left, mysmb_u8 top,
                     mysmb_u8 right, mysmb_u8 bottom)
{
    return game->ram[address] == left &&
           game->ram[(mysmb_u16)(address + 1U)] == top &&
           game->ram[(mysmb_u16)(address + 2U)] == right &&
           game->ram[(mysmb_u16)(address + 3U)] == bottom;
}

int main(void)
{
    static const mysmb_u8 bound_box_ctrl_data[48] = {
        0x02U,0x08U,0x0eU,0x20U,0x03U,0x14U,0x0dU,0x20U,
        0x02U,0x14U,0x0eU,0x20U,0x02U,0x09U,0x0eU,0x15U,
        0x00U,0x00U,0x18U,0x06U,0x00U,0x00U,0x20U,0x0dU,
        0x00U,0x00U,0x30U,0x0dU,0x00U,0x00U,0x08U,0x08U,
        0x06U,0x04U,0x0aU,0x08U,0x03U,0x0eU,0x0dU,0x14U,
        0x00U,0x02U,0x10U,0x15U,0x04U,0x04U,0x0cU,0x1cU
    };
    struct mysmb_game game;
    mysmb_u8 control;
    mysmb_u8 table_offset;

    /* Every BoundBoxCtrlData entry is exercised with source byte wrap. */
    for (control = 0U; control < 12U; ++control) {
        mysmb_game_initialize_memory(&game, 0U);
        table_offset = (mysmb_u8)(control << 2U);
        mysmb_world_set_bounding_box(&game, 0x04c8U, control, 0xf8U, 0xf0U);
        if (!check_box(&game, 0x04c8U,
                       (mysmb_u8)(0xf8U + bound_box_ctrl_data[table_offset]),
                       (mysmb_u8)(0xf0U + bound_box_ctrl_data[table_offset + 1U]),
                       (mysmb_u8)(0xf8U + bound_box_ctrl_data[table_offset + 2U]),
                       (mysmb_u8)(0xf0U + bound_box_ctrl_data[table_offset + 3U])))
            return (int)(control + 1U);
    }

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 1U; game.ram[0x071cU] = 0x90U;
    /* Right half: positive right edge turns both X corners into $ff. */
    mysmb_world_set_bounding_box(&game, 0x04c8U, 7U, 0x10U, 0x40U);
    mysmb_world_clip_bounding_box_to_screen(&game, 0x04c8U, 2U, 0x10U);
    if (!check_box(&game, 0x04c8U, 0xffU, 0x40U, 0xffU, 0x48U)) return 20;

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 1U; game.ram[0x071cU] = 0x90U;
    /* Right half: already negative right edge takes NoOfs unchanged. */
    mysmb_world_set_bounding_box(&game, 0x04c8U, 7U, 0xf8U, 0x40U);
    mysmb_world_clip_bounding_box_to_screen(&game, 0x04c8U, 2U, 0xf8U);
    if (!check_box(&game, 0x04c8U, 0xf8U, 0x40U, 0xffU, 0x48U)) return 21;

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 1U; game.ram[0x071cU] = 0x90U;
    /* Left half: $a0-$ff clips; negative right edge clips as well. */
    mysmb_world_set_bounding_box(&game, 0x04c8U, 7U, 0xf0U, 0x40U);
    mysmb_world_clip_bounding_box_to_screen(&game, 0x04c8U, 1U, 0x80U);
    if (!check_box(&game, 0x04c8U, 0U, 0x40U, 0U, 0x48U)) return 22;

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 1U; game.ram[0x071cU] = 0x90U;
    /* Left half: $80-$9f is the source's no-clip range. */
    mysmb_world_set_bounding_box(&game, 0x04c8U, 7U, 0x90U, 0x40U);
    mysmb_world_clip_bounding_box_to_screen(&game, 0x04c8U, 1U, 0x20U);
    if (!check_box(&game, 0x04c8U, 0x90U, 0x40U, 0x98U, 0x48U)) return 23;
    return 0;
}
