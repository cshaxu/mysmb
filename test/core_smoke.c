#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_checkpoint checkpoint;
    const mysmb_u8 title_commands[] = {
        0x20U, 0x00U, 0x02U, 0x11U, 0x12U,
        0x20U, 0x21U, 0xc2U, 0x33U, 0x00U
    };
    unsigned int index;

    mysmb_game_initialize(&game);
    input.buttons = 0U;
    for (index = 0U; index < 120U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }

    if (game.frame_number != 120UL || game.ram[0x07feU] != 0U ||
        game.ram[0x07ffU] != 0xffU || game.ram[0x015fU] != 0U ||
        game.ram[0x0160U] != 0xffU || game.ram[0x01feU] != 0xffU ||
        game.ram[0x0200U] != 0xf8U || game.ram[0x0204U] != 0xf8U ||
        game.ram[0x02fcU] != 0xf8U || game.ram[0x0201U] != 0U ||
        game.name_table[0][0U] != 0x24U ||
        game.name_table[1][0x03bfU] != 0x24U ||
        game.name_table[0][0x03c0U] != 0U ||
        game.name_table[1][0x03ffU] != 0U) {
        return 1;
    }

    game.ram[0x07d7U] = 0xffU;
    mysmb_game_initialize_memory(&game, 0xd6U);
    if (game.ram[0x07d6U] != 0U || game.ram[0x07d7U] != 0xffU) {
        return 1;
    }
    /* InitializeGame restores this after its partial RAM clear. */
    game.ram[0x07a2U] = 0x18U;
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;

    if (mysmb_game_apply_title_commands(&game, title_commands,
                                        (mysmb_u16)sizeof(title_commands)) == 0U ||
        game.name_table[0][0U] != 0x11U || game.name_table[0][1U] != 0x12U ||
        game.name_table[0][0x21U] != 0x33U ||
        game.name_table[0][0x41U] != 0x33U) {
        return 1;
    }

    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    mysmb_game_checkpoint(&game, &checkpoint);
    if (frame.start_pressed != 1U || frame.operating_mode != 1U ||
        frame.operating_mode_task != 0U || checkpoint.demo_timer != 0U ||
        checkpoint.operating_mode != 1U || checkpoint.operating_mode_task != 0U ||
        game.ram[0x0757U] != 1U || game.ram[0x075dU] != 1U ||
        game.ram[0x0764U] != 1U) {
        return 1;
    }

    mysmb_game_tick(&game, &input, &frame);
    return frame.start_pressed == 0U ? 0 : 1;
}
