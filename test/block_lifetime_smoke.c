#include "game/objects.h"
#include "game/world/world.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures, calls;
static unsigned int seen[8];
static mysmb_u8 slots[8];
static unsigned int change_offset;
static void record(struct mysmb_game *g, unsigned int id, mysmb_u8 slot)
{
    if (calls >= 8U) { ++failures; return; }
    seen[calls] = id; slots[calls++] = slot;
    if (change_offset && calls == 1U) g->ram[8U] = 1U;
}
void mysmb_world_impose_gravity_block(struct mysmb_game *g, mysmb_u8 slot)
{ record(g, 1U, slot); }
mysmb_u8 mysmb_world_move_spr_object_horizontally(struct mysmb_game *g, mysmb_u8 slot)
{ record(g, 2U, slot); return 0U; }
void mysmb_oam_relative_block_position(struct mysmb_game *g, mysmb_u8 slot)
{ record(g, 3U, slot); }
void mysmb_oam_get_block_offscreen_bits(struct mysmb_game *g, mysmb_u8 slot)
{ record(g, 4U, slot); }
void mysmb_objects_draw_bouncing_block(struct mysmb_game *g, mysmb_u8 slot)
{ record(g, 5U, slot); }
void mysmb_objects_draw_brick_chunks(struct mysmb_game *g, mysmb_u8 slot)
{ record(g, 6U, slot); }

static int run_case(unsigned int state, unsigned int y, unsigned int high,
                    unsigned int second_y, unsigned int slot)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    static const unsigned int chunk_calls[7] = {1U,2U,1U,2U,3U,4U,6U};
    static const unsigned int bounce_calls[4] = {1U,3U,4U,5U};
    unsigned int i, count, final_slot, nibble, old_failures;
    mysmb_u8 call_slot;
    old_failures = failures;
    memset(&g, 0xa5, sizeof(g));
    g.ram[8U] = (mysmb_u8)slot;
    g.ram[0x26U + slot] = (mysmb_u8)state;
    final_slot = change_offset && state ? 1U : slot;
    g.ram[0xd7U + final_slot] = (mysmb_u8)y;
    g.ram[0xbeU + final_slot] = (mysmb_u8)high;
    g.ram[0xd9U + final_slot] = (mysmb_u8)second_y;
    memcpy(expected, g.ram, sizeof(expected));
    nibble = state & 15U;
    count = state == 0U ? 0U : (nibble == 1U ? 4U : 7U);
    if (change_offset && state) expected[8U] = 1U;
    expected[0x26U + final_slot] = (mysmb_u8)nibble;
    if (state && nibble == 1U && y % 16U <= 4U) {
        expected[0x3ecU + final_slot] = 1U;
        expected[0x26U + final_slot] = 0U;
    }
    if (state && nibble != 1U && high) {
        if (second_y > 240U) expected[0xd9U + final_slot] = 240U;
        if (y >= 240U) expected[0x26U + final_slot] = 0U;
    }
    calls = 0U;
    mysmb_objects_step_block(&g, (mysmb_u8)slot);
    if (memcmp(expected, g.ram, sizeof(expected)) != 0 || calls != count)
        ++failures;
    for (i = 0U; i < count; ++i) {
        if (seen[i] != (nibble == 1U ? bounce_calls[i] : chunk_calls[i]))
            ++failures;
        call_slot = (mysmb_u8)final_slot;
        if (i == 0U) call_slot = (mysmb_u8)slot;
        if (nibble != 1U && i < 4U) {
            if (i == 1U) call_slot = (mysmb_u8)(slot + 9U);
            if (i == 2U) call_slot = (mysmb_u8)(slot + 2U);
            if (i == 3U) call_slot = (mysmb_u8)(slot + 11U);
        }
        if (slots[i] != call_slot) ++failures;
    }
    return failures != old_failures;
}
int main(void)
{
    unsigned int state,y,slot,n,count;
    static const unsigned int second[3] = {239U,240U,241U};
    count = 0U;
    for (slot=0U; slot<2U; ++slot)
        for (state=0U; state<256U; ++state)
            for (y=0U; y<256U; ++y) {
                if (run_case(state,y,(y>>4U)&1U,second[y%3U],slot))
                    return 1;
                ++count;
            }
    for (n=0U; n<3U; ++n)
        for (y=239U; y<242U; ++y)
            for (slot=0U; slot<2U; ++slot) {
                if (run_case(2U,y,1U,second[n],slot)) return 1;
                ++count;
            }
    change_offset=1U;
    if (run_case(0x11U,4U,1U,241U,0U) ||
        run_case(0x12U,241U,1U,241U,0U)) return 1;
    printf("%u state/write cases, 2 live-slot reload cases, %u failures\n",
           count,failures);
    return failures ? 1 : 0;
}
