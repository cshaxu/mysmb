#ifndef MYSMB_HOLE_UNDERPART_FIXTURE_H
#define MYSMB_HOLE_UNDERPART_FIXTURE_H

/* Cases 0..95: four AreaTypes x six shared slots x initial/continuing x
 * two immutable hole records ($a30c column zero, $ae18 column twelve).
 * Case 96: ordinary staircase lookup at $a57f selects adjacent-ROM index 21,
 * supplying row seven/height $90 to exercise UnderPart's signed exit.
 * Case 97: mushroom-center record at $a473 exercises the rock/stem guard. */
static void mysmb_hole_underpart_fixture(unsigned char *ram, unsigned char scenario)
{
    unsigned char shape, continuation, slot, i;
    shape = (unsigned char)(scenario % 2U);
    continuation = (unsigned char)((scenario / 2U) % 2U);
    slot = (unsigned char)((scenario / 4U) % 6U);
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 3U;
    ram[0x00eU] = 8U;
    ram[0x773U] = 0U;
    ram[0x71fU] = 8U;
    ram[0x725U] = 1U;
    ram[0x726U] = shape == 0U ? 0U : 12U;
    ram[0x728U] = 0U;
    ram[0x72aU] = continuation || shape ? 1U : 0U;
    ram[0x72bU] = 0U;
    ram[0x72cU] = continuation ? 2U : 0U;
    ram[0x72dU] = 0U;
    ram[0x72eU] = 0U;
    ram[0x72fU] = 0U;
    ram[0x730U] = 0xffU;
    ram[0x731U] = 0xffU;
    ram[0x732U] = continuation ? 1U : 0xffU;
    ram[0x73fU] = 0U;
    ram[0x0e7U] = shape == 0U ? 0x0cU : 0x18U;
    ram[0x0e8U] = shape == 0U ? 0xa3U : 0xaeU;
    ram[0x74eU] = (unsigned char)(scenario / 24U);
    ram[0x46aU] = slot;
    for (i = 0U; i < 18U; ++i) ram[0x46bU + i] = 0xa5U;
    if (scenario == 96U) {
        ram[0x726U] = 0U;
        ram[0x72aU] = 1U;
        ram[0x72cU] = 2U;
        ram[0x732U] = 0U;
        ram[0x734U] = 22U;
        ram[0x0e7U] = 0x7fU;
        ram[0x0e8U] = 0xa5U;
        ram[0x74eU] = 1U;
    }
    if (scenario == 97U) {
        ram[0x726U] = 6U;
        ram[0x72aU] = 1U;
        ram[0x72cU] = 2U;
        ram[0x732U] = 2U;
        ram[0x733U] = 1U;
        ram[0x738U] = 2U;
        ram[0x0e7U] = 0x73U;
        ram[0x0e8U] = 0xa4U;
        ram[0x74eU] = 1U;
    }
}

static int mysmb_hole_underpart_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-hole=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 97U) return 0;
    return (int)value + 1;
}
#endif
