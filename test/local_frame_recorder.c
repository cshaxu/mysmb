#include <stdio.h>
#include <stdlib.h>

#include "game/frame_snapshot.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

/* Owner-local trace writer for M2 T10.  Its record body deliberately matches
 * the reference recorder: ordinal, RAM, two physical CIRAM pages, palette,
 * OAM, then the seven PPU-visible scalar bytes.  The output is protected
 * derived data and must be written only below an ignored build directory. */
static mysmb_u8 mysmb_recorder_write(FILE *output, const void *bytes,
                                     unsigned long count)
{
    return fwrite(bytes, 1U, count, output) == count ? 1U : 0U;
}

static mysmb_u8 mysmb_recorder_script_buttons(const char *script,
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

static mysmb_u8 mysmb_recorder_equals(const char *left, const char *right)
{
    while (*left != '\0' && *right != '\0' && *left == *right) {
        ++left;
        ++right;
    }
    return *left == '\0' && *right == '\0' ? 1U : 0U;
}

static mysmb_u8 mysmb_recorder_write_frame(FILE *output,
                                            const struct mysmb_frame_snapshot *snapshot)
{
    mysmb_u8 scalar[7];

    scalar[0] = snapshot->ppu_control_0;
    scalar[1] = snapshot->ppu_mask;
    scalar[2] = snapshot->ppu_name_table;
    scalar[3] = snapshot->scroll_x;
    scalar[4] = snapshot->scroll_y;
    scalar[5] = (mysmb_u8)(snapshot->ppu_address & 0xffU);
    scalar[6] = (mysmb_u8)(snapshot->ppu_address >> 8U);
    return mysmb_recorder_write(output, &snapshot->sequence, 4UL) &&
        mysmb_recorder_write(output, snapshot->cpu_ram, 0x0800UL) &&
        mysmb_recorder_write(output, snapshot->name_table[0], 0x0400UL) &&
        mysmb_recorder_write(output, snapshot->name_table[1], 0x0400UL) &&
        mysmb_recorder_write(output, snapshot->palette, 0x20UL) &&
        mysmb_recorder_write(output, snapshot->oam, 0x0100UL) &&
        mysmb_recorder_write(output, scalar, 7UL);
}

int main(int argument_count, char **arguments)
{
    static const unsigned char magic[8] = { 'M', 'S', 'F', 'N', 1U, 0U, 0U, 0U };
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_frame_snapshot snapshot;
    FILE *output;
    unsigned long parsed_frames;
    unsigned long start_frame;
    unsigned long release_frame;
    unsigned long index;
    mysmb_u32 frames;
    const char *script;
    mysmb_u8 bootstrap_title;

    if (argument_count < 5 || argument_count > 7) return 64;
    parsed_frames = strtoul(arguments[2], 0, 10);
    start_frame = strtoul(arguments[3], 0, 10);
    release_frame = strtoul(arguments[4], 0, 10);
    if (parsed_frames == 0UL || parsed_frames > 600UL ||
        start_frame >= release_frame || release_frame > parsed_frames) return 64;
    script = 0;
    bootstrap_title = 0U;
    for (index = 5UL; index < (unsigned long)argument_count; ++index) {
        if (mysmb_recorder_equals(arguments[index], "--bootstrap-title") != 0U) {
            bootstrap_title = 1U;
        }
        else if (script == 0) {
            script = arguments[index];
        }
        else {
            return 64;
        }
    }
    frames = (mysmb_u32)parsed_frames;
    output = fopen(arguments[1], "wb");
    if (output == 0) return 65;
    if (mysmb_recorder_write(output, magic, 8UL) == 0U ||
        mysmb_recorder_write(output, &frames, 4UL) == 0U) {
        fclose(output);
        return 65;
    }
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_title_source(&game, mysmb_local_title_data,
                                 MYSMB_LOCAL_TITLE_DATA_SIZE,
                                 mysmb_local_title_icon_data,
                                 MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    if (bootstrap_title != 0U) {
        if (mysmb_game_begin_title_bootstrap(&game) == 0U) {
            fclose(output);
            return 65;
        }
    }
    else if (mysmb_game_apply_title_commands(&game, mysmb_local_title_data,
                                             MYSMB_LOCAL_TITLE_DATA_SIZE) == 0U ||
             mysmb_game_apply_vram_commands(&game, mysmb_local_title_icon_data,
                                            MYSMB_LOCAL_TITLE_ICON_DATA_SIZE) == 0U) {
        fclose(output);
        return 65;
    }
    for (index = 0UL; index < parsed_frames; ++index) {
        input.buttons = index >= start_frame && index < release_frame ?
            MYSMB_BUTTON_START : 0U;
        if (mysmb_recorder_script_buttons(script,
                                          index, &input.buttons) == 0U) {
            fclose(output);
            return 64;
        }
        mysmb_game_tick(&game, &input, &frame);
        mysmb_frame_snapshot_capture(&game, &snapshot);
        if (mysmb_recorder_write_frame(output, &snapshot) == 0U) {
            fclose(output);
            return 65;
        }
    }
    fclose(output);
    return 0;
}
