#include "game/oam/oam.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include <string.h>

static unsigned int calls, bad, mode;
static mysmb_u8 front_slot, rear_slot, initial_flag;
static mysmb_u8 trace[8], slots[8];
static void mark(mysmb_u8 id, mysmb_u8 slot)
{
    if (calls >= 8U) { ++bad; return; }
    trace[calls] = id; slots[calls++] = slot;
}
void mysmb_objects_draw_retainer(struct mysmb_game *g, mysmb_u8 s)
{
    mark(1U,s);
    if (calls == 1U) {
        if (s != front_slot || g->ram[0x36aU] != (mysmb_u8)(initial_flag+1U)) ++bad;
        /* The parent must use fresh state/direction/coordinates after drawing. */
        g->ram[0x1eU+s] = (mysmb_u8)(mode & 1U ? 0x20U : 0U);
        g->ram[0x46U+s] = (mysmb_u8)(mode & 2U ? 1U : 2U);
        g->ram[0x87U+s] = (mysmb_u8)(mode & 2U ? 3U : 0xfcU);
        g->ram[0xcfU+s] = 0xfcU;
    }
    else {
        if (s != rear_slot || g->ram[8U] != rear_slot ||
            g->ram[0x36aU] != (mysmb_u8)(initial_flag+2U) ||
            g->ram[0x87U+s] != (mysmb_u8)(mode & 2U ? 0xf3U : 0x0cU) ||
            g->ram[0xcfU+s] != 4U || g->ram[0x16U+s] != 45U ||
            g->ram[0x1eU+s] != (mysmb_u8)(mode & 1U ? 0x20U : 0U)) ++bad;
        /* Rear post-draw state can differ from the copied front state. */
        g->ram[0x1eU+s] = (mysmb_u8)(mode & 4U ? 0x40U : 0U);
    }
}
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *g, mysmb_u8 s)
{
    mark(2U,s);
    if (g->ram[0x49aU+s] != 10U || g->ram[0x1eU+s] != 0U) ++bad;
    g->ram[0U] = (mysmb_u8)(0x80U+s);
}
void mysmb_objects_player_enemy_current(struct mysmb_game *g, mysmb_u8 s,
                                        mysmb_u8 preserve)
{
    mark(3U,s);
    if (preserve != 1U || g->ram[0U] != (mysmb_u8)(0x80U+s)) ++bad;
    g->ram[1U] = (mysmb_u8)(0x90U+s);
}
int main(void)
{
    static struct mysmb_game g;
    static mysmb_u8 expected[2048];
    static const mysmb_u8 flags[3] = {0U,254U,255U};
    unsigned int f, i, count;
    for (f=0U; f<3U; ++f) for (mode=0U; mode<8U; ++mode) {
        memset(&g,0,sizeof(g));calls=bad=0U;
        front_slot=(mysmb_u8)(mode & 2U ? 5U : 0U);rear_slot=3U;
        initial_flag=flags[f];g.ram[8U]=front_slot;g.ram[0x36aU]=initial_flag;
        g.ram[0x6cfU]=rear_slot;g.ram[0x6eU+rear_slot]=0x77U;
        /* Source entry must not require a live flag or Bowser ID. */
        g.ram[0x1eU+front_slot]=(mysmb_u8)(mode & 1U ? 0U : 0x20U);
        memcpy(expected,g.ram,sizeof(expected));
        expected[0x36aU]=0U;
        expected[0x1eU+front_slot]=(mysmb_u8)(mode & 1U ? 0x20U : 0U);
        expected[0x46U+front_slot]=expected[0x46U+rear_slot]=(mysmb_u8)(mode & 2U ? 1U : 2U);
        expected[0x87U+front_slot]=(mysmb_u8)(mode & 2U ? 3U : 0xfcU);
        expected[0xcfU+front_slot]=0xfcU;
        expected[0x87U+rear_slot]=(mysmb_u8)(mode & 2U ? 0xf3U : 0x0cU);
        expected[0xcfU+rear_slot]=4U;expected[0x16U+rear_slot]=45U;
        expected[0x1eU+rear_slot]=(mysmb_u8)(mode & 4U ? 0x40U : 0U);
        if (!(mode & 1U)) {
            expected[0x49aU+front_slot]=10U;
            expected[0U]=(mysmb_u8)(0x80U+front_slot);expected[1U]=(mysmb_u8)(0x90U+front_slot);
        }
        if (!(mode & 4U)) {
            expected[0x49aU+rear_slot]=10U;
            expected[0U]=(mysmb_u8)(0x80U+rear_slot);expected[1U]=(mysmb_u8)(0x90U+rear_slot);
        }
        mysmb_objects_draw_bowsers_slot(&g,front_slot);
        count=0U;
        for (i=0U; i<2U; ++i) {
            mysmb_u8 s;
            s=i==0U?front_slot:rear_slot;
            if (trace[count]!=1U || slots[count++]!=s) ++bad;
            if ((i==0U && !(mode & 1U)) || (i!=0U && !(mode & 4U))) {
                if (trace[count]!=2U || slots[count++]!=s) ++bad;
                if (trace[count]!=3U || slots[count++]!=s) ++bad;
            }
        }
        if (bad || calls!=count || memcmp(g.ram,expected,sizeof(expected))) return (int)(f*8U+mode+1U);
    }
    return 0;
}
