#ifndef MYSMB_CASTLE_SCENE_FIXTURE_H
#define MYSMB_CASTLE_SCENE_FIXTURE_H

/* Original InitializeArea first; then ordinary ScreenRoutines parser sets.
 * Case six covers castle six's second half. Only source RAM is seeded. */
static void mysmb_castle_scene_fixture(unsigned char *ram, unsigned char scenario)
{
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 0U;
    ram[0x750U] = (unsigned char)(0x60U + (scenario == 6U ? 5U : scenario));
    ram[0x75bU] = scenario == 6U ? 16U : 0U;
    ram[0x752U] = 0U;
}

static void mysmb_castle_scene_continue(unsigned char *ram)
{
    ram[0x73cU] = 8U;
    ram[0x71eU] = 127U;
    ram[0x722U] = 0U;
}

static int mysmb_castle_scene_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-castle-scene=";
    unsigned int i;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '6' || text[i+1U] != '\0') return 0;
    return (int)(text[i] - '0') + 1;
}
#endif
