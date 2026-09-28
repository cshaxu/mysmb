#ifndef MYSMB_FLYING_CHEEP_MOVEMENT_FIXTURE_H
#define MYSMB_FLYING_CHEEP_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_flying_cheep_movement_slot(unsigned int n)
{ return (unsigned char)((n & 1U) * 5U); }
static void mysmb_flying_cheep_movement_fixture(unsigned char *ram, unsigned int n)
{
    unsigned int i;
    unsigned char slot;
    slot = mysmb_flying_cheep_movement_slot(n);
    mysmb_actor_dispatch_fixture(ram, 40U + (n & 1U));
    for (i = 0U; i < 6U; ++i) ram[0xfU + i] = 0U;
    ram[0xfU + slot] = 1U; ram[0x16U + slot] = 20U;
    ram[0x1eU + slot] = (unsigned char)(n >= 480U ? 0x20U : 0U);
    ram[0x6eU + slot] = 1U; ram[0x87U + slot] = (unsigned char)(n & 2U ? 0xffU : 0U);
    ram[0xb6U + slot] = 1U; ram[0xcfU + slot] = (unsigned char)((n / 32U) * 16U);
    ram[0x434U + slot] = (unsigned char)((n % 16U) * 16U + (n & 16U ? 15U : 0U));
    ram[0x417U + slot] = (unsigned char)(n & 4U ? 0xffU : 0U);
    ram[0xa0U + slot] = (unsigned char)(n & 8U ? 0xffU : 0U);
    ram[0x58U + slot] = (unsigned char)(n & 16U ? 0xf7U : 0x19U);
    ram[0x401U + slot] = (unsigned char)(n & 4U ? 0xffU : 0U);
    ram[0x3c5U + slot] = 0xc3U;
    ram[0x747U] = 0U;
    /* A near-top trajectory covers force $F0 plus $10 wrapping to zero
     * after the real gravity child has advanced its fractional state. */
    if (n == 15U) {
        ram[0x434U + slot] = 0xe3U;
        ram[0xcfU + slot] = 8U;
    }
}
static int mysmb_flying_cheep_movement_argument(const char *text)
{
    static const char prefix[] = "--fixture=t40-flying-cheep-movement=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    if (!digits || text[i] != '\0' || value >= 512U) return 0;
    return (int)value + 1;
}
#endif
