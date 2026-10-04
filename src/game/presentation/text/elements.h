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
#define MYSMB_TEXT_GOOMBA_FLAT 17U
#define MYSMB_TEXT_SHELL 18U
#define MYSMB_TEXT_KOOPA 19U
#define MYSMB_TEXT_BEETLE 20U
#define MYSMB_TEXT_BLOOBER 21U
#define MYSMB_TEXT_BULLET 22U
#define MYSMB_TEXT_FISH 23U
#define MYSMB_TEXT_PODOBOO 24U
#define MYSMB_TEXT_PIRANHA 25U
#define MYSMB_TEXT_HAMMER_BRO 26U
#define MYSMB_TEXT_SPINY 27U
#define MYSMB_TEXT_EGG 28U
#define MYSMB_TEXT_LAKITU 29U
#define MYSMB_TEXT_BOWSER_FRONT 30U
#define MYSMB_TEXT_BOWSER_REAR 31U
#define MYSMB_TEXT_FLAME 32U
#define MYSMB_TEXT_RETAINER 33U
#define MYSMB_TEXT_SPRING 34U
#define MYSMB_TEXT_EMPTY_BLOCK 35U
#define MYSMB_TEXT_VINE_LEAF 36U
#define MYSMB_TEXT_VINE_CAP 37U
#define MYSMB_TEXT_PLATFORM_PART 38U
#define MYSMB_TEXT_FLAG_SCORE 39U
#define MYSMB_TEXT_JUMP_COIN 40U
#define MYSMB_TEXT_SCORE 41U
#define MYSMB_TEXT_KIND_COUNT 42U
#define MYSMB_TEXT_STAND 0U
#define MYSMB_TEXT_RUN 1U
#define MYSMB_TEXT_JUMP 2U
#define MYSMB_TEXT_SKID 3U
#define MYSMB_TEXT_SWIM 4U
#define MYSMB_TEXT_CLIMB 5U
#define MYSMB_TEXT_CROUCH 6U
#define MYSMB_TEXT_THROW 7U
#define MYSMB_TEXT_DEAD 8U
#define MYSMB_TEXT_RUN_SECOND 9U
#define MYSMB_TEXT_RUN_THIRD 10U
#define MYSMB_TEXT_SWIM_SECOND 11U
#define MYSMB_TEXT_SWIM_THIRD 12U
#define MYSMB_TEXT_CLIMB_SECOND 13U
#define MYSMB_TEXT_SWIM_KICK 14U
#define MYSMB_TEXT_SWIM_KICK_SECOND 15U
#define MYSMB_TEXT_SWIM_KICK_THIRD 16U
#define MYSMB_TEXT_PLAYER_POSES 17U
/* Non-player variants: second phase or vertically inverted whole object. */
#define MYSMB_TEXT_SECOND 1U
#define MYSMB_TEXT_INVERTED 2U
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
