#ifndef MYSMB_BRIDGE_COLLAPSE_FIXTURE_H
#define MYSMB_BRIDGE_COLLAPSE_FIXTURE_H
#include "actor_dispatch_fixture.h"
static void mysmb_bridge_collapse_fixture(unsigned char *r, unsigned int n)
{
    unsigned char slot, state;
    unsigned int v;
    mysmb_actor_dispatch_fixture(r, 90U);
    slot = (unsigned char)((n & 1U) * 4U);
    r[0x770U] = 2U; r[0x772U] = 0U; r[0x722U] = 0U;
    r[0x368U] = slot; r[8U] = (unsigned char)(slot == 0U ? 4U : 0U);
    r[0x16U + slot] = 45U; r[0xfU + slot] = 1U;
    r[0x1eU + slot] = 0U; r[0xcfU + slot] = 0x80U;
    r[0xb6U + slot] = 1U; r[0x6eU + slot] = 1U;
    r[0x87U + slot] = 0x90U; r[0x46U + slot] = 2U;
    r[0x6cfU] = (unsigned char)(slot == 0U ? 1U : 0U);
    r[0x363U] = 0U; r[0x364U] = (unsigned char)(n < 60U ? 1U : 2U);
    r[0x369U] = (unsigned char)((n / 2U) % 15U);
    r[0x300U] = 0U; r[0x301U] = 0U;
    if (n >= 120U) {
        v = (n - 120U) / 2U;
        state = (unsigned char)(v % 3U == 0U ? 0x20U : (v % 3U == 1U ? 0x40U : 0U));
        r[0x1eU + slot] = state;
        r[0xcfU + slot] = (unsigned char)(v % 2U ? 0xdfU : 0xe0U);
        r[0x364U] = 0U;
        if (v >= 24U) r[0x16U + slot] = 0U;
    }
}
static int mysmb_bridge_collapse_argument(const char *text)
{
    static const char prefix[] = "--fixture=t41-bridge-collapse=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    if (!digits || text[i] != '\0' || value >= 180U) return 0;
    return (int)value + 1;
}
#endif
