#include "platform/win32/focus_pause.h"

void mysmb_win32_focus_pause_initialize(struct mysmb_win32_focus_pause *state)
{
    state->focused = 0U;
    state->pending = 0U;
    state->enter_released = 0U;
    state->sent_start = 0U;
}

void mysmb_win32_focus_pause_lost(struct mysmb_win32_focus_pause *state,
    mysmb_u8 game_started, const struct mysmb_game *game)
{
    if (state->focused == 0U) return;
    state->focused = 0U;
    state->enter_released = 0U;
    if (game_started != 0U &&
        mysmb_game_pause_input_state(game) != MYSMB_PAUSE_INPUT_UNAVAILABLE)
        state->pending = 1U;
}

void mysmb_win32_focus_pause_gained(struct mysmb_win32_focus_pause *state)
{
    if (state->focused != 0U) return;
    state->focused = 1U;
    state->enter_released = 0U;
}

mysmb_u8 mysmb_win32_focus_pause_buttons(
    struct mysmb_win32_focus_pause *state, const struct mysmb_game *game,
    mysmb_u8 physical_buttons)
{
    mysmb_u8 pause_input_state;

    state->sent_start = 0U;
    if (state->pending != 0U) {
        pause_input_state = mysmb_game_pause_input_state(game);
        if (pause_input_state == MYSMB_PAUSE_INPUT_READY) {
            state->sent_start = 1U;
            return MYSMB_BUTTON_START;
        }
        if (pause_input_state == MYSMB_PAUSE_INPUT_WAIT) return 0U;
        state->pending = 0U;
        state->enter_released = 0U;
    }
    if (state->focused == 0U) return 0U;
    if ((physical_buttons & MYSMB_BUTTON_START) == 0U)
        state->enter_released = 1U;
    else if (state->enter_released == 0U)
        physical_buttons = (mysmb_u8)(physical_buttons & ~MYSMB_BUTTON_START);
    return physical_buttons;
}

void mysmb_win32_focus_pause_after_tick(
    struct mysmb_win32_focus_pause *state, const struct mysmb_game *game)
{
    if (state->sent_start != 0U && mysmb_game_is_paused(game) != 0U) {
        state->pending = 0U;
        state->enter_released = 0U;
    }
    state->sent_start = 0U;
}
