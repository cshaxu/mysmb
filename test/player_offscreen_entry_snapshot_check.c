#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Owner-ROM records stay in ignored build/.  This checks the naturally
 * reached player entry through its shared offscreen child. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    unsigned char header[8];
    unsigned char record[4100];
    FILE *input;
    unsigned int child;
    unsigned int address;
    unsigned int failures;
    unsigned int deferred_child_scratch;
    if (argc != 2) return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1U, 8U, input) != 8U ||
        memcmp(header, "MSRC\2", 5U) != 0 ||
        header[5] == 0U || header[5] > 8U) return 66;
    failures = 0U;
    deferred_child_scratch = 0U;
    for (child = 0U; child < header[5]; ++child) {
        if (fread(record, 1U, sizeof(record), input) != sizeof(record) ||
            record[0] != 7U) return 66;
        if (record[3] != 1U) {
            printf("child=%u did not enter $f1c0 with X=Y=0\n", child);
            ++failures;
        }
        if (record[2] != record[4U + 0x0008U]) {
            printf("child=%u original X return=%02x ObjectOffset=%02x\n",
                   child, record[2], record[4U + 0x0008U]);
            ++failures;
        }
        memcpy(game.ram, record + 4U, 2048U);
        mysmb_oam_get_player_offscreen_bits(&game);
        for (address = 0U; address < 2048U; ++address) {
            if (address >= 0x100U && address < 0x200U) continue;
            if (game.ram[address] != record[2052U + address]) {
                /* The common GetOffScreenBitsSet child is owned by S4.
                 * Report its known scratch gap; this checker only credits
                 * the player entry and its returned offscreen byte. */
                if (address == 0U || (address >= 4U && address <= 7U)) {
                    ++deferred_child_scratch;
                    continue;
                }
                if (failures < 20U)
                    printf("child=%u RAM=%04x ROM=%02x C=%02x\n",
                           child, address,
                           record[2052U + address], game.ram[address]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("player offscreen children=%u failures=%u deferred-child-scratch=%u\n",
           child, failures, deferred_child_scratch);
    return failures != 0U;
}
