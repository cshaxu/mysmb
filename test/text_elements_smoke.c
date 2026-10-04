#include "io/text_glyph.h"
#include "game/presentation/text/elements.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

static struct mysmb_io_text_frame frame;
static struct mysmb_io_text_frame before;
static struct mysmb_io_text_frame monochrome;
static struct mysmb_text_element elements[8];

#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "check failed at line %d\n", __LINE__); return 1; \
} } while (0)

int main(int argc, char **argv)
{
    struct mysmb_text_element original;
    unsigned int i;
    unsigned int row;
    unsigned int column;
    unsigned int facing;
    unsigned int ink;
    unsigned int cases = 0U;
    unsigned int line;
    unsigned int first;
    unsigned int last;
    struct mysmb_text_element plain;
    FILE *preview;

    /* Exhaustive byte domain and horizontal reflection contract. */
    for(i=0U;i<256U;++i) {
        column=mysmb_io_text_glyph_unicode((mysmb_io_u8)i);
        if(i>=32U && i<=126U)CHECK(column==i);
        else if(column!=0U)CHECK(column>=0x2500U && column<=0x2590U);
        CHECK(mysmb_io_text_glyph_mirror(mysmb_io_text_glyph_mirror((mysmb_io_u8)i))==i);
    }
    CHECK(mysmb_io_text_glyph_unicode(0U)==0U);
    CHECK(mysmb_io_text_glyph_unicode(0x80U)==0U);
    CHECK(mysmb_io_text_glyph_unicode(MYSMB_IO_GLYPH_TOP_LEFT)==0x250cU);
    CHECK(mysmb_io_text_glyph_unicode(MYSMB_IO_GLYPH_UPPER)==0x2580U);
    CHECK(mysmb_io_text_glyph_unicode(MYSMB_IO_GLYPH_LOWER)==0x2584U);
    CHECK(mysmb_io_text_glyph_mirror(MYSMB_IO_GLYPH_TOP_LEFT)==MYSMB_IO_GLYPH_TOP_RIGHT);
    memset(elements, 0, sizeof(elements));
    elements[0].kind = MYSMB_TEXT_PLAYER_SMALL;
    elements[0].foreground = 14U;
    elements[0].background = 4U;
    original = elements[0];
    CHECK(mysmb_text_elements_build(elements, 1U, 9U, &frame));
    CHECK(memcmp(&original, elements, sizeof(original)) == 0);
    CHECK(frame.cells[1].character == '_');
    CHECK(frame.cells[1].background == 4U);
    CHECK(frame.cells[0].background == 9U);
    CHECK(frame.cells[83].character == '>');
    elements[0].face_left = 1U;
    CHECK(mysmb_text_elements_build(elements, 1U, 9U, &frame));
    CHECK(frame.cells[81].character == '<');
    elements[0].face_left = 0U;
    elements[0].pose = MYSMB_TEXT_RUN;
    CHECK(mysmb_text_elements_build(elements, 1U, 9U, &frame));
    CHECK(frame.cells[164].character == '>');
    elements[0].pose = MYSMB_TEXT_JUMP;
    CHECK(mysmb_text_elements_build(elements, 1U, 9U, &frame));
    CHECK(frame.cells[80].character == '<');
    elements[0].x = -1;
    elements[0].y = -1;
    CHECK(mysmb_text_elements_build(elements, 1U, 9U, &frame));
    CHECK(frame.cells[0].character == '/');
    elements[0].x = SHRT_MIN;
    elements[0].y = SHRT_MAX;
    CHECK(mysmb_text_elements_build(elements, 1U, 9U, &frame));
    CHECK(frame.cells[0].character == ' ');
    elements[0].x = 0; elements[0].y = 0; elements[0].pose = 0U;
    elements[1] = elements[0];
    elements[1].kind = MYSMB_TEXT_BRICK;
    CHECK(mysmb_text_elements_build(elements, 2U, 9U, &frame));
    CHECK(frame.cells[0].character == MYSMB_IO_GLYPH_TOP_LEFT);
    before = frame;
    elements[1].kind = MYSMB_TEXT_KIND_COUNT;
    CHECK(!mysmb_text_elements_build(elements, 2U, 9U, &frame));
    CHECK(memcmp(&frame, &before, sizeof(frame)) == 0);
    CHECK(!mysmb_text_elements_build(elements, 65U, 9U, &frame));
    CHECK(!mysmb_text_elements_build(0, 1U, 9U, &frame));
    CHECK(!mysmb_text_elements_build(0, 0U, 16U, &frame));
    CHECK(!mysmb_text_elements_build(0, 0U, 9U, 0));
    elements[1] = elements[0]; elements[1].foreground = 16U;
    CHECK(!mysmb_text_elements_build(elements, 2U, 9U, &frame));
    elements[1] = elements[0]; elements[1].background = 16U;
    CHECK(!mysmb_text_elements_build(elements, 2U, 9U, &frame));
    elements[1] = elements[0]; elements[1].face_left = 2U;
    CHECK(!mysmb_text_elements_build(elements, 2U, 9U, &frame));
    elements[1] = elements[0]; elements[1].pose = MYSMB_TEXT_PLAYER_POSES;
    CHECK(!mysmb_text_elements_build(elements, 2U, 9U, &frame));
    elements[1] = elements[0]; elements[1].kind = MYSMB_TEXT_GOOMBA;
    elements[1].kind = MYSMB_TEXT_BRICK;elements[1].pose = MYSMB_TEXT_RUN;
    CHECK(!mysmb_text_elements_build(elements, 2U, 9U, &frame));
    CHECK(memcmp(&frame, &before, sizeof(frame)) == 0);
    elements[0].x = 255; elements[0].y = 239;
    CHECK(mysmb_text_elements_build(elements, 1U, 9U, &frame));
    CHECK(frame.cells[3999].character == ' ');
    CHECK(mysmb_text_elements_build(0, 0U, 9U, &frame));
    /* Every authored pose/orientation is visible and color-independent. */
    for(i=0U;i<MYSMB_TEXT_KIND_COUNT;++i) {
        elements[0].kind=(mysmb_io_u8)i;elements[0].x=64;elements[0].y=64;
        for(row=0U;row<(i==MYSMB_TEXT_LUIGI_SMALL || i==MYSMB_TEXT_LUIGI_LARGE?
            MYSMB_TEXT_PLAYER_POSES:i==MYSMB_TEXT_SCORE?11U:i==MYSMB_TEXT_JUMP_COIN?4U:
            i==MYSMB_TEXT_FLAG_SCORE?5U:i>=MYSMB_TEXT_VINE_LEAF?1U:i<2U?MYSMB_TEXT_PLAYER_POSES:
            i==MYSMB_TEXT_GOOMBA || i>=MYSMB_TEXT_GOOMBA_FLAT?3U:1U);++row) {
            elements[0].pose=(mysmb_io_u8)row;
            for(facing=0U;facing<2U;++facing) {
                elements[0].face_left=(mysmb_io_u8)facing;
                CHECK(mysmb_text_elements_build(elements,1U,9U,&frame));
                plain=elements[0];plain.foreground=15U;plain.background=0U;
                CHECK(mysmb_text_elements_build(&plain,1U,0U,&monochrome));
                ink=0U;
                for(column=0U;column<MYSMB_IO_TEXT_CELLS;++column) {
                    CHECK(mysmb_io_text_glyph_unicode(frame.cells[column].character)!=0U);
                    CHECK(frame.cells[column].foreground<16U && frame.cells[column].background<16U);
                    CHECK(frame.cells[column].character==monochrome.cells[column].character);
                    if(frame.cells[column].character!=' ') {
                        ++ink;
                        CHECK(frame.cells[column].foreground==elements[0].foreground);
                        CHECK(frame.cells[column].background==elements[0].background);
                        CHECK(monochrome.cells[column].foreground==15U);
                        CHECK(monochrome.cells[column].background==0U);
                    }
                }
                if(ink==0U)fprintf(stderr,"invisible kind=%u pose=%u facing=%u\n",i,row,facing);
                CHECK(ink!=0U);
                /* Interior spaces must carry the object's fill, not sky. */
                for(line=0U;line<50U;++line) {
                    first=80U;last=0U;
                    for(column=0U;column<80U;++column) {
                        if(frame.cells[line*80U+column].character!=' ') {
                            if(first==80U)first=column;
                            last=column;
                        }
                    }
                    if(first==80U)continue;
                    for(column=first;column<=last;++column) {
                        CHECK(frame.cells[line*80U+column].background==elements[0].background);
                        CHECK(monochrome.cells[line*80U+column].background==0U);
                    }
                }
                ++cases;
            }
        }
    }
    for (i = 0U; i < 7U; ++i) {
        elements[i].kind = (mysmb_io_u8)i;
        elements[i].pose = 0U;
        elements[i].face_left = 0U;
        elements[i].x = (short)(i * 32U);
        elements[i].y = 96;
        elements[i].foreground = 15U;
        elements[i].background = (mysmb_io_u8)(i + 1U);
    }
    CHECK(mysmb_text_elements_build(elements, 7U, 9U, &frame));
    for (i = 0U; i < MYSMB_IO_TEXT_CELLS; ++i) {
        CHECK(mysmb_io_text_glyph_unicode(frame.cells[i].character)!=0U);
        CHECK(frame.cells[i].foreground < 16U && frame.cells[i].background < 16U);
    }
    if (argc == 2) {
        preview = fopen(argv[1], "wb");
        CHECK(preview != 0);
        for (row = 0U; row < 50U; ++row) {
            for (column = 0U; column < 80U; ++column)
                fputc(frame.cells[row * 80U + column].character, preview);
            fputc('\n', preview);
        }
        CHECK(fclose(preview) == 0);
    }
    printf("element templates: %u kind/pose/orientation cases; colored/monochrome geometry, visibility, interior fill, clipping/layers/atomicity passed\n",cases);
    return 0;
}
