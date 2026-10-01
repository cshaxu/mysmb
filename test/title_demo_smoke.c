#include "game/game.h"

int main(void)
{
    static const mysmb_u8 icon_data[8] = {
        0x07U, 0x22U, 0x49U, 0x83U, 0xceU, 0x24U, 0x24U, 0x00U
    };
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;

    mysmb_game_initialize(&game);
    input.buttons2 = 0U;
    input.buttons = 0U;
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0U;
    game.ram[0x0717U] = 0U;
    game.ram[0x0718U] = 0U;

    if (mysmb_game_title_step(&game, &input) != 1U ||
        game.ram[0x06fcU] != MYSMB_BUTTON_RIGHT ||
        game.ram[0x0717U] != 1U || game.ram[0x0718U] != 0x9aU ||
        game.ram[0x0719U] != 0U) {
        return 1;
    }

    if (mysmb_game_title_step(&game, &input) != 1U ||
        game.ram[0x06fcU] != MYSMB_BUTTON_RIGHT ||
        game.ram[0x0717U] != 1U || game.ram[0x0718U] != 0x99U) {
        return 1;
    }

    game.ram[0x0718U] = 0U;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x06fcU] != MYSMB_BUTTON_A ||
        game.ram[0x0717U] != 2U || game.ram[0x0718U] != 0x0fU) {
        return 1;
    }

    game.ram[0x0717U] = 20U;
    game.ram[0x0718U] = 0U;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x06fcU] != 0U || game.ram[0x0717U] != 21U ||
        game.ram[0x0718U] != 0xfeU) {
        return 1;
    }

    game.ram[0x0717U] = 21U;
    game.ram[0x0718U] = 0U;
    game.ram[0x0722U] = 1U;
    game.ram[0x0774U] = 0U;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x0722U] != 0U || game.ram[0x0774U] != 1U) {
        return 1;
    }
    mysmb_game_initialize(&game);
    mysmb_game_bind_title_source(&game, 0, 0U, icon_data, 8U);
    game.ram[0x077aU] = 0U;
    game.ram[0x0304U] = 0xa5U;
    game.ram[0x0306U] = 0x5aU;
    mysmb_game_draw_mushroom_icon(&game);
    if (game.ram[0x0300U] != 7U || game.ram[0x0301U] != 0x22U ||
        game.ram[0x0302U] != 0x49U || game.ram[0x0303U] != 0x83U ||
        game.ram[0x0304U] != 0xceU || game.ram[0x0305U] != 0x24U ||
        game.ram[0x0306U] != 0x24U || game.ram[0x0307U] != 0U) {
        return 1;
    }

    mysmb_game_initialize(&game);
    mysmb_game_bind_title_source(&game, 0, 0U, icon_data, 8U);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0x55U;
    game.ram[0x0780U] = 0U;
    game.ram[0x06fcU] = MYSMB_BUTTON_SELECT;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x077aU] != 1U || game.ram[0x07a2U] != 0x18U ||
        game.ram[0x0780U] != 0x10U || game.ram[0x06fcU] != 0U ||
        game.ram[0x0300U] != 7U || game.ram[0x0301U] != 0x22U ||
        game.ram[0x0304U] != 0x24U || game.ram[0x0306U] != 0xceU) {
        return 1;
    }

    mysmb_game_initialize(&game);
    /* ROM ChkSelect checks the expired DemoTimer before ChkWorldSel.  B
     * therefore starts the demo even with world selection enabled. */
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0U;
    game.ram[0x07fcU] = 1U;
    game.ram[0x076bU] = 4U;
    game.ram[0x075fU] = 4U;
    game.ram[0x0780U] = 0U;
    game.ram[0x06fcU] = MYSMB_BUTTON_B;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x076bU] != 4U || game.ram[0x075fU] != 4U ||
        game.ram[0x0780U] != MYSMB_BUTTON_B ||
        game.ram[0x06fcU] != MYSMB_BUTTON_RIGHT ||
        game.ram[0x0717U] != 1U || game.ram[0x0718U] != 0x9aU) {
        return 18;
    }

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0x55U;
    game.ram[0x0780U] = 0U;
    game.ram[0x07fcU] = 1U;
    game.ram[0x076bU] = 0U;
    game.ram[0x075fU] = 4U;
    game.ram[0x06fcU] = MYSMB_BUTTON_B;
    game.ram[0x0300U] = 0xaaU;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x076bU] != 1U || game.ram[0x075fU] != 1U ||
        game.ram[0x0766U] != 1U || game.ram[0x0760U] != 0U ||
        game.ram[0x0767U] != 0U || game.ram[0x0300U] != 4U ||
        game.ram[0x0301U] != 0x20U || game.ram[0x0302U] != 0x73U ||
        game.ram[0x0303U] != 1U || game.ram[0x0304U] != 2U ||
        game.ram[0x0305U] != 0U || game.ram[0x07a2U] != 0x18U ||
        game.ram[0x0780U] != 0x10U || game.ram[0x06fcU] != 0U) {
        return 1;
    }

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0U;
    game.ram[0x0722U] = 1U;
    game.ram[0x0774U] = 0U;
    game.ram[0x06fcU] = MYSMB_BUTTON_SELECT;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x0722U] != 0U || game.ram[0x0774U] != 1U) {
        return 1;
    }

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0U;
    game.ram[0x0722U] = 1U;
    game.ram[0x0774U] = 0U;
    game.ram[0x06fcU] = MYSMB_BUTTON_START;
    mysmb_game_title_step(&game, &input);
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x0722U] != 0U || game.ram[0x0774U] != 1U) {
        return 1;
    }

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0x55U;
    game.ram[0x06fcU] = 0U;
    game.ram[0x06fdU] = MYSMB_BUTTON_START;
    if (mysmb_game_title_step(&game, &input) != 0U ||
        game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x07a2U] != 0U) {
        return 1;
    }

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 1U;
    game.ram[0x000eU] = 0U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x000eU] != 7U) {
        return 1;
    }

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;
    game.ram[0x07a2U] = 0U;
    game.ram[0x0717U] = 1U;
    game.ram[0x0718U] = 1U;
    game.ram[0x000eU] = 6U;
    /* RunDemo calls GameCoreRoutine before its post-return comparison.  A
     * source-reachable PlayerLoseLife with one life left falls through
     * ContinueGame, which changes mode/task and clears subroutine six. */
    game.ram[0x075aU] = 1U;
    game.ram[0x0722U] = 1U;
    game.ram[0x0774U] = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x000eU] != 0U || game.ram[0x0722U] != 0U ||
        game.ram[0x0774U] != 1U) {
        return 1;
    }
    return 0;
}
