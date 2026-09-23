#include "game/game.h"

void mysmb_game_initialize(struct mysmb_game *game)
{
    mysmb_u16 index;

    for (index = 0U; index < 0x0800U; ++index) {
        game->ram[index] = 0xffU;
    }
    mysmb_game_initialize_memory(game, 0xfeU);
    game->frame_number = 0UL;
}

/* Translation of ROM $90cc-$90e6 (InitializeMemory). */
void mysmb_game_initialize_memory(struct mysmb_game *game, mysmb_u8 initial_y)
{
    mysmb_u8 page;
    mysmb_u8 offset;

    page = 0x07U;
    offset = initial_y;
    do {
        do {
            if (page != 0x01U || offset < 0x60U) {
                game->ram[(mysmb_u16)((mysmb_u16)page * 0x0100U + offset)] = 0U;
            }
            offset = (mysmb_u8)(offset - 1U);
        } while (offset != 0xffU);
        page = (mysmb_u8)(page - 1U);
    } while (page != 0xffU);
}

void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame)
{
    game->frame_number++;
    frame->sprite0_y = game->ram[0x0200U];
    frame->sprite0_x = game->ram[0x0203U];
    frame->start_pressed = (input->buttons & MYSMB_BUTTON_START) != 0U;
}
