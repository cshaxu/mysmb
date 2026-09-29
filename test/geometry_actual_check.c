#include "game/world/world.h"
#include <stdio.h>
#include <string.h>

/* Replays only natural original-ROM collision-child records.  The recorder
 * stores each child RAM image before and after the original call; this check
 * compares the shared C owner directly, without replaying a caller result. */
static unsigned char record[4098];
static unsigned int checked;

static int check_one(FILE *file)
{
    unsigned char header[8];
    unsigned int index;
    unsigned int count;
    unsigned int child_id;
    unsigned int expected_id;
    unsigned short first;
    unsigned short second;
    struct mysmb_game game;
    mysmb_u8 carry;

    if (fread(header, 1U, 8U, file) != 8U) return 0;
    count = header[5];
    if (count > 64U) return 0;
    if (memcmp(header, "MS~C\1", 5U) == 0) expected_id = 3U;
    else if (memcmp(header, "MS!C\1", 5U) == 0) expected_id = 2U;
    else if (memcmp(header, "MS@C\1", 5U) == 0) expected_id = 3U;
    else return 0;

    for (index = 0U; index < count; ++index) {
        if (fread(record, 1U, sizeof(record), file) != sizeof(record)) return 0;
        child_id = record[0] & 0x7fU;
        if (child_id != expected_id) continue;
        memcpy(game.ram, record + 2U, 2048U);
        second = (unsigned short)(0x04acU + record[1]);
        if (header[2] == '~') first = 0x04acU;
        else if (header[2] == '!')
            first = (unsigned short)(0x04acU + game.ram[1U] * 4U + 4U);
        else first = 0x04acU;
        carry = mysmb_world_boxes_collide(&game, first, second);
        if (carry != (mysmb_u8)(record[0] >> 7U) ||
            memcmp(game.ram, record + 2050U, 2048U) != 0) return 0;
        ++checked;
    }
    return fgetc(file) == EOF;
}

int main(int argc, char **argv)
{
    int index;
    FILE *file;

    if (argc < 2) return 64;
    for (index = 1; index < argc; ++index) {
        file = fopen(argv[index], "rb");
        if (file == NULL || !check_one(file)) {
            if (file != NULL) fclose(file);
            return 1;
        }
        if (fclose(file) != 0) return 1;
    }
    if (checked == 0U) return 1;
    printf("geometry actual records: %u\n", checked);
    return 0;
}
