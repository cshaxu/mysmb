#include "game/audio.h"
#include <stdio.h>
#include <string.h>

enum {
    MYSMB_PRG_SIZE = 32768U,
    MYSMB_OPERATING_MODE = 0x0770U,
    MYSMB_NOISE_BUFFER = 0x00f3U,
    MYSMB_NOISE_LENGTH = 0x07bfU,
    MYSMB_BOWSER_ENVELOPE = 0xffcaU,
    MYSMB_BOWSER_COUNT = 32U,
    MYSMB_BRICK_ENVELOPE = 0xffeaU,
    MYSMB_BRICK_COUNT = 16U
};

static unsigned char mysmb_read_cpu(const unsigned char *prg,
                                    unsigned int address)
{
    return prg[address - 0x8000U];
}

static unsigned int mysmb_check_brick(const unsigned char *prg)
{
    struct mysmb_game game;
    unsigned int index;
    unsigned int failures;
    unsigned char length;

    failures = 0U;
    for (index = 0U; index < MYSMB_BRICK_COUNT; ++index) {
        memset(&game, 0, sizeof(game));
        game.area_prg = prg;
        game.area_prg_size = MYSMB_PRG_SIZE;
        game.ram[MYSMB_OPERATING_MODE] = 1U;
        game.ram[MYSMB_NOISE_BUFFER] = 1U;
        length = (unsigned char)((index << 1U) | 1U);
        game.ram[MYSMB_NOISE_LENGTH] = length;
        mysmb_audio_step(&game);
        if (game.apu_registers[12U] != (index == 0U ? 0xf0U :
                mysmb_read_cpu(prg, MYSMB_BRICK_ENVELOPE + index)) ||
            game.apu_registers[15U] != 0x18U ||
            game.ram[MYSMB_NOISE_LENGTH] != (unsigned char)(length - 1U)) {
            printf("brick index=%u\n", index);
            ++failures;
        }
    }
    return failures;
}

static unsigned int mysmb_check_bowser(const unsigned char *prg)
{
    struct mysmb_game game;
    unsigned int index;
    unsigned int failures;
    unsigned char length;

    failures = 0U;
    for (index = 0U; index < MYSMB_BOWSER_COUNT; ++index) {
        memset(&game, 0, sizeof(game));
        game.area_prg = prg;
        game.area_prg_size = MYSMB_PRG_SIZE;
        game.ram[MYSMB_OPERATING_MODE] = 1U;
        game.ram[MYSMB_NOISE_BUFFER] = 2U;
        length = (unsigned char)((index + 1U) << 1U);
        game.ram[MYSMB_NOISE_LENGTH] = length;
        mysmb_audio_step(&game);
        if (game.apu_registers[12U] !=
                mysmb_read_cpu(prg, MYSMB_BOWSER_ENVELOPE + index) ||
            game.apu_registers[14U] != 0x0fU ||
            game.apu_registers[15U] != 0x18U ||
            game.ram[MYSMB_NOISE_LENGTH] != (unsigned char)(length - 1U)) {
            printf("bowser index=%u\n", index);
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
    failures = mysmb_check_brick(prg);
    failures += mysmb_check_bowser(prg);
    printf("noise envelope checks=48 failures=%u\n", failures);
    return failures != 0U;
}
