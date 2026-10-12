#include "core/game.h"
#include "core/area.h"
#include "core/player.h"

int main(void)
{
    static unsigned char pipe_prg[32768];
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    /* PlayerLoseLife keeps a surviving solo player in the same world, derives
     * the original half-way page, and hands area setup to mode task zero. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    /* GameMode task 3 is GameCoreRoutine; task 1 is ScreenRoutines. */
    game.ram[0x0772U] = 3U;
    game.ram[0x000eU] = 6U;
    game.ram[0x075aU] = 2U;
    game.ram[0x075fU] = 0U;
    game.ram[0x075cU] = 0U;
    game.ram[0x071aU] = 7U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x075aU] != 1U || game.ram[0x075bU] != 5U ||
        game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x000eU] != 0U || game.ram[0x0754U] != 1U ||
        game.ram[0x00fcU] != 0x80U) return 1;

    /* HalfwayPageNybbles chooses high versus low nybbles from the area LSB,
     * and increments its world-derived index only for areas three and four. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    /* GameMode task 3 is GameCoreRoutine; task 1 is ScreenRoutines. */
    game.ram[0x0772U] = 3U;
    game.ram[0x000eU] = 6U;
    game.ram[0x075aU] = 2U;
    game.ram[0x075fU] = 0U;
    game.ram[0x075cU] = 1U;
    game.ram[0x071aU] = 7U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x075bU] != 6U || game.ram[0x0772U] != 0U) return 21;
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    /* GameMode task 3 is GameCoreRoutine; task 1 is ScreenRoutines. */
    game.ram[0x0772U] = 3U;
    game.ram[0x000eU] = 6U;
    game.ram[0x075aU] = 2U;
    game.ram[0x075fU] = 0U;
    game.ram[0x075cU] = 2U;
    game.ram[0x071aU] = 7U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x075bU] != 4U || game.ram[0x0772U] != 0U) return 22;

    /* The last solo life enters the original three-stage game-over mode. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    /* GameMode task 3 is GameCoreRoutine; task 1 is ScreenRoutines. */
    game.ram[0x0772U] = 3U;
    game.ram[0x000eU] = 6U;
    game.ram[0x075aU] = 0U;
    game.ram[0x075fU] = 4U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 3U || game.ram[0x0772U] != 0U ||
        game.ram[0x075aU] != 0xffU) return 2;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0772U] != 1U || game.ram[0x00fcU] != 2U) return 3;
    /* RunGameTimer is a GameEngine leaf and must not append a timer command
     * or reload its divider while GameOverMode runs ScreenRoutines. */
    game.ram[0x000eU] = 8U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x0787U] = 0U;
    game.ram[0x07f8U] = 3U;
    game.ram[0x07f9U] = 0U;
    game.ram[0x07faU] = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0787U] != 0U) return 31;
    /* The ROM-free mode smoke has no owner-local text source.  The dedicated
     * local area smoke verifies its ScreenRoutines-to-GameOver output route. */
    game.ram[0x0772U] = 2U;
    game.ram[0x07a0U] = 2U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 3U || game.ram[0x0772U] != 2U ||
        game.ram[0x0774U] != 0U) return 32;
    game.ram[0x07a0U] = 0U;
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x07fdU] != 4U || game.ram[0x00fcU] != 0x80U) return 4;

    /* Game-over termination transposes an eligible second player and resumes
     * their complete seven-byte record rather than returning to title. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 3U;
    game.ram[0x0772U] = 2U;
    game.ram[0x077aU] = 1U;
    game.ram[0x0753U] = 0U;
    game.ram[0x075aU] = 0xffU;
    game.ram[0x075fU] = 1U;
    game.ram[0x0761U] = 2U;
    game.ram[0x0766U] = 6U;
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x0753U] != 1U || game.ram[0x075aU] != 2U ||
        game.ram[0x075fU] != 6U || game.ram[0x00fcU] != 0x80U) return 5;

    /* PlayerEndLevel owns the level increment while NextArea owns the new
     * area task, timer reload request, screen gate, and checkpoint reset. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    /* GameMode task 3 is GameCoreRoutine; task 1 is ScreenRoutines. */
    game.ram[0x0772U] = 3U;
    game.ram[0x000eU] = 5U;
    game.ram[0x0746U] = 5U;
    game.ram[0x075cU] = 1U;
    game.ram[0x0760U] = 2U;
    game.ram[0x075bU] = 6U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x90U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x075cU] != 2U || game.ram[0x0760U] != 3U ||
        game.ram[0x0772U] != 0U || game.ram[0x075bU] != 0U ||
        game.ram[0x0757U] == 0U) return 6;

    /* PlayerVictoryWalk first runs AutoControlPlayer, then keeps scrolling
     * at the ROM's half-pixel cadence until the screen reaches its destination
     * page.  Reaching Mario's x target alone must not advance mode task 3. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 2U;
    game.ram[0x0772U] = 2U;
    game.ram[0x0034U] = 1U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x60U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0772U] != 2U || game.ram[0x0035U] != 2U ||
        game.ram[0x0768U] != 0x80U || game.ram[0x071cU] != 1U ||
        game.ram[0x0775U] != 1U) return 7;

    /* PlayerEndWorld returns worlds one through seven to game mode with the
     * first area and level records reset for the following world. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 2U;
    game.ram[0x0772U] = 4U;
    game.ram[0x075fU] = 2U;
    game.ram[0x0760U] = 3U;
    game.ram[0x075cU] = 2U;
    game.ram[0x07a1U] = 0U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x075fU] != 3U || game.ram[0x0760U] != 0U ||
        game.ram[0x075cU] != 0U || game.ram[0x0757U] == 0U) return 8;

    /* NMI DecTimers, rather than PlayerEndWorld, owns WorldEndTimer.  On an
     * interval-timer frame it reaches zero before the terminal leaf runs. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 2U;
    game.ram[0x0772U] = 4U;
    game.ram[0x075fU] = 2U;
    game.ram[0x07a1U] = 1U;
    game.ram[0x077fU] = 0U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x07a1U] != 0U || game.ram[0x0770U] != 1U ||
        game.ram[0x0772U] != 0U || game.ram[0x075fU] != 3U) return 10;

    /* ROM EndChkBButton ORs both saved controller latches before entering
     * TerminateGame.  The second latch must take the same title-return path. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 2U;
    game.ram[0x0772U] = 4U;
    game.ram[0x075fU] = 7U;
    game.ram[0x07a0U] = 0x44U;
    game.ram[0x06fcU] = 0U;
    game.ram[0x06fdU] = MYSMB_BUTTON_B;
    /* ReadJoypads refreshes both saved latches at the NMI boundary.  Feed
     * port two through the input seam instead of manufacturing stale RAM. */
    input.buttons2 = MYSMB_BUTTON_B;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x07fcU] != 1U || game.ram[0x075aU] != 0xffU ||
        game.ram[0x00fcU] != 0x80U || game.ram[0x07fdU] != 7U ||
        game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x07a0U] != 0U) return 11;

    /* VictoryMode calls its selected leaf first.  A continuing bridge task
     * remains task zero and therefore branches to AutoPlayer before the
     * slot-zero EnemiesAndLoopsCore turn. */
    {
        static const mysmb_u8 prg[1] = { 0U };

        mysmb_game_initialize(&game);
        mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
        game.ram[0x0770U] = 2U;
        game.ram[0x0772U] = 0U;
        game.ram[0x0368U] = 0U;
        game.ram[0x0016U] = 45U;
        game.ram[0x0364U] = 2U;
        game.ram[0x03c5U] = 0x5aU;
        game.ram[0x03d0U] = 0xa5U;
        input.buttons2 = 0U;
        input.buttons = 0U;
        mysmb_game_tick(&game, &input, &frame);
        if (game.ram[0x0772U] != 0U || game.ram[0x03c5U] != 0x5aU ||
            game.ram[0x03d0U] != 0xa5U) return 12;
    }

    /* SetupVictoryMode advances task one to two before VictoryMode checks
     * it, so the same frame executes only current slot zero.  The normal
     * enemy core clears this source-owned attribute before graphics; a
     * direct Retainer-only shortcut cannot produce this result. */
    {
        static const mysmb_u8 prg[1] = { 0U };

        mysmb_game_initialize(&game);
        mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
        game.ram[0x0770U] = 2U;
        game.ram[0x0772U] = 1U;
        game.ram[0x000fU] = 1U;
        game.ram[0x0016U] = 6U;
        game.ram[0x0008U] = 3U;
        game.ram[0x03c5U] = 0x5aU;
        game.ram[0x0747U] = 0xffU;
        input.buttons2 = 0U;
        input.buttons = 0U;
        mysmb_game_tick(&game, &input, &frame);
        if (game.ram[0x0772U] != 2U || game.ram[0x0008U] != 0U ||
            game.ram[0x03c5U] != 0U) return 13;
    }

    /* RetainerObject is a RunEnemyObjectsCore special-ID branch.  The outer
     * VictoryMode call reaches its three-row renderer through the same one
     * current-slot dispatcher, never through a root-level OAM shortcut. */
    {
        static const mysmb_u8 prg[1] = { 0U };

        mysmb_game_initialize(&game);
        mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
        game.ram[0x0770U] = 2U;
        game.ram[0x0772U] = 1U;
        game.ram[0x000fU] = 1U;
        game.ram[0x0016U] = 0x35U;
        game.ram[0x03c5U] = 0x5aU;
        input.buttons2 = 0U;
        input.buttons = 0U;
        mysmb_game_tick(&game, &input, &frame);
        if (game.ram[0x03c5U] != 0x5aU || game.ram[0x0201U] != 0xcdU) return 14;
    }

    /* HandlePipeEntry selects the original middle-pipe destination before
     * VerticalPipeEntry starts its 48-frame transition. */
    mysmb_game_initialize(&game);
    /* Explicit synthetic binding for the three source table reads. */
    pipe_prg[0x07f7U] = 5U;
    pipe_prg[0x1cb8U] = 0x12U;
    pipe_prg[0x1cceU] = 0x42U;
    game.area_prg = pipe_prg;
    game.area_prg_size = sizeof(pipe_prg);
    game.ram[0x000bU] = MYSMB_BUTTON_DOWN;
    game.ram[0x06d6U] = 1U;
    game.ram[0x0086U] = 0x80U;
    game.ram[0x075fU] = 0U;
    if (mysmb_player_handle_vertical_pipe(&game, 0x10U, 0x11U) == 0U ||
        game.ram[0x075fU] != 4U || game.ram[0x0760U] != 0U ||
        game.ram[0x0750U] != 0x42U || game.ram[0x00fcU] != 0x80U ||
        game.ram[0x075cU] != 0U || game.ram[0x000eU] != 3U ||
        game.ram[0x06deU] != 0x30U) return 9;
    return 0;
}
