#include "core/game.h"

static int mysmb_pause_case(mysmb_u8 mode, mysmb_u8 task, mysmb_u8 status,
                            mysmb_u8 timer, mysmb_u8 audio, mysmb_u8 buttons,
                            mysmb_u8 expected_status, mysmb_u8 expected_timer,
                            mysmb_u8 expected_audio)
{
    struct mysmb_game game;
    struct mysmb_frame frame;
    struct mysmb_input input;

    mysmb_game_initialize(&game);
    mysmb_game_frame_initialize(&frame);
    game.ram[0x0770U] = mode;
    game.ram[0x0772U] = task;
    game.ram[0x0776U] = status;
    game.ram[0x0777U] = timer;
    game.ram[0x00faU] = audio;
    game.ram[0x074aU] = 0U;
    input.buttons2 = 0U;
    input.buttons = buttons;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != mode || game.ram[0x0772U] != task ||
        game.ram[0x0776U] != expected_status ||
        game.ram[0x0777U] != expected_timer ||
        game.ram[0x00faU] != expected_audio) return 1;
    if (mysmb_game_is_paused(&game) !=
        ((expected_status & 1U) != 0U ? 1U : 0U)) return 1;
    return 0;
}

int main(void)
{
    if (mysmb_pause_case(0U, 3U, 0x81U, 0x19U, 0U, 0U,
                         0x81U, 0x19U, 0U) != 0) return 1;
    if (mysmb_pause_case(1U, 2U, 0x81U, 0x19U, 0U, 0U,
                         0x81U, 0x19U, 0U) != 0) return 2;
    if (mysmb_pause_case(1U, 3U, 0x01U, 0x2aU, 0U, 0U,
                         0x01U, 0x29U, 0U) != 0) return 3;
    if (mysmb_pause_case(1U, 3U, 0x81U, 0U, 0U, 0U,
                         0x01U, 0U, 0U) != 0) return 4;
    if (mysmb_pause_case(1U, 3U, 0U, 0U, 0U, MYSMB_BUTTON_START,
                         0x81U, 0x2bU, 1U) != 0) return 5;
    if (mysmb_pause_case(1U, 3U, 0x81U, 0U, 0U, MYSMB_BUTTON_START,
                         0x81U, 0U, 0U) != 0) return 6;
    return 0;
}
