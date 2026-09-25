#include "game/world/world.h"

/* ROM BlockBufferCollision: add the X probe with ADC, then use the carry
 * to select the page-local block buffer. */
mysmb_u8 mysmb_world_collision_page(mysmb_u8 page, mysmb_u8 object_x,
                                    mysmb_u8 probed_x)
{
    return (mysmb_u8)(page + (probed_x < object_x ? 1U : 0U));
}

/* ROM $e2a5 BoundBoxCtrlData and $dc71 BoundingBoxCore. */
void mysmb_world_set_bounding_box(struct mysmb_game *game,
                                    mysmb_u16 address, mysmb_u8 control,
                                    mysmb_u8 x, mysmb_u8 y)
{
    static const mysmb_u8 bounds[48] = {
        0x02U, 0x08U, 0x0eU, 0x20U, 0x03U, 0x14U, 0x0dU, 0x20U,
        0x02U, 0x14U, 0x0eU, 0x20U, 0x02U, 0x09U, 0x0eU, 0x15U,
        0x00U, 0x00U, 0x18U, 0x06U, 0x00U, 0x00U, 0x20U, 0x0dU,
        0x00U, 0x00U, 0x30U, 0x0dU, 0x00U, 0x00U, 0x08U, 0x08U,
        0x06U, 0x04U, 0x0aU, 0x08U, 0x03U, 0x0eU, 0x0dU, 0x14U,
        0x00U, 0x02U, 0x10U, 0x15U, 0x04U, 0x04U, 0x0cU, 0x1cU
    };
    mysmb_u8 offset;

    if (control >= 12U) control = 0U;
    offset = (mysmb_u8)(control * 4U);
    game->ram[address] = (mysmb_u8)(x + bounds[offset]);
    game->ram[address + 1U] = (mysmb_u8)(y + bounds[offset + 1U]);
    game->ram[address + 2U] = (mysmb_u8)(x + bounds[offset + 2U]);
    game->ram[address + 3U] = (mysmb_u8)(y + bounds[offset + 3U]);
}

/* ROM $dcf6 PlayerCollisionCore, for same-screen power-up boxes. */
mysmb_u8 mysmb_world_boxes_collide(const struct mysmb_game *game,
                                            mysmb_u16 first, mysmb_u16 second)
{
    mysmb_u8 coordinate;

    /* `first` is the player box (X in PlayerCollisionCore) and `second`
     * is the sprite box (Y).  Preserve the 6502 comparisons, including
     * their intentional one-byte-wrap branches. */
    for (coordinate = 0U; coordinate < 2U; ++coordinate) {
        mysmb_u8 player_upper;
        mysmb_u8 player_lower;
        mysmb_u8 enemy_upper;
        mysmb_u8 enemy_lower;

        player_upper = game->ram[(mysmb_u16)(first + coordinate)];
        player_lower = game->ram[(mysmb_u16)(first + coordinate + 2U)];
        enemy_upper = game->ram[(mysmb_u16)(second + coordinate)];
        enemy_lower = game->ram[(mysmb_u16)(second + coordinate + 2U)];

        if (enemy_upper >= player_upper) {
            /* FirstBoxGreater. */
            if (enemy_upper == player_upper) continue;
            if (enemy_upper < player_lower) continue;
            if (enemy_upper == player_lower) continue;
            if (enemy_upper <= enemy_lower) return 0U;
            if (enemy_lower >= player_upper) continue;
            return 0U;
        }

        if (enemy_upper < player_lower) {
            /* SecondBoxVerticalChk. */
            if (player_lower < player_upper) continue;
            if (enemy_lower >= player_upper) continue;
            return 0U;
        }
        if (enemy_upper == player_lower) continue;
        if (enemy_lower < enemy_upper) continue;
        if (enemy_lower >= player_upper) continue;
        return 0U;
    }
    return 1U;
}