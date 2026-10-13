#ifndef MYSMB_PLATFORM_WIN32_FOCUS_PAUSE_H
#define MYSMB_PLATFORM_WIN32_FOCUS_PAUSE_H

#include "core/game.h"

struct mysmb_win32_focus_pause {
    mysmb_u8 focused;
    mysmb_u8 pending;
    mysmb_u8 enter_released;
    mysmb_u8 sent_start;
};

void mysmb_win32_focus_pause_initialize(struct mysmb_win32_focus_pause *state);
void mysmb_win32_focus_pause_lost(struct mysmb_win32_focus_pause *state,
    mysmb_u8 game_started, const struct mysmb_game *game);
void mysmb_win32_focus_pause_gained(struct mysmb_win32_focus_pause *state);
mysmb_u8 mysmb_win32_focus_pause_buttons(
    struct mysmb_win32_focus_pause *state, const struct mysmb_game *game,
    mysmb_u8 physical_buttons);
void mysmb_win32_focus_pause_after_tick(
    struct mysmb_win32_focus_pause *state, const struct mysmb_game *game);

#endif
