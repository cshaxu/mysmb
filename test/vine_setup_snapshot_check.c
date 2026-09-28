#include "game/objects.h"
#include <stdio.h>
#include <string.h>

/* Actual leaf execution: no reference child substitutions. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned int i, failures;
    FILE *input;
    if (argc != 2) return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1, 8, input) != 8 || memcmp(header, "MSVP\1", 5) != 0 ||
        header[5] != 1U || header[6] >= 6U || header[7] >= 2U ||
        fread(game.ram, 1, 2048, input) != 2048 ||
        fread(expected, 1, 2048, input) != 2048 || fgetc(input) != EOF) {
        fclose(input); return 66;
    }
    fclose(input);
    mysmb_objects_start_vine(&game, header[6], header[7]);
    failures = 0U;
    for (i = 8U; i < 2048U; ++i) {
        if (i >= 0x100U && i < 0x200U && (i < 0x133U || i > 0x139U)) continue;
        if (game.ram[i] != expected[i]) {
            printf("%04x original=%02x native=%02x\n", i,
                   (unsigned int)expected[i], (unsigned int)game.ram[i]);
            ++failures;
        }
    }
    printf("height-data=%02x%02x\n", (unsigned int)mysmb_vine_height_data[0],
           (unsigned int)mysmb_vine_height_data[1]);
    return failures != 0U;
}
