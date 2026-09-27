#ifndef MYSMB_CANNON_FIXTURE_H
#define MYSMB_CANNON_FIXTURE_H

/* Source RAM selects immutable area records in the owner's 7-1 stream at
 * $ab7e: $ab8c (height 0), $ab84 (height 1), $ab92 (height 2).
 * Two extra 3-3 records at $a473/$a48f select height 5 and bottom overflow
 * using source RAM AreaStyle=2. Five shapes x six cannon slots.
 * No program/PC/stack modification. */
static void mysmb_cannon_fixture(unsigned char *ram, unsigned char scenario)
{
    static const unsigned char offsets[5] = {14U, 6U, 20U, 8U, 36U};
    static const unsigned char columns[5] = {12U, 3U, 14U, 6U, 1U};
    unsigned char height;
    height = (unsigned char)(scenario / 6U);
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 3U;
    ram[0x00eU] = 8U;
    ram[0x773U] = 0U;
    ram[0x71fU] = 8U;
    ram[0x725U] = 1U;
    ram[0x726U] = columns[height];
    ram[0x728U] = 0U;
    ram[0x72aU] = height == 1U ? 0U : 1U;
    ram[0x72bU] = 0U;
    ram[0x72cU] = offsets[height];
    ram[0x72dU] = 0U;
    ram[0x72eU] = 0U;
    ram[0x72fU] = 0U;
    ram[0x730U] = 0xffU;
    ram[0x731U] = 0xffU;
    ram[0x732U] = 0xffU;
    ram[0x733U] = 2U;
    ram[0x73fU] = 0U;
    ram[0x0e7U] = height < 3U ? 0x7eU : 0x6bU;
    ram[0x0e8U] = height < 3U ? 0xabU : 0xa4U;
    ram[0x74eU] = 1U;
    ram[0x46aU] = (unsigned char)(scenario % 6U);
}

static int mysmb_cannon_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-cannon=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 29U) return 0;
    return (int)value + 1;
}
#endif
