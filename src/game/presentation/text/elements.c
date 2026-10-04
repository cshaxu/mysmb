#include "game/presentation/text/elements.h"
#include "io/text_glyph.h"

/* Project-authored whole-element art. Spaces are transparent. No CHR bytes,
 * tile lookup, pixel sampling or animation state machine is used here. */
struct mysmb_text_art {
    const char *cells;
    mysmb_io_u8 width;
    mysmb_io_u8 height;
};

static const struct mysmb_text_art small[17] = {
    { " _M_ " " /o> " "/|_|\\", 5U, 3U },
    { " _M_ " " /o> " " /|_>", 5U, 3U },
    { " _M_ " "</o> " " /|\\ ", 5U, 3U },
    { " _M_ " " /o> " "<_|/ ", 5U, 3U },
    { " _M_ " "</o>~" " ~|~ ", 5U, 3U },
    { " _M| " " /o| " " /|| ", 5U, 3U },
    { " _M_ " "(/o>)" " /_\\ ", 5U, 3U },
    { " _M_ " " /o>>" " /|\\ ", 5U, 3U },
    { " _M_ " "<x_x>" " /\\  ", 5U, 3U },
    { " _M_ " " /o> " "<_|/ ", 5U, 3U },
    { " _M_ " " /o> " " /|\\ ", 5U, 3U },
    { " _M_ " " /o>~" "~ |~ ", 5U, 3U },
    { " _M_ " "</o> " " ~|~~", 5U, 3U },
    { " _M| " "</o| " " ||/ ", 5U, 3U },
    { " _M_ " "</o>~" "~ /|~", 5U, 3U },
    { " _M_ " " /o>~" "~/ |~", 5U, 3U },
    { " _M_ " "</o> " "~ |/~", 5U, 3U }
};
static const struct mysmb_text_art large[17] = {
    { " _M_ " " /o> " " |_| " " /|\\ " " |#| " " / \\ " "/_ _\\", 5U, 7U },
    { " _M_ " " /o> " " |_| " " /|_>" " |#| " " /\\  " "/  \\_", 5U, 7U },
    { " _M_ " " /o> " "<|_|>" " |#| " " /|\\ " " / \\ " "     ", 5U, 7U },
    { " _M_ " " /o> " " |_| " "<_|\\ " " |#| " "  /| " "<_ / ", 5U, 7U },
    { " _M_ " " /o> " "<|_|~" " |#| " " ~|~ " " ~ ~ " "     ", 5U, 7U },
    { " _M| " " /o| " " |_| " " /|| " " |#| " " /|| " " ||/ ", 5U, 7U },
    { " _M_ " " /o> " "(_#_)" " /_\\ ", 5U, 4U },
    { " _M_ " " /o>>" " |_| " " |#| " " /|\\ " " / \\ " "/_ _\\", 5U, 7U },
    { " _M_ " " x_x " "<|_|>" " |#| " " /|\\ " " /\\  " "     ", 5U, 7U },
    { " _M_ " " /o> " " |_| " "<_|\\ " " |#| " "  /| " "<_ / ", 5U, 7U },
    { " _M_ " " /o> " " |_| " " /|\\ " " |#| " " /|  " "/ \\_ ", 5U, 7U },
    { " _M_ " " /o> " " |_|~" " |#| " "~ |~ " " ~ ~ " "     ", 5U, 7U },
    { " _M_ " " /o> " "<|_| " " |#| " " ~|~~" "~ ~  " "     ", 5U, 7U },
    { " _M| " " /o| " "<|_| " " ||/ " " |#| " " ||/ " " /|| ", 5U, 7U },
    { " _M_ " " /o> " "<|_|~" " |#| " " ~|~ " "~/|  " "~ / ~", 5U, 7U },
    { " _M_ " " /o> " " |_|~" " |#| " "~ |~ " " /|~ " "~ / ~", 5U, 7U },
    { " _M_ " " /o> " "<|_| " " |#| " " ~|~~" "~ |/~" " ~ /~", 5U, 7U }
};
static const struct mysmb_text_art parts[3] = {
    { "|}" "| ", 2U, 2U }, { "^|" " |", 2U, 2U },
    { "[=]", 3U, 1U }
};
static const struct mysmb_text_art flag_scores[5] = {
    {"5000",4U,1U},{"2000",4U,1U},{"800",3U,1U},
    {"400",3U,1U},{"100",3U,1U}
};
static const struct mysmb_text_art jump_coins[4] = {
    {"()" "$$" "()",2U,3U},{" |" " |" " |",2U,3U},
    {"()" "||" "()",2U,3U},{"| " "| " "| ",2U,3U}
};
static const struct mysmb_text_art scores[11] = {
    {"100",3U,1U},{"200",3U,1U},{"400",3U,1U},
    {"500",3U,1U},{"800",3U,1U},{"1000",4U,1U},
    {"2000",4U,1U},{"4000",4U,1U},{"5000",4U,1U},
    {"8000",4U,1U},{"1UP",3U,1U}
};
static const struct mysmb_text_art star_flag={"|***>" "| **>" "|___>",5U,3U};

static const struct mysmb_text_art actors[19][2] = {
    {{"/___\\",5U,1U},{"/___\\",5U,1U}},
    {{" /--\\" "(___)" " /  \\" ,5U,3U},{" /--\\" "(___)" "  /\\ ",5U,3U}},
    {{"  __ " " /o> " "(###)" " / \\ " "/_ _\\",5U,5U},
     {"  __ " " /o> " "(###)" " /|  " "/ \\_ ",5U,5U}},
    {{" /--\\" "(oo_)" " /  \\" ,5U,3U},{" /--\\" "(oo_)" "  /\\ ",5U,3U}},
    {{" /^^\\" "(o_o)" " ||| " " /|\\ ",5U,4U},{" /^^\\" "(o_o)" " /|\\ " " ||| ",5U,4U}},
    {{" ___ " "<o==]" " --- ",5U,3U},{" ___ " "<o==]" " --- ",5U,3U}},
    {{" /\\  " "<o )>" " \\/  ",5U,3U},{" /\\  " "<o)> " " \\/  ",5U,3U}},
    {{" /\\ " "(oo)" " \\/ ",4U,3U},{" /\\ " "(oo)" " \\/ ",4U,3U}},
    {{"\\/\\/ " "(o_o)" " \\|/ " "  |  " "  |  ",5U,5U},
     {" /^^\\" "<o_o>" " \\|/ " "  |  " "  |  ",5U,5U}},
    {{" _H_ " " /o> " "[##] " " /|\\ " " / \\ ",5U,5U},
     {" _H_ " " /o>>" "[##] " " /|  " "/_ \\ ",5U,5U}},
    {{"/^^^^" "(o##)" " /  \\" ,5U,3U},{"/^^^^" "(o##)" "  /\\ ",5U,3U}},
    {{"/^^\\" "(oo)" "\\__/",4U,3U},{"/^^\\" "(oo)" "\\__/",4U,3U}},
    {{" _L_ " "(o_o)" "(~~~)" " \\_/ ",5U,4U},
     {" _L_ " "(o_o)" "(~~~)" " /_/ ",5U,4U}},
    {{" /^^\\" "<o_/>" " |##|" " /|| " " / \\ ",5U,5U},
     {" /^^\\" "<o__>" " |##|" " /|| " " / \\ ",5U,5U}},
    {{"/^^^^" "|###>" "|### " " ||\\ " " / \\ ",5U,5U},
     {"/^^^^" "|###>" "|### " " /|| " " / \\ ",5U,5U}},
    {{"<<~~~*>",7U,1U},{"<*~~~>>",7U,1U}},
    {{" _T_ " "(o_o)" " /|\\ " " / \\ ",5U,4U},
     {" _P_ " "(o_o)" " /|\\ " " /_\\ ",5U,4U}},
    {{"[===]" " /\\  " "[===]",5U,3U},{"[===]" "[===]",5U,2U}},
    {{"\xda\xc4\xc4\xc4\xbf" "\xb3   \xb3" "\xc0\xc4\xc4\xc4\xd9",5U,3U},{"\xda\xc4\xc4\xc4\xbf" "\xb3   \xb3" "\xc0\xc4\xc4\xc4\xd9",5U,3U}}
};
static const struct mysmb_text_art goomba_second={" /^^\\" "(o_o)" " /|\\ ",5U,3U};
static const struct mysmb_text_art scenery[15] = {
    { " /^^\\" "(o_o)" "/   \\", 5U, 3U },
    { " /^^\\" "(o_o)" "  |  ", 5U, 3U },
    { "\xda\xc4\xc4\xc4\xbf" "\xb3_#_\xb3" "\xc0\xc4\xc4\xc4\xd9", 5U, 3U },
    { " ($) " " ($) " "     ", 5U, 3U },
    { "\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf" "\xb3########\xb3" "\xc0\xc4\xc2" "####" "\xc2\xc4\xd9" "  \xb3####\xb3  "
      "  \xb3####\xb3  " "  \xb3####\xb3  " "  \xb3####\xb3  ", 10U, 7U },
    { " (o) " " \\|/ " "  |  ", 5U, 3U },
    { " /\\ " "<**>" " \\/ ", 4U, 3U },
    { "@", 1U, 1U },
    { "\\|/" "-*-" "/|\\", 3U, 3U },
    { "[]" " |", 2U, 2U },
    { "#", 1U, 1U },
    { "|" "}" "|" "{" "|" "}", 1U, 6U },
    { "[======]", 8U, 1U },
    { "|===>" "|  / " "|_/  ", 5U, 3U },
    { "o", 1U, 1U }
};

static const struct mysmb_text_art *art_for(
    const struct mysmb_text_element MYSMB_IO_FAR *element)
{
    if (element->kind == MYSMB_TEXT_PLAYER_SMALL ||
        element->kind == MYSMB_TEXT_LUIGI_SMALL) return &small[element->pose];
    if (element->kind == MYSMB_TEXT_PLAYER_LARGE ||
        element->kind == MYSMB_TEXT_LUIGI_LARGE) return &large[element->pose];
    if (element->kind == MYSMB_TEXT_STAR_FLAG)return &star_flag;
    if (element->kind == MYSMB_TEXT_FLAG_SCORE) return &flag_scores[element->pose];
    if (element->kind == MYSMB_TEXT_JUMP_COIN) return &jump_coins[element->pose];
    if (element->kind == MYSMB_TEXT_SCORE) return &scores[element->pose];
    if (element->kind >= MYSMB_TEXT_VINE_LEAF)
        return &parts[element->kind-MYSMB_TEXT_VINE_LEAF];
    if (element->kind >= MYSMB_TEXT_GOOMBA_FLAT)
        return &actors[element->kind-MYSMB_TEXT_GOOMBA_FLAT][element->pose==1U?1U:0U];
    if (element->kind==MYSMB_TEXT_GOOMBA && element->pose==1U)return &goomba_second;
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
    return mysmb_io_text_glyph_mirror(c);
}

static int valid_element(const struct mysmb_text_element MYSMB_IO_FAR *e)
{
    return e != 0 && e->kind < MYSMB_TEXT_KIND_COUNT &&
        e->face_left <= 1U && e->foreground <= 15U && e->background <= 15U &&
        (e->kind==MYSMB_TEXT_LUIGI_SMALL || e->kind==MYSMB_TEXT_LUIGI_LARGE ?
            e->pose<MYSMB_TEXT_PLAYER_POSES:
         e->kind==MYSMB_TEXT_STAR_FLAG ? e->pose==0U:
         e->kind==MYSMB_TEXT_SCORE ? e->pose<11U:
         e->kind==MYSMB_TEXT_JUMP_COIN ? e->pose<4U:
         e->kind==MYSMB_TEXT_FLAG_SCORE ? e->pose<5U:
         e->kind>=MYSMB_TEXT_VINE_LEAF ? e->pose==0U:
         e->kind < MYSMB_TEXT_GOOMBA ? e->pose<MYSMB_TEXT_PLAYER_POSES :
         e->kind==MYSMB_TEXT_GOOMBA || e->kind>=MYSMB_TEXT_GOOMBA_FLAT ?
            e->pose<=2U:e->pose==0U);
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
    mysmb_io_u8 row_left,row_right;
    mysmb_io_u16 source_row;
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
            source_row=(mysmb_io_u16)((element->kind>=MYSMB_TEXT_GOOMBA &&
                element->kind<MYSMB_TEXT_JUMP_COIN &&
                element->pose==MYSMB_TEXT_INVERTED?art->height-1U-row:row)*art->width);
            row_left=0U;row_right=art->width;
            while(row_left<art->width && art->cells[source_row+row_left]==' ')row_left++;
            while(row_right>row_left && art->cells[source_row+row_right-1U]==' ')row_right--;
            destination_y = y + row;
            if (destination_y < 0L || destination_y >= 50L) continue;
            for (column = 0U; column < art->width; ++column) {
                destination_x = x + column;
                if (destination_x < 0L || destination_x >= 80L) continue;
                source = (mysmb_io_u16)(source_row +
                    (element->face_left != 0U ? art->width - 1U - column : column));
                glyph = (mysmb_io_u8)art->cells[source];
                if(glyph=='M' && (element->kind==MYSMB_TEXT_LUIGI_SMALL ||
                    element->kind==MYSMB_TEXT_LUIGI_LARGE))glyph='L';
                if (source-source_row<row_left || source-source_row>=row_right)continue;
                if (filter != 0 && !filter(context,
                    (mysmb_io_u16)destination_x,
                    (mysmb_io_u16)destination_y)) continue;
                if (element->face_left != 0U) glyph = mirror(glyph);
                if(element->kind>=MYSMB_TEXT_GOOMBA &&
                    element->kind<MYSMB_TEXT_JUMP_COIN && element->pose==MYSMB_TEXT_INVERTED) {
                    if(glyph=='^')glyph='v';
                    else if(glyph=='/')glyph='\\';
                    else if(glyph=='\\')glyph='/';
                }
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
