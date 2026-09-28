#include "game/objects.h"

/* ROM $BB84-$BB95 FindEmptyMiscSlot/FMiscLoop/UseMiscS. Only the CPY
 * reached after DEY changes carry. A free slot eight preserves entry carry. */
mysmb_u8 mysmb_objects_find_empty_misc_slot(struct mysmb_game *game,
                                            mysmb_u8 *carry)
{
    mysmb_u8 slot;

    slot = 8U;
    while (game->ram[0x002aU + slot] != 0U) {
        --slot;
        *carry = 1U;
        if (slot == 5U) {
            slot = 8U;
            break;
        }
    }
    game->ram[0x06b7U] = slot;
    return slot;
}

/* ROM $BB6C-$BB83 JCoinC. The score child owns score/coin digits;
 * this caller increments the separate 1-up-block tally after its return. */
static void mysmb_coin_finish_setup(struct mysmb_game *game,
                                     mysmb_u8 block_slot, mysmb_u8 slot)
{
    game->ram[0x00acU + slot] = 0xfbU;
    game->ram[0x00c2U + slot] = 1U;
    game->ram[0x002aU + slot] = 1U;
    game->ram[0x00feU] = 1U;
    game->ram[0x0008U] = block_slot;
    mysmb_objects_give_one_coin(game);
    game->ram[0x0748U]++;
}

/* ROM $BB38-$BB50 CoinBlock. Incoming carry belongs to BlockCode; the
 * allocation search may replace it before SBC #$10. X is the block slot. */
void mysmb_objects_coin_block(struct mysmb_game *game, mysmb_u8 block_slot,
                               mysmb_u8 carry)
{
    mysmb_u8 slot;

    slot = mysmb_objects_find_empty_misc_slot(game, &carry);
    game->ram[0x007aU + slot] = game->ram[0x0076U + block_slot];
    game->ram[0x0093U + slot] = (mysmb_u8)(game->ram[0x008fU + block_slot] | 5U);
    game->ram[0x00dbU + slot] =
        (mysmb_u8)(game->ram[0x00d7U + block_slot] - 0x11U + carry);
    mysmb_coin_finish_setup(game, block_slot, slot);
}

/* ROM $BB51-$BB6B SetupJumpCoin. Four ASLs leave input bit four in carry;
 * the subsequent LDA/ORA preserve it for ADC #$20. */
void mysmb_objects_setup_jump_coin(struct mysmb_game *game, mysmb_u8 block_slot)
{
    mysmb_u8 slot;
    mysmb_u8 carry;
    mysmb_u8 column;

    carry = 0U;
    slot = mysmb_objects_find_empty_misc_slot(game, &carry);
    game->ram[0x007aU + slot] = game->ram[0x03eaU + block_slot];
    column = game->ram[6U];
    game->ram[0x0093U + slot] = (mysmb_u8)((column << 4U) | 5U);
    carry = (mysmb_u8)((column >> 4U) & 1U);
    game->ram[0x00dbU + slot] = (mysmb_u8)(game->ram[2U] + 0x20U + carry);
    mysmb_coin_finish_setup(game, block_slot, slot);
}
