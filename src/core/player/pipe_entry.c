#include "core/player.h"

/* Original tables belong to the bound program data, including adjacent
 * bytes reached by raw source indices. Resource-free tests bind their own
 * data explicitly; there is no shortened production warp-number array. */
static mysmb_u8 pipe_byte(const struct mysmb_game *game, mysmb_u16 address)
{
    mysmb_u16 offset;
    offset = (mysmb_u16)(address - 0x8000U);
    if (game->area_prg != 0 && offset < game->area_prg_size)
        return game->area_prg[offset];
    return 0U;
}

/* ROM $DEE8-$DF4A HandlePipeEntry / GetWNum / ExPipeE. Left and right
 * carry the original RAM01 and RAM00 foot-query results respectively. */
mysmb_u8 mysmb_player_handle_vertical_pipe(struct mysmb_game *game,
    mysmb_u8 left, mysmb_u8 right)
{
    mysmb_u8 index, world, area_index;
    if ((game->ram[0x000bU] & 4U) == 0U) return 0U;
    if (right != 0x11U) return 0U;
    if (left != 0x10U) return 0U;
    game->ram[0x06deU] = 0x30U;
    game->ram[0x000eU] = 3U;
    game->ram[0x00ffU] = 0x10U;
    game->ram[0x03c4U] = 0x20U;
    if (game->ram[0x06d6U] == 0U) return 1U;

    index = (mysmb_u8)((game->ram[0x06d6U] & 3U) << 2U);
    if (game->ram[0x0086U] >= 0x60U) {
        ++index;
        if (game->ram[0x0086U] >= 0xa0U) ++index;
    }
    world = (mysmb_u8)(pipe_byte(game, (mysmb_u16)(0x87f2U + index)) - 1U);
    game->ram[0x075fU] = world;
    area_index = pipe_byte(game, (mysmb_u16)(0x9cb4U + world));
    game->ram[0x0750U] = pipe_byte(game, (mysmb_u16)(0x9cbcU + area_index));
    game->ram[0x00fcU] = 0x80U;
    game->ram[0x0751U] = 0U;
    game->ram[0x0760U] = 0U;
    game->ram[0x075cU] = 0U;
    game->ram[0x0752U] = 0U;
    ++game->ram[0x075dU];
    ++game->ram[0x0757U];
    return 1U;
}
