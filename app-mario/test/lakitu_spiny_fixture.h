#ifndef MYSMB_LAKITU_SPINY_FIXTURE_H
#define MYSMB_LAKITU_SPINY_FIXTURE_H

#include "enemy_init_fixture.h"

/* Only NMI RAM is prepared. The original queue and dispatcher select $C3A4. */
static void mysmb_lakitu_spiny_fixture(unsigned char *ram, unsigned int n)
{
    unsigned int i, lakitu;
    mysmb_enemy_init_fixture(ram, n == 1U ? 37U : 36U);
    for (i = 0U; i < 6U; ++i) ram[0x16U + i] = 0U;
    ram[0x78fU] = n == 0U ? 0x40U : 0U;
    ram[0x6d1U] = 6U;
    ram[0x71dU] = (n & 1U) ? 0xf0U : 0xa0U;
    ram[0x71bU] = (n & 2U) ? 0xffU : 4U;
    ram[0xceU] = 0x80U;
    ram[0x57U] = 0U;
    if (n < 16U) {
        if (n >= 2U && n <= 5U)
            ram[0x6d1U] = (unsigned char)(n == 2U ? 0U :
                (n == 3U ? 5U : (n == 4U ? 6U : 0xffU)));
        if (n >= 6U) ram[0x0fU + 1U + (n - 6U) % 4U] = 0U;
        return;
    }
    lakitu = 1U + (n - 16U) % 4U;
    ram[0x16U + lakitu] = 0x11U;
    ram[0x1eU + lakitu] = n == 16U ? 1U : 0U;
    ram[0xceU] = n == 17U ? 0x2bU : (n == 18U ? 0x2cU : 0x80U);
    ram[0x6eU + lakitu] = 4U;
    ram[0x87U + lakitu] = (unsigned char)(n * 7U);
    ram[0xcfU + lakitu] = (n & 1U) ? 4U : 0x40U;
    ram[0x57U] = (unsigned char)((n - 16U) / 4U);
    ram[0x775U] = (unsigned char)(n & 3U);
    /* The original NMI shifts each PRNG byte once before entering the chain. */
    for (i = 0U; i < 8U; ++i)
        ram[0x7a7U + i] = (unsigned char)(2U * ((n + i) & 3U));
    ram[0x434U] = 0x39U;
    ram[0xa0U] = 0x67U;
    ram[0x58U] = 0x45U;
    ram[0x401U] = 0x29U;
}

static int mysmb_lakitu_spiny_argument(const char *text)
{
    static const char prefix[] = "--fixture=t38-spiny=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U; digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 2U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 80U) return 0;
    return (int)value + 1;
}
#endif
