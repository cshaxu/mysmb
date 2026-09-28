#include "game/objects.h"

/* ROM $B949-$B94A VineHeightData; the growth consumer retains its own proof. */
const mysmb_u8 mysmb_vine_height_data[2] = { 0x30U, 0x60U };

/* ROM $B91E-$B948 Setup_Vine/NextVO. X is the enemy slot, Y the block slot.
 * Slot selection belongs to the original caller, not this initialization. */
void mysmb_objects_start_vine(struct mysmb_game *game, mysmb_u8 slot,
                              mysmb_u8 block_slot)
{
    mysmb_u8 vine_slot;

    game->ram[0x0016U + slot] = 0x2fU;
    game->ram[0x000fU + slot] = 1U;
    game->ram[0x006eU + slot] = game->ram[0x0076U + block_slot];
    game->ram[0x0087U + slot] = game->ram[0x008fU + block_slot];
    game->ram[0x00cfU + slot] = game->ram[0x00d7U + block_slot];
    vine_slot = game->ram[0x0398U];
    if (vine_slot == 0U) game->ram[0x039dU] = game->ram[0x00cfU + slot];
    game->ram[0x039aU + vine_slot] = slot;
    game->ram[0x0398U] = (mysmb_u8)(game->ram[0x0398U] + 1U);
    game->ram[0x00feU] = 4U;
}
