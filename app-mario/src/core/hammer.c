#include "core/objects.h"
#include "core/oam/oam.h"
#include "core/world/world.h"

/* ROM $BA89-$BA93: allocation dependency and released horizontal speeds. */
const mysmb_u8 mysmb_hammer_enemy_offsets[9] = {
    4U, 4U, 4U, 5U, 5U, 5U, 6U, 6U, 6U
};
const mysmb_u8 mysmb_hammer_x_speeds[2] = { 0x10U, 0xf0U };

/* ROM $BA94-$BAC2 SpawnHammerObj through NoHammer. The result is carry;
 * the parent slot is read from ObjectOffset at the original reload point. */
mysmb_u8 mysmb_objects_spawn_hammer(struct mysmb_game *game)
{
    mysmb_u8 slot;

    slot = (mysmb_u8)(game->ram[0x07a8U] & 7U);
    if (slot == 0U) slot = (mysmb_u8)(game->ram[0x07a8U] & 8U);
    if (game->ram[0x002aU + slot] != 0U) return 0U;
    if (game->ram[0x000fU + mysmb_hammer_enemy_offsets[slot]] != 0U)
        return 0U;
    game->ram[0x06aeU + slot] = game->ram[0x0008U];
    game->ram[0x002aU + slot] = 0x90U;
    game->ram[0x04a2U + slot] = 7U;
    return 1U;
}

/* ROM $BAC3-$BB37 ProcHammerObj through RunHSubs. Facing is the original
 * one/two state. Child implementations keep their separate proof status. */
void mysmb_objects_step_hammer(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 state;
    mysmb_u8 parent;
    mysmb_u8 direction;
    mysmb_u8 speed;
    mysmb_u16 x_sum;

    if (game->ram[0x0747U] == 0U) {
        state = (mysmb_u8)(game->ram[0x002aU + slot] & 0x7fU);
        parent = game->ram[0x06aeU + slot];
        if (state < 2U) {
            game->ram[0] = 0x10U;
            game->ram[1] = 0x0fU;
            game->ram[2] = 4U;
            mysmb_world_impose_gravity_spr_object(game,
                (mysmb_u8)(slot + 0x0dU), 0x10U, 4U);
            mysmb_world_move_spr_object_horizontally(game,
                (mysmb_u8)(slot + 0x0dU));
            slot = game->ram[0x0008U];
            mysmb_objects_check_hammer_collision(game, slot);
        }
        else {
            if (state == 2U) {
                game->ram[0x00acU + slot] = 0xfeU;
                game->ram[0x001eU + parent] &= 0xf7U;
                direction = (mysmb_u8)(game->ram[0x0046U + parent] - 1U);
                speed = mysmb_hammer_x_speeds[direction];
                slot = game->ram[0x0008U];
                game->ram[0x0064U + slot] = speed;
            }
            game->ram[0x002aU + slot]--;
            x_sum = (mysmb_u16)game->ram[0x0087U + parent] + 2U;
            game->ram[0x0093U + slot] = (mysmb_u8)x_sum;
            game->ram[0x007aU + slot] = (mysmb_u8)(
                game->ram[0x006eU + parent] + (x_sum > 0xffU ? 1U : 0U));
            game->ram[0x00dbU + slot] =
                (mysmb_u8)(game->ram[0x00cfU + parent] - 0x0aU);
            game->ram[0x00c2U + slot] = 1U;
        }
    }
    mysmb_oam_get_misc_offscreen_bits(game, slot);
    mysmb_oam_relative_misc_position(game, slot);
    mysmb_objects_get_hammer_bounding_box(game, slot);
    mysmb_objects_draw_hammer(game, slot);
}
