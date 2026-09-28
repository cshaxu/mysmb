#ifndef MYSMB_PLATFORM_INITIALIZATION_FIXTURE_H
#define MYSMB_PLATFORM_INITIALIZATION_FIXTURE_H
#include "enemy_init_fixture.h"

static unsigned char mysmb_platform_init_slot(unsigned int n)
{
    return (unsigned char)(n % 6U);
}

/* Ten original vector IDs, supplied only through NMI RAM inputs. */
static void mysmb_platform_init_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char xs[8] = {0U,7U,8U,0xefU,0xf3U,0xf4U,0xf8U,0xffU};
    static const unsigned char ys[8] = {0U,1U,0x7fU,0x80U,0x81U,0xfeU,0xffU,0x40U};
    static const unsigned char alignments[4] = {0U,0x7fU,0x80U,0xffU};
    unsigned char slot, id, i;
    unsigned int v;
    v = n % 24U; slot = mysmb_platform_init_slot(n);
    id = n < 216U ? (unsigned char)(36U + n / 24U) : 54U;
    mysmb_enemy_init_fixture(ram, 72U);
    for (i = 0U; i < 6U; ++i) ram[0x0fU+i] = (unsigned char)(0x80U+i);
    ram[0x0fU+slot] = 0U; ram[0x6cdU] = id;
    ram[0x6ccU] = (unsigned char)(v & 1U);
    ram[0x74eU] = (unsigned char)((v / 2U) % 4U);
    ram[0x3a0U] = alignments[v % 4U];
    ram[0x6eU+slot] = (unsigned char)(v % 3U == 2U ? 255U : v % 3U);
    ram[0x87U+slot] = xs[v % 8U]; ram[0xcfU+slot] = ys[v / 3U];
    ram[0x46U+slot] = 0x41U; ram[0x58U+slot] = 0x53U;
    ram[0xa0U+slot] = 0x67U; ram[0x434U+slot] = 0x39U;
    ram[0x401U+slot] = 0x29U; ram[0x417U+slot] = 0x63U;
    ram[0x3a2U+slot] = 0x45U;
}

static int mysmb_platform_init_argument(const char *text)
{
    static const char prefix[] = "--fixture=t39-platform-init=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U; digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 240U) return 0;
    return (int)value + 1;
}
#endif
