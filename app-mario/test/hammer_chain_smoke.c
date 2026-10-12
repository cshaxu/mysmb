#include "core/objects.h"
#include "core/oam/oam.h"
#include "core/world/world.h"
#include <stdio.h>
#include <string.h>

static unsigned int errors, count, calls[8], args[8], mutate;
static void record(unsigned int id, unsigned int slot)
{
    if (count >= 8U) { ++errors; return; }
    calls[count] = id; args[count++] = slot;
}
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *g,
    mysmb_u8 slot, mysmb_u8 force, mysmb_u8 max_speed)
{
    record(1U, slot);
    if (force != 0x10U || max_speed != 4U || g->ram[0] != 0x10U ||
        g->ram[1] != 0x0fU || g->ram[2] != 4U) ++errors;
}
mysmb_u8 mysmb_world_move_spr_object_horizontally(struct mysmb_game *g,mysmb_u8 slot)
{
    record(2U, slot);
    if (mutate != 0U) g->ram[8] = 7U;
return 0U; }
void mysmb_objects_check_hammer_collision(struct mysmb_game *g,mysmb_u8 slot)
{ (void)g; record(3U, slot); }
void mysmb_oam_get_misc_offscreen_bits(struct mysmb_game *g,mysmb_u8 slot)
{ (void)g; record(4U, slot); }
void mysmb_oam_relative_misc_position(struct mysmb_game *g,mysmb_u8 slot)
{ (void)g; record(5U, slot); }
void mysmb_objects_get_hammer_bounding_box(struct mysmb_game *g,mysmb_u8 slot)
{ (void)g; record(6U, slot); }
void mysmb_objects_draw_hammer(struct mysmb_game *g,mysmb_u8 slot)
{ (void)g; record(7U, slot); }

int main(void)
{
    static struct mysmb_game g;
    static mysmb_u8 before[2048];
    unsigned int random, blocked, i, slot, state, freeze, facing, x;
    unsigned int expected_slot, first, cases;
    mysmb_u8 result;

    cases = 0U;
    /* Exhaust every random byte and each independent allocation rejection.
     * All persistent bytes except the three spawn writes must be preserved. */
    for (random = 0U; random < 256U; ++random) {
        slot = random % 8U;
        if (slot == 0U) slot = random & 8U;
        for (blocked = 0U; blocked < 3U; ++blocked) {
            memset(&g,0,sizeof(g)); g.ram[8] = 3U;
            g.ram[0x7a8U] = (mysmb_u8)random;
            g.ram[0x7abU] = (mysmb_u8)(random ^ 7U);
            g.ram[0x6beU + slot] = 0x5aU;
            if (blocked == 1U) g.ram[0x2aU + slot] = 1U;
            if (blocked == 2U) g.ram[0xfU + 4U + slot / 3U] = 1U;
            memcpy(before,g.ram,2048U);
            result = mysmb_objects_spawn_hammer(&g);
            if (result != (blocked == 0U ? 1U : 0U)) ++errors;
            if (blocked == 0U) {
                before[0x6aeU + slot] = 3U;
                before[0x2aU + slot] = 0x90U;
                before[0x4a2U + slot] = 7U;
            }
            if (memcmp(before,g.ram,2048U) != 0) ++errors;
            ++cases;
        }
    }
    for (slot = 0U; slot < 9U; ++slot)
    for (state = 0U; state < 256U; ++state)
    for (freeze = 0U; freeze < 2U; ++freeze)
    for (facing = 1U; facing <= 2U; ++facing) {
        memset(&g,0,sizeof(g)); count = 0U;
        g.ram[8] = (mysmb_u8)slot;
        g.ram[0x2aU + slot] = (mysmb_u8)state;
        g.ram[0x6aeU + slot] = 4U;
        /* Inactive parent is intentionally legal at this entry. */
        g.ram[0x22U] = 0xffU; g.ram[0x4aU] = (mysmb_u8)facing;
        x = (state & 1U) != 0U ? 0xffU : 0xfeU;
        g.ram[0x8bU] = (mysmb_u8)x; g.ram[0x72U] = 0xffU;
        g.ram[0xd3U] = 3U; g.ram[0x747U] = (mysmb_u8)freeze;
        mutate = ((state & 0x7fU) == 1U) ? 1U : 0U;
        mysmb_objects_step_hammer(&g,(mysmb_u8)slot);
        first = freeze == 0U && (state & 0x7fU) < 2U ? 1U : 4U;
        if (count != 8U - first) ++errors;
        expected_slot = first == 1U && mutate != 0U ? 7U : slot;
        for (i = 0U; i < count; ++i) {
            if (calls[i] != first + i) ++errors;
            if (args[i] != (calls[i] < 3U ? slot + 13U : expected_slot)) ++errors;
        }
        if (freeze == 0U && (state & 0x7fU) >= 2U) {
            if (g.ram[0x2aU + slot] != (mysmb_u8)(state - 1U) ||
                g.ram[0x93U + slot] != (mysmb_u8)(x + 2U) ||
                g.ram[0x7aU + slot] != 0U ||
                g.ram[0xdbU + slot] != 0xf9U ||
                g.ram[0xc2U + slot] != 1U) ++errors;
            if ((state & 0x7fU) == 2U &&
                (g.ram[0xacU + slot] != 0xfeU || g.ram[0x22U] != 0xf7U ||
                 g.ram[0x64U + slot] != (facing == 1U ? 0x10U : 0xf0U))) ++errors;
        }
        else if (g.ram[0x2aU + slot] != state) ++errors;
        ++cases;
    }
    printf("hammer chain: %u cases, %u errors\n",cases,errors);
    return errors != 0U;
}
