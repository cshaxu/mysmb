#ifndef MYSMB_PIPE_ENTRY_FIXTURE_H
#define MYSMB_PIPE_ENTRY_FIXTURE_H
#include "player_terrain_fixture.h"

static void mysmb_pipe_entry_inputs(unsigned char *r, unsigned int n)
{
    static const unsigned char xs[6] = { 0U, 0x5fU, 0x60U, 0x9fU, 0xa0U, 255U };
    r[0xbU] = 4U; r[0U] = 0x11U; r[1U] = 0x10U;
    r[0x6d6U] = 0U; r[0x86U] = 0x80U;
    r[0x750U] = 0x55U; r[0x75fU] = 7U;
    r[0x751U] = r[0x760U] = r[0x75cU] = r[0x752U] = 9U;
    r[0x75dU] = (n & 1U) ? 255U : 0U;
    r[0x757U] = (n & 2U) ? 255U : 0x7fU;
    r[0xfcU] = 0x40U; r[0xffU] = 0x80U;
    r[0x3c4U] = 0xffU; r[0x6deU] = 0x22U;
    if (n < 128U) {
        r[0xbU] = (unsigned char)n;
        r[0U] = (n & 16U) ? 0x11U : 0U;
        r[1U] = (n & 32U) ? 0x10U : 0x11U;
        r[0x6d6U] = (n & 64U) ? 0x80U : 0U;
    } else if (n < 384U) {
        r[0x6d6U] = (unsigned char)(n - 128U);
        r[0x86U] = xs[((n - 128U) >> 2U) % 6U];
    } else {
        r[0x6d6U] = (unsigned char)(0x80U | (n & 3U));
        r[0x86U] = (unsigned char)((n - 384U) * 2U);
    }
}
static int mysmb_pipe_entry_argument(const char *text)
{
    static const char prefix[] = "--fixture=t43-pipe-entry=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i]; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    return digits && !text[i] && value < 512U ? (int)value + 1 : 0;
}
#endif
