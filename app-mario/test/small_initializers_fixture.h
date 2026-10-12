#ifndef MYSMB_SMALL_INITIALIZERS_FIXTURE_H
#define MYSMB_SMALL_INITIALIZERS_FIXTURE_H
#include "enemy_init_fixture.h"

static unsigned char mysmb_small_init_slot(unsigned int n)
{
    return (unsigned char)(n < 96U ? (n % 48U) / 8U :
        (n < 160U ? 5U : (n - 160U) % 6U));
}

/* NMI RAM input; original loop, queue and initializer vectors stay intact. */
static void mysmb_small_init_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char positions[8] = {0xf8U,0xffU,0U,0x0fU,0x10U,0x70U,0x78U,0xf7U};
    unsigned char slot, id, i;
    slot = mysmb_small_init_slot(n);
    id = n < 48U ? 13U : (n < 96U ? 14U :
        (n < 160U ? 24U : (unsigned char)(0x12U + (n - 160U) / 6U)));
    mysmb_enemy_init_fixture(ram, 26U);
    for (i = 0U; i < 6U; ++i) {
        ram[0x0fU + i] = (unsigned char)(0x80U + i);
        ram[0x16U + i] = (n >= 96U && n < 160U &&
            ((n - 96U) & (1U << i))) ? 17U : 6U;
        ram[0x1eU + i] = (unsigned char)(0x21U + i);
    }
    ram[0x0fU + slot] = 0U;
    ram[0x6cdU] = id == 0x13U ? 0x12U : id;
    ram[0xcfU + slot] = positions[n % 8U];
    ram[0x46U + slot] = 0x41U;
    ram[0xa0U + slot] = 0x67U;
    ram[0x434U + slot] = 0x39U;
    ram[0x401U + slot] = 0x29U;
    ram[0x417U + slot] = 0x53U;
    ram[0x78fU] = 2U; /* Original timer early return isolates vector writes. */
}

static int mysmb_small_init_argument(const char *text)
{
    static const char prefix[] = "--fixture=t39-small-init=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U; digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 196U) return 0;
    return (int)value + 1;
}
#endif
