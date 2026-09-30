#include "game/audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Original SoundEngine entry/stack-return snapshots remain in build/. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    unsigned char header[16];
    unsigned char record[4144];
    unsigned char sound_header[8];
    FILE *rom;
    FILE *input;
    unsigned int child;
    unsigned int address;
    unsigned int failures;
    unsigned int kind;
    int full_ram;

    if (argc != 4) return 64;
    kind = (unsigned int)atoi(argv[3]);
    if (kind > 12U) return 64;
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
        full_ram = (kind >= 1U && kind != 9U && kind != 10U) ||
            record[0x0770U] == 0U;
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record, 2048U);
        memcpy(game.apu_registers, record + 2048U, 24U);
        game.apu_delta_counter_load = game.apu_registers[17U];
        game.apu_channel_enable = game.apu_registers[21U];
        game.apu_frame_counter = game.apu_registers[23U];
        game.area_prg = prg;
        game.area_prg_size = sizeof(prg);
        mysmb_audio_step(&game);
        for (address = 0U; address < 2048U; ++address) {
            int selected;
            if (address >= 0x100U && address < 0x200U) continue;
            selected = full_ram || (address >= 0xfaU && address <= 0xffU) ||
                address == 0x07b2U || address == 0x07c0U ||
                address == 0x07c6U;
            if (!selected) continue;
            if (game.ram[address] != record[2072U + address]) {
                if (failures < 30U)
                    printf("child=%u RAM=%04x ROM=%02x C=%02x\n", child,
                           address, record[2072U + address],
                           game.ram[address]);
                ++failures;
            }
        }
        for (address = 0U; address < 24U; ++address) {
            if (!full_ram && address != 17U && address != 21U &&
                address != 23U) continue;
            if (game.apu_registers[address] != record[4120U + address]) {
                if (failures < 30U)
                    printf("child=%u APU=%02x ROM=%02x C=%02x\n", child,
                           address, record[4120U + address],
                           game.apu_registers[address]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("sound entry case=%u children=%u failures=%u\n",
           kind, child, failures);
    return failures != 0U;
}
