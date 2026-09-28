#ifndef MYSMB_BLOCK_ADDRESS_FIXTURE_H
#define MYSMB_BLOCK_ADDRESS_FIXTURE_H
#include "pipe_tail_fixture.h"

/* Existing original parser route, with each physical block-buffer column.
 * Only source RAM changes; immutable pipe data gives nonempty column writes. */
static void mysmb_block_address_fixture(unsigned char *ram, unsigned char column)
{
    unsigned char page, alternate;
    if (column >= 32U) {
        page = (unsigned char)((column - 32U) % 8U);
        alternate = (unsigned char)((column - 32U) / 8U);
        ram[0x722U] = 0U;
        ram[0x770U] = 1U;
        ram[0x772U] = 0U;
        ram[0x75bU] = alternate != 0U ? (unsigned char)((page + 3U) % 8U) : page;
        ram[0x751U] = page;
        ram[0x752U] = alternate;
        return;
    }
    mysmb_pipe_tail_fixture(ram, 7U);
    ram[0x6a0U] = column;
}

static int mysmb_block_address_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-block-address=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 47U) return 0;
    return (int)value + 1;
}
#endif
