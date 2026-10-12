#ifndef MYSMB_GRAVITY_FIXTURE_H
#define MYSMB_GRAVITY_FIXTURE_H
#include "entrance_fixture.h"

/* Frame-boundary source RAM only; every entry is reached by ordinary NMI. */
static void mysmb_gravity_fixture(unsigned char *ram, unsigned char n)
{
    static const unsigned char speeds[8] = {
        0U, 3U, 8U, 0x7fU, 0x80U, 0xfcU, 0xffU, 0xffU
    };
    unsigned char kind, k, offset;
    kind = (unsigned char)(n / 8U); k = (unsigned char)(n % 8U);
    mysmb_entrance_fixture(ram, 0U);
    ram[0xeU] = 8U; ram[0x747U] = 0U;
    ram[0xceU] = 0x80U; ram[0x1dU] = 1U; ram[0x70eU] = 0U;
    offset = kind == 0U ? 9U : 1U;
    if (kind == 0U) {
        ram[0x26U] = 2U; ram[0x76U] = 7U; ram[0x8fU] = 0x80U;
        ram[0x3edU] = 0U;
    } else {
        ram[0xfU] = 1U; ram[0x1eU] = 0U;
        ram[0x16U] = kind == 3U ? 0x0fU : 0x25U;
        ram[0x6eU] = 7U; ram[0x87U] = 0x80U;
        ram[0x58U] = kind == 1U ? 0xf0U : 0U;
        ram[0x401U] = 0U; ram[0x49aU] = 6U;
    }
    ram[0x9fU + offset] = speeds[k];
    ram[0xb5U + offset] = (k & 1U) ? 0xffU : 1U;
    /* Actor visibility must hold until the original gravity entry. */
    if (kind != 0U) ram[0xb5U + offset] = 1U;
    ram[0xceU + offset] = (k & 1U) ? 0x80U : 0U;
    if (kind != 0U) ram[0xceU + offset] = 0x80U;
    ram[0x416U + offset] = (k & 1U) ? 0xffU : 0U;
    ram[0x433U + offset] = (k & 2U) ? 0xffU : 0x7fU;
}

static int mysmb_gravity_argument(const char *text)
{
    static const char prefix[] = "--fixture=t37-gravity=";
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
