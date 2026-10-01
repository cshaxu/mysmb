#include <stdio.h>
#include <stdlib.h>

#include "game/area.h"
#include "game/frame_root.h"
#include "game/frame_snapshot.h"
#include "castle_column_fixture.h"
#include "block_row_column_fixture.h"
#include "cannon_fixture.h"
#include "staircase_fixture.h"
#include "jumpspring_fixture.h"
#include "item_block_fixture.h"
#include "hole_underpart_fixture.h"
#include "area_helper_fixture.h"
#include "parser_boundary_fixture.h"
#include "pipe_tail_fixture.h"
#include "block_address_fixture.h"
#include "area_pointer_fixture.h"
#include "castle_scene_fixture.h"
#include "ground_scene_fixture.h"
#include "underground_scene_fixture.h"
#include "water_scene_fixture.h"
#include "game_entry_fixture.h"
#include "engine_tail_fixture.h"
#include "engine_slots_fixture.h"
#include "engine_environment_fixture.h"
#include "engine_warp_fixture.h"
#include "engine_normal_fixture.h"
#include "scroll_fixture.h"
#include "entrance_fixture.h"
#include "player_control_fixture.h"
#include "player_transition_fixture.h"
#include "player_modes_fixture.h"
#include "player_end_level_fixture.h"
#include "player_movement_fixture.h"
#include "engine_cannon_fixture.h"
#include "timer_fixture.h"
#include "vine_setup_fixture.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

/* Owner-local trace writer for M2 T10.  Its record body deliberately matches
 * the reference recorder: ordinal, RAM, two physical CIRAM pages, palette,
 * OAM, then the seven PPU-visible scalar bytes.  Its script byte uses MySMB's
 * decoded masks, where Start=$10 and Right=$01; this intentionally differs
 * from the reference recorder's NES serial controller bit order.  The output
 * is protected derived data and must be written only below an ignored build
 * directory. */
static mysmb_u8 mysmb_recorder_write(FILE *output, const void *bytes,
                                     unsigned long count)
{
    return fwrite(bytes, 1U, count, output) == count ? 1U : 0U;
}

static mysmb_u8 mysmb_recorder_script_buttons(const char *script,
                                              unsigned long frame,
                                              unsigned long maximum_frame,
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
        if (next == cursor || change_frame > maximum_frame ||
            change_buttons > 0xffUL) return 0U;
        if (change_frame > frame) return 1U;
        *buttons = (mysmb_u8)change_buttons;
        if (*next == '\0') return 1U;
        if (*next != ',') return 0U;
        cursor = next + 1;
    }
    return 1U;
}

static int mysmb_recorder_parse_warmup(const char *argument,
                                       unsigned long *warmup)
{
    static const char prefix[] = "--warmup=";
    unsigned int index;
    char *next;
    unsigned long parsed;

    for (index = 0U; prefix[index] != '\0'; ++index) {
        if (argument[index] != prefix[index]) return 0;
    }
    parsed = strtoul(argument + index, &next, 10);
    if (next == argument + index || *next != '\0' || parsed > 3600UL)
        return -1;
    *warmup = parsed;
    return 1;
}

struct mysmb_recorder_ram_write {
    unsigned long frame;
    mysmb_u16 address;
    mysmb_u8 value;
    mysmb_u8 present;
};

/* Controlled branch preconditions belong only to this owner-local recorder;
 * they cannot be reached by any product or platform input path. */
static int mysmb_recorder_parse_ram_write(
    const char *argument, struct mysmb_recorder_ram_write *write)
{
    static const char prefix[] = "--ram-write=";
    unsigned int index;
    char *next;
    unsigned long frame;
    unsigned long address;
    unsigned long value;

    if (write->present != 0U) return -1;
    for (index = 0U; prefix[index] != '\0'; ++index) {
        if (argument[index] != prefix[index]) return 0;
    }
    frame = strtoul(argument + index, &next, 0);
    if (next == argument + index || *next != ':') return -1;
    address = strtoul(next + 1, &next, 0);
    if (*next != ':' || address > 0x07ffUL) return -1;
    value = strtoul(next + 1, &next, 0);
    if (*next != '\0' || value > 0xffUL) return -1;
    write->frame = frame;
    write->address = (mysmb_u16)address;
    write->value = (mysmb_u8)value;
    write->present = 1U;
    return 1;
}
static mysmb_u8 mysmb_recorder_equals(const char *left, const char *right)
{
    while (*left != '\0' && *right != '\0' && *left == *right) {
        ++left;
        ++right;
    }
    return *left == '\0' && *right == '\0' ? 1U : 0U;
}

/* Fixed T26 source-route precondition.  This is deliberately not a general
 * RAM mutation interface: it prepares GameCoreRoutine's slot-zero pass for
 * the FloateyNumbersRoutine 1-UP branch at its original NMI boundary. */
static void mysmb_recorder_apply_t26_floatey_fixture(struct mysmb_game *game)
{
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 3U;
    game->ram[0x000eU] = 8U;
    game->ram[0x000fU] = 0U;
    game->ram[0x0016U] = 9U;
    game->ram[0x001eU] = 2U;
    game->ram[0x071fU] = 7U;
    game->ram[0x0110U] = 0x0bU;
    game->ram[0x0117U] = 0x80U;
    game->ram[0x011eU] = 0x40U;
    game->ram[0x012cU] = 0x2bU;
    game->ram[0x06e5U] = 0x20U;
    game->ram[0x075aU] = 2U;
}

/* Fixed T26 Floatey leaves: timer zero clears the control without drawing;
 * the numeric route takes ScoreUpdateData[$06] and GetAltOffset before it
 * writes the two score sprites. */
static void mysmb_recorder_apply_t26_floatey_leaf_fixture(
    struct mysmb_game *game, mysmb_u8 kind)
{
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 3U;
    game->ram[0x000eU] = 8U;
    game->ram[0x000fU] = 0U;
    game->ram[0x0016U] = kind == 0U ? 9U : 0U;
    game->ram[0x001eU] = 0U;
    game->ram[0x071fU] = 7U;
    game->ram[0x0110U] = kind == 0U ? 2U : 6U;
    game->ram[0x0117U] = 0x40U;
    game->ram[0x011eU] = kind == 0U ? 0x40U : 0x10U;
    game->ram[0x012cU] = kind == 0U ? 0U : 0x2bU;
    game->ram[0x06e5U] = 0x20U;
    game->ram[0x03eeU] = 1U;
    game->ram[0x06edU] = 0x40U;
}

/* Fixed T26 terminal precondition for PlayerEndWorld's world-eight B path. */
static void mysmb_recorder_apply_t26_endworld_b_fixture(struct mysmb_game *game)
{
    game->ram[0x0770U] = 2U;
    game->ram[0x0772U] = 4U;
    game->ram[0x075fU] = 7U;
    game->ram[0x07a1U] = 0U;
    game->ram[0x06fcU] = MYSMB_BUTTON_B;
    game->ram[0x06fdU] = 0U;
}

/* Fixed T26 PlayerEndWorld precondition for the ordinary next-world path. */
static void mysmb_recorder_apply_t26_endworld_next_fixture(struct mysmb_game *game)
{
    game->ram[0x0770U] = 2U;
    game->ram[0x0772U] = 4U;
    game->ram[0x075fU] = 2U;
    game->ram[0x0760U] = 3U;
    game->ram[0x075cU] = 2U;
    game->ram[0x0757U] = 0U;
    game->ram[0x07a1U] = 0U;
}

/* Fixed T26 PlayerEndWorld return leaves: the first keeps the world-end
 * timer nonzero while timer control suppresses DecTimers; the second reaches
 * World8's B test with neither controller latch set. */
static void mysmb_recorder_apply_t26_endworld_return_fixture(
    struct mysmb_game *game, mysmb_u8 kind)
{
    game->ram[0x0770U] = 2U;
    game->ram[0x0772U] = 4U;
    game->ram[0x00fcU] = 0U;
    game->ram[0x06fcU] = 0U;
    game->ram[0x06fdU] = 0U;
    if (kind == 0U) {
        game->ram[0x075fU] = 2U;
        game->ram[0x07a1U] = 5U;
        game->ram[0x0747U] = 1U;
        return;
    }
    game->ram[0x075fU] = 7U;
    game->ram[0x07a1U] = 0U;
}

/* Fixed T26 PrintVictoryMessages preconditions: first text, world-eight
 * music text, and the non-world-eight end-timer branch. */
static void mysmb_recorder_apply_t26_victory_message_fixture(
    struct mysmb_game *game, mysmb_u8 primary, mysmb_u8 secondary,
    mysmb_u8 player, mysmb_u8 world)
{
    game->ram[0x0770U] = 2U;
    game->ram[0x0772U] = 3U;
    game->ram[0x0719U] = primary;
    game->ram[0x0749U] = secondary;
    game->ram[0x0753U] = player;
    game->ram[0x075fU] = world;
    game->ram[0x00fcU] = 0U;
    game->ram[0x07a1U] = 0U;
}

/* Fixed T26 SetupVictoryMode and PlayerVictoryWalk preconditions. */
static void mysmb_recorder_apply_t26_victory_walk_fixture(
    struct mysmb_game *game, mysmb_u8 kind)
{
    game->ram[0x0770U] = 2U;
    game->ram[0x00fcU] = 0U;
    if (kind == 0U) {
        game->ram[0x0772U] = 1U;
        game->ram[0x071bU] = 1U;
        return;
    }
    game->ram[0x0772U] = 2U;
    game->ram[0x0034U] = 1U;
    game->ram[0x0086U] = 0x60U;
    game->ram[0x071aU] = kind == 1U ? 1U : 0U;
    game->ram[0x071bU] = kind == 1U ? 1U : 0U;
    game->ram[0x071cU] = 0U;
    game->ram[0x071dU] = 0xffU;
    game->ram[0x006dU] = kind == 1U ? 1U : 0U;
    game->ram[0x0035U] = 0U;
    game->ram[0x0768U] = 0U;
}

/* Fixed T26 outer-dispatch precondition.  Bowser's front slot deliberately
 * contains no Bowser, so ROM BridgeCollapse takes SetM2: it queues Silence
 * and advances the victory task before VictoryMode's shared collaborators.
 * This records the T26 handoff without claiming the bridge or enemy owners. */
static void mysmb_recorder_apply_t26_victory_bridge_handoff_fixture(
    struct mysmb_game *game)
{
    game->ram[0x0770U] = 2U;
    game->ram[0x0772U] = 0U;
    game->ram[0x0368U] = 0U;
    game->ram[0x0016U] = 0U;
    game->ram[0x00fcU] = 0U;
}

/* Direct ROM inputs for a repeatable VictoryMode/AutoPlayer standing route.
 * Sprite0HitDetectFlag is zero so the source NMI takes SkipSprite0 rather
 * than waiting for a fixture-unrelated physical sprite-zero hit. */
static void mysmb_recorder_apply_t26_victory_outer_player_fixture(
    struct mysmb_game *game)
{
    mysmb_recorder_apply_t26_victory_bridge_handoff_fixture(game);
    game->ram[0x000eU] = 8U; game->ram[0x000fU] = 0U;
    game->ram[0x0016U] = 0U; game->ram[0x001dU] = 0U;
    game->ram[0x0033U] = 1U; game->ram[0x0045U] = 1U;
    game->ram[0x0057U] = 0U; game->ram[0x006dU] = 0U;
    game->ram[0x0086U] = 0x30U; game->ram[0x009fU] = 0U;
    game->ram[0x00b5U] = 1U; game->ram[0x00ceU] = 0x80U;
    game->ram[0x03c4U] = 0U; game->ram[0x03d0U] = 0U;
    game->ram[0x06e4U] = 0U; game->ram[0x0700U] = 0U;
    game->ram[0x0704U] = 0U; game->ram[0x070bU] = 0U;
    game->ram[0x070cU] = 1U; game->ram[0x070dU] = 0U;
    game->ram[0x0714U] = 0U; game->ram[0x071aU] = 0U;
    game->ram[0x071bU] = 0U; game->ram[0x071cU] = 0U;
    game->ram[0x071dU] = 0xffU; game->ram[0x071fU] = 7U;
    game->ram[0x0722U] = 0U; game->ram[0x0754U] = 1U;
    game->ram[0x0781U] = 1U; game->ram[0x079eU] = 0U;
}

/* Fixed T27 ScreenRoutines inputs.  These are recorder-only snapshots at an
 * NMI boundary; no product or platform path can select them. */
static void mysmb_recorder_apply_t27_screen_fixture(struct mysmb_game *game,
                                                    mysmb_u8 kind)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x07a0U] = 0U;
    game->ram[0x0774U] = 1U;
    game->ram[0x0759U] = 0U;
    game->ram[0x0769U] = 0U;
    game->ram[0x077aU] = 0U;
    game->ram[0x0753U] = 0U;
    if (kind == 14U) {
        game->ram[0x073cU] = 3U;
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        return;
    }
    if (kind == 15U) {
        game->ram[0x073cU] = 14U;
        game->ram[0x0770U] = 0U;
        game->ram[0x0772U] = 1U;
        return;
    }
    game->ram[0x073cU] = kind == 0U || kind == 3U ||
        kind == 8U || kind == 9U ? 4U :
        (kind == 5U || kind == 6U ? 5U :
        (kind == 12U || kind == 13U ? 7U : 6U));
    if (kind == 0U) {
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        game->ram[0x0759U] = 1U;
        return;
    }
    if (kind == 1U) {
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        game->ram[0x0752U] = 0U;
        game->ram[0x074eU] = 3U;
        game->ram[0x0769U] = 1U;
        return;
    }
    if (kind == 3U) {
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        return;
    }
    if (kind == 4U) {
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        game->ram[0x0752U] = 0U;
        game->ram[0x074eU] = 1U;
        return;
    }
    if (kind == 5U || kind == 6U) {
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        game->ram[0x07a0U] = kind == 5U ? 1U : 0U;
        return;
    }
    if (kind == 7U) {
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        game->ram[0x0752U] = 1U;
        return;
    }
    if (kind == 8U || kind == 9U) {
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        game->ram[0x0759U] = 1U;
        game->ram[0x077aU] = 1U;
        game->ram[0x0753U] = kind == 8U ? 0U : 1U;
        return;
    }
    if (kind == 10U || kind == 11U) {
        game->ram[0x0770U] = 3U;
        game->ram[0x0772U] = 1U;
        game->ram[0x077aU] = 1U;
        game->ram[0x0753U] = kind == 10U ? 1U : 0U;
        return;
    }
    if (kind == 12U || kind == 13U) {
        game->ram[0x0770U] = 1U;
        game->ram[0x0772U] = 1U;
        game->ram[0x07a0U] = kind == 12U ? 1U : 0U;
        return;
    }
    game->ram[0x0770U] = 3U;
    game->ram[0x0772U] = 1U;
}

/* Fixed T28 entry to the matching TitleScreenMode -> ScreenRoutines -> InitScreen
 * route.  This is recorder-only state at a native frame boundary; the normal
 * translated mode selector remains responsible for dispatch. */
static void mysmb_recorder_apply_t28_init_screen_fixture(struct mysmb_game *game)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x07a0U] = 0U;
    game->ram[0x0774U] = 1U;
    game->ram[0x0759U] = 0U;
    game->ram[0x0769U] = 0U;
    game->ram[0x077aU] = 0U;
    game->ram[0x0753U] = 0U;
    game->ram[0x073cU] = 0U;
    game->ram[0x0770U] = 0U;
    game->ram[0x0772U] = 1U;
}

/* Prepare the original Buffer1 byte protocol at a native frame boundary.
 * FrameRoot consumes it through its ordinary shared NMI path on this frame. */
static void mysmb_recorder_apply_t28_vram_fixture(struct mysmb_game *game,
                                                   mysmb_u8 kind)
{
    game->ram[0x0773U] = 0U;
    game->ram[0x0300U] = kind == 0U ? 5U : 7U;
    game->ram[0x0301U] = 0x20U;
    game->ram[0x0302U] = 0x00U;
    if (kind == 0U) {
        game->ram[0x0303U] = 0x43U;
        game->ram[0x0304U] = 0x29U;
        game->ram[0x0305U] = 0U;
    }
    else {
        game->ram[0x0303U] = 0x83U;
        game->ram[0x0304U] = 0x11U;
        game->ram[0x0305U] = 0x22U;
        game->ram[0x0306U] = 0x33U;
        game->ram[0x0307U] = 0U;
    }
}

/* T28/S7 enters the ordinary GameMode -> GameCoreRoutine -> GameEngine timer
 * tail.  This prepares only source RAM at a frame boundary; dispatch remains
 * in the shared game root. */
static void mysmb_recorder_apply_t28_status_timer_fixture(struct mysmb_game *game)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 3U;
    game->ram[0x000eU] = 8U;
    game->ram[0x00b5U] = 0U;
    game->ram[0x0787U] = 0U;
    game->ram[0x07f8U] = 1U;
    game->ram[0x07f9U] = 0U;
    game->ram[0x07faU] = 2U;
}

static void mysmb_recorder_apply_t28_status_timer_borrow_fixture(
    struct mysmb_game *game)
{
    mysmb_recorder_apply_t28_status_timer_fixture(game);
    game->ram[0x07faU] = 0U;
}

static void mysmb_recorder_apply_t28_top_score_fixture(struct mysmb_game *game,
                                                        mysmb_u8 copy)
{
    game->ram[0x07d7U] = 1U;
    game->ram[0x07d8U] = 2U;
    game->ram[0x07d9U] = copy != 0U ? 3U : 4U;
    game->ram[0x07ddU] = 1U;
    game->ram[0x07deU] = 2U;
    game->ram[0x07dfU] = copy != 0U ? 4U : 3U;
    game->ram[0x07e3U] = 1U;
    game->ram[0x07e4U] = 2U;
    game->ram[0x07e5U] = 2U;
}

/* T28/S8 uses only an NMI-boundary source-RAM precondition.  The next
 * normal mode selector invokes InitializeArea; this never redirects a PC. */
static void mysmb_recorder_apply_t28_area_entry_fixture(struct mysmb_game *game)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 0U;
}

/* This enters the normal title task-two fallthrough from PrimaryGameSetup
 * into SecondaryGameSetup, without calling either translated leaf directly. */
static void mysmb_recorder_apply_t28_secondary_setup_fixture(struct mysmb_game *game)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 0U;
    game->ram[0x0772U] = 2U;
}

/* T29/S2 mirrors the source-RAM-only GameMode task-two preconditions used by
 * the reference recorder; normal game dispatch remains the only caller. */
static void mysmb_recorder_apply_t29_area_music_fixture(struct mysmb_game *game,
                                                         mysmb_u8 kind)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 2U;
    game->ram[0x074eU] = 3U;
    game->ram[0x0710U] = 0U;
    game->ram[0x0752U] = 0U;
    game->ram[0x0743U] = 0U;
    if (kind == 0U) game->ram[0x074eU] = 1U;
    else if (kind == 1U) game->ram[0x0710U] = 6U;
    else if (kind == 2U) game->ram[0x0752U] = 2U;
    else game->ram[0x0743U] = 1U;
}

static void mysmb_recorder_apply_t29_area_entry_fixture(struct mysmb_game *game,
                                                         mysmb_u8 kind)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 3U;
    game->ram[0x000eU] = 0U;
    game->ram[0x071aU] = 3U;
    game->ram[0x074eU] = 1U;
    game->ram[0x0710U] = 2U;
    game->ram[0x0752U] = 0U;
    game->ram[0x0715U] = 2U;
    game->ram[0x0757U] = 1U;
    game->ram[0x079fU] = 0x23U;
    game->ram[0x0755U] = 0xa5U;
    if (kind == 1U) {
        game->ram[0x0752U] = 2U;
        game->ram[0x0715U] = 0U;
    }
    else if (kind == 2U) {
        game->ram[0x0758U] = 1U;
        game->ram[0x0398U] = 0U;
    }
    else if (kind == 3U) {
        game->ram[0x074eU] = 0U;
        game->ram[0x0007U] = 1U;
    }
}

/* T29/S7 uses the same source-RAM-only parser precondition as the reference
 * recorder.  GameEngine remains the caller on both sides; this fixture does
 * not enter an area-parser leaf or alter a return path. */
static void mysmb_recorder_apply_t29_parser_dispatch_fixture(
    struct mysmb_game *game)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 3U;
    game->ram[0x000eU] = 8U;
    game->ram[0x0773U] = 0U;
    game->ram[0x071fU] = 8U;
    game->ram[0x0725U] = 0U;
    game->ram[0x0726U] = 0U;
    game->ram[0x06a0U] = 0U;
    game->ram[0x0728U] = 0U;
    game->ram[0x073fU] = 0U;
}

/* Mirror the source-recorder T29/S8 fixture: the original L_GroundArea16
 * post-header stream begins at $a9d0 and its final $6d,$c5 special object is
 * at offset $2c.  The native route still enters through game tick/parser. */
static void mysmb_recorder_apply_t29_special_object_fixture(
    struct mysmb_game *game)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 3U;
    game->ram[0x000eU] = 8U;
    game->ram[0x0773U] = 0U;
    game->ram[0x071fU] = 8U;
    game->ram[0x0725U] = 1U;
    game->ram[0x0726U] = 6U;
    game->ram[0x0728U] = 0U;
    game->ram[0x072aU] = 0U;
    game->ram[0x072bU] = 0U;
    game->ram[0x072cU] = 0x2cU;
    game->ram[0x072dU] = 0U;
    game->ram[0x072eU] = 0U;
    game->ram[0x072fU] = 0U;
    game->ram[0x0730U] = 0xffU;
    game->ram[0x0731U] = 0xffU;
    game->ram[0x0732U] = 0xffU;
    game->ram[0x073fU] = 0U;
    game->ram[0x00e7U] = 0xd0U;
    game->ram[0x00e8U] = 0xa9U;
    game->ram[0x074eU] = 1U;
    game->ram[0x075fU] = 0U;
}

/* Source-RAM mirror of the original L_GroundArea1 CastleObject route. */
static void mysmb_recorder_apply_t29_geometry_castle_fixture(
    struct mysmb_game *game)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 3U;
    game->ram[0x000eU] = 8U;
    game->ram[0x0773U] = 0U;
    game->ram[0x071fU] = 8U;
    game->ram[0x0725U] = 0U;
    game->ram[0x0726U] = 0U;
    game->ram[0x0728U] = 0U;
    game->ram[0x072aU] = 0U;
    game->ram[0x072bU] = 0U;
    game->ram[0x072cU] = 2U;
    game->ram[0x072dU] = 0U;
    game->ram[0x072eU] = 0U;
    game->ram[0x072fU] = 0U;
    game->ram[0x0730U] = 0xffU;
    game->ram[0x0731U] = 0xffU;
    game->ram[0x0732U] = 0xffU;
    game->ram[0x073fU] = 0U;
    game->ram[0x00e7U] = 0x6bU;
    game->ram[0x00e8U] = 0xa4U;
}

/* Mirror the controlled ROM route for L_GroundArea6 +$0e ($68,$f2). */
static void mysmb_recorder_apply_t29_geometry_vertical_pipe_fixture(
    struct mysmb_game *game)
{
    mysmb_recorder_apply_t29_geometry_castle_fixture(game);
    game->ram[0x0725U] = 1U;
    game->ram[0x0726U] = 6U;
    game->ram[0x072aU] = 0U;
    game->ram[0x072bU] = 0U;
    game->ram[0x072cU] = 0x0eU;
    game->ram[0x00e7U] = 0x8eU;
    game->ram[0x00e8U] = 0xa6U;
    game->ram[0x0760U] = 1U;
}

/* Source-RAM mirror of L_GroundArea3's real $4c,$63 question-block row. */
static void mysmb_recorder_apply_t29_final_question_fixture(
    struct mysmb_game *game)
{
    mysmb_recorder_apply_t29_geometry_castle_fixture(game);
    game->ram[0x0726U] = 4U;
    game->ram[0x072cU] = 0x32U;
    game->ram[0x00e7U] = 0x37U;
    game->ram[0x00e8U] = 0xa5U;
}

/* Source-RAM mirror of L_GroundArea3's real $1d,$c1 FlagpoleObject route. */
static void mysmb_recorder_apply_t22_flagpole_fixture(struct mysmb_game *game)
{
    mysmb_recorder_apply_t29_geometry_castle_fixture(game);
    game->ram[0x0725U] = 14U;
    game->ram[0x0726U] = 1U;
    game->ram[0x072aU] = 13U;
    game->ram[0x072bU] = 0U;
    game->ram[0x072cU] = 2U;
    game->ram[0x00e7U] = 0x83U;
    game->ram[0x00e8U] = 0xa5U;
}

/* Source-RAM branch preconditions for the next ordinary FlagpoleRoutine tick. */
static void mysmb_recorder_apply_t22_flagpole_score_fixture(
    struct mysmb_game *game)
{
    game->ram[0x000eU] = 4U;
    game->ram[0x001dU] = 3U;
    game->ram[0x00d4U] = 0xaaU;
    game->ram[0x010fU] = 2U;
    game->ram[0x0753U] = 0U;
    game->ram[0x0716U] = 1U;
}

static void mysmb_recorder_apply_t29_special_chain_fixture(
    struct mysmb_game *game, mysmb_u8 kind)
{
    mysmb_recorder_apply_t29_special_object_fixture(game);
    if (kind == 0U) {
        game->ram[0x00e7U] = 0x39U; game->ram[0x00e8U] = 0xa5U;
        game->ram[0x072cU] = 0x4aU; game->ram[0x0725U] = 13U;
        game->ram[0x0726U] = 14U; game->ram[0x072aU] = 13U;
    }
    else if (kind == 1U) {
        game->ram[0x00e7U] = 0x91U; game->ram[0x00e8U] = 0xa8U;
        game->ram[0x072cU] = 0x1cU; game->ram[0x0725U] = 3U;
        game->ram[0x0726U] = 1U; game->ram[0x072aU] = 3U;
    }
    else {
        game->ram[0x00e7U] = 0x91U; game->ram[0x00e8U] = 0xa8U;
        game->ram[0x072cU] = 6U; game->ram[0x0725U] = 1U;
        game->ram[0x0726U] = 3U; game->ram[0x072aU] = 1U;
        game->ram[0x0733U] = 0U;
    }
}

static void mysmb_recorder_apply_t29_special_continuation_fixture(
    struct mysmb_game *game, mysmb_u8 kind)
{
    mysmb_recorder_apply_t29_special_object_fixture(game);
    if (kind == 0U) {
        mysmb_recorder_apply_t29_special_chain_fixture(game, 0U);
        game->ram[0x001aU] = 0x18U;
        return;
    }
    game->ram[0x00e7U] = 0x91U;
    game->ram[0x00e8U] = 0xa8U;
    game->ram[0x0725U] = kind <= 2U ? 3U : 1U;
    game->ram[0x0726U] = kind <= 2U ? 1U : 3U;
    game->ram[0x072aU] = game->ram[0x0725U];
    game->ram[0x072cU] = kind <= 2U ? 0x1eU : (kind == 3U ? 0x06U : 0x08U);
    game->ram[0x072fU] = kind <= 2U ? 0x1cU : 0x06U;
    game->ram[0x0730U] = 0xffU;
    game->ram[0x0731U] = 0xffU;
    game->ram[0x0732U] = kind == 1U ? 1U :
        (kind == 3U ? 0xffU : (kind == 4U ? 2U : 0U));
    game->ram[0x0733U] = kind >= 3U && kind <= 5U ? 1U : 0U;
    if (kind == 4U) game->ram[0x0736U] = 2U;
}

static void mysmb_recorder_apply_t29_warp_selector_fixture(
    struct mysmb_game *game, mysmb_u8 kind)
{
    mysmb_recorder_apply_t29_special_object_fixture(game);
    if (kind == 0U) {
        game->ram[0x000fU] = 1U;
        game->ram[0x0016U] = 13U;
    }
    else if (kind == 1U) {
        game->ram[0x075fU] = 1U;
        game->ram[0x074eU] = 1U;
    }
    else if (kind == 2U) {
        game->ram[0x075fU] = 1U;
        game->ram[0x074eU] = 2U;
    }
    else {
        game->ram[0x075fU] = 0U;
        game->ram[0x074eU] = 2U;
    }
}

static void mysmb_recorder_apply_t28_title_score_fixture(struct mysmb_game *game)
{
    game->ram[0x0770U] = 0U;
    game->ram[0x0772U] = 1U;
    game->ram[0x073cU] = 14U;
}

/* T54/S3 reaches the ordinary title-mode ScreenRoutines task-12/13 entries
 * only through a native-frame boundary.  The fixture supplies RAM state; it
 * never calls a translated title leaf directly. */
static void mysmb_recorder_apply_t54_title_task_fixture(
    struct mysmb_game *game, mysmb_u8 task)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 0U;
    game->ram[0x0772U] = 1U;
    game->ram[0x073cU] = task;
}

/* T52/S4 prepares the normal game-mode ScreenRoutines task-ten boundary.
 * The frame root remains the caller; this only supplies the source RAM state
 * for either GetBackgroundColor path. */
static void mysmb_recorder_apply_t52_background_palette_fixture(
    struct mysmb_game *game, mysmb_u8 background_control)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 1U;
    game->ram[0x073cU] = 10U;
    game->ram[0x0744U] = background_control;
    game->ram[0x074eU] = 1U;
    game->ram[0x0753U] = 0U;
    game->ram[0x0756U] = 1U;
    game->ram[0x0773U] = 0U;
    game->ram[0x0300U] = 0U;
}

/* T54/S1 exercises GetAreaPalette through every source AreaType table entry.
 * The ordinary title-mode ScreenRoutines dispatcher remains the caller. */
static void mysmb_recorder_apply_t54_area_palette_fixture(struct mysmb_game *game,
                                                           mysmb_u8 area_type)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 1U;
    game->ram[0x073cU] = 9U;
    game->ram[0x074eU] = area_type;
}

static void mysmb_recorder_apply_t54_player_palette_fixture(struct mysmb_game *game,
                                                             mysmb_u8 player,
                                                             mysmb_u8 status)
{
    mysmb_recorder_apply_t52_background_palette_fixture(game, 0U);
    game->ram[0x0753U] = player;
    game->ram[0x0756U] = status;
}

static void mysmb_recorder_apply_t54_alternate_palette_fixture(struct mysmb_game *game,
                                                                mysmb_u8 area_style)
{
    game->ram[0x0722U] = 0U;
    game->ram[0x0770U] = 1U;
    game->ram[0x0772U] = 1U;
    game->ram[0x073cU] = 11U;
    game->ram[0x0733U] = area_style;
    game->ram[0x0773U] = 0x66U;
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
        mysmb_recorder_write(output, snapshot->audio,
                             MYSMB_FRAME_SNAPSHOT_AUDIO_BYTES) &&
        mysmb_recorder_write(output, scalar, 7UL);
}

int main(int argument_count, char **arguments)
{
    static const unsigned char magic[8] = { 'M', 'S', 'F', 'N', 2U, 0U, 0U, 0U };
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_frame_snapshot snapshot;
    FILE *output;
    unsigned long parsed_frames;
    unsigned long start_frame;
    unsigned long release_frame;
    unsigned long index;
    unsigned long warmup_frames;
    unsigned long total_frames;
    mysmb_u32 frames;
    int warmup_result;
    int block_scenario;
    const char *script;
    mysmb_u8 bootstrap_title;
    unsigned int t26_fixture;
    mysmb_u8 t22_flagpole_score_pending;
    struct mysmb_recorder_ram_write ram_write = {0};

    if (argument_count < 5 || argument_count > 9) return 64;
    parsed_frames = strtoul(arguments[2], 0, 10);
    start_frame = strtoul(arguments[3], 0, 10);
    release_frame = strtoul(arguments[4], 0, 10);
    if (parsed_frames == 0UL || parsed_frames > 600UL) return 64;
    script = 0;
    bootstrap_title = 0U;
    warmup_frames = 0UL;
    ram_write.present = 0U;
    t26_fixture = 0U;
    t22_flagpole_score_pending = 0U;
    for (index = 5UL; index < (unsigned long)argument_count; ++index) {
        if (mysmb_recorder_equals(arguments[index], "--bootstrap-title") != 0U) {
            bootstrap_title = 1U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-floatey-oneup") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 1U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-endworld-b") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 2U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-first-message") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 3U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-music-message") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 4U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-end-timer") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 5U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-setup") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 6U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-no-walk") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 7U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-walk") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 8U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-endworld-next-world") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 9U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-bridge-handoff") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 10U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-luigi-message") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 11U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-retainer-message") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 12U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-counter-only") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 13U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-endworld-timer-active") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 14U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-endworld-no-b") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 15U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-floatey-timer-zero") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 16U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-floatey-numeric-alt") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 17U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t26-victory-outer-player") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 18U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-timeup") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 19U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-intermediate") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 20U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-gameover") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 21U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-no-timeup") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 22U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-player-intermediate") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 23U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-reset-pending") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 24U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-reset-expired") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 25U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-nointer-alt") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 26U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-timeup-luigi") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 27U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-timeup-mario") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 28U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-gameover-luigi") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 29U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-gameover-mario") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 30U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-task7-pending") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 31U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-task7-expired") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 32U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-bottom-status") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 33U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-screen-title-score") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 34U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-warp-text4") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 35U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-warp-text5") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 36U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t27-warp-text6") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 37U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-render-left") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 38U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-render-right") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 39U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-attribute-left") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 40U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-attribute-right") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 41U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-palette-normal") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 42U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-palette-wrap") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 43U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-palette-frame-gate") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 44U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-palette-buffer-full") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 45U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-remove-coin-water") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 46U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-write-block") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 47U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-rem-bridge") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 48U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-destroy-block") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 49U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-init-screen") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 50U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-vram-repeat") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 51U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-vram-vertical") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 52U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-status-timer") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 53U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-status-timer-borrow") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 54U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-top-score-copy") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 55U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-top-score-retain") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 56U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-area-entry") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 58U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-secondary-setup") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 59U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-area-music-normal") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 60U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-area-music-pipe") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 61U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-area-music-alternate") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 62U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-area-music-cloud") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 63U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-area-entry-normal") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 64U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-area-entry-alternate") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 65U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-area-entry-vine") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 66U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-area-entry-water") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 67U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-parser-dispatch") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 68U;
        }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t29-special-object") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 69U;
        }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-frenzy") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 70U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-pulley") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 71U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-tree") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 72U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-frenzy-present") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 73U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-pulley-rope") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 74U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-pulley-end") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 75U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-mush-start") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 76U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-mush-middle") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 77U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-mush-end") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 78U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-tree-end") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 79U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-warp-piranha") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 80U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-warp-world-ground") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 81U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-warp-world-water") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 82U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-special-warp-zero-water") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 83U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-geometry-castle") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 84U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-geometry-vertical-pipe") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 85U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t29-final-question-high") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 86U; }
        else if ((block_scenario = mysmb_player_control_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(775 + block_scenario);
        }
        else if ((block_scenario = mysmb_player_transition_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(825 + block_scenario);
        }
        else if ((block_scenario = mysmb_player_modes_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(853 + block_scenario);
        }
        else if ((block_scenario = mysmb_vine_setup_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(1292 + block_scenario);
        }
        else if ((block_scenario = mysmb_timer_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(1244 + block_scenario);
        }
        else if ((block_scenario = mysmb_player_movement_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(904 + block_scenario);
        }
        else if ((block_scenario = mysmb_player_end_level_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(875 + block_scenario);
        }
        else if ((block_scenario = mysmb_entrance_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(740 + block_scenario);
        }
        else if ((block_scenario = mysmb_scroll_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(716 + block_scenario);
        }
        else if ((block_scenario = mysmb_engine_normal_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(651 + block_scenario);
        }
        else if ((block_scenario = mysmb_engine_warp_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(641 + block_scenario);
        }
        else if ((block_scenario = mysmb_engine_cannon_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(616 + block_scenario);
        }
        else if ((block_scenario = mysmb_engine_environment_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(604 + block_scenario);
        }
        else if ((block_scenario = mysmb_engine_slots_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(602 + block_scenario);
        }
        else if ((block_scenario = mysmb_engine_tail_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(587 + block_scenario);
        }
        else if ((block_scenario = mysmb_game_entry_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(583 + block_scenario);
        }
        else if ((block_scenario = mysmb_water_scene_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(580 + block_scenario);
        }
        else if ((block_scenario = mysmb_underground_scene_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(577 + block_scenario);
        }
        else if ((block_scenario = mysmb_ground_scene_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(554 + block_scenario);
        }
        else if ((block_scenario = mysmb_castle_scene_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(547 + block_scenario);
        }
        else if ((block_scenario = mysmb_area_pointer_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(476 + block_scenario);
        }
        else if ((block_scenario = mysmb_block_address_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(428 + block_scenario);
        }
        else if ((block_scenario = mysmb_pipe_tail_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(396 + block_scenario);
        }
        else if ((block_scenario = mysmb_parser_boundary_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(372 + block_scenario);
        }
        else if ((block_scenario = mysmb_area_helper_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(352 + block_scenario);
        }
        else if ((block_scenario = mysmb_hole_underpart_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (unsigned int)(254 + block_scenario);
        }
        else if ((block_scenario = mysmb_item_block_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (mysmb_u8)(182 + block_scenario);
        }
        else if ((block_scenario = mysmb_jumpspring_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (mysmb_u8)(174 + block_scenario);
        }
        else if ((block_scenario = mysmb_staircase_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (mysmb_u8)(162 + block_scenario);
        }
        else if ((block_scenario = mysmb_cannon_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (mysmb_u8)(132 + block_scenario);
        }
        else if ((block_scenario = mysmb_block_row_column_argument(arguments[index])) != 0) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = (mysmb_u8)(100 + block_scenario);
        }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t30-column-axe") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 89U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t30-column-chain") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 90U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t30-column-bridge") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 91U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t30-column-empty") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 92U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t30-column-bridge-mid") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 93U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t30-column-bridge-end") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 94U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t22-flagpole") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 87U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t22-flagpole-score") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 88U; }
        else if (mysmb_recorder_equals(arguments[index],
                                       "--fixture=t28-title-score") != 0U) {
            if (t26_fixture != 0U) return 64;
            t26_fixture = 57U;
        }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t52-background-palette-0") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 103U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t52-background-palette-4") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 104U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t52-background-palette-5") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 105U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t52-background-palette-6") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 106U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t52-background-palette-7") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 107U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-screen-init-nmi") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 109U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-area-palette-0") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 110U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-area-palette-1") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 111U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-area-palette-2") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 112U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-area-palette-3") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 113U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-player-mario") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 114U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-player-luigi") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 115U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-player-fire") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 116U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-alternate-standard") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 117U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-alternate-mushroom") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 118U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-title-draw") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 119U; }
        else if (mysmb_recorder_equals(arguments[index], "--fixture=t54-title-clear") != 0U) { if (t26_fixture != 0U) return 64; t26_fixture = 120U; }
        else {
            warmup_result = mysmb_recorder_parse_ram_write(arguments[index],
                                                            &ram_write);
            if (warmup_result < 0) return 64;
            if (warmup_result != 0) continue;
            warmup_result = mysmb_recorder_parse_warmup(arguments[index],
                                                        &warmup_frames);
            if (warmup_result < 0) return 64;
            if (warmup_result == 0) {
                if (script != 0) return 64;
                script = arguments[index];
            }
        }
    }
    total_frames = parsed_frames + warmup_frames;
    if (total_frames < parsed_frames || total_frames > 4200UL ||
        start_frame >= release_frame || release_frame > total_frames ||
        (t26_fixture >= 35U && t26_fixture <= 52U && parsed_frames != 1UL)) return 64;
    frames = (mysmb_u32)parsed_frames;
    output = fopen(arguments[1], "wb");
    if (output == 0) return 65;
    if (mysmb_recorder_write(output, magic, 8UL) == 0U ||
        mysmb_recorder_write(output, &frames, 4UL) == 0U) {
        fclose(output);
        return 65;
    }
    mysmb_game_power_on(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_title_source(&game, mysmb_local_title_data,
                                 MYSMB_LOCAL_TITLE_DATA_SIZE,
                                 mysmb_local_title_icon_data,
                                 MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    mysmb_game_reset(&game);
    if (bootstrap_title == 0U &&
        (mysmb_game_apply_title_commands(&game, mysmb_local_title_data,
                                             MYSMB_LOCAL_TITLE_DATA_SIZE) == 0U ||
             mysmb_game_apply_vram_commands(&game, &mysmb_local_title_icon_data[1],
                                            (mysmb_u16)(MYSMB_LOCAL_TITLE_ICON_DATA_SIZE - 1U)) == 0U)) {
        fclose(output);
        return 65;
    }
    for (index = 0UL; index < total_frames; ++index) {
        input.buttons2 = 0U;
        input.buttons = index >= start_frame && index < release_frame ?
            MYSMB_BUTTON_START : 0U;
        if (mysmb_recorder_script_buttons(script, index, total_frames,
                                          &input.buttons) == 0U) {
            fclose(output);
            return 64;
        }
        if (ram_write.present != 0U && ram_write.frame == index) {
            game.ram[ram_write.address] = ram_write.value;
            ram_write.present = 0U;
        }
        if (index == warmup_frames) {
            if (t26_fixture == 1U)
                mysmb_recorder_apply_t26_floatey_fixture(&game);
            else if (t26_fixture == 2U)
                mysmb_recorder_apply_t26_endworld_b_fixture(&game);
            else if (t26_fixture == 3U)
                mysmb_recorder_apply_t26_victory_message_fixture(&game, 0U, 0U, 0U, 0U);
            else if (t26_fixture == 4U)
                mysmb_recorder_apply_t26_victory_message_fixture(&game, 3U, 0U, 0U, 7U);
            else if (t26_fixture == 5U)
                mysmb_recorder_apply_t26_victory_message_fixture(&game, 4U, 0U, 0U, 0U);
            else if (t26_fixture == 6U)
                mysmb_recorder_apply_t26_victory_walk_fixture(&game, 0U);
            else if (t26_fixture == 7U)
                mysmb_recorder_apply_t26_victory_walk_fixture(&game, 1U);
            else if (t26_fixture == 8U)
                mysmb_recorder_apply_t26_victory_walk_fixture(&game, 2U);
            else if (t26_fixture == 9U)
                mysmb_recorder_apply_t26_endworld_next_fixture(&game);
            else if (t26_fixture == 10U)
                mysmb_recorder_apply_t26_victory_bridge_handoff_fixture(&game);
            else if (t26_fixture == 11U)
                mysmb_recorder_apply_t26_victory_message_fixture(&game, 0U, 0U, 1U, 0U);
            else if (t26_fixture == 12U)
                mysmb_recorder_apply_t26_victory_message_fixture(&game, 2U, 0U, 0U, 0U);
            else if (t26_fixture == 13U)
                mysmb_recorder_apply_t26_victory_message_fixture(&game, 2U, 4U, 0U, 0U);
            else if (t26_fixture == 14U)
                mysmb_recorder_apply_t26_endworld_return_fixture(&game, 0U);
            else if (t26_fixture == 15U)
                mysmb_recorder_apply_t26_endworld_return_fixture(&game, 1U);
            else if (t26_fixture == 16U)
                mysmb_recorder_apply_t26_floatey_leaf_fixture(&game, 0U);
            else if (t26_fixture == 17U)
                mysmb_recorder_apply_t26_floatey_leaf_fixture(&game, 1U);
            else if (t26_fixture == 18U)
                mysmb_recorder_apply_t26_victory_outer_player_fixture(&game);
            else if (t26_fixture >= 19U && t26_fixture <= 34U)
                mysmb_recorder_apply_t27_screen_fixture(&game,
                    (mysmb_u8)(t26_fixture - 19U));
            else if (t26_fixture == 50U)
                mysmb_recorder_apply_t28_init_screen_fixture(&game);
            else if (t26_fixture == 51U)
                mysmb_recorder_apply_t28_vram_fixture(&game, 0U);
            else if (t26_fixture == 52U)
                mysmb_recorder_apply_t28_vram_fixture(&game, 1U);
            else if (t26_fixture == 53U)
                mysmb_recorder_apply_t28_status_timer_fixture(&game);
            else if (t26_fixture == 54U)
                mysmb_recorder_apply_t28_status_timer_borrow_fixture(&game);
            else if (t26_fixture == 55U)
                mysmb_recorder_apply_t28_top_score_fixture(&game, 1U);
            else if (t26_fixture == 56U)
                mysmb_recorder_apply_t28_top_score_fixture(&game, 0U);
            else if (t26_fixture == 57U)
                mysmb_recorder_apply_t28_title_score_fixture(&game);
            else if (t26_fixture == 109U)
                mysmb_recorder_apply_t28_init_screen_fixture(&game);
            else if (t26_fixture >= 110U && t26_fixture <= 113U)
                mysmb_recorder_apply_t54_area_palette_fixture(&game,
                    (mysmb_u8)(t26_fixture - 110U));
            else if (t26_fixture >= 114U && t26_fixture <= 116U)
                mysmb_recorder_apply_t54_player_palette_fixture(&game,
                    t26_fixture == 115U ? 1U : 0U,
                    t26_fixture == 116U ? 2U : 0U);
            else if (t26_fixture >= 117U && t26_fixture <= 118U)
                mysmb_recorder_apply_t54_alternate_palette_fixture(&game,
                    (mysmb_u8)(t26_fixture - 117U));
            else if (t26_fixture == 119U || t26_fixture == 120U)
                mysmb_recorder_apply_t54_title_task_fixture(&game,
                    t26_fixture == 119U ? 12U : 13U);
            else if (t26_fixture >= 103U && t26_fixture <= 107U)
                mysmb_recorder_apply_t52_background_palette_fixture(&game,
                    t26_fixture == 103U ? 0U : (mysmb_u8)(t26_fixture - 100U));
            else if (t26_fixture == 58U)
                mysmb_recorder_apply_t28_area_entry_fixture(&game);
            else if (t26_fixture == 59U)
                mysmb_recorder_apply_t28_secondary_setup_fixture(&game);
            else if (t26_fixture >= 60U && t26_fixture <= 63U)
                mysmb_recorder_apply_t29_area_music_fixture(&game,
                    (mysmb_u8)(t26_fixture - 60U));
            else if (t26_fixture >= 64U && t26_fixture <= 67U)
                mysmb_recorder_apply_t29_area_entry_fixture(&game,
                    (mysmb_u8)(t26_fixture - 64U));
            else if (t26_fixture == 68U)
                mysmb_recorder_apply_t29_parser_dispatch_fixture(&game);
            else if (t26_fixture == 69U)
                mysmb_recorder_apply_t29_special_object_fixture(&game);
            else if (t26_fixture >= 70U && t26_fixture <= 72U)
                mysmb_recorder_apply_t29_special_chain_fixture(&game,
                    (mysmb_u8)(t26_fixture - 70U));
            else if (t26_fixture >= 73U && t26_fixture <= 79U)
                mysmb_recorder_apply_t29_special_continuation_fixture(&game,
                    (mysmb_u8)(t26_fixture - 73U));
            else if (t26_fixture >= 80U && t26_fixture <= 83U)
                mysmb_recorder_apply_t29_warp_selector_fixture(&game,
                    (mysmb_u8)(t26_fixture - 80U));
            else if (t26_fixture == 84U)
                mysmb_recorder_apply_t29_geometry_castle_fixture(&game);
            else if (t26_fixture == 85U)
                mysmb_recorder_apply_t29_geometry_vertical_pipe_fixture(&game);
            else if (t26_fixture == 86U)
                mysmb_recorder_apply_t29_final_question_fixture(&game);
            else if (t26_fixture >= 1293U && t26_fixture <= 1308U) {
                mysmb_vine_setup_fixture(game.ram,(mysmb_u8)(t26_fixture-1293U));
            }
            else if (t26_fixture >= 1245U && t26_fixture <= 1260U) {
                mysmb_timer_fixture(game.ram,(mysmb_u8)(t26_fixture-1245U));
            }
            else if (t26_fixture >= 905U && t26_fixture <= 1150U) {
                mysmb_player_movement_fixture(game.ram,(mysmb_u8)(t26_fixture-905U));
                game.ppu_control_0 = game.ram[0x0778U];
            }
            else if (t26_fixture >= 776U && t26_fixture <= 904U) {
                if (t26_fixture <= 825U)
                    mysmb_player_control_fixture(game.ram,(mysmb_u8)(t26_fixture-776U));
                else if (t26_fixture <= 853U)
                    mysmb_player_transition_fixture(game.ram,(mysmb_u8)(t26_fixture-826U));
                else if (t26_fixture <= 875U)
                    mysmb_player_modes_fixture(game.ram,(mysmb_u8)(t26_fixture-854U));
                else mysmb_player_end_level_fixture(game.ram,(mysmb_u8)(t26_fixture-876U),mysmb_local_prg);
                game.ppu_control_0 = game.ram[0x0778U];
            }
            else if (t26_fixture >= 741U && t26_fixture <= 775U) {
                mysmb_entrance_fixture(game.ram, (mysmb_u8)(t26_fixture - 741U));
                /* These source-RAM fixtures replace the NMI input mirror.
                 * Keep its native cached representation at the same input. */
                game.ppu_control_0 = game.ram[0x0778U];
            }
            else if (t26_fixture >= 717U && t26_fixture <= 740U) {
                mysmb_scroll_fixture(game.ram, (mysmb_u8)(t26_fixture - 717U));
                game.ppu_control_0 = game.ram[0x0778U];
            }
            else if (t26_fixture >= 652U && t26_fixture <= 716U)
                mysmb_engine_normal_fixture(game.ram, (mysmb_u8)(t26_fixture - 652U));
            else if (t26_fixture >= 642U && t26_fixture <= 651U)
                mysmb_engine_warp_fixture(game.ram, (mysmb_u8)(t26_fixture - 642U));
            else if (t26_fixture >= 617U && t26_fixture <= 641U)
                mysmb_engine_cannon_fixture(game.ram, (mysmb_u8)(t26_fixture - 617U));
            else if (t26_fixture >= 605U && t26_fixture <= 616U)
                mysmb_engine_environment_fixture(game.ram, (mysmb_u8)(t26_fixture - 605U));
            else if (t26_fixture >= 603U && t26_fixture <= 604U)
                mysmb_engine_slots_fixture(game.ram, (mysmb_u8)(t26_fixture - 603U));
            else if (t26_fixture >= 588U && t26_fixture <= 602U)
                mysmb_engine_tail_fixture(game.ram, (mysmb_u8)(t26_fixture - 588U));
            else if (t26_fixture >= 584U && t26_fixture <= 587U)
                mysmb_game_entry_fixture(game.ram, (mysmb_u8)(t26_fixture - 584U));
            else if (t26_fixture >= 581U && t26_fixture <= 583U)
                mysmb_water_scene_fixture(game.ram, (mysmb_u8)(t26_fixture - 581U));
            else if (t26_fixture >= 578U && t26_fixture <= 580U)
                mysmb_underground_scene_fixture(game.ram, (mysmb_u8)(t26_fixture - 578U));
            else if (t26_fixture >= 555U && t26_fixture <= 577U)
                mysmb_ground_scene_fixture(game.ram, (mysmb_u8)(t26_fixture - 555U));
            else if (t26_fixture >= 548U && t26_fixture <= 554U)
                mysmb_castle_scene_fixture(game.ram, (mysmb_u8)(t26_fixture - 548U));
            else if (t26_fixture >= 477U && t26_fixture <= 547U)
                mysmb_area_pointer_fixture(game.ram, (mysmb_u8)(t26_fixture - 477U));
            else if (t26_fixture >= 429U && t26_fixture <= 476U)
                mysmb_block_address_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 429U));
            else if (t26_fixture >= 397U && t26_fixture <= 428U)
                mysmb_pipe_tail_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 397U));
            else if (t26_fixture >= 373U && t26_fixture <= 396U)
                mysmb_parser_boundary_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 373U));
            else if (t26_fixture >= 353U && t26_fixture <= 372U)
                mysmb_area_helper_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 353U));
            else if (t26_fixture >= 255U && t26_fixture <= 352U)
                mysmb_hole_underpart_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 255U));
            else if (t26_fixture >= 183U && t26_fixture <= 254U)
                mysmb_item_block_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 183U));
            else if (t26_fixture >= 175U && t26_fixture <= 182U)
                mysmb_jumpspring_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 175U));
            else if (t26_fixture >= 163U && t26_fixture <= 174U)
                mysmb_staircase_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 163U));
            else if (t26_fixture >= 133U && t26_fixture <= 162U)
                mysmb_cannon_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 133U));
            else if (t26_fixture >= 101U && t26_fixture <= 132U)
                mysmb_block_row_column_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 101U));
            else if (t26_fixture >= 89U && t26_fixture <= 94U)
                mysmb_castle_column_fixture(game.ram,
                    (mysmb_u8)(t26_fixture - 89U));
            else if (t26_fixture == 87U)
                mysmb_recorder_apply_t22_flagpole_fixture(&game);
            else if (t26_fixture == 88U) {
                mysmb_recorder_apply_t22_flagpole_fixture(&game);
                t22_flagpole_score_pending = 1U;
            }
            else if (t26_fixture >= 35U && t26_fixture <= 37U) {
                game.ram[0x0300U] = 0U;
                game.ram[0x06d6U] = (mysmb_u8)(t26_fixture - 31U);
                if (mysmb_area_queue_game_text(&game,
                                               (mysmb_u8)(t26_fixture - 31U)) == 0U) {
                    fclose(output);
                    return 65;
                }
                mysmb_frame_snapshot_capture(&game, &snapshot);
                if (mysmb_recorder_write_frame(output, &snapshot) == 0U) {
                    fclose(output);
                    return 65;
                }
                fclose(output);
                return 0;
            }
            else if (t26_fixture >= 38U && t26_fixture <= 39U) {
                static const mysmb_u8 metatiles[13] = {
                    0x00U, 0x41U, 0x82U, 0xc3U, 0x04U, 0x45U, 0x86U,
                    0xc7U, 0x08U, 0x49U, 0x8aU, 0xcbU, 0x0cU
                };
                mysmb_u8 row;
                game.ram[0x0340U] = 0U;
                game.ram[0x071fU] = t26_fixture == 38U ? 0U : 1U;
                game.ram[0x0726U] = t26_fixture == 38U ? 0U : 1U;
                game.ram[0x0720U] = 0x20U;
                game.ram[0x0721U] = 0x9fU;
                for (row = 0U; row < 13U; ++row)
                    game.ram[(mysmb_u16)(0x06a1U + row)] = metatiles[row];
                if (mysmb_area_render_graphics(&game) == 0U ||
                    mysmb_area_render_attribute_tables(&game) == 0U) {
                    fclose(output);
                    return 65;
                }
                mysmb_frame_snapshot_capture(&game, &snapshot);
                if (mysmb_recorder_write_frame(output, &snapshot) == 0U) {
                    fclose(output);
                    return 65;
                }
                fclose(output);
                return 0;
            }
            else if (t26_fixture >= 40U && t26_fixture <= 41U) {
                static const mysmb_u8 left[7] = { 0x10U, 0x32U, 0x10U, 0x32U, 0x10U, 0x32U, 0U };
                static const mysmb_u8 right[7] = { 0x40U, 0xc8U, 0x40U, 0xc8U, 0x40U, 0xc8U, 0U };
                mysmb_u8 row;
                game.ram[0x0340U] = 29U;
                game.ram[0x0720U] = 0x24U;
                game.ram[0x0721U] = 0x80U;
                for (row = 0U; row < 7U; ++row)
                    game.ram[(mysmb_u16)(0x03f9U + row)] =
                        (t26_fixture == 40U ? left : right)[row];
                if (mysmb_area_render_attribute_tables(&game) == 0U) {
                    fclose(output);
                    return 65;
                }
                mysmb_frame_snapshot_capture(&game, &snapshot);
                if (mysmb_recorder_write_frame(output, &snapshot) == 0U) {
                    fclose(output);
                    return 65;
                }
                fclose(output);
                return 0;
            }
            else if (t26_fixture >= 42U && t26_fixture <= 45U) {
                game.ram[0x0009U] = t26_fixture == 44U ? 1U : 0U;
                game.ram[0x0300U] = t26_fixture == 45U ? 0x31U :
                    (t26_fixture == 44U ? 7U : 0U);
                game.ram[0x074eU] = t26_fixture == 42U ? 1U : 3U;
                game.ram[0x06d4U] = t26_fixture == 42U ? 0U :
                    (t26_fixture == 43U ? 5U : 2U);
                mysmb_area_step_palette_rotation(&game);
                mysmb_frame_snapshot_capture(&game, &snapshot);
                if (mysmb_recorder_write_frame(output, &snapshot) == 0U) {
                    fclose(output);
                    return 65;
                }
                fclose(output);
                return 0;
            }
            else if (t26_fixture == 46U) {
                game.ram[0x074eU] = 0U;
                game.ram[0x0007U] = 5U;
                mysmb_area_remove_coin_axe(&game, 0xd2U, 0x20U);
                mysmb_frame_snapshot_capture(&game, &snapshot);
                if (mysmb_recorder_write_frame(output, &snapshot) == 0U) return 65;
                fclose(output);
                return 0;
            }
            else if (t26_fixture == 47U) {
                game.ram[0x0007U] = 5U;
                game.ram[0x03e4U] = 0x20U;
                game.ram[0x03e6U] = 0x04U;
                game.ram[0x03e8U] = 0x51U;
                game.ram[0x03ecU] = 1U;
                mysmb_area_apply_block_replacements(&game);
                mysmb_frame_snapshot_capture(&game, &snapshot);
                if (mysmb_recorder_write_frame(output, &snapshot) == 0U) return 65;
                fclose(output);
                return 0;
            }
            else if (t26_fixture == 48U) {
                game.ram[0x0000U] = 3U;
                game.ram[0x0004U] = 0x58U;
                game.ram[0x0005U] = 0x22U;
                mysmb_area_rem_bridge(&game, 12U, 1U, 0x58U, 0x22U);
                mysmb_frame_snapshot_capture(&game, &snapshot);
                if (mysmb_recorder_write_frame(output, &snapshot) == 0U) return 65;
                fclose(output);
                return 0;
            }
            else if (t26_fixture == 49U) {
                game.ram[0x0007U] = 5U;
                mysmb_area_destroy_block_metatile(&game, 0U, 0xd2U, 0x20U);
                mysmb_frame_snapshot_capture(&game, &snapshot);
                if (mysmb_recorder_write_frame(output, &snapshot) == 0U) return 65;
                fclose(output);
                return 0;
            }
        }
        if (t26_fixture >= 581U && t26_fixture <= 583U && index == warmup_frames + 1UL)
            mysmb_water_scene_continue(game.ram);
        if (t26_fixture >= 578U && t26_fixture <= 580U && index == warmup_frames + 1UL)
            mysmb_underground_scene_continue(game.ram);
        if ((t26_fixture >= 555U && t26_fixture <= 577U && index == warmup_frames + 1UL) ||
            (t26_fixture == 577U && index == warmup_frames + 129UL))
            mysmb_ground_scene_continue(game.ram);
        if (t26_fixture >= 548U && t26_fixture <= 554U && index == warmup_frames + 1UL)
            mysmb_castle_scene_continue(game.ram);
        if (t22_flagpole_score_pending != 0U &&
            index == warmup_frames + 1UL) {
            mysmb_recorder_apply_t22_flagpole_score_fixture(&game);
            t22_flagpole_score_pending = 0U;
        }
        if ((t26_fixture == 51U || t26_fixture == 52U) &&
            index == warmup_frames) {
            mysmb_u8 mode_before;
            mysmb_u8 task_before;

            /* This is the shared NMI prefix through UpdateScreen.  The
             * reference recorder stops at the source successor immediately
             * after that call, so do not run a mode/mainline step here. */
            (void)mysmb_frame_root_begin(&game, &input, &mode_before,
                                         &task_before);
            mysmb_frame_snapshot_capture(&game, &snapshot);
            if (mysmb_recorder_write_frame(output, &snapshot) == 0U) {
                fclose(output);
                return 65;
            }
            fclose(output);
            return 0;
        }
        mysmb_game_tick(&game, &input, &frame);
        if (index >= warmup_frames) {
            mysmb_frame_snapshot_capture(&game, &snapshot);
            if (mysmb_recorder_write_frame(output, &snapshot) == 0U) {
                fclose(output);
                return 65;
            }
        }
    }
    fclose(output);
    return 0;
}
