/*
 * Owner-local reference recorder for M2 T9.  This source is compiled only
 * against a local nnes checkout; it is never part of the MySMB product.
 * Records are raw owner-ROM traces and must remain beneath an ignored output
 * directory.  Sampling occurs when SMB1 reaches the NMI RTI at $8181.
 */
#include <stdio.h>
#include <stdlib.h>

#include "core/driver.h"
#include "core/machine.h"

#define MYSMB_REFERENCE_NMI_RETURN 0x8181u
#define MYSMB_REFERENCE_PPU_CONTROL_MIRROR 0x0778u
#define MYSMB_REFERENCE_HORIZONTAL_SCROLL 0x073fu
#define MYSMB_REFERENCE_VERTICAL_SCROLL 0x0740u
#define MYSMB_REFERENCE_OPERATING_MODE 0x0770u
#define MYSMB_REFERENCE_SCREEN_TASK 0x073cu
#define MYSMB_REFERENCE_VRAM_ADDRESS_CONTROL 0x0773u
#define MYSMB_REFERENCE_TITLE_DRAW_TASK 0x0du
#define MYSMB_REFERENCE_TITLE_BUFFER_CONTROL 0x05u
/* This retains the existing 512 driver-run budget in instruction work:
 * core_driver_run executes at most 256 instructions per call. */
#define MYSMB_REFERENCE_MAX_STEPS_PER_FRAME 131072u

static int mysmb_reference_write(FILE *output, const void *bytes, size_t count)
{
    return fwrite(bytes, 1u, count, output) == count;
}

static int mysmb_reference_write_frame(FILE *output, const core_machine *machine)
{
    const core_ppu *ppu = &machine->ppu;
    /* t and fine_x hold the NMI's committed physical scroll even though the
     * main route may have already advanced the RAM scroll variables.  The
     * DrawTitleScreen data read is the exception: it writes $2006/$2007 after
     * the scroll commit, so rebuild its output scalar from source mirrors. */
    lib_u16 display_address = ppu->temporary_address;
    lib_u8 name_table = (lib_u8)((display_address >> 10u) & 3u);
    lib_u8 scroll_x = (lib_u8)(((display_address & 0x001fu) << 3u) | ppu->fine_x);
    lib_u8 scroll_y = (lib_u8)((((display_address >> 5u) & 0x001fu) << 3u) |
        ((display_address >> 12u) & 7u));

    if (machine->ram[MYSMB_REFERENCE_OPERATING_MODE] == 0u &&
        machine->ram[MYSMB_REFERENCE_SCREEN_TASK] == MYSMB_REFERENCE_TITLE_DRAW_TASK &&
        machine->ram[MYSMB_REFERENCE_VRAM_ADDRESS_CONTROL] ==
        MYSMB_REFERENCE_TITLE_BUFFER_CONTROL) {
        name_table = (lib_u8)(machine->ram[MYSMB_REFERENCE_PPU_CONTROL_MIRROR] & 3u);
        scroll_x = machine->ram[MYSMB_REFERENCE_HORIZONTAL_SCROLL];
        scroll_y = machine->ram[MYSMB_REFERENCE_VERTICAL_SCROLL];
        display_address = (lib_u16)(
            ((lib_u16)(scroll_y & 7u) << 12u) |
            ((lib_u16)name_table << 10u) |
            ((lib_u16)((scroll_y >> 3u) & 0x1fu) << 5u) |
            (lib_u16)(scroll_x >> 3u));
    }

    return mysmb_reference_write(output, &ppu->frame_revision,
            sizeof(ppu->frame_revision)) &&
        mysmb_reference_write(output, machine->ram, sizeof(machine->ram)) &&
        mysmb_reference_write(output, ppu->ciram, sizeof(ppu->ciram)) &&
        mysmb_reference_write(output, ppu->palette, sizeof(ppu->palette)) &&
        mysmb_reference_write(output, ppu->oam, sizeof(ppu->oam)) &&
        mysmb_reference_write(output, &ppu->control, sizeof(ppu->control)) &&
        mysmb_reference_write(output, &ppu->mask, sizeof(ppu->mask)) &&
        mysmb_reference_write(output, &name_table, sizeof(name_table)) &&
        mysmb_reference_write(output, &scroll_x, sizeof(scroll_x)) &&
        mysmb_reference_write(output, &scroll_y, sizeof(scroll_y)) &&
        mysmb_reference_write(output, &display_address, sizeof(display_address));
}

/* Optional script syntax is `frame:buttons[,frame:buttons...]`.  A later
 * entry replaces the held byte from its frame onward, allowing a one-frame
 * Start press without introducing a host input path into the product. */
static int mysmb_reference_script_buttons(const char *script,
                                          lib_u32 frame,
                                          unsigned int *buttons)
{
    const char *cursor;
    char *next;
    unsigned long change_frame;
    unsigned long change_buttons;

    if (script == NULL) return 1;
    cursor = script;
    while (*cursor != '\0') {
        change_frame = strtoul(cursor, &next, 10);
        if (next == cursor || *next != ':') return 0;
        cursor = next + 1;
        change_buttons = strtoul(cursor, &next, 0);
        if (next == cursor || change_buttons > 0xffu) return 0;
        if (change_frame > 600u) return 0;
        if ((lib_u32)change_frame > frame) return 1;
        *buttons = (unsigned int)change_buttons;
        if (*next == '\0') return 1;
        if (*next != ',') return 0;
        cursor = next + 1;
    }
    return 1;
}

int main(int argument_count, char **arguments)
{
    core_driver *driver = LIB_NULL;
    FILE *output;
    unsigned long parsed_frames;
    lib_u32 requested_frames;
    lib_u32 recorded;
    lib_u32 step_count;
    lib_u32 last_frame_revision;
    lib_bool have_frame_revision;
    unsigned int buttons;
    const unsigned char magic[8] = { 'M', 'S', 'F', 'R', 1u, 0u, 0u, 0u };

    if (argument_count != 5 && argument_count != 6) return 64;
    parsed_frames = strtoul(arguments[3], LIB_NULL, 10);
    buttons = (unsigned int)strtoul(arguments[4], LIB_NULL, 0);
    if (parsed_frames == 0u || parsed_frames > 600u || buttons > 0xffu)
        return 64;
    requested_frames = (lib_u32)parsed_frames;
    output = fopen(arguments[2], "wb");
    if (output == LIB_NULL) return 65;
    if (!mysmb_reference_write(output, magic, sizeof(magic)) ||
        !mysmb_reference_write(output, &requested_frames, sizeof(requested_frames))) {
        fclose(output);
        return 66;
    }
    if (core_driver_create(&driver, &(core_driver_options){ 0u, LIB_FALSE }) !=
        LIB_STATUS_OK || !core_driver_set_media(driver, arguments[1],
        LIB_STORAGE_MEDIUM_READONLY) || core_machine_breakpoint_set(driver->machine,
        MYSMB_REFERENCE_NMI_RETURN, LIB_TRUE) != LIB_STATUS_OK) {
        fclose(output);
        return 67;
    }
    recorded = 0u;
    step_count = 0u;
    last_frame_revision = 0u;
    have_frame_revision = LIB_FALSE;
    if (!mysmb_reference_script_buttons(argument_count == 6 ? arguments[5] : NULL,
                                        recorded, &buttons)) {
        fclose(output);
        (void)core_driver_destroy(driver);
        return 68;
    }
    core_controller_set_buttons(&driver->machine->controller, (lib_u8)buttons);
    while (recorded < requested_frames &&
           step_count < requested_frames * MYSMB_REFERENCE_MAX_STEPS_PER_FRAME) {
        core_run_result result;

        if (driver->machine->pc == MYSMB_REFERENCE_NMI_RETURN) {
            /* Sample before RTI.  Stepping the RTI below clears this program
             * counter, so every subsequent return is independently visible.
             * The frame ordinal is an NMI-return sequence: two returns can
             * share a PPU revision yet have different RAM timer state.  PPU
             * revisions may also have gaps while NMI is masked; only a
             * regression invalidates the sequence. */
            if (have_frame_revision &&
                driver->machine->ppu.frame_revision < last_frame_revision) break;
            if (!mysmb_reference_write_frame(output, driver->machine)) break;
            last_frame_revision = driver->machine->ppu.frame_revision;
            have_frame_revision = LIB_TRUE;
            ++recorded;
            if (recorded == requested_frames) break;
            if (!mysmb_reference_script_buttons(argument_count == 6 ? arguments[5] : NULL,
                                                recorded, &buttons)) break;
            core_controller_set_buttons(&driver->machine->controller, (lib_u8)buttons);
        }
        if (core_machine_debug_step(driver->machine, 1u, 1024u, &result) !=
            LIB_STATUS_OK || result.trap_valid) break;
        ++step_count;
    }
    fclose(output);
    (void)core_driver_destroy(driver);
    return recorded == requested_frames ? 0 : 68;
}
