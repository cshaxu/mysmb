#ifndef MYSMB_ENGINE_SLOTS_FIXTURE_H
#define MYSMB_ENGINE_SLOTS_FIXTURE_H

#include "game_entry_fixture.h"

static void mysmb_engine_slots_fixture(unsigned char *ram, unsigned char scenario)
{
    unsigned int slot;
    mysmb_game_entry_fixture(ram, 2U);
    ram[0x71fU] = 7U;
    for (slot = 0U; slot < 6U; ++slot) {
        ram[0x110U+slot] = scenario != 0U ? (unsigned char)(slot+1U) : 0U;
        ram[0x12cU+slot] = 0x20U;
        ram[0x117U+slot] = (unsigned char)(0x30U+slot*16U);
        ram[0x11eU+slot] = 0x80U;
        ram[0x1eU+slot] = 2U;
    }
}

static int mysmb_engine_slots_argument(const char *text)
{
    static const char prefix[] = "--fixture=t31-engine-slots=";
    unsigned int i;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '1' || text[i+1U] != '\0') return 0;
    return (int)(text[i] - '0') + 1;
}
#endif
