#ifndef MYSMB_LAKITU_MOVEMENT_FIXTURE_H
#define MYSMB_LAKITU_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_lakitu_movement_slot(unsigned int n)
{ return (unsigned char)((n & 1U) * 5U); }
static void mysmb_lakitu_movement_fixture(unsigned char *ram, unsigned int n)
{
    unsigned int i;
    unsigned char slot;
    slot = mysmb_lakitu_movement_slot(n);
    mysmb_actor_dispatch_fixture(ram, 34U + (n & 1U));
    for (i = 0U; i < 6U; ++i) ram[0xfU + i] = 0U;
    ram[0xfU + slot] = 1U; ram[0x16U + slot] = 17U;
    ram[0x1eU + slot] = 0U; ram[0x747U] = 0U;
}
/* Declared input variations at naturally reached entries, independent of
 * observation. No CPU/register, PC, stack, ROM or output patches. */
static void mysmb_lakitu_movement_inputs(unsigned char *r, unsigned int n,
                                       unsigned int pc)
{
    static const unsigned char distances[8] = {0,59,60,61,128,192,255,4};
    static const unsigned char directions[4] = {0,1,2,255};
    static const unsigned char speeds[4] = {0,1,2,255};
    static const unsigned char player_speeds[4] = {0,24,25,255};
    unsigned char slot;
    slot = mysmb_lakitu_movement_slot(n);
    if (pc == 0xcf28U) {
        r[0x1eU + slot] = (unsigned char)(n < 32U ? 0x20U : (n < 64U ? 1U : 0U));
        r[0x6dU] = 1U; r[0x86U] = 0U;
        r[0x6eU + slot] = (unsigned char)(n & 16U ? 0U : 1U);
        r[0x87U + slot] = distances[(n / 2U) % 8U];
        r[0xa0U + slot] = directions[(n / 32U) % 4U];
        r[0x58U + slot] = speeds[(n / 128U) % 4U];
        r[0x57U] = player_speeds[(n / 8U) % 4U];
        r[0x775U] = (unsigned char)((n / 4U) % 3U);
    }
    if (pc == 0xcf6cU && n >= 512U) {
        r[0x16U + slot] = (unsigned char)((n / 64U) % 3U == 0U ? 17U :
            ((n / 64U) % 3U == 1U ? 18U : 6U));
        r[1U] = (unsigned char)n; r[2U] = (unsigned char)(n * 3U);
        r[3U] = (unsigned char)(n * 7U);
    }
}
static int mysmb_lakitu_movement_argument(const char *text)
{
    static const char prefix[] = "--fixture=t40-lakitu-movement=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 4U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    if (!digits || text[i] != '\0' || value >= 1024U) return 0;
    return (int)value + 1;
}
#endif
