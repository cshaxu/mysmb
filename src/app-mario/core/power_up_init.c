#include "core/objects.h"

/* ROM $BC60-$BC84 PwrUpJmp, StrType and PutBehind. This residual entry
 * preserves existing ID and coordinates, regardless of the caller slot. */
void mysmb_objects_initialize_power_up(struct mysmb_game *game)
{
    mysmb_u8 status;

    game->ram[0x0023U] = 1U;
    game->ram[0x0014U] = 1U;
    game->ram[0x049fU] = 3U;
    if (game->ram[0x0039U] < 2U) {
        status = game->ram[0x0756U];
        if (status >= 2U) status = (mysmb_u8)(status >> 1U);
        game->ram[0x0039U] = status;
    }
    game->ram[0x03caU] = 0x20U;
    game->ram[0x00feU] = 2U;
}

/* ROM $BC49-$BC5F SetupPowerUp, then fall through into PwrUpJmp. */
void mysmb_objects_start_power_up(struct mysmb_game *game, mysmb_u8 block_slot)
{
    game->ram[0x001bU] = 0x2eU;
    game->ram[0x0073U] = game->ram[0x0076U + block_slot];
    game->ram[0x008cU] = game->ram[0x008fU + block_slot];
    game->ram[0x00bbU] = 1U;
    game->ram[0x00d4U] = (mysmb_u8)(game->ram[0x00d7U + block_slot] - 8U);
    mysmb_objects_initialize_power_up(game);
}
