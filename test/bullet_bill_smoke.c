#include "game/game.h"
#include "game/objects.h"
/* PlayerCtrlRoutine has already run before source object collisions.  These
 * direct object tests therefore provide the control-0 primary box that the
 * ROM left in $04ac-$04af (relative X + 2/+14, Y + 8/+32). */
static void source_player_box(struct mysmb_game *game)
{
    mysmb_u8 x;

    x = (mysmb_u8)(game->ram[0x0086U] - game->ram[0x071cU]);
    game->ram[0x04acU] = (mysmb_u8)(x + 2U);
    game->ram[0x04adU] = (mysmb_u8)(game->ram[0x00ceU] + 8U);
    game->ram[0x04aeU] = (mysmb_u8)(x + 14U);
    game->ram[0x04afU] = (mysmb_u8)(game->ram[0x00ceU] + 32U);
}

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 8U;
    game.ram[0x001eU] = 0x20U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x00a0U] = 0xfdU;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    mysmb_objects_step_bullet_bills(&game);
    if (game.ram[0x00b6U] != 0U || game.ram[0x00cfU] != 0x6dU ||
        game.ram[0x00a0U] != 0xfdU || game.ram[0x0434U] != 0x1cU) return 1;
    mysmb_game_initialize(&game);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 8U;
    game.ram[0x001eU] = 1U;
    game.ram[0x0046U] = 1U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x0773U] = 1U;
    mysmb_objects_step_bullet_bills(&game);
    if (game.ram[0x0220U] != 0x50U || game.ram[0x0221U] != 0xfcU ||
        game.ram[0x0222U] != 3U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0x50U || game.ram[0x0225U] != 0xfcU ||
        game.ram[0x0226U] != 3U || game.ram[0x0227U] != 0x48U ||
        game.ram[0x0228U] != 0x58U || game.ram[0x0229U] != 0xe8U ||
        game.ram[0x022dU] != 0xe7U || game.ram[0x0231U] != 0xeaU ||
        game.ram[0x0235U] != 0xe9U) return 1;
    game.ram[0x0046U] = 2U;
    mysmb_objects_step_bullet_bills(&game);
    if (game.ram[0x0221U] != 0xfcU || game.ram[0x0222U] != 0x43U ||
        game.ram[0x0225U] != 0xfcU || game.ram[0x0226U] != 0x43U ||
        game.ram[0x0229U] != 0xe7U || game.ram[0x022aU] != 0x43U ||
        game.ram[0x022dU] != 0xe8U || game.ram[0x022eU] != 0x43U ||
        game.ram[0x0231U] != 0xe9U || game.ram[0x0235U] != 0xeaU) return 1;
    mysmb_game_initialize(&game);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 1U;
    game.ram[0x0499U] = 0U;
    game.ram[0x0011U] = 1U;
    game.ram[0x0018U] = 8U;
    game.ram[0x0089U] = 0x40U;
    game.ram[0x00b8U] = 1U;
    game.ram[0x00d1U] = 0x70U;
    game.ram[0x049bU] = 9U;
    game.ram[0x005aU] = 0x18U;
    source_player_box(&game);
    mysmb_objects_check_bullet_bill_stomp(&game);
    if (game.ram[0x0020U] != 0x20U || game.ram[0x00d1U] != 0x6eU ||
        game.ram[0x00a2U] != 0U || game.ram[0x0436U] != 0U ||
        game.ram[0x005aU] != 0U || game.ram[0x009fU] != 0xfdU) return 1;
    mysmb_game_initialize(&game);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 1U;
    game.ram[0x0499U] = 0U;
    game.ram[0x0011U] = 1U;
    game.ram[0x0018U] = 7U;
    game.ram[0x0089U] = 0x40U;
    game.ram[0x00b8U] = 1U;
    game.ram[0x00d1U] = 0x70U;
    game.ram[0x049bU] = 9U;
    game.ram[0x005aU] = 1U;
    source_player_box(&game);
    mysmb_objects_check_bloober_stomp(&game);
    if (game.ram[0x0020U] != 0x20U || game.ram[0x00d1U] != 0x6eU ||
        game.ram[0x00a2U] != 0U || game.ram[0x0436U] != 0U ||
        game.ram[0x005aU] != 0U || game.ram[0x009fU] != 0xfdU) return 1;
    mysmb_game_initialize(&game);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 1U;
    game.ram[0x0499U] = 0U;
    game.ram[0x0011U] = 1U;
    game.ram[0x0018U] = 8U;
    game.ram[0x0070U] = 1U;
    game.ram[0x0089U] = 0x40U;
    game.ram[0x00b8U] = 1U;
    game.ram[0x00d1U] = 0x70U;
    game.ram[0x049bU] = 9U;
    source_player_box(&game);
    mysmb_objects_check_bullet_bill_stomp(&game);
    if (game.ram[0x0020U] != 0U || game.ram[0x009fU] != 1U || game.ram[0x0493U] != 0U) return 1;
    mysmb_game_initialize(&game);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 1U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x0499U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0491U] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 17U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 3U;
    source_player_box(&game);
    mysmb_objects_check_lakitu_stomp(&game);
    if (game.ram[0x001eU] != 0x20U || game.ram[0x00cfU] != 0x6eU ||
        game.ram[0x00a0U] != 0U || game.ram[0x0434U] != 0U ||
        game.ram[0x0058U] != 0U || game.ram[0x009fU] != 0xfdU ||
        game.ram[0x0110U] != 5U || game.ram[0x012cU] != 0x30U) return 1;
    /* BulletBillCheepCheep water route: PRNG height choice, right extent
     * carry, timer and normal Cheep checkpoint are source-owned. */
    mysmb_game_initialize(&game);
    game.ram[0x074eU] = 0U;
    game.ram[0x075fU] = 1U;
    game.ram[0x071bU] = 2U;
    game.ram[0x071dU] = 0xf0U;
    game.ram[0x07a7U] = 0U;
    mysmb_enemy_step_bullet_bill_cheep_frenzy(&game, 0U);
    if (game.ram[0x0016U] != 11U || game.ram[0x000fU] != 1U ||
        game.ram[0x0087U] != 0x10U || game.ram[0x006eU] != 3U ||
        game.ram[0x00cfU] != 0x40U || game.ram[0x078fU] != 0x20U) return 101;
    /* Land route fires a Bill only when none is already active. */
    mysmb_game_initialize(&game);
    game.ram[0x074eU] = 1U;
    mysmb_enemy_step_bullet_bill_cheep_frenzy(&game, 0U);
    if (game.ram[0x0016U] != 8U || game.ram[0x000fU] != 1U ||
        (game.ram[0x00feU] & 8U) == 0U) return 102;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 8U;
    game.ram[0x000fU + 1U] = 0U;
    mysmb_enemy_step_bullet_bill_cheep_frenzy(&game, 1U);
    if (game.ram[0x000fU + 1U] != 0U) return 103;
    return 0;
}
