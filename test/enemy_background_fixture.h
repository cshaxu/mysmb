#ifndef MYSMB_ENEMY_BACKGROUND_FIXTURE_H
#define MYSMB_ENEMY_BACKGROUND_FIXTURE_H
#include "normal_actor_fixture.h"

static unsigned int background_root_inputs_done, background_hit_inputs_done;
static void mysmb_background_fixture(unsigned char *r, unsigned int n)
{
    mysmb_normal_actor_fixture(r, n & 1U);
    background_root_inputs_done = background_hit_inputs_done = 0U;
}
static void mysmb_background_inputs(unsigned char *r, unsigned short pc,
    unsigned char x, unsigned int n)
{
    unsigned int i, slot;
    static const unsigned char hit_ids[4] = { 7U, 8U, 0x33U, 9U };
    slot = (n & 1U) ? 5U : 0U;
    if (x != slot) return;
    if (pc == 0xdfc1U && !background_root_inputs_done) {
        background_root_inputs_done = 1U;
        for (i = 0x500U; i < 0x6a0U; ++i)
            r[i] = n >= 1024U ? 0x23U : (n >= 768U ? (unsigned char)n : 0U);
        r[0x16U + slot] = n < 256U ? (unsigned char)n : (n < 512U ? 18U : 0U);
        r[0xcfU + slot] = n >= 256U && n < 512U ? (unsigned char)n : 0x80U;
        r[0x1eU + slot] = n >= 512U && n < 768U ? (unsigned char)n : 0U;
        r[0x6eU + slot] = 1U; r[0x87U + slot] = 0x70U;
        r[0x6dU] = 1U; r[0x86U] = 0x40U;
        r[0x74eU] = 1U; r[0x3aeU] = 0x30U;
    }
    if (pc == 0xdffaU && n >= 1024U && !background_hit_inputs_done) {
        background_hit_inputs_done = 1U;
        r[0x16U + slot] = n < 1280U ? 0U :
            (n < 1536U ? (unsigned char)n : hit_ids[n & 3U]);
        r[0x3aeU] = n < 1280U ? (unsigned char)n : 0U;
        r[0x1eU + slot] = n >= 1536U && n < 1792U ? (unsigned char)n : 0xa1U;
        r[0xcfU + slot] = (unsigned char)(n & 3U);
        r[0x74eU] = (unsigned char)(n & 1U);
        r[0x6eU + slot] = (n & 4U) ? 255U : 0U;
        r[0x6dU] = (n & 8U) ? 255U : 0U;
        r[0x87U + slot] = n >= 1792U ? (unsigned char)n : ((n & 16U) ? 255U : 0U);
        r[0x86U] = (n & 32U) ? 255U : 0U;
        r[0x46U + slot] = 0xa5U;
    }
}
static int mysmb_background_argument(const char *text)
{
    static const char prefix[] = "--fixture=t43-enemy-background=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i]; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 4U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    return digits && !text[i] && value < 2048U ? (int)value + 1 : 0;
}
#endif
