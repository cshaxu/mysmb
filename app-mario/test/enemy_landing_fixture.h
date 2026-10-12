#ifndef MYSMB_ENEMY_LANDING_FIXTURE_H
#define MYSMB_ENEMY_LANDING_FIXTURE_H
#include "normal_actor_fixture.h"

static unsigned int landing_inputs_done;
static void mysmb_landing_fixture(unsigned char *r, unsigned int n)
{
    mysmb_normal_actor_fixture(r, n & 1U);
    landing_inputs_done = 0U;
}
static void mysmb_landing_inputs(unsigned char *r, unsigned short pc,
    unsigned char x, unsigned int n)
{
    unsigned int i, slot;
    static const unsigned char ids[4] = { 6U, 18U, 3U, 0U };
    static const unsigned char natural_ids[9] = { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 18U, 46U };
    slot = (n & 1U) ? 5U : 0U;
    if (pc != 0xdfc1U || x != slot || landing_inputs_done) return;
    landing_inputs_done = 1U;
    for (i = 0x500U; i < 0x6a0U; ++i) r[i] = n < 768U && n >= 512U ? 0U : 0x51U;
    r[0x16U + slot] = 0U;
    r[0x1eU + slot] = 0U;
    r[0xcfU + slot] = 0x80U;
    if (n < 256U) r[0x1eU + slot] = (unsigned char)n;
    else if (n < 512U) r[0xcfU + slot] = (unsigned char)(6U + ((n - 256U) % 188U));
    else if (n < 768U) r[0x1eU + slot] = (unsigned char)(n - 512U);
    else if (n < 896U) {
        r[0x1eU + slot] = 1U; r[0x16U + slot] = natural_ids[(n - 768U) % 9U];
    } else {
        r[0x1eU + slot] = 5U; r[0x16U + slot] = ids[n & 3U];
    }
    r[9U] = (unsigned char)n;
    r[0x46U + slot] = (n & 4U) ? 2U : 1U;
    r[0x6eU + slot] = 1U; r[0x87U + slot] = 0x70U;
    r[0x6dU] = 1U; r[0x86U] = 0x40U;
    r[0x74eU] = 1U; r[0x3aeU] = 0x30U;
}
static int mysmb_landing_argument(const char *text)
{
    static const char prefix[] = "--fixture=t43-enemy-landing=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i]; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 4U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    return digits && !text[i] && value < 1024U ? (int)value + 1 : 0;
}
#endif
