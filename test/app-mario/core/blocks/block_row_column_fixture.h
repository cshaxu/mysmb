#ifndef MYSMB_BLOCK_ROW_COLUMN_FIXTURE_H
#define MYSMB_BLOCK_ROW_COLUMN_FIXTURE_H

/* Immutable ROM records at $a2f1, $a1b1, $a35e, $a22a; ordinary
 * GameEngine/ProcessAreaData entry after a source-RAM-only NMI fixture.
 * Four object kinds x four area types x cloud clear/set. */
static void mysmb_block_row_column_fixture(unsigned char *ram,
                                           unsigned char scenario)
{
    static const unsigned char low[4] = {0xefU, 0xafU, 0x5cU, 0x28U};
    static const unsigned char high[4] = {0xa2U, 0xa1U, 0xa3U, 0xa2U};
    static const unsigned char column[4] = {0U, 0U, 4U, 9U};
    unsigned char kind;
    kind = (unsigned char)(scenario / 8U);
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 3U;
    ram[0x00eU] = 8U;
    ram[0x773U] = 0U;
    ram[0x71fU] = 8U;
    ram[0x725U] = 1U;
    ram[0x726U] = column[kind];
    ram[0x728U] = 0U;
    ram[0x72aU] = kind == 0U ? 0U : 1U;
    ram[0x72bU] = 0U;
    ram[0x72cU] = 2U;
    ram[0x72dU] = 0U;
    ram[0x72eU] = 0U;
    ram[0x72fU] = 0U;
    ram[0x730U] = 0xffU;
    ram[0x731U] = 0xffU;
    ram[0x732U] = 0xffU;
    ram[0x73fU] = 0U;
    ram[0x0e7U] = low[kind];
    ram[0x0e8U] = high[kind];
    ram[0x74eU] = (unsigned char)((scenario / 2U) % 4U);
    ram[0x743U] = (unsigned char)(scenario % 2U);
}

/* Zero means another argument; 1..32 identify the admitted cases. */
static int mysmb_block_row_column_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-blocks=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 31U) return 0;
    return (int)value + 1;
}
#endif
