#include "core/world/world.h"

/* ROM $e325 PlayerCollisionCore through $e387 CollisionFound return.
 * `first` and `second` are BoundingBox_UL_Corner addresses.  The original
 * enters X/Y as offsets from $04ac; preserve its two scratch bytes after
 * every terminal path as well as its carry-equivalent return value. */
mysmb_u8 mysmb_world_boxes_collide(struct mysmb_game *game,
                                   mysmb_u16 first, mysmb_u16 second)
{
    mysmb_u8 second_offset;
    mysmb_u8 counter;
    mysmb_u8 coordinate;
    mysmb_u8 first_upper;
    mysmb_u8 first_lower;
    mysmb_u8 second_upper;
    mysmb_u8 second_lower;

    second_offset = (mysmb_u8)(second - 0x04acU);
    game->ram[0x0006U] = second_offset;
    game->ram[0x0007U] = 1U;
    counter = 1U;
    coordinate = 0U;

    for (;;) {
        first_upper = game->ram[(mysmb_u16)(first + coordinate)];
        first_lower = game->ram[(mysmb_u16)(first + coordinate + 2U)];
        second_upper = game->ram[(mysmb_u16)(second + coordinate)];
        second_lower = game->ram[(mysmb_u16)(second + coordinate + 2U)];

        if (second_upper >= first_upper) {
            /* FirstBoxGreater. */
            if (second_upper == first_upper) goto collision_found;
            if (second_upper < first_lower) goto collision_found;
            if (second_upper == first_lower) goto collision_found;
            if (second_upper <= second_lower) goto no_collision_found;
            if (second_lower >= first_upper) goto collision_found;
            goto no_collision_found;
        }

        if (second_upper < first_lower) {
            /* SecondBoxVerticalChk. */
            if (first_lower < first_upper) goto collision_found;
            if (second_lower >= first_upper) goto collision_found;
            goto no_collision_found;
        }
        if (second_upper == first_lower) goto collision_found;
        if (second_lower < second_upper) goto collision_found;
        if (second_lower >= first_upper) goto collision_found;
        goto no_collision_found;

collision_found:
        ++second_offset;
        ++coordinate;
        --counter;
        game->ram[0x0007U] = counter;
        if ((counter & 0x80U) == 0U) continue;
        game->ram[0x0006U] = (mysmb_u8)(second_offset - coordinate);
        return 1U;

no_collision_found:
        game->ram[0x0006U] = (mysmb_u8)(second_offset - coordinate);
        return 0U;
    }
}
