#ifndef MYSMB_BULLET_SWIMMING_FISH_FIXTURE_H
#define MYSMB_BULLET_SWIMMING_FISH_FIXTURE_H
#include "enemy_init_fixture.h"

static unsigned char mysmb_bullet_swim_slot(unsigned int n)
{
    if (n < 12U) return (unsigned char)(n / 2U);
    if (n < 18U) return (unsigned char)(n - 12U);
    if (n < 146U) return (unsigned char)(n % 3U);
    return (unsigned char)(((n - 146U) / 6U == 0U &&
        (n - 146U) / 2U % 3U != 1U) ? 5U : 0U);
}

/* RAM-only NMI inputs; original queue, vectors and child calls execute. */
static void mysmb_bullet_swim_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char seeds[4] = {0U,0xa9U,0xaaU,0xffU};
    static const unsigned char filters[10] = {
        0U,255U,85U,170U,254U,127U,240U,15U,129U,24U
    };
    unsigned int i, seed, variant, bit, blocker, kind;
    unsigned char slot;
    mysmb_enemy_init_fixture(ram, 46U);
    slot = mysmb_bullet_swim_slot(n);
    for (i = 0U; i < 6U; ++i) {
        ram[0x0fU + i] = (unsigned char)(0x80U + i);
        ram[0x16U + i] = 0U;
    }
    ram[0x0fU + slot] = 0U;
    ram[0x78fU] = n < 12U ? (unsigned char)(n + 1U) : 0U;
    ram[0x74eU] = n < 12U ? (unsigned char)(n & 1U) : 0U;
    ram[0x75fU] = 1U;
    ram[0x6ddU] = 0U;
    seed = 0U;
    if (n >= 18U && n < 50U) {
        variant = n - 18U;
        seed = seeds[variant % 4U];
        ram[0x75fU] = (unsigned char)(variant / 4U % 2U);
        ram[0x6ddU] = (variant & 16U) ? 0xffU : 0U;
    }
    if (n >= 50U && n < 146U) {
        variant = (n - 50U) % 12U;
        bit = (n - 50U) / 12U;
        seed = bit + ((n & 2U) ? 0xa8U : 0U);
        ram[0x74eU] = (unsigned char)(variant & 1U);
        ram[0x6ddU] = variant < 10U ? filters[variant] :
            (unsigned char)(variant == 10U ? (1U << bit) : (255U ^ (1U << bit)));
    }
    if (n >= 146U) {
        blocker = (n - 146U) / 6U;
        kind = (n - 146U) / 2U % 3U;
        ram[0x74eU] = 1U;
        ram[0x16U + blocker] = kind == 2U ? 9U : 8U;
        ram[0x0fU + blocker] = kind == 1U ? 0U : (unsigned char)(0x80U + blocker);
        seed = n & 7U;
    }
    /* Invert one original ROR-chain step to obtain the desired entry byte. */
    for (i = 0U; i < 8U; ++i) ram[0x7a7U + i] = 0U;
    ram[0x7a7U + slot] = (unsigned char)(seed * 2U);
    if (slot == 0U)
        ram[0x7a8U] = (unsigned char)(2U * ((seed & 1U) ^ (seed >> 7U)));
    else ram[0x7a6U + slot] = (unsigned char)(seed >> 7U);
    ram[0x71dU] = (n & 1U) ? 255U : 0xc0U;
    ram[0x71bU] = (n & 2U) ? 255U : 0U;
    ram[0x401U + slot] = 0x39U;
    ram[0x434U + slot] = 0x67U;
    ram[0x417U + slot] = 0x45U;
    ram[0x1eU + slot] = 0x37U;
}

static int mysmb_bullet_swim_argument(const char *text)
{
    static const char prefix[] = "--fixture=t39-bullet-swim=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U; digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 182U) return 0;
    return (int)value + 1;
}
#endif
