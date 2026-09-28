#include "game/blocks/head.h"
#include "game/objects.h"
#include "game/area.h"

/* ROM $BCEB: BlockYPosAdderData, consumed at $BD62. */
static const mysmb_u8 block_y_adder[2] = { 0x04U, 0x12U };

/* ROM $BD84-$BD9A InitBlock_XY_Pos. AND preserves the ADC carry. */
void mysmb_blocks_initialize_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 sum;
    sum = (mysmb_u16)game->ram[0x0086U] + 8U;
    game->ram[0x008fU + slot] = (mysmb_u8)(sum & 0xf0U);
    game->ram[0x0076U + slot] =
        (mysmb_u8)(game->ram[0x006dU] + (sum >> 8U));
    game->ram[0x03eaU + slot] = game->ram[0x0076U + slot];
    game->ram[0x00beU + slot] = game->ram[0x00b5U];
}

/* ROM $BCED-$BD83 PlayerHeadCollision through InvOBit.
 * The incoming A/metatile survives child calls, as on the original stack.
 * Scratch $02 and $06-$07 are inputs from the head block-buffer probe. */
void mysmb_blocks_head_collision(struct mysmb_game *game, mysmb_u8 metatile)
{
    mysmb_u8 slot;
    mysmb_u8 tile;
    mysmb_u8 replacement;
    mysmb_u8 matched;
    mysmb_u8 offset;
    mysmb_u16 address;

    slot = game->ram[0x03eeU];
    game->ram[0x0026U + slot] = game->ram[0x0754U] != 0U ? 0x11U : 0x12U;
    mysmb_area_destroy_block_metatile(game, slot, game->ram[6U], game->ram[2U]);
    slot = game->ram[0x03eeU];
    game->ram[0x03e4U + slot] = game->ram[2U];
    game->ram[0x03e6U + slot] = game->ram[6U];
    address = (mysmb_u16)(((mysmb_u16)game->ram[7U] << 8U) |
                           game->ram[6U]);
    tile = game->ram[(mysmb_u16)(address + game->ram[2U])];
    matched = mysmb_blocks_bumped_index(tile);
    game->ram[0U] = tile;
    replacement = game->ram[0x0754U] != 0U ? tile : 0U;
    if (matched != 0xffU) {
        game->ram[0x0026U + slot] = 0x11U;
        replacement = 0xc4U;
        if (tile == 0x58U || tile == 0x5dU) {
            if (game->ram[0x06bcU] == 0U) {
                game->ram[0x079dU] = 0x0bU;
                game->ram[0x06bcU]++;
            }
            if (game->ram[0x079dU] != 0U) replacement = tile;
        }
    }
    game->ram[0x03e8U + slot] = replacement;
    mysmb_blocks_initialize_position(game, slot);
    game->ram[(mysmb_u16)(address + game->ram[2U])] = 0x23U;
    game->ram[0x0784U] = 0x10U;
    game->ram[5U] = metatile;
    offset = (game->ram[0x0714U] != 0U || game->ram[0x0754U] != 0U) ? 1U : 0U;
    game->ram[0x00d7U + slot] =
        (mysmb_u8)((game->ram[0x00ceU] + block_y_adder[offset]) & 0xf0U);
    if (game->ram[0x0026U + slot] == 0x11U) mysmb_blocks_bump(game, slot);
    else mysmb_blocks_shatter(game, slot);
    game->ram[0x03eeU] ^= 1U;
}

/* Existing native adapter supplies the probe's original scratch inputs. */
mysmb_u8 mysmb_objects_start_head_bump(struct mysmb_game *game,
                                       mysmb_u8 metatile,
                                       mysmb_u8 block_low,
                                       mysmb_u8 block_row)
{
    game->ram[2U] = block_row;
    game->ram[6U] = block_low;
    game->ram[7U] = 5U;
    mysmb_blocks_head_collision(game, metatile);
    return 1U;
}
