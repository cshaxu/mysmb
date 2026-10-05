#include "game/blocks/bump.h"
#include "core/area.h"
#include "game/objects.h"
#include "core/frame_root.h"

/* ROM BrickQBlockMetatiles: question/hidden entries, ground bricks, then
 * alternate-area bricks. Selection and collision consume one data owner. */
const mysmb_u8 mysmb_brick_question_metatiles[14] = {
    0xc1U, 0xc0U, 0x5fU, 0x60U, 0x55U, 0x56U, 0x57U,
    0x58U, 0x59U, 0x5aU, 0x5bU, 0x5cU, 0x5dU, 0x5eU
};

/* ROM $BDF6-$BE01 BlockBumpedChk, BumpChkLoop and MatchBump.
 * Descending search retains both the original Y result and carry meaning. */
mysmb_u8 mysmb_blocks_bumped_index(mysmb_u8 metatile)
{
    mysmb_u8 index;
    index = 13U;
    do {
        if (metatile == mysmb_brick_question_metatiles[index]) return index;
        --index;
    } while (index < 0x80U);
    return 0xffU;
}

/* ROM $BD9B-$BDE7 BumpBlock, BlockCode and all nine content targets.
 * The overlapping BIT entries select types 0, 2 and 3 before their common
 * SetupPowerUp tail; the native switch preserves those entry semantics. */
void mysmb_blocks_bump(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 index;
    mysmb_blocks_check_top(game, slot, game->ram[6U], game->ram[2U]);
    /* CheckTopOfBlock returns X from SprDataOffset_Ctrl, including its
     * post-coin reload. No native cached metatile survives that child. */
    slot = game->ram[0x03eeU];
    game->ram[0x00ffU] = 2U;
    game->ram[0x0060U + slot] = 0U;
    game->ram[0x043cU + slot] = 0U;
    game->ram[0x009fU] = 0U;
    game->ram[0x00a8U + slot] = 0xfeU;
    index = mysmb_blocks_bumped_index(game->ram[5U]);
    if (index == 0xffU) return;
    if (index >= 9U) index = (mysmb_u8)(index - 5U);
    /* ROM $BDBD JSR JumpEngine saves $BDBF and the selected vector in
     * $04-$07 before entering the content handler. */
    mysmb_game_jump_engine_state(game, 0xbdbfU, index);
    switch (index) {
    case 0U:
    case 4U:
        game->ram[0x0039U] = 0U;
        mysmb_objects_start_power_up(game, slot);
        break;
    case 1U:
    case 2U:
    case 7U:
        mysmb_objects_coin_block(game, slot, 0U);
        break;
    case 3U:
    case 8U:
        game->ram[0x0039U] = 3U;
        mysmb_objects_start_power_up(game, slot);
        break;
    case 5U:
        mysmb_objects_start_vine(game, 5U, game->ram[0x03eeU]);
        break;
    case 6U:
        game->ram[0x0039U] = 2U;
        mysmb_objects_start_power_up(game, slot);
        break;
    }
}
