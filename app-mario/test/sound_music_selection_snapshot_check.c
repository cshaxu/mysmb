#include "core/audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char find_header_selector(unsigned char music,
                                          unsigned char base)
{
    unsigned char selector;
    unsigned char carry;

    selector = base;
    do {
        ++selector;
        carry = (unsigned char)(music & 1U);
        music >>= 1U;
    } while (carry == 0U && music != 0U);
    return selector;
}

static void source_selection_oracle(unsigned char *expected,
                                    const unsigned char *prg)
{
    unsigned char event;
    unsigned char area;
    unsigned char selector;
    unsigned char header;

    event = expected[0x00fcU];
    area = expected[0x00fbU];
    if (event != 0U) {
        expected[0x07b1U] = event;
        if (event == 1U) expected[0x00f1U] = 0U;
        expected[0x07c5U] = expected[0x00f4U];
        expected[0x07c4U] = event == 0x40U ? 8U : 0U;
        expected[0x00f4U] = 0U;
        selector = find_header_selector(event, 0U);
    }
    else if (area != 0U) {
        if (area == 4U) expected[0x00f1U] = 0U;
        expected[0x07c7U] = 0x10U;
        expected[0x07b1U] = 0U;
        expected[0x00f4U] = area;
        if (area == 1U) {
            expected[0x07c7U]++;
            selector = expected[0x07c7U];
        }
        else selector = find_header_selector(area, 8U);
    }
    else return;
    header = prg[0x790cU + selector];
    expected[0x00f0U] = prg[0x790dU + header];
    expected[0x00f5U] = prg[0x790eU + header];
    expected[0x00f6U] = prg[0x790fU + header];
    expected[0x00f9U] = prg[0x7910U + header];
    expected[0x00f8U] = prg[0x7911U + header];
    expected[0x07b0U] = prg[0x7912U + header];
    expected[0x07c1U] = expected[0x07b0U];
    expected[0x00f7U] = 0U;
    expected[0x07b4U] = 1U;
    expected[0x07b6U] = 1U;
    expected[0x07b9U] = 1U;
    expected[0x07baU] = 1U;
    expected[0x07caU] = 0U;
}

/* Bounded original SoundEngine records for T49/S3 event/area selector and
 * header-load routes.  Records remain owner-local under build/. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    static const unsigned int ram_addresses[] = {
        0x00f0U, 0x00f1U, 0x00f2U, 0x00f4U, 0x00f5U, 0x00f6U, 0x00f7U,
        0x00f8U, 0x00f9U, 0x07b0U, 0x07b1U, 0x07b3U, 0x07b4U, 0x07b6U,
        0x07b8U, 0x07b9U, 0x07baU, 0x07c1U, 0x07c4U, 0x07c5U, 0x07c7U,
        0x07caU
    };
    unsigned char header[16];
    unsigned char sound_header[8];
    unsigned char record[4144];
    unsigned char expected[2048];
    FILE *rom;
    FILE *input;
    unsigned int child;
    unsigned int index;
    unsigned int failures;
    unsigned int case_id;

    if (argc != 4) return 64;
    case_id = (unsigned int)atoi(argv[3]);
    if (case_id < 96U || case_id > 100U) return 64;
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
        mysmb_audio_select_music(&game);
        memcpy(expected, record, sizeof(expected));
        source_selection_oracle(expected, prg);
        for (index = 0U; index < sizeof(ram_addresses) / sizeof(ram_addresses[0]);
             ++index) {
            unsigned int address = ram_addresses[index];
            if (game.ram[address] != expected[address]) {
                if (failures < 24U)
                    printf("case=%u child=%u RAM=%04x ROM=%02x C=%02x\n",
                           case_id, child, address, expected[address],
                           game.ram[address]);
                ++failures;
            }
        }
        if (game.apu_registers[21U] != 0x0fU) {
            if (failures < 24U)
                printf("case=%u child=%u APU=15 ROM=%02x C=%02x\n", case_id,
                       child, record[4120U + 21U], game.apu_registers[21U]);
            ++failures;
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("music selection case=%u children=%u failures=%u\n", case_id,
           child, failures);
    return failures != 0U;
}
