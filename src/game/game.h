#ifndef MYSMB_GAME_GAME_H
#define MYSMB_GAME_GAME_H

/* This header intentionally uses only C90 language and headers. */
typedef unsigned char mysmb_u8;
typedef unsigned short mysmb_u16;
typedef unsigned long mysmb_u32;

enum {
    MYSMB_SCREEN_WIDTH = 256,
    MYSMB_SCREEN_HEIGHT = 240,
    MYSMB_BUTTON_LEFT = 0x01,
    MYSMB_BUTTON_RIGHT = 0x02,
    MYSMB_BUTTON_START = 0x04
};

struct mysmb_input {
    mysmb_u8 buttons;
};

/* M1 T3 replaces this non-ROM state with the provenance-mapped SMB1 RAM model. */
struct mysmb_game {
    mysmb_u32 frame_number;
    mysmb_u16 actor_x;
    mysmb_u8 actor_direction;
    mysmb_u8 title_started;
};

struct mysmb_frame {
    mysmb_u16 actor_x;
    mysmb_u16 actor_y;
    mysmb_u8 title_started;
};

void mysmb_game_initialize(struct mysmb_game *game);
void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame);

#endif
