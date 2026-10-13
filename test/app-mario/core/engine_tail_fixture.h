#ifndef MYSMB_ENGINE_TAIL_FIXTURE_H
#define MYSMB_ENGINE_TAIL_FIXTURE_H

#include "game_entry_fixture.h"

/* Enter the real GameCore/PlayerDeath return through NMI, then exercise
 * engine-tail state. These are RAM inputs, never injected leaf calls. */
static void mysmb_engine_tail_fixture(unsigned char *ram, unsigned char scenario)
{
    mysmb_game_entry_fixture(ram, 2U);
    ram[0xb5U] = 1U;
    ram[0x3c4U] = 0xa7U;
    ram[0x79fU] = 0U;
    ram[0x77fU] = 0U;
    ram[9U] = 31U;
    ram[0xaU] = 0xc0U;
    ram[0xcU] = 3U;
    ram[0x74eU] = 1U;
    ram[0x71fU] = 0U;
    ram[0x73dU] = 0U;
    ram[0x340U] = 0x12U;
    if (scenario == 1U || scenario == 2U || scenario == 7U || scenario == 14U)
        ram[0x79fU] = 4U;
    if (scenario == 2U) ram[0x77fU] = 1U;
    if (scenario == 3U) ram[0x79fU] = 7U;
    if (scenario == 4U) ram[0x79fU] = 8U;
    if (scenario == 5U) ram[0xb5U] = 2U;
    if (scenario == 6U || scenario == 7U) ram[0xb5U] = 130U;
    if (scenario == 8U) ram[0x73dU] = 31U;
    if (scenario == 9U) ram[0x73dU] = 32U;
    if (scenario == 10U) ram[0x73dU] = 159U;
    if (scenario == 11U) ram[0x73dU] = 160U;
    if (scenario == 12U) ram[0x73dU] = 255U;
    if (scenario == 13U) ram[0x71fU] = 1U;
    if (scenario == 14U) ram[9U] = 0U;
}

static int mysmb_engine_tail_argument(const char *text)
{
    static const char prefix[] = "--fixture=t31-engine-tail=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 14U) return 0;
    return (int)value + 1;
}
#endif
