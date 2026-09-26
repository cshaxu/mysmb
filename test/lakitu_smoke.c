#include "game/game.h"
#include "game/objects.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/stream.h"

int main(void)
{
    struct mysmb_game game;

    /* PlayerLakituDiff: 64 pixels is capped at $3c, then $15-$10 yields
     * $05.  Direction zero selects the negated horizontal speed. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 17U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    mysmb_enemy_step_lakitus(&game);
    if (game.ram[0x06cbU] != 18U || game.ram[0x0058U] != 0xfbU ||
        game.ram[0x0046U] != 2U || game.ram[0x0087U] != 0x7fU ||
        game.ram[0x0401U] != 0xb0U) return 1;

    /* Beyond $3c, a left-moving Lakitu decelerates before reversing. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 17U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0U;
    game.ram[0x00a0U] = 1U;
    game.ram[0x0058U] = 2U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x10U;
    mysmb_enemy_step_lakitus(&game);
    if (game.ram[0x0058U] != 1U || game.ram[0x00a0U] != 1U ||
        game.ram[0x0087U] != 0U) return 2;

    /* A stomped Lakitu follows MoveD_EnemyVertically's $3d gravity route. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 17U;
    game.ram[0x001eU] = 0x20U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    mysmb_enemy_step_lakitus(&game);
    if (game.ram[0x00cfU] != 0x70U || game.ram[0x0417U] != 0U ||
        game.ram[0x0434U] != 0x3dU) return 3;

    /* The active frenzy request recreates Lakitu after seven timer periods. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x06cbU] = 18U;
    game.ram[0x06d1U] = 6U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071dU] = 0xf0U;
    mysmb_enemy_init_lakitu_spiny_frenzy(&game, 2U);
    if (game.ram[0x078fU] != 0x80U || game.ram[0x06d1U] != 0U ||
        game.ram[0x0013U] != 1U || game.ram[0x001aU] != 17U ||
        game.ram[0x0072U] != 2U || game.ram[0x008bU] != 0x10U ||
        game.ram[0x00d3U] != 0x20U) return 4;

    /* A normal Lakitu creates an egg in a free ordinary slot. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x06cbU] = 18U;
    game.ram[0x00ceU] = 0x2cU;
    game.ram[0x0013U] = 1U;
    game.ram[0x001aU] = 17U;
    game.ram[0x0022U] = 0U;
    game.ram[0x0072U] = 1U;
    game.ram[0x008bU] = 0x90U;
    game.ram[0x00d3U] = 0x80U;
    mysmb_enemy_init_lakitu_spiny_frenzy(&game, 3U);
    if (game.ram[0x0012U] != 1U || game.ram[0x0019U] != 18U ||
        game.ram[0x0021U] != 5U || game.ram[0x0071U] != 1U ||
        game.ram[0x008aU] != 0x90U || game.ram[0x00d2U] != 0x78U ||
        game.ram[0x00a3U] != 0xfdU || game.ram[0x0049U] != 2U) return 1;

    /* Spiny eggs select the same routine with the original $20 force. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 18U;
    game.ram[0x001eU] = 5U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x00a0U] = 0xfdU;
    mysmb_enemy_step_spiny_eggs(&game);
    if (game.ram[0x00cfU] != 0x6dU || game.ram[0x0417U] != 0U ||
        game.ram[0x0434U] != 0x20U) return 1;

    /* EnemyToBGCollisionDet lands the egg and restores ordinary Spiny state. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 18U;
    game.ram[0x001eU] = 5U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x00a0U] = 0xfdU;
    game.ram[0x0434U] = 0x20U;
    game.ram[0x0564U] = 1U;
    mysmb_enemy_step_spiny_eggs(&game);
    if (game.ram[0x001eU] != 0U || game.ram[0x00cfU] != 0x78U ||
        game.ram[0x00a0U] != 0U || game.ram[0x0434U] != 0U ||
        game.ram[0x0046U] != 1U || game.ram[0x0058U] != 8U) return 1;
    /* EndFrenzy clears every Lakitu (including slot five), clears the
     * persistent controller byte, then removes the stop controller. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 17U;
    game.ram[0x0012U] = 1U;
    game.ram[0x0019U] = 17U;
    game.ram[0x0013U] = 1U;
    game.ram[0x001aU] = 6U;
    game.ram[0x06cbU] = 18U;
    mysmb_enemy_end_frenzy(&game, 5U);
    if (game.ram[0x000fU] != 0U || game.ram[0x0012U] != 0U ||
        game.ram[0x0013U] != 1U || game.ram[0x06cbU] != 0U) return 1;
    /* ProcessEnemyData $12 must enter InitEnemyFrenzy with its current
     * ObjectOffset.  The initial controller remains in slot two while its
     * reappearance counter waits; it must not be transferred by a frame root
     * scan or another free-slot search. */
    {
        static const mysmb_u8 prg[] = { 0x00U, 18U };
        struct mysmb_area_source source;
        mysmb_u8 slot;

        mysmb_game_initialize_memory(&game, 0xfeU);
        for (slot = 0U; slot < 6U; ++slot) game.ram[0x000fU + slot] = 0U;
        source.prg = prg;
        source.prg_size = sizeof(prg);
        game.ram[0x00e9U] = 0U;
        game.ram[0x00eaU] = 0x80U;
        game.ram[0x0739U] = 0U;
        game.ram[0x073aU] = 0U;
        game.ram[0x071bU] = 0U;
        game.ram[0x071dU] = 0U;
        game.ram[0x078fU] = 0U;
        game.ram[0x06d1U] = 0U;
        if (mysmb_enemy_stream_process_current(&game, &source, 2U) != 1U ||
            game.ram[0x06cbU] != 18U || game.ram[0x078fU] != 0x80U ||
            game.ram[0x0011U] != 1U || game.ram[0x0018U] != 18U ||
            game.ram[0x001fU] != 0U || game.ram[0x0739U] != 2U) return 7;
    }
    return 0;
}