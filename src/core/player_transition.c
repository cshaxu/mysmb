#include "core/player.h"

/* ROM $b213-$b21e ChgAreaMode/ExitCAPipe, shared by pipe, vine and NextArea. */
void mysmb_player_change_area_mode(struct mysmb_game *game)
{
    ++game->ram[0x0774U];
    game->ram[0x0772U] = 0U;
    game->ram[0x0722U] = 0U;
}

/* ROM $b1dd SetEntr. */
void mysmb_player_set_entrance(struct mysmb_game *game)
{
    game->ram[0x0752U] = 2U;
    mysmb_player_change_area_mode(game);
}

/* ROM $b1c7-$b1dc Vine_AutoClimb/AutoClimb. */
void mysmb_player_step_auto_climb(struct mysmb_game *game)
{
    if (game->ram[0x00b5U] == 0U && game->ram[0x00ceU] < 0xe4U) {
        mysmb_player_set_entrance(game);
        return;
    }
    game->ram[0x0758U] = 8U;
    game->ram[0x001dU] = 3U;
    mysmb_player_auto_control(game, 8U);
}

/* ROM $b200-$b205 MovePlayerYAxis, low-byte addition only. */
void mysmb_player_move_y_axis(struct mysmb_game *game, mysmb_u8 amount)
{
    game->ram[0x00ceU] = (mysmb_u8)(game->ram[0x00ceU] + amount);
}

/* ROM $b20b ChgAreaPipe: DEC always executes, including 00 -> ff. */
static void mysmb_player_change_area_pipe(struct mysmb_game *game, mysmb_u8 mode)
{
    --game->ram[0x06deU];
    if (game->ram[0x06deU] != 0U) return;
    game->ram[0x0752U] = mode;
    mysmb_player_change_area_mode(game);
}

/* ROM $b1e5-$b1ff VerticalPipeEntry reads the selector after scrolling. */
void mysmb_player_step_vertical_pipe(struct mysmb_game *game)
{
    mysmb_u8 mode;
    mysmb_player_move_y_axis(game, 1U);
    mysmb_player_update_scroll(game);
    mode = 0U;
    if (game->ram[0x06d6U] == 0U)
        mode = game->ram[0x074eU] == 3U ? 2U : 1U;
    mysmb_player_change_area_pipe(game, mode);
}

/* ROM $b21f-$b232 EnterSidePipe/RightPipe. */
void mysmb_player_enter_side_pipe(struct mysmb_game *game)
{
    mysmb_u8 buttons;
    game->ram[0x0057U] = 8U;
    buttons = 1U;
    if ((game->ram[0x0086U] & 0x0fU) == 0U) {
        game->ram[0x0057U] = 0U;
        buttons = 0U;
    }
    mysmb_player_auto_control(game, buttons);
}

/* ROM $b206 SideExitPipeEntry chooses mode 2 after its child returns. */
void mysmb_player_step_side_pipe(struct mysmb_game *game)
{
    mysmb_player_enter_side_pipe(game);
    mysmb_player_change_area_pipe(game, 2U);
}
