#include "core/audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* T49/S5 compares the Square1 stream/result surface after an unchanged
 * SoundEngine invocation.  Input and output records remain owner-local under
 * build/; the supplied ROM is never copied into tracked data. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    static const unsigned int ram_addresses[] = {
        0x00f1U, 0x00f8U, 0x07b6U, 0x07b7U, 0x07caU
    };
    static const unsigned int apu_addresses[] = { 0U, 1U, 2U, 3U };
    unsigned char header[16];
    unsigned char sound_header[8];
    unsigned char record[4144];
    FILE *rom;
    FILE *input;
    unsigned int child;
    unsigned int index;
    unsigned int failures;
    unsigned int case_id;

    if (argc != 4) return 64;
    case_id = (unsigned int)atoi(argv[3]);
    if (case_id < 107U || case_id > 110U) return 64;
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
        if (fread(record, 1U, sizeof(record), input) != sizeof(record))
            return 66;
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record, 2048U);
        memcpy(game.apu_registers, record + 2048U, 24U);
        game.apu_delta_counter_load = game.apu_registers[17U];
        game.apu_channel_enable = game.apu_registers[21U];
        game.apu_frame_counter = game.apu_registers[23U];
        game.area_prg = prg;
        game.area_prg_size = sizeof(prg);
        mysmb_audio_step(&game);
        for (index = 0U; index < sizeof(ram_addresses) / sizeof(ram_addresses[0]);
             ++index) {
            unsigned int address = ram_addresses[index];
            if (game.ram[address] != record[2072U + address]) {
                if (failures < 24U)
                    printf("case=%u child=%u RAM=%04x ROM=%02x C=%02x\n",
                           case_id, child, address, record[2072U + address],
                           game.ram[address]);
                ++failures;
            }
        }
        for (index = 0U; index < sizeof(apu_addresses) / sizeof(apu_addresses[0]);
             ++index) {
            unsigned int address = apu_addresses[index];
            if (game.apu_registers[address] != record[4120U + address]) {
                if (failures < 24U)
                    printf("case=%u child=%u APU=%02x ROM=%02x C=%02x\n",
                           case_id, child, address, record[4120U + address],
                           game.apu_registers[address]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("square1-music case=%u children=%u failures=%u\n", case_id,
           child, failures);
    return failures != 0U;
}
