#include "game/presentation/text/elements.h"

/* Project-authored whole-element art. Spaces are transparent. No CHR bytes,
 * tile lookup, pixel sampling or animation state machine is used here. */
struct mysmb_text_art {
    const char *cells;
    mysmb_io_u8 width;
    mysmb_io_u8 height;
};

static const struct mysmb_text_art small[3] = {
    { " _M_ " " /o> " "/|_|\\", 5U, 3U },
    { " _M_ " " /o> " " /|_>", 5U, 3U },
    { " _M_ " "</o> " " /|\\ ", 5U, 3U }
};
static const struct mysmb_text_art large[3] = {
    { " _M_ " " /o> " " |_| " " /|\\ " " |#| " " / \\ " "/_ _\\", 5U, 7U },
    { " _M_ " " /o> " " |_| " " /|_>" " |#| " " /\\  " "/  \\_", 5U, 7U },
    { " _M_ " " /o> " "<|_|>" " |#| " " /|\\ " " / \\ " "     ", 5U, 7U }
};
static const struct mysmb_text_art scenery[15] = {
    { " /^^\\" "(o_o)" "/   \\", 5U, 3U },
    { " /^^\\" "(o_o)" "  |  ", 5U, 3U },
    { "+---+" "|_#_|" "+---+", 5U, 3U },
    { " ($) " " ($) " "     ", 5U, 3U },
    { "+========+" "|########|" "+-+####+-+" "  |####|  "
      "  |####|  " "  |####|  " "  |####|  ", 10U, 7U },
    { " (o) " " \\|/ " "  |  ", 5U, 3U },
    { " /\\ " "<**>" " \\/ ", 4U, 3U },
    { "@", 1U, 1U },
    { "\\|/" "-*-" "/|\\", 3U, 3U },
    { "[]" " |", 2U, 2U },
    { "#", 1U, 1U },
    { "|" "}" "|" "{" "|" "}", 1U, 6U },
    { "[======]", 8U, 1U },
    { "|>" "| ", 2U, 2U },
    { "o", 1U, 1U }
};

static const struct mysmb_text_art *art_for(
    const struct mysmb_text_element MYSMB_IO_FAR *element)
{
    if (element->kind == MYSMB_TEXT_PLAYER_SMALL) return &small[element->pose];
    if (element->kind == MYSMB_TEXT_PLAYER_LARGE) return &large[element->pose];
    return &scenery[element->kind - MYSMB_TEXT_GOOMBA];
}

/* Floor projection, including negative positions. Multiplication uses long
 * so the full signed-short input domain also works with 16-bit int. */
static long project(short value, long scale, long extent)
{
    long product;
    product = (long)value * scale;
    if (product < 0L) return -((-product + extent - 1L) / extent);
    return product / extent;
}

static mysmb_io_u8 mirror(mysmb_io_u8 c)
{
    switch (c) {
    case '/': return '\\'; case '\\': return '/';
    case '<': return '>'; case '>': return '<';
    case '(': return ')'; case ')': return '(';
    default: return c;
    }
}

static int valid_element(const struct mysmb_text_element MYSMB_IO_FAR *e)
{
    return e != 0 && e->kind < MYSMB_TEXT_KIND_COUNT && e->pose <= 2U &&
        e->face_left <= 1U && e->foreground <= 15U && e->background <= 15U &&
        (e->kind < MYSMB_TEXT_GOOMBA || e->pose == 0U);
}

int mysmb_text_element_draw(
    const struct mysmb_text_element MYSMB_IO_FAR *element,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    mysmb_text_cell_filter filter, const void MYSMB_IO_FAR *context)
{
    mysmb_io_u16 cell;
    mysmb_io_u16 source;
    mysmb_io_u8 row;
    mysmb_io_u8 column;
    mysmb_io_u8 glyph;
    long x;
    long y;
    long destination_x;
    long destination_y;
    const struct mysmb_text_art *art;
    if (frame == 0 || !valid_element(element)) return 0;
        art = art_for(element);
        x = project(element->x, 80L, 256L);
        y = project(element->y, 50L, 240L);
        for (row = 0U; row < art->height; ++row) {
            destination_y = y + row;
            if (destination_y < 0L || destination_y >= 50L) continue;
            for (column = 0U; column < art->width; ++column) {
                destination_x = x + column;
                if (destination_x < 0L || destination_x >= 80L) continue;
                source = (mysmb_io_u16)(row * art->width +
                    (element->face_left != 0U ? art->width - 1U - column : column));
                glyph = (mysmb_io_u8)art->cells[source];
                if (glyph == ' ') continue;
                if (filter != 0 && !filter(context,
                    (mysmb_io_u16)destination_x,
                    (mysmb_io_u16)destination_y)) continue;
                if (element->face_left != 0U) glyph = mirror(glyph);
                cell = (mysmb_io_u16)(destination_y * 80L + destination_x);
                frame->cells[cell].character = glyph;
                frame->cells[cell].foreground = element->foreground;
                frame->cells[cell].background = element->background;
            }
        }
    return 1;
}

int mysmb_text_elements_build(
    const struct mysmb_text_element MYSMB_IO_FAR *elements,
    mysmb_io_u16 count, mysmb_io_u8 sky,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{
    mysmb_io_u16 i;
    if (frame == 0 || sky > 15U || count > MYSMB_TEXT_ELEMENT_CAPACITY ||
        (count != 0U && elements == 0)) return 0;
    for (i=0U;i<count;++i) if (!valid_element(&elements[i])) return 0;
    for (i=0U;i<MYSMB_IO_TEXT_CELLS;++i) {
        frame->cells[i].character=' ';
        frame->cells[i].foreground=sky;
        frame->cells[i].background=sky;
    }
    for (i=0U;i<count;++i)
        (void)mysmb_text_element_draw(&elements[i],frame,0,0);
    return 1;
}
