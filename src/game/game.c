#include "game/game.h"

void mysmb_game_initialize(struct mysmb_game *game)
{
    game->frame_number = 0UL;
    game->actor_x = 24U;
    game->actor_direction = 1U;
    game->title_started = 0U;
}

void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame)
{
    if ((input->buttons & MYSMB_BUTTON_START) != 0U) {
        game->title_started = 1U;
    }

    if ((input->buttons & MYSMB_BUTTON_LEFT) != 0U) {
        game->actor_direction = 0U;
    }
    if ((input->buttons & MYSMB_BUTTON_RIGHT) != 0U) {
        game->actor_direction = 1U;
    }

    if (game->actor_direction != 0U) {
        if (game->actor_x < (MYSMB_SCREEN_WIDTH - 24U)) {
            game->actor_x = (mysmb_u16)(game->actor_x + 1U);
        }
        else {
            game->actor_direction = 0U;
        }
    }
    else if (game->actor_x > 24U) {
        game->actor_x = (mysmb_u16)(game->actor_x - 1U);
    }
    else {
        game->actor_direction = 1U;
    }

    game->frame_number++;
    frame->actor_x = game->actor_x;
    frame->actor_y = 184U;
    frame->title_started = game->title_started;
}
