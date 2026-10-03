#include "game/enemy/platform.h"
#include "game/enemy/core.h"
#include "game/objects.h"
#include "game/oam/oam.h"

/* Shared existing offscreen child seam; source scratch remains child-owned. */
void mysmb_platform_get_offscreen(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
}

/* ROM $C982 LargePlatformSubroutines, valid IDs $24-$2A. */
void mysmb_platform_movement_dispatch(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u16 targets[7] = {
        0xd432U,0xd5d3U,0xd64fU,0xd64fU,0xd607U,0xd631U,0xd63dU
    };
    mysmb_u8 id;
    mysmb_u16 target;
    id = (mysmb_u8)(game->ram[0x16U + slot] - 0x24U);
    target = targets[id];
    game->ram[4U] = 0x89U;game->ram[5U] = 0xc9U;
    game->ram[6U] = (mysmb_u8)target;game->ram[7U] = (mysmb_u8)(target >> 8U);
    switch (id) {
    case 0U: mysmb_platform_move_balance(game, slot); break;
    case 1U: mysmb_platform_move_y(game, slot); break;
    case 2U: case 3U: mysmb_platform_move_large_lift(game, slot); break;
    case 4U: mysmb_platform_move_x(game, slot); break;
    case 5U: mysmb_platform_move_drop(game, slot); break;
    case 6U: mysmb_platform_move_right(game, slot); break;
    }
}

/* ROM $C94D RunSmallPlatform: drawing precedes movement. */
void mysmb_enemy_run_small_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_platform_box_small(game, slot);
    mysmb_platform_collision_small(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_objects_draw_small_platform(game, slot);
    mysmb_platform_move_small(game, slot);
    mysmb_objects_check_enemy_offscreen_bounds(game, slot);
}

/* ROM $C965 RunLargePlatform / $C979 SkipPT: movement precedes drawing. */
void mysmb_enemy_run_large_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_platform_box_large(game, slot);
    mysmb_platform_collision_large(game, slot);
    if (game->ram[0x747U] == 0U) mysmb_platform_movement_dispatch(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_objects_draw_large_platform(game, slot);
    mysmb_objects_check_enemy_offscreen_bounds(game, slot);
}
