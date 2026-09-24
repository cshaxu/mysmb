#include <stdio.h>
#include <stdlib.h>

#include "game/frame_snapshot.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

static mysmb_u32 mysmb_summary_hash(const mysmb_u8 *bytes, mysmb_u16 count,
                                    mysmb_u32 value)
{
    mysmb_u16 index;

    for (index = 0U; index < count; ++index) {
        value ^= (mysmb_u32)bytes[index];
        value *= 16777619UL;
    }
    return value;
}

/* Keep the owner-local native summary on the reference recorder's bounded
 * `frame:buttons[,frame:buttons...]` input syntax.  Values use MySMB's
 * decoded button masks; the three mandatory arguments retain the original
 * one-frame Start route, and an optional script replaces its held byte from
 * its declared frame onward. */
static mysmb_u8 mysmb_summary_script_buttons(const char *script,
                                             unsigned long frame,
                                             mysmb_u8 *buttons)
{
    const char *cursor;
    char *next;
    unsigned long change_frame;
    unsigned long change_buttons;

    if (script == 0) return 1U;
    cursor = script;
    while (*cursor != '\0') {
        change_frame = strtoul(cursor, &next, 10);
        if (next == cursor || *next != ':') return 0U;
        cursor = next + 1;
        change_buttons = strtoul(cursor, &next, 0);
        if (next == cursor || change_frame > 600UL ||
            change_buttons > 0xffUL) return 0U;
        if (change_frame > frame) return 1U;
        *buttons = (mysmb_u8)change_buttons;
        if (*next == '\0') return 1U;
        if (*next != ',') return 0U;
        cursor = next + 1;
    }
    return 1U;
}

int main(int argument_count, char **arguments)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_frame_snapshot snapshot;
    unsigned long frames;
    unsigned long start_frame;
    unsigned long release_frame;
    unsigned long index;
    mysmb_u32 hash;

    if (argument_count != 4 && argument_count != 5) return 64;
    frames = strtoul(arguments[1], 0, 10);
    start_frame = strtoul(arguments[2], 0, 10);
    release_frame = strtoul(arguments[3], 0, 10);
    if (frames == 0UL || frames > 600UL || start_frame >= release_frame ||
        release_frame > frames) return 64;
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    if (mysmb_game_apply_title_commands(&game, mysmb_local_title_data,
                                        MYSMB_LOCAL_TITLE_DATA_SIZE) == 0U)
        return 65;
    if (mysmb_game_apply_vram_commands(&game, mysmb_local_title_icon_data,
                                       MYSMB_LOCAL_TITLE_ICON_DATA_SIZE) == 0U)
        return 65;
    printf("frame,mode,task,ram_ppu_control,ram_ppu_mask,disable_screen,"
           "horizontal_scroll,vertical_scroll,ppu_control,ppu_mask,"
           "ppu_name_table,scroll_x,scroll_y,screen_left_page,screen_left_x,"
           "player_page,player_x,player_pos_for_scroll,player_x_scroll,"
           "player_x_speed,player_facing,player_moving_direction,"
           "player_x_force,friction_high,friction_low,game_engine_subroutine,screen_routine_task,screen_timer,timer_control,interval_timer_control,"
           "game_timer_control,game_timer_hundreds,game_timer_tens,game_timer_ones,"
           "vram_buffer_offset,vram_header_0,vram_header_1,vram_header_2,"
           "ppu_address,ciram_fnv1a,"
           "palette_fnv1a,oam_fnv1a\n");
    for (index = 0UL; index < frames; ++index) {
        /* NES serial Start is bit 3; MySMB's decoded RAM representation is $10. */
        input.buttons = index >= start_frame && index < release_frame ?
            MYSMB_BUTTON_START : 0U;
        if (mysmb_summary_script_buttons(argument_count == 5 ? arguments[4] : 0,
                                         index, &input.buttons) == 0U) return 64;
        mysmb_game_tick(&game, &input, &frame);
        mysmb_frame_snapshot_capture(&game, &snapshot);
        hash = mysmb_summary_hash(snapshot.name_table[0], 0x0400U, 2166136261UL);
        hash = mysmb_summary_hash(snapshot.name_table[1], 0x0400U, hash);
        printf("%lu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%04x,%08lx,",
               index, (unsigned int)frame.operating_mode,
               (unsigned int)frame.operating_mode_task,
               (unsigned int)game.ram[0x0778U],
               (unsigned int)game.ram[0x0779U],
               (unsigned int)game.ram[0x0774U],
               (unsigned int)game.ram[0x073fU],
               (unsigned int)game.ram[0x0740U],
               (unsigned int)snapshot.ppu_control_0,
               (unsigned int)snapshot.ppu_mask,
               (unsigned int)snapshot.ppu_name_table,
               (unsigned int)snapshot.scroll_x,
               (unsigned int)snapshot.scroll_y,
               (unsigned int)game.ram[0x071aU],
               (unsigned int)game.ram[0x071cU],
               (unsigned int)game.ram[0x006dU],
               (unsigned int)game.ram[0x0086U],
               (unsigned int)game.ram[0x0755U],
               (unsigned int)game.ram[0x06ffU],
               (unsigned int)game.ram[0x0057U],
               (unsigned int)game.ram[0x0033U],
               (unsigned int)game.ram[0x0045U],
               (unsigned int)game.ram[0x0705U],
               (unsigned int)game.ram[0x0701U],
               (unsigned int)game.ram[0x0702U],
               (unsigned int)game.ram[0x000eU],
               (unsigned int)game.ram[0x073cU],
               (unsigned int)game.ram[0x07a0U],
               (unsigned int)game.ram[0x0747U],
               (unsigned int)game.ram[0x077fU],
               (unsigned int)game.ram[0x0787U],
               (unsigned int)game.ram[0x07f8U],
               (unsigned int)game.ram[0x07f9U],
               (unsigned int)game.ram[0x07faU],
               (unsigned int)game.ram[0x0300U],
               (unsigned int)game.ram[0x0301U],
               (unsigned int)game.ram[0x0302U],
               (unsigned int)game.ram[0x0303U],
               (unsigned int)snapshot.ppu_address, hash);
        hash = mysmb_summary_hash(snapshot.palette, 0x20U, 2166136261UL);
        printf("%08lx,", hash);
        hash = mysmb_summary_hash(snapshot.oam, 0x0100U, 2166136261UL);
        printf("%08lx\n", hash);
    }
    return 0;
}
