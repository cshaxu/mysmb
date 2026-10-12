#ifndef MYSMB_ITEM_BLOCK_FIXTURE_H
#define MYSMB_ITEM_BLOCK_FIXTURE_H

/* Nine immutable small-object records, four AreaTypes and hidden clear/set.
 * GameEngine/ProcessAreaData source-RAM fixtures only; no PC/stack edits. */
static void mysmb_item_block_fixture(unsigned char *ram, unsigned char scenario)
{
    static const unsigned char low[9] = { 0x9fU, 0x1cU, 0xedU, 0x59U, 0xe4U, 0xbaU, 0xdeU, 0x1eU, 0x1fU };
    static const unsigned char high[9] = { 0xa2U, 0xa3U, 0xa1U, 0xa5U, 0xa4U, 0xa5U, 0xa5U, 0xa5U, 0xabU };
    static const unsigned char columns[9] = { 0x07U, 0x0aU, 0x0aU, 0x0cU, 0x02U, 0x01U, 0x0cU, 0x0eU, 0x0cU };
    static const unsigned char carry[9] = { 0x00U, 0x00U, 0x00U, 0x00U, 0x01U, 0x00U, 0x00U, 0x01U, 0x00U };
    unsigned char selector;
    selector = (unsigned char)(scenario / 8U);
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 3U;
    ram[0x00eU] = 8U;
    ram[0x773U] = 0U;
    ram[0x71fU] = 8U;
    ram[0x725U] = 1U;
    ram[0x726U] = columns[selector];
    ram[0x728U] = 0U;
    ram[0x72aU] = (unsigned char)(1U - carry[selector]);
    ram[0x72bU] = 0U;
    ram[0x72cU] = 0U;
    ram[0x72dU] = 0U;
    ram[0x72eU] = 0U;
    ram[0x72fU] = 0U;
    ram[0x730U] = 0xffU;
    ram[0x731U] = 0xffU;
    ram[0x732U] = 0xffU;
    ram[0x73fU] = 0U;
    ram[0x0e7U] = low[selector];
    ram[0x0e8U] = high[selector];
    ram[0x74eU] = (unsigned char)((scenario / 2U) % 4U);
    ram[0x75dU] = (unsigned char)(scenario % 2U);
    ram[0x6bcU] = 0xa5U;
}

static int mysmb_item_block_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-items=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 71U) return 0;
    return (int)value + 1;
}
#endif
