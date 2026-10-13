#ifndef MYSMB_STAIRCASE_FIXTURE_H
#define MYSMB_STAIRCASE_FIXTURE_H

/* The immutable row-15 staircase record is at $a57f. Cases 0..8 select
 * continuation indices, 9 starts a new object, 10/11 exercise original
 * adjacent-ROM reads after control 10/0. Only source RAM is changed. */
static void mysmb_staircase_fixture(unsigned char *ram, unsigned char scenario)
{
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 3U;
    ram[0x00eU] = 8U;
    ram[0x773U] = 0U;
    ram[0x71fU] = 8U;
    ram[0x725U] = 1U;
    ram[0x726U] = 0U;
    ram[0x728U] = 0U;
    ram[0x72aU] = 1U;
    ram[0x72bU] = 0U;
    ram[0x72cU] = scenario == 9U ? 0U : 2U;
    ram[0x72dU] = 0U;
    ram[0x72eU] = 0U;
    ram[0x72fU] = 0U;
    ram[0x730U] = 0xffU;
    ram[0x731U] = 0xffU;
    ram[0x732U] = scenario == 9U ? 0xffU :
        (scenario < 9U ? scenario : 0U);
    ram[0x734U] = scenario == 9U ? 0xa5U :
        (scenario == 10U ? 10U : (scenario == 11U ? 0U : scenario + 1U));
    ram[0x73fU] = 0U;
    ram[0x0e7U] = 0x7fU;
    ram[0x0e8U] = 0xa5U;
    ram[0x74eU] = 1U;
}

static int mysmb_staircase_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-stair=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 11U) return 0;
    return (int)value + 1;
}
#endif
