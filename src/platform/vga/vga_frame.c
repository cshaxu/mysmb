#include "platform/vga/vga_frame.h"

static mysmb_u8 mysmb_vga_tile_color(mysmb_u8 tile)
{
    if (tile >= 0x80U) return MYSMB_VGA_COLOR_GROUND;
    if (tile >= 0x50U) return MYSMB_VGA_COLOR_BLOCK;
    if (tile >= 0x30U) return MYSMB_VGA_COLOR_BLOCK;
    return MYSMB_VGA_COLOR_SKY;
}

static mysmb_u8 mysmb_vga_actor_color(mysmb_u8 identity)
{
    return identity == 0U ? MYSMB_VGA_COLOR_PLAYER : MYSMB_VGA_COLOR_ENEMY;
}

static void mysmb_vga_set_pixel(struct mysmb_vga_frame *vga_frame,
                                mysmb_u16 offset, mysmb_u8 color)
{
    vga_frame->pages[offset / MYSMB_VGA_PAGE_SIZE][offset % MYSMB_VGA_PAGE_SIZE] = color;
}

static void mysmb_vga_fill_background(const struct mysmb_render_frame *render_frame,
                                      struct mysmb_vga_frame *vga_frame)
{
    mysmb_u16 row;
    mysmb_u16 column;
    mysmb_u16 source_row;
    mysmb_u16 source_column;
    mysmb_u8 color;

    for (row = 0U; row < MYSMB_VGA_HEIGHT; ++row) {
        source_row = (mysmb_u16)(row * MYSMB_RENDER_TILE_ROWS / MYSMB_VGA_HEIGHT);
        for (column = 0U; column < MYSMB_VGA_WIDTH; ++column) {
            source_column = (mysmb_u16)(column * MYSMB_RENDER_TILE_COLUMNS /
                                        MYSMB_VGA_WIDTH);
            color = mysmb_vga_tile_color(render_frame->tile_data[
                source_row * MYSMB_RENDER_TILE_COLUMNS + source_column]);
            mysmb_vga_set_pixel(vga_frame, row * MYSMB_VGA_WIDTH + column, color);
        }
    }
}

static void mysmb_vga_draw_actor(const struct mysmb_render_command *command,
                                 struct mysmb_vga_frame *vga_frame)
{
    mysmb_u16 left;
    mysmb_u16 top;
    mysmb_u16 right;
    mysmb_u16 bottom;
    mysmb_u16 row;
    mysmb_u16 column;
    mysmb_u8 color;

    left = (mysmb_u16)command->x * 5U / 4U;
    top = (mysmb_u16)command->y * 5U / 6U;
    right = ((mysmb_u16)command->x + command->length) * 5U / 4U;
    bottom = ((mysmb_u16)command->y + command->length) * 5U / 6U;
    if (right <= left) right = (mysmb_u16)(left + 1U);
    if (bottom <= top) bottom = (mysmb_u16)(top + 1U);
    if (right > MYSMB_VGA_WIDTH) right = MYSMB_VGA_WIDTH;
    if (bottom > MYSMB_VGA_HEIGHT) bottom = MYSMB_VGA_HEIGHT;
    color = mysmb_vga_actor_color(command->identity);
    for (row = top; row < bottom; ++row) {
        for (column = left; column < right; ++column) {
            mysmb_vga_set_pixel(vga_frame, row * MYSMB_VGA_WIDTH + column, color);
        }
    }
}

void mysmb_vga_frame_initialize(struct mysmb_vga_frame *vga_frame,
                                mysmb_u8 MYSMB_VGA_FAR *page0,
                                mysmb_u8 MYSMB_VGA_FAR *page1,
                                mysmb_u8 MYSMB_VGA_FAR *page2,
                                mysmb_u8 MYSMB_VGA_FAR *page3)
{
    vga_frame->pages[0] = page0;
    vga_frame->pages[1] = page1;
    vga_frame->pages[2] = page2;
    vga_frame->pages[3] = page3;
}

void mysmb_vga_frame_build(const struct mysmb_render_frame *render_frame,
                           struct mysmb_vga_frame *vga_frame)
{
    mysmb_u16 index;

    mysmb_vga_fill_background(render_frame, vga_frame);
    for (index = 0U; index < render_frame->command_count; ++index) {
        if (render_frame->commands[index].kind == MYSMB_RENDER_COMMAND_ACTOR) {
            mysmb_vga_draw_actor(&render_frame->commands[index], vga_frame);
        }
    }
}
