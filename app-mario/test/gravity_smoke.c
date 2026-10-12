#include "core/world/world.h"
#include <stdio.h>
#include <string.h>

/* Independent boundary expectations from original ADC/CMP/BMI/BPL rules. */
int main(void)
{
    static struct mysmb_game g;
    unsigned int failures;
    failures = 0U;
    memset(&g, 0, sizeof(g));
    g.ram[2U] = 8U; g.ram[0x9fU] = 0x80U; g.ram[0x433U] = 0xffU;
    mysmb_world_impose_gravity(&g, 0U, 0U);
    /* $80-$08=$78 has N clear, despite the speed's own sign bit. */
    if (g.ram[0x9fU] != 8U || g.ram[0x433U] != 0U ||
        g.ram[7U] != 0xffU || g.ram[0xb5U] != 0xffU) ++failures;

    memset(&g, 0, sizeof(g));
    g.ram[2U] = 2U; g.ram[1U] = 6U; g.ram[0x9fU] = 0x7fU;
    g.ram[0x433U] = 0x10U;
    mysmb_world_impose_gravity(&g, 0U, 1U);
    /* $7F-$FE=$81 sets N: upward clamp follows CMP's wrapped result. */
    if (g.ram[0x9fU] != 0xfeU || g.ram[0x433U] != 0xffU ||
        g.ram[7U] != 0xfeU) ++failures;

    memset(&g, 0, sizeof(g));
    g.ram[2U] = 3U; g.ram[0x9fU] = 0xffU;
    g.ram[0x416U] = 0xffU; g.ram[0x433U] = 1U;
    g.ram[0xceU] = 0x80U; g.ram[0xb5U] = 1U;
    mysmb_world_impose_gravity(&g, 0U, 0U);
    if (g.ram[0xceU] != 0x80U || g.ram[0xb5U] != 1U ||
        g.ram[0x416U] != 0U) ++failures;

    memset(&g, 0, sizeof(g));
    g.ram[0x43cU] = 0x40U; g.ram[0xa8U] = 7U;
    mysmb_world_residual_gravity(&g, 0U);
    if (g.ram[0U] != 0x50U || g.ram[2U] != 6U ||
        g.ram[0xa8U] != 6U || g.ram[0x43cU] != 0U) ++failures;
    memset(&g, 0, sizeof(g));
    g.ram[0x43cU] = 0x40U; g.ram[0xa8U] = 7U;
    mysmb_world_impose_gravity_block(&g, 0U);
    if (g.ram[2U] != 8U || g.ram[0xa8U] != 7U ||
        g.ram[0x43cU] != 0x90U) ++failures;

    memset(&g, 0, sizeof(g));
    g.ram[0x16U] = 0x29U;
    mysmb_world_move_platform_vertically(&g, 0U, 0U);
    if (g.ram[0U] != 9U || g.ram[1U] != 10U || g.ram[2U] != 3U ||
        g.ram[0x434U] != 9U) ++failures;
    printf("six gravity boundary/entry cases, %u failures\n", failures);
    return failures ? 1 : 0;
}
