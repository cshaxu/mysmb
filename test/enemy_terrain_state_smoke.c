#include "game/objects.h"

static void mysmb_test_prepare_enemy(struct mysmb_game *game, mysmb_u8 id,
                                     mysmb_u8 state)
{
    mysmb_game_initialize_memory(game, 0U);
    game->ram[0x071dU] = 0xf0U;
    game->ram[0x074eU] = 1U; /* AreaType: ground */
    game->ram[0x000fU] = 1U; /* Enemy_Flag */
    game->ram[0x0016U] = id; /* Enemy_ID */
    game->ram[0x001eU] = state; /* Enemy_State */
    game->ram[0x0046U] = 1U; /* Enemy_MovingDir */
    game->ram[0x006eU] = 0U; /* Enemy_PageLoc */
    game->ram[0x0087U] = 0x40U; /* Enemy_X_Position */
    game->ram[0x00b6U] = 1U; /* Enemy_Y_HighPos */
    game->ram[0x00cfU] = 0x50U; /* Enemy_Y_Position */
    game->ram[0x0058U] = 0x20U; /* Enemy_X_Speed */
    game->ram[0x03aeU] = 0x40U; /* Enemy_Rel_XPos */ /* Enemy_X_Speed */
}

int main(void)
{
    struct mysmb_game game;

    /* EnemyToBGCollisionDet -> LandEnemyProperly -> LandEnemyInitState.
     * The bottom $15 probe sees a solid at Y+$12, and a falling Goomba
     * lands at its ROM low-nibble alignment. */
    mysmb_test_prepare_enemy(&game, 6U, 0x40U);
    game.ram[0x0544U] = 0x61U;
    game.ram[0x00a0U] = 2U;
    game.ram[0x0434U] = 0x7fU;
    mysmb_objects_step_normal_enemy_terrain(&game, 0U);
    if (game.ram[0x00cfU] != 0x58U || game.ram[0x00a0U] != 0U ||
        game.ram[0x0434U] != 0U || game.ram[0x001eU] != 0U) return 1;

    /* Empty bottom probe enters ChkForRedKoopa's EnemyBGCStateData[0]. */
    mysmb_test_prepare_enemy(&game, 6U, 0U);
    mysmb_objects_step_normal_enemy_terrain(&game, 0U);
    if (game.ram[0x001eU] != 1U) return 2;

    /* A normal red koopa reaches ChkForBump_HammerBroJ directly; it reverses
     * even though the bottom probe is empty, and d7 is clear so no bump SFX. */
    mysmb_test_prepare_enemy(&game, 3U, 0U);
    game.ram[0x00ffU] = 0U;
    mysmb_objects_step_normal_enemy_terrain(&game, 0U);
    if (game.ram[0x0046U] != 2U || game.ram[0x0058U] != 0xe0U ||
        game.ram[0x00ffU] != 0U) return 3;

    /* HandleEToBGCollision consumes a bumped block and routes a Goomba
     * through KillEnemyAboveBlock, score allocation, and SetStun. */
    mysmb_test_prepare_enemy(&game, 6U, 0x40U);
    game.ram[0x0544U] = 0x23U;
    mysmb_objects_step_normal_enemy_terrain(&game, 0U);
    if (game.ram[0x0544U] != 0U || game.ram[0x001eU] != 0x22U ||
        game.ram[0x00cfU] != 0x4eU || game.ram[0x00a0U] != 0xfdU ||
        game.ram[0x0046U] != 1U || game.ram[0x0058U] != 0x10U ||
        game.ram[0x0110U] != 1U) return 4;

    /* Non-Goomba walkers receive the same SetStun handoff without the
     * ShellOrBlockDefeat d5 write. */
    mysmb_test_prepare_enemy(&game, 0U, 0U);
    game.ram[0x0544U] = 0x23U;
    mysmb_objects_step_normal_enemy_terrain(&game, 0U);
    if (game.ram[0x0544U] != 0U || game.ram[0x001eU] != 2U ||
        game.ram[0x00cfU] != 0x4eU || game.ram[0x00a0U] != 0xfdU) return 5;

    return 0;
}