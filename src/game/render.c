#include "game/render.h"

enum {
    MYSMB_RENDER_OPERATING_MODE = 0x0770U,
    MYSMB_RENDER_PLAYER_PAGE = 0x006dU,
    MYSMB_RENDER_PLAYER_X = 0x0086U,
    MYSMB_RENDER_PLAYER_Y = 0x00ceU,
    MYSMB_RENDER_SCREEN_PAGE = 0x071aU,
    MYSMB_RENDER_SCREEN_X = 0x071cU,
    MYSMB_RENDER_ENEMY_FLAG = 0x000fU,
    MYSMB_RENDER_ENEMY_ID = 0x0016U,
    MYSMB_RENDER_ENEMY_PAGE = 0x006eU,
    MYSMB_RENDER_ENEMY_X = 0x0087U,
    MYSMB_RENDER_ENEMY_Y = 0x00cfU
};

static mysmb_u8 mysmb_render_relative_x(const struct mysmb_game *game,
                                        mysmb_u8 page, mysmb_u8 x,
                                        mysmb_u8 *visible)
{
    mysmb_u16 world;
    mysmb_u16 screen;
    mysmb_u16 relative;

    world = (mysmb_u16)(((mysmb_u16)page << 8U) | x);
    screen = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_RENDER_SCREEN_PAGE] << 8U) |
                          game->ram[MYSMB_RENDER_SCREEN_X]);
    if (world < screen) {
        *visible = 0U;
        return 0U;
    }
    relative = (mysmb_u16)(world - screen);
    if (relative >= 0x100U) {
        *visible = 0U;
        return 0U;
    }
    *visible = 1U;
    return (mysmb_u8)relative;
}

static void mysmb_render_append_actor(const struct mysmb_game *game,
                                      struct mysmb_render_frame *frame,
                                      mysmb_u8 page, mysmb_u8 x, mysmb_u8 y,
                                      mysmb_u8 identity)
{
    struct mysmb_render_command *command;
    mysmb_u8 visible;

    if (frame->command_count >= MYSMB_RENDER_MAX_COMMANDS) return;
    x = mysmb_render_relative_x(game, page, x, &visible);
    if (visible == 0U) return;
    command = &frame->commands[frame->command_count];
    command->kind = MYSMB_RENDER_COMMAND_ACTOR;
    command->x = x;
    command->y = y;
    command->length = 16U;
    command->data_offset = 0U;
    command->identity = identity;
    frame->command_count++;
}

void mysmb_render_build(const struct mysmb_game *game,
                        struct mysmb_render_frame *frame)
{
    mysmb_u16 index;
    mysmb_u8 row;
    mysmb_u8 slot;
    struct mysmb_render_command *command;

    frame->command_count = 0U;
    for (index = 0U; index < MYSMB_RENDER_TILE_ROWS * MYSMB_RENDER_TILE_COLUMNS;
         ++index) frame->tile_data[index] = game->ppu.name_table[0][index];
    for (row = 0U; row < MYSMB_RENDER_TILE_ROWS; ++row) {
        command = &frame->commands[frame->command_count];
        command->kind = MYSMB_RENDER_COMMAND_TILE_ROW;
        command->x = 0U;
        command->y = row;
        command->length = MYSMB_RENDER_TILE_COLUMNS;
        command->data_offset = (mysmb_u16)row * MYSMB_RENDER_TILE_COLUMNS;
        command->identity = 0U;
        frame->command_count++;
    }
    if (game->ram[MYSMB_RENDER_OPERATING_MODE] == 0U) return;
    mysmb_render_append_actor(game, frame, game->ram[MYSMB_RENDER_PLAYER_PAGE],
        game->ram[MYSMB_RENDER_PLAYER_X], game->ram[MYSMB_RENDER_PLAYER_Y], 0U);
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_RENDER_ENEMY_FLAG + slot] == 0U) continue;
        mysmb_render_append_actor(game, frame,
            game->ram[MYSMB_RENDER_ENEMY_PAGE + slot],
            game->ram[MYSMB_RENDER_ENEMY_X + slot],
            game->ram[MYSMB_RENDER_ENEMY_Y + slot],
            game->ram[MYSMB_RENDER_ENEMY_ID + slot]);
    }
}
