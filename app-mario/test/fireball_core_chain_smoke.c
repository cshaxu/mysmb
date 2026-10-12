#include "core/fireball/fireball.h"
#include "core/oam/oam.h"
#include "core/world/world.h"
#include <string.h>
#include <stdio.h>

static unsigned int errors, calls;
static mysmb_u8 selected, mask, mutate;
static char order[16];
static void record(char c)
{
    if (calls >= 15U) { ++errors; return; }
    order[calls++] = c; order[calls] = '\0';
}
static void slot_check(mysmb_u8 slot)
{ if (slot != selected) ++errors; }
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *g,
    mysmb_u8 slot, mysmb_u8 force, mysmb_u8 maximum)
{
    record('G'); slot_check((mysmb_u8)(slot - 7U));
    if (g->ram[8U] != selected || force != 0x50U || maximum != 3U) ++errors;
}
mysmb_u8 mysmb_world_move_spr_object_horizontally(struct mysmb_game *g, mysmb_u8 slot)
{
    record('M'); slot_check((mysmb_u8)(slot - 7U));
    if (mutate != 0U) { selected ^= 1U; g->ram[8U] = selected; }
return 0U; }
void mysmb_oam_relative_fireball_position(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; record('R'); slot_check(slot); }
void mysmb_oam_get_fireball_offscreen_bits(struct mysmb_game *g, mysmb_u8 slot)
{ record('O'); slot_check(slot); g->ram[0x3d2U] = (mysmb_u8)~mask; }
void mysmb_world_get_fireball_bounding_box(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; record('B'); slot_check(slot); }
void mysmb_world_fireball_background_collision(struct mysmb_game *g, mysmb_u8 slot)
{ record('T'); slot_check(slot); g->ram[0x3d2U] = mask; }
void mysmb_world_fireball_enemy_collision(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; record('E'); slot_check(slot); }
void mysmb_oam_draw_fireball(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; record('D'); slot_check(slot); }
void mysmb_oam_draw_fireball_explosion(struct mysmb_game *g, mysmb_u8 slot)
{
    record('X'); slot_check(slot);
    if (g->ram[8U] != selected || (g->ram[0x24U + slot] & 0x80U) == 0U) ++errors;
}

int main(void)
{
    static struct mysmb_game g;
    unsigned int slot, state, facing, x, bits, cases;
    cases = 0U;
    for (slot = 0U; slot < 2U; ++slot)
    for (state = 0U; state < 256U; ++state)
    for (facing = 1U; facing <= 2U; ++facing)
    for (x = 251U; x < 256U; ++x) {
        memset(&g, 0, sizeof(g)); selected = (mysmb_u8)slot;
        calls = 0U; order[0] = '\0'; mask = 0U; mutate = 0U;
        g.ram[8U] = 0x55U; g.ram[0x24U + slot] = (mysmb_u8)state;
        g.ram[0x33U] = (mysmb_u8)facing; g.ram[0x86U] = (mysmb_u8)x;
        g.ram[0x6dU] = 0xffU; g.ram[0xceU] = 0x7fU;
        mysmb_fireball_step_object(&g, (mysmb_u8)slot); ++cases;
        if (g.ram[8U] != slot) ++errors;
        if (strcmp(order, state == 0U ? "" : state >= 128U ? "RX" : "GMROBTED") != 0) ++errors;
        if (state >= 2U && state < 128U) {
            if (g.ram[0x8dU + slot] != (mysmb_u8)(x + 4U) ||
                g.ram[0x74U + slot] != (mysmb_u8)(x >= 252U ? 0U : 0xffU) ||
                g.ram[0xd5U + slot] != 0x7fU || g.ram[0xbcU + slot] != 1U ||
                g.ram[0x5eU + slot] != (facing == 1U ? 0x40U : 0xc0U) ||
                g.ram[0xa6U + slot] != 4U || g.ram[0x4a0U + slot] != 7U ||
                g.ram[0x24U + slot] != state - 1U) ++errors;
        } else if (g.ram[0x24U + slot] != state) ++errors;
    }
    /* Every bit pattern is tested after the background child changes it. */
    for (bits = 0U; bits < 256U; ++bits) {
        memset(&g, 0, sizeof(g)); selected = 0U; mask = (mysmb_u8)bits;
        calls = 0U; order[0] = '\0'; g.ram[0x24U] = 1U;
        mysmb_fireball_step_object(&g, 0U);
        if (strcmp(order, (bits & 0xccU) != 0U ? "GMROBT" : "GMROBTED") != 0 ||
            g.ram[0x24U] != ((bits & 0xccU) != 0U ? 0U : 1U)) ++errors;
    }
    memset(&g, 0, sizeof(g)); selected = 0U; mask = 0U; mutate = 1U;
    calls = 0U; order[0] = '\0'; g.ram[0x24U] = 1U;
    mysmb_fireball_step_object(&g, 0U);
    if (selected != 1U || strcmp(order, "GMROBTED") != 0) ++errors;
    printf("core states=%u mask cases=256 offset reload=1 errors=%u\n", cases, errors);
    return errors != 0U;
}
