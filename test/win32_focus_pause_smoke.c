#include "game/game.h"
#include "platform/win32/focus_pause.h"

static struct mysmb_game game;
static struct mysmb_frame frame;
static struct mysmb_win32_focus_pause focus;

static void setup(mysmb_u8 mode, mysmb_u8 task)
{
    mysmb_game_initialize(&game);
    mysmb_game_frame_initialize(&frame);
    game.ram[0x0770U] = mode;
    game.ram[0x0772U] = task;
    game.ram[0x0776U] = 0U;
    game.ram[0x0777U] = 0U;
    game.ram[0x074aU] = 0U;
    mysmb_win32_focus_pause_initialize(&focus);
    mysmb_win32_focus_pause_gained(&focus);
}

static void tick(mysmb_u8 buttons)
{
    struct mysmb_input input;
    input.buttons = buttons;
    input.buttons2 = 0U;
    mysmb_game_tick(&game, &input, &frame);
    mysmb_win32_focus_pause_after_tick(&focus, &game);
}

int main(void)
{
    mysmb_u8 buttons;

    setup(0U, 0U);
    mysmb_win32_focus_pause_lost(&focus, 1U, &game);
    if (focus.pending != 0U ||
        mysmb_win32_focus_pause_buttons(&focus, &game,
            MYSMB_BUTTON_START | MYSMB_BUTTON_A) != 0U) return 1;
    mysmb_win32_focus_pause_gained(&focus);
    if (mysmb_win32_focus_pause_buttons(&focus, &game,
            MYSMB_BUTTON_START) != 0U) return 2;
    mysmb_win32_focus_pause_buttons(&focus, &game, 0U);
    if (mysmb_win32_focus_pause_buttons(&focus, &game,
            MYSMB_BUTTON_START) != MYSMB_BUTTON_START) return 3;

    setup(1U, 3U);
    mysmb_win32_focus_pause_lost(&focus, 1U, &game);
    mysmb_win32_focus_pause_lost(&focus, 1U, &game);
    if (focus.pending == 0U) return 4;
    buttons = mysmb_win32_focus_pause_buttons(&focus, &game, 0U);
    if (buttons != MYSMB_BUTTON_START) return 5;
    tick(buttons);
    if (mysmb_game_is_paused(&game) == 0U || focus.pending != 0U ||
        game.ram[0x00faU] != 1U) return 6;
    mysmb_win32_focus_pause_gained(&focus);
    if (mysmb_win32_focus_pause_buttons(&focus, &game,
            MYSMB_BUTTON_START) != 0U) return 7;
    mysmb_win32_focus_pause_buttons(&focus, &game, 0U);
    if (mysmb_win32_focus_pause_buttons(&focus, &game,
            MYSMB_BUTTON_START) != MYSMB_BUTTON_START) return 8;

    setup(1U, 3U);
    game.ram[0x0777U] = 2U;
    game.ram[0x074aU] = MYSMB_BUTTON_START;
    mysmb_win32_focus_pause_lost(&focus, 1U, &game);
    mysmb_win32_focus_pause_gained(&focus);
    buttons = mysmb_win32_focus_pause_buttons(&focus, &game,
        MYSMB_BUTTON_START | MYSMB_BUTTON_A);
    if (buttons != 0U) return 9;
    tick(buttons);
    if (game.ram[0x0777U] != 1U || game.ram[0x074aU] != 0U) return 10;
    buttons = mysmb_win32_focus_pause_buttons(&focus, &game,
        MYSMB_BUTTON_START);
    if (buttons != 0U) return 11;
    tick(buttons);
    if (game.ram[0x0777U] != 0U) return 12;
    buttons = mysmb_win32_focus_pause_buttons(&focus, &game,
        MYSMB_BUTTON_START);
    if (buttons != MYSMB_BUTTON_START) return 13;
    tick(buttons);
    if (mysmb_game_is_paused(&game) == 0U || focus.pending != 0U) return 14;
    if (mysmb_win32_focus_pause_buttons(&focus, &game,
            MYSMB_BUTTON_START) != 0U) return 15;

    setup(1U, 3U);
    game.ram[0x0776U] = 1U;
    mysmb_win32_focus_pause_lost(&focus, 1U, &game);
    if (focus.pending != 0U) return 16;
    setup(2U, 0U);
    if (mysmb_game_pause_input_state(&game) != MYSMB_PAUSE_INPUT_READY)
        return 17;
    mysmb_win32_focus_pause_lost(&focus, 1U, &game);
    game.ram[0x0770U] = 3U;
    if (mysmb_win32_focus_pause_buttons(&focus, &game, 0U) != 0U ||
        focus.pending != 0U) return 18;
    return 0;
}
