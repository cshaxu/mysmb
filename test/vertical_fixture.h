#ifndef MYSMB_VERTICAL_FIXTURE_H
#define MYSMB_VERTICAL_FIXTURE_H
#include "entrance_fixture.h"

/* Controlled source RAM at an ordinary NMI; CPU and stack stay untouched. */
static void mysmb_vertical_fixture(unsigned char *ram, unsigned char n)
{
    unsigned char kind, k;
    kind = (unsigned char)(n / 4U);
    k = (unsigned char)(n % 4U);
    mysmb_entrance_fixture(ram, 0U);
    ram[0xeU] = 8U; ram[0x747U] = 0U;
    ram[0xceU] = 0x80U; ram[0x1dU] = 1U;
    ram[0x70eU] = 0U;
    if (kind == 0U) {
        ram[0x747U] = (k & 1U) ? 0xffU : 0U;
        ram[0x70eU] = (k & 2U) ? 1U : 0U;
        return;
    }
    ram[0xfU] = 1U; ram[0x16U] = 6U; ram[0x1eU] = 0x40U;
    ram[0x6eU] = 7U; ram[0x87U] = 0x80U;
    ram[0xb6U] = 1U; ram[0xcfU] = 0x80U;
    ram[0xa0U] = (k & 1U) ? 0xffU : 1U;
    ram[0x434U] = (k & 2U) ? 0xffU : 0U;
    ram[0x417U] = (k & 2U) ? 0xffU : 0U;
    if (kind == 1U) ram[0x1eU] = (k & 1U) ? 5U : 0x40U;
    if (kind == 2U) {
        ram[0x16U] = 0x24U; ram[0x1eU] = 1U;
        ram[0x46U] = 1U; ram[0x3a2U] = 0xffU;
        ram[0xd0U] = 0x80U;
    }
    if (kind == 3U || kind == 4U) {
        ram[0x16U] = 0x0fU; ram[0x1eU] = 0U;
        ram[0x58U] = kind == 3U ? 0x90U : 0x70U;
    }
    if (kind == 5U) {
        ram[0x16U] = 0x29U; ram[0x1eU] = 0U;
        ram[0x86U] = 0x80U; ram[0xceU] = 0x60U;
        ram[0x49aU] = 6U;
        ram[0x9fU] = 1U; ram[0x3a2U] = 0U;
    }
    if (kind == 6U) { ram[0x16U] = 7U; ram[0x1eU] = 0x20U; }
    if (kind == 7U) { ram[0x16U] = 0x0eU; ram[0x1eU] = 0x20U; }
}

static int mysmb_vertical_argument(const char *text)
{
    static const char prefix[] = "--fixture=t37-vertical=";
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
