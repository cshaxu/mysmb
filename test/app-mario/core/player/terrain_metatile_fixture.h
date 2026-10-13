#ifndef MYSMB_TERRAIN_METATILE_FIXTURE_H
#define MYSMB_TERRAIN_METATILE_FIXTURE_H
#include "player_terrain_fixture.h"

/* The ordinary terrain root selects a coin or axe; control only the
 * naturally reached handler's RAM inputs, preserving CPU/ROM/stack state. */
static void mysmb_terrain_metatile_inputs(unsigned char *r, unsigned int n)
{
    static const unsigned char coins[4] = { 0U, 98U, 99U, 255U };
    unsigned int address;
    r[7U] = (unsigned char)(4U + ((n >> 3U) % 3U));
    r[6U] = (n & 32U) ? 0xd3U : 3U;
    r[2U] = (n & 64U) ? 0xb0U : 0x10U;
    address = (unsigned int)r[7U] * 256U + r[6U] + r[2U];
    r[address] = (n & 1U) ? 0xc5U : 0xc2U;
    r[0x74eU] = (unsigned char)((n >> 1U) & 3U);
    r[0x748U] = (unsigned char)((n >> 3U) * 17U);
    r[0x75eU] = coins[(n >> 4U) & 3U];
    r[0x753U] = (unsigned char)((n >> 3U) & 1U);
    r[0x75aU] = (n & 32U) ? 255U : 2U;
}
static int mysmb_terrain_metatile_argument(const char *text)
{
    static const char prefix[] = "--fixture=t43-coin-axe=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i]; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    return digits && !text[i] && value < 128U ? (int)value + 1 : 0;
}
#endif
