#ifndef MYSMB_UNDERGROUND_SCENE_FIXTURE_H
#define MYSMB_UNDERGROUND_SCENE_FIXTURE_H

/* Enter the original area initializer through source RAM only. */
static void mysmb_underground_scene_fixture(unsigned char *ram, unsigned char scenario)
{
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 0U;
    ram[0x750U] = (unsigned char)(0x40U + scenario);
    ram[0x75bU] = 0U;
    ram[0x752U] = 0U;
}

static void mysmb_underground_scene_continue(unsigned char *ram)
{
    ram[0x73cU] = 8U;
    ram[0x71eU] = 127U;
    ram[0x722U] = 0U;
}

static int mysmb_underground_scene_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-underground-scene=";
    unsigned int i;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '2' || text[i+1U] != '\0') return 0;
    return (int)(text[i] - '0') + 1;
}
#endif
