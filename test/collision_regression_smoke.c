#include "game/objects.h"
#include "game/player.h"

static void mysmb_clear_block_buffers(struct mysmb_game *game)
{
    mysmb_u16 index;

    for (index = 0U; index < 0x01a0U; ++index) {
        game->ram[(mysmb_u16)(0x0500U + index)] = 0U;
    }
}

int main(void)
{
    struct mysmb_game game;

    /* ROM PlayerBGCollision: a right-facing Mario samples (X+12,Y+24).
     * A solid metatile there cancels rightward velocity and nudges him left. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x001dU] = 2U;
    game.ram[0x0754U] = 1U;
    game.ram[0x0045U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0057U] = 0x10U;
    game.ram[0x0705U] = 0x80U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0522U] = 0x61U;
    if (mysmb_player_check_sides(&game) == 0U) return 11;
    if (game.ram[0x0086U] != 0x1fU) return 12;
    if (game.ram[0x0057U] != 0U) return 13;
    if (game.ram[0x0705U] != 0x80U) return 14;

    /* ROM DoEnemySideCheck: an active mushroom moving right samples
     * (X+20,Y+20).  A pipe's C0 metatile reverses it to leftward F0 speed. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x001eU + 5U] = 0x80U;
    game.ram[0x0039U] = 0U;
    game.ram[0x0046U + 5U] = 1U;
    game.ram[0x0058U + 5U] = 0x10U;
    game.ram[0x006eU + 5U] = 0U;
    game.ram[0x0087U + 5U] = 0x20U;
    game.ram[0x00cfU + 5U] = 0x30U;
    game.ram[0x00b6U + 5U] = 1U;
    game.ram[0x0523U] = 0xc0U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0046U + 5U] != 2U ||
        game.ram[0x0058U + 5U] != 0xf0U) return 2;

    /* BlockBufferCollision's ADC carries X+20 into the object's page before
     * GetBlockBufferAddr.  A pipe just over the page edge must still reverse
     * the mushroom; using the unadjusted page probes the wrong buffer. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x001eU + 5U] = 0x80U;
    game.ram[0x0039U] = 0U;
    game.ram[0x0046U + 5U] = 1U;
    game.ram[0x0058U + 5U] = 0x10U;
    game.ram[0x006eU + 5U] = 0U;
    game.ram[0x0087U + 5U] = 0xf0U;
    game.ram[0x00cfU + 5U] = 0x30U;
    game.ram[0x00b6U + 5U] = 1U;
    game.ram[0x05f0U] = 0xc0U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0046U + 5U] != 2U ||
        game.ram[0x0058U + 5U] != 0xf0U) return 3;
    return 0;
}
