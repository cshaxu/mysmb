#ifndef MYSMB_BOWSER_FLAME_FIXTURE_H
#define MYSMB_BOWSER_FLAME_FIXTURE_H

#include "enemy_init_fixture.h"

static unsigned char mysmb_bowser_flame_slot(unsigned int n)
{
    return n < 24U ? (unsigned char)(n / 4U) :
        (unsigned char)((n & 1U) ? 5U : 0U);
}

/* Prepare source RAM at NMI; the original loop and vectors enter the chain. */
static void mysmb_bowser_flame_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char positions[8] = {
        0U,1U,13U,14U,15U,127U,248U,255U
    };
    static const unsigned char heights[16] = {
        0U,1U,0x67U,0x68U,0x6fU,0x70U,0x77U,0x78U,
        0x7fU,0x80U,0x87U,0x88U,0x8fU,0x90U,0xf8U,0xffU
    };
    unsigned int i, variant;
    unsigned char slot;
    mysmb_enemy_init_fixture(ram, n < 24U ? 90U : 42U);
    slot = mysmb_bowser_flame_slot(n);
    for (i = 0U; i < 7U; ++i) ram[0x0fU + i] = (unsigned char)(0x80U + i);
    ram[0x0fU + slot] = 0U;
    ram[0x87U + slot] = positions[n % 8U];
    ram[0xcfU + slot] = heights[n % 16U];
    ram[0x6eU + slot] = (n & 2U) ? 0xffU : 4U;
    ram[0x49aU + slot] = 0x37U;
    ram[0x369U] = 0x19U;
    ram[0x363U] = 0x29U;
    ram[0x367U] = 7U;
    ram[0x434U + slot] = 0x39U;
    ram[0x401U + slot] = 0x29U;
    ram[0x796U + slot] = 0x55U;
    ram[0x78aU + slot] = 0x45U;
    for (i = 0U; i < 8U; ++i) ram[0x7a7U + i] = 0U;
    if (n < 24U) {
        ram[0x0fU + slot + 1U + n % 4U % (6U - slot)] = 0U;
        return;
    }
    ram[0x368U] = 3U;
    ram[0x19U] = n >= 96U ? 45U : 0U;
    ram[0x78fU] = n < 32U ? (unsigned char)(n - 23U) : 0U;
    if (n < 96U) {
        variant = n < 32U ? 0U : n - 32U;
        ram[0x367U] = (unsigned char)(variant / 8U);
        ram[0x6ccU] = (unsigned char)((variant / 4U) & 1U);
        ram[0x7a7U + slot] = (unsigned char)(2U * (variant & 3U));
        ram[0x71dU] = (variant & 1U) ? 0xffU : 0xc0U;
        ram[0x71bU] = (variant & 2U) ? 0xffU : 4U;
    } else {
        variant = n - 96U;
        ram[0x7a7U + slot] = (unsigned char)(2U * (variant / 16U));
        ram[0x8aU] = positions[variant % 8U];
        ram[0xd2U] = heights[variant % 16U];
        ram[0x71U] = (variant & 1U) ? 0xffU : 4U;
    }
}

static int mysmb_bowser_flame_argument(const char *text)
{
    static const char prefix[] = "--fixture=t39-bowser-flame=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U; digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 160U) return 0;
    return (int)value + 1;
}
#endif
