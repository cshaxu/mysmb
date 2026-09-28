#ifndef MYSMB_ENEMY_INIT_FIXTURE_H
#define MYSMB_ENEMY_INIT_FIXTURE_H
#include "entrance_fixture.h"

static unsigned char mysmb_enemy_init_slot(unsigned int n)
{
    return n < 2U ? 0U : (unsigned char)((n & 1U) ? 5U : 0U);
}

/* Controlled NMI RAM inputs. The original loop consumes EnemyFrenzyQueue;
 * ID zero instead uses an ordinary unchanged ROM enemy record. */
static void mysmb_enemy_init_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char common_ids[13] = {
        1U,3U,5U,6U,7U,8U,10U,11U,12U,15U,16U,17U,53U
    };
    unsigned char id, slot, i;
    mysmb_entrance_fixture(ram, 0U);
    id = n < 110U ? (unsigned char)(n / 2U) : common_ids[(n - 110U) / 4U];
    slot = mysmb_enemy_init_slot(n);
    ram[0x0eU] = 12U;
    ram[0x747U] = 0xffU;
    ram[0x71fU] = 0U;
    for (i = 0U; i < 6U; ++i) ram[0x0fU + i] = (unsigned char)(0x80U + i);
    ram[0x0fU + slot] = 0U;
    ram[0x745U] = 0U;
    ram[0x6cbU] = 0U;
    ram[0x6cdU] = id;
    ram[0x398U] = 0U;
    ram[0x3a0U] = 0xffU;
    ram[0x6eU + slot] = 4U;
    ram[0x87U + slot] = 0xfeU;
    ram[0xb6U + slot] = 1U;
    ram[0xcfU + slot] = (n & 1U) ? 0xfcU : 0x70U;
    ram[0x73aU] = 4U;
    ram[0x73bU] = 1U;
    ram[0x71bU] = 4U;
    ram[0x71dU] = 0xa0U;
    ram[0x6ccU] = (unsigned char)(n & 1U);
    ram[0x76aU] = (unsigned char)(n & 1U);
    ram[0x739U] = 0U;
    ram[0xe9U] = 0xacU;
    ram[0xeaU] = 0x9eU;
    if (id == 0x16U) {
        /* Fireworks require the original star-flag partner for their scan. */
        ram[0x17U] = 0x31U;
        ram[0x1fU] = 0U;
        ram[0x88U] = 0x70U;
        ram[0x6fU] = 4U;
        ram[0x6d7U] = 1U;
    }
    if (n >= 110U) {
        /* Added S4 cases retain original control flow while selecting both
         * Y signs, PRNG bit values and occupied/free frenzy at entry. */
        ram[0xcfU + slot] = ((n - 110U) & 2U) ? 0x78U : 0x70U;
        ram[0x401U + slot] = 0x39U;
        ram[0x417U + slot] = 0x67U;
        ram[0x110U + slot] = 0x25U;
        ram[0x125U + slot] = 0x35U;
        if (id == 17U) ram[0x6cbU] = ((n - 110U) & 2U) ? 0x11U : 0U;
        for (i = 0U; i < 8U; ++i)
            ram[0x7a7U + i] = ((n - 110U) & 2U) ? 0x20U : 0U;
    }
}

/* Neutral target addresses audited against all 110 original vector bytes.
 * Observation only: neither this table nor the fixture changes the CPU PC. */
static unsigned int mysmb_enemy_init_target(unsigned int pc, unsigned char id)
{
    static const unsigned short targets[55] = {
        0xc30eU,0xc30eU,0xc30eU,0xc31eU,0xc2f0U,0xc328U,0xc2f1U,0xc342U,
        0xc36bU,0xc2f0U,0xc375U,0xc375U,0xc2f7U,0xc787U,0xc7d1U,0xc34aU,
        0xc33dU,0xc385U,0xc7a0U,0xc2f0U,0xc7a0U,0xc7a0U,0xc7a0U,0xc7a0U,
        0xc7b8U,0xc2f0U,0xc2f0U,0xc45cU,0xc45cU,0xc45cU,0xc45cU,0xc459U,
        0xc2f0U,0xc2f0U,0xc2f0U,0xc2f0U,0xc7dfU,0xc812U,0xc83fU,0xc845U,
        0xc80bU,0xc803U,0xc80bU,0xc84bU,0xc857U,0xc549U,0xbc60U,0xb91eU,
        0xc2f0U,0xc2f0U,0xc2f0U,0xc2f0U,0xc2f0U,0xc307U,0xc881U
    };
    return id < 55U && pc == targets[id] ? (unsigned int)id + 1U : 0U;
}

static int mysmb_enemy_init_argument(const char *text)
{
    static const char prefix[] = "--fixture=t38-init=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U;
    digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 3U) {
        value = value * 10U + (unsigned int)(text[i++] - '0');
        ++digits;
    }
    if (digits == 0U || text[i] != '\0' || value >= 162U) return 0;
    return (int)value + 1;
}
#endif
