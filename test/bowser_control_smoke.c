#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/distance.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/loop.h"
#include "game/enemy/movement.h"
#include "game/objects.h"
#include <string.h>
static mysmb_u8 page, trace[8];
static unsigned int calls, bad;
static void call(mysmb_u8 id, mysmb_u8 slot)
{ if (slot != 3U) ++bad; trace[calls++] = id; }
void mysmb_enemy_move_d_bowser(struct mysmb_game *g, mysmb_u8 s)
{ (void)g; call(1U,s); }
void mysmb_enemy_kill_all(struct mysmb_game *g)
{ (void)g; call(2U,3U); }
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *g, mysmb_u8 s)
{ call(3U,s); g->ram[0U] = 0x71U; return page; }
void mysmb_enemy_move_slow_vertically(struct mysmb_game *g, mysmb_u8 s)
{ call(4U,s); g->ram[0xd2U] = 0x80U; }
mysmb_u8 mysmb_objects_spawn_hammer(struct mysmb_game *g)
{ call(5U,g->ram[8U]); g->ram[0x7aaU] = 2U; return 1U; }
void mysmb_enemy_init_vertical_state(struct mysmb_game *g, mysmb_u8 s)
{ call(6U,s); g->ram[0xa3U] = 0U; g->ram[0x437U] = 0U; }
mysmb_u8 mysmb_enemy_set_flame_timer(struct mysmb_game *g)
{ (void)g; call(7U,3U); return 0xbfU; }
void mysmb_objects_draw_bowsers_slot(struct mysmb_game *g, mysmb_u8 s)
{ (void)g; call(8U,s); }
int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    static const unsigned char order[][4] = {
        {1,0,0,0},{2,0,0,0},{7,8,0,0},{8,0,0,0},
        {6,8,0,0},{4,5,8,0},{4,8,0,0},{3,8,0,0},
        {3,8,0,0},{3,8,0,0},{8,0,0,0},{8,0,0,0}
    };
    unsigned int n, i, length;
    for (n = 0U; n < 12U; ++n) {
        memset(&g,0,sizeof(g)); calls = bad = 0U; page = 0U;
        g.ram[8U] = 3U; g.ram[0x49U] = 2U;
        g.ram[0x6cbU] = 0x55U; g.ram[0x364U] = 2U;
        g.ram[0x75fU] = 5U; g.ram[0x78dU] = 2U;
        if (n < 2U) { g.ram[0x21U] = 0x20U; g.ram[0xd2U] = (mysmb_u8)(n ? 0xe0U : 0xdfU); }
        if (n == 2U) { g.ram[0x747U] = 1U; g.ram[0x75fU] = 7U; g.ram[0x363U] = 0x80U; g.ram[0x6ccU] = 1U; }
        if (n == 3U) { g.ram[0x747U] = 1U; g.ram[0x363U] = 0x80U; }
        if (n == 4U) { g.ram[0x363U] = 0x80U; g.ram[0x78dU] = 1U; g.ram[0xd2U] = 0x80U; g.ram[0x437U] = 0x7fU; }
        if (n == 5U || n == 6U) { g.ram[0x363U] = 0x80U; g.ram[0x78dU] = 0U; g.ram[0x7aaU] = 3U; }
        if (n == 6U) { g.ram[0x75fU] = 4U; g.ram[0x790U] = 1U; }
        if (n >= 7U && n <= 9U) {
            g.ram[9U] = 4U; g.ram[0x6dcU] = 0x20U;
            if (n == 7U) g.ram[0x366U] = 0x90U;
            else g.ram[0x8aU] = 0x90U;
        }
        if (n == 9U) { page = 0xffU; g.ram[0x8aU] = 0xc8U; }
        if (n == 10U) { g.ram[0x747U] = 1U; g.ram[0x75fU] = 7U; }
        if (n == 11U) { g.ram[0x747U] = 1U; g.ram[0x75fU] = 6U; g.ram[0x363U] = 0x80U; }
        memcpy(expected,g.ram,sizeof(expected));
        if (n >= 2U) expected[0x6cbU] = 0U;
        if (n == 2U) { expected[0x363U] = 0U; expected[0x790U] = 0xafU; expected[0x6cbU] = 21U; }
        if (n == 4U) { expected[0xd2U] = 0x7fU; expected[0x437U] = 0U; expected[0xa3U] = 0xfeU; }
        if (n == 5U || n == 6U) { expected[0xd2U] = 0x80U; expected[0x78dU] = (mysmb_u8)(n == 5U ? 0x11U : 0x31U); }
        if (n == 5U) expected[0x7aaU] = 2U;
        if (n >= 7U && n <= 9U) { expected[0U] = 0x71U; expected[0x364U] = 1U; }
        if (n == 7U) expected[0x365U] = 0xffU;
        if (n == 8U) expected[0x365U] = 1U;
        if (n == 9U) { expected[0x49U] = 1U; expected[0x365U] = 2U; expected[0x78dU] = expected[0x790U] = 0x20U; }
        if (n == 10U) { expected[0x363U] = 0x80U; expected[0x790U] = 0x20U; }
        mysmb_enemy_run_bowser(&g,3U);
        length = 0U; while (length < 4U && order[n][length]) ++length;
        if (bad || calls != length || memcmp(g.ram,expected,sizeof(expected))) return (int)n + 1;
        for (i = 0U; i < calls; ++i) if (trace[i] != order[n][i]) return 20;
    }
    return 0;
}
