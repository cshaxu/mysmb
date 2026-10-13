#include "core/objects.h"
#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Original RunSmallPlatform -> DrawSmallPlatform child records. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    unsigned char header[8], record[4098];
    unsigned int call, count, matched, i;
    FILE *input;
    if (argc != 2) return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1U, 8U, input) != 8U ||
        memcmp(header, "MS9C\1", 5U) != 0) {
        fclose(input);
        return 66;
    }
    count = header[5];
    matched = 0U;
    for (call = 0U; call < count; ++call) {
        if (fread(record, 1U, sizeof(record), input) != sizeof(record)) {
            fclose(input);
            return 66;
        }
        if (record[0] != 10U) continue;
        ++matched;
        memcpy(game.ram, record + 2U, 2048U);
        mysmb_objects_draw_small_platform(&game, record[1]);
        for (i = 0U; i < 2048U; ++i) {
            if (i >= 0x100U && i < 0x200U) continue;
            if (game.ram[i] != record[2050U + i]) {
                fprintf(stderr, "call=%u ram=%04x ROM=%02x C=%02x\n",
                        call, i, record[2050U + i], game.ram[i]);
                fclose(input);
                return 1;
            }
        }
    }
    if (fgetc(input) != EOF) {
        fclose(input);
        return 66;
    }
    fclose(input);
    printf("matched=%u\n", matched);
    return matched == 0U ? 2 : 0;
}
