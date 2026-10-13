#ifndef MYSMB_AREA_POINTER_FIXTURE_H
#define MYSMB_AREA_POINTER_FIXTURE_H

/* Normal dispatch only: two-player GameOver -> ContinueGame -> InitializeArea,
 * or direct GameMode task-zero entry. Inputs enumerate world/area and slots. */
static void mysmb_area_pointer_fixture(unsigned char *ram, unsigned char scenario)
{
    static const unsigned char worlds[8] = { 5U, 5U, 4U, 5U, 4U, 4U, 5U, 4U };
    static const unsigned char slots[4] = { 3U, 22U, 3U, 6U };
    unsigned char group, index;
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x74eU] = 0xfeU;
    ram[0x74fU] = 0xeeU;
    ram[0xe7U] = 0x91U; ram[0xe8U] = 0x92U;
    ram[0xe9U] = 0x93U; ram[0xeaU] = 0x94U;
    if (scenario == 70U) {
        ram[0x770U] = 3U; ram[0x772U] = 2U;
        ram[0x7a0U] = 0U; ram[0x77aU] = 0U;
        ram[0x75fU] = 5U;
    } else if (scenario < 36U) {
        group = 0U; index = scenario;
        while (index >= worlds[group]) { index = (unsigned char)(index-worlds[group]); ++group; }
        ram[0x761U] = 2U; ram[0x762U] = 0U; ram[0x763U] = 0U;
        ram[0x764U] = 0U; ram[0x765U] = 0U;
        ram[0x766U] = group; ram[0x767U] = index;
        ram[0x77aU] = 1U;
        ram[0x753U] = 0U;
        ram[0x770U] = 3U;
        ram[0x772U] = 2U;
        ram[0x7a0U] = 0U;
    } else {
        group = 0U; index = (unsigned char)(scenario-36U);
        while (index >= slots[group]) { index = (unsigned char)(index-slots[group]); ++group; }
        ram[0x750U] = (unsigned char)(group*32U + index + (scenario%2U)*128U);
        ram[0x75bU] = (unsigned char)(scenario%4U);
        ram[0x752U] = 0U;
        ram[0x772U] = 0U;
    }
}

static int mysmb_area_pointer_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-area-pointer=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9') value = value*10U + (unsigned int)(text[i++]-'0');
    if (text[i] != '\0' || value > 70U) return 0;
    return (int)value+1;
}
#endif
