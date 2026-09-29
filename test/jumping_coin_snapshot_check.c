#include "game/objects.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;

static void compare_ram(const unsigned char *expected,
    const unsigned char *actual)
{
    unsigned int i;
    for (i = 0U; i < 2048U; ++i) {
        /* The original JSR/RTS uses the 6502 stack; native C has no
         * corresponding RAM stack traffic. */
        if (i >= 0x100U && i < 0x200U) continue;
        if (expected[i] != actual[i]) ++failures;
    }
}

static int check_file(const char *path, unsigned int *matches)
{
    unsigned char header[8], record[4098];
    unsigned int i, count;
    FILE *input;
    struct mysmb_game game;

    input = fopen(path, "rb");
    if (input == NULL) return 1;
    if (fread(header, 1U, 8U, input) != 8U ||
        memcmp(header, "MSUC\1", 5U) != 0 || header[6] != 0U ||
        header[7] != 0U) { fclose(input); return 2; }
    count = header[5];
    for (i = 0U; i < count; ++i) {
        if (fread(record, 1U, sizeof(record), input) != sizeof(record)) {
            fclose(input); return 2;
        }
        if (record[0] == 6U) {
            memset(&game, 0, sizeof(game));
            memcpy(game.ram, record + 2U, 2048U);
            mysmb_objects_draw_jump_coin(&game, record[1]);
            compare_ram(record + 2050U, game.ram);
            ++*matches;
        }
    }
    if (fgetc(input) != EOF) { fclose(input); return 2; }
    fclose(input);
    return 0;
}

int main(int argc, char **argv)
{
    unsigned int i, matches;
    int result;
    if (argc < 2) return 64;
    matches = 0U;
    for (i = 1U; i < (unsigned int)argc; ++i) {
        result = check_file(argv[i], &matches);
        if (result != 0) return result;
    }
    printf("jumping-coin-snapshot records=%u %s\n", matches,
        failures == 0U ? "pass" : "fail");
    return failures != 0U || matches == 0U ? 1 : 0;
}
