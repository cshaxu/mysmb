#include <stdio.h>
#include "game/objects.h"
#include "game/player.h"

static void mysmb_clear_block_buffers(struct mysmb_game *game)
{
    mysmb_u16 index;

    for (index = 0U; index < 0x01a0U; ++index) {
        game->ram[(mysmb_u16)(0x0500U + index)] = 0U;
    }
}

static void mysmb_setup_active_mushroom(struct mysmb_game *game,
                                        mysmb_u8 state, mysmb_u8 x, mysmb_u8 y,
                                        mysmb_u8 direction)
{
    mysmb_game_initialize_memory(game, 0xfeU);
    mysmb_clear_block_buffers(game);
    game->ram[0x001eU + 5U] = state;
    game->ram[0x0039U] = 0U;
    game->ram[0x0046U + 5U] = 0U;
    game->ram[0x0058U + 5U] = 0U;
    game->ram[0x0401U + 5U] = 0U;
    game->ram[0x00a0U + 5U] = 0U;
    game->ram[0x00b6U + 5U] = 1U;
    game->ram[0x0417U + 5U] = 0U;
    game->ram[0x0434U + 5U] = 0U;
    game->ram[0x006eU + 5U] = 1U;
    game->ram[0x0087U + 5U] = x;
    game->ram[0x00cfU + 5U] = y;
    game->ram[0x0046U + 5U] = direction;
    game->ram[0x0747U] = 0U;
    game->ram[0x0009U] = 0U;
}

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 step;

    /* ROM PlayerBGCollision: a right-facing Mario samples (X+12,Y+24). */
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
    if (game.ram[0x0086U] != 0x1fU || game.ram[0x0057U] != 0U ||
        game.ram[0x0705U] != 0x80U) return 12;

    /* PlayerHeadCollision still bounces an ordinary brick for small Mario.
     * The brick is not in BlockBumpedChk, but the ROM sets Y speed to zero
     * through BumpBlock and retains the metatile for the block object. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x05f2U] = 0x51U;
    if (mysmb_player_check_head(&game) == 0U ||
        game.ram[0x0026U] != 0x11U || game.ram[0x03e8U] != 0x51U ||
        game.ram[0x05f2U] != 0x23U || game.ram[0x009fU] != 0U ||
        game.ram[0x0784U] != 0x10U) return 13;

    /* Hidden coin blocks are $5f in the collision buffer.  They are absent
     * from scenery only; PlayerHeadCollision must still enter BumpBlock. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x05f2U] = 0x5fU;
    if (mysmb_player_check_head(&game) == 0U ||
        game.ram[0x0026U] != 0x11U || game.ram[0x03e8U] != 0xc4U ||
        game.ram[0x05f2U] != 0x23U || game.ram[0x009fU] != 0U ||
        game.ram[0x0784U] != 0x10U) return 14;
    for (step = 0U; step < 24U; ++step) {
        mysmb_objects_apply_block_replacements(&game);
        /* NMI has consumed the previous VRAM command before the next frame. */
        game.ram[0x0301U] = 0U;
        mysmb_objects_step_blocks(&game);
    }
    if (game.ram[0x05f2U] != 0xc4U) return 15;
    /* PowerUpObjHandler calls RunPUSubs from state 6.  GameCore invokes this
     * collision routine after the handler, so state 6 must not be rejected
     * simply because d7 has not yet been set. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x001bU] = 0x2eU;
    game.ram[0x0023U] = 6U;
    game.ram[0x0014U] = 1U;
    game.ram[0x0073U] = 1U;
    game.ram[0x008cU] = 0x30U;
    game.ram[0x00d4U] = 0x50U;
    game.ram[0x049fU] = 3U;
    /* The first World 1-1 fire flower is type 1 while Mario is big. */
    game.ram[0x0039U] = 1U;
    game.ram[0x0756U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x30U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x50U;
    game.ram[0x0499U] = 1U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0009U] = 0U;
    /* PlayerEnemyCollision consumes boxes prepared by PlayerGfxHandler and
     * RunPUSubs.  This isolated fixture supplies that source-owned RAM. */
    game.ram[0x03d8U + 5U] = 0U;
    mysmb_objects_set_bounding_box(&game, 0x04acU, game.ram[0x0499U],
                                   0x30U, game.ram[0x00ceU]);
    mysmb_objects_set_bounding_box(&game, 0x04b0U + 5U * 4U,
                                   game.ram[0x049fU], 0x30U,
                                   game.ram[0x00d4U]);
    mysmb_objects_check_power_up_collision(&game);
    if (game.ram[0x001bU] != 0U || game.ram[0x0023U] != 0U ||
        game.ram[0x0014U] != 0U || game.ram[0x0756U] != 2U ||
        game.ram[0x000eU] != 12U) return 2;
    /* ChkUnderEnemy uses BlockBuffer_Y_Adder[$15]=$18, selecting row $20
     * at Y=$29.  The $15 passed by the ROM is an adder-table index. */
    mysmb_setup_active_mushroom(&game, 0xc0U, 0U, 0x29U, 1U);
    game.ram[0x05f0U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x00cfU + 5U] != 0x28U ||
        game.ram[0x001eU + 5U] != 0x80U) return 3;

    /* LandEnemyProperly sends D-F through the falling-state transition. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0U, 0x2dU, 1U);
    game.ram[0x05f0U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x00cfU + 5U] != 0x2dU ||
        game.ram[0x001eU + 5U] != 0xc0U) return 4;

    /* On a flat floor, ChkUnderEnemy samples row $20 while
     * DoEnemySideCheck samples row $10.  The mushroom must remain grounded
     * and advance horizontally instead of treating its floor as a wall. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0U, 0x28U, 1U);
    game.ram[0x0058U + 5U] = 0x10U;
    game.ram[0x05f0U] = 0x61U;
    for (step = 0U; step < 4U; ++step) {
        mysmb_objects_step_power_up(&game);
    }
    if (game.ram[0x0087U + 5U] != 4U ||
        game.ram[0x00cfU + 5U] != 0x28U ||
        game.ram[0x001eU + 5U] != 0x80U ||
        game.ram[0x0046U + 5U] != 1U) return 7;


    /* A mushroom that has entered d6 falling state must use the same
     * LandEnemyProperly two-pass landing as the ROM, then resume horizontal
     * movement.  The floor is block-buffer page two, row $b0: Y=$90 advances through the d-f
     * transition and settles at Y=$b8. */
    mysmb_setup_active_mushroom(&game, 0xc0U, 0U, 0x90U, 1U);
    game.ram[0x0058U + 5U] = 0x10U;
    for (step = 0U; step < 16U; ++step) {
        game.ram[0x0680U + step] = 0x54U;
    }
    for (step = 0U; step < 64U; ++step) {
        mysmb_objects_step_power_up(&game);
    }
    if (game.ram[0x00cfU + 5U] != 0xb8U ||
        game.ram[0x001eU + 5U] != 0x80U ||
        game.ram[0x0087U + 5U] == 0U ||
        game.ram[0x0046U + 5U] != 1U) return 14;
    /* DoEnemySideCheck uses left (X,Y+14), not X+4. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0x2cU, 0x30U, 2U);
    game.ram[0x05f2U] = 0xc0U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0046U + 5U] != 1U ||
        game.ram[0x0058U + 5U] != 0x10U) return 5;

    /* DoEnemySideCheck uses right (X+16,Y+14), not X+20. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0x2dU, 0x30U, 1U);
    game.ram[0x05f3U] = 0xc0U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0046U + 5U] != 2U ||
        game.ram[0x0058U + 5U] != 0xf0U) return 6;
    return 0;
}
