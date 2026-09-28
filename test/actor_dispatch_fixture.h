#ifndef MYSMB_ACTOR_DISPATCH_FIXTURE_H
#define MYSMB_ACTOR_DISPATCH_FIXTURE_H
#include "enemy_init_fixture.h"

static unsigned char mysmb_actor_dispatch_slot(unsigned int n)
{
    return (unsigned char)(n < 108U ? (n % 2U) * 5U : (n - 108U) / 12U);
}

static void mysmb_actor_dispatch_fixture(unsigned char *ram, unsigned int n)
{
    unsigned char i, slot, id;
    unsigned int v;
    mysmb_enemy_init_fixture(ram, 26U);
    slot = mysmb_actor_dispatch_slot(n);
    id = n < 108U ? (unsigned char)(n / 2U) : 53U;
    for (i = 0U; i < 6U; ++i) ram[0xfU+i] = (unsigned char)(0x80U+i);
    ram[0xfU+slot] = 1U; ram[0x16U+slot] = id; ram[0x1eU+slot] = 0U;
    ram[0x6cdU] = 0U; ram[0x6cbU] = 0U;
    ram[0x6eU+slot] = 1U; ram[0x87U+slot] = 0x70U;
    ram[0xcfU+slot] = 0x80U; ram[0xb6U+slot] = 1U;
    ram[0x71aU] = 1U; ram[0x71cU] = 0x20U;
    ram[0x71bU] = 2U; ram[0x71dU] = 0x1fU;
    ram[0x6e5U+slot] = 0x40U; ram[0x3c5U+slot] = 0x20U;
    ram[0x723U] = 0U; ram[0x6cfU] = (unsigned char)(slot == 0U ? 1U : 0U);
    ram[0x368U] = slot; ram[0x483U] = 5U;
    if (n >= 108U) {
        v = (n-108U) % 12U;
        ram[0x75fU] = (unsigned char)(v % 2U ? 7U : 0U);
        ram[0x87U+slot] = (unsigned char)(v / 2U == 0U ? 0x18U :
            (v / 2U == 1U ? 0x20U : (v / 2U == 2U ? 0xffU : 0x70U)));
        ram[0xcfU+slot] = (unsigned char)(v / 2U == 3U ? 0U :
            (v / 2U == 4U ? 0xf0U : 0xb8U));
        ram[0xb6U+slot] = (unsigned char)(v / 2U == 5U ? 2U : 1U);
    }
}

/* Original vector child IDs; NoRunCode and proved WarpZoneObject are local. */
static unsigned int mysmb_actor_dispatch_target(unsigned int pc)
{
    static const unsigned short targets[13] = {
        0xc8e0U,0xc935U,0xd295U,0xc947U,0xc965U,0xc94dU,
        0xd065U,0xbc85U,0xb94bU,0xd2d9U,0xb8baU,0xc8d7U,0xb7a4U
    };
    unsigned int i;
    for (i=0U;i<12U;++i) if (pc==targets[i]) return i+1U;
    return 0U;
}

static int mysmb_actor_dispatch_argument(const char *text)
{
    static const char prefix[] = "--fixture=t39-actor-dispatch=";
    unsigned int i, value, digits;
    for (i=0U;prefix[i]!='\0';++i) if (text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while (text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if (!digits || text[i]!='\0' || value>=180U) return 0;
    return (int)value+1;
}
#endif
