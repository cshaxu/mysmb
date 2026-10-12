#include "core/objects.h"
#include "core/oam/oam.h"
#include "core/world/world.h"

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

/* ROM $B94B VineObjectHandler through ExitVH. Active vines have one or two
 * registered entries; the original caller, not an invented clamp, owns that
 * invariant. Child algorithms retain their original proof obligations. */
void mysmb_objects_step_vine(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 index;
    struct mysmb_enemy_terrain terrain;

    if (slot != 5U) return;
    index = (mysmb_u8)(game->ram[0x0398U] - 1U);
    if (game->ram[0x0399U] != mysmb_vine_height_data[index] &&
        (game->ram[0x0009U] & 2U) != 0U) {
        game->ram[0x00d4U] = (mysmb_u8)(game->ram[0x00d4U] - 1U);
        game->ram[0x0399U] = (mysmb_u8)(game->ram[0x0399U] + 1U);
    }
    if (game->ram[0x0399U] < 8U) return;
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
    index = 0U;
    do {
        mysmb_objects_draw_vine(game, index);
        index = (mysmb_u8)(index + 1U);
    } while (index != game->ram[0x0398U]);
    if ((game->ram[0x03d1U] & 0x0cU) != 0U) {
        index = (mysmb_u8)(index - 1U);
        do {
            mysmb_objects_erase_enemy(game, game->ram[0x039aU + index]);
            index = (mysmb_u8)(index - 1U);
        } while ((index & 0x80U) == 0U);
        /* EraseEnemyObject returns A=0 in the original caller contract. */
        game->ram[0x0398U] = 0U;
        game->ram[0x0399U] = 0U;
    }
    if (game->ram[0x0399U] < 0x20U) return;
    /* Original X=6 is the sprite-object index for enemy slot five;
     * Y=1B and A=1 select the probe and horizontal contact output. */
    (void)mysmb_world_query_enemy_block(game, 5U, 0x1bU, 1U, &terrain);
    if (terrain.block_row_offset >= 0xd0U) return;
    if (game->ram[terrain.block_address] == 0U)
        game->ram[terrain.block_address] = 0x26U;
}
