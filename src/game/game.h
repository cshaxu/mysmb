#ifndef MYSMB_GAME_GAME_H
#define MYSMB_GAME_GAME_H

/* This header intentionally uses only C90 language and headers. */
typedef unsigned char mysmb_u8;
typedef unsigned short mysmb_u16;
typedef unsigned long mysmb_u32;

enum {
    MYSMB_SCREEN_WIDTH = 256,
    MYSMB_SCREEN_HEIGHT = 240,
    /* ROM $8e5c stores the NES serial order as these bit positions. */
    MYSMB_BUTTON_RIGHT = 0x01,
    MYSMB_BUTTON_LEFT = 0x02,
    MYSMB_BUTTON_DOWN = 0x04,
    MYSMB_BUTTON_UP = 0x08,
    MYSMB_BUTTON_START = 0x10,
    MYSMB_BUTTON_SELECT = 0x20,
    MYSMB_BUTTON_B = 0x40,
    MYSMB_BUTTON_A = 0x80
};

struct mysmb_input {
    mysmb_u8 buttons;
};

struct mysmb_area_command {
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u8 page;
    mysmb_u8 dispatch_id;
};

struct mysmb_game {
    mysmb_u32 frame_number;
    /* Original CPU RAM $0000-$07ff; OAM is RAM[$0200-$02ff]. */
    mysmb_u8 ram[0x0800U];
    /* Original PPU name tables $2000-$23ff and $2400-$27ff. */
    mysmb_u8 name_table[2][0x0400U];
    /* Owner-local NROM data binding; null in ROM-free builds and tests. */
    const mysmb_u8 *area_prg;
    mysmb_u16 area_prg_size;
    mysmb_u8 area_command_count;
    struct mysmb_area_command area_commands[16];
};

struct mysmb_frame {
    mysmb_u16 sprite0_x;
    mysmb_u16 sprite0_y;
    mysmb_u8 start_pressed;
    mysmb_u8 operating_mode;
    mysmb_u8 operating_mode_task;
};

struct mysmb_checkpoint {
    mysmb_u32 frame_number;
    mysmb_u8 operating_mode;
    mysmb_u8 operating_mode_task;
    mysmb_u8 saved_joypad1_bits;
    mysmb_u8 demo_timer;
    mysmb_u8 world_number;
    mysmb_u8 area_number;
};

/* ROM $90cc-$90e6, with Y supplied by its verified caller. */
void mysmb_game_initialize_memory(struct mysmb_game *game, mysmb_u8 initial_y);
/* ROM $8220-$8230. */
void mysmb_game_move_all_sprites_offscreen(struct mysmb_game *game);
/* ROM $8e19-$8e5b. */
void mysmb_game_initialize_name_tables(struct mysmb_game *game);
/* ROM $8e92-$8eec, limited to the title command stream's name-table writes. */
mysmb_u8 mysmb_game_apply_title_commands(struct mysmb_game *game,
                                         const mysmb_u8 *commands,
                                         mysmb_u16 command_size);
void mysmb_game_initialize(struct mysmb_game *game);
/* ROM $8231/$8245/$8255, title-menu state and title-to-game-mode transfer. */
void mysmb_game_title_step(struct mysmb_game *game, const struct mysmb_input *input);
void mysmb_game_checkpoint(const struct mysmb_game *game,
                           struct mysmb_checkpoint *checkpoint);
void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame);

#endif
