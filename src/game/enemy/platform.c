#include "game/enemy/platform.h"
#include "game/world/world.h"

/* ROM $D5D3-$D606 YMovingPlatform through ExYPl. Gravity returns
 * X=ObjectOffset; the rest path preserves its incoming enemy slot. */
void mysmb_platform_move_y(struct mysmb_game *g, mysmb_u8 slot)
{
    if ((g->ram[0x00a0U + slot] | g->ram[0x0434U + slot]) == 0U) {
        g->ram[0x0417U + slot] = 0U;
        if (g->ram[0x00cfU + slot] < g->ram[0x0401U + slot]) {
            if ((g->ram[0x0009U] & 7U) == 0U)
                ++g->ram[0x00cfU + slot];
            if ((g->ram[0x03a2U + slot] & 0x80U) == 0U)
                mysmb_platform_position_player_vertical(g, slot);
            return;
        }
    }
    mysmb_world_move_platform_vertically(g, slot,
        g->ram[0x00cfU + slot] >= g->ram[0x0058U + slot] ? 1U : 0U);
    slot = g->ram[8U];
    if ((g->ram[0x03a2U + slot] & 0x80U) == 0U)
        mysmb_platform_position_player_vertical(g, slot);
}
