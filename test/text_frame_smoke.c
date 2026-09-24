#include "game/game.h"
#include "game/render.h"
#include "platform/text/text_frame.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_render_frame render_frame;
    struct mysmb_text_frame text_frame;

    mysmb_game_initialize(&game);
    game.name_table[0][0U] = 0x24U;
    game.name_table[0][31U] = 0x52U;
    game.name_table[0][32U] = 0x82U;
    game.ram[0x0770U] = 1U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00ceU] = 0xb0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x60U;
    game.ram[0x00cfU] = 0xb8U;
    mysmb_render_build(&game, &render_frame);
    mysmb_text_frame_build(&render_frame, &text_frame);
    if (text_frame.cells[0].character != ' ' ||
        text_frame.cells[0].color != MYSMB_TEXT_COLOR_SKY ||
        text_frame.cells[79].character != '+' ||
        text_frame.cells[80].character != '#') return 1;
    if (text_frame.cells[18U * MYSMB_TEXT_COLUMNS + 20U].character != '@' ||
        text_frame.cells[18U * MYSMB_TEXT_COLUMNS + 20U].color != MYSMB_TEXT_COLOR_ACTOR ||
        text_frame.cells[19U * MYSMB_TEXT_COLUMNS + 30U].character != 'g' ||
        text_frame.cells[19U * MYSMB_TEXT_COLUMNS + 30U].color != MYSMB_TEXT_COLOR_ENEMY) {
        return 1;
    }
    return 0;
}
