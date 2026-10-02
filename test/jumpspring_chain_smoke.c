#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

static unsigned int calls, errors, mutation;
static mysmb_u8 selected, original_y;
static void check_child(unsigned int expected, mysmb_u8 slot)
{
    if (calls != expected || slot != selected) ++errors;
    ++calls;
}
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *g,
                                               mysmb_u8 slot)
{
    check_child(0U, slot);
    if (g->ram[0x00ceU] != original_y) ++errors;
    return 0x5aU;
}
void mysmb_oam_relative_enemy_position(struct mysmb_game *g, mysmb_u8 slot)
{
    check_child(1U, slot);
    if (g->ram[0x03d1U] != 0x5aU) ++errors;
    g->ram[0x03aeU] = 0x39U;
}
mysmb_u8 mysmb_objects_draw_normal_enemy_graphics(struct mysmb_game *g, mysmb_u8 slot)
{
    check_child(2U, slot);
    if (g->ram[0x03aeU] != 0x39U) ++errors;
    return 1U;
}
void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *g,
                                               mysmb_u8 slot)
{
    check_child(3U, slot);
    if (mutation == 1U) g->ram[0x070eU] = 0U;
    if (mutation == 2U) {
        g->ram[0x070eU] = 0xffU;
        g->ram[0x0786U] = 0U;
    }
    if (mutation == 3U) g->ram[0x0786U] = 9U;
}
int main(void)
{
    static struct mysmb_game g;
    static const mysmb_u8 player_y[4] = { 2U, 2U, 0xfeU, 0xfeU };
    static const mysmb_u8 spring_y[4] = { 0U, 8U, 0U, 0xf8U };
    unsigned int slot, anim, frozen, buttons, timer, cases;
    mysmb_u8 force, expected_anim, expected_timer;
    cases = 0U;
    for (slot = 0U; slot < 6U; ++slot)
    for (anim = 0U; anim < 5U; ++anim)
    for (frozen = 0U; frozen < 2U; ++frozen)
    for (buttons = 0U; buttons < 4U; ++buttons)
    for (timer = 0U; timer < 2U; ++timer) {
        memset(&g, 0, sizeof(g));
        calls = 0U; selected = (mysmb_u8)slot; original_y = 0U;
        g.ram[0x070eU] = (mysmb_u8)anim;
        g.ram[0x0747U] = (mysmb_u8)frozen;
        g.ram[0x0786U] = (mysmb_u8)timer;
        g.ram[0x0058U + slot] = 0xf8U;
        g.ram[0x00cfU + slot] = 0x55U;
        g.ram[0x06dbU] = 0xfaU;
        g.ram[0x009fU] = 0x33U;
        g.ram[0x000aU] = (mysmb_u8)((buttons & 1U) * 0x80U);
        g.ram[0x000dU] = (mysmb_u8)((buttons & 2U) * 0x40U);
        mysmb_objects_step_jumpspring(&g, selected);
        if (calls != 4U) ++errors;
        force = 0xfaU; expected_anim = (mysmb_u8)anim;
        if (frozen == 0U && anim != 0U) {
            if (g.ram[0x00ceU] != player_y[anim - 1U] ||
                g.ram[0x00cfU + slot] != spring_y[anim - 1U]) ++errors;
            if (anim >= 2U && buttons == 1U) force = 0xf4U;
            if (anim == 4U) expected_anim = 0U;
        } else if (g.ram[0x00ceU] != 0U ||
                   g.ram[0x00cfU + slot] != 0x55U) ++errors;
        if (g.ram[0x06dbU] != force ||
            g.ram[0x009fU] != (anim == 4U && frozen == 0U ? force : 0x33U))
            ++errors;
        expected_timer = (mysmb_u8)timer;
        if (expected_anim != 0U && timer == 0U) {
            ++expected_anim; expected_timer = 4U;
        }
        if (g.ram[0x070eU] != expected_anim ||
            g.ram[0x0786U] != expected_timer) ++errors;
        ++cases;
    }
    for (mutation = 1U; mutation <= 3U; ++mutation) {
        memset(&g, 0, sizeof(g)); calls = 0U;
        g.ram[0x0747U] = 1U; g.ram[0x070eU] = 1U;
        mysmb_objects_step_jumpspring(&g, selected);
        if (calls != 4U || g.ram[0x070eU] != (mutation == 3U ? 1U : 0U) ||
            g.ram[0x0786U] != (mutation == 1U ? 0U : mutation == 2U ? 4U : 9U))
            ++errors;
    }
    printf("jumpspring cases=%u; child order/state mutations; errors=%u\n", cases, errors);
    return errors != 0U;
}
