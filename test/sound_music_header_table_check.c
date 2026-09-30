#include "game/audio.h"
#include <stdio.h>
#include <string.h>

enum {
    MYSMB_PRG_SIZE = 32768U,
    MYSMB_HEADER_TABLE = 0x790dU
};

static unsigned int check_header(const unsigned char *prg, unsigned int selector)
{
    static const unsigned int addresses[] = {
        0x00f0U, 0x00f5U, 0x00f6U, 0x00f7U, 0x00f8U, 0x00f9U,
        0x07b0U, 0x07b4U, 0x07b6U, 0x07b9U, 0x07baU, 0x07c1U,
        0x07caU
    };
    struct mysmb_game game;
    unsigned int offset;
    unsigned int failures;
    unsigned int index;
    unsigned char expected[13];

    memset(&game, 0xa5, sizeof(game));
    game.area_prg = prg;
    game.area_prg_size = MYSMB_PRG_SIZE;
    offset = prg[MYSMB_HEADER_TABLE - 1U + selector];
    expected[0] = prg[MYSMB_HEADER_TABLE + offset];
    expected[1] = prg[MYSMB_HEADER_TABLE + offset + 1U];
    expected[2] = prg[MYSMB_HEADER_TABLE + offset + 2U];
    expected[3] = 0U;
    expected[4] = prg[MYSMB_HEADER_TABLE + offset + 4U];
    expected[5] = prg[MYSMB_HEADER_TABLE + offset + 3U];
    expected[6] = prg[MYSMB_HEADER_TABLE + offset + 5U];
    expected[7] = 1U;
    expected[8] = 1U;
    expected[9] = 1U;
    expected[10] = 1U;
    expected[11] = expected[6];
    expected[12] = 0U;
    failures = mysmb_audio_load_music_header(&game, (mysmb_u8)selector) == 1U ?
        0U : 1U;
    for (index = 0U; index < sizeof(addresses) / sizeof(addresses[0]); ++index) {
        if (game.ram[addresses[index]] != expected[index]) ++failures;
    }
    if (game.apu_registers[21U] != 0x0fU) ++failures;
    if (failures != 0U)
        printf("selector=%u offset=%u failures=%u\n", selector, offset, failures);
    return failures;
}

int main(int argc, char **argv)
{
    unsigned char ines[16];
    static unsigned char prg[MYSMB_PRG_SIZE];
    FILE *rom;
    unsigned int selector;
    unsigned int failures;

    if (argc != 2) return 64;
    rom = fopen(argv[1], "rb");
    if (rom == NULL) return 65;
    if (fread(ines, 1U, sizeof(ines), rom) != sizeof(ines) ||
        memcmp(ines, "NES\032", 4U) != 0 || ines[4] != 2U ||
        (ines[6] & 4U) != 0U || fread(prg, 1U, sizeof(prg), rom) != sizeof(prg)) {
        fclose(rom);
        return 66;
    }
    fclose(rom);
    failures = 0U;
    for (selector = 1U; selector < 0x40U; ++selector)
        failures += check_header(prg, selector);
    printf("music header table selectors=63 failures=%u\n", failures);
    return failures != 0U;
}
