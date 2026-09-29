#include "game/objects.h"
#include "game/area.h"
#include "game/world/world.h"
#include "game/enemy/distance.h"
#include "game/enemy/init_targets.h"

/* ROM $D84D-$DA24. One player/enemy response chain for every actor.
 * Original children remain separately owned; no host state is consulted. */
const mysmb_u8 mysmb_residual_x_speeds[2] = {0x18U, 0xe8U};
static const mysmb_u8 kicked_speeds[2] = {0x30U, 0xd0U};
static const mysmb_u8 demoted_speeds[2] = {8U, 0xf8U};
static const mysmb_u8 kicked_points[3] = {10U, 6U, 4U};
static const mysmb_u8 stomped_points[4] = {2U, 6U, 5U, 6U};
static const mysmb_u8 revival_rates[2] = {0x10U, 0x0bU};

/* Preserve the original unmasked byte index with a bound local PRG. The
 * resource-free fallback is limited to the declared table's legal domain. */
static mysmb_u8 contact_data(const struct mysmb_game *g, mysmb_u16 address,
    mysmb_u8 index, const mysmb_u8 *fallback, mysmb_u8 length)
{
    mysmb_u16 offset;
    offset = (mysmb_u16)(address - 0x8000U + index);
    if (g->area_prg != 0 && offset < g->area_prg_size)
        return g->area_prg[offset];
    return index < length ? fallback[index] : 0U;
}

/* $DA11 SetupFloateyNumber / ExSFN: caller-prepared relative X. */
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *g,
    mysmb_u8 slot, mysmb_u8 control)
{
    g->ram[0x0110U + slot] = control;
    g->ram[0x012cU + slot] = 0x30U;
    g->ram[0x011eU + slot] = g->ram[0x00cfU + slot];
    g->ram[0x0117U + slot] = g->ram[0x03aeU];
}

/* $D948 SetPRout. Source returns X=ObjectOffset, dead at these C tails. */
void mysmb_objects_set_player_routine(struct mysmb_game *g,
    mysmb_u8 routine, mysmb_u8 state)
{
    g->ram[0x000eU] = routine;
    g->ram[0x001dU] = state;
    g->ram[0x0747U] = 0xffU;
    g->ram[0x0775U] = 0U;
}

/* $D931 ForceInjury consumes A; unlike InjurePlayer it has no timer gate. */
void mysmb_objects_force_injury_entry(struct mysmb_game *g, mysmb_u8 a)
{
    if (g->ram[0x0756U] == 0U) {
        /* $D958 KillPlayer is reached with X=0. */
        g->ram[0x0057U] = 0U;
        g->ram[0x00fcU] = 1U;
        g->ram[0x009fU] = 0xfcU;
        mysmb_objects_set_player_routine(g, 11U, 1U);
    }
    else {
        g->ram[0x0756U] = a;
        g->ram[0x079eU] = 8U;
        g->ram[0x00ffU] = 0x10U;
        (void)mysmb_area_queue_player_palette(g);
        mysmb_objects_set_player_routine(g, 10U, 1U);
    }
}

/* Historical API name; this is the guarded $D92C InjurePlayer entry. */
void mysmb_objects_force_injury(struct mysmb_game *g)
{
    if (g->ram[0x079eU] == 0U) mysmb_objects_force_injury_entry(g, 0U);
}

/* $DA05 EnemyFacePlayer: PlayerEnemyDiff returns the high-byte sign. */
mysmb_u8 mysmb_objects_enemy_face_player(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_u8 direction;
    direction = (mysmb_enemy_player_difference(g, slot) & 0x80U) != 0U ? 2U : 1U;
    g->ram[0x0046U + slot] = direction;
    return (mysmb_u8)(direction - 1U);
}

/* $D969 EnemyStomped, including both demotion and shell tails. */
void mysmb_objects_enemy_stomped(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_u8 id, index, direction;
    id = g->ram[0x0016U + slot];
    if (id == 18U) {
        mysmb_objects_force_injury(g);
        return;
    }
    g->ram[0x00ffU] = 4U;
    id = g->ram[0x0016U + slot];
    index = 0U;
    if (id == 20U || id == 8U || id == 0x33U || id == 12U)
        index = 0U;
    else if (id == 5U) index = 1U;
    else if (id == 17U) index = 2U;
    else if (id == 7U) index = 3U;
    else {
        if (id >= 9U) {
            g->ram[0x0016U + slot] = (mysmb_u8)(id & 1U);
            g->ram[0x001eU + slot] = 0U;
            mysmb_objects_setup_floatey_from_relative(g, slot, 3U);
            mysmb_enemy_init_vertical_state(g, slot);
            index = mysmb_objects_enemy_face_player(g, slot);
            g->ram[0x0058U + slot] = contact_data(g, 0xd851U, index,
                demoted_speeds, 2U);
        }
        else {
            g->ram[0x001eU + slot] = 4U;
            ++g->ram[0x0484U];
            mysmb_objects_setup_floatey_from_relative(g, slot,
                (mysmb_u8)(g->ram[0x0484U] + g->ram[0x0791U]));
            ++g->ram[0x0791U];
            g->ram[0x0796U + slot] = contact_data(g, 0xd9d2U,
                g->ram[0x076aU], revival_rates, 2U);
        }
        g->ram[0x009fU] = 0xfcU;
        return;
    }
    mysmb_objects_setup_floatey_from_relative(g, slot,
        contact_data(g, 0xd965U, index, stomped_points, 4U));
    direction = g->ram[0x0046U + slot];
    mysmb_world_set_stun(g, slot);
    g->ram[0x0046U + slot] = direction;
    g->ram[0x001eU + slot] = 0x20U;
    mysmb_enemy_init_vertical_state(g, slot);
    g->ram[0x0058U + slot] = 0U;
    g->ram[0x009fU] = 0xfdU;
}

/* $D8F9 ChkForPlayerInjury, including facing/turnaround injury tails. */
static void check_player_injury(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_u8 speed;
    speed = g->ram[0x009fU];
    if ((speed != 0U && speed < 0x80U) ||
        (g->ram[0x0016U + slot] >= 7U &&
         (mysmb_u8)(g->ram[0x00ceU] + 12U) < g->ram[0x00cfU + slot]) ||
        g->ram[0x0791U] != 0U) {
        mysmb_objects_enemy_stomped(g, slot);
        return;
    }
    if (g->ram[0x079eU] != 0U) return;
    if ((g->ram[0x03adU] < g->ram[0x03aeU] && g->ram[0x0046U + slot] == 1U) ||
        (g->ram[0x03adU] >= g->ram[0x03aeU] && g->ram[0x0046U + slot] != 1U))
        mysmb_objects_turn_enemy(g, slot);
    mysmb_objects_force_injury(g);
}

/* $D895 HandlePECollisions consumes Y=ID supplied by CheckForPUpCollision. */
void mysmb_objects_handle_player_enemy_contact(struct mysmb_game *g,
    mysmb_u8 slot, mysmb_u8 id)
{
    mysmb_u8 index, points, state;
    if (((g->ram[0x0491U + slot] & 1U) | g->ram[0x03d8U + slot]) != 0U)
        return;
    g->ram[0x0491U + slot] |= 1U;
    if (id == 18U || id == 0x33U) {
        check_player_injury(g, slot);
        return;
    }
    if (id == 13U || id == 12U || id >= 0x15U || g->ram[0x074eU] == 0U) {
        mysmb_objects_force_injury(g);
        return;
    }
    state = g->ram[0x001eU + slot];
    if ((state & 0x80U) != 0U || (state & 7U) < 2U) {
        check_player_injury(g, slot);
        return;
    }
    if (g->ram[0x0016U + slot] == 6U) return;
    g->ram[0x00ffU] = 8U;
    g->ram[0x001eU + slot] |= 0x80U;
    index = mysmb_objects_enemy_face_player(g, slot);
    g->ram[0x0058U + slot] = contact_data(g, 0xd84fU, index, kicked_speeds, 2U);
    points = (mysmb_u8)(3U + g->ram[0x0484U]);
    index = g->ram[0x0796U + slot];
    if (index < 3U) points = contact_data(g, 0xd892U, index, kicked_points, 3U);
    mysmb_objects_setup_floatey_from_relative(g, slot, points);
}

/* $D853 PlayerEnemyCollision consumes the caller's prepared boxes. The
 * legacy preserve argument remains ABI-only; the ROM never rebuilds boxes. */
void mysmb_objects_player_enemy_current(struct mysmb_game *g, mysmb_u8 slot,
    mysmb_u8 preserve_collision_boxes)
{
    mysmb_u8 box, hit, id;
    (void)preserve_collision_boxes;
    if ((g->ram[9U] & 1U) != 0U) return;
    if (mysmb_world_player_vertical_carry(g) != 0U) return;
    if (g->ram[0x03d8U + slot] != 0U || g->ram[0x000eU] != 8U ||
        (g->ram[0x001eU + slot] & 0x20U) != 0U) return;
    box = mysmb_world_enemy_box_offset(g);
    hit = mysmb_world_boxes_collide(g, 0x04acU, (mysmb_u16)(0x04acU + box));
    slot = g->ram[8U];
    if (hit == 0U) {
        g->ram[0x0491U + slot] &= 0xfeU;
        return;
    }
    id = g->ram[0x0016U + slot];
    if (id == 0x2eU) mysmb_objects_collect_power_up(g, slot);
    else if (g->ram[0x079fU] != 0U) mysmb_world_shell_or_block_defeat(g, slot);
    else mysmb_objects_handle_player_enemy_contact(g, slot, id);
}
