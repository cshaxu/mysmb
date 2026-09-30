#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Original CPU X/Y and full non-stack RAM/OAM at DrawSpriteObject entry
 * and stack-derived return.  Owner-ROM records remain under build/. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    unsigned char header[8];
    unsigned char record[4100];
    FILE *input;
    unsigned int child;
    unsigned int address;
    unsigned int failures;
    if (argc != 2) return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1U, 8U, input) != 8U ||
        memcmp(header, "MSSO\1", 5U) != 0 ||
        header[5] == 0U || header[5] > 8U) return 66;
    failures = 0U;
    for (child = 0U; child < header[5]; ++child) {
        mysmb_u8 x;
        mysmb_u8 y;
        if (fread(record, 1U, sizeof(record), input) != sizeof(record))
            return 66;
        x = record[0];
        y = record[1];
        memcpy(game.ram, record + 4U, 2048U);
        mysmb_oam_draw_sprite_object(&game, &x, &y);
        if (x != record[2] || y != record[3]) {
            if (failures < 20U)
                printf("child=%u X/Y ROM=%02x/%02x C=%02x/%02x\n",
                       child, record[2], record[3], x, y);
            ++failures;
        }
        for (address = 0U; address < 2048U; ++address) {
            if (address >= 0x100U && address < 0x200U) continue;
            if (game.ram[address] != record[2052U + address]) {
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
    printf("sprite row children=%u failures=%u\n", child, failures);
    return failures != 0U;
}
