#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    unsigned int index;

    mysmb_game_initialize(&game);
    input.buttons = 0U;
    for (index = 0U; index < 120U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }

    if (game.frame_number != 120UL || frame.actor_y != 184U ||
        frame.actor_x <= 24U) {
        return 1;
    }

    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    return frame.title_started == 1U ? 0 : 1;
}
