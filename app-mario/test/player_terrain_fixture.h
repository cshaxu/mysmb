#ifndef MYSMB_PLAYER_TERRAIN_FIXTURE_H
#define MYSMB_PLAYER_TERRAIN_FIXTURE_H
#include "entrance_fixture.h"

/* Original NMI reaches PlayerBGCollision; only its RAM inputs are controlled. */
static void mysmb_player_terrain_fixture(unsigned char *r, unsigned int n)
{
    (void)n;
    mysmb_entrance_fixture(r, 0U);
    r[0xeU] = 8U;
    r[0x747U] = 0U;
}
static void mysmb_player_terrain_inputs(unsigned char *r, unsigned int n)
{
    unsigned int i, k;
    for (i = 0x500U; i < 0x6a0U; ++i) r[i] = 0U;
    r[0xeU] = 8U; r[0x716U] = 0U; r[0x704U] = 0U;
    r[0xb5U] = 1U; r[0xceU] = 0x70U; r[0x9fU] = 2U;
    r[0x6dU] = 1U; r[0x86U] = 0x34U; r[0x1dU] = 1U;
    r[0x754U] = 1U; r[0x714U] = 0U; r[0x74eU] = 1U;
    r[0x70eU] = 0U; r[0x34bU] = 0U; r[0x33U] = 1U;
    r[0x45U] = 1U; r[0xbU] = 0U; r[0x784U] = 0U;
    if (n == 0U) r[0x643U] = 0xc5U;
    if (n == 1U) r[0x644U] = 0xc5U;
    if (n == 2U) { r[0x643U] = 0xc2U; r[0x644U] = 0x61U; }
    if (n == 3U) { r[0x1dU] = 3U; r[0x9fU] = 0xffU; r[0xceU] = 0x2fU; }
    if (n == 4U) r[0x643U] = 0x61U;
    if (n == 5U) r[0x643U] = 0x5fU;
    if (n == 6U) r[0x643U] = 0x67U;
    if (n == 7U) { r[0xb5U] = 0U; r[0x1dU] = 3U; }
    if (n >= 8U && n < 72U) {
        k = n - 8U;
        r[0xeU] = (unsigned char)((k & 7U) == 7U ? 11U : k & 7U);
        r[0x716U] = (unsigned char)((k >> 3U) & 1U);
        r[0x704U] = (unsigned char)((k >> 4U) & 1U);
        r[0x1dU] = (unsigned char)((k & 32U) ? 3U : 0U);
    }
    /* Exhaust every metatile at the head, selected foot, and side entry. */
    if (n >= 72U && n < 328U) {
        r[0xceU] = 0x84U; r[0x9fU] = 0xffU; r[0x754U] = 0U;
        r[0x633U] = (unsigned char)(n - 72U);
    }
    if (n >= 328U && n < 584U) {
        k = n - 328U;
        r[(k & 1U) ? 0x644U : 0x643U] = (unsigned char)k;
    }
    if (n >= 584U && n < 840U) {
        r[0x86U] = 0x2cU;
        r[0x632U] = (unsigned char)(n - 584U);
    }
    if (n >= 840U && n < 856U) {
        k = n - 840U;
        r[0x754U] = (unsigned char)((k & 7U) == 7U ? 0xffU : k & 7U);
        r[0x714U] = (unsigned char)((k >> 3U) & 1U);
    }
    if (n >= 856U && n < 880U) {
        static const unsigned char ys[12] = {
            0U,8U,15U,16U,31U,32U,0x83U,0x84U,0xceU,0xcfU,0xd0U,0xffU
        };
        k = n - 856U;
        r[0xceU] = ys[k % 12U]; r[0x9fU] = k < 12U ? 0xffU : 1U;
        r[0x754U] = 0U; r[0x704U] = k < 12U ? 1U : 0U;
    }
    if (n >= 880U && n < 896U) {
        k = n - 880U;
        r[0xceU] = (unsigned char)((k & 1U) ? 0x84U : 0x83U);
        r[0x9fU] = 0xffU; r[0x754U] = 0U; r[0x633U] = 0x51U;
        r[0x74eU] = (unsigned char)((k >> 1U) & 1U);
        r[0x784U] = (unsigned char)((k >> 2U) & 1U);
        if (k & 8U) r[0x9fU] = 0U;
    }
    if (n >= 896U && n < 928U) {
        k = n - 896U;
        r[0xceU] = (unsigned char)((k & 1U) ? 0x75U : 0x74U);
        r[0x70eU] = (unsigned char)((k >> 1U) & 1U);
        r[0x45U] = (unsigned char)((k & 4U) ? 2U : 1U);
        r[0x704U] = (unsigned char)((k >> 3U) & 1U);
        r[0x643U] = (k & 16U) ? 0x67U : 0x61U;
    }
    if (n >= 928U && n < 992U) {
        k = n - 928U;
        r[0x86U] = (k & 1U) ? 0x24U : 0x20U;
        r[0x642U] = r[0x643U] = 0x61U;
        r[0x632U] = (k & 2U) ? 0x6cU : 0x1fU;
        r[0x71aU] = (unsigned char)((k >> 2U) & 1U);
        r[0x3c4U] = (k & 8U) ? 0x20U : 0U;
        r[0xeU] = (k & 16U) ? 7U : 8U;
        r[0x33U] = (k & 32U) ? 2U : 1U;
    }
    if (n >= 992U && n < 1024U) {
        k = n - 992U;
        r[0x643U] = (k & 1U) ? 0xc2U : 0x61U;
        r[0x644U] = (k & 2U) ? 0xc3U : 0x11U;
        r[0xbU] = (k & 4U) ? 4U : 0U;
        r[0x70eU] = (unsigned char)((k >> 3U) & 1U);
        r[0x9fU] = (k & 16U) ? 0xffU : 2U;
    }

    if (n >= 1024U && n < 1026U) {
        r[0x86U] = 0x2cU; r[0x70eU] = 1U;
        r[n == 1024U ? 0x632U : 0x633U] = n == 1024U ? 0x67U : 0x68U;
    }
    if (n >= 1026U && n < 1034U) {
        r[0x86U] = 0x24U;
        r[0x642U] = r[0x643U] = 0x61U;
        r[0x632U] = n == 1026U ? 0x61U : (n == 1027U ? 0x10U : 0x6cU);
        if (n >= 1028U) r[0xeU] = (unsigned char)(n - 1024U);
    }

}
static int mysmb_player_terrain_argument(const char *text)
{
    static const char prefix[] = "--fixture=t43-player-terrain=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i]; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 4U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    return digits && !text[i] && value < 1034U ? (int)value + 1 : 0;
}
#endif
