#ifndef MYSMB_GAME_ENTRY_FIXTURE_H
#define MYSMB_GAME_ENTRY_FIXTURE_H

/* Source RAM only at the ordinary NMI boundary. Cases 0/1 return from
 * PlayerLoseLife; cases 2/3 keep PlayerDeath inert while selecting either
 * controller. No ROM, program counter, stack or output is patched. */
static void mysmb_game_entry_fixture(unsigned char *ram, unsigned char scenario)
{
    ram[0x722U] = 0U;
    ram[0x774U] = 0U;
    ram[0x77aU] = 0U;
    ram[0x753U] = 0U;
    ram[0x75aU] = scenario == 1U ? 0U : 2U;
    ram[0x75bU] = 0U;
    ram[0x75cU] = 0U;
    ram[0x75fU] = 0U;
    ram[0x761U] = 0xffU;
    ram[0x71aU] = 7U;
    ram[0x6fcU] = 0U;
    ram[0x7a0U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 3U;
    ram[0x00eU] = 6U;
    if (scenario >= 2U) {
        ram[0x753U] = (unsigned char)(scenario - 2U);
        ram[0x00eU] = 11U;
        ram[0x747U] = 0xffU;
    }
}

static int mysmb_game_entry_argument(const char *text)
{
    static const char prefix[] = "--fixture=t31-game-entry=";
    unsigned int i;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '3' || text[i+1U] != '\0') return 0;
    return (int)(text[i] - '0') + 1;
}
#endif
