/*
 * Owner-local reference recorder for M2 T9.  This source is compiled only
 * against a local nnes checkout; it is never part of the MySMB product.
 * Records are raw owner-ROM traces and must remain beneath an ignored output
 * directory.  Sampling occurs when SMB1 reaches the NMI RTI at $8181.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../test/castle_column_fixture.h"
#include "../test/block_row_column_fixture.h"
#include "../test/cannon_fixture.h"
#include "../test/staircase_fixture.h"
#include "../test/jumpspring_fixture.h"
#include "../test/item_block_fixture.h"
#include "../test/hole_underpart_fixture.h"
#include "../test/area_helper_fixture.h"
#include "../test/parser_boundary_fixture.h"
#include "../test/pipe_tail_fixture.h"
#include "../test/block_address_fixture.h"
#include "../test/area_pointer_fixture.h"
#include "../test/castle_scene_fixture.h"
#include "../test/ground_scene_fixture.h"
#include "../test/underground_scene_fixture.h"
#include "../test/water_scene_fixture.h"
#include "../test/game_entry_fixture.h"
#include "../test/engine_tail_fixture.h"
#include "../test/engine_slots_fixture.h"
#include "../test/engine_environment_fixture.h"
#include "../test/engine_warp_fixture.h"
#include "../test/engine_normal_fixture.h"
#include "../test/scroll_fixture.h"
#include "../test/entrance_fixture.h"
#include "../test/player_control_fixture.h"
#include "../test/player_transition_fixture.h"
#include "../test/player_modes_fixture.h"
#include "../test/player_end_level_fixture.h"
#include "../test/player_movement_fixture.h"
#include "../test/fireball_dispatch_fixture.h"
#include "../test/fireball_core_fixture.h"
#include "../test/bubble_core_fixture.h"
#include "../test/timer_fixture.h"
#include "../test/jumpspring_core_fixture.h"
#include "../test/vine_setup_fixture.h"
#include "../test/vine_actor_fixture.h"
#include "../test/hammer_chain_fixture.h"
#include "../test/coin_allocation_fixture.h"
#include "../test/score_hud_fixture.h"
#include "../test/power_up_init_fixture.h"
#include "../test/power_up_actor_fixture.h"
#include "../test/block_head_fixture.h"
#include "../test/block_bump_fixture.h"
#include "../test/block_chunks_fixture.h"
#include "../test/block_lifetime_fixture.h"
#include "../test/block_replacement_fixture.h"
#include "../test/horizontal_fixture.h"
#include "../test/vertical_fixture.h"
#include "../test/gravity_fixture.h"
#include "../test/enemy_loop_fixture.h"
#include "../test/enemy_stream_fixture.h"
#include "../test/enemy_init_fixture.h"
#include "../test/lakitu_spiny_fixture.h"
#include "../test/flying_fish_fixture.h"
#include "../test/bowser_flame_fixture.h"
#include "../test/fireworks_fixture.h"
#include "../test/bullet_swimming_fish_fixture.h"
#include "../test/group_enemy_fixture.h"
#include "../test/small_initializers_fixture.h"
#include "../test/platform_initialization_fixture.h"
#include "../test/actor_dispatch_fixture.h"
#include "../test/normal_actor_fixture.h"
#include "../test/special_actor_fixture.h"
#include "../test/large_platform_graphics_fixture.h"
#include "../test/podoboo_movement_fixture.h"
#include "../test/hammer_movement_fixture.h"
#include "../test/paratroopa_movement_fixture.h"
#include "../test/green_counter_fixture.h"
#include "../test/bloober_movement_fixture.h"
#include "../test/bullet_movement_fixture.h"
#include "../test/swimming_cheep_movement_fixture.h"
#include "../test/firebar_chain_fixture.h"
#include "../test/flying_cheep_movement_fixture.h"
#include "../test/lakitu_movement_fixture.h"
#include "../test/bridge_collapse_fixture.h"
#include "../test/bowser_control_fixture.h"
#include "../test/bowser_graphics_fixture.h"
#include "../test/flame_actor_fixture.h"
#include "../test/fireworks_lifetime_fixture.h"
#include "../test/star_flag_fixture.h"
#include "../test/piranha_movement_fixture.h"
#include "../test/balance_platform_fixture.h"
#include "../test/vertical_platform_fixture.h"
#include "../test/horizontal_platform_fixture.h"
#include "../test/lift_platform_fixture.h"
#include "../test/offscreen_bounds_fixture.h"
#include "../test/fireball_enemy_scan_fixture.h"
#include "../test/fireball_hit_fixture.h"
#include "../test/hammer_contact_fixture.h"
#include "../test/powerup_pickup_fixture.h"
#include "../test/platform_position_fixture.h"
#include "../test/terrain_metatile_fixture.h"
#include "../test/climbing_fixture.h"
#include "../test/pipe_entry_fixture.h"
#include "../test/impede_fixture.h"
#include "reference_metatile_observer.h"
#include "../test/enemy_background_fixture.h"
#include "../test/enemy_landing_fixture.h"
#include "reference_enemy_background_observer.h"
#include "../test/platform_collision_fixture.h"
#include "../test/enemy_pair_fixture.h"
#include "../test/player_enemy_contact_fixture.h"
#include "../test/misc_lifetime_fixture.h"
#include "../test/engine_cannon_fixture.h"

#include "core/driver.h"
#include "core/machine.h"

#define MYSMB_REFERENCE_NMI_RETURN 0x8181u
#define MYSMB_REFERENCE_NMI_ENTRY 0x8085u
/* Source $8175 is the ordinary SkipSprite0 JSR OperModeExecutionTree.
 * Capturing at this instruction preserves the NMI's just-written physical
 * $2000 state, before mode logic can alter the mirror for a later frame. */
#define MYSMB_REFERENCE_NMI_DISPATCH 0x8175u
#define MYSMB_REFERENCE_T28_INIT_SCREEN_SUCCESSOR 0x85c8u
#define MYSMB_REFERENCE_T28_VRAM_COMMAND_ENTRY 0x8e92u
#define MYSMB_REFERENCE_T28_VRAM_EXIT 0x8ee6u
#define MYSMB_REFERENCE_T29_AREA_ENTRY_RETURN 0x919eu
#define MYSMB_REFERENCE_T52_OUTPUT_INTER_RETURN 0x86d2u
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
static unsigned long mysmb_area_read_hits[32768];
static unsigned long mysmb_player_table_reads[208];
static unsigned long mysmb_player_offset_reads[16];
static unsigned long mysmb_swim_kick_reads[2];

static int mysmb_reference_write_area_reads(const char *path)
{
    FILE *output;
    unsigned int offset;
    int ok;
    if (path == NULL) return 1;
    output = fopen(path, "w");
    if (output == NULL) return 0;
    ok = fprintf(output, "address,reads\n") >= 0;
    for (offset = 0u; offset < 32768u && ok; ++offset)
        if (mysmb_area_read_hits[offset] != 0ul)
            ok = fprintf(output, "%04x,%lu\n", offset + 0x8000u,
                         mysmb_area_read_hits[offset]) >= 0;
    if (fclose(output) != 0) ok = 0;
    return ok;
}

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
    ram[0x0302u] = kind == 0u ? 0x00u : 0x10u;
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
    /* ParserCore reaches ProcessAreaData on its core slots.  Keep the
     * controlled dispatch source-reachable by retaining the reset-selected
     * real post-header GroundArea stream, rather than leaving the title-mode
     * area pointer.
     * This changes RAM only at the normal NMI boundary. */
    ram[0x00e7u] = 0x90u;
    ram[0x00e8u] = 0xa6u;
    ram[0x074eu] = 1u;
    ram[0x075fu] = 0u;
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

/* T29/S9 selects the first ordinary large object in L_GroundArea1
 * (CPU $a46d: $0f,$26, CastleObject).  This is an NMI-boundary state for
 * the normal GameEngine parser tail: it supplies the post-header area-data
 * address and lets ProcessAreaData fill slot two before RunAObj dispatches
 * the castle chain. */
static void mysmb_reference_apply_t29_geometry_castle_fixture(lib_u8 *ram)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 3u;
    ram[0x000eu] = 8u;
    ram[0x0773u] = 0u;
    ram[0x071fu] = 8u;
    ram[0x0725u] = 0u;
    ram[0x0726u] = 0u;
    ram[0x0728u] = 0u;
    ram[0x072au] = 0u;
    ram[0x072bu] = 0u;
    ram[0x072cu] = 2u;
    ram[0x072du] = 0u;
    ram[0x072eu] = 0u;
    ram[0x072fu] = 0u;
    ram[0x0730u] = 0xffu;
    ram[0x0731u] = 0xffu;
    ram[0x0732u] = 0xffu;
    ram[0x073fu] = 0u;
    ram[0x00e7u] = 0x6bu;
    ram[0x00e8u] = 0xa4u;
}

/* T22/S5 selects the original L_GroundArea3 flagpole ($1d,$c1 at $a585).
 * The area pointer is two bytes before that pair, exactly as the normal parser
 * consumes AreaDataOffset 2.  The first byte's column is one; $c1 first
 * advances object page 13 to 14, then row-13/d6 dispatches FlagpoleObject. */
static void mysmb_reference_apply_t22_flagpole_fixture(lib_u8 *ram)
{
    mysmb_reference_apply_t29_geometry_castle_fixture(ram);
    ram[0x0725u] = 14u;
    ram[0x0726u] = 1u;
    ram[0x072au] = 13u;
    ram[0x072bu] = 0u;
    ram[0x072cu] = 2u;
    ram[0x00e7u] = 0x83u;
    ram[0x00e8u] = 0xa5u;
}

/* The second frame of the same normal parser route selects FlagpoleRoutine's
 * GiveFPScr branch after the first frame has created slot five. */
static void mysmb_reference_apply_t22_flagpole_score_fixture(lib_u8 *ram)
{
    ram[0x000eu] = 4u;
    ram[0x001du] = 3u;
    ram[0x00cfu + 5u] = 0xaau;
    ram[0x010fu] = 2u;
    ram[0x0753u] = 0u;
    ram[0x0716u] = 1u;
}

/* The original 1-1 stream has VerticalPipe $68,$f2 at CPU $a69c.  Its page
 * bit advances the object page from zero to the already-current page one. */
static void mysmb_reference_apply_t29_geometry_vertical_pipe_fixture(lib_u8 *ram)
{
    mysmb_reference_apply_t29_geometry_castle_fixture(ram);
    ram[0x0725u] = 1u;
    ram[0x0726u] = 6u;
    ram[0x072au] = 0u;
    ram[0x072bu] = 0u;
    ram[0x072cu] = 0x0eu;
    ram[0x00e7u] = 0x8eu;
    ram[0x00e8u] = 0xa6u;
    ram[0x0760u] = 1u;
}

/* L_GroundArea3 contains the original $4c,$63 QuestionBlockRow_High pair.
 * The fixture selects that resident area-stream object at an NMI boundary;
 * GameEngine remains responsible for ProcessAreaData, RunAObj and JumpEngine. */
static void mysmb_reference_apply_t29_final_question_fixture(lib_u8 *ram)
{
    mysmb_reference_apply_t29_geometry_castle_fixture(ram);
    ram[0x0726u] = 4u;
    ram[0x072cu] = 0x32u;
    ram[0x00e7u] = 0x37u;
    ram[0x00e8u] = 0xa5u;
}

/* T29/S8 additional real area-stream objects.  Each variant remains at a
 * normal NMI return and lets GameEngine dispatch the ROM parser; only the
 * already-reached stream cursor/page/column state differs. */
static void mysmb_reference_apply_t29_special_chain_fixture(lib_u8 *ram,
                                                             lib_u8 kind)
{
    mysmb_reference_apply_t29_special_object_fixture(ram);
    if (kind == 0u) { /* L_GroundArea3 +$4a: $ed,$4a, frenzy selector 10. */
        ram[0x00e7u] = 0x39u; ram[0x00e8u] = 0xa5u;
        ram[0x072cu] = 0x4au; ram[0x0725u] = 13u;
        ram[0x0726u] = 14u; ram[0x072au] = 13u;
    }
    else if (kind == 1u) { /* L_GroundArea13 +$1c: $1c,$17, pulley. */
        ram[0x00e7u] = 0x91u; ram[0x00e8u] = 0xa8u;
        ram[0x072cu] = 0x1cu; ram[0x0725u] = 3u;
        ram[0x0726u] = 1u; ram[0x072au] = 3u;
    }
    else { /* L_GroundArea13 +$06: $33,$14, tree-style object. */
        ram[0x00e7u] = 0x91u; ram[0x00e8u] = 0xa8u;
        ram[0x072cu] = 6u; ram[0x0725u] = 1u;
        ram[0x0726u] = 3u; ram[0x072au] = 1u;
        ram[0x0733u] = 0u;
    }
}

/* P4 continues genuine S8 objects through ProcessAreaData's resident slot
 * rather than jumping into a special-object leaf.  These are the exact RAM
 * fields left by the preceding parser column: slot two remains resident,
 * its saved source offset points at the original pair, and its non-negative
 * length selects RunAObj. */
static void mysmb_reference_apply_t29_special_continuation_fixture(
    lib_u8 *ram, lib_u8 kind)
{
    mysmb_reference_apply_t29_special_object_fixture(ram);
    if (kind == 0u) { /* Frenzy's existing-ID outcome. */
        mysmb_reference_apply_t29_special_chain_fixture(ram, 0u);
        ram[0x001au] = 0x18u;
        return;
    }
    ram[0x00e7u] = 0x91u;
    ram[0x00e8u] = 0xa8u;
    ram[0x0725u] = kind <= 2u ? 3u : 1u;
    ram[0x0726u] = kind <= 2u ? 1u : 3u;
    ram[0x072au] = ram[0x0725u];
    ram[0x072cu] = kind <= 2u ? 0x1eu : (kind == 3u ? 0x06u : 0x08u);
    ram[0x072fu] = kind <= 2u ? 0x1cu : 0x06u;
    ram[0x0730u] = 0xffu;
    ram[0x0731u] = 0xffu;
    ram[0x0732u] = kind == 1u ? 1u :
        (kind == 3u ? 0xffu : (kind == 4u ? 2u : 0u));
    ram[0x0733u] = kind >= 3u && kind <= 5u ? 1u : 0u;
    if (kind == 4u) ram[0x0736u] = 2u;
}

static void mysmb_reference_apply_t29_warp_selector_fixture(lib_u8 *ram,
                                                             lib_u8 kind)
{
    mysmb_reference_apply_t29_special_object_fixture(ram);
    if (kind == 0u) {
        ram[0x000fu] = 1u;
        ram[0x0016u] = 13u;
    }
    else if (kind == 1u) {
        ram[0x075fu] = 1u;
        ram[0x074eu] = 1u;
    }
    else if (kind == 2u) {
        ram[0x075fu] = 1u;
        ram[0x074eu] = 2u;
    }
    else {
        ram[0x075fu] = 0u;
        ram[0x074eu] = 2u;
    }
}

static void mysmb_reference_apply_t28_title_score_fixture(lib_u8 *ram)
{
    ram[0x0770u] = 0u;
    ram[0x0772u] = 1u;
    ram[0x073cu] = 14u;
}

/* T54/S3 mirrors the native recorder's NMI-boundary task-12/13 state.  It
 * does not redirect PC or stack state; the ordinary title dispatcher calls
 * the source ScreenRoutines task. */
static void mysmb_reference_apply_t54_title_task_fixture(lib_u8 *ram,
                                                          lib_u8 task)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 0u;
    ram[0x0772u] = 1u;
    ram[0x073cu] = task;
}

/* T52/S2 sets only the ordinary title-menu RAM state at an NMI return.  The
 * next ROM NMI reaches GameMenuRoutine through TitleScreenMode; no PC or
 * stack is redirected.  This distinguishes ChkSelect's expired-demo path
 * from the nonzero-DemoTimer ChkWorldSel path. */
static void mysmb_reference_apply_t52_title_menu_fixture(lib_u8 *ram,
                                                          lib_u8 demo_timer)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 0u;
    ram[0x0772u] = 3u;
    ram[0x07a2u] = demo_timer;
    ram[0x07fcu] = 1u;
    ram[0x076bu] = 4u;
    ram[0x075fu] = 4u;
    ram[0x0780u] = 0u;
    ram[0x06fcu] = 0x02u;
    ram[0x06fdu] = 0u;
}

/* T52/S4 enters only through the ordinary GameMode/ScreenRoutines dispatch
 * after placing the original task-ten palette precondition at an NMI return. */
static void mysmb_reference_apply_t52_background_palette_fixture(lib_u8 *ram,
                                                                  lib_u8 background_control)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 1u;
    ram[0x073cu] = 10u;
    ram[0x0744u] = background_control;
    ram[0x074eu] = 1u;
    ram[0x0753u] = 0u;
    ram[0x0756u] = 1u;
    ram[0x0773u] = 0u;
    ram[0x0300u] = 0u;
}

/* T54/S1 exercises GetAreaPalette through every source AreaType table entry.
 * The ordinary title-mode ScreenRoutines dispatcher remains the caller. */
static void mysmb_reference_apply_t54_area_palette_fixture(lib_u8 *ram,
                                                            lib_u8 area_type)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 1u;
    ram[0x073cu] = 9u;
    ram[0x074eu] = area_type;
}

static void mysmb_reference_apply_t54_player_palette_fixture(lib_u8 *ram,
                                                              lib_u8 player,
                                                              lib_u8 status)
{
    mysmb_reference_apply_t52_background_palette_fixture(ram, 0u);
    ram[0x0753u] = player;
    ram[0x0756u] = status;
}

static void mysmb_reference_apply_t54_alternate_palette_fixture(lib_u8 *ram,
                                                                 lib_u8 area_style)
{
    ram[0x0722u] = 0u;
    ram[0x0770u] = 1u;
    ram[0x0772u] = 1u;
    ram[0x073cu] = 11u;
    ram[0x0733u] = area_style;
    ram[0x0773u] = 0x66u;
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
    int block_scenario;
    const char *script;
    const char *coverage_path;
    const char *area_reads_path;
    const char *player_table_reads_path;
    const char *player_offset_reads_path;
    const char *metatile_path = NULL;
    const char *enemy_background_path = NULL;
    const char *enemy_landing_path = NULL;
    const char *movement_snapshot_path;
    unsigned char movement_snapshots[4096];
    unsigned int movement_snapshot_phase;
    unsigned int background_snapshot;
    const char *entrance_children_path;
    unsigned char entrance_children[64][4098];
    const char *player_action_child_path;
    unsigned char player_action_children[8][4098];
    unsigned int player_action_child_count;
    unsigned int player_action_child_active;
    lib_u16 player_action_child_return;
    lib_u8 player_action_child_stack;
    const char *player_size_child_path;
    unsigned char player_size_children[8][4098];
    unsigned int player_size_child_count;
    unsigned int player_size_child_active;
    lib_u16 player_size_child_return;
    lib_u8 player_size_child_stack;
    const char *relative_child_path;
    unsigned char relative_children[8][4100];
    unsigned int relative_child_count;
    unsigned int relative_child_active;
    unsigned int relative_kind;
    char *relative_kind_end;
    unsigned int relative_coordinate_variant;
    char *relative_coordinate_variant_end;
    lib_u16 relative_child_entry;
    lib_u16 relative_child_return;
    lib_u8 relative_child_stack;
    const char *sprite_row_child_path;
    unsigned char sprite_row_children[8][4100];
    unsigned int sprite_row_child_count;
    unsigned int sprite_row_child_active;
    lib_u16 sprite_row_child_return;
    lib_u8 sprite_row_child_stack;
    unsigned int sprite_row_flip_variant;
    const char *sound_child_path;
    unsigned char sound_children[8][4144];
    unsigned int sound_child_count;
    unsigned int sound_child_active;
    lib_u16 sound_child_return;
    lib_u8 sound_child_stack;
    unsigned int sound_case;
    const char *sound_helper_path;
    unsigned char sound_helpers[128][58];
    unsigned int sound_helper_count;
    unsigned int sound_helper_active[9];
    unsigned int sound_helper_record[9];
    lib_u16 sound_helper_return[9];
    lib_u8 sound_helper_stack[9];
    const lib_u16 sound_helper_pc[9] = {
        0xf381u, 0xf388u, 0xf38bu, 0xf38du, 0xf39eu,
        0xf39fu, 0xf3a6u, 0xf3a9u, 0xf3adu
    };
    lib_u16 control_return;
    lib_u8 control_stack;
    lib_u16 transition_entry;
    lib_u8 transition_argument;
    lib_u8 vine_block_slot;
    lib_u8 hammer_return_carry;
    lib_u8 coin_entry_carry;
    unsigned int entrance_child_count;
    unsigned int entrance_child_active;
    lib_u16 entrance_child_return;
    lib_u8 entrance_child_stack;
    struct mysmb_reference_ram_write ram_write;
    unsigned int t26_fixture;
    unsigned int screen_dispatch_task;
    unsigned int enemy_graphics_variant;
    char *enemy_graphics_variant_end;
    unsigned int block_graphics_variant;
    char *block_graphics_variant_end;
    unsigned int projectile_frame;
    char *projectile_frame_end;
    unsigned int small_platform_variant;
    char *small_platform_variant_end;
    unsigned int bubble_player_variant;
    char *bubble_player_variant_end;
    unsigned int bubble_draw_variant;
    char *bubble_draw_variant_end;
    unsigned int player_table_variant;
    char *player_table_variant_end;
    unsigned int player_action_variant;
    char *player_action_variant_end;
    unsigned int player_size_variant;
    char *player_size_variant_end;
    unsigned int player_attribute_variant;
    char *player_attribute_variant_end;
    unsigned int player_control_variant;
    char *player_control_variant_end;
    unsigned int intermediate_player_variant;
    char *intermediate_player_variant_end;
    lib_bool direct_warp_text;
    lib_bool direct_screen_dispatch;
    lib_bool screen_dispatch_pending;
    lib_bool capture_nmi_dispatch;
    lib_bool t28_vram_pending;
    lib_bool t29_vertical_pipe_pending;
    lib_bool t22_flagpole_score_pending;
    lib_bool t52_timeup_output_inter_probe;
    lib_u8 t28_vram_phase;
    lib_u8 t29_area_entry_phase;
    lib_u32 last_frame_revision;
    lib_bool have_frame_revision;
    unsigned int buttons;
    const unsigned char magic[8] = { 'M', 'S', 'F', 'R', 2u, 0u, 0u, 0u };

    if (argument_count < 5 || argument_count > 12) return 64;
    parsed_frames = strtoul(arguments[3], LIB_NULL, 10);
    buttons = (unsigned int)strtoul(arguments[4], LIB_NULL, 0);
    if (parsed_frames == 0u || parsed_frames > 600u || buttons > 0xffu)
        return 64;
    requested_frames = (lib_u32)parsed_frames;
    warmup_frames = 0u;
    script = NULL;
    coverage_path = NULL;
    area_reads_path = NULL;
    player_table_reads_path = NULL;
    player_offset_reads_path = NULL;
    movement_snapshot_path = NULL;
    movement_snapshot_phase = 0u;
    background_snapshot = 0u;
    entrance_children_path = NULL;
    entrance_child_count = 0u;
    entrance_child_active = 0u;
    entrance_child_return = 0u;
    entrance_child_stack = 0u;
    player_action_child_path = NULL;
    player_action_child_count = 0u;
    player_action_child_active = 0u;
    player_action_child_return = 0u;
    player_action_child_stack = 0u;
    player_size_child_path = NULL;
    player_size_child_count = 0u;
    player_size_child_active = 0u;
    player_size_child_return = 0u;
    player_size_child_stack = 0u;
    relative_child_path = NULL;
    relative_child_count = 0u;
    relative_child_active = 0u;
    relative_kind = 0xffffffffu;
    relative_coordinate_variant = 0xffffffffu;
    relative_child_entry = 0u;
    relative_child_return = 0u;
    relative_child_stack = 0u;
    sprite_row_child_path = NULL;
    sprite_row_child_count = 0u;
    sprite_row_child_active = 0u;
    sprite_row_child_return = 0u;
    sprite_row_child_stack = 0u;
    sprite_row_flip_variant = 0u;
    sound_child_path = NULL;
    sound_child_count = 0u;
    sound_child_active = 0u;
    sound_child_return = 0u;
    sound_child_stack = 0u;
    sound_case = 0u;
    sound_helper_path = NULL;
    sound_helper_count = 0u;
    memset(sound_helper_active, 0, sizeof(sound_helper_active));
    control_return = 0u;
    control_stack = 0u;
    transition_entry = 0u;
    transition_argument = 0u;
    vine_block_slot = 0u;
    hammer_return_carry = 0u;
    coin_entry_carry = 0u;
    ram_write.present = LIB_FALSE;
    t26_fixture = 0u;
    screen_dispatch_task = 0xffffffffu;
    enemy_graphics_variant = 0xffffffffu;
    block_graphics_variant = 0xffffffffu;
    projectile_frame = 0xffffffffu;
    small_platform_variant = 0xffffffffu;
    bubble_player_variant = 0xffffffffu;
    bubble_draw_variant = 0xffffffffu;
    player_table_variant = 0xffffffffu;
    player_action_variant = 0xffffffffu;
    player_size_variant = 0xffffffffu;
    player_attribute_variant = 0xffffffffu;
    player_control_variant = 0xffffffffu;
    intermediate_player_variant = 0xffffffffu;
    direct_warp_text = LIB_FALSE;
    direct_screen_dispatch = LIB_FALSE;
    screen_dispatch_pending = LIB_FALSE;
    capture_nmi_dispatch = LIB_FALSE;
    t28_vram_pending = LIB_FALSE;
    t29_vertical_pipe_pending = LIB_FALSE;
    t22_flagpole_score_pending = LIB_FALSE;
    t52_timeup_output_inter_probe = LIB_FALSE;
    t28_vram_phase = 0u;
    t29_area_entry_phase = 0u;
    for (recorded = 5u; recorded < (lib_u32)argument_count; ++recorded) {
        if (strncmp(arguments[recorded], "--screen-task=", 14u) == 0) {
            if (screen_dispatch_task != 0xffffffffu) return 64;
            screen_dispatch_task = (unsigned int)strtoul(arguments[recorded] + 14,
                                                          LIB_NULL, 10);
            if (screen_dispatch_task > 14u) return 64;
            continue;
        }
        if (strcmp(arguments[recorded], "--capture=nmi-dispatch") == 0) {
            if (capture_nmi_dispatch || requested_frames != 1u) return 64;
            capture_nmi_dispatch = LIB_TRUE;
            continue;
        }
        if (strncmp(arguments[recorded], "--sound-child=", 14u) == 0) {
            if (sound_child_path != NULL ||
                arguments[recorded][14] == '\0') return 64;
            sound_child_path = arguments[recorded] + 14u;
            continue;
        }
        if (strncmp(arguments[recorded], "--sound-helper=", 15u) == 0) {
            if (sound_helper_path != NULL ||
                arguments[recorded][15] == '\0') return 64;
            sound_helper_path = arguments[recorded] + 15u;
            continue;
        }
        if (strncmp(arguments[recorded], "--sound-case=", 13u) == 0) {
            char *end;
            unsigned long value = strtoul(arguments[recorded] + 13u,
                                          &end, 10);
            if (end == arguments[recorded] + 13u || *end != '\0' ||
                value > 122ul) return 64;
            sound_case = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--sprite-row-child=", 19u) == 0) {
            if (sprite_row_child_path != NULL ||
                arguments[recorded][19] == '\0') return 64;
            sprite_row_child_path = arguments[recorded] + 19u;
            continue;
        }
        if (strcmp(arguments[recorded],
                   "--sprite-row-flip-variant=1") == 0) {
            if (sprite_row_flip_variant != 0u) return 64;
            sprite_row_flip_variant = 1u;
            continue;
        }
        if (strncmp(arguments[recorded], "--relative-child=", 17u) == 0) {
            if (relative_child_path != NULL ||
                arguments[recorded][17] == '\0') return 64;
            relative_child_path = arguments[recorded] + 17u;
            continue;
        }
        if (strncmp(arguments[recorded], "--relative-kind=", 16u) == 0) {
            unsigned long value;
            if (relative_kind != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 16u,
                            &relative_kind_end, 10);
            if (relative_kind_end == arguments[recorded] + 16u ||
                *relative_kind_end != '\0' || value >= 12u) return 64;
            relative_kind = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded],
                    "--relative-coordinate-variant=", 30u) == 0) {
            unsigned long value;
            if (relative_coordinate_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 30u,
                            &relative_coordinate_variant_end, 10);
            if (relative_coordinate_variant_end ==
                    arguments[recorded] + 30u ||
                *relative_coordinate_variant_end != '\0' || value != 1u)
                return 64;
            relative_coordinate_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-size-child=", 20u) == 0) {
            if (player_size_child_path != NULL ||
                arguments[recorded][20] == '\0') return 64;
            player_size_child_path = arguments[recorded] + 20u;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-size-variant=", 22u) == 0) {
            unsigned long value;
            if (player_size_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 22u,
                            &player_size_variant_end, 10);
            if (player_size_variant_end == arguments[recorded] + 22u ||
                *player_size_variant_end != '\0' || value >= 24u) return 64;
            player_size_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-attribute-variant=", 27u) == 0) {
            unsigned long value;
            if (player_attribute_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 27u,
                            &player_attribute_variant_end, 10);
            if (player_attribute_variant_end == arguments[recorded] + 27u ||
                *player_attribute_variant_end != '\0' || value >= 8u) return 64;
            player_attribute_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-action-variant=", 24u) == 0) {
            unsigned long value;
            if (player_action_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 24u,
                            &player_action_variant_end, 10);
            if (player_action_variant_end == arguments[recorded] + 24u ||
                *player_action_variant_end != '\0' || value >= 18u) return 64;
            player_action_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-action-child=", 22u) == 0) {
            if (player_action_child_path != NULL ||
                arguments[recorded][22] == '\0') return 64;
            player_action_child_path = arguments[recorded] + 22u;
            continue;
        }
        if (strncmp(arguments[recorded], "--intermediate-player-variant=", 30u) == 0) {
            unsigned long value;
            if (intermediate_player_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 30u,
                            &intermediate_player_variant_end, 10);
            if (intermediate_player_variant_end == arguments[recorded] + 30u ||
                *intermediate_player_variant_end != '\0' || value >= 4u) return 64;
            intermediate_player_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-control-variant=", 25u) == 0) {
            unsigned long value;
            if (player_control_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 25u,
                            &player_control_variant_end, 10);
            if (player_control_variant_end == arguments[recorded] + 25u ||
                *player_control_variant_end != '\0' || value >= 12u) return 64;
            player_control_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-offset-reads=", 22u) == 0) {
            if (player_offset_reads_path != NULL || arguments[recorded][22] == '\0') return 64;
            player_offset_reads_path = arguments[recorded] + 22u;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-table-variant=", 23u) == 0) {
            unsigned long value;
            if (player_table_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 23u,
                            &player_table_variant_end, 10);
            if (player_table_variant_end == arguments[recorded] + 23u ||
                *player_table_variant_end != '\0' || value >= 26u) return 64;
            player_table_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-table-reads=", 21u) == 0) {
            if (player_table_reads_path != NULL || arguments[recorded][21] == '\0') return 64;
            player_table_reads_path = arguments[recorded] + 21;
            continue;
        }
        if (strncmp(arguments[recorded], "--bubble-draw-variant=", 22u) == 0) {
            unsigned long value;
            if (bubble_draw_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 22u,
                            &bubble_draw_variant_end, 10);
            if (bubble_draw_variant_end == arguments[recorded] + 22u ||
                *bubble_draw_variant_end != '\0' || value >= 4u) return 64;
            bubble_draw_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--bubble-player-variant=", 24u) == 0) {
            unsigned long value;
            if (bubble_player_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 24u,
                            &bubble_player_variant_end, 10);
            if (bubble_player_variant_end == arguments[recorded] + 24u ||
                *bubble_player_variant_end != '\0' || value >= 16u) return 64;
            bubble_player_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--small-platform-variant=", 25u) == 0) {
            unsigned long value;
            if (small_platform_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 25u,
                            &small_platform_variant_end, 10);
            if (small_platform_variant_end == arguments[recorded] + 25u ||
                *small_platform_variant_end != '\0' || value >= 64u) return 64;
            small_platform_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--projectile-frame=", 19u) == 0) {
            unsigned long value;
            if (projectile_frame != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 19u,
                            &projectile_frame_end, 10);
            if (projectile_frame_end == arguments[recorded] + 19u ||
                *projectile_frame_end != '\0' || value >= 32u) return 64;
            projectile_frame = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--enemy-graphics-variant=", 25u) == 0) {
            unsigned long value;
            if (enemy_graphics_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 25u,
                            &enemy_graphics_variant_end, 10);
            if (enemy_graphics_variant_end == arguments[recorded] + 25u ||
                *enemy_graphics_variant_end != '\0' || value >= 20u) return 64;
            enemy_graphics_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--block-graphics-variant=", 25u) == 0) {
            unsigned long value;
            if (block_graphics_variant != 0xffffffffu) return 64;
            value = strtoul(arguments[recorded] + 25u,
                            &block_graphics_variant_end, 10);
            if (block_graphics_variant_end == arguments[recorded] + 25u ||
                *block_graphics_variant_end != '\0' || value >= 8u) return 64;
            block_graphics_variant = (unsigned int)value;
            continue;
        }
        if (strncmp(arguments[recorded], "--enemy-background-calls=", 25u) == 0) {
            if (enemy_background_path != NULL || enemy_landing_path != NULL) return 64;
            enemy_background_path = arguments[recorded] + 25u;
            continue;
        }
        if (strncmp(arguments[recorded], "--enemy-landing-calls=", 22u) == 0) {
            if (enemy_background_path != NULL || enemy_landing_path != NULL) return 64;
            enemy_landing_path = arguments[recorded] + 22u;
            continue;
        }
        if (strncmp(arguments[recorded], "--metatile-calls=", 17u) == 0) {
            if (metatile_path != NULL) return 64;
            metatile_path = arguments[recorded] + 17u;
            continue;
        }
        if (strncmp(arguments[recorded], "--impede-snapshot=", 18u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 18u;
            background_snapshot = 79u;
            continue;
        }
        if (strncmp(arguments[recorded], "--pipe-entry-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 78u;
            continue;
        }
        if (strncmp(arguments[recorded], "--hidden-spring-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 25u;
            background_snapshot = 77u;
            continue;
        }
        if (strncmp(arguments[recorded], "--climbing-snapshot=", 20u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 20u;
            background_snapshot = 76u;
            continue;
        }
        if (strncmp(arguments[recorded], "--terrain-metatile-snapshot=", 28u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 28u;
            background_snapshot = 75u;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-terrain-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 26u;
            background_snapshot = 74u;
            continue;
        }
        if (strncmp(arguments[recorded], "--platform-position-snapshot=", 29u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 29u;
            background_snapshot = 73u;
            continue;
        }
        if (strncmp(arguments[recorded], "--platform-collision-snapshot=", 30u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 30u;
            background_snapshot = 72u;
            continue;
        }
        if (strncmp(arguments[recorded], "--enemy-pair-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 71u;
            continue;
        }
        if (strncmp(arguments[recorded], "--player-enemy-contact-snapshot=", 32u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 32u;
            background_snapshot = 70u;
            continue;
        }
        if (strncmp(arguments[recorded], "--powerup-pickup-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 26u;
            background_snapshot = 69u;
            continue;
        }
        if (strncmp(arguments[recorded], "--hammer-contact-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 26u;
            background_snapshot = 68u;
            continue;
        }
        if (strncmp(arguments[recorded], "--fireball-hit-snapshot=", 24u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 24u;
            background_snapshot = 67u;
            continue;
        }
        if (strncmp(arguments[recorded], "--fireball-enemy-scan-snapshot=", 31u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 31u;
            background_snapshot = 66u;
            continue;
        }
        if (strncmp(arguments[recorded], "--offscreen-bounds-snapshot=", 28u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 28u;
            background_snapshot = 65u;
            continue;
        }
        if (strncmp(arguments[recorded], "--lift-platform-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 25u;
            background_snapshot = 64u;
            continue;
        }
        if (strncmp(arguments[recorded], "--horizontal-platform-snapshot=", 31u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 31u;
            background_snapshot = 63u;
            continue;
        }
        if (strncmp(arguments[recorded], "--vertical-platform-snapshot=", 29u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 29u;
            background_snapshot = 62u;
            continue;
        }
        if (strncmp(arguments[recorded], "--balance-platform-snapshot=", 28u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 28u;
            background_snapshot = 61u;
            continue;
        }
        if (strncmp(arguments[recorded], "--piranha-movement-snapshot=", 28u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 28u;
            background_snapshot = 60u;
            continue;
        }
        if (strncmp(arguments[recorded], "--star-flag-snapshot=", 21u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 21u;
            background_snapshot = 59u;
            continue;
        }
        if (strncmp(arguments[recorded], "--fireworks-lifetime-snapshot=", 30u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 30u;
            background_snapshot = 58u;
            continue;
        }
        if (strncmp(arguments[recorded], "--flame-actor-snapshot=", 23u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 23u;
            background_snapshot = 57u;
            continue;
        }
        if (strncmp(arguments[recorded], "--bowser-graphics-snapshot=", 27u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 27u;
            background_snapshot = 56u;
            continue;
        }
        if (strncmp(arguments[recorded], "--bowser-control-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 26u;
            background_snapshot = 55u;
            continue;
        }
        if (strncmp(arguments[recorded], "--bridge-collapse-snapshot=", 27u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 27u;
            background_snapshot = 54u;
            continue;
        }
        if (strncmp(arguments[recorded], "--lakitu-movement-snapshot=", 27u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 27u;
            background_snapshot = 53u;
            continue;
        }
        if (strncmp(arguments[recorded], "--flying-cheep-movement-snapshot=", 33u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 33u;
            background_snapshot = 52u;
            continue;
        }
        if (strncmp(arguments[recorded], "--firebar-chain-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 25u;
            background_snapshot = 51u;
            continue;
        }
        if (strncmp(arguments[recorded], "--swimming-cheep-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 26u;
            background_snapshot = 50u;
            continue;
        }
        if (strncmp(arguments[recorded], "--bullet-movement-snapshot=", 27u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 27u;
            background_snapshot = 49u;
            continue;
        }
        if (strncmp(arguments[recorded], "--bloober-snapshot=", 19u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 19u;
            background_snapshot = 48u;
            continue;
        }
        if (strncmp(arguments[recorded], "--green-counter-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 25u;
            background_snapshot = 47u;
            continue;
        }
        if (strncmp(arguments[recorded], "--paratroopa-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 46u;
            continue;
        }
        if (strncmp(arguments[recorded], "--hammer-movement-snapshot=", 27u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 27u;
            background_snapshot = 45u;
            continue;
        }
        if (strncmp(arguments[recorded], "--podoboo-snapshot=", 19u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 19u;
            background_snapshot = 44u;
            continue;
        }
        if (strncmp(arguments[recorded], "--special-actor-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 25u;
            background_snapshot = 43u;
            continue;
        }
        if (strncmp(arguments[recorded], "--large-platform-graphics-snapshot=", 35u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 35u;
            background_snapshot = 80u;
            continue;
        }
        if (strncmp(arguments[recorded], "--normal-actor-snapshot=", 24u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 24u;
            background_snapshot = 42u;
            continue;
        }
        if (strncmp(arguments[recorded], "--actor-dispatch-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 26u;
            background_snapshot = 41u;
            continue;
        }
        if (strncmp(arguments[recorded], "--platform-init-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 25u;
            background_snapshot = 40u;
            continue;
        }
        if (strncmp(arguments[recorded], "--small-init-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 39u;
            continue;
        }
        if (strncmp(arguments[recorded], "--group-snapshot=", 17u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 17u;
            background_snapshot = 38u;
            continue;
        }
        if (strncmp(arguments[recorded], "--bullet-swim-snapshot=", 23u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 23u;
            background_snapshot = 37u;
            continue;
        }
        if (strncmp(arguments[recorded], "--fireworks-snapshot=", 21u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 21u;
            background_snapshot = 36u;
            continue;
        }
        if (strncmp(arguments[recorded], "--bowser-flame-snapshot=", 24u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 24u;
            background_snapshot = 35u;
            continue;
        }
        if (strncmp(arguments[recorded], "--flying-fish-snapshot=", 23u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 23u;
            background_snapshot = 34u;
            continue;
        }
        if (strncmp(arguments[recorded], "--lakitu-spiny-snapshot=", 24u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 24u;
            background_snapshot = 33u;
            continue;
        }
        if (strncmp(arguments[recorded], "--enemy-init-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 32u;
            continue;
        }
        if (strncmp(arguments[recorded], "--enemy-stream-snapshot=", 24u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 24u;
            background_snapshot = 31u;
            continue;
        }
        if (strncmp(arguments[recorded], "--enemy-loop-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 30u;
            continue;
        }
        if (strncmp(arguments[recorded], "--gravity-snapshot=", 19u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 19u;
            background_snapshot = 29u;
            continue;
        }
        if (strncmp(arguments[recorded], "--vertical-snapshot=", 20u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 20u;
            background_snapshot = 28u;
            continue;
        }
        if (strncmp(arguments[recorded], "--horizontal-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 27u;
            continue;
        }
        if (strncmp(arguments[recorded], "--block-replacement-snapshot=", 29u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 29u;
            background_snapshot = 26u;
            continue;
        }
        if (strncmp(arguments[recorded], "--block-lifetime-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 26u;
            background_snapshot = 25u;
            continue;
        }
        if (strncmp(arguments[recorded], "--block-chunks-snapshot=", 24u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 24u;
            background_snapshot = 24u;
            continue;
        }
        if (strncmp(arguments[recorded], "--block-bump-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 23u;
            continue;
        }
        if (strncmp(arguments[recorded], "--block-head-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 22u;
            background_snapshot = 22u;
            continue;
        }
        if (strncmp(arguments[recorded], "--power-up-actor-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 26u;
            background_snapshot = 21u;
            continue;
        }
        if (strncmp(arguments[recorded], "--power-up-init-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 25u;
            background_snapshot = 20u;
            continue;
        }
        if (strncmp(arguments[recorded], "--score-hud-snapshot=", 21u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 21u;
            background_snapshot = 19u;
            continue;
        }
        if (strncmp(arguments[recorded], "--misc-lifetime-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 25u;
            background_snapshot = 18u;
            continue;
        }
        if (strncmp(arguments[recorded], "--coin-allocation-snapshot=", 27u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 27u;
            background_snapshot = 17u;
            continue;
        }
        if (strncmp(arguments[recorded], "--hammer-chain-snapshot=", 24u) == 0) {
            if (movement_snapshot_path != NULL) return 64;
            movement_snapshot_path = arguments[recorded] + 24u;
            background_snapshot = 16u;
            continue;
        }
        if (strncmp(arguments[recorded], "--vine-actor-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][22] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 22;
            background_snapshot = 15u;
            continue;
        }
        if (strncmp(arguments[recorded], "--vine-setup-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][22] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 22;
            background_snapshot = 14u;
            continue;
        }
        if (strncmp(arguments[recorded], "--jumpspring-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][22] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 22;
            background_snapshot = 13u;
            continue;
        }
        if (strncmp(arguments[recorded], "--timer-snapshot=", 17u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][17] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 17;
            background_snapshot = 12u;
            continue;
        }
        if (strncmp(arguments[recorded], "--bubble-snapshot=", 18u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][18] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 18;
            background_snapshot = 11u;
            continue;
        }
        if (strncmp(arguments[recorded], "--fireball-core-snapshot=", 25u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][25] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 25;
            background_snapshot = 10u;
            continue;
        }
        if (strncmp(arguments[recorded], "--dispatch-snapshot=", 20u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][20] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 20;
            background_snapshot = 9u;
            continue;
        }
        if (strncmp(arguments[recorded], "--movement-state-snapshot=", 26u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][26] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 26;
            background_snapshot = 8u;
            continue;
        }
        if (strncmp(arguments[recorded], "--end-level-snapshot=", 21u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][21] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 21;
            background_snapshot = 7u;
            continue;
        }
        if (strncmp(arguments[recorded], "--modes-snapshot=", 17u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][17] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 17;
            background_snapshot = 6u;
            continue;
        }
        if (strncmp(arguments[recorded], "--transition-snapshot=", 22u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][22] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 22;
            background_snapshot = 5u;
            continue;
        }
        if (strncmp(arguments[recorded], "--control-snapshot=", 19u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][19] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 19;
            background_snapshot = 4u;
            continue;
        }
        if (strncmp(arguments[recorded], "--control-children=", 19u) == 0) {
            if (entrance_children_path != NULL || arguments[recorded][19] == '\0') return 64;
            entrance_children_path = arguments[recorded] + 19;
            continue;
        }
        if (strncmp(arguments[recorded], "--entrance-children=", 20u) == 0) {
            if (entrance_children_path != NULL || arguments[recorded][20] == '\0') return 64;
            entrance_children_path = arguments[recorded] + 20;
            continue;
        }
        if (strncmp(arguments[recorded], "--entrance-snapshot=", 20u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][20] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 20;
            background_snapshot = 3u;
            continue;
        }
        if (strncmp(arguments[recorded], "--scroll-snapshot=", 18u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][18] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 18;
            background_snapshot = 2u;
            continue;
        }
        if (strncmp(arguments[recorded], "--enemy-background-snapshot=", 28u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][28] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 28;
            background_snapshot = 1u;
            continue;
        }
        if (strncmp(arguments[recorded], "--normal-movement-snapshot=", 27u) == 0) {
            if (movement_snapshot_path != NULL || arguments[recorded][27] == '\0') return 64;
            movement_snapshot_path = arguments[recorded] + 27;
            continue;
        }
        if (strncmp(arguments[recorded], "--area-read-coverage=", 21u) == 0) {
            if (area_reads_path != NULL || arguments[recorded][21] == '\0') return 64;
            area_reads_path = arguments[recorded] + 21;
            continue;
        }
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
        if (strcmp(arguments[recorded], "--fixture=t29-special-frenzy") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 76u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-pulley") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 77u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-tree") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 78u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-frenzy-present") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 79u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-pulley-rope") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 80u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-pulley-end") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 81u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-mush-start") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 82u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-mush-middle") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 83u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-mush-end") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 84u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-tree-end") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 85u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-warp-piranha") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 86u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-warp-world-ground") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 87u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-warp-world-water") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 88u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-special-warp-zero-water") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 89u; continue; }
        block_scenario = mysmb_background_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(27677 + block_scenario);
            continue;
        }
        block_scenario = mysmb_landing_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(29725 + block_scenario);
            continue;
        }
        block_scenario = mysmb_impede_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(26653 + block_scenario);
            transition_entry = 0xdf4bu;
            continue;
        }
        block_scenario = mysmb_pipe_entry_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(26141 + block_scenario);
            transition_entry = 0xdee8u;
            continue;
        }
        block_scenario = mysmb_climbing_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(25117 + block_scenario);
            transition_entry = 0xde2eu;
            continue;
        }
        block_scenario = mysmb_terrain_metatile_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(24989 + block_scenario);
            transition_entry = ((block_scenario - 1) & 1) ? 0xde0eu : 0xde05u;
            continue;
        }
        block_scenario = mysmb_player_terrain_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(23955 + block_scenario);
            transition_entry = 0xdc64u;
            continue;
        }
        block_scenario = mysmb_platform_position_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(23371 + block_scenario);
            transition_entry = mysmb_platform_position_small((unsigned int)(block_scenario-1)) ? 0xdc19u : 0xdc21u;
            continue;
        }
        block_scenario = mysmb_platform_collision_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(21323 + block_scenario);
            transition_entry = block_scenario <= 1024 ? 0xdb45u : 0xdb7bu;
            continue;
        }
        block_scenario = mysmb_enemy_pair_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(20299 + block_scenario);
            transition_entry = 0xda33u;
            continue;
        }
        block_scenario = mysmb_player_enemy_contact_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(18699 + block_scenario);
            transition_entry = 0xd853u;
            continue;
        }
        block_scenario = mysmb_powerup_pickup_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(18571 + block_scenario);
            transition_entry = 0xd800u;
            continue;
        }
        block_scenario = mysmb_hammer_contact_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(18283 + block_scenario);
            transition_entry = 0xd7c4u;
            continue;
        }
        block_scenario = mysmb_fireball_hit_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(17771 + block_scenario);
            transition_entry = 0xd73eu;
            continue;
        }
        block_scenario = mysmb_fireball_enemy_scan_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(16747 + block_scenario);
            transition_entry = 0xd6d9u;
            continue;
        }
        block_scenario = mysmb_offscreen_bounds_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(15723 + block_scenario);
            transition_entry = 0xd67au;
            continue;
        }
        block_scenario = mysmb_lift_platform_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(15211 + block_scenario);
            transition_entry = (lib_u16)mysmb_lift_platform_entry((unsigned int)(block_scenario - 1));
            continue;
        }
        block_scenario = mysmb_horizontal_platform_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(14443 + block_scenario);
            transition_entry = (lib_u16)mysmb_horizontal_platform_entry((unsigned int)(block_scenario - 1));
            continue;
        }
        block_scenario = mysmb_vertical_platform_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(13931 + block_scenario);
            transition_entry = 0xd5d3u;
            continue;
        }
        block_scenario = mysmb_balance_platform_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(12907 + block_scenario);
            transition_entry = 0xd432u;
            continue;
        }
        block_scenario = mysmb_piranha_movement_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(12395 + block_scenario);
            transition_entry = 0xd3b0u;
            continue;
        }
        block_scenario = mysmb_star_flag_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(11371 + block_scenario);
            transition_entry = 0xd2d9u;
            continue;
        }
        block_scenario = mysmb_fireworks_lifetime_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(10859 + block_scenario);
            transition_entry = 0xd295u;
            continue;
        }
        block_scenario = mysmb_flame_actor_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(9835 + block_scenario);
            transition_entry = 0xd1ebu;
            continue;
        }
        block_scenario = mysmb_bowser_graphics_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(9323 + block_scenario);
            transition_entry = 0xd17bu;
            continue;
        }
        block_scenario = mysmb_bowser_control_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(8299 + block_scenario);
            transition_entry = 0xd065u;
            continue;
        }
        block_scenario = mysmb_bridge_collapse_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(8119 + block_scenario);
            transition_entry = 0xcfecu;
            continue;
        }
        block_scenario = mysmb_lakitu_movement_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(7095 + block_scenario);
            transition_entry = block_scenario <= 512 ? 0xcf28u : 0xcf6cu;
            continue;
        }
        block_scenario = mysmb_flying_cheep_movement_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(6583 + block_scenario);
            transition_entry = 0xcedfu;
            continue;
        }
        block_scenario = mysmb_firebar_chain_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(6071 + block_scenario);
            transition_entry = 0xcd3cu;
            continue;
        }
        block_scenario = mysmb_swimming_cheep_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(5559 + block_scenario);
            transition_entry = 0xcc4au;
            continue;
        }
        block_scenario = mysmb_bullet_movement_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(5431 + block_scenario);
            transition_entry = 0xcc36u;
            continue;
        }
        block_scenario = mysmb_bloober_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(4919 + block_scenario);
            transition_entry = 0xcb89u;
            continue;
        }
        block_scenario = mysmb_green_counter_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(4631 + block_scenario);
            transition_entry = (lib_u16)mysmb_green_counter_entry((unsigned int)(block_scenario-1));
            continue;
        }
        block_scenario = mysmb_paratroopa_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(4471 + block_scenario);
            transition_entry = (lib_u16)mysmb_paratroopa_entry((unsigned int)(block_scenario-1));
            continue;
        }
        block_scenario = mysmb_hammer_movement_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(4115 + block_scenario);
            transition_entry = (lib_u16)mysmb_hammer_movement_entry((unsigned int)(block_scenario-1));
            continue;
        }
        block_scenario = mysmb_podoboo_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(4051 + block_scenario);
            transition_entry = 0xc9b0u;
            continue;
        }
        block_scenario = mysmb_special_actor_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(3959 + block_scenario);
            transition_entry = (lib_u16)mysmb_special_actor_entry((unsigned int)(block_scenario-1));
            continue;
        }
        block_scenario = mysmb_large_platform_graphics_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(39999 + block_scenario);
            transition_entry = 0xc965u;
            continue;
        }
        block_scenario = mysmb_normal_actor_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(3833 + block_scenario);
            transition_entry = block_scenario <= 84 ? 0xc8e0u : 0xc905u;
            continue;
        }
        block_scenario = mysmb_actor_dispatch_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(3653 + block_scenario);
            transition_entry = block_scenario <= 108 ? 0xc882u : 0xc8d7u;
            continue;
        }
        block_scenario = mysmb_platform_init_argument(arguments[recorded]);
        if (block_scenario != 0) {
            static const lib_u16 entries[10] = {
                0xc7dfu,0xc812u,0xc83fu,0xc845u,0xc80bu,
                0xc803u,0xc80bu,0xc84bu,0xc857u,0xc881u
            };
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(3413 + block_scenario);
            transition_entry = entries[(block_scenario - 1) / 24];
            continue;
        }
        block_scenario = mysmb_small_init_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u32)(3217 + block_scenario);
            transition_entry = block_scenario <= 48 ? 0xc787u :
                (block_scenario <= 96 ? 0xc7d1u :
                (block_scenario <= 160 ? 0xc7b8u : 0xc7a0u));
            continue;
        }
        block_scenario = mysmb_group_enemy_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(3089 + block_scenario);
            transition_entry = 0xc71bu;
            continue;
        }
        block_scenario = mysmb_bullet_swim_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(2907 + block_scenario);
            transition_entry = 0xc69cu;
            continue;
        }
        block_scenario = mysmb_fireworks_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(2787 + block_scenario);
            transition_entry = 0xc63du;
            continue;
        }
        block_scenario = mysmb_bowser_flame_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(2627 + block_scenario);
            transition_entry = block_scenario <= 24 ? 0xc549u : 0xc5a3u;
            continue;
        }
        block_scenario = mysmb_flying_fish_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(2475 + block_scenario);
            transition_entry = 0xc4a8u;
            continue;
        }
        block_scenario = mysmb_lakitu_spiny_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(2355 + block_scenario);
            transition_entry = 0xc3a4u;
            continue;
        }
        block_scenario = mysmb_enemy_init_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)((block_scenario >= 163 ? 2273 : 2193) + block_scenario);
            transition_entry = 0xc26cu;
            continue;
        }
        block_scenario = mysmb_enemy_stream_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(2113 + block_scenario);
            transition_entry = 0xc144u;
            continue;
        }
        block_scenario = mysmb_enemy_loop_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(2017 + block_scenario);
            transition_entry = 0xc047u;
            continue;
        }
        block_scenario = mysmb_gravity_argument(arguments[recorded]);
        if (block_scenario != 0) {
            static const lib_u16 entries[4] = {0xbfa4u, 0xbfb4u, 0xbfb7u, 0xbfd7u};
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1985 + block_scenario);
            transition_entry = entries[(block_scenario - 1) / 8];
            continue;
        }
        block_scenario = mysmb_vertical_argument(arguments[recorded]);
        if (block_scenario != 0) {
            static const lib_u16 entries[8] = {
                0xbf4du, 0xbf63u, 0xbf6bu, 0xbf70u,
                0xbf75u, 0xbf88u, 0xbf8cu, 0xbf92u
            };
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1953 + block_scenario);
            transition_entry = entries[(block_scenario - 1) / 4];
            continue;
        }
        block_scenario = mysmb_horizontal_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1857 + block_scenario);
            transition_entry = block_scenario<=32 ? 0xbf09u :
                (block_scenario<=64 ? 0xbf02u : 0xbf0fu);
            continue;
        }
        block_scenario = mysmb_block_replacement_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1825 + block_scenario);
            transition_entry = 0xbed4u;
            continue;
        }
        block_scenario = mysmb_block_lifetime_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1793 + block_scenario);
            transition_entry = 0xbe70u;
            continue;
        }
        block_scenario = mysmb_block_chunks_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1777 + block_scenario);
            transition_entry = 0xbe02u;
            continue;
        }
        block_scenario = mysmb_block_bump_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1717 + block_scenario);
            transition_entry = 0xbd9bu;
            continue;
        }
        block_scenario = mysmb_block_head_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1645 + block_scenario);
            transition_entry = 0xbcedu;
            continue;
        }
        block_scenario = mysmb_power_up_actor_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1595 + block_scenario);
            transition_entry = 0xbc85u;
            continue;
        }
        block_scenario = mysmb_power_up_init_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1559 + block_scenario);
            transition_entry = block_scenario <= 18 ? 0xbc49u : 0xbc60u;
            continue;
        }
        block_scenario = mysmb_score_hud_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1503 + block_scenario);
            transition_entry = block_scenario <= 32 ? 0xbbfeu :
                (block_scenario <= 40 ? 0xbc27u :
                (block_scenario <= 48 ? 0xbc30u : 0xbc36u));
            continue;
        }
        block_scenario = mysmb_misc_lifetime_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = block_scenario <= 42 ?
                (unsigned int)(1461 + block_scenario) :
                (unsigned int)(41000 + block_scenario - 43);
            transition_entry = 0xbb96u;
            continue;
        }
        block_scenario = mysmb_coin_allocation_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1413 + block_scenario);
            transition_entry = block_scenario <= 32 ? 0xbb38u : 0xbb51u;
            continue;
        }
        block_scenario = mysmb_hammer_chain_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1350 + block_scenario);
            transition_entry = block_scenario <= 27 ? 0xba94u : 0xbac3u;
            continue;
        }
        block_scenario = mysmb_vine_actor_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1308 + block_scenario);
            transition_entry = 0xb94bu;
            continue;
        }
        block_scenario = mysmb_vine_setup_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1292 + block_scenario);
            transition_entry = 0xb91eu;
            continue;
        }
        block_scenario = mysmb_jumpspring_core_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1260 + block_scenario);
            transition_entry = 0xb8bau;
            continue;
        }
        block_scenario = mysmb_timer_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1244 + block_scenario);
            transition_entry = 0xb74fu;
            continue;
        }
        block_scenario = mysmb_bubble_core_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1214 + block_scenario);
            transition_entry = block_scenario <= 24 ? 0xb6f9u : 0xb70bu;
            continue;
        }
        block_scenario = mysmb_fireball_core_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1182 + block_scenario);
            transition_entry = 0xb689u;
            continue;
        }
        block_scenario = mysmb_fireball_dispatch_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(1150 + block_scenario);
            transition_entry = 0xb624u;
            continue;
        }
        block_scenario = mysmb_player_movement_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(904 + block_scenario);
            transition_entry = 0xb329u;
            continue;
        }
        block_scenario = mysmb_player_end_level_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(875 + block_scenario);
            transition_entry = block_scenario<=4 ? 0xb2a4u :
                (block_scenario<=28 ? 0xb2cau : 0xb315u);
            continue;
        }
        block_scenario = mysmb_player_modes_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(853 + block_scenario);
            transition_entry = block_scenario<=5 ? 0xb233u :
                (block_scenario<=10 ? 0xb245u : (block_scenario<=13 ? 0xb269u :
                (block_scenario<=18 ? 0xb27du : (block_scenario==19 ? 0xb288u : 0xb29au))));
            if (block_scenario>20) transition_entry = 0xb245u;
            continue;
        }
        block_scenario = mysmb_player_transition_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(825 + block_scenario);
            transition_entry = block_scenario<=6 ? 0xb1c7u :
                (block_scenario<=14 ? 0xb206u : (block_scenario<=26 ? 0xb1e5u : 0xb200u));
            continue;
        }
        block_scenario = mysmb_player_control_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(775 + block_scenario);
            continue;
        }
        block_scenario = mysmb_entrance_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(740 + block_scenario);
            continue;
        }
        block_scenario = mysmb_scroll_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(716 + block_scenario);
            continue;
        }
        block_scenario = mysmb_engine_normal_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(651 + block_scenario);
            continue;
        }
        block_scenario = mysmb_engine_warp_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(641 + block_scenario);
            continue;
        }
        block_scenario = mysmb_engine_cannon_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(616 + block_scenario);
            continue;
        }
        block_scenario = mysmb_engine_environment_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(604 + block_scenario);
            continue;
        }
        block_scenario = mysmb_engine_slots_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(602 + block_scenario);
            continue;
        }
        block_scenario = mysmb_engine_tail_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(587 + block_scenario);
            continue;
        }
        block_scenario = mysmb_game_entry_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(583 + block_scenario);
            continue;
        }
        block_scenario = mysmb_water_scene_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(580 + block_scenario);
            continue;
        }
        block_scenario = mysmb_underground_scene_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(577 + block_scenario);
            continue;
        }
        block_scenario = mysmb_ground_scene_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(554 + block_scenario);
            continue;
        }
        block_scenario = mysmb_castle_scene_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(547 + block_scenario);
            continue;
        }
        block_scenario = mysmb_area_pointer_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(476 + block_scenario);
            continue;
        }
        block_scenario = mysmb_block_address_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(428 + block_scenario);
            continue;
        }
        block_scenario = mysmb_pipe_tail_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(396 + block_scenario);
            continue;
        }
        block_scenario = mysmb_parser_boundary_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(372 + block_scenario);
            continue;
        }
        block_scenario = mysmb_area_helper_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(352 + block_scenario);
            continue;
        }
        block_scenario = mysmb_hole_underpart_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (unsigned int)(254 + block_scenario);
            continue;
        }
        block_scenario = mysmb_item_block_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u8)(182 + block_scenario);
            continue;
        }
        block_scenario = mysmb_jumpspring_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u8)(174 + block_scenario);
            continue;
        }
        block_scenario = mysmb_staircase_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u8)(162 + block_scenario);
            continue;
        }
        block_scenario = mysmb_cannon_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u8)(132 + block_scenario);
            continue;
        }
        block_scenario = mysmb_block_row_column_argument(arguments[recorded]);
        if (block_scenario != 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = (lib_u8)(100 + block_scenario);
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t30-column-axe") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 95u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t30-column-chain") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 96u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t30-column-bridge") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 97u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t30-column-empty") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 98u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t30-column-bridge-mid") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 99u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t30-column-bridge-end") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 100u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t22-flagpole") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 93u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t22-flagpole-score") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 94u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-geometry-castle") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 90u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-geometry-vertical-pipe") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 91u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t29-final-question-high") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 92u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t28-title-score") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 57u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t52-title-demo-expired-b") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 101u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t52-title-demo-active-b") == 0) {
            if (t26_fixture != 0u) return 64;
            t26_fixture = 102u;
            continue;
        }
        if (strcmp(arguments[recorded], "--fixture=t52-background-palette-0") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 103u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t52-background-palette-4") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 104u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t52-background-palette-5") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 105u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t52-background-palette-6") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 106u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t52-background-palette-7") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 107u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t52-timeup-output-inter-return") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 108u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-screen-init-nmi") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 109u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-area-palette-0") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 110u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-area-palette-1") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 111u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-area-palette-2") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 112u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-area-palette-3") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 113u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-player-mario") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 114u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-player-luigi") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 115u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-player-fire") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 116u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-alternate-standard") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 117u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-alternate-mushroom") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 118u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-title-draw") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 119u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-title-clear") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 120u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-top-mario") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 121u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-top-luigi") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 122u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-lives-crown") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 123u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-warp4") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 124u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-warp5") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 125u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-warp6") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 126u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-timeup-luigi") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 127u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-timeup-mario") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 128u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-gameover-luigi") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 129u; continue; }
        if (strcmp(arguments[recorded], "--fixture=t54-text-gameover-mario") == 0) { if (t26_fixture != 0u) return 64; t26_fixture = 130u; continue; }
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
    if ((relative_child_path == NULL) !=
        (relative_kind == 0xffffffffu)) return 64;
    if (sprite_row_flip_variant != 0u &&
        sprite_row_child_path == NULL) return 64;
    if (sound_case != 0u && sound_child_path == NULL) return 64;
    if (relative_coordinate_variant != 0xffffffffu &&
        relative_child_path == NULL) return 64;
    if (relative_child_path != NULL) {
        static const lib_u16 entries[12] = {
            0xf12au, 0xf131u, 0xf13bu, 0xf148u, 0xf152u, 0xf159u,
            0xf180u, 0xf187u, 0xf191u, 0xf19bu, 0xf1afu, 0xf1b6u
        };
        relative_child_entry = entries[relative_kind];
    }
    if (enemy_graphics_variant != 0xffffffffu &&
        (background_snapshot != 42u || t26_fixture < 3834u ||
         t26_fixture > 3959u)) return 64;
    if (block_graphics_variant != 0xffffffffu &&
        (background_snapshot != 25u || t26_fixture < 1794u ||
         t26_fixture > 1825u)) return 64;
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
    if (screen_dispatch_task != 0xffffffffu) {
        /* Wait until reset has completed and an ordinary NMI has returned.
         * Before that boundary the driver can still own CPU reset state. */
        screen_dispatch_pending = LIB_TRUE;
    }
    mysmb_reference_apply_ram_write(&ram_write, elapsed, driver->machine->ram);
    core_controller_set_buttons(&driver->machine->controller, (lib_u8)buttons);
    while (recorded < requested_frames &&
           step_count < total_frames * MYSMB_REFERENCE_MAX_STEPS_PER_FRAME) {
        core_run_result result;
        lib_u16 before_pc;
        lib_u16 area_read_address = 0u;

        if (direct_warp_text && driver->machine->pc == 0x8001u) {
            if (!mysmb_reference_write_frame(output, driver->machine)) break;
            ++recorded;
            break;
        }
        if (direct_screen_dispatch && driver->machine->pc == 0x8001u) {
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
        /* The normal controlled write is applied after an NMI return.  For
         * this pre-dispatch probe, apply its one declared value at the next
         * NMI entry instead, so ordinary mainline work cannot overwrite the
         * explicitly requested mirror before the source writes $2000. */
        if (capture_nmi_dispatch && ram_write.present &&
            ram_write.frame == elapsed + 1u &&
            driver->machine->pc == MYSMB_REFERENCE_NMI_ENTRY)
            mysmb_reference_apply_ram_write(&ram_write, elapsed + 1u,
                                            driver->machine->ram);
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
        /* OutputInter has completed its text/timer/enable writes but has not
         * returned to its natural caller.  This records the ROM instruction
         * boundary separately from a later NMI-return observation. */
        if (t52_timeup_output_inter_probe &&
            driver->machine->pc == MYSMB_REFERENCE_T52_OUTPUT_INTER_RETURN) {
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
        /* ROM $af8f is the normal GameEngine JSR AreaParserTaskHandler.
         * All earlier frame logic has run; this replaces only the source-RAM
         * parser precondition before the original call executes. */
        if (t29_vertical_pipe_pending && driver->machine->pc == 0xaf8fu) {
            mysmb_reference_apply_t29_geometry_vertical_pipe_fixture(
                driver->machine->ram);
            t29_vertical_pipe_pending = LIB_FALSE;
        }

        if (capture_nmi_dispatch && elapsed >= warmup_frames &&
            driver->machine->pc == MYSMB_REFERENCE_NMI_DISPATCH) {
            /* This is a source-reachable boundary, immediately before the
             * original JSR.  It is intentionally separate from the normal
             * RTI snapshot contract used by full-frame comparisons. */
            if (!mysmb_reference_write_frame(output, driver->machine)) break;
            ++recorded;
            break;
        }

        if (screen_dispatch_pending &&
            driver->machine->pc == MYSMB_REFERENCE_NMI_RETURN) {
            /* Enter the original ScreenRoutines entry with a real 6502
             * return frame. JumpEngine consumes it and the selected leaf
             * RTSes to the recorder sentinel. */
            driver->machine->ram[0x073cu] = (lib_u8)screen_dispatch_task;
            driver->machine->ram[0x0770u] = 0u;
            driver->machine->ram[0x0772u] = 1u;
            /* The JSR at $856a pushes its own inline-table return.  The
             * preexisting caller frame is therefore only the sentinel used
             * when the selected leaf finally RTSes from ScreenRoutines. */
            driver->machine->ram[0x01feu] = 0u;
            driver->machine->ram[0x01ffu] = 0x80u;
            driver->machine->s = 0xfdu;
            driver->machine->pc = 0x8567u;
            direct_screen_dispatch = LIB_TRUE;
            screen_dispatch_pending = LIB_FALSE;
            continue;
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
                else if (t26_fixture == 101u)
                    mysmb_reference_apply_t52_title_menu_fixture(
                        driver->machine->ram, 0u);
                else if (t26_fixture == 102u)
                    mysmb_reference_apply_t52_title_menu_fixture(
                        driver->machine->ram, 1u);
                else if (t26_fixture >= 103u && t26_fixture <= 107u)
                    mysmb_reference_apply_t52_background_palette_fixture(
                        driver->machine->ram, t26_fixture == 103u ? 0u :
                        (lib_u8)(t26_fixture - 100u));
                else if (t26_fixture == 109u)
                    mysmb_reference_apply_t28_init_screen_fixture(
                        driver->machine->ram);
                else if (t26_fixture >= 110u && t26_fixture <= 113u)
                    mysmb_reference_apply_t54_area_palette_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 110u));
                else if (t26_fixture >= 114u && t26_fixture <= 116u)
                    mysmb_reference_apply_t54_player_palette_fixture(
                        driver->machine->ram, t26_fixture == 115u ? 1u : 0u,
                        t26_fixture == 116u ? 2u : 0u);
                else if (t26_fixture >= 117u && t26_fixture <= 118u)
                    mysmb_reference_apply_t54_alternate_palette_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 117u));
                else if (t26_fixture == 119u || t26_fixture == 120u)
                    mysmb_reference_apply_t54_title_task_fixture(
                        driver->machine->ram,
                        t26_fixture == 119u ? 12u : 13u);
                else if (t26_fixture >= 121u && t26_fixture <= 130u) {
                    driver->machine->ram[0x0300u] = 0u;
                    if (t26_fixture == 122u) {
                        driver->machine->ram[0x077au] = 1u;
                        driver->machine->ram[0x0753u] = 1u;
                    }
                    if (t26_fixture == 123u) {
                        driver->machine->ram[0x075au] = 9u;
                        driver->machine->ram[0x075fu] = 1u;
                        driver->machine->ram[0x075cu] = 3u;
                    }
                    if (t26_fixture >= 127u) {
                        driver->machine->ram[0x077au] = 1u;
                        driver->machine->ram[0x0753u] =
                            (t26_fixture == 127u || t26_fixture == 130u) ? 0u : 1u;
                        if (t26_fixture >= 129u) driver->machine->ram[0x0770u] = 3u;
                    }
                    /* This controlled leaf route returns straight to the
                     * recorder sentinel.  Unlike the older parser-owned
                     * Warp fixtures, it has no caller continuation to model. */
                    driver->machine->ram[0x01feu] = 0u;
                    driver->machine->ram[0x01ffu] = 0x80u;
                    driver->machine->a = t26_fixture == 123u ? 1u :
                        (t26_fixture >= 127u ? (lib_u8)(t26_fixture - 125u) :
                        (t26_fixture >= 124u ? (lib_u8)(t26_fixture - 120u) : 0u));
                    driver->machine->s = 0xfdu;
                    driver->machine->pc = 0x8808u;
                    direct_warp_text = LIB_TRUE;
                }
                else if (t26_fixture == 108u) {
                    mysmb_reference_apply_t27_screen_fixture(
                        driver->machine->ram, 0u);
                    if (core_machine_breakpoint_set(driver->machine,
                        MYSMB_REFERENCE_T52_OUTPUT_INTER_RETURN,
                        LIB_TRUE) != LIB_STATUS_OK) break;
                    t52_timeup_output_inter_probe = LIB_TRUE;
                }
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
                else if (t26_fixture >= 76u && t26_fixture <= 78u)
                    mysmb_reference_apply_t29_special_chain_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 76u));
                else if (t26_fixture >= 79u && t26_fixture <= 85u)
                    mysmb_reference_apply_t29_special_continuation_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 79u));
                else if (t26_fixture >= 86u && t26_fixture <= 89u)
                    mysmb_reference_apply_t29_warp_selector_fixture(
                        driver->machine->ram, (lib_u8)(t26_fixture - 86u));
                else if (t26_fixture >= 27678u && t26_fixture <= 29725u)
                    mysmb_background_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 27678u));
                else if (t26_fixture >= 29726u && t26_fixture <= 30749u)
                    mysmb_landing_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 29726u));
                else if (t26_fixture >= 26654u && t26_fixture <= 27677u)
                    mysmb_player_terrain_fixture(driver->machine->ram, 0u);
                else if (t26_fixture >= 26142u && t26_fixture <= 26653u)
                    mysmb_player_terrain_fixture(driver->machine->ram, 0u);
                else if (t26_fixture >= 25118u && t26_fixture <= 26141u)
                    mysmb_player_terrain_fixture(driver->machine->ram, 0u);
                else if (t26_fixture >= 24990u && t26_fixture <= 25117u)
                    mysmb_player_terrain_fixture(driver->machine->ram, 0u);
                else if (t26_fixture >= 23956u && t26_fixture <= 24989u)
                    mysmb_player_terrain_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 23956u));
                else if (t26_fixture >= 23372u && t26_fixture <= 23955u)
                    mysmb_platform_position_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 23372u));
                else if (t26_fixture >= 21324u && t26_fixture <= 23371u)
                    mysmb_platform_collision_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 21324u));
                else if (t26_fixture >= 20300u && t26_fixture <= 21323u)
                    mysmb_enemy_pair_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 20300u));
                else if (t26_fixture >= 18700u && t26_fixture <= 20299u)
                    mysmb_player_enemy_contact_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 18700u));
                else if (t26_fixture >= 18572u && t26_fixture <= 18699u)
                    mysmb_powerup_pickup_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 18572u));
                else if (t26_fixture >= 18284u && t26_fixture <= 18571u)
                    mysmb_hammer_contact_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 18284u));
                else if (t26_fixture >= 17772u && t26_fixture <= 18283u)
                    mysmb_fireball_hit_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 17772u));
                else if (t26_fixture >= 16748u && t26_fixture <= 17771u)
                    mysmb_fireball_enemy_scan_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 16748u));
                else if (t26_fixture >= 15724u && t26_fixture <= 16747u)
                    mysmb_offscreen_bounds_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 15724u));
                else if (t26_fixture >= 15212u && t26_fixture <= 15723u)
                    mysmb_lift_platform_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 15212u));
                else if (t26_fixture >= 14444u && t26_fixture <= 15211u)
                    mysmb_horizontal_platform_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 14444u));
                else if (t26_fixture >= 13932u && t26_fixture <= 14443u)
                    mysmb_vertical_platform_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 13932u));
                else if (t26_fixture >= 12908u && t26_fixture <= 13931u)
                    mysmb_balance_platform_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 12908u));
                else if (t26_fixture >= 12396u && t26_fixture <= 12907u)
                    mysmb_piranha_movement_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 12396u));
                else if (t26_fixture >= 11372u && t26_fixture <= 12395u)
                    mysmb_star_flag_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 11372u));
                else if (t26_fixture >= 10860u && t26_fixture <= 11371u)
                    mysmb_fireworks_lifetime_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 10860u));
                else if (t26_fixture >= 9836u && t26_fixture <= 10859u)
                    mysmb_flame_actor_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 9836u));
                else if (t26_fixture >= 9324u && t26_fixture <= 9835u)
                    mysmb_bowser_graphics_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 9324u));
                else if (t26_fixture >= 8300u && t26_fixture <= 9323u)
                    mysmb_bowser_control_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 8300u));
                else if (t26_fixture >= 8120u && t26_fixture <= 8299u)
                    mysmb_bridge_collapse_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 8120u));
                else if (t26_fixture >= 7096u && t26_fixture <= 8119u)
                    mysmb_lakitu_movement_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 7096u));
                else if (t26_fixture >= 6584u && t26_fixture <= 7095u)
                    mysmb_flying_cheep_movement_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 6584u));
                else if (t26_fixture >= 6072u && t26_fixture <= 6583u)
                    mysmb_firebar_chain_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 6072u));
                else if (t26_fixture >= 5560u && t26_fixture <= 6071u)
                    mysmb_swimming_cheep_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 5560u));
                else if (t26_fixture >= 5432u && t26_fixture <= 5559u)
                    mysmb_bullet_movement_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 5432u));
                else if (t26_fixture >= 4920u && t26_fixture <= 5431u)
                    mysmb_bloober_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 4920u));
                else if (t26_fixture >= 4632u && t26_fixture <= 4919u)
                    mysmb_green_counter_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 4632u));
                else if (t26_fixture >= 4472u && t26_fixture <= 4631u)
                    mysmb_paratroopa_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 4472u));
                else if (t26_fixture >= 4116u && t26_fixture <= 4471u)
                    mysmb_hammer_movement_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 4116u));
                else if (t26_fixture >= 4052u && t26_fixture <= 4115u)
                    mysmb_podoboo_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 4052u));
                else if (t26_fixture >= 40000u && t26_fixture <= 40009u)
                    mysmb_large_platform_graphics_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 40000u));
                else if (t26_fixture >= 3960u && t26_fixture <= 4051u)
                    mysmb_special_actor_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 3960u));
                else if (t26_fixture >= 3834u && t26_fixture <= 3959u)
                    mysmb_normal_actor_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 3834u));
                else if (t26_fixture >= 3654u && t26_fixture <= 3833u)
                    mysmb_actor_dispatch_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 3654u));
                else if (t26_fixture >= 3414u && t26_fixture <= 3653u)
                    mysmb_platform_init_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 3414u));
                else if (t26_fixture >= 3218u && t26_fixture <= 3413u)
                    mysmb_small_init_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 3218u));
                else if (t26_fixture >= 3090u && t26_fixture <= 3217u)
                    mysmb_group_enemy_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 3090u));
                else if (t26_fixture >= 2908u && t26_fixture <= 3089u)
                    mysmb_bullet_swim_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 2908u));
                else if (t26_fixture >= 2788u && t26_fixture <= 2907u)
                    mysmb_fireworks_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 2788u));
                else if (t26_fixture >= 2628u && t26_fixture <= 2787u)
                    mysmb_bowser_flame_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 2628u));
                else if (t26_fixture >= 2476u && t26_fixture <= 2627u)
                    mysmb_flying_fish_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 2476u));
                else if (t26_fixture >= 2436u && t26_fixture <= 2475u)
                    mysmb_enemy_init_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 2274u));
                else if (t26_fixture >= 2356u && t26_fixture <= 2435u)
                    mysmb_lakitu_spiny_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 2356u));
                else if (t26_fixture >= 2194u && t26_fixture <= 2355u)
                    mysmb_enemy_init_fixture(driver->machine->ram,
                        (unsigned int)(t26_fixture - 2194u));
                else if (t26_fixture >= 2114u && t26_fixture <= 2193u)
                    mysmb_enemy_stream_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 2114u));
                else if (t26_fixture >= 2018u && t26_fixture <= 2113u)
                    mysmb_enemy_loop_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 2018u));
                else if (t26_fixture >= 1986u && t26_fixture <= 2017u)
                    mysmb_gravity_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1986u));
                else if (t26_fixture >= 1954u && t26_fixture <= 1985u)
                    mysmb_vertical_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1954u));
                else if (t26_fixture >= 1858u && t26_fixture <= 1953u)
                    mysmb_horizontal_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1858u));
                else if (t26_fixture >= 1826u && t26_fixture <= 1857u)
                    mysmb_block_replacement_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1826u));
                else if (t26_fixture >= 1794u && t26_fixture <= 1825u)
                    mysmb_block_lifetime_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1794u));
                else if (t26_fixture >= 1778u && t26_fixture <= 1793u)
                    mysmb_block_chunks_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1778u));
                else if (t26_fixture >= 1718u && t26_fixture <= 1777u)
                    mysmb_block_bump_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1718u));
                else if (t26_fixture >= 1646u && t26_fixture <= 1717u)
                    mysmb_block_head_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1646u));
                else if (t26_fixture >= 1596u && t26_fixture <= 1645u)
                    mysmb_power_up_actor_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1596u));
                else if (t26_fixture >= 1560u && t26_fixture <= 1595u)
                    mysmb_power_up_init_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1560u));
                else if (t26_fixture >= 41000u && t26_fixture <= 41005u)
                    mysmb_misc_lifetime_fixture(driver->machine->ram,
                        (lib_u8)(42u + t26_fixture - 41000u));
                else if (t26_fixture >= 1504u && t26_fixture <= 1559u)
                    mysmb_score_hud_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1504u));
                else if (t26_fixture >= 1462u && t26_fixture <= 1509u)
                    mysmb_misc_lifetime_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1462u));
                else if (t26_fixture >= 1414u && t26_fixture <= 1461u)
                    mysmb_coin_allocation_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1414u));
                else if (t26_fixture >= 1351u && t26_fixture <= 1413u)
                    mysmb_hammer_chain_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1351u));
                else if (t26_fixture >= 1309u && t26_fixture <= 1350u)
                    mysmb_vine_actor_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1309u));
                else if (t26_fixture >= 1293u && t26_fixture <= 1308u)
                    mysmb_vine_setup_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1293u));
                else if (t26_fixture >= 1261u && t26_fixture <= 1292u)
                    mysmb_jumpspring_core_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1261u));
                else if (t26_fixture >= 1245u && t26_fixture <= 1260u)
                    mysmb_timer_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1245u));
                else if (t26_fixture >= 1215u && t26_fixture <= 1244u)
                    mysmb_bubble_core_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1215u));
                else if (t26_fixture >= 1183u && t26_fixture <= 1214u)
                    mysmb_fireball_core_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1183u));
                else if (t26_fixture >= 1151u && t26_fixture <= 1182u)
                    mysmb_fireball_dispatch_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 1151u));
                else if (t26_fixture >= 905u && t26_fixture <= 1150u)
                    mysmb_player_movement_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 905u));
                else if (t26_fixture >= 876u && t26_fixture <= 904u)
                    mysmb_player_end_level_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 876u),driver->machine->cartridge->prg);
                else if (t26_fixture >= 854u && t26_fixture <= 875u)
                    mysmb_player_modes_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 854u));
                else if (t26_fixture >= 826u && t26_fixture <= 853u)
                    mysmb_player_transition_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 826u));
                else if (t26_fixture >= 776u && t26_fixture <= 825u)
                    mysmb_player_control_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 776u));
                else if (t26_fixture >= 741u && t26_fixture <= 775u)
                    mysmb_entrance_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 741u));
                else if (t26_fixture >= 717u && t26_fixture <= 740u)
                    mysmb_scroll_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 717u));
                else if (t26_fixture >= 652u && t26_fixture <= 716u)
                    mysmb_engine_normal_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 652u));
                else if (t26_fixture >= 642u && t26_fixture <= 651u)
                    mysmb_engine_warp_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 642u));
                else if (t26_fixture >= 617u && t26_fixture <= 641u)
                    mysmb_engine_cannon_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 617u));
                else if (t26_fixture >= 605u && t26_fixture <= 616u)
                    mysmb_engine_environment_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 605u));
                else if (t26_fixture >= 603u && t26_fixture <= 604u)
                    mysmb_engine_slots_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 603u));
                else if (t26_fixture >= 588u && t26_fixture <= 602u)
                    mysmb_engine_tail_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 588u));
                else if (t26_fixture >= 584u && t26_fixture <= 587u)
                    mysmb_game_entry_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 584u));
                else if (t26_fixture >= 581u && t26_fixture <= 583u)
                    mysmb_water_scene_fixture(driver->machine->ram, (lib_u8)(t26_fixture - 581u));
                else if (t26_fixture >= 578u && t26_fixture <= 580u)
                    mysmb_underground_scene_fixture(driver->machine->ram, (lib_u8)(t26_fixture - 578u));
                else if (t26_fixture >= 555u && t26_fixture <= 577u)
                    mysmb_ground_scene_fixture(driver->machine->ram, (lib_u8)(t26_fixture - 555u));
                else if (t26_fixture >= 548u && t26_fixture <= 554u)
                    mysmb_castle_scene_fixture(driver->machine->ram, (lib_u8)(t26_fixture - 548u));
                else if (t26_fixture >= 477u && t26_fixture <= 547u)
                    mysmb_area_pointer_fixture(driver->machine->ram, (lib_u8)(t26_fixture - 477u));
                else if (t26_fixture >= 429u && t26_fixture <= 476u)
                    mysmb_block_address_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 429u));
                else if (t26_fixture >= 397u && t26_fixture <= 428u)
                    mysmb_pipe_tail_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 397u));
                else if (t26_fixture >= 373u && t26_fixture <= 396u)
                    mysmb_parser_boundary_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 373u));
                else if (t26_fixture >= 353u && t26_fixture <= 372u)
                    mysmb_area_helper_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 353u));
                else if (t26_fixture >= 255u && t26_fixture <= 352u)
                    mysmb_hole_underpart_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 255u));
                else if (t26_fixture >= 183u && t26_fixture <= 254u)
                    mysmb_item_block_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 183u));
                else if (t26_fixture >= 175u && t26_fixture <= 182u)
                    mysmb_jumpspring_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 175u));
                else if (t26_fixture >= 163u && t26_fixture <= 174u)
                    mysmb_staircase_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 163u));
                else if (t26_fixture >= 133u && t26_fixture <= 162u)
                    mysmb_cannon_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 133u));
                else if (t26_fixture >= 101u && t26_fixture <= 132u)
                    mysmb_block_row_column_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 101u));
                else if (t26_fixture >= 95u && t26_fixture <= 100u)
                    mysmb_castle_column_fixture(driver->machine->ram,
                        (lib_u8)(t26_fixture - 95u));
                else if (t26_fixture == 93u)
                    mysmb_reference_apply_t22_flagpole_fixture(driver->machine->ram);
                else if (t26_fixture == 94u)
                {
                    mysmb_reference_apply_t22_flagpole_fixture(driver->machine->ram);
                    t22_flagpole_score_pending = LIB_TRUE;
                }
                else if (t26_fixture == 90u)
                    mysmb_reference_apply_t29_geometry_castle_fixture(
                        driver->machine->ram);
                else if (t26_fixture == 91u)
                {
                    mysmb_reference_apply_t29_geometry_castle_fixture(
                        driver->machine->ram);
                    t29_vertical_pipe_pending = LIB_TRUE;
                }
                else if (t26_fixture == 92u)
                    mysmb_reference_apply_t29_final_question_fixture(
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
            if (t26_fixture >= 581u && t26_fixture <= 583u && elapsed == warmup_frames + 1u)
                mysmb_water_scene_continue(driver->machine->ram);
            if (t26_fixture >= 578u && t26_fixture <= 580u && elapsed == warmup_frames + 1u)
                mysmb_underground_scene_continue(driver->machine->ram);
            if ((t26_fixture >= 555u && t26_fixture <= 577u && elapsed == warmup_frames + 1u) ||
                (t26_fixture == 577u && elapsed == warmup_frames + 129u))
                mysmb_ground_scene_continue(driver->machine->ram);
            if (t26_fixture >= 548u && t26_fixture <= 554u && elapsed == warmup_frames + 1u)
                mysmb_castle_scene_continue(driver->machine->ram);
            if (t22_flagpole_score_pending &&
                elapsed == warmup_frames + 1u) {
                mysmb_reference_apply_t22_flagpole_score_fixture(
                    driver->machine->ram);
                t22_flagpole_score_pending = LIB_FALSE;
            }
            if (!mysmb_reference_script_buttons(script, elapsed, total_frames,
                                                &buttons)) break;
            core_controller_set_buttons(&driver->machine->controller, (lib_u8)buttons);
        }
        before_pc = driver->machine->pc;
        if (elapsed >= warmup_frames &&
            ((t26_fixture >= 4372u && t26_fixture <= 4403u && before_pc == 0xc9d8u) ||
             (t26_fixture >= 4416u && t26_fixture <= 4423u && before_pc == 0xca77u)) &&
            driver->machine->x == mysmb_hammer_movement_slot(
                (unsigned int)(t26_fixture - 4116u)))
            mysmb_hammer_movement_entry_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 4116u));
        /* Residual NoFrenzyCode: controlled RAM input at a naturally reached
         * entry, independent of observation. Never modify PC, stack or ROM. */
        if (elapsed >= warmup_frames && t26_fixture >= 3384u &&
            t26_fixture <= 3389u && before_pc == 0xc7a0u &&
            driver->machine->x == mysmb_small_init_slot(
                (unsigned int)(t26_fixture - 3218u)))
            driver->machine->ram[0x16u + driver->machine->x] = 0x13u;
        /* S8 controlled RAM input at the naturally reached actor entry.
         * Applied independently of observation mode; no CPU/ROM/output patch. */
        if (elapsed >= warmup_frames && t26_fixture >= 6072u && t26_fixture <= 6075u &&
            before_pc == 0xcd3cu && driver->machine->x ==
                mysmb_firebar_chain_slot((unsigned int)(t26_fixture - 6072u)))
            driver->machine->ram[0x00b5u] = 2u;
        /* Four additional input cases align the player sprite with the
         * center ball after the normal player phase, including power loss. */
        if (elapsed >= warmup_frames && t26_fixture >= 6076u && t26_fixture <= 6079u &&
            before_pc == 0xcd3cu && driver->machine->x ==
                mysmb_firebar_chain_slot((unsigned int)(t26_fixture - 6072u))) {
            driver->machine->ram[0x0207u] = (lib_u8)(
                driver->machine->ram[0x0087u + driver->machine->x] -
                driver->machine->ram[0x071cu] - 4u);
            driver->machine->ram[0x00ceu] = (lib_u8)(
                driver->machine->ram[0x00cfu + driver->machine->x] - 0x18u);
            driver->machine->ram[0x0754u] = 1u;
            driver->machine->ram[0x0756u] = 1u;
        }
        if (elapsed >= warmup_frames && t26_fixture >= 7096u && t26_fixture <= 8119u &&
            (before_pc == 0xcf28u || before_pc == 0xcf6cu) &&
            driver->machine->x == mysmb_lakitu_movement_slot((unsigned int)(t26_fixture - 7096u)))
            mysmb_lakitu_movement_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 7096u), before_pc);
        if (elapsed >= warmup_frames && t26_fixture >= 8300u && t26_fixture <= 9323u &&
            before_pc == 0xd065u && driver->machine->x ==
                mysmb_bowser_control_slot((unsigned int)(t26_fixture - 8300u)))
            mysmb_bowser_control_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 8300u));
        if (elapsed >= warmup_frames && t26_fixture >= 9324u && t26_fixture <= 9835u &&
            before_pc == 0xd17bu && driver->machine->x ==
                mysmb_bowser_graphics_slot((unsigned int)(t26_fixture - 9324u)))
            mysmb_bowser_graphics_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 9324u));
        if (elapsed >= warmup_frames && t26_fixture >= 9836u && t26_fixture <= 10859u &&
            before_pc == 0xd1ebu && driver->machine->x ==
                mysmb_flame_actor_slot((unsigned int)(t26_fixture - 9836u)))
            mysmb_flame_actor_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 9836u));
        if (elapsed >= warmup_frames && t26_fixture >= 10860u && t26_fixture <= 11371u &&
            before_pc == 0xd295u && driver->machine->x ==
                mysmb_fireworks_lifetime_slot((unsigned int)(t26_fixture - 10860u)))
            mysmb_fireworks_lifetime_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 10860u));
        if (elapsed >= warmup_frames && t26_fixture >= 11372u && t26_fixture <= 12395u &&
            before_pc == 0xd2d9u && driver->machine->x ==
                mysmb_star_flag_slot((unsigned int)(t26_fixture - 11372u)))
            mysmb_star_flag_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 11372u));
        if (elapsed >= warmup_frames && t26_fixture >= 12396u && t26_fixture <= 12907u &&
            before_pc == 0xd3b0u && driver->machine->x ==
                mysmb_piranha_movement_slot((unsigned int)(t26_fixture - 12396u)))
            mysmb_piranha_movement_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 12396u));
        if (elapsed >= warmup_frames && t26_fixture >= 12908u && t26_fixture <= 13931u &&
            before_pc == 0xd432u && driver->machine->x ==
                mysmb_balance_platform_slot((unsigned int)(t26_fixture - 12908u)))
            mysmb_balance_platform_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 12908u));
        if (elapsed >= warmup_frames && t26_fixture >= 13932u && t26_fixture <= 14443u &&
            before_pc == 0xd5d3u && driver->machine->x ==
                mysmb_vertical_platform_slot((unsigned int)(t26_fixture - 13932u)))
            mysmb_vertical_platform_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 13932u));
        if (elapsed >= warmup_frames && t26_fixture >= 14444u && t26_fixture <= 15211u &&
            before_pc == mysmb_horizontal_platform_entry((unsigned int)(t26_fixture - 14444u)) && driver->machine->x ==
                mysmb_horizontal_platform_slot((unsigned int)(t26_fixture - 14444u)))
            mysmb_horizontal_platform_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 14444u));
        if (elapsed >= warmup_frames && t26_fixture >= 15212u && t26_fixture <= 15723u &&
            before_pc == mysmb_lift_platform_entry((unsigned int)(t26_fixture - 15212u)) && driver->machine->x ==
                mysmb_lift_platform_slot((unsigned int)(t26_fixture - 15212u)))
            mysmb_lift_platform_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 15212u));
        if (elapsed >= warmup_frames && t26_fixture >= 15724u && t26_fixture <= 16747u &&
            before_pc == 0xd67au && driver->machine->x ==
                mysmb_offscreen_bounds_slot((unsigned int)(t26_fixture - 15724u)))
            mysmb_offscreen_bounds_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 15724u));
        if (elapsed >= warmup_frames && t26_fixture >= 16748u && t26_fixture <= 17771u &&
            before_pc == 0xd6d9u && driver->machine->x ==
                mysmb_fireball_enemy_scan_slot((unsigned int)(t26_fixture - 16748u)))
            mysmb_fireball_enemy_scan_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 16748u));
        if (elapsed >= warmup_frames && t26_fixture >= 17772u && t26_fixture <= 18283u) {
            if (before_pc == 0xd6d9u && driver->machine->x == 0u)
                mysmb_fireball_enemy_scan_inputs(driver->machine->ram,0u);
            if (before_pc == 0xd73eu && driver->machine->x == 4u)
                mysmb_fireball_hit_inputs(driver->machine->ram,
                    (unsigned int)(t26_fixture - 17772u));
        }
        if (elapsed >= warmup_frames && t26_fixture >= 18284u && t26_fixture <= 18571u &&
            before_pc == 0xd7c4u && driver->machine->x ==
                mysmb_hammer_contact_slot((unsigned int)(t26_fixture - 18284u)))
            mysmb_hammer_contact_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 18284u));
        if (elapsed >= warmup_frames && t26_fixture >= 18572u && t26_fixture <= 18699u && driver->machine->x == 5u) {
            if (before_pc == 0xd853u) mysmb_powerup_pickup_contact(driver->machine->ram);
            if (before_pc == 0xd800u) mysmb_powerup_pickup_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 18572u));
        }
        if (elapsed >= warmup_frames && t26_fixture >= 18700u && t26_fixture <= 20299u &&
            before_pc == 0xd853u && driver->machine->x == 5u)
            mysmb_player_enemy_contact_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 18700u));
        if (elapsed >= warmup_frames && t26_fixture >= 20300u && t26_fixture <= 21323u &&
            before_pc == 0xda33u && driver->machine->x ==
                mysmb_enemy_pair_slot((unsigned int)(t26_fixture - 20300u)))
            mysmb_enemy_pair_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 20300u));
        if (elapsed >= warmup_frames && t26_fixture >= 21324u && t26_fixture <= 23371u &&
            before_pc == (t26_fixture < 22348u ? 0xdb45u : 0xdb7bu) && driver->machine->x ==
                mysmb_platform_collision_slot((unsigned int)(t26_fixture - 21324u)))
            mysmb_platform_collision_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 21324u));
        if (elapsed >= warmup_frames && t26_fixture >= 26654u && t26_fixture <= 27677u) {
            if (before_pc == 0xdc64u) mysmb_player_terrain_inputs(driver->machine->ram, 681u);
            if (before_pc == 0xdf4bu && movement_snapshot_phase == 0u)
                mysmb_impede_inputs(driver->machine->ram, (unsigned int)(t26_fixture - 26654u));
        }
        if (elapsed >= warmup_frames && t26_fixture >= 26142u && t26_fixture <= 26653u) {
            if (before_pc == 0xdc64u) mysmb_player_terrain_inputs(driver->machine->ram, 4u);
            if (before_pc == 0xdee8u)
                mysmb_pipe_entry_inputs(driver->machine->ram, (unsigned int)(t26_fixture - 26142u));
        }
        if (elapsed >= warmup_frames && t26_fixture >= 25118u && t26_fixture <= 26141u) {
            if (before_pc == 0xdc64u)
                mysmb_climbing_root_inputs(driver->machine->ram, (unsigned int)(t26_fixture - 25118u));
            if (before_pc == 0xde2eu)
                mysmb_climbing_inputs(driver->machine->ram, (unsigned int)(t26_fixture - 25118u));
        }
        if (elapsed >= warmup_frames && t26_fixture >= 24990u && t26_fixture <= 25117u) {
            if (before_pc == 0xdc64u)
                mysmb_player_terrain_inputs(driver->machine->ram, (t26_fixture & 1u) ? 0u : 2u);
            if (before_pc == ((t26_fixture & 1u) ? 0xde0eu : 0xde05u))
                mysmb_terrain_metatile_inputs(driver->machine->ram,
                    (unsigned int)(t26_fixture - 24990u));
        }
        if (elapsed >= warmup_frames && t26_fixture >= 23956u && t26_fixture <= 24989u &&
            before_pc == 0xdc64u)
            mysmb_player_terrain_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 23956u));
        if (elapsed >= warmup_frames && t26_fixture >= 23372u && t26_fixture <= 23955u &&
            before_pc == (mysmb_platform_position_small((unsigned int)(t26_fixture - 23372u)) ? 0xd655u : 0xd64fu) &&
            driver->machine->x == mysmb_platform_position_slot((unsigned int)(t26_fixture - 23372u)))
            mysmb_platform_position_inputs(driver->machine->ram,
                (unsigned int)(t26_fixture - 23372u));
        if (elapsed >= warmup_frames && t26_fixture >= 27678u && t26_fixture <= 29725u) {
            mysmb_background_inputs(driver->machine->ram, before_pc,
                driver->machine->x, (unsigned int)(t26_fixture - 27678u));
            if (enemy_background_path != NULL &&
                !background_observe(driver->machine->ram, before_pc,
                    driver->machine->a, driver->machine->x, driver->machine->y,
                    driver->machine->p, driver->machine->s,
                    (unsigned int)(t26_fixture - 27678u))) return 69;
        }
        if (elapsed >= warmup_frames && t26_fixture >= 29726u && t26_fixture <= 30749u) {
            mysmb_landing_inputs(driver->machine->ram, before_pc,
                driver->machine->x, (unsigned int)(t26_fixture - 29726u));
            if (enemy_landing_path != NULL &&
                !background_observe(driver->machine->ram, before_pc,
                    driver->machine->a, driver->machine->x, driver->machine->y,
                    driver->machine->p, driver->machine->s,
                    (unsigned int)(t26_fixture - 29726u))) return 69;
        }
        if (metatile_path != NULL && elapsed >= warmup_frames &&
            !metatile_observe(driver->machine->ram, before_pc,
                driver->machine->a, driver->machine->x, driver->machine->y,
                driver->machine->p, driver->machine->s)) return 69;
        /* T45 S3: vary only the input FrameCounter at a naturally reached
         * projectile graphics entry. CPU state and ROM remain untouched. */
        if (elapsed >= warmup_frames && projectile_frame != 0xffffffffu &&
            (before_pc == 0xecdeu || before_pc == 0xecedu))
            driver->machine->ram[9u] = (lib_u8)projectile_frame;
        /* T45 S5: vary only PlayerGfxHandler input RAM after its natural
         * GameEngine call. Preserve original PC, registers, stack and PRG. */
        if (elapsed >= warmup_frames && background_snapshot == 11u &&
            bubble_player_variant != 0xffffffffu && before_pc == 0xeee9u) {
            driver->machine->ram[0x001du] =
                (lib_u8)((bubble_player_variant & 8u) != 0u ? 0u : 1u);
            driver->machine->ram[0x0704u] = 1u;
            driver->machine->ram[0x0033u] =
                (lib_u8)((bubble_player_variant & 1u) != 0u ? 2u : 1u);
            driver->machine->ram[0x0754u] =
                (lib_u8)((bubble_player_variant & 2u) != 0u ? 1u : 0u);
            driver->machine->ram[9u] =
                (lib_u8)((bubble_player_variant & 4u) != 0u ? 4u : 0u);
            driver->machine->ram[0x070bu] = 0u;
            driver->machine->ram[0x079eu] = 0u;
            driver->machine->ram[0x070du] = 0u;
            driver->machine->ram[0x0781u] = 0u;
        }
        /* T46 S1: vary only the naturally reached player handler's input
         * RAM to expose its dispatch and offscreen branch successors. */
        if (elapsed >= warmup_frames && background_snapshot == 11u &&
            player_control_variant != 0xffffffffu && before_pc == 0xeee9u) {
            lib_u8 *ram = driver->machine->ram;
            unsigned int choice = player_control_variant;
            ram[0x070bu] = 0u;
            ram[0x079eu] = 0u;
            if (choice == 1u || choice == 2u) {
                ram[0x079eu] = 2u;
                ram[9u] = (lib_u8)(choice == 1u ? 1u : 0u);
            }
            if (choice == 3u) ram[0x000eu] = 0x0bu;
            if (choice == 4u) {
                ram[0x070bu] = 1u;
                ram[0x070du] = 1u;
                ram[9u] = 1u;
            }
            if (choice == 5u || choice == 6u) {
                ram[0x001du] = 1u;
                ram[0x0704u] = 1u;
                ram[0x0754u] = (lib_u8)(choice == 6u ? 1u : 0u);
                ram[9u] = 0u;
            }
            if (choice >= 7u && choice <= 9u) {
                ram[0x0711u] = (lib_u8)(choice == 9u ? 2u : 5u);
                ram[0x0781u] = (lib_u8)(choice == 9u ? 5u : 2u);
                ram[0x0057u] = (lib_u8)(choice == 8u ? 1u : 0u);
                ram[0x000cu] = 0u;
            }
            if (choice == 10u) ram[0x03d0u] = 0xf0u;
            if (choice == 11u) ram[0x03d0u] = 0x50u;
        }
        /* T46 S2: seed only OAM input bytes when the world/lives caller
         * naturally enters DrawPlayer_Intermediate. */
        if (elapsed >= warmup_frames && t26_fixture == 23u &&
            intermediate_player_variant != 0xffffffffu &&
            before_pc == 0xefa4u) {
            driver->machine->ram[0x0226u] =
                (lib_u8)(intermediate_player_variant == 0u ? 0u :
                (intermediate_player_variant == 1u ? 3u :
                (intermediate_player_variant == 2u ? 0x80u : 0xc3u)));
            driver->machine->ram[0x0222u] =
                (lib_u8)(intermediate_player_variant == 0u ? 0u : 0x20u);
        }
        if (elapsed >= warmup_frames && background_snapshot == 11u &&
            bubble_draw_variant != 0xffffffffu && before_pc == 0xede1u) {
            driver->machine->ram[0x00b5u] =
                (lib_u8)(bubble_draw_variant == 0u ? 0u :
                         (bubble_draw_variant == 3u ? 2u : 1u));
            driver->machine->ram[0x03d3u] =
                (lib_u8)(bubble_draw_variant == 1u ? 8u : 0u);
        }
        /* T45 S5: one naturally called PlayerGfxHandler for each of the
         * 26 eight-tile PlayerGraphicsTable poses. Only input RAM changes. */
        if (elapsed >= warmup_frames && background_snapshot == 11u &&
            player_table_variant != 0xffffffffu && before_pc == 0xeee9u) {
            lib_u8 *ram = driver->machine->ram;
            unsigned int pose = player_table_variant;
            ram[0x001du] = 0u; ram[0x0704u] = 0u; ram[0x0754u] = 0u;
            ram[0x0714u] = 0u; ram[0x0057u] = 0u; ram[0x000cu] = 0u;
            ram[0x0700u] = 0u; ram[0x0045u] = 1u; ram[0x0033u] = 1u;
            ram[0x070du] = 0u; ram[0x0781u] = 1u; ram[0x0782u] = 0u;
            ram[0x000au] = 0u; ram[0x0711u] = 0u; ram[0x070bu] = 0u;
            ram[0x000eu] = 8u; ram[0x079eu] = 0u; ram[9u] = 1u;
            ram[0x009fu] = 0u;
            if (pose <= 2u || (pose >= 12u && pose <= 14u)) {
                ram[0x0057u] = 1u;
                ram[0x000cu] = 1u;
                ram[0x070du] = (lib_u8)(pose <= 2u ? pose : pose - 12u);
            }
            if (pose == 3u || pose == 15u) {
                ram[0x0057u] = 1u;
                ram[0x000cu] = 1u;
                ram[0x0700u] = 9u;
                ram[0x0045u] = 2u;
            }
            if (pose == 4u || pose == 16u) ram[0x001du] = 1u;
            if ((pose >= 5u && pose <= 7u) ||
                (pose >= 17u && pose <= 19u)) {
                ram[0x001du] = 1u;
                ram[0x0704u] = 1u;
                ram[0x0782u] = 1u;
                ram[0x070du] = (lib_u8)(pose <= 7u ? pose - 5u : pose - 17u);
            }
            if ((pose >= 8u && pose <= 9u) ||
                (pose >= 20u && pose <= 21u)) {
                ram[0x001du] = 3u;
                ram[0x009fu] = 1u;
                ram[0x070du] = (lib_u8)(pose == 9u || pose == 21u ? 1u : 0u);
            }
            if (pose == 10u) ram[0x0714u] = 1u;
            if (pose == 11u) ram[0x0711u] = 2u;
            if (pose >= 12u && pose <= 23u) ram[0x0754u] = 1u;
            if (pose == 22u) ram[0x000eu] = 0x0bu;
            if (pose == 24u) {
                ram[0x070bu] = 1u;
                ram[0x070du] = 1u;
            }
        }
        /* T46 S3: vary only RAM at the original ProcessPlayerAction entry.
         * The GameEngine call, CPU PC/registers/stack and ROM are unaltered. */
        if (elapsed >= warmup_frames && background_snapshot == 11u &&
            player_action_variant != 0xffffffffu && before_pc == 0xefecu) {
            lib_u8 *ram = driver->machine->ram;
            unsigned int v = player_action_variant;
            ram[0x001du] = 0u; ram[0x0704u] = 0u; ram[0x0754u] = 0u;
            ram[0x0714u] = 0u; ram[0x0057u] = 0u; ram[0x000cu] = 0u;
            ram[0x0700u] = 0u; ram[0x0045u] = 1u; ram[0x0033u] = 1u;
            ram[0x070du] = 0u; ram[0x0781u] = 1u; ram[0x0782u] = 0u;
            ram[0x070cu] = 3u; ram[0x000au] = 0u; ram[0x009fu] = 0u;
            if (v == 1u) { ram[0x001du] = 2u; ram[0x070du] = 1u; }
            if (v == 2u || v == 3u || v == 14u) {
                ram[0x001du] = 3u;
                ram[0x009fu] = (lib_u8)(v == 2u ? 0u : 1u);
                ram[0x0781u] = 0u;
                ram[0x070du] = 1u;
            }
            if (v == 4u) ram[0x0714u] = 1u;
            if (v == 5u || v == 6u || v == 13u) {
                ram[0x0057u] = 1u; ram[0x000cu] = 1u;
                ram[0x0781u] = 0u;
                ram[0x070du] = 2u;
                if (v == 6u) {
                    ram[0x0700u] = 9u;
                    ram[0x0045u] = 2u;
                }
            }
            if (v >= 7u && v <= 12u) ram[0x001du] = 1u;
            if (v == 8u) ram[0x0714u] = 1u;
            if (v >= 9u && v <= 12u) ram[0x0704u] = 1u;
            if (v == 10u) ram[0x000au] = 0x80u;
            if (v == 11u) ram[0x0782u] = 1u;
            if (v == 12u) ram[0x070du] = 1u;
            if (v == 13u || v == 14u || v == 15u)
                ram[0x0754u] = 1u;
            if (v == 16u || v == 17u) {
                ram[0x001du] = 2u;
                ram[0x070du] = (lib_u8)(v == 16u ? 0x20u : 0x3fu);
            }
        }
        /* T46 S4: seed only player graphics input RAM at a naturally
         * reached handler and attribute child; CPU and ROM are unchanged. */
        if (elapsed >= warmup_frames && background_snapshot == 11u &&
            player_size_variant != 0xffffffffu && before_pc == 0xeee9u) {
            lib_u8 *ram = driver->machine->ram;
            unsigned int v = player_size_variant;
            ram[0x000eu] = 8u;
            ram[0x070bu] = 1u;
            ram[0x079eu] = 0u;
            ram[0x0711u] = 0u;
            ram[0x0754u] = (lib_u8)((v >= 10u && v < 20u) || v >= 22u);
            ram[0x070du] = (lib_u8)(v < 20u ? v % 10u :
                                    (v & 1u) != 0u ? 9u : 8u);
            ram[9u] = (lib_u8)(v < 20u ? 1u : 0u);
        }
        if (elapsed >= warmup_frames && background_snapshot == 11u &&
            player_attribute_variant != 0xffffffffu && before_pc == 0xf0e9u) {
            static const lib_u8 offsets[8] = {
                0u, 0x50u, 0xb8u, 0xc0u, 0xc8u, 0u, 0u, 0u
            };
            lib_u8 *ram = driver->machine->ram;
            unsigned int v = player_attribute_variant;
            ram[0x000eu] = (lib_u8)(v == 5u ? 0x0bu : 8u);
            ram[0x06d5u] = offsets[v];
            ram[0x06e4u] = 0x20u;
            ram[0x0232u] = 0xc3u;
            ram[0x0236u] = 0x83u;
            ram[0x023au] = 0xc2u;
            ram[0x023eu] = 0x82u;
        }
        /* T45 S4: vary the ROM graphics consumer's input RAM only after the
         * original actor reaches DrawSmallPlatform. */
        if (elapsed >= warmup_frames && background_snapshot == 43u &&
            small_platform_variant != 0xffffffffu && before_pc == 0xed66u &&
            driver->machine->x == driver->machine->ram[8u]) {
            static const lib_u8 y_values[8] = {
                0x10u, 0x1fu, 0x20u, 0x7fu,
                0x80u, 0x9fu, 0xa0u, 0xffu
            };
            lib_u8 slot = driver->machine->x;
            driver->machine->ram[0x00cfu + slot] =
                y_values[small_platform_variant & 7u];
            driver->machine->ram[0x03d1u] =
                (lib_u8)((small_platform_variant >> 3u) << 1u);
            driver->machine->ram[0x03aeu] =
                (lib_u8)((small_platform_variant & 1u) != 0u ? 0xf8u : 0x30u);
            driver->machine->ram[0x03b9u] = 0x7du;
        }
        /* T44 S8: controlled RAM at the original EnemyGfxHandler entry.
         * CPU registers, PC, stack, code and parent call order are untouched. */
        if (elapsed >= warmup_frames && background_snapshot == 42u &&
            enemy_graphics_variant != 0xffffffffu && before_pc == 0xe87du &&
            driver->machine->x == driver->machine->ram[8u]) {
            static const lib_u8 states[20] = {
                0u, 2u, 4u, 5u, 8u, 0x20u, 0x40u, 0x80u,
                0xa0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u,
                0u, 0u, 0u, 0u
            };
            lib_u8 slot = driver->machine->x;
            driver->machine->ram[0x001eu + slot] =
                states[enemy_graphics_variant];
            driver->machine->ram[9u] =
                enemy_graphics_variant == 10u ? 8u : 0u;
            driver->machine->ram[0x0747u] =
                enemy_graphics_variant == 15u ? 1u : 0u;
            driver->machine->ram[0x0796u + slot] =
                enemy_graphics_variant == 13u ? 5u :
                (enemy_graphics_variant == 12u ? 1u : 0u);
            driver->machine->ram[0x078fu] =
                enemy_graphics_variant == 14u ? 0x10u : 0u;
            driver->machine->ram[0x078au + slot] = 1u;
            driver->machine->ram[0x0058u + slot] =
                enemy_graphics_variant == 11u ? 0x80u : 0u;
            driver->machine->ram[0x00a0u + slot] = 0u;
            /* T45 S1: preserve the ROM-computed offscreen bits unless a
             * controlled row-mask case is selected at this original entry. */
            if (enemy_graphics_variant >= 16u)
                driver->machine->ram[0x03d1u] =
                    (lib_u8)(enemy_graphics_variant == 16u ? 0x20u :
                    (enemy_graphics_variant == 17u ? 0x40u :
                    (enemy_graphics_variant == 18u ? 0x80u : 0xccu)));
        }
        /* T45 S2: vary RAM only when the original block/chunk graphics
         * entry is reached by BlockObjectsCore.  CPU/stack/ROM are intact. */
        if (elapsed >= warmup_frames && background_snapshot == 25u &&
            block_graphics_variant != 0xffffffffu &&
            driver->machine->x == driver->machine->ram[8u]) {
            lib_u8 slot = driver->machine->x;
            if (before_pc == 0xebd1u && block_graphics_variant < 4u) {
                driver->machine->ram[0x074eu] =
                    block_graphics_variant < 2u ? 1u : 0u;
                driver->machine->ram[0x03e8u + slot] =
                    (block_graphics_variant & 1u) != 0u ? 0x51u : 0xc4u;
                driver->machine->ram[0x03d4u] =
                    block_graphics_variant == 2u ? 0x0cu :
                    (block_graphics_variant == 3u ? 0x04u : 0u);
            }
            if (before_pc == 0xec53u && block_graphics_variant >= 4u) {
                driver->machine->ram[0x000eu] =
                    block_graphics_variant == 4u ? 5u : 8u;
                if (block_graphics_variant >= 5u) {
                    driver->machine->ram[0x03d4u] =
                        block_graphics_variant == 5u ? 0x88u : 0u;
                    driver->machine->ram[0x03f1u + slot] = 0u;
                    driver->machine->ram[0x071cu] = 0x20u;
                    driver->machine->ram[0x03b1u] =
                        block_graphics_variant == 6u ? 0xf0u : 0x10u;
                    driver->machine->ram[0x03b2u] = 0x10u;
                }
            }
        }
        /* T32 observes the real control caller and immediate children.
         * Return PCs/depths come only from the original hardware stack. */
        if ((((background_snapshot >= 4u && background_snapshot <= 79u) &&
             t26_fixture >= 776u && t26_fixture <= 27677u) ||
             (background_snapshot == 80u && t26_fixture >= 40000u &&
              t26_fixture <= 40009u) ||
             (background_snapshot == 18u && t26_fixture >= 41000u &&
              t26_fixture <= 41005u)) && movement_snapshot_path != NULL &&
            elapsed >= warmup_frames) {
            if (movement_snapshot_phase == 0u &&
                before_pc == (background_snapshot == 4u ? 0xb0e9u : transition_entry) &&
                (background_snapshot != 73u || driver->machine->x ==
                    mysmb_platform_position_slot((unsigned int)(t26_fixture - 23372u))) &&
                (background_snapshot != 72u || driver->machine->x ==
                    mysmb_platform_collision_slot((unsigned int)(t26_fixture - 21324u))) &&
                (background_snapshot != 71u || driver->machine->x ==
                    mysmb_enemy_pair_slot((unsigned int)(t26_fixture - 20300u))) &&
                (background_snapshot != 70u || driver->machine->x == 5u) &&
                (background_snapshot != 69u || driver->machine->x == 5u) &&
                (background_snapshot != 68u || driver->machine->x ==
                    mysmb_hammer_contact_slot((unsigned int)(t26_fixture - 18284u))) &&
                (background_snapshot != 67u || driver->machine->x == 4u) &&
                (background_snapshot != 66u || driver->machine->x ==
                    mysmb_fireball_enemy_scan_slot((unsigned int)(t26_fixture - 16748u))) &&
                (background_snapshot != 65u || driver->machine->x ==
                    mysmb_offscreen_bounds_slot((unsigned int)(t26_fixture - 15724u))) &&
                (background_snapshot != 64u || driver->machine->x ==
                    mysmb_lift_platform_slot((unsigned int)(t26_fixture - 15212u))) &&
                (background_snapshot != 63u || driver->machine->x ==
                    mysmb_horizontal_platform_slot((unsigned int)(t26_fixture - 14444u))) &&
                (background_snapshot != 62u || driver->machine->x ==
                    mysmb_vertical_platform_slot((unsigned int)(t26_fixture - 13932u))) &&
                (background_snapshot != 61u || driver->machine->x ==
                    mysmb_balance_platform_slot((unsigned int)(t26_fixture - 12908u))) &&
                (background_snapshot != 60u || driver->machine->x ==
                    mysmb_piranha_movement_slot((unsigned int)(t26_fixture - 12396u))) &&
                (background_snapshot != 59u || driver->machine->x ==
                    mysmb_star_flag_slot((unsigned int)(t26_fixture - 11372u))) &&
                (background_snapshot != 58u || driver->machine->x ==
                    mysmb_fireworks_lifetime_slot((unsigned int)(t26_fixture - 10860u))) &&
                (background_snapshot != 57u || driver->machine->x ==
                    mysmb_flame_actor_slot((unsigned int)(t26_fixture - 9836u))) &&
                (background_snapshot != 56u || driver->machine->x ==
                    mysmb_bowser_graphics_slot((unsigned int)(t26_fixture - 9324u))) &&
                (background_snapshot != 55u || driver->machine->x ==
                    mysmb_bowser_control_slot((unsigned int)(t26_fixture - 8300u))) &&
                (background_snapshot != 53u || driver->machine->ram[8u] ==
                    mysmb_lakitu_movement_slot((unsigned int)(t26_fixture - 7096u))) &&
                (background_snapshot != 52u || driver->machine->ram[8u] ==
                    mysmb_flying_cheep_movement_slot((unsigned int)(t26_fixture - 6584u))) &&
                (background_snapshot != 51u || driver->machine->ram[8u] ==
                    mysmb_firebar_chain_slot((unsigned int)(t26_fixture - 6072u))) &&
                (background_snapshot != 50u || driver->machine->ram[8u] ==
                    mysmb_swimming_cheep_slot((unsigned int)(t26_fixture - 5560u))) &&
                (background_snapshot != 49u || driver->machine->ram[8u] ==
                    mysmb_bullet_movement_slot((unsigned int)(t26_fixture - 5432u))) &&
                (background_snapshot != 48u || driver->machine->ram[8u] ==
                    mysmb_bloober_slot((unsigned int)(t26_fixture - 4920u))) &&
                (background_snapshot != 47u || driver->machine->ram[8u] ==
                    mysmb_green_counter_slot((unsigned int)(t26_fixture - 4632u))) &&
                (background_snapshot != 46u || driver->machine->ram[8u] ==
                    mysmb_paratroopa_slot((unsigned int)(t26_fixture - 4472u))) &&
                (background_snapshot != 45u || driver->machine->ram[8u] ==
                    mysmb_hammer_movement_slot((unsigned int)(t26_fixture - 4116u))) &&
                (background_snapshot != 44u || driver->machine->ram[8u] ==
                    mysmb_podoboo_slot((unsigned int)(t26_fixture - 4052u))) &&
                (background_snapshot != 43u || driver->machine->ram[8u] ==
                    mysmb_special_actor_slot((unsigned int)(t26_fixture - 3960u))) &&
                (background_snapshot != 42u || driver->machine->ram[8u] ==
                    mysmb_normal_actor_slot((unsigned int)(t26_fixture - 3834u))) &&
                (background_snapshot != 41u || driver->machine->ram[8u] ==
                    mysmb_actor_dispatch_slot((unsigned int)(t26_fixture - 3654u))) &&
                (background_snapshot != 40u || driver->machine->x ==
                    mysmb_platform_init_slot((unsigned int)(t26_fixture - 3414u))) &&
                (background_snapshot != 39u || driver->machine->x ==
                    mysmb_small_init_slot((unsigned int)(t26_fixture - 3218u))) &&
                (background_snapshot != 37u || driver->machine->x ==
                    mysmb_bullet_swim_slot((unsigned int)(t26_fixture - 2908u))) &&
                (background_snapshot != 36u || driver->machine->x ==
                    mysmb_fireworks_slot((unsigned int)(t26_fixture - 2788u))) &&
                (background_snapshot != 35u || driver->machine->x ==
                    mysmb_bowser_flame_slot((unsigned int)(t26_fixture - 2628u))) &&
                (background_snapshot != 34u || driver->machine->x ==
                    mysmb_flying_fish_slot((unsigned int)(t26_fixture - 2476u))) &&
                (background_snapshot != 33u || driver->machine->x ==
                    (t26_fixture == 2357u ? 5u : 0u)) &&
                (background_snapshot != 32u || driver->machine->x ==
                    mysmb_enemy_init_slot((unsigned int)(t26_fixture -
                        (t26_fixture >= 2436u ? 2274u : 2194u)))) &&
                (background_snapshot != 31u || driver->machine->x == ((t26_fixture-2114u)%8u==5u?5u:0u)) &&
                (background_snapshot != 30u || driver->machine->x == 0u) &&
                (background_snapshot != 29u || t26_fixture < 2010u || driver->machine->x == 1u) &&
                (background_snapshot != 27u || t26_fixture < 1922u || driver->machine->x == 10u) &&
                (background_snapshot != 25u || driver->machine->x == (t26_fixture - 1794u) % 2u) &&
                (background_snapshot != 16u || driver->machine->x ==
                    (t26_fixture < 1378u ? 0u : (t26_fixture - 1378u) % 9u)) &&
                (background_snapshot != 15u || driver->machine->x ==
                    (t26_fixture < 1314u ? t26_fixture - 1309u : 5u)) &&
                (background_snapshot != 10u || driver->machine->x == (t26_fixture - 1183u) / 16u) &&
                (background_snapshot != 11u || driver->machine->x ==
                    (t26_fixture < 1239u ? (t26_fixture - 1215u) / 8u : (t26_fixture - 1239u) / 2u))) {
                memcpy(movement_snapshots, driver->machine->ram, 2048u);
                if (background_snapshot == 47u) coin_entry_carry = driver->machine->a;
                if (background_snapshot == 76u) coin_entry_carry = driver->machine->a;
                if (background_snapshot == 73u) coin_entry_carry = driver->machine->a;
                if (background_snapshot == 29u) coin_entry_carry = driver->machine->a;
                if (background_snapshot == 17u) coin_entry_carry = (lib_u8)(driver->machine->p & 1u);
                if (background_snapshot == 14u) vine_block_slot = driver->machine->y;
                transition_argument = background_snapshot >= 10u && background_snapshot != 19u && background_snapshot != 22u && background_snapshot != 38u ? driver->machine->x : driver->machine->a;
                control_stack = driver->machine->s;
                control_return = (lib_u16)(1u +
                    driver->machine->ram[0x100u + (lib_u8)(control_stack + 1u)] +
                    256u * driver->machine->ram[0x100u + (lib_u8)(control_stack + 2u)]);
                movement_snapshot_phase = 1u;
            }
            if (movement_snapshot_phase == 1u) {
                if (entrance_child_active != 0u) {
                    if (before_pc == entrance_child_return && driver->machine->s ==
                        (lib_u8)(entrance_child_stack + 2u)) {
                        memcpy(entrance_children[entrance_child_count] + 2050u,
                               driver->machine->ram, 2048u);
                        if (background_snapshot == 74u) {
                            if (entrance_child_active <= 3u &&
                                (driver->machine->y != (lib_u8)(entrance_children[entrance_child_count][1] +
                                 (entrance_child_active == 2u ? 1u : 0u)) ||
                                 driver->machine->a != driver->machine->ram[3u])) return 69;
                            if (entrance_child_active == 4u && (driver->machine->p & 1u))
                                entrance_children[entrance_child_count][0] |= 0x80u;
                        }
                        if (background_snapshot == 72u) {
                            if (entrance_child_active == 1u) {
                                if (driver->machine->x != entrance_children[entrance_child_count][1]) return 69;
                                entrance_children[entrance_child_count][1] = (unsigned char)(driver->machine->p & 1u);
                            }
                            if (entrance_child_active == 2u) {
                                if (driver->machine->y != (lib_u8)(entrance_children[entrance_child_count][1]*4u+4u) || driver->machine->a > 15u) return 69;
                                entrance_children[entrance_child_count][0] |= (unsigned char)(driver->machine->a << 4u);
                            }
                            if (entrance_child_active == 3u) {
                                if (driver->machine->y != entrance_children[entrance_child_count][1]) return 69;
                                if (driver->machine->p & 1u) entrance_children[entrance_child_count][0] |= 0x80u;
                            }
                        }
                        if (background_snapshot == 71u) {
                            if (entrance_child_active == 1u) {
                                if (driver->machine->x != transition_argument) return 69;
                                entrance_children[entrance_child_count][1] = driver->machine->y;
                            }
                            if (entrance_child_active == 2u && (driver->machine->p & 1u))
                                entrance_children[entrance_child_count][0] |= 0x80u;
                            if (entrance_child_active == 3u && driver->machine->x !=
                                entrance_children[entrance_child_count][1]) return 69;
                            if (entrance_child_active == 4u && driver->machine->x !=
                                ((entrance_children[entrance_child_count][0] >> 4u) & 7u)) return 69;
                        }
                        if (background_snapshot == 70u) {
                            if (entrance_child_active == 1u)
                                entrance_children[entrance_child_count][1] = (unsigned char)(driver->machine->p & 1u);
                            if (entrance_child_active == 2u)
                                entrance_children[entrance_child_count][1] = driver->machine->y;
                            if (entrance_child_active == 3u && (driver->machine->p & 1u))
                                entrance_children[entrance_child_count][0] |= 0x80u;
                            if (entrance_child_active == 9u)
                                entrance_children[entrance_child_count][1] = driver->machine->a;
                            if ((entrance_child_active == 7u || entrance_child_active == 8u ||
                                 entrance_child_active == 9u || entrance_child_active == 10u) &&
                                driver->machine->x != 5u) return 69;
                        }
                        if (background_snapshot == 69u && (entrance_child_active == 1u || entrance_child_active == 2u) && driver->machine->x != 5u) return 69;
                        if (background_snapshot == 69u && entrance_child_active == 4u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 68u && entrance_child_active == 1u)
                            entrance_children[entrance_child_count][1] = (unsigned char)(driver->machine->p & 1u);
                        if (background_snapshot == 67u && entrance_child_active == 1u &&
                            driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 67u && (entrance_child_active == 2u || entrance_child_active == 3u) &&
                            driver->machine->x != entrance_children[entrance_child_count][1]) return 69;
                        if (background_snapshot == 67u && entrance_child_active == 2u && driver->machine->a != 0u) return 69;
                        if (background_snapshot == 66u && entrance_child_active == 1u)
                            entrance_children[entrance_child_count][1] = (unsigned char)(driver->machine->p & 1u);
                        if (background_snapshot == 65u && driver->machine->x != entrance_children[entrance_child_count][1]) return 69;
                        if (background_snapshot == 64u && driver->machine->x !=
                            entrance_children[entrance_child_count][2u + 8u]) return 69;
                        if (background_snapshot == 63u) {
                            if (entrance_child_active >= 2u && entrance_child_active <= 4u &&
                                driver->machine->x != driver->machine->ram[8u]) return 69;
                            if ((entrance_child_active == 1u || entrance_child_active == 5u) &&
                                driver->machine->x != entrance_children[entrance_child_count][1]) return 69;
                            if (entrance_child_active == 4u) entrance_children[entrance_child_count][1] = driver->machine->a;
                        }
                        if (background_snapshot == 62u) {
                            if ((entrance_child_active == 2u || entrance_child_active == 3u) &&
                                driver->machine->x != driver->machine->ram[8u]) return 69;
                            if (entrance_child_active == 5u && driver->machine->x != entrance_children[entrance_child_count][1]) return 69;
                        }
                        if (background_snapshot == 61u) {
                            if ((entrance_child_active == 2u || entrance_child_active == 3u || entrance_child_active == 6u) &&
                                driver->machine->x != driver->machine->ram[8u]) return 69;
                            if ((entrance_child_active == 1u || entrance_child_active == 4u || entrance_child_active == 5u || entrance_child_active == 7u) &&
                                driver->machine->x != entrance_children[entrance_child_count][1]) return 69;
                            if (entrance_child_active == 6u && driver->machine->y != 1u) return 69;
                            if (entrance_child_active == 7u && driver->machine->y != 1u) return 69;
                            if (entrance_child_active == 4u && driver->machine->a != 0u) return 69;
                        }
                        if (background_snapshot == 60u) {
                            if (driver->machine->x != entrance_children[entrance_child_count][2u+8u]) return 69;
                            entrance_children[entrance_child_count][1] = driver->machine->a;
                        }
                        if (background_snapshot == 59u && entrance_child_active == 1u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 58u && entrance_child_active == 1u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 57u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 56u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 55u && (entrance_child_active == 4u || entrance_child_active == 7u))
                            entrance_children[entrance_child_count][1] = driver->machine->a;
                        if (background_snapshot == 54u && entrance_child_active == 4u &&
                            entrance_children[entrance_child_count][1] != driver->machine->y) return 69;
                        if (background_snapshot == 53u && entrance_child_active == 3u)
                            entrance_children[entrance_child_count][1] = driver->machine->a;
                        if (background_snapshot == 51u && entrance_child_active == 2u &&
                            (driver->machine->x != entrance_children[entrance_child_count][2u+8u] ||
                             driver->machine->y != (entrance_children[entrance_child_count][2u+0x34u+driver->machine->x] == 0u ? 0x18u : 8u))) return 69;
                        if (background_snapshot == 51u && (entrance_child_active == 2u || entrance_child_active == 3u))
                            entrance_children[entrance_child_count][1] = driver->machine->a;
                        if (background_snapshot == 51u && entrance_child_active == 4u &&
                            entrance_children[entrance_child_count][1] != driver->machine->y) return 69;
                        if ((background_snapshot == 47u || background_snapshot == 48u) && entrance_child_active == 1u)
                            entrance_children[entrance_child_count][1] = driver->machine->a;
                        if (background_snapshot == 45u && entrance_child_active <= 2u)
                            entrance_children[entrance_child_count][1] = entrance_child_active == 1u ?
                                (unsigned char)(driver->machine->p & 1u) : driver->machine->a;
                        if (background_snapshot == 8u && entrance_child_active == 4u)
                            entrance_children[entrance_child_count][1] = driver->machine->a;
                        if (background_snapshot == 22u && entrance_child_active == 2u)
                            entrance_children[entrance_child_count][1] = (unsigned char)(driver->machine->p & 1u);
                        if (background_snapshot == 77u && entrance_child_active != 2u) {
                            if (driver->machine->a != entrance_children[entrance_child_count][1]) return 69;
                            entrance_children[entrance_child_count][0] |= (unsigned char)(
                                (entrance_child_active == 1u ? ((driver->machine->p >> 1u) & 1u) :
                                (driver->machine->p & 1u)) << 7u);
                        }
                        ++entrance_child_count;
                        entrance_child_active = 0u;
                    }
                }
                else if (entrance_children_path != NULL) {
                    unsigned int child;
                    child = background_snapshot == 77u ?
                        (before_pc == 0xdebdu ? 1u : (before_pc == 0xdec4u ? 2u :
                        (before_pc == 0xdeddu ? 3u : 0u))) :
                        background_snapshot == 76u ? (before_pc == 0x9716u ? 1u : 0u) :
                        background_snapshot == 75u ?
                        (before_pc == 0x8a4du ? 1u : (before_pc == 0xbbfeu ? 2u : 0u)) :
                        background_snapshot == 74u ?
                        (before_pc == 0xe3e9u ? 1u : (before_pc == 0xe3e8u ? 2u :
                        (before_pc == 0xe3ecu ? 3u : (before_pc == 0xdfa1u ? 4u :
                        (before_pc == 0xbcedu ? 5u : (before_pc == 0xde05u ? 6u :
                        (before_pc == 0xde0eu ? 7u : (before_pc == 0xde2eu ? 8u :
                        (before_pc == 0xdec4u ? 9u : (before_pc == 0xdee8u ? 10u :
                        (before_pc == 0xdf4bu ? 11u : 0u))))))))))) :
                        background_snapshot == 72u ? (before_pc == 0xdc41u ? 1u :
                        (before_pc == 0xdc52u || before_pc == 0xdc54u ? 2u :
                        (before_pc == 0xe325u ? 3u : (before_pc == 0xdf4bu ? 4u : 0u)))) : background_snapshot == 71u ? (before_pc == 0xdc52u ? 1u :
                        (before_pc == 0xe327u ? 2u : (before_pc == 0xd795u ? 3u :
                        (before_pc == 0xda11u ? 4u : 0u)))) : background_snapshot == 70u ? (before_pc == 0xdc41u ? 1u :
                        (before_pc == 0xdc52u ? 2u : (before_pc == 0xe325u ? 3u :
                        (before_pc == 0xd800u ? 4u : (before_pc == 0xd795u ? 5u :
                        (before_pc == 0x85f1u ? 6u : (before_pc == 0xe02fu ? 7u :
                        (before_pc == 0xc363u ? 8u : (before_pc == 0xe143u ? 9u :
                        (before_pc == 0xdb1cu ? 10u : 0u)))))))))) :
                        background_snapshot == 69u ? (before_pc == 0xc998u ? 1u : (before_pc == 0xda11u ? 2u : (before_pc == 0x85f1u ? 3u : (before_pc == 0xd948u ? 4u : 0u)))) :
                        background_snapshot == 68u ? (before_pc == 0xe325u ? 1u : (before_pc == 0xd92cu ? 2u : 0u)) :
                        background_snapshot == 67u ? (before_pc == 0xf152u ? 1u : (before_pc == 0xc363u ? 2u : (before_pc == 0xe01bu ? 3u : (before_pc == 0xda11u ? 4u : 0u)))) :
                        background_snapshot == 66u ? (before_pc == 0xe327u ? 1u : (before_pc == 0xd73eu ? 2u : 0u)) :
                        background_snapshot == 65u ? (before_pc == 0xc998u ? 1u : 0u) :
                        background_snapshot == 64u ?
                        (before_pc == 0xdc21u ? 1u : (before_pc == 0xdc19u ? 2u : 0u)) :
                        background_snapshot == 63u ?
                        (before_pc == 0xcb47u ? 1u : (before_pc == 0xcb66u ? 2u :
                        (before_pc == 0xbf88u ? 3u : (before_pc == 0xbf02u ? 4u :
                        (before_pc == 0xdc21u ? 5u : 0u))))) :
                        background_snapshot == 62u ?
                        (before_pc == 0xbfb7u ? 2u : (before_pc == 0xbfb4u ? 3u :
                        (before_pc == 0xdc21u ? 5u : 0u))) :
                        background_snapshot == 61u ?
                        (before_pc == 0xc998u ? 1u : (before_pc == 0xbfb7u ? 2u :
                        (before_pc == 0xbfb4u ? 3u : (before_pc == 0xc363u ? 4u :
                        (before_pc == 0xdc21u ? 5u : (before_pc == 0xf1afu ? 6u :
                        (before_pc == 0xda11u ? 7u : (before_pc == 0xbf6bu ? 8u : 0u)))))))) :
                        background_snapshot == 60u ? (before_pc == 0xe143u ? 1u : 0u) :
                        background_snapshot == 59u ?
                        (before_pc == 0xf152u ? 1u : (before_pc == 0x8f5fu ? 2u :
                        (before_pc == 0xbc36u ? 3u : 0u))) :
                        background_snapshot == 58u ?
                        (before_pc == 0xf152u ? 1u : (before_pc == 0xed17u ? 2u :
                        (before_pc == 0xd336u ? 3u : 0u))) :
                        background_snapshot == 57u ?
                        (before_pc == 0xf152u ? 1u : (before_pc == 0xf1afu ? 2u : 0u)) :
                        background_snapshot == 56u ?
                        (before_pc == 0xc8d7u ? 1u : (before_pc == 0xe243u ? 2u :
                        (before_pc == 0xd853u ? 3u : 0u))) :
                        background_snapshot == 55u ?
                        (before_pc == 0xc998u ? 1u : (before_pc == 0xbf8cu ? 2u :
                        (before_pc == 0xd17bu ? 3u : (before_pc == 0xe143u ? 4u :
                        (before_pc == 0xba94u ? 5u : (before_pc == 0xc363u ? 6u :
                        (before_pc == 0xd1d9u ? 7u : 0u))))))) :
                        background_snapshot == 54u ?
                        (before_pc == 0xd071u ? 1u : (before_pc == 0xbf8cu ? 2u :
                        (before_pc == 0xd17bu ? 3u : (before_pc == 0x8acdu ? 4u :
                        (before_pc == 0x8a8fu ? 5u : (before_pc == 0xc363u ? 6u : 0u)))))) :
                        background_snapshot == 53u ?
                        (before_pc == 0xbf63u ? 1u : (before_pc == 0xbf02u ? 2u :
                        (before_pc == 0xe143u ? 3u : 0u))) :
                        background_snapshot == 52u ?
                        (before_pc == 0xbf02u ? 1u : (before_pc == 0xbf96u ? 2u :
                        (before_pc == 0xbf92u ? 3u : 0u))) :
                        background_snapshot == 51u ?
                        (before_pc == 0xf1afu ? 1u : (before_pc == 0xd410u ? 2u :
                        (before_pc == 0xf152u ? 3u : (before_pc == 0xecedu ? 4u :
                        (before_pc == 0xd92cu ? 5u : 0u))))) :
                        background_snapshot == 50u ? (before_pc == 0xbf8cu ? 1u : 0u) :
                        background_snapshot == 49u ?
                        (before_pc == 0xbf92u ? 1u : (before_pc == 0xbf02u ? 2u : 0u)) :
                        background_snapshot == 48u ?
                        (before_pc == 0xe143u ? 1u : (before_pc == 0xbf8cu ? 2u : 0u)) :
                        background_snapshot == 47u ? (before_pc == 0xbf02u ? 1u : 0u) :
                        background_snapshot == 46u ?
                        mysmb_paratroopa_target(before_pc) :
                        background_snapshot == 45u ?
                        mysmb_hammer_movement_target(before_pc) :
                        background_snapshot == 44u ?
                        mysmb_podoboo_target(before_pc) :
                        background_snapshot == 43u ?
                        mysmb_special_actor_target(before_pc) :
                        background_snapshot == 80u ?
                        mysmb_special_actor_target(before_pc) :
                        background_snapshot == 42u ?
                        mysmb_normal_actor_target(before_pc) :
                        background_snapshot == 41u ?
                        (transition_entry == 0xc882u ? mysmb_actor_dispatch_target(before_pc) :
                        (before_pc == 0xf1afu ? 1u : (before_pc == 0xf152u ? 2u :
                        (before_pc == 0xe87du ? 3u : 0u)))) :
                        background_snapshot == 40u ?
                        (before_pc == 0xc871u ? 1u : (before_pc == 0xc363u ? 2u :
                        (before_pc == 0xc82bu ? 3u : 0u))) :
                        background_snapshot == 39u ?
                        (transition_entry == 0xc7a0u ?
                        (before_pc == 0xc3a4u ? 1u : (before_pc == 0xc7b7u ? 2u :
                        (before_pc == 0xc4a8u ? 3u : (before_pc == 0xc5a3u ? 4u :
                        (before_pc == 0xc63du ? 5u : (before_pc == 0xc69cu ? 6u : 0u)))))) : 0u) :
                        background_snapshot == 38u ?
                        (before_pc == 0xc26cu ? 1u : (before_pc == 0xc25eu ? 2u : 0u)) :
                        background_snapshot == 37u ?
                        (before_pc == 0xc5d8u ? 1u : (before_pc == 0xc26cu ? 2u : 0u)) :
                        background_snapshot == 36u ? 0u :
                        background_snapshot == 35u ?
                        (before_pc == 0xc575u ? 1u : (before_pc == 0xd1d9u ? 2u : 0u)) :
                        background_snapshot == 34u ? (before_pc == 0xc346u ? 1u : 0u) :
                        background_snapshot == 33u ?
                        (before_pc == 0xc38au ? 1u : (before_pc == 0xc5d8u ? 2u :
                        (before_pc == 0xcf6cu ? 3u : (before_pc == 0xc346u ? 4u : 0u)))) :
                        background_snapshot == 32u ?
                        mysmb_enemy_init_target(before_pc,
                            movement_snapshots[0x16u + transition_argument]) :
                        background_snapshot == 31u ? (before_pc == 0xc26cu ? 1u :
                        (before_pc == 0xc0ccu ? 2u : (before_pc == 0xc71bu ? 3u : 0u))) :
                        background_snapshot == 30u ? (before_pc == 0xc144u ? 1u :
                        (before_pc == 0xc226u ? 2u : (before_pc == 0xc882u ? 3u : 0u))) :
                        background_snapshot == 29u ? 0u :
                        background_snapshot == 28u ? (before_pc == 0xbfadu ? 1u :
                        (before_pc == 0xbfd1u ? 2u : 0u)) :
                        background_snapshot == 27u ? 0u :
                        background_snapshot == 26u ? (before_pc == 0x8a61u ? 1u : 0u) :
                        background_snapshot == 25u ? (before_pc == 0xbfa4u ? 1u :
                        (before_pc == 0xbf0fu ? 2u : (before_pc == 0xf159u ? 3u :
                        (before_pc == 0xf1b6u ? 4u : (before_pc == 0xebd1u ? 5u :
                        (before_pc == 0xec53u ? 6u : 0u)))))) :
                        background_snapshot == 24u ? (before_pc == 0x8a4du ? 1u :
                        (before_pc == 0xbb51u ? 2u : (before_pc == 0xbc27u ? 3u : 0u))) :
                        background_snapshot == 23u ? (before_pc == 0xbe1fu ? 1u :
                        (before_pc == 0xbc49u ? 2u : (before_pc == 0xbb38u ? 3u :
                        (before_pc == 0xb91eu ? 4u : 0u)))) :
                        background_snapshot == 22u ? (before_pc == 0x8a6bu ? 1u :
                        (before_pc == 0xbdf6u ? 2u : (before_pc == 0xbd9bu ? 3u :
                        (before_pc == 0xbe02u ? 4u : 0u)))) :
                        background_snapshot == 21u ? (before_pc == 0xcaf9u ? 1u :
                        (before_pc == 0xe163u ? 2u : (before_pc == 0xca77u ? 3u :
                        (before_pc == 0xdfc1u ? 4u : (before_pc == 0xf152u ? 5u :
                        (before_pc == 0xf1afu ? 6u : (before_pc == 0xe243u ? 7u :
                        (before_pc == 0xe6d2u ? 8u : (before_pc == 0xd853u ? 9u :
                        (before_pc == 0xd67au ? 10u : 0u)))))))))) :
                        background_snapshot == 20u ? 0u :
                        background_snapshot == 19u ? (before_pc == 0x8f5fu ? 1u :
                        (before_pc == 0x8f06u ? 2u : 0u)) :
                        background_snapshot == 18u ? (before_pc == 0xbac3u ? 1u :
                        (before_pc == 0xbfd7u ? 2u : (before_pc == 0xf148u ? 3u :
                        (before_pc == 0xf19bu ? 4u : (before_pc == 0xe236u ? 5u :
                        (before_pc == 0xe686u ? 6u : 0u)))))) :
                        background_snapshot == 17u ? (before_pc == 0xbbfeu ? 1u : 0u) :
                        background_snapshot == 16u ? (before_pc == 0xbfd7u ? 1u :
                        (before_pc == 0xbf0fu ? 2u : (before_pc == 0xd7c4u ? 3u :
                        (before_pc == 0xf19bu ? 4u : (before_pc == 0xf148u ? 5u :
                        (before_pc == 0xe236u ? 6u : (before_pc == 0xe4dcu ? 7u : 0u))))))) :
                        background_snapshot == 15u ? (before_pc == 0xf152u ? 1u :
                        (before_pc == 0xf1afu ? 2u : (before_pc == 0xe435u ? 3u :
                        (before_pc == 0xc998u ? 4u : (before_pc == 0xe3f0u ? 5u : 0u))))) :
                        background_snapshot == 13u ? (before_pc == 0xf1afu ? 1u :
                        (before_pc == 0xf152u ? 2u : (before_pc == 0xe87du ? 3u :
                        (before_pc == 0xd67au ? 4u : 0u)))) :
                        background_snapshot == 12u ? (before_pc == 0x8f5fu ? 1u :
                        (before_pc == 0x8f06u ? 2u : (before_pc == 0xd931u ? 3u : 0u))) :
                        background_snapshot == 10u ? (before_pc == 0xbfd7u ? 1u :
                        (before_pc == 0xbf0fu ? 2u : (before_pc == 0xf13bu ? 3u :
                        (before_pc == 0xf187u ? 4u : (before_pc == 0xe22du ? 5u :
                        (before_pc == 0xe1c8u ? 6u : (before_pc == 0xd6d9u ? 7u :
                        (before_pc == 0xecdeu ? 8u : (before_pc == 0xed09u ? 9u : 0u))))))))) :
                        background_snapshot == 9u ? (before_pc == 0xb689u ? 1u :
                        (before_pc == 0xb6f9u ? 2u : (before_pc == 0xf131u ? 3u :
                        (before_pc == 0xf191u ? 4u : (before_pc == 0xede1u ? 5u : 0u))))) :
                        background_snapshot == 8u ? (before_pc == 0xb450u ? 1u :
                        (before_pc == 0xb58fu ? 2u : (before_pc == 0xb5ccu ? 3u :
                        (before_pc == 0xbf09u ? 4u : (before_pc == 0xbf4du ? 5u :
                        (before_pc == 0xb3cfu ? 6u : 0u)))))) :
                        background_snapshot == 7u ? (before_pc == 0xb0e6u ? 1u :
                        (before_pc == 0x9c03u ? 2u : (before_pc == 0xb213u ? 3u : 0u))) :
                        background_snapshot == 6u ? (before_pc == 0xb0e9u ? 1u : 0u) :
                        background_snapshot == 5u ?
                        (before_pc == 0xb0e6u ? 1u : (before_pc == 0xaf93u ? 2u : 0u)) :
                        (before_pc == 0xb329u ? 1u :
                        (before_pc == 0xaf93u ? 2u :
                        (before_pc == 0xf180u ? 3u :
                        (before_pc == 0xf12au ? 4u :
                        (before_pc == 0xe29cu ? 5u :
                        (before_pc == 0xdc64u ? 6u :
                        (before_pc == 0xb1ddu ? 7u : 0u)))))));
                    if (child != 0u) {
                        if (background_snapshot == 28u) {
                            lib_u8 kind, expected_a, expected_x;
                            kind = (lib_u8)((t26_fixture - 1954u) / 4u);
                            expected_a = kind == 0u ? 4u :
                                (kind == 3u ? 0u : (kind == 4u ? 1u :
                                (kind == 5u || kind == 6u ? 2u : 3u)));
                            expected_x = kind == 0u ? 0u : (lib_u8)(transition_argument + 1u);
                            if (driver->machine->a != expected_a ||
                                driver->machine->x != expected_x) return 69;
                        }
                        if (background_snapshot == 54u && child == 4u && driver->machine->x != 12u) return 69;
                        if (entrance_child_count >= (background_snapshot == 18u || background_snapshot == 51u || background_snapshot == 71u ? 64u : 16u)) return 69;
                        if (background_snapshot == 58u && child == 2u &&
                            (driver->machine->x != driver->machine->ram[8u] ||
                             driver->machine->a != driver->machine->ram[0x58u + driver->machine->x] ||
                             driver->machine->y != driver->machine->ram[0x6e5u + driver->machine->x])) return 69;
                        if (background_snapshot == 60u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 51u && child == 2u &&
                            (driver->machine->x != driver->machine->ram[8u] ||
                             driver->machine->a != driver->machine->ram[0x388u+driver->machine->x])) return 69;
                        if (background_snapshot == 64u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 64u && child == 2u && driver->machine->a != driver->machine->ram[0x3a2u + driver->machine->x]) return 69;
                        if (background_snapshot == 63u && child == 1u && driver->machine->a != 0x0eu) return 69;
                        if (background_snapshot == 63u && child == 4u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 61u && child == 7u && driver->machine->a != 6u) return 69;
                        if (background_snapshot == 66u) {
                            if (child == 1u && (driver->machine->x != (lib_u8)(driver->machine->ram[1u] * 4u + 4u) ||
                                driver->machine->y != (lib_u8)(transition_argument * 4u + 0x1cu))) return 69;
                            if (child == 2u && driver->machine->x != driver->machine->ram[1u]) return 69;
                        }
                        if (background_snapshot == 67u && child == 3u && driver->machine->a !=
                            (driver->machine->ram[0x16u+driver->machine->x] == 13u ?
                             driver->machine->ram[0xcfu+driver->machine->x] : driver->machine->ram[0x16u+driver->machine->x])) return 69;
                        if (background_snapshot == 67u && child == 4u && driver->machine->x != driver->machine->ram[1u]) return 69;
                        if (background_snapshot == 68u && child == 1u &&
                            driver->machine->y != (lib_u8)(transition_argument*4u+0x24u)) return 69;
                        if (background_snapshot == 68u && child == 2u &&
                            driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (background_snapshot == 69u) {
                            if ((child == 1u || child == 2u) && driver->machine->x != 5u) return 69;
                            if (child == 2u && driver->machine->a != 6u) return 69;
                            if (child == 3u && driver->machine->x != driver->machine->ram[8u]) return 69;
                            if (child == 4u && driver->machine->y != 0u) return 69;
                        }
                        if (background_snapshot == 72u && before_pc == 0xdc54u && driver->machine->a != driver->machine->x) return 69;
                        if (background_snapshot == 71u && child == 2u && driver->machine->x !=
                            (lib_u8)(driver->machine->ram[1u]*4u+4u)) return 69;
                        if (background_snapshot == 70u && child != 6u &&
                            driver->machine->x != 5u) return 69;
                        entrance_children[entrance_child_count][0] = (unsigned char)child;
                        if (background_snapshot == 15u && child == 5u &&
                            (driver->machine->x != 6u || driver->machine->a != 1u)) return 69;
                        entrance_children[entrance_child_count][1] =
                            (background_snapshot == 76u || background_snapshot == 77u) ? driver->machine->a :
                            background_snapshot == 74u ? (child <= 3u ? driver->machine->y :
                                (child == 11u ? driver->machine->ram[0u] : driver->machine->a)) :
                            background_snapshot == 72u && child == 2u ? (before_pc == 0xdc52u ? driver->machine->ram[8u] : driver->machine->a) :
                            background_snapshot == 72u && child == 3u ? driver->machine->y :
                            background_snapshot == 72u && child == 4u ? driver->machine->ram[0u] :
                            background_snapshot == 71u && child == 2u ? driver->machine->y :
                            background_snapshot == 71u && child == 4u ? driver->machine->a :
                            background_snapshot == 70u && child == 3u ? driver->machine->y :
                            background_snapshot == 69u && (child == 2u || child == 4u) ? driver->machine->a :
                            background_snapshot == 67u && child == 4u ? driver->machine->a :
                            background_snapshot == 59u ? (child == 1u ? driver->machine->x :
                                (child == 2u ? driver->machine->y : driver->machine->a)) :
                            background_snapshot == 54u && (child == 4u || child == 5u) ? driver->machine->y :
                            background_snapshot == 51u && child == 4u ? driver->machine->y :
                            background_snapshot == 46u && child == 3u ? driver->machine->a :
                            background_snapshot == 40u && child == 1u ? driver->machine->y :
                            background_snapshot == 32u ? driver->machine->y :
                            background_snapshot == 31u && child == 3u ? driver->machine->a :
                            background_snapshot == 19u ?
                            (child == 1u ? driver->machine->y : driver->machine->a) :
                            background_snapshot == 15u && (child == 3u || child == 5u) ?
                            driver->machine->y : background_snapshot == 12u ?
                            (child == 1u ? driver->machine->y : driver->machine->a) : background_snapshot >= 9u || (child == 5u && background_snapshot != 8u) ?
                            driver->machine->x : driver->machine->a;
                        if (background_snapshot == 71u && child == 4u) {
                            if (driver->machine->x > 5u) return 69;
                            entrance_children[entrance_child_count][0] |= (unsigned char)(driver->machine->x << 4u);
                        }
                        memcpy(entrance_children[entrance_child_count] + 2u,
                               driver->machine->ram, 2048u);
                        entrance_child_stack = driver->machine->s;
                        entrance_child_return = (lib_u16)(1u +
                            driver->machine->ram[0x100u + (lib_u8)(entrance_child_stack + 1u)] +
                            256u * driver->machine->ram[0x100u + (lib_u8)(entrance_child_stack + 2u)]);
                        entrance_child_active = child;
                    }
                }
                if (before_pc == control_return && driver->machine->s ==
                    (lib_u8)(control_stack + 2u)) {
                    memcpy(movement_snapshots + 2048u, driver->machine->ram, 2048u);
                    if (background_snapshot == 16u)
                        hammer_return_carry = (lib_u8)(driver->machine->p & 1u);
                    if (background_snapshot == 19u || background_snapshot == 20u)
                        hammer_return_carry = driver->machine->x;
                    if (background_snapshot == 28u) {
                        hammer_return_carry = driver->machine->x;
                        if (transition_entry != 0xbf4du &&
                            driver->machine->x != driver->machine->ram[8u]) return 69;
                    }
                    if (background_snapshot == 27u) {
                        hammer_return_carry = driver->machine->a;
                        if (transition_entry == 0xbf02u && driver->machine->x != driver->machine->ram[8u]) return 69;
                        if (transition_entry == 0xbf0fu && driver->machine->x != transition_argument) return 69;
                    }
                    if (background_snapshot == 53u) hammer_return_carry = driver->machine->a;
                    movement_snapshot_phase = 2u;
                }
            }
        }
        /* T45 S5: after BubbleCheck returns to the original GameEngine
         * frame, observe DrawBubble and PlayerGfxHandler as real JSR children.
         * The existing BubbleCheck snapshot ends before these calls. */
        if (entrance_children_path != NULL && background_snapshot == 11u &&
            movement_snapshot_phase == 2u && elapsed >= warmup_frames) {
            if (entrance_child_active != 0u) {
                if (before_pc == entrance_child_return && driver->machine->s ==
                    (lib_u8)(entrance_child_stack + 2u)) {
                    memcpy(entrance_children[entrance_child_count] + 2050u,
                           driver->machine->ram, 2048u);
                    ++entrance_child_count;
                    entrance_child_active = 0u;
                }
            }
            else if (before_pc == 0xede1u || before_pc == 0xeee9u) {
                if (entrance_child_count >= 16u) return 69;
                entrance_children[entrance_child_count][0] =
                    (unsigned char)(before_pc == 0xede1u ? 1u : 2u);
                entrance_children[entrance_child_count][1] = driver->machine->x;
                memcpy(entrance_children[entrance_child_count] + 2u,
                       driver->machine->ram, 2048u);
                entrance_child_stack = driver->machine->s;
                entrance_child_return = (lib_u16)(1u +
                    driver->machine->ram[0x100u + (lib_u8)(entrance_child_stack + 1u)] +
                    256u * driver->machine->ram[0x100u + (lib_u8)(entrance_child_stack + 2u)]);
                entrance_child_active = entrance_children[entrance_child_count][0];
            }
        }
        /* T46 S2: observe the actual world/lives DrawPlayer_Intermediate
         * JSR and its stack-derived return without altering execution. */
        if (entrance_children_path != NULL && t26_fixture == 23u &&
            elapsed >= warmup_frames) {
            if (entrance_child_active != 0u) {
                if (before_pc == entrance_child_return && driver->machine->s ==
                    (lib_u8)(entrance_child_stack + 2u)) {
                    memcpy(entrance_children[entrance_child_count] + 2050u,
                           driver->machine->ram, 2048u);
                    ++entrance_child_count;
                    entrance_child_active = 0u;
                }
            }
            else if (before_pc == 0xefa4u) {
                if (entrance_child_count >= 16u) return 69;
                entrance_children[entrance_child_count][0] = 1u;
                entrance_children[entrance_child_count][1] = driver->machine->x;
                memcpy(entrance_children[entrance_child_count] + 2u,
                       driver->machine->ram, 2048u);
                entrance_child_stack = driver->machine->s;
                entrance_child_return = (lib_u16)(1u +
                    driver->machine->ram[0x100u + (lib_u8)(entrance_child_stack + 1u)] +
                    256u * driver->machine->ram[0x100u + (lib_u8)(entrance_child_stack + 2u)]);
                entrance_child_active = 1u;
            }
        }
        /* T46 S3: observe the source-reached ProcessPlayerAction JSR
         * and its original return value and RAM without stepping away. */
        if (player_action_child_path != NULL && background_snapshot == 11u &&
            elapsed >= warmup_frames) {
            if (player_action_child_active != 0u) {
                if (before_pc == player_action_child_return &&
                    driver->machine->s ==
                    (lib_u8)(player_action_child_stack + 2u)) {
                    player_action_children[player_action_child_count][1] =
                        driver->machine->a;
                    memcpy(player_action_children[player_action_child_count] +
                           2050u, driver->machine->ram, 2048u);
                    ++player_action_child_count;
                    player_action_child_active = 0u;
                }
            }
            else if (before_pc == 0xefecu) {
                if (player_action_child_count >= 8u) return 69;
                player_action_children[player_action_child_count][0] = 1u;
                memcpy(player_action_children[player_action_child_count] +
                       2u, driver->machine->ram, 2048u);
                player_action_child_stack = driver->machine->s;
                player_action_child_return = (lib_u16)(1u +
                    driver->machine->ram[0x100u + (lib_u8)(player_action_child_stack + 1u)] +
                    256u * driver->machine->ram[0x100u + (lib_u8)(player_action_child_stack + 2u)]);
                player_action_child_active = 1u;
            }
        }
        /* T46 S4: capture the original HandleChangeSize and
         * ChkForPlayerAttrib JSRs with their stack-derived returns. */
        if (player_size_child_path != NULL && background_snapshot == 11u &&
            elapsed >= warmup_frames) {
            if (player_size_child_active != 0u) {
                if (before_pc == player_size_child_return &&
                    driver->machine->s ==
                    (lib_u8)(player_size_child_stack + 2u)) {
                    player_size_children[player_size_child_count][1] =
                        driver->machine->a;
                    memcpy(player_size_children[player_size_child_count] +
                           2050u, driver->machine->ram, 2048u);
                    ++player_size_child_count;
                    player_size_child_active = 0u;
                }
            }
            else if (before_pc == 0xf0b0u || before_pc == 0xf0e9u) {
                if (player_size_child_count >= 8u) return 69;
                player_size_children[player_size_child_count][0] =
                    (unsigned char)(before_pc == 0xf0b0u ? 1u : 2u);
                memcpy(player_size_children[player_size_child_count] +
                       2u, driver->machine->ram, 2048u);
                player_size_child_stack = driver->machine->s;
                player_size_child_return = (lib_u16)(1u +
                    driver->machine->ram[0x100u + (lib_u8)(player_size_child_stack + 1u)] +
                    256u * driver->machine->ram[0x100u + (lib_u8)(player_size_child_stack + 2u)]);
                player_size_child_active = 1u;
            }
        }
        /* T47 S2: vary only the selected routine's RAM inputs after its
         * natural call.  The original CPU PC/registers/stack/ROM stay put. */
        if (relative_coordinate_variant == 1u &&
            before_pc == relative_child_entry) {
            static const lib_u8 coordinate_displacements[6] = {
                0u, 0x009cu - 0x0086u, 0x008du - 0x0086u,
                0x0093u - 0x0086u, 0x0087u - 0x0086u,
                0x008fu - 0x0086u
            };
            lib_u8 *ram = driver->machine->ram;
            if (relative_kind == 6u) {
                /* T47 S3: boundary inputs only, at the natural player
                 * offscreen entry.  CPU registers/PC/stack remain intact. */
                ram[0x071cu] = 0xf0u;
                ram[0x071du] = 0xf0u;
                ram[0x0086u] = 5u;
                ram[0x00ceu] = 0xf9u;
                ram[0x00b5u] = 1u;
            }
            else if (relative_kind >= 7u) {
                static const lib_u8 offscreen_displacements[5] = {
                    7u, 22u, 13u, 1u, 9u
                };
                lib_u8 source = (lib_u8)(driver->machine->x +
                    offscreen_displacements[relative_kind - 7u]);
                ram[0x071au] = 1u;
                ram[0x071bu] = 2u;
                ram[0x071cu] = 0xf0u;
                ram[0x071du] = 0x40u;
                ram[0x006du + source] = 2u;
                ram[0x0086u + source] = 0x30u;
                ram[0x00b5u + source] = 1u;
                ram[0x00ceu + source] = 0xf8u;
                ram[0u] = 0xccu;
                ram[4u] = 0xa4u;
                ram[5u] = 0xa5u;
                ram[6u] = 0xa6u;
                ram[7u] = 0xa7u;
            }
            else {
                lib_u8 source = (lib_u8)(driver->machine->x +
                                         coordinate_displacements[relative_kind]);
                ram[0x071cu] = 0xf0u;
                ram[0x0086u + source] = 5u;
                ram[0x00ceu + source] = 0x95u;
                if (relative_kind == 5u) {
                    source = (lib_u8)(source + 2u);
                    ram[0x0086u + source] = 7u;
                    ram[0x00ceu + source] = 0x96u;
                }
                ram[0u] = 0xccu;
                ram[0x0755u] = 0xa5u;
            }
        }
        /* T47 S2: observe a source-reached relative-position call and
         * stack-derived return.  Never redirect the original CPU. */
        if (relative_child_path != NULL && elapsed >= warmup_frames) {
            if (relative_child_active != 0u) {
                if (relative_kind == 6u && before_pc == 0xf1c0u &&
                    driver->machine->x == 0u &&
                    driver->machine->y == 0u)
                    relative_children[relative_child_count][3] = 1u;
                if (before_pc == relative_child_return &&
                    driver->machine->s ==
                    (lib_u8)(relative_child_stack + 2u)) {
                    relative_children[relative_child_count][2] =
                        driver->machine->x;
                    memcpy(relative_children[relative_child_count] + 2052u,
                           driver->machine->ram, 2048u);
                    ++relative_child_count;
                    relative_child_active = 0u;
                }
            }
            else if (relative_child_count < 8u &&
                     before_pc == relative_child_entry) {
                relative_children[relative_child_count][0] =
                    (unsigned char)(relative_kind + 1u);
                relative_children[relative_child_count][1] =
                    driver->machine->x;
                relative_children[relative_child_count][3] = 0u;
                memcpy(relative_children[relative_child_count] + 4u,
                       driver->machine->ram, 2048u);
                relative_child_stack = driver->machine->s;
                relative_child_return = (lib_u16)(1u +
                    driver->machine->ram[0x100u +
                        (lib_u8)(relative_child_stack + 1u)] +
                    256u * driver->machine->ram[0x100u +
                        (lib_u8)(relative_child_stack + 2u)]);
                relative_child_active = 1u;
            }
        }
        /* T47 S5: observe naturally reached DrawSpriteObject and its
         * stack-derived return.  The optional variant changes only RAM
         * scratch after the original caller has entered the routine. */
        if (sprite_row_flip_variant != 0u && before_pc == 0xf282u) {
            lib_u8 *ram = driver->machine->ram;
            ram[0u] = 0x12u;
            ram[1u] = 0x34u;
            ram[2u] = 0xf9u;
            ram[3u] = (lib_u8)(ram[3u] | 2u);
            ram[4u] = 0x85u;
            ram[5u] = 0xfcu;
        }
        if (sprite_row_child_path != NULL && elapsed >= warmup_frames) {
            if (sprite_row_child_active != 0u) {
                if (before_pc == sprite_row_child_return &&
                    driver->machine->s ==
                    (lib_u8)(sprite_row_child_stack + 2u)) {
                    sprite_row_children[sprite_row_child_count][2] =
                        driver->machine->x;
                    sprite_row_children[sprite_row_child_count][3] =
                        driver->machine->y;
                    memcpy(sprite_row_children[sprite_row_child_count] + 2052u,
                           driver->machine->ram, 2048u);
                    ++sprite_row_child_count;
                    sprite_row_child_active = 0u;
                }
            }
            else if (sprite_row_child_count < 8u && before_pc == 0xf282u) {
                sprite_row_children[sprite_row_child_count][0] =
                    driver->machine->x;
                sprite_row_children[sprite_row_child_count][1] =
                    driver->machine->y;
                memcpy(sprite_row_children[sprite_row_child_count] + 4u,
                       driver->machine->ram, 2048u);
                sprite_row_child_stack = driver->machine->s;
                sprite_row_child_return = (lib_u16)(1u +
                    driver->machine->ram[0x100u +
                        (lib_u8)(sprite_row_child_stack + 1u)] +
                    256u * driver->machine->ram[0x100u +
                        (lib_u8)(sprite_row_child_stack + 2u)]);
                sprite_row_child_active = 1u;
            }
        }
        /* T48 S2: record the original helper's real CPU entry and RTS.
         * Nested helper labels have independent stack-derived returns. */
        if (sound_helper_path != NULL && elapsed >= warmup_frames) {
            unsigned int helper;
            for (helper = 0u; helper < 9u; ++helper) {
                if (sound_helper_active[helper] != 0u &&
                    before_pc == sound_helper_return[helper] &&
                    driver->machine->s ==
                    (lib_u8)(sound_helper_stack[helper] + 2u)) {
                    unsigned char *row =
                        sound_helpers[sound_helper_record[helper]];
                    memcpy(row + 30u, driver->machine->apu.registers, 24u);
                    row[54] = driver->machine->a;
                    row[55] = driver->machine->x;
                    row[56] = driver->machine->y;
                    row[57] = driver->machine->s;
                    sound_helper_active[helper] = 0u;
                }
                if (before_pc == sound_helper_pc[helper] &&
                    sound_helper_active[helper] == 0u) {
                    unsigned char *row;
                    lib_u8 s;
                    if (sound_helper_count >= 128u) return 69;
                    row = sound_helpers[sound_helper_count];
                    row[0] = (unsigned char)(before_pc & 0xffu);
                    row[1] = (unsigned char)(before_pc >> 8u);
                    row[2] = driver->machine->a;
                    row[3] = driver->machine->x;
                    row[4] = driver->machine->y;
                    row[5] = driver->machine->s;
                    memcpy(row + 6u, driver->machine->apu.registers, 24u);
                    s = driver->machine->s;
                    sound_helper_stack[helper] = s;
                    sound_helper_return[helper] = (lib_u16)(1u +
                        driver->machine->ram[0x100u + (lib_u8)(s + 1u)] +
                        256u * driver->machine->ram[0x100u +
                                                   (lib_u8)(s + 2u)]);
                    sound_helper_record[helper] = sound_helper_count++;
                    sound_helper_active[helper] = 1u;
                }
            }
        }
        /* T48 S1: only entry RAM is varied.  The original SoundEngine
         * executes unchanged and returns through its real stack frame. */
        if (sound_child_path != NULL && elapsed >= warmup_frames) {
            if (sound_child_active != 0u) {
                if (before_pc == sound_child_return &&
                    driver->machine->s ==
                    (lib_u8)(sound_child_stack + 2u)) {
                    memcpy(sound_children[sound_child_count] + 2072u,
                           driver->machine->ram, 2048u);
                    memcpy(sound_children[sound_child_count] + 4120u,
                           driver->machine->apu.registers, 24u);
                    ++sound_child_count;
                    sound_child_active = 0u;
                }
            }
            else if (sound_child_count < 8u && before_pc == 0xf2d0u) {
                lib_u8 *ram = driver->machine->ram;
                if (sound_case >= 13u) {
                    ram[0x0770u] = 1u;
                    ram[0x07c6u] = 0u;
                    ram[0x00fau] = 0u;
                    ram[0x07b2u] = 0u;
                    ram[0x00f1u] = sound_case == 99u ? 0x80u :
                        sound_case >= 37u && sound_case <= 40u ?
                        0x80u : sound_case == 41u || sound_case == 42u ?
                        0x02u : sound_case == 43u || sound_case == 44u ?
                        0x20u : sound_case == 45u ||
                        (sound_case >= 46u && sound_case <= 48u) ? 0x04u :
                        sound_case >= 49u && sound_case <= 51u ? 0x08u :
                        sound_case >= 52u && sound_case <= 55u ? 0x10u :
                        sound_case == 56u ? 0x40u :
                        sound_case == 57u ? 0x01u : 0u;
                    ram[0x00f2u] = sound_case == 82u ? 0x80u :
                        sound_case == 84u ? 0x40u :
                        sound_case == 87u ? 0x02u :
                        sound_case == 88u ? 0x04u :
                        sound_case == 62u || sound_case == 70u ||
                        sound_case == 74u ?
                        0x01u : sound_case == 64u || sound_case == 75u ? 0x10u :
                        sound_case == 66u || sound_case == 76u ? 0x08u :
                        sound_case >= 68u && sound_case <= 69u ||
                        sound_case == 77u ? 0x20u :
                        sound_case == 79u ? 0x11u :
                        sound_case == 80u ? 0x41u : 0u;
                    ram[0x00f3u] = sound_case == 90u ||
                        sound_case == 91u ? 0x01u :
                        sound_case == 93u ? 0x02u : 0u;
                    ram[0x00f4u] = sound_case == 95u ? 0x01u : 0u;
                    ram[0x07b1u] = 0u;
                    ram[0x00fbu] = sound_case == 98u ? 0x01u :
                        sound_case == 99u ? 0x04u : sound_case == 100u ?
                        0x02u : sound_case >= 29u && sound_case <= 36u ?
                        (lib_u8)(1u << (sound_case - 29u)) : 0u;
                    ram[0x00fcu] = sound_case == 96u ? 0x01u :
                        sound_case == 97u ? 0x40u : 0u;
                    ram[0x00ffu] = sound_case <= 20u ?
                        (lib_u8)(1u << (sound_case - 13u)) :
                        sound_case == 59u ? 0x03u :
                        sound_case == 60u ? 0x81u : 0u;
                    ram[0x07bbu] = sound_case == 37u ? 0x25u :
                        sound_case == 38u ? 0x20u :
                        sound_case == 39u ? 0x24u :
                        sound_case == 40u ? 0x1fu :
                        sound_case == 41u || sound_case == 43u ? 6u :
                        sound_case == 42u || sound_case == 44u ? 7u :
                        sound_case == 45u || sound_case == 46u ||
                        sound_case == 49u ? 0x0eu :
                        sound_case == 47u ? 6u :
                        sound_case == 48u || sound_case == 51u ||
                        sound_case == 55u || sound_case == 56u ||
                        sound_case == 57u ? 1u :
                        sound_case == 50u || sound_case == 54u ? 8u :
                        sound_case == 52u ? 0x2fu :
                        sound_case == 53u ? 0x2cu : 0u;
                    ram[0x00feu] = sound_case == 61u ? 0x01u :
                        sound_case == 81u ? 0x80u :
                        sound_case == 83u ? 0x40u :
                        sound_case == 85u ? 0x02u :
                        sound_case == 86u ? 0x04u :
                        sound_case == 63u ? 0x10u :
                        sound_case == 65u ? 0x08u :
                        sound_case == 67u ? 0x20u :
                        sound_case == 72u ? 0x11u :
                        sound_case == 78u ? 0x03u :
                        sound_case == 80u ? 0x01u :
                        sound_case >= 21u && sound_case <= 28u ?
                        (lib_u8)(1u << (sound_case - 21u)) : 0u;
                    ram[0x07bdu] = sound_case == 81u ? 0u :
                        sound_case == 82u ? 8u :
                        sound_case == 84u ? 8u :
                        sound_case == 87u ? 0x10u :
                        sound_case == 88u ? 0x20u :
                        sound_case == 62u || sound_case == 64u ?
                        0x30u : sound_case == 74u || sound_case == 75u ||
                        sound_case == 79u ? 0x30u :
                        sound_case == 66u || sound_case == 76u ? 0x18u :
                        sound_case == 68u || sound_case == 77u ? 0x36u : sound_case == 69u ?
                        0x35u : sound_case == 70u ? 1u : 0u;
                    ram[0x07beu] = sound_case == 87u ? 0x1fu :
                        sound_case == 88u ? 0x3fu : 0u;
                    ram[0x07bfu] = sound_case == 90u ? 0x1fu :
                        sound_case == 91u ? 1u : sound_case == 93u ? 2u : 0u;
                    ram[0x00fdu] = sound_case == 89u ? 0x01u :
                        sound_case == 92u ? 0x02u : sound_case == 94u ?
                        0x04u : 0u;
                    /* S2 ContinueMusic: active ground-music buffer after
                     * LoadHeader, with a real GroundM_P1 square-two stream.
                     * MusicHandler must take its direct handoff to
                     * HandleSquare2Music rather than reload a header. */
                    if (sound_case == 95u) {
                        ram[0x00f0u] = 0x18u;
                        ram[0x00f5u] = 0x01u;
                        ram[0x00f6u] = 0xfau;
                        ram[0x00f7u] = 0u;
                        ram[0x07b4u] = 1u;
                    }
                    /* S4 stream controls.  Cases 101--104 point MusicData at
                     * an unchanged owner-ROM terminator to exercise the four
                     * EndOfMusicData exits.  Case 105 enters a real length /
                     * note pair while Square2 SFX owns the channel, and 106
                     * enters a real music-stream rest. */
                    if (sound_case >= 101u && sound_case <= 106u) {
                        ram[0x00f0u] = 0u;
                        ram[0x00f4u] = sound_case >= 104u ? 0x01u : 0u;
                        ram[0x07b1u] = sound_case == 101u ? 1u :
                            sound_case == 102u ? 0x40u :
                            sound_case == 103u ? 0x04u : 0u;
                        ram[0x07c5u] = sound_case == 102u ? 1u : 0u;
                        ram[0x00f5u] = sound_case == 105u ? 0x01u :
                            sound_case == 106u ? 0x10u : 0x07u;
                        ram[0x00f6u] = sound_case == 105u ||
                            sound_case == 106u ? 0xfau : 0xf0u;
                        ram[0x00f7u] = 0u;
                        ram[0x07b4u] = 1u;
                        ram[0x07c7u] = sound_case == 102u ||
                            sound_case == 104u ? 0x10u : 0u;
                        ram[0x00f2u] = sound_case == 105u ? 0x01u : 0u;
                    }
                    /* T49 S5: Square1 music consumes the same untouched
                     * GroundM_P1 stream as the source.  The four records
                     * isolate a rest/control bypass, null-data loop followed
                     * by an audible note, SFX ownership exit and death
                     * alternate-control tail. */
                    if (sound_case >= 107u && sound_case <= 110u) {
                        ram[0x00f0u] = 0u;
                        ram[0x00f4u] = 0x01u;
                        ram[0x00f5u] = 0x00u;
                        ram[0x00f6u] = 0xfau;
                        /* Square2, triangle and noise take their no-fetch
                         * paths, leaving the S5 Square1 result surface
                         * attributable to this source chain. */
                        ram[0x00f7u] = 1u;
                        ram[0x07b4u] = 2u;
                        ram[0x00f9u] = 1u;
                        ram[0x07b9u] = 2u;
                        ram[0x07b0u] = 1u;
                        ram[0x07bau] = 2u;
                        ram[0x00f8u] = sound_case == 108u ? 0x1cu : 1u;
                        ram[0x07b6u] = sound_case == 110u ? 2u : 1u;
                        ram[0x00f1u] = sound_case == 109u ? 0x01u : 0u;
                        ram[0x07b1u] = sound_case == 110u ? 0x01u : 0u;
                    }
                    if (sound_case >= 111u && sound_case <= 114u) {
                        ram[0x00f0u] = 0u;
                        ram[0x00f5u] = 0x00u;
                        ram[0x00f6u] = 0xfau;
                        ram[0x00f7u] = 1u;
                        ram[0x07b4u] = 2u;
                        ram[0x00f8u] = 0u;
                        ram[0x07b6u] = 2u;
                        ram[0x07b0u] = 1u;
                        ram[0x07bau] = 2u;
                        ram[0x00f9u] = sound_case == 111u ? 0u : 1u;
                        ram[0x07b9u] = 1u;
                        ram[0x00f4u] = sound_case == 113u ? 0x02u :
                            (sound_case == 114u ? 0u : 1u);
                        ram[0x07b1u] = sound_case == 114u ? 0x08u : 0u;
                    }
                    if (sound_case >= 115u && sound_case <= 120u) {
                        /* T49 S7: retain each byte in the original PRG and
                         * isolate the area gate, counter, loopback and four
                         * NoiseBeatHandler outcomes. */
                        ram[0x00f0u] = 0u;
                        ram[0x00f1u] = 0u;
                        ram[0x00f2u] = 0u;
                        ram[0x00f4u] = sound_case == 115u ? 0x04u : 0x01u;
                        ram[0x00f5u] = sound_case == 118u ? 0x29u :
                            (sound_case == 119u ? 0xd0u : 0x00u);
                        ram[0x00f6u] = sound_case == 118u || sound_case == 120u ?
                            0xf0u : (sound_case == 119u ? 0xfdu : 0xfau);
                        ram[0x00f7u] = 1u;
                        ram[0x07b4u] = 2u;
                        ram[0x00f8u] = 0u;
                        ram[0x07b6u] = 2u;
                        ram[0x00f9u] = 2u;
                        ram[0x07b9u] = 1u;
                        ram[0x07b0u] = 0u;
                        ram[0x07b9u] = 1u;
                        ram[0x07bau] = sound_case == 116u ? 2u : 1u;
                        ram[0x07c1u] = sound_case == 117u ? 1u : 0u;
                    }
                    if (sound_case == 121u || sound_case == 122u) {
                        /* S8 envelope table selectors: owner-ROM Square2
                         * length/note pair, water versus Win-Castle event. */
                        ram[0x00f0u] = 0u;
                        ram[0x00f1u] = 0u;
                        ram[0x00f2u] = 0u;
                        ram[0x00f4u] = sound_case == 121u ? 0x02u : 0u;
                        ram[0x00f5u] = 0x01u;
                        ram[0x00f6u] = 0xfau;
                        ram[0x00f7u] = 1u;
                        ram[0x07b4u] = 1u;
                        ram[0x00f8u] = 0u;
                        ram[0x07b6u] = 2u;
                        ram[0x00f9u] = 2u;
                        ram[0x07b9u] = 1u;
                        ram[0x07b0u] = 1u;
                        ram[0x07bau] = 2u;
                        ram[0x07b1u] = sound_case == 122u ? 0x08u : 0u;
                    }
                }
                else if (sound_case != 0u) {
                    ram[0x0770u] = 1u;
                    ram[0x07c6u] = sound_case == 1u ||
                        sound_case == 9u || sound_case == 10u ? 0u : 1u;
                    ram[0x00fau] = sound_case == 1u ? 1u : 0u;
                    ram[0x07b2u] = sound_case == 1u || sound_case == 8u ||
                        sound_case == 9u || sound_case == 10u ?
                        0u : (sound_case == 6u ? 2u : 1u);
                    ram[0x07bbu] = sound_case == 2u ? 0x25u :
                        sound_case == 3u ? 0x24u :
                        sound_case == 4u ? 0x1eu :
                        sound_case == 5u ? 0x18u :
                        sound_case == 6u || sound_case == 7u ? 1u :
                        0x20u;
                    ram[0x00f1u] = 0x40u;
                    ram[0x00f2u] = 1u;
                    ram[0x00f3u] = 2u;
                    ram[0x00f4u] = sound_case == 9u ||
                        sound_case >= 11u ? 1u : 0u;
                    ram[0x07c0u] = sound_case == 9u ? 0x2fu :
                        sound_case == 11u ? 0x30u :
                        sound_case == 12u ? 0u : 3u;
                }
                memcpy(sound_children[sound_child_count], ram, 2048u);
                memcpy(sound_children[sound_child_count] + 2048u,
                       driver->machine->apu.registers, 24u);
                sound_child_stack = driver->machine->s;
                sound_child_return = (lib_u16)(1u +
                    ram[0x100u + (lib_u8)(sound_child_stack + 1u)] +
                    256u * ram[0x100u +
                        (lib_u8)(sound_child_stack + 2u)]);
                sound_child_active = 1u;
            }
        }
        /* Observe declared child entry/return states while the original
         * PlayerEntrance executes. Read the real return address and stack
         * depth; never replace the original child or alter CPU state. */
        if (entrance_children_path != NULL && background_snapshot == 3u &&
            movement_snapshot_phase == 1u) {
            if (entrance_child_active != 0u) {
                if (before_pc == entrance_child_return && driver->machine->s ==
                    (lib_u8)(entrance_child_stack + 2u)) {
                    memcpy(entrance_children[entrance_child_count] + 2050u,
                           driver->machine->ram, 2048u);
                    ++entrance_child_count;
                    entrance_child_active = 0u;
                }
            }
            else if (before_pc == 0xb0e9u || before_pc == 0xb21fu ||
                     before_pc == 0xb200u || before_pc == 0xb315u) {
                unsigned int child;
                if (entrance_child_count >= 4u) return 69;
                child = before_pc == 0xb0e9u ? 1u :
                    (before_pc == 0xb21fu ? 2u : (before_pc == 0xb200u ? 3u : 4u));
                entrance_children[entrance_child_count][0] = (unsigned char)child;
                entrance_children[entrance_child_count][1] = driver->machine->a;
                memcpy(entrance_children[entrance_child_count] + 2u,
                       driver->machine->ram, 2048u);
                entrance_child_stack = driver->machine->s;
                entrance_child_return = (lib_u16)(1u +
                    driver->machine->ram[0x100u + (lib_u8)(entrance_child_stack + 1u)] +
                    256u * driver->machine->ram[0x100u + (lib_u8)(entrance_child_stack + 2u)]);
                entrance_child_active = child;
            }
        }
        if (movement_snapshot_path != NULL && background_snapshot == 3u &&
            elapsed >= warmup_frames && t26_fixture >= 741u && t26_fixture <= 762u) {
            if (movement_snapshot_phase == 0u && before_pc == 0xb069u) {
                memcpy(movement_snapshots, driver->machine->ram, 2048u);
                movement_snapshot_phase = 1u;
            }
            else if (movement_snapshot_phase == 1u && before_pc == 0xaef6u) {
                memcpy(movement_snapshots + 2048u, driver->machine->ram, 2048u);
                movement_snapshot_phase = 2u;
            }
        }
        /* Read-only ScrollHandler boundary from the real pipe caller.
         * $b1ed is its JSR successor; no synthetic return is installed. */
        if (movement_snapshot_path != NULL && background_snapshot == 2u &&
            elapsed >= warmup_frames && t26_fixture >= 717u && t26_fixture <= 740u) {
            if (movement_snapshot_phase == 0u && before_pc == 0xaf93u) {
                memcpy(movement_snapshots, driver->machine->ram, 2048u);
                movement_snapshot_phase = 1u;
            }
            else if (movement_snapshot_phase == 1u && before_pc == 0xb1edu) {
                memcpy(movement_snapshots + 2048u, driver->machine->ram, 2048u);
                movement_snapshot_phase = 2u;
            }
        }
        /* Observe the real normal-enemy call and its natural successor.
         * Never change PC, stack, registers, RAM, or the frame record. The
         * fixed fixture family supplies one actor in the recorded NMI. */
        if (movement_snapshot_path != NULL && elapsed >= warmup_frames &&
            ((background_snapshot == 1u && t26_fixture >= 684u && t26_fixture <= 716u) ||
             (!background_snapshot && ((t26_fixture >= 652u && t26_fixture <= 683u) ||
              (t26_fixture >= 708u && t26_fixture <= 711u))))) {
            if (movement_snapshot_phase == 0u &&
                before_pc == (background_snapshot ? 0xdfc1u : 0xca77u)) {
                memcpy(movement_snapshots, driver->machine->ram, 2048u);
                movement_snapshot_phase = 1u;
            }
            else if (movement_snapshot_phase == 1u &&
                     before_pc == (background_snapshot ?
                         (t26_fixture >= 708u && t26_fixture <= 711u ? 0xbcb0u : 0xc8f4u) :
                         (t26_fixture >= 708u ? 0xbcadu : 0xc902u))) {
                memcpy(movement_snapshots + 2048u, driver->machine->ram, 2048u);
                movement_snapshot_phase = 2u;
            }
        }
        /* Observe successful LDA (AreaData),Y instructions without changing
         * execution. Payload bytes never enter the aggregate report. */
        if (area_reads_path != NULL && elapsed >= warmup_frames &&
            before_pc >= 0x8000u && before_pc < 0xffffu &&
            driver->machine->cartridge->prg_bytes == 32768u &&
            driver->machine->cartridge->prg[before_pc - 0x8000u] == 0xb1u &&
            driver->machine->cartridge->prg[before_pc - 0x8000u + 1u] == 0xe7u)
            area_read_address = (lib_u16)(driver->machine->ram[0xe7u] +
                ((lib_u16)driver->machine->ram[0xe8u] << 8u) + driver->machine->y);
        /* ROM $efdc loads a pair of PlayerGraphicsTable bytes with X as
         * its source table offset. Record only offsets, never payload. */
        if (player_table_reads_path != NULL && elapsed >= warmup_frames &&
            before_pc == 0xefdcu && driver->machine->x < 207u) {
            ++mysmb_player_table_reads[driver->machine->x];
            ++mysmb_player_table_reads[driver->machine->x + 1u];
        }
        if (player_offset_reads_path != NULL && elapsed >= warmup_frames) {
            if ((before_pc == 0xef42u || before_pc == 0xef67u ||
                 before_pc == 0xf030u || before_pc == 0xf0d3u ||
                 before_pc == 0xf0e5u) &&
                driver->machine->y < 16u)
                ++mysmb_player_offset_reads[driver->machine->y];
            if (before_pc == 0xef2du && driver->machine->x < 2u)
                ++mysmb_swim_kick_reads[driver->machine->x];
        }
        if (core_machine_debug_step(driver->machine, 1u, 1024u, &result) !=
            LIB_STATUS_OK || result.trap_valid) break;
        /* An interrupt can redirect a debug step before the sampled opcode.
         * Count only a completed two-byte LDA, never that redirected step. */
        if (area_read_address >= 0x8000u && result.instructions == 1u &&
            driver->machine->pc == (lib_u16)(before_pc + 2u))
            ++mysmb_area_read_hits[area_read_address - 0x8000u];
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
    if (enemy_background_path != NULL && !background_write(enemy_background_path)) return 69;
    if (enemy_landing_path != NULL && !background_write(enemy_landing_path)) return 69;
    if (metatile_path != NULL && !metatile_write(metatile_path)) return 69;
    if (movement_snapshot_path != NULL) {
        FILE *snapshot;
        int ok;
        if (movement_snapshot_phase != 2u) return 69;
        snapshot = fopen(movement_snapshot_path, "wb");
        if (snapshot == NULL) return 69;
        if ((background_snapshot >= 5u && background_snapshot <= 79u) ||
            background_snapshot == 80u) {
            unsigned char header[8] = {'M','S','T','P',1u,0u,0u,0u};
            header[5] = transition_entry == 0xb1c7u ? 1u :
                (transition_entry == 0xb206u ? 2u : (transition_entry == 0xb1e5u ? 3u : 4u));
            header[6] = transition_argument;
            if (background_snapshot == 6u) {
                header[2] = 'M';
                header[5] = transition_entry == 0xb233u ? 1u :
                    (transition_entry == 0xb245u ? 2u : (transition_entry == 0xb269u ? 3u :
                    (transition_entry == 0xb27du ? 4u : (transition_entry == 0xb288u ? 5u : 6u))));
            }
            if (background_snapshot == 7u) {
                header[2] = 'L';
                header[5] = transition_entry == 0xb2a4u ? 1u :
                    (transition_entry == 0xb2cau ? 2u : 3u);
            }
            if (background_snapshot == 8u) {
                header[2] = 'W';
                header[5] = 1u;
            }
            if (background_snapshot == 9u) {
                header[2] = 'D';
                header[5] = 1u;
            }
            if (background_snapshot == 10u) {
                header[2] = 'F';
                header[5] = 1u;
            }
            if (background_snapshot == 11u) {
                header[2] = 'B';
                header[5] = transition_entry == 0xb6f9u ? 1u : 2u;
            }
            if (background_snapshot == 79u) { header[2] = '*'; header[5] = 1u; }
            if (background_snapshot == 80u) { header[2] = 'P'; header[5] = 1u; }
            if (background_snapshot == 78u) { header[2] = ')'; header[5] = 1u; }
            if (background_snapshot == 77u) { header[2] = '$'; header[5] = 1u; }
            if (background_snapshot == 76u) { header[2] = '&'; header[5] = 1u; header[7] = coin_entry_carry; }
            if (background_snapshot == 75u) { header[2] = '%'; header[5] = transition_entry == 0xde05u ? 1u : 2u; }
            if (background_snapshot == 74u) { header[2] = '$'; header[5] = 1u; }
            if (background_snapshot == 73u) { header[2] = '#'; header[5] = transition_entry == 0xdc21u ? 1u : 2u; header[7] = coin_entry_carry; }
            if (background_snapshot == 72u) { header[2] = '@'; header[5] = transition_entry == 0xdb45u ? 1u : 2u; }
            if (background_snapshot == 71u) { header[2] = '!'; header[5] = 1u; }
            if (background_snapshot == 70u) { header[2] = '~'; header[5] = 1u; }
            if (background_snapshot == 69u) { header[2] = 'z'; header[5] = 1u; }
            if (background_snapshot == 68u) { header[2] = 'y'; header[5] = 1u; }
            if (background_snapshot == 67u) { header[2] = 'x'; header[5] = 1u; }
            if (background_snapshot == 66u) { header[2] = 'w'; header[5] = 1u; }
            if (background_snapshot == 65u) { header[2] = 'v'; header[5] = 1u; }
            if (background_snapshot == 64u) { header[2] = 'u'; header[5] = 1u; }
            if (background_snapshot == 63u) { header[2] = 't'; header[5] = 1u; }
            if (background_snapshot == 62u) { header[2] = 's'; header[5] = 1u; }
            if (background_snapshot == 61u) { header[2] = 'r'; header[5] = 1u; }
            if (background_snapshot == 60u) { header[2] = 'q'; header[5] = 1u; }
            if (background_snapshot == 59u) { header[2] = 'p'; header[5] = 1u; }
            if (background_snapshot == 58u) { header[2] = 'o'; header[5] = 1u; }
            if (background_snapshot == 57u) { header[2] = 'n'; header[5] = 1u; }
            if (background_snapshot == 56u) { header[2] = 'm'; header[5] = 1u; }
            if (background_snapshot == 55u) { header[2] = 'l'; header[5] = 1u; }
            if (background_snapshot == 54u) { header[2] = 'k'; header[5] = 1u; }
            if (background_snapshot == 53u) { header[2] = 'j'; header[5] = transition_entry == 0xcf28u ? 1u : 2u; header[7] = hammer_return_carry; }
            if (background_snapshot == 52u) { header[2] = 'i'; header[5] = 1u; }
            if (background_snapshot == 51u) { header[2] = 'h'; header[5] = 1u; }
            if (background_snapshot == 50u) { header[2] = 'g'; header[5] = 1u; }
            if (background_snapshot == 49u) { header[2] = 'f'; header[5] = 1u; }
            if (background_snapshot == 48u) { header[2] = 'e'; header[5] = 1u; }
            if (background_snapshot == 47u) { header[2] = 'd'; header[5] = transition_entry == 0xcb25u ? 1u : 2u; header[7] = transition_entry == 0xcb47u ? coin_entry_carry : 0u; }
            if (background_snapshot == 46u) { header[2] = 'c'; header[5] = transition_entry == 0xcaf9u ? 1u : 2u; }
            if (background_snapshot == 45u) { header[2] = 'b'; header[5] = transition_entry == 0xc9d8u ? 1u : 2u; }
            if (background_snapshot == 44u) header[2] = 'a';
            if (background_snapshot == 43u) {
                header[2] = '9';
                header[5] = (unsigned char)mysmb_special_actor_mode((unsigned int)(t26_fixture-3960u));
            }
            if (background_snapshot == 42u) {
                header[2] = '8';
                header[5] = transition_entry == 0xc8e0u ? 1u : 2u;
            }
            if (background_snapshot == 41u) {
                header[2] = '7';
                header[5] = transition_entry == 0xc882u ? 1u : 2u;
            }
            if (background_snapshot == 40u) {
                header[2] = '6';
                header[5] = movement_snapshots[0x16u + transition_argument];
            }
            if (background_snapshot == 39u) {
                header[2] = '5';
                header[5] = transition_entry == 0xc787u ? 1u :
                    (transition_entry == 0xc7d1u ? 2u :
                    (transition_entry == 0xc7b8u ? 3u : 4u));
            }
            if (background_snapshot == 38u) {
                header[2] = '4';
                header[5] = 1u;
            }
            if (background_snapshot == 37u) {
                header[2] = '3';
                header[5] = 1u;
            }
            if (background_snapshot == 36u) {
                header[2] = '2';
                header[5] = 1u;
            }
            if (background_snapshot == 35u) {
                header[2] = 'O';
                header[5] = transition_entry == 0xc549u ? 1u : 2u;
            }
            if (background_snapshot == 34u) {
                header[2] = 'Y';
                header[5] = 1u;
            }
            if (background_snapshot == 33u) {
                header[2] = 'A';
                header[5] = 1u;
            }
            if (background_snapshot == 32u) {
                header[2] = 'Z';
                header[5] = 1u;
            }
            if (background_snapshot == 31u) {
                header[2] = 'S';
                header[5] = 1u;
            }
            if (background_snapshot == 30u) {
                header[2] = 'E';
                header[5] = 1u;
            }
            if (background_snapshot == 29u) {
                header[2] = '9';
                header[5] = (unsigned char)((t26_fixture - 1986u) / 8u);
                header[7] = coin_entry_carry;
            }
            if (background_snapshot == 28u) {
                header[2] = 'V';
                header[5] = (unsigned char)((t26_fixture - 1954u) / 4u);
                header[7] = hammer_return_carry;
            }
            if (background_snapshot == 27u) {
                header[2] = 'X';
                header[5] = transition_entry == 0xbf09u ? 1u : (transition_entry == 0xbf02u ? 2u : 3u);
                header[7] = hammer_return_carry;
            }
            if (background_snapshot == 26u) {
                header[2] = 'R';
                header[5] = 1u;
            }
            if (background_snapshot == 25u) {
                header[2] = 'L';
                header[5] = 1u;
            }
            if (background_snapshot == 24u) {
                header[2] = 'Q';
                header[5] = 1u;
            }
            if (background_snapshot == 23u) {
                header[2] = 'K';
                header[5] = 1u;
            }
            if (background_snapshot == 22u) {
                header[2] = 'H';
                header[5] = 1u;
            }
            if (background_snapshot == 21u) {
                header[2] = '7';
                header[5] = 1u;
            }
            if (background_snapshot == 20u) {
                header[2] = '6';
                header[5] = transition_entry == 0xbc49u ? 1u : 2u;
                header[7] = hammer_return_carry;
            }
            if (background_snapshot == 19u) {
                header[2] = 'S';
                header[5] = transition_entry == 0xbbfeu ? 1u :
                    (transition_entry == 0xbc27u ? 2u :
                    (transition_entry == 0xbc30u ? 3u : 4u));
                header[7] = hammer_return_carry;
            }
            if (background_snapshot == 18u) {
                header[2] = 'U';
                header[5] = 1u;
            }
            if (background_snapshot == 17u) {
                header[2] = 'Q';
                header[5] = transition_entry == 0xbb38u ? 1u : 2u;
                header[7] = coin_entry_carry;
            }
            if (background_snapshot == 16u) {
                header[2] = 'H';
                header[5] = transition_entry == 0xba94u ? 1u : 2u;
                header[7] = hammer_return_carry;
            }
            if (background_snapshot == 15u) {
                header[2] = 'I';
                header[5] = 1u;
            }
            if (background_snapshot == 14u) {
                header[2] = 'V';
                header[5] = 1u;
                header[7] = vine_block_slot;
            }
            if (background_snapshot == 13u) {
                header[2] = 'J';
                header[5] = 1u;
            }
            if (background_snapshot == 12u) {
                header[2] = 'G';
                header[5] = 1u;
            }
            ok = fwrite(header,1u,8u,snapshot) == 8u &&
                fwrite(movement_snapshots,1u,4096u,snapshot) == 4096u;
        }
        else {
        ok = fwrite(background_snapshot == 4u ? "MSPC\1\0\0\0" :
                    (background_snapshot == 3u ? "MSEN\1\0\0\0" :
                    (background_snapshot == 2u ? "MSSC\1\0\0\0" :
                    (background_snapshot ? "MSNB\1\0\0\0" : "MSNM\1\0\0\0"))),
                    1u, 8u, snapshot) == 8u &&
             fwrite(movement_snapshots, 1u, 4096u, snapshot) == 4096u;
        }
        if (fclose(snapshot) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (entrance_children_path != NULL) {
        FILE *children;
        unsigned char header[8] = { 'M','S','E','C',1u,0u,0u,0u };
        unsigned int child;
        int ok;
        if (t26_fixture == 23u) {
            if (entrance_child_count != 1u || entrance_child_active != 0u)
                return 69;
            header[2] = 'I';
        }
        else if ((background_snapshot < 3u || background_snapshot > 80u) ||
                 movement_snapshot_phase != 2u ||
                 entrance_child_active != 0u) return 69;
        if (background_snapshot == 4u) header[2] = 'P';
        if (background_snapshot == 5u) header[2] = 'T';
        if (background_snapshot == 6u) header[2] = 'M';
        if (background_snapshot == 7u) header[2] = 'L';
        if (background_snapshot == 8u) header[2] = 'W';
        if (background_snapshot == 9u) header[2] = 'D';
        if (background_snapshot == 11u) header[2] = 'B';
        if (background_snapshot == 10u) header[2] = 'F';
        if (background_snapshot == 12u) header[2] = 'G';
        if (background_snapshot == 13u) header[2] = 'J';
        if (background_snapshot == 15u) header[2] = 'I';
        if (background_snapshot == 16u) header[2] = 'H';
        if (background_snapshot == 17u) header[2] = 'Q';
        if (background_snapshot == 18u) header[2] = 'U';
        if (background_snapshot == 19u) header[2] = 'S';
        if (background_snapshot == 20u) header[2] = '6';
        if (background_snapshot == 21u) header[2] = '7';
        if (background_snapshot == 22u) header[2] = 'H';
        if (background_snapshot == 23u) header[2] = 'K';
        if (background_snapshot == 24u) header[2] = 'Q';
        if (background_snapshot == 25u) header[2] = 'L';
        if (background_snapshot == 26u) header[2] = 'R';
        if (background_snapshot == 28u) header[2] = 'V';
        if (background_snapshot == 30u) header[2] = 'E';
        if (background_snapshot == 31u) header[2] = 'S';
        if (background_snapshot == 32u) header[2] = 'Z';
        if (background_snapshot == 33u) header[2] = 'A';
        if (background_snapshot == 77u) header[2] = '(';
        if (background_snapshot == 76u) header[2] = '&';
        if (background_snapshot == 75u) header[2] = '%';
        if (background_snapshot == 74u) header[2] = '$';
        if (background_snapshot == 72u) header[2] = '@';
        if (background_snapshot == 71u) header[2] = '!';
        if (background_snapshot == 70u) header[2] = '~';
        if (background_snapshot == 69u) header[2] = 'z';
        if (background_snapshot == 68u) header[2] = 'y';
        if (background_snapshot == 67u) header[2] = 'x';
        if (background_snapshot == 66u) header[2] = 'w';
        if (background_snapshot == 65u) header[2] = 'v';
        if (background_snapshot == 64u) header[2] = 'u';
        if (background_snapshot == 63u) header[2] = 't';
        if (background_snapshot == 62u) header[2] = 's';
        if (background_snapshot == 61u) header[2] = 'r';
        if (background_snapshot == 60u) header[2] = 'q';
        if (background_snapshot == 59u) header[2] = 'p';
        if (background_snapshot == 58u) header[2] = 'o';
        if (background_snapshot == 57u) header[2] = 'n';
        if (background_snapshot == 56u) header[2] = 'm';
        if (background_snapshot == 55u) header[2] = 'l';
        if (background_snapshot == 54u) header[2] = 'k';
        if (background_snapshot == 53u) header[2] = 'j';
        if (background_snapshot == 52u) header[2] = 'i';
        if (background_snapshot == 51u) header[2] = 'h';
        if (background_snapshot == 50u) header[2] = 'g';
        if (background_snapshot == 49u) header[2] = 'f';
        if (background_snapshot == 48u) header[2] = 'e';
        if (background_snapshot == 47u) header[2] = 'd';
        if (background_snapshot == 46u) header[2] = 'c';
        if (background_snapshot == 45u) header[2] = 'b';
        if (background_snapshot == 44u) header[2] = 'a';
        if (background_snapshot == 80u) header[2] = 'P';
        if (background_snapshot == 43u) header[2] = '9';
        if (background_snapshot == 42u) header[2] = '8';
        if (background_snapshot == 41u) header[2] = '7';
        if (background_snapshot == 40u) header[2] = '6';
        if (background_snapshot == 39u) header[2] = '5';
        if (background_snapshot == 38u) header[2] = '4';
        if (background_snapshot == 37u) header[2] = '3';
        if (background_snapshot == 36u) header[2] = '2';
        if (background_snapshot == 35u) header[2] = 'O';
        if (background_snapshot == 34u) header[2] = 'Y';
        header[5] = (unsigned char)entrance_child_count;
        children = fopen(entrance_children_path, "wb");
        if (children == NULL) return 69;
        ok = fwrite(header, 1u, 8u, children) == 8u;
        for (child = 0u; child < entrance_child_count; ++child)
            if (fwrite(entrance_children[child], 1u, 4098u, children) != 4098u) ok = 0;
        if (fclose(children) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (player_table_reads_path != NULL) {
        FILE *reads = fopen(player_table_reads_path, "w");
        unsigned int offset;
        int ok;
        if (reads == NULL) return 69;
        ok = fprintf(reads, "offset,reads\n") >= 0;
        for (offset = 0u; offset < 208u && ok; ++offset)
            if (mysmb_player_table_reads[offset] != 0ul)
                ok = fprintf(reads, "%u,%lu\n", offset,
                             mysmb_player_table_reads[offset]) >= 0;
        if (fclose(reads) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (sprite_row_child_path != NULL) {
        FILE *children;
        unsigned char header[8] = { 'M', 'S', 'S', 'O', 1u, 0u, 0u, 0u };
        unsigned int child;
        int ok;
        if (sprite_row_child_count == 0u ||
            sprite_row_child_active != 0u) return 69;
        header[5] = (unsigned char)sprite_row_child_count;
        children = fopen(sprite_row_child_path, "wb");
        if (children == NULL) return 69;
        ok = fwrite(header, 1u, 8u, children) == 8u;
        for (child = 0u; child < sprite_row_child_count; ++child)
            if (fwrite(sprite_row_children[child], 1u, 4100u, children) !=
                4100u) ok = 0;
        if (fclose(children) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (sound_child_path != NULL) {
        FILE *children;
        unsigned char header[8] = { 'M', 'S', 'S', 'N', 1u, 0u, 0u, 0u };
        unsigned int child;
        int ok;
        if (sound_child_count == 0u || sound_child_active != 0u) return 69;
        header[5] = (unsigned char)sound_child_count;
        children = fopen(sound_child_path, "wb");
        if (children == NULL) return 69;
        ok = fwrite(header, 1u, 8u, children) == 8u;
        for (child = 0u; child < sound_child_count; ++child)
            if (fwrite(sound_children[child], 1u, 4144u, children) !=
                4144u) ok = 0;
        if (fclose(children) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (sound_helper_path != NULL) {
        FILE *helpers;
        unsigned char header[8] = { 'M', 'S', 'A', 'H', 1u, 0u, 0u, 0u };
        unsigned int helper;
        int ok;
        if (sound_helper_count == 0u || sound_helper_count > 255u)
            return 69;
        for (helper = 0u; helper < 9u; ++helper)
            if (sound_helper_active[helper] != 0u) return 69;
        header[5] = (unsigned char)sound_helper_count;
        helpers = fopen(sound_helper_path, "wb");
        if (helpers == NULL) return 69;
        ok = fwrite(header, 1u, 8u, helpers) == 8u;
        for (helper = 0u; helper < sound_helper_count; ++helper)
            if (fwrite(sound_helpers[helper], 1u, 58u, helpers) != 58u)
                ok = 0;
        if (fclose(helpers) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (player_action_child_path != NULL) {
        FILE *children;
        unsigned char header[8] = { 'M','S','A','C',1u,0u,0u,0u };
        unsigned int child;
        int ok;
        if (player_action_child_count == 0u ||
            player_action_child_active != 0u) return 69;
        header[5] = (unsigned char)player_action_child_count;
        children = fopen(player_action_child_path, "wb");
        if (children == NULL) return 69;
        ok = fwrite(header, 1u, 8u, children) == 8u;
        for (child = 0u; child < player_action_child_count; ++child)
            if (fwrite(player_action_children[child], 1u, 4098u, children) !=
                4098u) ok = 0;
        if (fclose(children) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (player_size_child_path != NULL) {
        FILE *children;
        unsigned char header[8] = { 'M', 'S', 'S', 'C', 1u, 0u, 0u, 0u };
        unsigned int child;
        int ok;
        if (player_size_child_count == 0u ||
            player_size_child_active != 0u) return 69;
        header[5] = (unsigned char)player_size_child_count;
        children = fopen(player_size_child_path, "wb");
        if (children == NULL) return 69;
        ok = fwrite(header, 1u, 8u, children) == 8u;
        for (child = 0u; child < player_size_child_count; ++child)
            if (fwrite(player_size_children[child], 1u, 4098u, children) !=
                4098u) ok = 0;
        if (fclose(children) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (relative_child_path != NULL) {
        FILE *children;
        unsigned char header[8] = { 'M', 'S', 'R', 'C', 2u, 0u, 0u, 0u };
        unsigned int child;
        int ok;
        if (relative_child_count == 0u ||
            relative_child_active != 0u) return 69;
        header[5] = (unsigned char)relative_child_count;
        children = fopen(relative_child_path, "wb");
        if (children == NULL) return 69;
        ok = fwrite(header, 1u, 8u, children) == 8u;
        for (child = 0u; child < relative_child_count; ++child)
            if (fwrite(relative_children[child], 1u, 4100u, children) !=
                4100u) ok = 0;
        if (fclose(children) != 0) ok = 0;
        if (!ok) return 69;
    }
    if (player_offset_reads_path != NULL) {
        FILE *reads = fopen(player_offset_reads_path, "w");
        unsigned int index;
        int ok;
        if (reads == NULL) return 69;
        ok = fprintf(reads, "source,index,reads\n") >= 0;
        for (index = 0u; index < 16u && ok; ++index)
            if (mysmb_player_offset_reads[index] != 0ul)
                ok = fprintf(reads, "offset,%u,%lu\n", index,
                             mysmb_player_offset_reads[index]) >= 0;
        for (index = 0u; index < 2u && ok; ++index)
            if (mysmb_swim_kick_reads[index] != 0ul)
                ok = fprintf(reads, "kick,%u,%lu\n", index,
                             mysmb_swim_kick_reads[index]) >= 0;
        if (fclose(reads) != 0) ok = 0;
        if (!ok) return 69;
    }
    return mysmb_reference_write_coverage(coverage_path) &&
           mysmb_reference_write_area_reads(area_reads_path) ? 0 : 69;
}
