#include "core/enemy/actor_slots.h"
#include "core/enemy/init_targets.h"
#include "core/enemy/movement.h"
#include <string.h>

static unsigned char expected[2048];
static unsigned int calls, bad;
static mysmb_u8 expected_slot, random_after, expired;
void mysmb_enemy_init_podoboo(struct mysmb_game *g, mysmb_u8 s)
{
    if (s != expected_slot || calls++ != 0U || !expired) ++bad;
    /* Verify the caller reads PRNG after the child's return and keeps
     * unrelated child effects, even when it changes eligibility flags. */
    g->ram[0x7a8U+s] = random_after;
    g->ram[0xfU+s] = 0U;
    g->ram[0x747U] = 0xffU;
    g->ram[0x796U+s] = 0xa5U;
    expected[0x7a8U+s] = random_after;
    expected[0xfU+s] = 0U;
    expected[0x747U] = 0xffU;
    expected[0x434U+s] = (mysmb_u8)(random_after | 0x80U);
    expected[0x796U+s] = (mysmb_u8)((random_after & 15U) | 6U);
    expected[0xa0U+s] = 0xf9U;
}
void mysmb_enemy_move_j_vertically(struct mysmb_game *g, mysmb_u8 s)
{
    if (s != expected_slot || calls++ != (unsigned int)expired ||
        memcmp(g->ram, expected, 2048U) != 0) ++bad;
    g->ram[0xcfU+s] ^= 0x5aU;
    expected[0xcfU+s] ^= 0x5aU;
}
int main(void)
{
    static struct mysmb_game g;
    unsigned int slot, value, timer;
    for (slot=0U; slot<6U; ++slot)
        for (value=0U; value<256U; ++value)
            for (timer=0U; timer<4U; ++timer) {
                memset(g.ram, (int)value, 2048U);
                g.ram[0x796U+slot] = (mysmb_u8)(timer == 3U ? 255U : timer);
                g.ram[0x7a8U+slot] = (mysmb_u8)(value ^ 0xffU);
                memcpy(expected, g.ram, 2048U);
                expected_slot=(mysmb_u8)slot; random_after=(mysmb_u8)value;
                expired=(mysmb_u8)(timer==0U); calls=bad=0U;
                mysmb_objects_step_podoboos_slot(&g, expected_slot);
                if (bad || calls != (unsigned int)expired+1U ||
                    memcmp(g.ram, expected, 2048U) != 0) return 1;
            }
    return 0;
}
