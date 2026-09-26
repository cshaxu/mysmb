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
    /* PPU sprite RAM after the source NMI's $4014 transfer.  CPU RAM
     * $0200-$02ff remains the following frame's producer backing store. */
    mysmb_u8 visible_oam[0x0100U];
    mysmb_u8 oam_dma_primed;
    /* Translated PPU-visible output state; never a host PPU API. */
    mysmb_u8 palette[0x20U];
    mysmb_u8 ppu_control_0;
    mysmb_u8 ppu_mask;
    mysmb_u8 ppu_name_table;
    mysmb_u8 scroll_x;
    mysmb_u8 scroll_y;
    /* Physical PPU state committed at the NMI boundary.  The translated
     * game mutates the mirror/scroll fields during OperModeExecutionTree;
     * source NMI presents those mutations on the following boundary. */
    mysmb_u8 visible_ppu_control_0;
    mysmb_u8 visible_ppu_mask;
    mysmb_u8 visible_ppu_name_table;
    mysmb_u8 visible_scroll_x;
    mysmb_u8 visible_scroll_y;
    /* Portable copies of the ROM's directly-written APU output registers.
     * They are translated game output, not host audio state: adapters may
     * consume them but may not infer or replace their values. */
    mysmb_u8 apu_delta_counter_load;
    mysmb_u8 apu_channel_enable;
    /* Owner-local NROM data binding; null in ROM-free builds and tests. */
    /* Immutable owner-local CHR pattern data used by the shared PPU compositor. */
    const mysmb_u8 *chr_data;
    mysmb_u16 chr_data_size;
    const mysmb_u8 *area_prg;
    mysmb_u16 area_prg_size;
    /* Owner-local title streams.  The translated title tasks copy these
     * into original CPU-RAM buffers before the NMI transfer consumes them. */
    const mysmb_u8 *title_data;
    mysmb_u16 title_data_size;
    const mysmb_u8 *title_icon_data;
    mysmb_u16 title_icon_data_size;
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
/* ROM $8e19-$8e5b: name tables and scroll variables.  Its InitScroll tail
 * writes physical PPU scroll during the current NMI. */
void mysmb_game_initialize_name_tables(struct mysmb_game *game);
/* ROM $8e92-$8eec, portable execution of an admitted VRAM command stream. */
mysmb_u8 mysmb_game_apply_vram_commands(struct mysmb_game *game,
                                        const mysmb_u8 *commands,
                                        mysmb_u16 command_size);
/* Test-only title compatibility entry point; product roots use the translated
 * ScreenRoutines bootstrap below. */
mysmb_u8 mysmb_game_apply_title_commands(struct mysmb_game *game,
                                         const mysmb_u8 *commands,
                                         mysmb_u16 command_size);
/* Owner-local bindings and the original title ScreenRoutines bootstrap. */
void mysmb_game_bind_chr_source(struct mysmb_game *game,
                                 const mysmb_u8 *chr_data, mysmb_u16 chr_data_size);
void mysmb_game_bind_title_source(struct mysmb_game *game,
                                  const mysmb_u8 *title_data,
                                  mysmb_u16 title_data_size,
                                  const mysmb_u8 *icon_data,
                                  mysmb_u16 icon_data_size);
mysmb_u8 mysmb_game_begin_title_bootstrap(struct mysmb_game *game);
/* ROM Start/WBootCheck/ColdBoot.  This performs the reset subtree against
 * existing CPU RAM, preserving only a valid six-digit warm-boot top score. */
void mysmb_game_reset(struct mysmb_game *game);
/* Create neutral portable storage and enter the translated Start/ColdBoot
 * state.  Resource attachment is inert; the first shared NMI owns title work. */
void mysmb_game_power_on(struct mysmb_game *game);
/* Compatibility fixture constructor for focused tests.  Product roots use
 * mysmb_game_power_on so they cannot advance later ROM work before NMI. */
void mysmb_game_initialize(struct mysmb_game *game);
/* ROM $8231/$8245/$8255, title-menu state and title-to-game-mode transfer. */
void mysmb_game_title_step(struct mysmb_game *game, const struct mysmb_input *input);
void mysmb_game_checkpoint(const struct mysmb_game *game,
                           struct mysmb_checkpoint *checkpoint);
void mysmb_game_frame_initialize(struct mysmb_frame *frame);
void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame);

#endif
