#include "core/audio.h"
#include <stdio.h>
#include <string.h>

enum { MYSMB_PRG_SIZE = 32768U, MYSMB_HEADER_TABLE = 0x790dU };

static const unsigned int mysmb_music_starts[] = {
    0xf9b8U, 0xfa01U, 0xfa1cU, 0xfa49U, 0xfa75U, 0xfa9dU, 0xfac2U,
    0xfadbU, 0xfaf9U, 0xfb25U, 0xfb4bU, 0xfb72U, 0xfb74U, 0xfba4U,
    0xfc45U, 0xfc72U, 0xfcb0U, 0xfd11U, 0xfd52U, 0xfe51U, 0xfec8U
};

/* The source MusicHeaderOffsetData has 49 legal Y selectors: eight event
 * routes, eight area routes, then the 33-entry ground layout.  These CPU
 * addresses are label metadata only; stream bytes remain in the owner ROM. */
static const unsigned int mysmb_header_start_by_selector[] = {
    0xfb72U, 0xfc45U, 0xfec8U, 0xfe51U, 0xfc45U, 0xfcb0U, 0xfc72U,
    0xfa1cU, 0xfa01U, 0xfd52U, 0xfd11U, 0xfba4U, 0xf9b8U, 0xfaf9U,
    0xf9b8U, 0xfa1cU, 0xfaf9U, 0xfa01U, 0xfa01U, 0xfa49U, 0xfa75U,
    0xfa49U, 0xfa9dU, 0xfa49U, 0xfa75U, 0xfa49U, 0xfa9dU, 0xfac2U,
    0xfadbU, 0xfac2U, 0xfaf9U, 0xfa01U, 0xfa01U, 0xfb25U, 0xfb4bU,
    0xfb25U, 0xfb74U, 0xfb25U, 0xfb4bU, 0xfb25U, 0xfb74U, 0xfac2U,
    0xfadbU, 0xfac2U, 0xfaf9U, 0xfb25U, 0xfb4bU, 0xfb25U, 0xfb74U
};

static unsigned int find_start(unsigned int address)
{
    unsigned int index;
    for (index = 0U; index < sizeof(mysmb_music_starts) /
                                sizeof(mysmb_music_starts[0]); ++index)
        if (mysmb_music_starts[index] == address) return index + 1U;
    return 0U;
}

static void activate_source_music_family(struct mysmb_game *game,
                                         unsigned int selector)
{
    /* MusicHandler has already selected this header in the source route.
     * Restore its event/area buffer so one SoundEngine tick reaches each
     * header's four stream offsets under the matching family semantics. */
    if (selector <= 8U)
        game->ram[0x07b1U] = (mysmb_u8)(1U << (selector - 1U));
    else if (selector <= 16U)
        game->ram[0x00f4U] = (mysmb_u8)(1U << (selector - 9U));
    else
        game->ram[0x00f4U] = 1U;
}

static unsigned int check_selector(const unsigned char *prg,
                                   unsigned int selector,
                                   unsigned char seen[])
{
    struct mysmb_game game;
    unsigned int address;
    unsigned int entry;
    unsigned int failures;

    memset(&game, 0, sizeof(game));
    game.area_prg = prg;
    game.area_prg_size = MYSMB_PRG_SIZE;
    /* LoadHeader is the common source entry after the event/area bit scan
     * or the ground-layout counter.  The ground queue entry deliberately
     * resets that counter to $10 before selecting its first header, so a
     * one-shot queue fixture cannot legally force arbitrary layout entries.
     * Exercise every valid LoadHeader Y selector here; MusicHandler's three
     * queue families are covered independently by its dispatch test. */
    if (mysmb_audio_load_music_header(&game, (mysmb_u8)selector) == 0U)
        return 1U;
    address = (unsigned int)game.ram[0x00f5U] |
              ((unsigned int)game.ram[0x00f6U] << 8U);
    failures = 0U;
    if (address != mysmb_header_start_by_selector[selector - 1U]) {
        printf("selector=%u expected=%04x address=%04x\n", selector,
               mysmb_header_start_by_selector[selector - 1U], address);
        ++failures;
    }
    entry = find_start(address);
    if (entry == 0U) return failures + 1U;
    seen[entry - 1U] = 1U;
    /* The stream bytes remain owner-local.  The common LoadHeader entry has
     * established their Square2 pointer for every caller family. */
    activate_source_music_family(&game, selector);
    mysmb_audio_step(&game);
    return failures;
}

int main(int argc, char **argv)
{
    unsigned char ines[16];
    static unsigned char prg[MYSMB_PRG_SIZE];
    unsigned char seen[sizeof(mysmb_music_starts) /
                       sizeof(mysmb_music_starts[0])];
    FILE *rom;
    unsigned int selector;
    unsigned int index;
    unsigned int failures;
    unsigned int covered;

    if (argc != 2) return 64;
    rom = fopen(argv[1], "rb");
    if (rom == NULL) return 65;
    if (fread(ines, 1U, sizeof(ines), rom) != sizeof(ines) ||
        memcmp(ines, "NES\032", 4U) != 0 || ines[4] != 2U ||
        (ines[6] & 4U) != 0U ||
        fread(prg, 1U, sizeof(prg), rom) != sizeof(prg)) {
        fclose(rom);
        return 66;
    }
    fclose(rom);
    memset(seen, 0, sizeof(seen));
    failures = 0U;
    for (selector = 1U; selector < 0x32U; ++selector)
        failures += check_selector(prg, selector, seen);
    covered = 0U;
    for (index = 0U; index < sizeof(seen); ++index) {
        if (seen[index] == 0U) {
            printf("missing music start=%04x\n", mysmb_music_starts[index]);
            ++failures;
        }
        else ++covered;
    }
    printf("music stream records=%u failures=%u\n", covered, failures);
    return failures != 0U;
}


