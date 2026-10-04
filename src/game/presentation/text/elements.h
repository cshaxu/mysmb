#ifndef MYSMB_GAME_TEXT_ELEMENTS_H
#define MYSMB_GAME_TEXT_ELEMENTS_H

#include "io/video.h"

/* Presentation identities, not ROM object IDs or gameplay state. */
#define MYSMB_TEXT_PLAYER_SMALL 0U
#define MYSMB_TEXT_PLAYER_LARGE 1U
#define MYSMB_TEXT_GOOMBA 2U
#define MYSMB_TEXT_MUSHROOM 3U
#define MYSMB_TEXT_BRICK 4U
#define MYSMB_TEXT_COIN 5U
#define MYSMB_TEXT_PIPE 6U
#define MYSMB_TEXT_FLOWER 7U
#define MYSMB_TEXT_STAR 8U
#define MYSMB_TEXT_FIREBALL 9U
#define MYSMB_TEXT_EXPLOSION 10U
#define MYSMB_TEXT_HAMMER 11U
#define MYSMB_TEXT_CHUNK 12U
#define MYSMB_TEXT_VINE 13U
#define MYSMB_TEXT_PLATFORM 14U
#define MYSMB_TEXT_FLAG 15U
#define MYSMB_TEXT_BUBBLE 16U
#define MYSMB_TEXT_KIND_COUNT 17U
#define MYSMB_TEXT_STAND 0U
#define MYSMB_TEXT_RUN 1U
#define MYSMB_TEXT_JUMP 2U
#define MYSMB_TEXT_ELEMENT_CAPACITY 64U

struct mysmb_text_element {
    short x;
    short y;
    mysmb_io_u8 kind;
    mysmb_io_u8 pose;
    mysmb_io_u8 face_left;
    mysmb_io_u8 foreground;
    mysmb_io_u8 background;
};

/* Optional read-only cell visibility predicate supplied by composition.
 * It may reject cells, but must not mutate the frame, source or game. */
typedef int (*mysmb_text_cell_filter)(const void MYSMB_IO_FAR *context,
    mysmb_io_u16 column, mysmb_io_u16 row);
int mysmb_text_element_draw(
    const struct mysmb_text_element MYSMB_IO_FAR *element,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    mysmb_text_cell_filter filter, const void MYSMB_IO_FAR *context);

/* Caller supplies visible elements in back-to-front order. Coordinates are
 * source pixels. This function never reads RAM/OAM or selects game actions.
 * Invalid input leaves output untouched. All buffers may live outside DGROUP.
 * Input and output storage must not overlap. */
int mysmb_text_elements_build(
    const struct mysmb_text_element MYSMB_IO_FAR *elements,
    mysmb_io_u16 count, mysmb_io_u8 sky,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame);

#endif
