#ifndef MYSMB_FIREWORKS_FIXTURE_H
#define MYSMB_FIREWORKS_FIXTURE_H

#include "enemy_init_fixture.h"

static unsigned char mysmb_fireworks_slot(unsigned int n)
{
    return n < 12U ? (unsigned char)(n / 2U) :
        (unsigned char)(((n - 12U) / 18U + 1U) % 6U);
}

/* Source NMI queue/vector inputs; CPU entry and return remain unmodified. */
static void mysmb_fireworks_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char positions[3] = {0U,47U,255U};
    unsigned int i, index, variant, star;
    unsigned char slot;
    mysmb_enemy_init_fixture(ram, 44U);
    slot = mysmb_fireworks_slot(n);
    for (i = 0U; i < 6U; ++i) {
        ram[0x0fU + i] = (unsigned char)(0x80U + i);
        ram[0x16U + i] = 0U;
    }
    ram[0x0fU + slot] = 0U;
    ram[0x78fU] = n < 12U ? (unsigned char)((n & 1U) ? 255U : 1U) : 0U;
    star = n < 12U ? (slot + 1U) % 6U : (n - 12U) / 18U;
    index = n < 12U ? 0U : (n - 12U) / 3U % 6U;
    variant = n < 12U ? 0U : (n - 12U) % 3U;
    ram[0x16U + star] = 49U;
    if (star > 0U && slot != 0U) ram[0x16U] = 49U;
    ram[0x6d7U] = variant == 0U ? (unsigned char)(index + 1U) :
        (unsigned char)(variant == 1U ? 1U : 0U);
    ram[0x1eU + star] = variant == 0U ? 0U :
        (unsigned char)(index + (variant == 2U ? 1U : 0U));
    ram[0x87U + star] = positions[variant];
    ram[0x6eU + star] = variant == 0U ? 0U :
        (unsigned char)(variant == 1U ? 4U : 255U);
    ram[0x401U + slot] = 0x39U;
    ram[0x434U + slot] = 0x67U;
    ram[0x49aU + slot] = 0x45U;
    ram[0x58U + slot] = 0x27U;
    ram[0xa0U + slot] = 0x35U;
}

static int mysmb_fireworks_argument(const char *text)
{
    static const char prefix[] = "--fixture=t39-fireworks=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U; digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 120U) return 0;
    return (int)value + 1;
}
#endif
