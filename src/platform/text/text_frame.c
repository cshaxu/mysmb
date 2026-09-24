#include "platform/text/text_frame.h"

static mysmb_u8 mysmb_text_tile_color(mysmb_u8 tile)
{
    if (tile >= 0x80U) return MYSMB_TEXT_COLOR_GROUND;
    if (tile >= 0x50U) return MYSMB_TEXT_COLOR_BLOCK;
    if (tile >= 0x30U) return MYSMB_TEXT_COLOR_BLOCK;
    return MYSMB_TEXT_COLOR_SKY;
}

static mysmb_u8 mysmb_text_tile_character(mysmb_u8 tile)
{
    if (tile >= 0x80U) return '#';
    if (tile >= 0x50U) return '+';
    if (tile >= 0x30U) return '.';
    return ' ';
}

static mysmb_u8 mysmb_text_actor_character(mysmb_u8 identity)
{
    if (identity == 0U) return '@';
    if (identity == 6U || identity == 7U) return 'g';
    if (identity == 2U || identity == 3U) return 'k';
    if (identity >= 27U && identity <= 31U) return '*';
    if (identity == 45U) return 'B';
    return 'o';
}

static mysmb_u8 mysmb_text_actor_color(mysmb_u8 identity)
{
    return identity == 0U ? MYSMB_TEXT_COLOR_ACTOR : MYSMB_TEXT_COLOR_ENEMY;
}

static void mysmb_text_fill_background(const struct mysmb_render_frame *render_frame,
                                       struct mysmb_text_frame *text_frame)
{
    mysmb_u16 row;
    mysmb_u16 column;
    mysmb_u16 text_index;
    mysmb_u16 source_row;
    mysmb_u16 source_column;
    mysmb_u8 tile;

    for (row = 0U; row < MYSMB_TEXT_ROWS; ++row) {
        source_row = (mysmb_u16)(row * MYSMB_RENDER_TILE_ROWS / MYSMB_TEXT_ROWS);
        for (column = 0U; column < MYSMB_TEXT_COLUMNS; ++column) {
            source_column = (mysmb_u16)(column * MYSMB_RENDER_TILE_COLUMNS /
                                        MYSMB_TEXT_COLUMNS);
            tile = render_frame->tile_data[source_row * MYSMB_RENDER_TILE_COLUMNS +
                                           source_column];
            text_index = row * MYSMB_TEXT_COLUMNS + column;
            text_frame->cells[text_index].character = mysmb_text_tile_character(tile);
            text_frame->cells[text_index].color = mysmb_text_tile_color(tile);
        }
    }
}

static void mysmb_text_draw_actor(const struct mysmb_render_command *command,
                                  struct mysmb_text_frame *text_frame)
{
    mysmb_u16 left;
    mysmb_u16 top;
    mysmb_u16 right;
    mysmb_u16 bottom;
    mysmb_u16 row;
    mysmb_u16 column;
    mysmb_u8 character;
    mysmb_u8 color;

    left = (mysmb_u16)command->x * MYSMB_TEXT_COLUMNS / 256U;
    top = (mysmb_u16)command->y * MYSMB_TEXT_ROWS / 240U;
    right = ((mysmb_u16)command->x + command->length) * MYSMB_TEXT_COLUMNS / 256U;
    bottom = ((mysmb_u16)command->y + command->length) * MYSMB_TEXT_ROWS / 240U;
    if (right <= left) right = (mysmb_u16)(left + 1U);
    if (bottom <= top) bottom = (mysmb_u16)(top + 1U);
    if (right > MYSMB_TEXT_COLUMNS) right = MYSMB_TEXT_COLUMNS;
    if (bottom > MYSMB_TEXT_ROWS) bottom = MYSMB_TEXT_ROWS;
    character = mysmb_text_actor_character(command->identity);
    color = mysmb_text_actor_color(command->identity);
    for (row = top; row < bottom; ++row) {
        for (column = left; column < right; ++column) {
            text_frame->cells[row * MYSMB_TEXT_COLUMNS + column].character = character;
            text_frame->cells[row * MYSMB_TEXT_COLUMNS + column].color = color;
        }
    }
}

void mysmb_text_frame_build(const struct mysmb_render_frame *render_frame,
                            struct mysmb_text_frame *text_frame)
{
    mysmb_u16 index;

    mysmb_text_fill_background(render_frame, text_frame);
    for (index = 0U; index < render_frame->command_count; ++index) {
        if (render_frame->commands[index].kind == MYSMB_RENDER_COMMAND_ACTOR) {
            mysmb_text_draw_actor(&render_frame->commands[index], text_frame);
        }
    }
}
