#include "core/dispatcher.h"
#include "core/frame_root.h"
#include "core/player.h"

/* ROM $b04a GameRoutines. Child bodies keep their separate proof status. */
void mysmb_game_routines(struct mysmb_game *game)
{
    mysmb_game_jump_engine_state(game, 0xb04eU, game->ram[0x000eU]);
    switch (game->ram[0x000eU]) {
    case 0U: mysmb_player_initialize_entrance(game); break;
    case 1U: mysmb_player_step_auto_climb(game); break;
    case 2U: mysmb_player_step_side_pipe(game); break;
    case 3U: mysmb_player_step_vertical_pipe(game); break;
    case 4U: mysmb_player_step_flagpole_slide(game); break;
    case 5U: mysmb_player_step_end_level(game); break;
    case 6U: mysmb_game_lose_life(game); break;
    case 7U: mysmb_player_finish_normal_entrance(game); break;
    case 8U: mysmb_player_step(game, game->ram[0x06fcU]); break;
    case 9U: mysmb_player_step_change_size(game); break;
    case 10U: mysmb_player_step_injury_blink(game, game->ram[0x06fcU]); break;
    case 11U: mysmb_player_step_death(game); break;
    case 12U: mysmb_player_step_fire_flower(game); break;
    }
}

/* ROM $b0e6 AutoControlPlayer falls into PlayerCtrlRoutine. */
void mysmb_player_auto_control(struct mysmb_game *game, mysmb_u8 buttons)
{
    game->ram[0x06fcU] = buttons;
    mysmb_player_step(game, buttons);
}

/* ROM $b069-$b0e5 PlayerEntrance through ExitEntr. Children may change
 * coordinates, so OffVine tests the post-AutoControlPlayer X byte. */
void mysmb_player_finish_normal_entrance(struct mysmb_game *game)
{
    mysmb_u8 buttons;
    if (game->ram[0x0752U] != 2U) {
        if (game->ram[0x00ceU] < 0x30U) {
            mysmb_player_auto_control(game, 0U);
            return;
        }
        if (game->ram[0x0710U] == 6U || game->ram[0x0710U] == 7U) {
            if (game->ram[0x03c4U] == 0U) {
                mysmb_player_auto_control(game, 1U);
                return;
            }
            mysmb_player_enter_side_pipe(game);
            --game->ram[0x06deU];
            if (game->ram[0x06deU] == 0U) {
                ++game->ram[0x0769U];
                mysmb_game_next_area(game);
            }
            return;
        }
    }
    else if (game->ram[0x0758U] == 0U) {
        mysmb_player_move_y_axis(game, 0xffU);
        if (game->ram[0x00ceU] >= 0x91U) return;
    }
    else {
        if (game->ram[0x0399U] != 0x60U) return;
        buttons = 1U;
        if (game->ram[0x00ceU] >= 0x99U) {
            game->ram[0x001dU] = 3U;
            game->ram[0x05b4U] = 8U;
            buttons = 8U;
        }
        game->ram[0x0716U] = buttons == 8U ? 1U : 0U;
        mysmb_player_auto_control(game, buttons);
        if (game->ram[0x0086U] < 0x48U) return;
    }
    game->ram[0x000eU] = 8U;
    game->ram[0x0033U] = 1U;
    game->ram[0x0752U] = 0U;
    game->ram[0x0716U] = 0U;
    game->ram[0x0758U] = 0U;
}
