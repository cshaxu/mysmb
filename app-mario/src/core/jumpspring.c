#include "core/objects.h"
#include "core/oam/oam.h"

/* ROM $B8B6-$B91D: Jumpspring_Y_PosData and JumpspringHandler.
 * The original actor owns state; the four children retain their own owners.
 * Active animation values 1..4 select the four original table entries. */
void mysmb_objects_step_jumpspring(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 y_position[4] = { 8U, 16U, 8U, 0U };
    mysmb_u8 frame;

    mysmb_oam_get_enemy_offscreen_bits(game, slot);
    if (game->ram[0x0747U] == 0U && game->ram[0x070eU] != 0U) {
        frame = (mysmb_u8)(game->ram[0x070eU] - 1U);
        if ((frame & 2U) != 0U)
            game->ram[0x00ceU] = (mysmb_u8)(game->ram[0x00ceU] - 2U);
        else
            game->ram[0x00ceU] = (mysmb_u8)(game->ram[0x00ceU] + 2U);
        game->ram[0x00cfU + slot] =
            (mysmb_u8)(game->ram[0x0058U + slot] + y_position[frame]);
        if (frame >= 1U && (game->ram[0x000aU] & 0x80U) != 0U &&
            (game->ram[0x000dU] & 0x80U) == 0U)
            game->ram[0x06dbU] = 0xf4U;
        if (frame == 3U) {
            game->ram[0x009fU] = game->ram[0x06dbU];
            game->ram[0x070eU] = 0U;
        }
    }
    mysmb_oam_relative_enemy_position(game, slot);
    (void)mysmb_objects_draw_normal_enemy_graphics(game, slot);
    mysmb_objects_check_enemy_offscreen_bounds(game, slot);
    if (game->ram[0x070eU] != 0U && game->ram[0x0786U] == 0U) {
        game->ram[0x0786U] = 4U;
        game->ram[0x070eU] = (mysmb_u8)(game->ram[0x070eU] + 1U);
    }
}
