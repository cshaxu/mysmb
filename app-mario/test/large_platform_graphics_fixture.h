#ifndef MYSMB_LARGE_PLATFORM_GRAPHICS_FIXTURE_H
#define MYSMB_LARGE_PLATFORM_GRAPHICS_FIXTURE_H

#include "special_actor_fixture.h"

/* Controlled RAM preconditions for the original RunLargePlatform caller.
 * They are recorder inputs only; each starts from special-actor case 36,
 * which is large-platform ID $24 in slot zero. */
static void mysmb_large_platform_graphics_fixture(unsigned char *ram,
                                                   unsigned int n)
{
    mysmb_special_actor_fixture(ram, 36U);
    if (n == 0U) ram[0x74eU] = 3U;       /* castle tail suppression */
    if (n == 1U) ram[0x6ccU] = 1U;       /* secondary-hard suppression */
    if (n == 2U) ram[0x743U] = 1U;       /* cloud tile override */
    if (n == 3U) { ram[0x00b6U] = 0U; ram[0x00cfU] = 0U; }
    /* GetXOffscreenBits raw masks $80, $c0, $e0, $f0, $f8 and $fc.
     * The fixture's source screen edges are pages $01/$02 at X $20/$1f. */
    if (n == 4U) ram[0x0087U] = 0x19U;
    if (n == 5U) ram[0x0087U] = 0x11U;
    if (n == 6U) ram[0x0087U] = 0x09U;
    if (n == 7U) ram[0x0087U] = 0x01U;
    if (n == 8U) ram[0x0087U] = 0x00U;
    if (n == 9U) { ram[0x006eU] = 0U; ram[0x0087U] = 0xf1U; }
}

static int mysmb_large_platform_graphics_argument(const char *text)
{
    static const char prefix[] = "--fixture=t44-large-platform=";
    unsigned int i, value, digits;

    for (i = 0U; prefix[i] != '\0'; ++i) if (text[i] != prefix[i]) return 0;
    value = 0U;
    digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 2U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (!digits || text[i] != '\0' || value >= 10U) return 0;
    return (int)value + 1;
}

#endif
