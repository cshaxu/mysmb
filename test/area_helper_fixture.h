#ifndef MYSMB_AREA_HELPER_FIXTURE_H
#define MYSMB_AREA_HELPER_FIXTURE_H

/* Ordinary ScreenRoutines parser entries over immutable records. Cases 0..3
 * exercise hole length gates; 4..7 cannon coordinates; 8..15 jumpspring
 * allocation consumers; 16..19 fixed-length vertical pipe columns. */
static void mysmb_area_helper_fixture(unsigned char *ram, unsigned char scenario)
{
    unsigned char i;
    if (scenario < 4U) {
        mysmb_hole_underpart_fixture(ram,
            (unsigned char)((scenario / 2U) * 24U + (scenario % 2U) * 2U));
    } else if (scenario < 8U) {
        mysmb_cannon_fixture(ram, (unsigned char)((scenario - 4U) * 6U));
    } else {
        mysmb_jumpspring_fixture(ram, scenario < 16U ?
            (unsigned char)(scenario - 8U) : 0U);
    }
    ram[0x772U] = 1U;
    ram[0x73cU] = 8U;
    ram[0x71eU] = 0U;
    if (scenario < 16U) return;
    /* L_GroundArea6 + $0e: immutable $68,$f2 pipe, row eight. */
    ram[0xe7U] = 0x8eU;
    ram[0xe8U] = 0xa6U;
    ram[0x725U] = 1U;
    ram[0x726U] = 6U;
    ram[0x72aU] = 0U;
    ram[0x72bU] = 0U;
    ram[0x72cU] = 14U;
    ram[0x760U] = 1U;
    for (i = 0U; i < 6U; ++i) ram[0x0fU+i] = 0U;
    if (scenario == 17U || scenario == 18U) {
        ram[0x732U] = scenario == 17U ? 1U : 0U;
        ram[0x72fU] = 14U;
        ram[0x72cU] = 16U;
        ram[0x72aU] = 1U;
    }
    if (scenario == 19U)
        for (i = 0U; i < 5U; ++i) ram[0x0fU+i] = 1U;
}

static int mysmb_area_helper_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-helper=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 19U) return 0;
    return (int)value + 1;
}
#endif
