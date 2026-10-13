#ifndef MYSMB_GROUND_SCENE_FIXTURE_H
#define MYSMB_GROUND_SCENE_FIXTURE_H

/* Source-RAM entry into InitializeArea. Case 22 traverses all of area 17. */
static void mysmb_ground_scene_fixture(unsigned char *ram, unsigned char scenario)
{
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 0U;
    ram[0x750U] = (unsigned char)(0x20U + (scenario == 22U ? 16U : scenario));
    ram[0x75bU] = 0U;
    ram[0x752U] = 0U;
}

static void mysmb_ground_scene_continue(unsigned char *ram)
{
    ram[0x73cU] = 8U;
    ram[0x71eU] = 127U;
    ram[0x722U] = 0U;
}

static int mysmb_ground_scene_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-ground-scene=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    value = 0U;
    digits = 0U;
    while (text[i] >= '0' && text[i] <= '9') {
        if (++digits > 2U) return 0;
        value = value * 10U + (unsigned int)(text[i++] - '0');
    }
    if (digits == 0U || text[i] != '\0' || value > 22U) return 0;
    return (int)value + 1;
}
#endif
