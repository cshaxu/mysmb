#include "game/audio.h"
#include <stdio.h>
#include <string.h>

/* Original helper entry/stack-return records are owner-local in build/. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    unsigned char header[16];
    unsigned char helper_header[8];
    unsigned char record[58];
    FILE *rom;
    FILE *input;
    unsigned int count;
    unsigned int index;
    unsigned int failures;
    unsigned int address;
    unsigned int pc;
    mysmb_u8 result_a;

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
    if (fread(helper_header, 1U, 8U, input) != 8U ||
        memcmp(helper_header, "MSAH\1", 5U) != 0 ||
        helper_header[5] == 0U) return 66;
    count = helper_header[5];
    failures = 0U;
    for (index = 0U; index < count; ++index) {
        if (fread(record, 1U, sizeof(record), input) != sizeof(record))
            return 66;
        memset(&game, 0, sizeof(game));
        memcpy(game.apu_registers, record + 6U, 24U);
        game.area_prg = prg;
        game.area_prg_size = sizeof(prg);
        pc = record[0] | ((unsigned int)record[1] << 8U);
        result_a = record[2];
        switch (pc) {
        case 0xf381U:
            mysmb_audio_dump_squ1_regs(&game, record[3], record[4]);
            break;
        case 0xf388U:
            result_a = mysmb_audio_play_squ1_sfx(&game, record[2],
                                                  record[3], record[4]);
            break;
        case 0xf38bU:
            result_a = mysmb_audio_set_freq_squ1(&game, record[2]);
            break;
        case 0xf38dU:
            result_a = mysmb_audio_dump_freq_regs(&game, record[2],
                                                   record[3]);
            break;
        case 0xf39eU:
            /* NoTone is only RTS; its outgoing APU state is unchanged. */
            break;
        case 0xf39fU:
            mysmb_audio_dump_sq2_regs(&game, record[3], record[4]);
            break;
        case 0xf3a6U:
            result_a = mysmb_audio_play_sq2_sfx(&game, record[2],
                                                 record[3], record[4]);
            break;
        case 0xf3a9U:
            result_a = mysmb_audio_set_freq_sq2(&game, record[2]);
            break;
        case 0xf3adU:
            result_a = mysmb_audio_set_freq_tri(&game, record[2]);
            break;
        default:
            return 66;
        }
        if (result_a != record[54]) {
            if (failures < 20U)
                printf("record=%u pc=%04x A ROM=%02x C=%02x\n",
                       index, pc, record[54], result_a);
            ++failures;
        }
        for (address = 0U; address < 24U; ++address) {
            if (game.apu_registers[address] != record[30U + address]) {
                if (failures < 20U)
                    printf("record=%u pc=%04x APU=%02x ROM=%02x C=%02x\n",
                           index, pc, address, record[30U + address],
                           game.apu_registers[address]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("sound helpers=%u failures=%u\n", count, failures);
    return failures != 0U;
}
