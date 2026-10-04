#include "game/presentation/text/elements.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

static struct mysmb_io_text_frame frame;
static struct mysmb_io_text_frame before;
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
    FILE *preview;

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
    CHECK(frame.cells[0].character == '+');
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
    /* Every authored pose must produce only printable cells and valid fill. */
    for(i=0U;i<MYSMB_TEXT_KIND_COUNT;++i) {
        elements[0].kind=(mysmb_io_u8)i;elements[0].x=64;elements[0].y=64;
        for(row=0U;row<(i==MYSMB_TEXT_SCORE?11U:i==MYSMB_TEXT_JUMP_COIN?4U:
            i==MYSMB_TEXT_FLAG_SCORE?5U:i>=MYSMB_TEXT_VINE_LEAF?1U:i<2U?MYSMB_TEXT_PLAYER_POSES:
            i==MYSMB_TEXT_GOOMBA || i>=MYSMB_TEXT_GOOMBA_FLAT?3U:1U);++row) {
            elements[0].pose=(mysmb_io_u8)row;
            CHECK(mysmb_text_elements_build(elements,1U,9U,&frame));
            for(column=0U;column<MYSMB_IO_TEXT_CELLS;++column) {
                if(frame.cells[column].character<32U || frame.cells[column].character>126U)
                    fprintf(stderr,"kind=%u pose=%u cell=%u code=%u\n",i,row,column,frame.cells[column].character);
                CHECK(frame.cells[column].character>=32U && frame.cells[column].character<=126U);
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
        CHECK(frame.cells[i].character >= 32U && frame.cells[i].character <= 126U);
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
    puts("element templates: pose/mirror/fill/clipping/layers/atomicity passed");
    return 0;
}
