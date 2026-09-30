#include "game/audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Original NMI SoundEngine records remain owner-local below build/. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    unsigned char header[16];
    unsigned char sound_header[8];
    unsigned char record[4144];
    FILE *rom;
    FILE *input;
    unsigned int child;
    unsigned int failures;
    unsigned int address;
    unsigned int case_id;
    const unsigned int ram_addresses[3] = { 0x00f3U, 0x00fdU, 0x07bfU };
    const unsigned int apu_addresses[3] = { 12U, 14U, 15U };

    if (argc != 4) return 64;
    case_id = (unsigned int)atoi(argv[3]);
    if (case_id < 89U || case_id > 94U) return 64;
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
        memcmp(sound_header, "MSSN\1", 5U) != 0 ||
        sound_header[5] == 0U || sound_header[5] > 8U) return 66;
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
        for (address = 0U; address < 3U; ++address) {
            unsigned int offset = ram_addresses[address];
            if (game.ram[offset] != record[2072U + offset]) {
                if (failures < 24U)
                    printf("case=%u child=%u RAM=%04x ROM=%02x C=%02x\n",
                           case_id, child, offset, record[2072U + offset],
                           game.ram[offset]);
                ++failures;
            }
        }
        for (address = 0U; address < 3U; ++address) {
            unsigned int offset = apu_addresses[address];
            if (game.apu_registers[offset] != record[4120U + offset]) {
                if (failures < 24U)
                    printf("case=%u child=%u APU=%02x ROM=%02x C=%02x\n",
                           case_id, child, offset, record[4120U + offset],
                           game.apu_registers[offset]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("noise case=%u children=%u failures=%u\n", case_id, child,
           failures);
    return failures != 0U;
}
