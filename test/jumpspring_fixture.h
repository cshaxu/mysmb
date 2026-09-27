#ifndef MYSMB_JUMPSPRING_FIXTURE_H
#define MYSMB_JUMPSPRING_FIXTURE_H

/* ScreenRoutines/AreaParserTaskControl builds the immutable 7-1 record at
 * $abc8 before actor execution. Cases 0..4 select a free
 * ordinary slot; 5..7 fill the ordinary pool and set slot five to 0/1/255. */
static void mysmb_jumpspring_fixture(unsigned char *ram, unsigned char scenario)
{
    unsigned char i, slot;
    slot = scenario < 5U ? scenario : 5U;
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 1U;
    ram[0x73cU] = 8U;
    ram[0x71eU] = 0U;
    ram[0x00eU] = 8U;
    ram[0x773U] = 0U;
    ram[0x71fU] = 8U;
    ram[0x725U] = 1U;
    ram[0x726U] = 7U;
    ram[0x728U] = 0U;
    ram[0x72aU] = 1U;
    ram[0x72bU] = 0U;
    ram[0x72cU] = 0U;
    ram[0x72dU] = 0U;
    ram[0x72eU] = 0U;
    ram[0x72fU] = 0U;
    ram[0x730U] = 0xffU;
    ram[0x731U] = 0xffU;
    ram[0x732U] = 0xffU;
    ram[0x73fU] = 0U;
    ram[0x0e7U] = 0xc8U;
    ram[0x0e8U] = 0xabU;
    ram[0x74eU] = 1U;
    for (i = 0U; i < 6U; ++i) {
        ram[0x0fU + i] = i < slot ? 1U : 0U;
        ram[0x16U + i] = 0x32U;
        ram[0x6eU + i] = 1U;
        ram[0x87U + i] = 0xe0U;
        ram[0xcfU + i] = 0xa0U;
        ram[0x58U + i] = 0xa0U;
        ram[0xb6U + i] = 1U;
    }
    if (scenario == 6U) ram[0x14U] = 1U;
    if (scenario == 7U) ram[0x14U] = 0xffU;
}

static int mysmb_jumpspring_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-spring=";
    unsigned int i;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '7' || text[i+1U] != '\0') return 0;
    return text[i] - '0' + 1;
}
#endif
