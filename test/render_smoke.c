#include "core/game.h"
#include "game/render.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_render_frame frame;

    mysmb_game_initialize(&game);
    game.ppu.name_table[0][0U] = 0x51U;
    mysmb_render_build(&game, &frame);
    if (frame.command_count != MYSMB_RENDER_TILE_ROWS ||
        frame.commands[0].kind != MYSMB_RENDER_COMMAND_TILE_ROW ||
        frame.commands[29].data_offset != 928U || frame.tile_data[0] != 0x51U) {
        return 1;
    }
    game.ram[0x0770U] = 1U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00ceU] = 0xb0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x60U;
    game.ram[0x00cfU] = 0xb8U;
    mysmb_render_build(&game, &frame);
    if (frame.command_count != MYSMB_RENDER_TILE_ROWS + 2U ||
        frame.commands[30].kind != MYSMB_RENDER_COMMAND_ACTOR ||
        frame.commands[30].x != 0x40U || frame.commands[30].y != 0xb0U ||
        frame.commands[30].identity != 0U ||
        frame.commands[31].x != 0x60U || frame.commands[31].identity != 6U) {
        return 1;
    }
    game.ram[0x006eU] = 1U;
    mysmb_render_build(&game, &frame);
    return frame.command_count == MYSMB_RENDER_TILE_ROWS + 1U ? 0 : 1;
}
