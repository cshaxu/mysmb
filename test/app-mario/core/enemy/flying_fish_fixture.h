#ifndef MYSMB_FLYING_FISH_FIXTURE_H
#define MYSMB_FLYING_FISH_FIXTURE_H

#include "enemy_init_fixture.h"

static unsigned char mysmb_flying_fish_slot(unsigned int n)
{
    return n < 24U ? (unsigned char)(n / 4U) : 0U;
}

/* Original NMI queue/vector route; only source RAM is prepared. */
static void mysmb_flying_fish_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char speeds[8] = {0U,1U,7U,8U,24U,25U,127U,255U};
    unsigned int i, variant, speed;
    unsigned char slot;
    mysmb_enemy_init_fixture(ram, 40U);
    slot = mysmb_flying_fish_slot(n);
    for (i = 0U; i < 6U; ++i) ram[0x0fU + i] = (unsigned char)(0x80U + i);
    ram[0x0fU + slot] = 0U;
    ram[0x78fU] = n < 24U && (n & 1U) ? 0x40U : 0U;
    ram[0x6ccU] = (n & 2U) ? 1U : 0U;
    variant = n < 24U ? n % 4U : (n - 24U) % 16U;
    speed = n < 24U ? 0U : (n - 24U) / 16U;
    ram[0x57U] = speeds[speed];
    ram[0x86U] = (unsigned char)(variant * 17U);
    ram[0x6dU] = (variant & 1U) ? 0xffU : 0U;
    /* NMI shifts these bytes once; select exact low bits at chain entry. */
    for (i = 0U; i < 8U; ++i) ram[0x7a7U + i] = 0U;
    ram[0x7a7U + slot] = (unsigned char)(2U * (variant & 3U));
    ram[0x7a8U + slot] = (unsigned char)(2U * (speed == 0U ? 1U : variant / 4U));
    ram[0x7a9U + slot] = (unsigned char)(2U * variant);
    ram[0x434U + slot] = 0x39U;
    ram[0xa0U + slot] = 0x67U;
    ram[0x58U + slot] = 0x45U;
    ram[0x401U + slot] = 0x29U;
}

static int mysmb_flying_fish_argument(const char *text)
{
    static const char prefix[] = "--fixture=t38-fish=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U; digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 152U) return 0;
    return (int)value + 1;
}
#endif
