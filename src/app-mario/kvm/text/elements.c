#include "io/video.h"
#include "text/elements.h"
#include "kvm/glyph.h"
#include "kvm/color.h"
#include "text/layout.h"
#include <string.h>

/* Project-authored whole-element art. Spaces are transparent. No CHR bytes,
 * tile lookup, pixel sampling or animation state machine is used here. */
struct mysmb_text_art {
    const char *cells;
    mygames_kvm_u8 width;
    mygames_kvm_u8 height;
};

static const struct mysmb_text_art small[17] = {
    { " \xdc" "M" "\xdc " " /o> " "/|_|\\", 5U, 3U },
    { " \xdc" "M" "\xdc " " /o> " " /|_>", 5U, 3U },
    { " \xdc" "M" "\xdc " "</o> " " /|\\ ", 5U, 3U },
    { " \xdc" "M" "\xdc " " /o> " "<_|/ ", 5U, 3U },
    { " \xdc" "M" "\xdc " "</o>~" " ~|~ ", 5U, 3U },
    { " \xdc" "M\xb3 " " /o| " " /|| ", 5U, 3U },
    { " \xdc" "M" "\xdc " "(/o>)" " /_\\ ", 5U, 3U },
    { " \xdc" "M" "\xdc " " /o>>" " /|\\ ", 5U, 3U },
    { " \xdc" "M" "\xdc " "<x_x>" " /\\  ", 5U, 3U },
    { " \xdc" "M" "\xdc " " /o> " "<_|/ ", 5U, 3U },
    { " \xdc" "M" "\xdc " " /o> " " /|\\ ", 5U, 3U },
    { " \xdc" "M" "\xdc " " /o>~" "~ |~ ", 5U, 3U },
    { " \xdc" "M" "\xdc " "</o> " " ~|~~", 5U, 3U },
    { " \xdc" "M\xb3 " "</o| " " ||/ ", 5U, 3U },
    { " \xdc" "M" "\xdc " "</o>~" "~ /|~", 5U, 3U },
    { " \xdc" "M" "\xdc " " /o>~" "~/ |~", 5U, 3U },
    { " \xdc" "M" "\xdc " "</o> " "~ |/~", 5U, 3U }
};
static const struct mysmb_text_art large[17] = {
    { " \xdc" "M" "\xdc " " /o> " " |_| " " /|\\ " " |#| " " / \\ " "/_ _\\", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " " |_| " " /|_>" " |#| " " /\\  " "/  \\_", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " "<|_|>" " |#| " " /|\\ " " / \\ " "     ", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " " |_| " "<_|\\ " " |#| " "  /| " "<_ / ", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " "<|_|~" " |#| " " ~|~ " " ~ ~ " "     ", 5U, 7U },
    { " \xdc" "M\xb3 " " /o| " " |_| " " /|| " " |#| " " /|| " " ||/ ", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " "(_#_)" " /_\\ ", 5U, 4U },
    { " \xdc" "M" "\xdc " " /o>>" " |_| " " |#| " " /|\\ " " / \\ " "/_ _\\", 5U, 7U },
    { " \xdc" "M" "\xdc " " x_x " "<|_|>" " |#| " " /|\\ " " /\\  " "     ", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " " |_| " "<_|\\ " " |#| " "  /| " "<_ / ", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " " |_| " " /|\\ " " |#| " " /|  " "/ \\_ ", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " " |_|~" " |#| " "~ |~ " " ~ ~ " "     ", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " "<|_| " " |#| " " ~|~~" "~ ~  " "     ", 5U, 7U },
    { " \xdc" "M\xb3 " " /o| " "<|_| " " ||/ " " |#| " " ||/ " " /|| ", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " "<|_|~" " |#| " " ~|~ " "~/|  " "~ / ~", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " " |_|~" " |#| " "~ |~ " " /|~ " "~ / ~", 5U, 7U },
    { " \xdc" "M" "\xdc " " /o> " "<|_| " " |#| " " ~|~~" "~ |/~" " ~ /~", 5U, 7U }
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
    {{" \xdc\xdb\xdb\xdc" "(oo_)" " /  \\" ,5U,3U},{" \xdc\xdb\xdb\xdc" "(oo_)" "  /\\ ",5U,3U}},
    {{" \xdc\xdb\xdb\xdc" "(o_o)" " ||| " " /|\\ ",5U,4U},{" \xdc\xdb\xdb\xdc" "(o_o)" " /|\\ " " ||| ",5U,4U}},
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
    {{" _T_ " "(o_o)" " /|\\ " " |_| " " / \\ ",5U,5U},
     {" ^P^ " " {o>}" " /|\\ " " /#\\ " "/___\\",5U,5U}},
    {{"[===]" " /\\  " "[===]",5U,3U},{"[===]" "[===]",5U,2U}},
    {{"\xda\xc4\xc4\xc4\xbf" "\xb3   \xb3" "\xc0\xc4\xc4\xc4\xd9",5U,3U},{"\xda\xc4\xc4\xc4\xbf" "\xb3   \xb3" "\xc0\xc4\xc4\xc4\xd9",5U,3U}}
};
static const struct mysmb_text_art goomba_second={" \xdc\xdb\xdb\xdc" "(o_o)" " /|\\ ",5U,3U};
static const struct mysmb_text_art winged[2]={
    {"\\ __/" " /o> " "(###)" " / \\ " "/_ _\\",5U,5U},
    {" /__\\" " /o> " "(###)" " /|  " "/ \\_ ",5U,5U}
};
static const struct mysmb_text_art fire_phases[2]={
    {"@",1U,1U},{"*",1U,1U}
};
static const struct mysmb_text_art explosions[3]={
    {"   " " * " "   ",3U,3U},
    {"\\ /" " * " "/ \\",3U,3U},
    {"\\|/" "-*-" "/|\\",3U,3U}
};
static const struct mysmb_text_art springs[3]={
    {"[===]" " /\\  " "[===]",5U,3U},
    {"[===]" "[===]",5U,2U},{"[===]",5U,1U}
};
static const struct mysmb_text_art hammer_throw[2]={
    {" _H_ " " /o> " "[##]>" " /|\\ " " / \\ ",5U,5U},
    {"^_H_ " " /o>>" "[##] " " /|  " "/_ \\ ",5U,5U}
};
static const struct mysmb_text_art egg_second={"/^^\\" "(OO)" "\\__/",4U,3U};
static const struct mysmb_text_art hammers[4]={
    {"[]" " |",2U,2U},{" |" "==",2U,2U},
    {"| " "[]",2U,2U},{"==" "| ",2U,2U}
};
static const struct mysmb_text_art scenery[15] = {
    { " \xdc\xdb\xdb\xdc" "(o_o)" "/   \\", 5U, 3U },
    { " \xdc\xdb\xdb\xdc" "(o_o)" "  |  ", 5U, 3U },
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
    const struct mysmb_text_element MYGAMES_KVM_FAR *element)
{
    if(element->kind==MYSMB_TEXT_WINGED_KOOPA)return &winged[element->pose==1U?1U:0U];
    if(element->kind==MYSMB_TEXT_FIREBALL)return &fire_phases[element->pose];
    if(element->kind==MYSMB_TEXT_EXPLOSION)return &explosions[element->pose];
    if(element->kind==MYSMB_TEXT_SPRING)return &springs[element->pose];
    if(element->kind==MYSMB_TEXT_HAMMER_BRO && element->pose>=3U)
        return &hammer_throw[element->pose-3U];
    if(element->kind==MYSMB_TEXT_EGG && element->pose==1U)return &egg_second;
    if(element->kind==MYSMB_TEXT_HAMMER)return &hammers[element->pose];
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

static mygames_kvm_u8 mirror(mygames_kvm_u8 c)
{
    return mygames_kvm_text_glyph_mirror(c);
}

static int valid_element(const struct mysmb_text_element MYGAMES_KVM_FAR *e)
{
    return e != 0 && e->kind < MYSMB_TEXT_KIND_COUNT &&
        e->face_left <= 1U && e->foreground <= 15U && e->background <= 15U &&
        (e->kind==MYSMB_TEXT_LUIGI_SMALL || e->kind==MYSMB_TEXT_LUIGI_LARGE ?
            e->pose<MYSMB_TEXT_PLAYER_POSES:
         e->kind==MYSMB_TEXT_WINGED_KOOPA ? e->pose<=2U:
         e->kind==MYSMB_TEXT_FIREBALL ? e->pose<2U:
         e->kind==MYSMB_TEXT_EXPLOSION ? e->pose<3U:
         e->kind==MYSMB_TEXT_SPRING ? e->pose<3U:
         e->kind==MYSMB_TEXT_HAMMER_BRO ? e->pose<5U:
         e->kind==MYSMB_TEXT_HAMMER ? e->pose<4U:
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
    const struct mysmb_text_element MYGAMES_KVM_FAR *element,
    struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame,
    mysmb_text_cell_filter filter, const void MYGAMES_KVM_FAR *context)
{
    mygames_kvm_u16 cell;
    mygames_kvm_u16 source;
    mygames_kvm_u8 row;
    mygames_kvm_u8 column;
    mygames_kvm_u8 glyph;
    mygames_kvm_u8 face_left;
    mygames_kvm_u8 row_left,row_right;
    mygames_kvm_u16 source_row;
    long x;
    long y;
    long destination_x;
    long destination_y;
    const struct mysmb_text_art *art;
    if (frame == 0 || !valid_element(element)) return 0;
        /* A facing descriptor never reverses information-bearing words. */
        face_left=element->kind==MYSMB_TEXT_SCORE || element->kind==MYSMB_TEXT_FLAG_SCORE?
            0U:element->face_left;
        art = art_for(element);
        x = project(element->x, 80L, 256L);
        y = project(element->y, 50L, 240L);
        for (row = 0U; row < art->height; ++row) {
            source_row=(mygames_kvm_u16)(((element->kind==MYSMB_TEXT_WINGED_KOOPA ||
                (element->kind>=MYSMB_TEXT_GOOMBA && element->kind<MYSMB_TEXT_JUMP_COIN &&
                 element->kind!=MYSMB_TEXT_EXPLOSION && element->kind!=MYSMB_TEXT_SPRING &&
                 element->kind!=MYSMB_TEXT_HAMMER)) &&
                element->pose==MYSMB_TEXT_INVERTED?art->height-1U-row:row)*art->width);
            row_left=0U;row_right=art->width;
            while(row_left<art->width && art->cells[source_row+row_left]==' ')row_left++;
            while(row_right>row_left && art->cells[source_row+row_right-1U]==' ')row_right--;
            destination_y = y + row;
            if (destination_y < 0L || destination_y >= 50L) continue;
            for (column = 0U; column < art->width; ++column) {
                destination_x = x + column;
                if (destination_x < 0L || destination_x >= 80L) continue;
                source = (mygames_kvm_u16)(source_row +
                    (face_left != 0U ? art->width - 1U - column : column));
                glyph = (mygames_kvm_u8)art->cells[source];
                if(glyph=='M' && (element->kind==MYSMB_TEXT_LUIGI_SMALL ||
                    element->kind==MYSMB_TEXT_LUIGI_LARGE))glyph='L';
                if (source-source_row<row_left || source-source_row>=row_right)continue;
                if (filter != 0 && !filter(context,
                    (mygames_kvm_u16)destination_x,
                    (mygames_kvm_u16)destination_y)) continue;
                if (face_left != 0U) glyph = mirror(glyph);
                if((element->kind==MYSMB_TEXT_WINGED_KOOPA ||
                    (element->kind>=MYSMB_TEXT_GOOMBA && element->kind<MYSMB_TEXT_JUMP_COIN &&
                     element->kind!=MYSMB_TEXT_EXPLOSION && element->kind!=MYSMB_TEXT_SPRING &&
                     element->kind!=MYSMB_TEXT_HAMMER)) && element->pose==MYSMB_TEXT_INVERTED) {
                    glyph=mygames_kvm_text_glyph_flip(glyph);
                }
                cell = (mygames_kvm_u16)(destination_y * 80L + destination_x);
                /* Half/full blocks carry authored silhouette color over the
                 * existing scene. Information overlays keep that background. */
                if(element->kind==MYSMB_TEXT_SCORE || element->kind==MYSMB_TEXT_FLAG_SCORE) {
                    frame->cells[cell].character=glyph;
                    frame->cells[cell].foreground=element->background!=frame->cells[cell].background?
                        element->background:mygames_kvm_color_text_contrast(frame->cells[cell].background);
                    continue;
                }
                if(glyph==MYGAMES_KVM_GLYPH_LOWER || glyph==MYGAMES_KVM_GLYPH_UPPER ||
                    glyph==MYGAMES_KVM_GLYPH_LEFT || glyph==MYGAMES_KVM_GLYPH_RIGHT ||
                    glyph==MYGAMES_KVM_GLYPH_FULL) {
                    frame->cells[cell].character=glyph;
                    frame->cells[cell].foreground=element->background!=frame->cells[cell].background?
                        element->background:element->foreground;
                    continue;
                }
                frame->cells[cell].character = glyph;
                frame->cells[cell].foreground = element->foreground;
                frame->cells[cell].background = element->background;
            }
        }
    return 1;
}

int mysmb_text_elements_build(
    const struct mysmb_text_element MYGAMES_KVM_FAR *elements,
    mygames_kvm_u16 count, mygames_kvm_u8 sky,
    struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame)
{
    mygames_kvm_u16 i;
    if (frame == 0 || sky > 15U || count > MYSMB_TEXT_ELEMENT_CAPACITY ||
        (count != 0U && elements == 0)) return 0;
    for (i=0U;i<count;++i) if (!valid_element(&elements[i])) return 0;
    mysmb_text_frame_initialize(frame,sky,50U,0);
    for (i=0U;i<count;++i)
        (void)mysmb_text_element_draw(&elements[i],frame,0,0);
    return 1;
}
