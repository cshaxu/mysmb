#include "game/game.h"
#include "game/player.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    /* PlayerLoseLife keeps a surviving solo player in the same world, derives
     * the original half-way page, and hands area setup to mode task zero. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 1U;
    game.ram[0x000eU] = 6U;
    game.ram[0x075aU] = 2U;
    game.ram[0x075fU] = 0U;
    game.ram[0x075cU] = 0U;
    game.ram[0x071aU] = 7U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x075aU] != 1U || game.ram[0x075bU] != 5U ||
        game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x000eU] != 0U || game.ram[0x0754U] != 1U ||
        game.ram[0x00fcU] != 0x80U) return 1;

    /* The last solo life enters the original three-stage game-over mode. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 1U;
    game.ram[0x000eU] = 6U;
    game.ram[0x075aU] = 0U;
    game.ram[0x075fU] = 4U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 3U || game.ram[0x0772U] != 0U ||
        game.ram[0x075aU] != 0xffU) return 2;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0772U] != 1U || game.ram[0x00fcU] != 2U) return 3;
    /* The ROM-free mode smoke has no owner-local text source.  The dedicated
     * local area smoke verifies its ScreenRoutines-to-GameOver output route. */
    game.ram[0x0772U] = 2U;
    game.ram[0x07a0U] = 0U;
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x07fdU] != 4U) return 4;

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
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x0753U] != 1U || game.ram[0x075aU] != 2U ||
        game.ram[0x075fU] != 6U) return 5;

    /* PlayerEndLevel owns the level increment while NextArea owns the new
     * area task, timer reload request, screen gate, and checkpoint reset. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 1U;
    game.ram[0x000eU] = 5U;
    game.ram[0x0746U] = 5U;
    game.ram[0x075cU] = 1U;
    game.ram[0x0760U] = 2U;
    game.ram[0x075bU] = 6U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x90U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x075cU] != 2U || game.ram[0x0760U] != 3U ||
        game.ram[0x0772U] != 0U || game.ram[0x075bU] != 0U ||
        game.ram[0x0757U] == 0U) return 6;

    /* PlayerEndWorld returns worlds one through seven to game mode with the
     * first area and level records reset for the following world. */
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 2U;
    game.ram[0x0772U] = 4U;
    game.ram[0x075fU] = 2U;
    game.ram[0x0760U] = 3U;
    game.ram[0x075cU] = 2U;
    game.ram[0x07a1U] = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x075fU] != 3U || game.ram[0x0760U] != 0U ||
        game.ram[0x075cU] != 0U || game.ram[0x0757U] == 0U) return 7;

    /* HandlePipeEntry selects the original middle-pipe destination before
     * VerticalPipeEntry starts its 48-frame transition. */
    mysmb_game_initialize(&game);
    game.ram[0x000bU] = MYSMB_BUTTON_DOWN;
    game.ram[0x06d6U] = 1U;
    game.ram[0x0086U] = 0x80U;
    game.ram[0x075fU] = 0U;
    if (mysmb_player_handle_vertical_pipe(&game, 0x10U, 0x11U) == 0U ||
        game.ram[0x075fU] != 4U || game.ram[0x0760U] != 0U ||
        game.ram[0x075cU] != 0U || game.ram[0x000eU] != 3U ||
        game.ram[0x06deU] != 0x30U) return 8;
    return 0;
}
