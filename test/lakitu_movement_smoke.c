#include "core/enemy/frenzy.h"
#include "core/enemy/actor_slots.h"
#include "core/enemy/distance.h"
#include "core/enemy/movement.h"
#include "core/world/world.h"
#include <string.h>

static mysmb_u8 low_byte, page_byte;
static unsigned int calls, bad;
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *g, mysmb_u8 slot)
{
    if (slot != 5U || calls != 0U) ++bad;
    ++calls; g->ram[0U] = low_byte; return page_byte;
}
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g, mysmb_u8 slot)
{
    if (slot != 5U || calls > 1U) ++bad;
    calls = 2U; g->ram[0x100U] = 0x91U; return 0U;
}
void mysmb_enemy_move_d_vertically(struct mysmb_game *g, mysmb_u8 slot)
{
    if (slot != 5U || calls != 0U) ++bad;
    calls = 3U; g->ram[0x100U] = 0x82U;
}
int main(void)
{
    /* page, low, ID, direction, speed, player speed, scroll, adjusters,
     * expected A, scratch zero, direction and speed. */
    static const unsigned char cases[][14] = {
        {0,0,17,1,9,0,0,21,48,64,20,0,1,9},
        {255,192,17,1,9,0,0,21,48,64,5,15,1,9},
        {0,60,17,0,9,25,2,21,48,64,5,15,0,9},
        {0,64,17,1,3,25,2,21,48,64,2,60,1,2},
        {0,64,17,1,1,25,2,21,48,64,5,15,0,0},
        {255,192,17,0,9,25,2,21,48,64,48,15,1,9},
        {0,4,18,0,9,25,2,21,48,0,254,1,0,9},
        {0,4,17,0,9,25,2,0,48,64,254,1,0,9},
        {0,4,18,0,9,0,2,42,48,64,40,1,0,9},
        {0,4,17,1,9,24,2,21,48,64,46,1,1,9},
        {0,4,17,1,9,25,1,21,48,64,46,1,1,9},
        {0,4,17,1,9,255,2,21,48,64,62,1,1,9},
        {128,0,17,2,0,25,2,21,48,64,63,0,2,0},
        {0,64,17,1,0,25,2,21,48,64,255,60,1,255}
    };
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int n;
    const unsigned char *c;
    for (n = 0U; n < sizeof(cases) / sizeof(cases[0]); ++n) {
        memset(&g, 0, sizeof(g)); memset(g.ram, 0x55, sizeof(g.ram));
        c = cases[n]; page_byte = c[0]; low_byte = c[1];
        g.ram[0x1bU] = c[2]; g.ram[0xa5U] = c[3]; g.ram[0x5dU] = c[4];
        g.ram[0x57U] = c[5]; g.ram[0x775U] = c[6];
        g.ram[1U] = c[7]; g.ram[2U] = c[8]; g.ram[3U] = c[9];
        memcpy(expected, g.ram, sizeof(expected));
        expected[0U] = c[11]; expected[0xa5U] = c[12]; expected[0x5dU] = c[13];
        calls = bad = 0U;
        if (mysmb_enemy_player_lakitu_difference(&g, 5U) != c[10] ||
            bad || calls != 1U || memcmp(g.ram, expected, sizeof(expected))) return 1;
    }
    for (n = 0U; n < 3U; ++n) {
        memset(&g, 0, sizeof(g)); memset(g.ram, 0x55, sizeof(g.ram));
        g.ram[0x23U] = (mysmb_u8)(n == 0U ? 0x20U : (n == 1U ? 1U : 0U));
        g.ram[0x1bU] = 17U; g.ram[0xa5U] = 1U; g.ram[0x5dU] = 3U;
        memcpy(expected, g.ram, sizeof(expected)); calls = bad = 0U;
        page_byte = 0U; low_byte = 64U;
        if (n == 0U) expected[0x100U] = 0x82U;
        else {
            expected[0x100U] = 0x91U;
            expected[0x6cbU] = n == 1U ? 0U : 18U;
            expected[0xa5U] = n == 1U ? 0U : 1U;
            expected[0x5dU] = n == 1U ? 0xf0U : 2U;
            expected[0x4bU] = n == 1U ? 2U : 1U;
            if (n == 2U) { expected[0U] = 60U; expected[1U] = 21U; expected[2U] = 48U; expected[3U] = 64U; }
        }
        mysmb_enemy_step_lakitus_slot(&g, 5U);
        if (bad || calls != (n == 0U ? 3U : 2U) ||
            memcmp(g.ram, expected, sizeof(expected))) return 2;
    }
    return 0;
}
