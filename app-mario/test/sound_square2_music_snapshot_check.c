#include "core/audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Compare only the S4-owned square-two stream/result surface after each real
 * SoundEngine call.  The original records are owner-local build evidence. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    unsigned char header[16];
    unsigned char sound_header[8];
    unsigned char record[4144];
    static const unsigned int ram_addresses[] = {
        0x00f0U, 0x00f4U, 0x00f5U, 0x00f6U, 0x00f7U,
        0x07b1U, 0x07b3U, 0x07b4U, 0x07b5U, 0x07c4U
    };
    static const unsigned int apu_addresses[] = { 4U, 5U, 6U, 7U, 8U };
    FILE *rom;
    FILE *input;
    unsigned int child;
    unsigned int index;
    unsigned int failures;
    unsigned int terminal_square2;

    if (argc != 3) return 64;
    rom = fopen(argv[2], "rb");
    if (rom == NULL) return 65;
    if (fread(header, 1U, 16U, rom) != 16U ||
        memcmp(header, "NES\032", 4U) != 0 || header[4] != 2U ||
        (header[6] & 4U) != 0U ||
        fread(prg, 1U, sizeof(prg), rom) != sizeof(prg)) return 66;
    fclose(rom);
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(sound_header, 1U, 8U, input) != 8U ||
        memcmp(sound_header, "MSSN\1", 5U) != 0 || sound_header[5] == 0U ||
        sound_header[5] > 8U) return 66;
    failures = 0U;
    for (child = 0U; child < sound_header[5]; ++child) {
        if (fread(record, 1U, sizeof(record), input) != sizeof(record)) return 66;
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record, 2048U);
        memcpy(game.apu_registers, record + 2048U, 24U);
        game.apu_delta_counter_load = game.apu_registers[17U];
        game.apu_channel_enable = game.apu_registers[21U];
        game.apu_frame_counter = game.apu_registers[23U];
        game.area_prg = prg;
        game.area_prg_size = sizeof(prg);
        /* $4008 is written by EndOfMusicData only on its terminal RTS path.
         * On a loop path, the original falls through to the later triangle
         * handler, which is outside S4's admitted chain. */
        terminal_square2 = record[0x07b1U] != 0U &&
            !(record[0x07b1U] == 0x40U && record[0x07c5U] != 0U) &&
            (record[0x07b1U] & 0x04U) == 0U &&
            (record[0x00f4U] & 0x5fU) == 0U;
        mysmb_audio_step(&game);
        for (index = 0U; index < sizeof(ram_addresses) / sizeof(ram_addresses[0]); ++index) {
            unsigned int address = ram_addresses[index];
            if (game.ram[address] != record[2072U + address]) {
                if (failures < 24U) printf("child=%u RAM=%04x ROM=%02x C=%02x\n", child, address, record[2072U + address], game.ram[address]);
                ++failures;
            }
        }
        for (index = 0U; index < sizeof(apu_addresses) / sizeof(apu_addresses[0]); ++index) {
            unsigned int address = apu_addresses[index];
            if (address == 8U && terminal_square2 == 0U) continue;
            if (game.apu_registers[address] != record[4120U + address]) {
                if (failures < 24U) printf("child=%u APU=%02x ROM=%02x C=%02x\n", child, address, record[4120U + address], game.apu_registers[address]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("square2-music children=%u failures=%u\n", child, failures);
    return failures != 0U;
}
