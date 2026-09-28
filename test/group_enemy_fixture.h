#ifndef MYSMB_GROUP_ENEMY_FIXTURE_H
#define MYSMB_GROUP_ENEMY_FIXTURE_H
#include "enemy_stream_fixture.h"

/* Six actual group record IDs in the original level data; never patch PRG. */
static void mysmb_group_enemy_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned short records[6] = {
        0x9f16U,0x9f88U,0xa0ebU,0xa10aU,0xa0e1U,0xa010U
    };
    static const unsigned char masks[8] = {0U,1U,5U,15U,23U,27U,30U,31U};
    unsigned int kind, variant, mask, i;
    unsigned short address;
    mysmb_enemy_stream_fixture(ram, 40U);
    kind = n < 96U ? n / 16U : 0U;
    variant = n < 96U ? n % 16U : n - 96U;
    mask = n < 96U ? masks[variant / 2U] : variant;
    for (i = 0U; i < 5U; ++i)
        ram[0x0fU + i] = (mask & (1U << i)) ? (unsigned char)(0x80U + i) : 0U;
    ram[0x14U] = 0U;
    ram[0x76aU] = (unsigned char)(variant & 1U);
    ram[0x73aU] = (variant & 2U) ? 255U : 4U;
    ram[0x71bU] = ram[0x73aU];
    /* On page $FF the parser's +$30 lookahead must not wrap first.
     * Three-member groups can still wrap their final +$18 scratch step. */
    ram[0x71dU] = (unsigned char)(kind == 3U ?
        ((variant & 2U) ? 0xbcU : 0xe0U) :
        ((variant & 2U) ? 0xccU : 0xf0U));
    ram[0x739U] = (variant & 8U) ? 0xfeU : 0U;
    ram[0x73bU] = 1U;
    address = (unsigned short)(records[kind] - ram[0x739U]);
    ram[0xe9U] = (unsigned char)address;
    ram[0xeaU] = (unsigned char)(address >> 8U);
    for (i = 0U; i < 6U; ++i) {
        ram[0x1eU + i] = 0x39U;
        ram[0xa0U + i] = 0x45U;
        ram[0x434U + i] = 0x67U;
    }
}

static int mysmb_group_enemy_argument(const char *text)
{
    static const char prefix[] = "--fixture=t39-group=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U; digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 128U) return 0;
    return (int)value + 1;
}
#endif
