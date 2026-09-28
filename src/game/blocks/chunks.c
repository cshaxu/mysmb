#include "game/blocks/chunks.h"
#include "game/area.h"
#include "game/objects.h"
#include "game/score.h"

/* ROM $BE1F-$BE40 CheckTopOfBlock and TopEx. The row write belongs to
 * every nonzero-row path, including a miss. Preserve the full pointer. */
void mysmb_blocks_check_top(struct mysmb_game *game, mysmb_u8 slot,
                            mysmb_u8 block_low, mysmb_u8 block_row)
{
    mysmb_u16 address;
    slot = game->ram[0x03eeU];
    if (block_row == 0U) return;
    game->ram[2U] = (mysmb_u8)(block_row - 0x10U);
    address = (mysmb_u16)(((mysmb_u16)game->ram[7U] << 8U) +
                           block_low + game->ram[2U]);
    if (game->ram[address] != 0xc2U) return;
    game->ram[address] = 0U;
    mysmb_area_remove_coin_axe(game, game->ram[6U], game->ram[2U]);
    slot = game->ram[0x03eeU];
    mysmb_objects_setup_jump_coin(game, slot);
}

/* ROM $BE41-$BE6F SpawnBrickChunks. In particular, neither chunk's Y
 * high byte is written by this original routine. */
void mysmb_blocks_spawn_chunks(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[0x03f1U + slot] = game->ram[0x008fU + slot];
    game->ram[0x0060U + slot] = 0xf0U;
    game->ram[0x0062U + slot] = 0xf0U;
    game->ram[0x00a8U + slot] = 0xfaU;
    game->ram[0x00aaU + slot] = 0xfcU;
    game->ram[0x043cU + slot] = 0U;
    game->ram[0x043eU + slot] = 0U;
    game->ram[0x0078U + slot] = game->ram[0x0076U + slot];
    game->ram[0x0091U + slot] = game->ram[0x008fU + slot];
    game->ram[0x00d9U + slot] = (mysmb_u8)(game->ram[0x00d7U + slot] + 8U);
    game->ram[0x00a8U + slot] = 0xfaU;
}

/* ROM $BE02-$BE1E BrickShatter. Child call order also determines score
 * and audio state; a bump's square-channel sound does not belong here. */
void mysmb_blocks_shatter(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_blocks_check_top(game, slot, game->ram[6U], game->ram[2U]);
    slot = game->ram[0x03eeU];
    game->ram[0x03ecU + slot] = 1U;
    game->ram[0x00fdU] = 1U;
    mysmb_blocks_spawn_chunks(game, slot);
    game->ram[0x009fU] = 0xfeU;
    game->ram[0x0139U] = 5U;
    (void)mysmb_score_add(game);
}
