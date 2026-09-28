#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include "game/world/world.h"
#include <string.h>

static unsigned char data[0x5000];
static unsigned int stage, bad;
static mysmb_u8 force_value, y_value;
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g, mysmb_u8 s)
{
    if (stage != 0U || s != 5U) ++bad;
    stage = 1U; g->ram[0x88U] = 0x72U; return 0x91U;
}
void mysmb_enemy_move_downward(struct mysmb_game *g, mysmb_u8 s,
                              mysmb_u8 amount, mysmb_u8 maximum)
{
    if (stage != 1U || s != 5U || amount != 13U || maximum != 5U) ++bad;
    stage = 2U; g->ram[0x434U + s] = force_value;
    g->ram[0xcfU + s] = y_value; g->ram[0x88U] = 0x83U;
}
void mysmb_enemy_move_j_vertically(struct mysmb_game *g, mysmb_u8 s)
{
    if (stage != 0U || s != 5U || g->ram[0x3c5U + s] != 0U) ++bad;
    stage = 3U; g->ram[0x88U] = 0xa4U;
}
int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int f, delta, i;
    mysmb_u8 difference, result;
    for (i = 0U; i < sizeof(data); ++i) data[i] = (unsigned char)(i * 37U + 19U);
    for (f = 0U; f < 256U; ++f) for (delta = 0U; delta < 256U; ++delta) {
        memset(&g, 0, sizeof(g)); memset(g.ram, 0x55, sizeof(g.ram));
        g.area_prg = data; g.area_prg_size = sizeof(data);
        g.ram[0x1eU + 5U] = 0U;
        force_value = (mysmb_u8)f;
        y_value = (mysmb_u8)(data[0x4ed5U + (f >> 4U)] + delta);
        memcpy(expected, g.ram, sizeof(expected));
        difference = (mysmb_u8)(delta < 128U ? delta : 256U - delta);
        result = (mysmb_u8)(f + (difference < 8U ? 16U : 0U));
        expected[0x434U + 5U] = result; expected[0xcfU + 5U] = y_value;
        expected[0x3c5U + 5U] = data[0x4edaU + (result >> 4U)];
        expected[0x88U] = 0x83U; stage = bad = 0U;
        mysmb_objects_step_flying_cheep_cheeps_slot(&g, 5U);
        if (bad || stage != 2U || memcmp(g.ram, expected, sizeof(expected))) return 1;
    }
    g.ram[0x1eU + 5U] = 0x21U;
    memcpy(expected, g.ram, sizeof(expected)); expected[0x3c5U + 5U] = 0U;
    expected[0x88U] = 0xa4U; stage = bad = 0U;
    mysmb_objects_step_flying_cheep_cheeps_slot(&g, 5U);
    return bad || stage != 3U || memcmp(g.ram, expected, sizeof(expected)) ? 2 : 0;
}
