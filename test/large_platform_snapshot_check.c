#include "game/objects.h"
#include <stdio.h>
#include <string.h>

/* Local original-ROM call records contain a normal RunLargePlatform route.
 * Each child entry records its id/slot and complete RAM before/after images.
 * Child id 14 is DrawLargePlatform; this checker deliberately compares only
 * that real child boundary, leaving its caller and sibling owners independent. */
static int mysmb_check_file(const char *path, unsigned int *matches)
{
    unsigned char header[8];
    unsigned char record[4098];
    FILE *file;
    unsigned int index;

    file = fopen(path, "rb");
    if (file == NULL) return 1;
    if (fread(header, 1U, 8U, file) != 8U ||
        header[0] != 'M' || header[1] != 'S' || header[3] != 'C' ||
        header[4] != 1U ||
        (header[2] != '9' && header[2] != 'P') ||
        header[5] > 16U) {
        fclose(file);
        return 2;
    }
    for (index = 0U; index < header[5]; ++index) {
        struct mysmb_game game;
        unsigned int address;

        if (fread(record, 1U, sizeof(record), file) != sizeof(record)) {
            fclose(file);
            return 3;
        }
        if (record[0] != 14U) continue;
        memcpy(game.ram, record + 2U, sizeof(game.ram));
        mysmb_objects_draw_large_platform(&game, record[1]);
        for (address = 0U; address < sizeof(game.ram); ++address) {
            /* The source child boundary includes JSR/RTS stack traffic;
             * portable C deliberately has no emulated 6502 stack. */
            if (address >= 0x0100U && address < 0x0200U) continue;
            if (game.ram[address] != record[2050U + address]) {
                fprintf(stderr, "%s slot=%u address=%04x original=%02x native=%02x\n",
                    path, (unsigned int)record[1], address,
                    (unsigned int)record[2050U + address],
                    (unsigned int)game.ram[address]);
                fclose(file);
                return 4;
            }
        }
        ++*matches;
    }
    if (fgetc(file) != EOF) {
        fclose(file);
        return 5;
    }
    fclose(file);
    return 0;
}

int main(int argc, char **argv)
{
    unsigned int file_index;
    unsigned int matches;

    if (argc < 2) return 64;
    matches = 0U;
    for (file_index = 1U; file_index < (unsigned int)argc; ++file_index) {
        int result;

        result = mysmb_check_file(argv[file_index], &matches);
        if (result != 0) return result;
    }
    return matches != 0U ? 0 : 65;
}
