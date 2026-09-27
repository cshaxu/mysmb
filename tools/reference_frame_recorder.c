/*
 * Owner-local reference recorder for M2 T9.  This source is compiled only
 * against a local nnes checkout; it is never part of the MySMB product.
 * Records are raw owner-ROM traces and must remain beneath an ignored output
 * directory.  Sampling occurs when SMB1 reaches the NMI RTI at $8181.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/driver.h"
#include "core/machine.h"

#define MYSMB_REFERENCE_NMI_RETURN 0x8181u
#define MYSMB_REFERENCE_NMI_ENTRY 0x8085u
#define MYSMB_REFERENCE_T28_INIT_SCREEN_SUCCESSOR 0x85c8u
#define MYSMB_REFERENCE_T28_VRAM_COMMAND_ENTRY 0x8e92u
#define MYSMB_REFERENCE_T28_VRAM_EXIT 0x8ee6u
#define MYSMB_REFERENCE_T29_AREA_ENTRY_RETURN 0x919eu
#define MYSMB_REFERENCE_PPU_CONTROL_MIRROR 0x0778u
#define MYSMB_REFERENCE_HORIZONTAL_SCROLL 0x073fu
#define MYSMB_REFERENCE_VERTICAL_SCROLL 0x0740u
#define MYSMB_REFERENCE_OPERATING_MODE 0x0770u
#define MYSMB_REFERENCE_SCREEN_TASK 0x073cu
#define MYSMB_REFERENCE_VRAM_ADDRESS_CONTROL 0x0773u
#define MYSMB_REFERENCE_TITLE_DRAW_TASK 0x0du
#define MYSMB_REFERENCE_TITLE_BUFFER_CONTROL 0x05u
#define MYSMB_REFERENCE_AUDIO_BYTES 14u
/* This retains the existing 512 driver-run budget in instruction work:
 * core_driver_run executes at most 256 instructions per call. */
#define MYSMB_REFERENCE_MAX_STEPS_PER_FRAME 131072u

/* Aggregate diagnostics only: no instruction bytes or RAM payloads. Counters
 * cover the recorded window, excluding warmup. For conditional branches,
 * fallthrough2/other distinguish the two instruction successors. */
static unsigned long mysmb_pc_hits[32768];
static unsigned long mysmb_pc_fallthrough2[32768];
static unsigned long mysmb_pc_other[32768];

static int mysmb_reference_write_coverage(const char *path)
{
    FILE *output;
    unsigned int offset;
    int ok;
    if (path == NULL) return 1;
    output = fopen(path, "w");
    if (output == NULL) return 0;
    ok = fprintf(output, "pc,hits,fallthrough2,other\n") >= 0;
    for (offset = 0u; offset < 32768u && ok; ++offset) {
        if (mysmb_pc_hits[offset] != 0ul) {
            ok = fprintf(output, "%04x,%lu,%lu,%lu\n", offset + 0x8000u,
                mysmb_pc_hits[offset], mysmb_pc_fallthrough2[offset],
                mysmb_pc_other[offset]) >= 0;
        }
    }
    if (fclose(output) != 0) ok = 0;
    return ok;
}

static int mysmb_reference_write(FILE *output, const void *bytes, size_t count)
{
    return fwrite(bytes, 1u, count, output) == count;
}

static int mysmb_reference_write_audio(FILE *output,
                                       const core_machine *machine)
{
    static const lib_u16 offsets[MYSMB_REFERENCE_AUDIO_BYTES] = {
        0x00f1u, 0x00f2u, 0x00f3u, 0x00f4u, 0x07b1u, 0x07b2u, 0x07bbu,
        0x07bdu, 0x07beu, 0x07bfu, 0x07c5u, 0x07c6u, 0x00ffu, 0x00fcu
    };
    lib_u8 index;

    for (index = 0u; index < MYSMB_REFERENCE_AUDIO_BYTES; ++index) {
        if (!mysmb_reference_write(output, &machine->ram[offsets[index]], 1u))
            return 0;
    }
    return 1;
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
        mysmb_reference_write_audio(output, machine) &&
        mysmb_reference_write(output, &ppu->control, sizeof(ppu->control)) &&
        mysmb_reference_write(output, &ppu->mask, sizeof(ppu->mask)) &&
        mysmb_reference_write(output, &name_table, sizeof(name_table)) &&
        mysmb_reference_write(output, &scroll_x, sizeof(scroll_x)) &&
        mysmb_reference_write(output, &scroll_y, sizeof(scroll_y)) &&
        mysmb_reference_write(output, &display_address, sizeof(display_address));
}

/* Optional script syntax is `frame:buttons[,frame:buttons...]`.  The byte is
 * the NES controller's serial bit order: A=$01, B=$02, Select=$04,
 * Start=$08, Up=$10, Down=$20, Left=$40, Right=$80.  A later entry replaces
 * the held byte from its frame onward, allowing a one-frame Start press
 * without introducing a host input path into the product. */
static int mysmb_reference_script_buttons(const char *script,
                                          lib_u32 frame,
                                          lib_u32 maximum_frame,
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
        if (change_frame > maximum_frame) return 0;
        if ((lib_u32)change_frame > frame) return 1;
        *buttons = (unsigned int)change_buttons;
        if (*next == '\0') return 1;
        if (*next != ',') return 0;
        cursor = next + 1;
    }
    return 1;
}

static int mysmb_reference_parse_warmup(const char *argument,
                                        lib_u32 *warmup)
{
    static const char prefix[] = "--warmup=";
    unsigned int index;
    char *next;
    unsigned long parsed;

    for (index = 0u; prefix[index] != '\0'; ++index) {
        if (argument[index] != prefix[index]) return 0;
    }
    parsed = strtoul(argument + index, &next, 10);
    if (next == argument + index || *next != '\0' || parsed > 3600u)
        return -1;
    *warmup = (lib_u32)parsed;
    return 1;
}

struct mysmb_reference_ram_write {
    lib_u32 frame;
    lib_u16 address;
    lib_u8 value;
    lib_bool present;
};

/* A single controlled RAM precondition for a source branch.  This stays in
 * the local ROM recorder and is never a product input path. */
static int mysmb_reference_parse_ram_write(
    const char *argument, struct mysmb_reference_ram_write *write)
{
    static const char prefix[] = "--ram-write=";
    unsigned int index;
    char *next;
    unsigned long frame;
    unsigned long address;
    unsigned long value;

    if (write->present) return -1;
    for (index = 0u; prefix[index] != '\0'; ++index) {
        if (argument[index] != prefix[index]) return 0;
    }
    frame = strtoul(argument + index, &next, 0);
    if (next == argument + index || *next != ':') return -1;
    address = strtoul(next + 1, &next, 0);
    if (*next != ':' || address > 0x07ffu) return -1;
    value = strtoul(next + 1, &next, 0);
    if (*next != '\0' || value > 0xffu) return -1;
    write->frame = (lib_u32)frame;
    write->address = (lib_u16)address;
    write->value = (lib_u8)value;
    write->present = LIB_TRUE;
    return 1;
}

static void mysmb_reference_apply_ram_write(
    struct mysmb_reference_ram_write *write, lib_u32 frame, lib_u8 *ram)
{
    if (write->present && write->frame == frame) {
        ram[write->address] = write->value;
        write->present = LIB_FALSE;
    }
}

/* Fixed T26 source-route precondition.  It matches the native recorder's
 * slot-zero GameEngine/FloateyNumbersRoutine 1-UP fixture and intentionally
 * exposes no arbitrary multi-write facility. */
static void mysmb_reference_apply_t26_floatey_fixture(lib_u8 *ram)
{
    ram[0x0770u] = 1u;
    ram[0x0772u] = 3u;
    ram[0x000eu] = 8u;
    ram[0x000fu] = 0u;
    ram[0x0016u] = 9u;
    ram[0x001eu] = 2u;
    ram[0x071fu] = 7u;
    ram[0x0110u] = 0x0bu;
    ram[0x0117u] = 0x80u;
    ram[0x011eu] = 0x40u;
    ram[0x012cu] = 0x2bu;
    ram[0x06e5u] = 0x20u;
    ram[0x075au] = 2u;
}

/* Fixed T26 Floatey return and numeric alternate-OAM leaves. */
static void mysmb_reference_apply_t26_floatey_leaf_fixture(
    lib_u8 *ram, lib_u8 kind)
{
    ram[0x0770u] = 1u;
    ram[0x0772u] = 3u;
    ram[0x000eu] = 8u;
    ram[0x000fu] = 0u;
    ram[0x0016u] = kind == 0u ? 9u : 0u;
    ram[0x001eu] = 0u;
    ram[0x071fu] = 7u;
    ram[0x0110u] = kind == 0u ? 2u : 6u;
    ram[0x0117u] = 0x40u;
    ram[0x011eu] = kind == 0u ? 0x40u : 0x10u;
    ram[0x012cu] = kind == 0u ? 0u : 0x2bu;
    ram[0x06e5u] = 0x20u;
    ram[0x03eeu] = 1u;
    ram[0x06edu] = 0x40u;
}

/* Fixed T26 terminal precondition for PlayerEndWorld's world-eight B path. */
static void mysmb_reference_apply_t26_endworld_b_fixture(lib_u8 *ram)
{
    ram[0x0770u] = 2u;
    ram[0x0772u] = 4u;
    ram[0x075fu] = 7u;
    ram[0x07a1u] = 0u;
    ram[0x06fcu] = 0x40u;
    ram[0x06fdu] = 0u;
}

/* Fixed T26 PlayerEndWorld precondition for the ordinary next-world path. */
static void mysmb_reference_apply_t26_endworld_next_fixture(lib_u8 *ram)
{
    ram[0x0770u] = 2u;
    ram[0x0772u] = 4u;
    ram[0x075fu] = 2u;
    ram[0x0760u] = 3u;
    ram[0x075cu] = 2u;
    ram[0x0757u] = 0u;
    ram[0x07a1u] = 0u;
}

/* Fixed T26 PlayerEndWorld return leaves.  Timer control preserves the
 * nonzero timer for EndExitOne; the second condition reaches EndExitTwo. */
static void mysmb_reference_apply_t26_endworld_return_fixture(
    lib_u8 *ram, lib_u8 kind)
{
    ram[0x0770u] = 2u;
    ram[0x0772u] = 4u;
    ram[0x00fcu] = 0u;
    ram[0x06fcu] = 0u;
    ram[0x06fdu] = 0u;
    if (kind == 0u) {
        ram[0x075fu] = 2u;
        ram[0x07a1u] = 5u;
        ram[0x0747u] = 1u;
        return;
    }
    ram[0x075fu] = 7u;
    ram[0x07a1u] = 0u;
}

/* Fixed T26 PrintVictoryMessages preconditions: first text, world-eight
 * music text, and the non-world-eight end-timer branch. */
static void mysmb_reference_apply_t26_victory_message_fixture(
    lib_u8 *ram, lib_u8 primary, lib_u8 secondary, lib_u8 player,
    lib_u8 world)
{
    ram[0x0770u] = 2u;
    ram[0x0772u] = 3u;
    ram[0x0719u] = primary;
    ram[0x0749u] = secondary;
    ram[0x0753u] = player;
    ram[0x075fu] = world;
    ram[0x00fcu] = 0u;
    ram[0x07a1u] = 0u;
}

/* Fixed T26 SetupVictoryMode and PlayerVictoryWalk preconditions. */
static void mysmb_reference_apply_t26_victory_walk_fixture(
    lib_u8 *ram, lib_u8 kind)
{
    ram[0x0770u] = 2u;
    ram[0x00fcu] = 0u;
    if (kind == 0u) {
        ram[0x0772u] = 1u;
        ram[0x071bu] = 1u;
        return;
    }
    ram[0x0772u] = 2u;
    ram[0x0034u] = 1u;
    ram[0x0086u] = 0x60u;
    ram[0x071au] = kind == 1u ? 1u : 0u;
    ram[0x071bu] = kind == 1u ? 1u : 0u;
    ram[0x071cu] = 0u;
    ram[0x071du] = 0xffu;
    ram[0x006du] = kind == 1u ? 1u : 0u;
    ram[0x0035u] = 0u;
    ram[0x0768u] = 0u;
}

/* Fixed T26 outer-dispatch precondition.  The missing Bowser front makes the
 * original BridgeCollapse take SetM2, recording the VictoryMode handoff
 * without turning bridge, enemy-loop, or player graphics collaborators into
 * T26 evidence. */
static void mysmb_reference_apply_t26_victory_bridge_handoff_fixture(
    lib_u8 *ram)
{
    ram[0x0770u] = 2u;
    ram[0x0772u] = 0u;
    ram[0x0368u] = 0u;
    ram[0x0016u] = 0u;
    ram[0x00fcu] = 0u;
}

/* Direct ROM inputs for a repeatable VictoryMode/AutoPlayer standing route.
 * Sprite0HitDetectFlag is zero so the source NMI takes SkipSprite0 rather
 * than waiting for a fixture-unrelated physical sprite-zero hit. */
static void mysmb_reference_apply_t26_victory_outer_player_fixture(lib_u8 *ram)
{
    mysmb_reference_apply_t26_victory_bridge_handoff_fixture(ram);
    ram[0x000eu] = 8u; ram[0x000fu] = 0u;
    ram[0x0016u] = 0u; ram[0x001du] = 0u;
    ram[0x0033u] = 1u; ram[0x0045u] = 1u;
    ram[0x0057u] = 0u; ram[0x006du] = 0u;
    ram[0x0086u] = 0x30u; ram[0x009fu] = 0u;
    ram[0x00b5u] = 1u; ram[0x00ceu] = 0x80u;
    ram[0x03c4u] = 0u; ram[0x03d0u] = 0u;
    ram[0x06e4u] = 0u; ram[0x0700u] = 0u;
    ram[0x0704u] = 0u; ram[0x070bu] = 0u;
    ram[0x070cu] = 1u; ram[0x070du] = 0u;
    ram[0x0714u] = 0u; ram[0x071au] = 0u;
    ram[0x071bu] = 0u; ram[0x071cu] = 0u;
    ram[0x071du] = 0xffu; ram[0x071fu] = 7u;
    ram[0x0722u] = 0u; ram[0x0754u] = 1u;
    ram[0x0781u] = 1u; ram[0x079eu] = 0u;
}

/* Fixed T27 ScreenRoutines inputs.  These are recorder-only snapshots at an
 * NMI boundary; no product or platform path can select them. */
static void mysmb_reference_apply_t27_screen_fixture(lib_u8 *ram, lib_u8 kind)
{
    ram[0x0722u] = 0u;
    ram[0x07a0u] = 0u;
    ram[0x0774u] = 1u;
    ram[0x0759u] = 0u;
    ram[0x0769u] = 0u;
    ram[0x077au] = 0u;
    ram[0x0753u] = 0u;
    if (kind == 14u) {
        ram[0x073cu] = 3u;
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        return;
    }
    if (kind == 15u) {
        ram[0x073cu] = 14u;
        ram[0x0770u] = 0u;
        ram[0x0772u] = 1u;
        return;
    }
    ram[0x073cu] = kind == 0u || kind == 3u ||
        kind == 8u || kind == 9u ? 4u :
        (kind == 5u || kind == 6u ? 5u :
        (kind == 12u || kind == 13u ? 7u : 6u));
    if (kind == 0u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        ram[0x0759u] = 1u;
        return;
    }
    if (kind == 1u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        ram[0x0752u] = 0u;
        ram[0x074eu] = 3u;
        ram[0x0769u] = 1u;
        return;
    }
    if (kind == 3u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        return;
    }
    if (kind == 4u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        ram[0x0752u] = 0u;
        ram[0x074eu] = 1u;
        return;
    }
    if (kind == 5u || kind == 6u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        ram[0x07a0u] = kind == 5u ? 1u : 0u;
        return;
    }
    if (kind == 7u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        ram[0x0752u] = 1u;
        return;
    }
    if (kind == 8u || kind == 9u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        ram[0x0759u] = 1u;
        ram[0x077au] = 1u;
        ram[0x0753u] = kind == 8u ? 0u : 1u;
        return;
    }
    if (kind == 10u || kind == 11u) {
        ram[0x0770u] = 3u;
        ram[0x0772u] = 1u;
        ram[0x077au] = 1u;
        ram[0x0753u] = kind == 10u ? 1u : 0u;
        return;
    }
    if (kind == 12u || kind == 13u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 1u;
        ram[0x07a0u] = kind == 12u ? 1u : 0u;
        return;
    }
    ram[0x0770u] = 3u;
    ram[0x0772u] = 1u;
}

/* Fixed T28 entry to the actual TitleScreenMode -> ScreenRoutines -> InitScreen
 * route.  The recorder alters RAM only at an NMI return; execution resumes
 * through the normal ROM operation-mode selector, never at a leaf PC. */
static void mysmb_reference_apply_t28_init_screen_fixture(lib_u8 *ram)
{
    ram[0x0722u] = 0u;
    ram[0x07a0u] = 0u;
    ram[0x0774u] = 1u;
    ram[0x0759u] = 0u;
    ram[0x0769u] = 0u;
    ram[0x077au] = 0u;
    ram[0x0753u] = 0u;
    ram[0x073cu] = 0u;
    ram[0x0770u] = 0u;
    ram[0x0772u] = 1u;
}

/* T28/S6 prepares a source-owned Buffer1 packet at an ordinary NMI return.
 * The next NMI still follows the ROM's normal UpdateScreen call; this helper
 * neither redirects the PC nor supplies a synthetic caller stack. */
static void mysmb_reference_apply_t28_vram_fixture(lib_u8 *ram, lib_u8 kind)
{
    ram[0x0773u] = 0u;
    ram[0x0300u] = kind == 0u ? 5u : 7u;
    ram[0x0301u] = 0x20u;
    ram[0x0302u] = 0x00u;
    if (kind == 0u) {
        /* $43: linear increment, repeated byte, length three. */
        ram[0x0303u] = 0x43u;
        ram[0x0304u] = 0x29u;
        ram[0x0305u] = 0u;
    }
    else {
        /* $83: vertical increment, three distinct bytes. */
        ram[0x0303u] = 0x83u;
        ram[0x0304u] = 0x11u;
        ram[0x0305u] = 0x22u;
        ram[0x0306u] = 0x33u;
        ram[0x0307u] = 0u;
    }
}

/* T28/S7 changes only RAM at an NMI return.  The following normal operation
 * mode dispatch reaches GameEngine and its RunGameTimer tail. */
static void mysmb_reference_apply_t28_status_timer_fixture(lib_u8 *ram)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 3u;
    ram[0x000eu] = 8u;
    ram[0x00b5u] = 0u;
    ram[0x0787u] = 0u;
    ram[0x07f8u] = 1u;
    ram[0x07f9u] = 0u;
    ram[0x07fau] = 2u;
}

static void mysmb_reference_apply_t28_status_timer_borrow_fixture(lib_u8 *ram)
{
    mysmb_reference_apply_t28_status_timer_fixture(ram);
    ram[0x07fau] = 0u;
}

static void mysmb_reference_apply_t28_top_score_fixture(lib_u8 *ram,
                                                         lib_u8 copy)
{
    ram[0x07d7u] = 1u;
    ram[0x07d8u] = 2u;
    ram[0x07d9u] = copy != 0u ? 3u : 4u;
    ram[0x07ddu] = 1u;
    ram[0x07deu] = 2u;
    ram[0x07dfu] = copy != 0u ? 4u : 3u;
    ram[0x07e3u] = 1u;
    ram[0x07e4u] = 2u;
    ram[0x07e5u] = 2u;
}

/* T28/S8 uses only an NMI-boundary source-RAM precondition.  The next
 * normal mode selector invokes InitializeArea; this never redirects a PC. */
static void mysmb_reference_apply_t28_area_entry_fixture(lib_u8 *ram)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 0u;
}

/* This enters the normal title task-two fallthrough from PrimaryGameSetup
 * into SecondaryGameSetup, without calling either translated leaf directly. */
static void mysmb_reference_apply_t28_secondary_setup_fixture(lib_u8 *ram)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 0u;
    ram[0x0772u] = 2u;
}

/* T29/S2 records the source GameMode task-two path.  Each variant changes
 * only source RAM at an NMI return; the ROM mode selector reaches
 * SecondaryGameSetup and GetAreaMusic naturally. */
static void mysmb_reference_apply_t29_area_music_fixture(lib_u8 *ram,
                                                          lib_u8 kind)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 2u;
    ram[0x074eu] = 3u;
    ram[0x0710u] = 0u;
    ram[0x0752u] = 0u;
    ram[0x0743u] = 0u;
    if (kind == 0u) ram[0x074eu] = 1u;
    else if (kind == 1u) ram[0x0710u] = 6u;
    else if (kind == 2u) ram[0x0752u] = 2u;
    else ram[0x0743u] = 1u;
}

static void mysmb_reference_apply_t29_area_entry_fixture(lib_u8 *ram,
                                                          lib_u8 kind)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 3u;
    ram[0x000eu] = 0u;
    ram[0x071au] = 3u;
    ram[0x074eu] = 1u;
    ram[0x0710u] = 2u;
    ram[0x0752u] = 0u;
    ram[0x0715u] = 2u;
    ram[0x0757u] = 1u;
    ram[0x079fu] = 0x23u;
    ram[0x0755u] = 0xa5u;
    if (kind == 1u) {
        ram[0x0752u] = 2u;
        ram[0x0715u] = 0u;
    }
    else if (kind == 2u) {
        ram[0x0758u] = 1u;
        ram[0x0398u] = 0u;
    }
    else if (kind == 3u) {
        ram[0x074eu] = 0u;
        ram[0x0007u] = 1u;
    }
}

/* T29/S4 changes only source RAM at an ordinary NMI return.  The next NMI
 * reaches PlayerLoseLife or GameOverMode through the normal mode selector;
 * this fixture neither redirects the PC nor manufactures a call stack. */
static void mysmb_reference_apply_t29_life_mode_fixture(lib_u8 *ram,
                                                         lib_u8 kind)
{
    ram[0x0722u] = 0u;
    ram[0x0774u] = 0u;
    ram[0x077au] = 0u;
    ram[0x0753u] = 0u;
    ram[0x075au] = 2u;
    ram[0x075bu] = 0u;
    ram[0x075cu] = 0u;
    ram[0x075fu] = 0u;
    ram[0x0761u] = 0xffu;
    ram[0x071au] = 7u;
    ram[0x06fcu] = 0u;
    ram[0x07a0u] = 0u;
    if (kind == 0u || kind == 1u) {
        ram[0x0770u] = 1u;
        ram[0x0772u] = 3u;
        ram[0x000eu] = 6u;
        if (kind == 1u) ram[0x075au] = 0u;
    }
    else {
        ram[0x0770u] = 3u;
        ram[0x0772u] = kind == 5u ? 0u : 2u;
        if (kind == 2u) ram[0x07a0u] = 0x18u;
        else if (kind == 3u) {
            ram[0x06fcu] = 0x10u;
            ram[0x075fu] = 4u;
        }
        else {
            ram[0x06fcu] = 0x10u;
            ram[0x077au] = 1u;
            ram[0x075au] = 0xffu;
            ram[0x075fu] = 1u;
            ram[0x0761u] = 2u;
            ram[0x0766u] = 6u;
        }
    }
}

/* T29/S5 starts a normal GameEngine parser tail at an NMI boundary.  The
 * ROM's own RunParser check calls AreaParserTaskHandler on following frames;
 * no leaf program counter or synthetic return stack is installed. */
static void mysmb_reference_apply_t29_parser_dispatch_fixture(lib_u8 *ram)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 3u;
    ram[0x000eu] = 8u;
    ram[0x0773u] = 0u;
    ram[0x071fu] = 8u;
    ram[0x0725u] = 0u;
    ram[0x0726u] = 0u;
    ram[0x06a0u] = 0u;
    ram[0x0728u] = 0u;
    ram[0x073fu] = 0u;
}

/* T29/S8 selects the final object in the original L_GroundArea16 stream
 * (CPU $a9fc: $6d,$c5).  It changes RAM only at an NMI boundary; GameEngine
 * still reaches AreaParserCore, ProcessAreaData and the row-13 JumpEngine
 * through the ROM's ordinary parser path.  $a9d0 is the post-header stream
 * address, and offset $2c is the real object's byte offset in that stream. */
static void mysmb_reference_apply_t29_special_object_fixture(lib_u8 *ram)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 3u;
    ram[0x000eu] = 8u;
    ram[0x0773u] = 0u;
    ram[0x071fu] = 8u;
    ram[0x0725u] = 1u;
    ram[0x0726u] = 6u;
    ram[0x0728u] = 0u;
    ram[0x072au] = 0u;
    ram[0x072bu] = 0u;
    ram[0x072cu] = 0x2cu;
    ram[0x072du] = 0u;
    ram[0x072eu] = 0u;
    ram[0x072fu] = 0u;
    ram[0x0730u] = 0xffu;
    ram[0x0731u] = 0xffu;
    ram[0x0732u] = 0xffu;
    ram[0x073fu] = 0u;
    ram[0x00e7u] = 0xd0u;
    ram[0x00e8u] = 0xa9u;
    ram[0x074eu] = 1u;
    ram[0x075fu] = 0u;
}

static void mysmb_reference_apply_t28_title_score_fixture(lib_u8 *ram)
{
    ram[0x0770u] = 0u;
    ram[0x0772u] = 1u;
    ram[0x073cu] = 14u;
}

int main(int argument_count, char **arguments)
{
    core_driver *driver = LIB_NULL;
    FILE *output;
    unsigned long parsed_frames;
    lib_u32 requested_frames;
    lib_u32 recorded;
    lib_u32 elapsed;
    lib_u32 warmup_frames;
    lib_u32 total_frames;
    lib_u32 step_count;
    int warmup_result;
    const char *script;
    const char *coverage_path;
    struct mysmb_reference_ram_write ram_write;
    lib_u8 t26_fixture;
    lib_bool direct_warp_text;
    lib_bool t28_vram_pending;
    lib_u8 t28_vram_phase;
    lib_u8 t29_area_entry_phase;
    lib_u32 last_frame_revision;
    lib_bool have_frame_revision;
    unsigned int buttons;
    const unsigned char magic[8] = { 'M', 'S', 'F', 'R', 2u, 0u, 0u, 0u };

    if (argument_count < 5 || argument_count > 9) return 64;
    parsed_frames = strtoul(arguments[3], LIB_NULL, 10);
    buttons = (unsigned int)strtoul(arguments[4], LIB_NULL, 0);
    if (parsed_frames == 0u || parsed_frames > 600u || buttons > 0xffu)
        return 64;
    requested_frames = (lib_u32)parsed_frames;
    warmup_frames = 0u;
    script = NULL;
    coverage_path = NULL;
    ram_write.present = LIB_FALSE;
    t26_fixture = 0u;
    direct_warp_text = LIB_FALSE;
    t28_vram_pending = LIB_FALSE;
    t28_vram_phase = 0u;
    t29_area_entry_phase = 0u;
    for (recorded = 5u; recorded < (lib_u32)argument_count; ++recorded) {
        if (strncmp(arguments[recorded], "--pc-coverage=", 14u) == 0) {
            if (coverage_path != NULL || arguments[recorded][14] == '\0')
                return 64;
            coverage_path = arguments[recorded] + 14;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-floatey-oneup") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 1u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-endworld-b") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 2u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-first-message") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 3u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-music-message") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 4u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-end-timer") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 5u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-setup") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 6u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-no-walk") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 7u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-walk") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 8u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-endworld-next-world") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 9u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-bridge-handoff") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 10u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-luigi-message") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 11u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-retainer-message") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 12u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-counter-only") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 13u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-endworld-timer-active") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 14u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-endworld-no-b") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 15u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-floatey-timer-zero") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 16u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-floatey-numeric-alt") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 17u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t26-victory-outer-player") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 18u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-timeup") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 19u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-intermediate") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 20u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-gameover") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 21u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-no-timeup") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 22u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-player-intermediate") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 23u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-reset-pending") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 24u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-reset-expired") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 25u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-nointer-alt") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 26u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-timeup-luigi") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 27u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-timeup-mario") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 28u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-gameover-luigi") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 29u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-gameover-mario") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 30u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-task7-pending") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 31u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-task7-expired") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 32u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-bottom-status") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 33u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-screen-title-score") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 34u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-warp-text4") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 35u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-warp-text5") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 36u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t27-warp-text6") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 37u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-render-left") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 38u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-render-right") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 39u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-attribute-left") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 40u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-attribute-right") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 41u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-palette-normal") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 42u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-palette-wrap") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 43u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-palette-frame-gate") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 44u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-palette-buffer-full") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 45u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-remove-coin-water") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 46u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-write-block") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 47u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-rem-bridge") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 48u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-destroy-block") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 49u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-init-screen") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 50u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-vram-repeat") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 51u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-vram-vertical") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 52u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-status-timer") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 53u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-status-timer-borrow") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 54u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-top-score-copy") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 55u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-top-score-retain") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 56u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-area-entry") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 58u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-secondary-setup") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 59u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-area-music-normal") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 60u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-area-music-pipe") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 61u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-area-music-alternate") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 62u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-area-music-cloud") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 63u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-area-entry-normal") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 64u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-area-entry-alternate") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 65u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-area-entry-vine") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 66u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-area-entry-water") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 67u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-life-survive") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 68u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-life-final") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 69u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-gameover-wait") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 70u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-gameover-single") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 71u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-gameover-two-player") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 72u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-gameover-setup") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 73u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-parser-dispatch") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 74u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t29-special-object") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 75u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t28-title-score") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 57u;
            continue;
        }
        warmup_result = mysmb_reference_parse_ram_write(arguments[recorded],
                                                         &ram_write);
        if (warmup_result < 0) return 64;
        if (warmup_result != 0) continue;
        warmup_result = mysmb_reference_parse_warmup(arguments[recorded],
                                                      &warmup_frames);
        if (warmup_result < 0) return 64;
        if (warmup_result == 0) {
            if (script != NULL) return 64;
            script = arguments[recorded];
        }
    }
    total_frames = requested_frames + warmup_frames;
    if (total_frames < requested_frames || total_frames > 4200u ||
        (t26_fixture >= 35u && t26_fixture <= 52u && requested_frames != 1u)) return 64;
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
    elapsed = 0u;
    step_count = 0u;
    last_frame_revision = 0u;
    have_frame_revision = LIB_FALSE;
    if (!mysmb_reference_script_buttons(script, elapsed, total_frames,
                                        &buttons)) {
        fclose(output);
        (void)core_driver_destroy(driver);
        return 68;
    }
    mysmb_reference_apply_ram_write(&ram_write, elapsed, driver->machine->ram);
    core_controller_set_buttons(&driver->machine->controller, (lib_u8)buttons);
    while (recorded < requested_frames &&
           step_count < total_frames * MYSMB_REFERENCE_MAX_STEPS_PER_FRAME) {
        core_run_result result;
        lib_u16 before_pc;

        if (direct_warp_text && driver->machine->pc == 0x8001u) {
            if (!mysmb_reference_write_frame(output, driver->machine)) break;
            ++recorded;
            break;
        }
        /* Apply only at the next ordinary NMI entry.  A write at the prior
         * RTI boundary can legitimately be superseded by the ROM mainline
         * before NMI selects its buffer pointer. */
        if (t28_vram_pending &&
            driver->machine->pc == MYSMB_REFERENCE_NMI_ENTRY) {
            mysmb_reference_apply_t28_vram_fixture(driver->machine->ram,
                t26_fixture == 51u ? 0u : 1u);
            if (core_machine_breakpoint_set(driver->machine,
                MYSMB_REFERENCE_T28_VRAM_COMMAND_ENTRY, LIB_TRUE) !=
                LIB_STATUS_OK) break;
            t28_vram_pending = LIB_FALSE;
            t28_vram_phase = 1u;
        }
        /* S5 reaches this source label only after GameMode and
         * ScreenRoutines have selected InitScreen, both InitScreen calls
         * have returned, and the nonzero-mode SetVRAMAddr_A write is done.
         * It is a natural-route capture point, never an injected leaf PC. */
        if (t26_fixture == 50u &&
            driver->machine->pc == MYSMB_REFERENCE_T28_INIT_SCREEN_SUCCESSOR) {
            if (!mysmb_reference_write_frame(output, driver->machine)) break;
            ++recorded;
            break;
        }
        /* Stop on the actual packet entry, then replace that breakpoint with
         * InitScroll.  This brackets the full source packet without a leaf
         * jump or an invented caller stack. */
        if (t28_vram_phase == 1u &&
            driver->machine->pc == MYSMB_REFERENCE_T28_VRAM_COMMAND_ENTRY) {
            if (core_machine_breakpoint_set(driver->machine,
                MYSMB_REFERENCE_T28_VRAM_COMMAND_ENTRY, LIB_FALSE) !=
                LIB_STATUS_OK || core_machine_breakpoint_set(driver->machine,
                MYSMB_REFERENCE_T28_VRAM_EXIT, LIB_TRUE) != LIB_STATUS_OK) break;
            t28_vram_phase = 2u;
        }
        if (t28_vram_phase == 2u &&
            driver->machine->pc == MYSMB_REFERENCE_T28_VRAM_EXIT) {
            if (!mysmb_reference_write_frame(output, driver->machine)) break;
            ++recorded;
            break;
        }
        /* The packet is reached only through ordinary GameEngine dispatch.
         * Capture at its RTS instruction, before later object handlers can
         * alter the source RAM owned by their separate chains. */
        if (t29_area_entry_phase == 1u && driver->machine->pc == 0x9131u)
            t29_area_entry_phase = 2u;
        if (t29_area_entry_phase == 2u &&
            driver->machine->pc == MYSMB_REFERENCE_T29_AREA_ENTRY_RETURN) {
            if (!mysmb_reference_write_frame(output, driver->machine)) break;
            ++recorded;
            break;
        }

        if (driver->machine->pc == MYSMB_REFERENCE_NMI_RETURN) {
            /* Sample before RTI.  Stepping the RTI below clears this program
             * counter, so every subsequent return is independently visible.
             * The frame ordinal is an NMI-return sequence: two returns can
             * share a PPU revision yet have different RAM timer state.  PPU
             * revisions may also have gaps while NMI is masked; only a
             * regression invalidates the sequence. */
            if (have_frame_revision &&
                driver->machine->ppu.frame_revision < last_frame_revision) break;
            if (elapsed >= warmup_frames &&
                !mysmb_reference_write_frame(output, driver->machine)) break;
            last_frame_revision = driver->machine->ppu.frame_revision;
            have_frame_revision = LIB_TRUE;
            ++elapsed;
            if (elapsed > warmup_frames) ++recorded;
            if (recorded == requested_frames) break;
            mysmb_reference_apply_ram_write(&ram_write, elapsed,
                                             driver->machine->ram);
            if (elapsed == warmup_frames) {
                if (t26_fixture == 1u)
                    mysmb_reference_apply_t26_floatey_fixture(driver->machine->ram);
                else if (t26_fixture == 2u)
                    mysmb_reference_apply_t26_endworld_b_fixture(driver->machine->ram);
                else if (t26_fixture == 3u)
                    mysmb_reference_apply_t26_victory_message_fixture(
                        driver->machine->ram, 0u, 0u, 0u, 0u);
                else if (t26_fixture == 4u)
                    mysmb_reference_apply_t26_victory_message_fixture(
                        driver->machine->ram, 3u, 0u, 0u, 7u);
                else if (t26_fixture == 5u)
                    mysmb_reference_apply_t26_victory_message_fixture(
                        driver->machine->ram, 4u, 0u, 0u, 0u);
                else if (t26_fixture == 6u)
                    mysmb_reference_apply_t26_victory_walk_fixture(
                        driver->machine->ram, 0u);
                else if (t26_fixture == 7u)
                    mysmb_reference_apply_t26_victory_walk_fixture(
                        driver->machine->ram, 1u);
                else if (t26_fixture == 8u)
                    mysmb_reference_apply_t26_victory_walk_fixture(
                        driver->machine->ram, 2u);
                else if (t26_fixture == 9u)
                    mysmb_reference_apply_t26_endworld_next_fixture(
                        driver->machine->ram);
                else if (t26_fixture == 10u)
                    mysmb_reference_apply_t26_victory_bridge_handoff_fixture(
                        driver->machine->ram);
                else if (t26_fixture == 11u)
                    mysmb_reference_apply_t26_victory_message_fixture(
                        driver->machine->ram, 0u, 0u, 1u, 0u);
                else if (t26_fixture == 12u)
                    mysmb_reference_apply_t26_victory_message_fixture(
                        driver->machine->ram, 2u, 0u, 0u, 0u);
                else if (t26_fixture == 13u)
                    mysmb_reference_apply_t26_victory_message_fixture(
                        driver->machine->ram, 2u, 4u, 0u, 0u);
                else if (t26_fixture == 14u)
                    mysmb_reference_apply_t26_endworld_return_fixture(
                        driver->machine->ram, 0u);
                else if (t26_fixture == 15u)
                    mysmb_reference_apply_t26_endworld_return_fixture(
                        driver->machine->ram, 1u);
                else if (t26_fixture == 16u)
                    mysmb_reference_apply_t26_floatey_leaf_fixture(
                        driver->machine->ram, 0u);
                else if (t26_fixture == 17u)
                    mysmb_reference_apply_t26_floatey_leaf_fixture(
                        driver->machine->ram, 1u);
                else if (t26_fixture == 18u)
                    mysmb_reference_apply_t26_victory_outer_player_fixture(
                        driver->machine->ram);
                else if (t26_fixture >= 19u && t26_fixture <= 34u)
                    mysmb_reference_apply_t27_screen_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 19u));
                else if (t26_fixture == 50u)
                {
                    mysmb_reference_apply_t28_init_screen_fixture(
                        driver->machine->ram);
                    if (core_machine_breakpoint_set(driver->machine,
                        MYSMB_REFERENCE_T28_INIT_SCREEN_SUCCESSOR,
                        LIB_TRUE) != LIB_STATUS_OK) break;
                }
                else if (t26_fixture == 51u || t26_fixture == 52u) {
                    t28_vram_pending = LIB_TRUE;
                    if (core_machine_breakpoint_set(driver->machine,
                        MYSMB_REFERENCE_NMI_ENTRY, LIB_TRUE) !=
                        LIB_STATUS_OK) break;
                }
                else if (t26_fixture == 53u)
                    mysmb_reference_apply_t28_status_timer_fixture(
                        driver->machine->ram);
                else if (t26_fixture == 54u)
                    mysmb_reference_apply_t28_status_timer_borrow_fixture(
                        driver->machine->ram);
                else if (t26_fixture == 55u)
                    mysmb_reference_apply_t28_top_score_fixture(
                        driver->machine->ram, 1u);
                else if (t26_fixture == 56u)
                    mysmb_reference_apply_t28_top_score_fixture(
                        driver->machine->ram, 0u);
                else if (t26_fixture == 57u)
                    mysmb_reference_apply_t28_title_score_fixture(
                        driver->machine->ram);
                else if (t26_fixture == 58u)
                    mysmb_reference_apply_t28_area_entry_fixture(
                        driver->machine->ram);
                else if (t26_fixture == 59u)
                    mysmb_reference_apply_t28_secondary_setup_fixture(
                        driver->machine->ram);
                else if (t26_fixture >= 60u && t26_fixture <= 63u)
                    mysmb_reference_apply_t29_area_music_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 60u));
                else if (t26_fixture >= 64u && t26_fixture <= 67u)
                {
                    mysmb_reference_apply_t29_area_entry_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 64u));
                    /* The driver already exposes each instruction boundary.
                     * Do not install a global breakpoint here: an older visit
                     * to this RTS during warmup would prevent ordinary
                     * GameEngine dispatch from reaching this fixture. */
                    t29_area_entry_phase = 1u;
                }
                else if (t26_fixture >= 68u && t26_fixture <= 73u)
                    mysmb_reference_apply_t29_life_mode_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 68u));
                else if (t26_fixture == 74u)
                    mysmb_reference_apply_t29_parser_dispatch_fixture(
                        driver->machine->ram);
                else if (t26_fixture == 75u)
                    mysmb_reference_apply_t29_special_object_fixture(
                        driver->machine->ram);
                else if (t26_fixture >= 35u && t26_fixture <= 37u) {
                    driver->machine->ram[0x0300u] = 0u;
                    driver->machine->ram[0x06d6u] = (lib_u8)(t26_fixture - 31u);
                    /* RenderAreaGraphics returns through SetVRAMCtrl.  The
                     * original parser caller immediately enters the separate
                     * RenderAttributeTables routine, so model that two-call
                     * stack rather than treating either leaf in isolation. */
                    driver->machine->ram[0x01feu] = 0x69u;
                    driver->machine->ram[0x01ffu] = 0x89u;
                    driver->machine->ram[0x0100u] = 0u;
                    driver->machine->ram[0x0101u] = 0x80u;
                    driver->machine->a = (lib_u8)(t26_fixture - 31u);
                    driver->machine->s = 0xfdu;
                    driver->machine->pc = 0x8808u;
                    direct_warp_text = LIB_TRUE;
                }
                else if (t26_fixture >= 38u && t26_fixture <= 39u) {
                    static const lib_u8 metatiles[13] = {
                        0x00u, 0x41u, 0x82u, 0xc3u, 0x04u, 0x45u, 0x86u,
                        0xc7u, 0x08u, 0x49u, 0x8au, 0xcbu, 0x0cu
                    };
                    lib_u8 row;
                    driver->machine->ram[0x0340u] = 0u;
                    driver->machine->ram[0x071fu] = t26_fixture == 38u ? 0u : 1u;
                    driver->machine->ram[0x0726u] = t26_fixture == 38u ? 0u : 1u;
                    driver->machine->ram[0x0720u] = 0x20u;
                    driver->machine->ram[0x0721u] = 0x9fu;
                    for (row = 0u; row < 13u; ++row)
                        driver->machine->ram[0x06a1u + row] = metatiles[row];
                    driver->machine->ram[0x01feu] = 0u;
                    driver->machine->ram[0x01ffu] = 0x80u;
                    driver->machine->s = 0xfdu;
                    driver->machine->pc = 0x88aeu;
                    direct_warp_text = LIB_TRUE;
                }
                else if (t26_fixture >= 40u && t26_fixture <= 41u) {
                    static const lib_u8 left[7] = { 0x10u, 0x32u, 0x10u, 0x32u, 0x10u, 0x32u, 0u };
                    static const lib_u8 right[7] = { 0x40u, 0xc8u, 0x40u, 0xc8u, 0x40u, 0xc8u, 0u };
                    lib_u8 row;
                    driver->machine->ram[0x0340u] = 29u;
                    driver->machine->ram[0x0720u] = 0x24u;
                    driver->machine->ram[0x0721u] = 0x80u;
                    for (row = 0u; row < 7u; ++row)
                        driver->machine->ram[0x03f9u + row] =
                            (t26_fixture == 40u ? left : right)[row];
                    driver->machine->ram[0x01feu] = 0u;
                    driver->machine->ram[0x01ffu] = 0x80u;
                    driver->machine->s = 0xfdu;
                    driver->machine->pc = 0x896au;
                    direct_warp_text = LIB_TRUE;
                }
                else if (t26_fixture >= 42u && t26_fixture <= 45u) {
                    driver->machine->ram[0x0009u] = t26_fixture == 44u ? 1u : 0u;
                    driver->machine->ram[0x0300u] = t26_fixture == 45u ? 0x31u :
                        (t26_fixture == 44u ? 7u : 0u);
                    driver->machine->ram[0x074eu] = t26_fixture == 42u ? 1u : 3u;
                    driver->machine->ram[0x06d4u] = t26_fixture == 42u ? 0u :
                        (t26_fixture == 43u ? 5u : 2u);
                    driver->machine->ram[0x01feu] = 0u;
                    driver->machine->ram[0x01ffu] = 0x80u;
                    driver->machine->s = 0xfdu;
                    driver->machine->pc = 0x89e1u;
                    direct_warp_text = LIB_TRUE;
                }
                else if (t26_fixture >= 46u && t26_fixture <= 47u) {
                    driver->machine->ram[0x0002u] = 0x20u;
                    driver->machine->ram[0x0006u] = t26_fixture == 46u ? 0xd2u : 0x04u;
                    driver->machine->ram[0x0007u] = 0x05u;
                    driver->machine->ram[0x074eu] = t26_fixture == 46u ? 0u : 1u;
                    driver->machine->ram[0x0300u] = 0u;
                    driver->machine->a = t26_fixture == 46u ? 0u : 0x51u;
                    driver->machine->x = 0u;
                    driver->machine->ram[0x01feu] = 0u;
                    driver->machine->ram[0x01ffu] = 0x80u;
                    driver->machine->s = 0xfdu;
                    driver->machine->pc = t26_fixture == 46u ? 0x8a4du : 0x8a6du;
                    direct_warp_text = LIB_TRUE;
                }
                else if (t26_fixture == 48u) {
                    driver->machine->ram[0x0000u] = 3u;
                    driver->machine->ram[0x0004u] = 0x58u;
                    driver->machine->ram[0x0005u] = 0x22u;
                    driver->machine->ram[0x0300u] = 0u;
                    driver->machine->x = 12u;
                    driver->machine->y = 1u;
                    driver->machine->ram[0x01feu] = 0u;
                    driver->machine->ram[0x01ffu] = 0x80u;
                    driver->machine->s = 0xfdu;
                    driver->machine->pc = 0x8acdu;
                    direct_warp_text = LIB_TRUE;
                }
                else if (t26_fixture == 49u) {
                    driver->machine->ram[0x0002u] = 0x20u;
                    driver->machine->ram[0x0006u] = 0xd2u;
                    driver->machine->ram[0x0007u] = 0x05u;
                    driver->machine->ram[0x0300u] = 0u;
                    driver->machine->x = 0u;
                    driver->machine->ram[0x01feu] = 0u;
                    driver->machine->ram[0x01ffu] = 0x80u;
                    driver->machine->s = 0xfdu;
                    driver->machine->pc = 0x8a6bu;
                    direct_warp_text = LIB_TRUE;
                }
            }
            if (!mysmb_reference_script_buttons(script, elapsed, total_frames,
                                                &buttons)) break;
            core_controller_set_buttons(&driver->machine->controller, (lib_u8)buttons);
        }
        before_pc = driver->machine->pc;
        if (core_machine_debug_step(driver->machine, 1u, 1024u, &result) !=
            LIB_STATUS_OK || result.trap_valid) break;
        if (coverage_path != NULL && elapsed >= warmup_frames &&
            before_pc >= 0x8000u) {
            unsigned int offset = before_pc - 0x8000u;
            ++mysmb_pc_hits[offset];
            if (driver->machine->pc == (lib_u16)(before_pc + 2u))
                ++mysmb_pc_fallthrough2[offset];
            else
                ++mysmb_pc_other[offset];
        }
        ++step_count;
    }
    fclose(output);
    (void)core_driver_destroy(driver);
    if (recorded != requested_frames) return 68;
    return mysmb_reference_write_coverage(coverage_path) ? 0 : 69;
}
