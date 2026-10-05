#include "game/objects.h"
#include "core/area.h"
#include "game/enemy/movement.h"
#include "game/enemy/loop.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/actor_slots.h"
#include <string.h>

static unsigned int calls, bad;
static mysmb_u8 ids[8], original_y, expected_low, expected_slot;
static void call(mysmb_u8 id) { ids[calls++] = id; }
void mysmb_enemy_kill_all(struct mysmb_game *g)
{
    call(1U);
    if (g->ram[0xfcU] != 0x80U || g->ram[0x772U] != 0U) ++bad;
    g->ram[0x600U] = 1U;
}
void mysmb_enemy_move_slow_vertically(struct mysmb_game *g, mysmb_u8 slot)
{
    call(2U); if (slot != expected_slot || g->ram[8U] != slot) ++bad;
    g->ram[0x600U] = 2U;
}
void mysmb_objects_draw_bowsers_slot(struct mysmb_game *g, mysmb_u8 slot)
{
    call(3U); if (slot != expected_slot) ++bad;
    g->ram[0x601U] = 3U;
}
void mysmb_area_rem_bridge(struct mysmb_game *g, mysmb_u8 graphics,
    mysmb_u8 y, mysmb_u8 low, mysmb_u8 high)
{
    call(4U);
    if (graphics != 12U || y != original_y || low != expected_low ||
        high != 0x22U || g->ram[4U] != low || g->ram[5U] != high ||
        g->ram[0x364U] != 4U || g->ram[0x363U] != 0x54U) ++bad;
    /* A child may change RAM offset; MoveVOffset still consumes saved Y.
     * ObjectOffset, unlike Y, is explicitly reloaded by the source caller. */
    g->ram[0x300U] = 0x71U; g->ram[8U] = expected_slot;
}
void mysmb_area_move_v_offset(struct mysmb_game *g, mysmb_u8 y)
{
    call(5U); if (y != original_y || g->ram[0x300U] != 0x71U) ++bad;
    g->ram[0x300U] = (mysmb_u8)(y + 9U);
}
void mysmb_enemy_init_vertical_state(struct mysmb_game *g, mysmb_u8 slot)
{
    call(6U);
    if (slot != expected_slot || g->ram[0x369U] != 15U ||
        g->ram[0xfeU] != 8U || g->ram[0xfdU] != 1U) ++bad;
    g->ram[0xa0U + slot] = 0U; g->ram[0x434U + slot] = 0U;
}
int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    static const unsigned char lows[15] = {
        0x1a,0x58,0x98,0x96,0x94,0x92,0x90,0x8e,
        0x8c,0x8a,0x88,0x86,0x84,0x82,0x80
    };
    unsigned int n, timer, offset;
    for (n = 0U; n < 15U; ++n) {
        for (offset = 0U; offset < 256U; offset += 85U) {
            memset(&g, 0, sizeof(g)); memset(g.ram, 0x55, sizeof(g.ram));
            calls = bad = 0U; expected_low = lows[n]; expected_slot = 4U;
            original_y = (mysmb_u8)(offset + 1U);
            g.ram[0x368U] = 0U; g.ram[0x16U] = 45U;
            g.ram[0x1eU] = 0U; g.ram[0x364U] = 1U;
            g.ram[0x369U] = (mysmb_u8)n; g.ram[0x300U] = (mysmb_u8)offset;
            memcpy(expected, g.ram, sizeof(expected));
            expected[8U] = 4U; expected[4U] = lows[n]; expected[5U] = 0x22U;
            expected[0x364U] = 4U; expected[0x363U] = 0x54U;
            expected[0x300U] = (mysmb_u8)(offset + 10U);
            expected[0xfeU] = n == 14U ? 0x80U : 8U;
            expected[0xfdU] = 1U; expected[0x369U] = (mysmb_u8)(n + 1U);
            expected[0x601U] = 3U;
            if (n == 14U) {
                expected[0xa4U] = expected[0x438U] = 0U;
                expected[0x22U] = 0x40U;
            }
            if (mysmb_objects_step_bridge_collapse(&g) != 0U || bad ||
                calls != (n == 14U ? 4U : 3U) || ids[0] != 4U ||
                ids[1] != 5U || ids[calls-1U] != 3U ||
                (n == 14U && ids[2] != 6U) ||
                memcmp(g.ram, expected, sizeof(expected))) return 1;
        }
    }
    for (timer = 0U; timer < 256U; ++timer) {
        if (timer == 1U) continue;
        memset(&g, 0, sizeof(g)); calls = bad = 0U; expected_slot = 5U;
        g.ram[0x368U] = 5U; g.ram[0x1bU] = 45U;
        g.ram[0x364U] = (mysmb_u8)timer;
        memcpy(expected, g.ram, sizeof(expected));
        expected[8U] = 5U; expected[0x364U] = (mysmb_u8)(timer-1U);
        expected[0x601U] = 3U;
        if (mysmb_objects_step_bridge_collapse(&g) != 0U || bad ||
            calls != 1U || ids[0] != 3U ||
            memcmp(g.ram, expected, sizeof(expected))) return 2;
    }
    for (n = 0U; n < 4U; ++n) {
        memset(&g, 0, sizeof(g)); calls = bad = 0U; expected_slot = 4U;
        g.ram[0x368U] = 4U; g.ram[8U] = 2U;
        g.ram[0x1aU] = (mysmb_u8)(n == 0U ? 0U : 45U);
        g.ram[0x22U] = (mysmb_u8)(n == 1U ? 0x20U : 0x40U);
        g.ram[0xd3U] = (mysmb_u8)(n == 2U ? 0xdfU : 0xe0U);
        g.ram[0x772U] = 0xffU;
        memcpy(expected, g.ram, sizeof(expected));
        if (n != 0U) expected[8U] = 4U;
        if (n == 2U) { expected[0x600U] = 2U; expected[0x601U] = 3U; }
        else { expected[0xfcU] = 0x80U; expected[0x772U] = 0U; expected[0x600U] = 1U; }
        if (mysmb_objects_step_bridge_collapse(&g) != (n == 2U ? 0U : 1U) ||
            bad || calls != (n == 2U ? 2U : 1U) ||
            ids[0] != (n == 2U ? 2U : 1U) ||
            memcmp(g.ram, expected, sizeof(expected))) return 3;
    }
    return 0;
}
