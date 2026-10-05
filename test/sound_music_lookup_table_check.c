#include "core/audio.h"
#include <stdio.h>
#include <string.h>

enum {
    MYSMB_PRG_SIZE = 32768U,
    MYSMB_FREQ_TABLE = 0xff00U,
    MYSMB_FREQ_LAST_PAIR = 0x64U,
    MYSMB_LENGTH_TABLE = 0xff66U,
    MYSMB_LENGTH_COUNT = 48U,
    MYSMB_END_CASTLE_ENVELOPE = 0xff96U,
    MYSMB_END_CASTLE_COUNT = 4U,
    MYSMB_AREA_ENVELOPE = 0xff9aU,
    MYSMB_AREA_COUNT = 8U,
    MYSMB_WATER_ENVELOPE = 0xffa2U,
    MYSMB_WATER_COUNT = 40U
};

static unsigned char mysmb_read_cpu(const unsigned char *prg,
                                    unsigned int address)
{
    return prg[address - 0x8000U];
}

static unsigned int mysmb_check_frequency(const unsigned char *prg)
{
    struct mysmb_game game;
    unsigned int a;
    unsigned int failures;
    unsigned char low;
    unsigned char high;

    failures = 0U;
    for (a = 0U; a <= MYSMB_FREQ_LAST_PAIR; a += 2U) {
        memset(&game, 0, sizeof(game));
        game.area_prg = prg;
        game.area_prg_size = MYSMB_PRG_SIZE;
        low = mysmb_read_cpu(prg, MYSMB_FREQ_TABLE + a + 1U);
        high = (unsigned char)(mysmb_read_cpu(prg, MYSMB_FREQ_TABLE + a) |
                               8U);
        if (mysmb_audio_dump_freq_regs(&game, (mysmb_u8)a, 0U) !=
            (low == 0U ? 0U : high) ||
            (low != 0U && (game.apu_registers[2] != low ||
                           game.apu_registers[3] != high))) {
            printf("freq a=%u x=0\n", a);
            ++failures;
        }
        memset(game.apu_registers, 0, sizeof(game.apu_registers));
        if (mysmb_audio_dump_freq_regs(&game, (mysmb_u8)a, 8U) !=
            (low == 0U ? 0U : high) ||
            (low != 0U && (game.apu_registers[10] != low ||
                           game.apu_registers[11] != high))) {
            printf("freq a=%u x=8\n", a);
            ++failures;
        }
    }
    return failures;
}

static unsigned int mysmb_check_lengths(const unsigned char *prg)
{
    struct mysmb_game game;
    unsigned int index;
    unsigned int failures;

    failures = 0U;
    memset(&game, 0, sizeof(game));
    game.area_prg = prg;
    game.area_prg_size = MYSMB_PRG_SIZE;
    for (index = 0U; index < MYSMB_LENGTH_COUNT; ++index) {
        game.ram[0x00f0U] = (mysmb_u8)index;
        game.ram[0x07c4U] = 0U;
        if (mysmb_audio_process_music_length(&game, 0U) !=
            mysmb_read_cpu(prg, MYSMB_LENGTH_TABLE + index)) {
            printf("length index=%u\n", index);
            ++failures;
        }
    }
    game.ram[0x00f0U] = 0x18U;
    game.ram[0x07c4U] = 0x0fU;
    if (mysmb_audio_process_music_length(&game, 0U) !=
        mysmb_read_cpu(prg, MYSMB_LENGTH_TABLE + 0x27U)) {
        printf("length indexed-addition\n");
        ++failures;
    }
    return failures;
}

static unsigned int mysmb_check_envelope(const unsigned char *prg,
                                         unsigned int start,
                                         unsigned int count,
                                         unsigned char event,
                                         unsigned char area)
{
    struct mysmb_game game;
    unsigned int index;
    unsigned int failures;

    failures = 0U;
    memset(&game, 0, sizeof(game));
    game.area_prg = prg;
    game.area_prg_size = MYSMB_PRG_SIZE;
    game.ram[0x07b1U] = event;
    game.ram[0x00f4U] = area;
    for (index = 0U; index < count; ++index) {
        if (mysmb_audio_load_music_envelope(&game, (mysmb_u8)index) !=
            mysmb_read_cpu(prg, start + index)) {
            printf("envelope start=%04x index=%u\n", start, index);
            ++failures;
        }
    }
    return failures;
}

int main(int argc, char **argv)
{
    unsigned char ines[16];
    static unsigned char prg[MYSMB_PRG_SIZE];
    FILE *rom;
    unsigned int failures;

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
    failures = mysmb_check_frequency(prg);
    failures += mysmb_check_lengths(prg);
    failures += mysmb_check_envelope(prg, MYSMB_END_CASTLE_ENVELOPE,
        MYSMB_END_CASTLE_COUNT, 0x08U, 0U);
    failures += mysmb_check_envelope(prg, MYSMB_AREA_ENVELOPE,
        MYSMB_AREA_COUNT, 0U, 0x01U);
    failures += mysmb_check_envelope(prg, MYSMB_WATER_ENVELOPE,
        MYSMB_WATER_COUNT, 0U, 0U);
    printf("music lookup checks=203 failures=%u\n", failures);
    return failures != 0U;
}
