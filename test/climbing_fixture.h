#ifndef MYSMB_CLIMBING_FIXTURE_H
#define MYSMB_CLIMBING_FIXTURE_H
#include "player_terrain_fixture.h"

static unsigned char mysmb_climbing_tile(unsigned int n)
{
    return n < 256U ? (unsigned char)(0x24U + (n & 3U)) :
        (n < 512U ? 0x27U : (n < 768U ? 0x26U : 0x25U));
}
static void mysmb_climbing_root_inputs(unsigned char *r, unsigned int n)
{
    mysmb_player_terrain_inputs(r, 584U + mysmb_climbing_tile(n));
}
static void mysmb_climbing_inputs(unsigned char *r, unsigned int n)
{
    static const unsigned char engines[4] = { 8U, 4U, 5U, 0U };
    unsigned int i;
    r[4U] = 8U; r[6U] = 0U; r[0x33U] = 1U;
    r[0xeU] = 8U; r[0xceU] = 0x70U;
    r[0x86U] = 0x40U; r[0x71cU] = 0x20U;
    r[0x71bU] = (n & 16U) ? 0U : 255U;
    r[0x723U] = (n & 32U) ? 255U : 0U;
    r[0x57U] = 0x91U; r[0x705U] = 0x83U;
    for (i = 0U; i < 6U; ++i) {
        r[0x16U + i] = (unsigned char)((n & (1U << i)) ?
            (n < 64U ? 0x33U : 12U) : 13U);
        r[0xfU + i] = (unsigned char)(0x80U + i);
    }
    if (n < 256U) {
        r[0xeU] = engines[(n >> 2U) & 3U];
        r[0xceU] = (unsigned char)((n >> 4U) * 17U);
        r[0x33U] = (n & 64U) ? 2U : 1U;
        r[0x86U] = (n & 128U) ? 0x2fU : 0x30U;
        r[6U] = (n & 16U) ? 0U : 0xffU;
    } else if (n < 512U) {
        r[0x33U] = (unsigned char)n;
    } else if (n < 768U) {
        r[4U] = (unsigned char)n;
        r[0xceU] = 0x1fU; r[0x86U] = 0x2fU;
    } else {
        r[6U] = (unsigned char)n;
        r[0xeU] = 5U; r[0x33U] = (unsigned char)(1U + (n & 1U));
    }
}
static int mysmb_climbing_argument(const char *text)
{
    static const char prefix[] = "--fixture=t43-climbing=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i]; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 4U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    return digits && !text[i] && value < 1024U ? (int)value + 1 : 0;
}
#endif
