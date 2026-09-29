#include "game/enemy/distance.h"
#include "game/objects.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Replays retained owner-local original child records.  The input record is
 * deliberately external: it is validation evidence, not game content. */
static int read_record(FILE *file, unsigned char *record)
{
    return fread(record, 1U, 4112U, file) == 4112U;
}

int main(int argc, char **argv)
{
    struct mysmb_game game;
    unsigned char header[8];
    unsigned char record[4112];
    unsigned int index;
    unsigned int count;
    unsigned int difference_count;
    unsigned int hammer_count;
    unsigned int argument;
    unsigned int pc;
    mysmb_u8 slot;
    FILE *file;

    if (argc < 2) return 64;
    difference_count = 0U;
    hammer_count = 0U;
    for (argument = 1U; argument < (unsigned int)argc; ++argument) {
        file = fopen(argv[argument], "rb");
        if (file == 0) return 65;
        if (fread(header, 1U, 8U, file) != 8U ||
            memcmp(header, "MS!B\1", 5U) != 0) {
            fclose(file);
            return 66;
        }
        count = header[5];
        for (index = 0U; index <= count; ++index) {
            if (!read_record(file, record)) {
                fclose(file);
                return 66;
            }
            pc = (unsigned int)record[0] + 256U * record[1];
            slot = record[3];
            if (pc == 0xe143U) {
                memset(&game, 0, sizeof(game));
                memcpy(game.ram, record + 16U, 2048U);
                if (mysmb_enemy_player_difference(&game, slot) != record[6] ||
                    game.ram[0U] != record[2064U]) {
                    fclose(file);
                    return 1;
                }
                ++difference_count;
            }
            if (pc == 0xe185U) {
                memset(&game, 0, sizeof(game));
                memcpy(game.ram, record + 16U, 2048U);
                mysmb_objects_step_hammer_terrain(&game, slot);
                if (game.ram[0x001eU + slot] != record[2064U + 0x001eU + slot] ||
                    game.ram[0x00a0U + slot] != record[2064U + 0x00a0U + slot] ||
                    game.ram[0x0434U + slot] != record[2064U + 0x0434U + slot] ||
                    game.ram[0x00cfU + slot] != record[2064U + 0x00cfU + slot]) {
                    fclose(file);
                    return 2;
                }
                ++hammer_count;
            }
        }
        fclose(file);
    }
    return difference_count == 0U || hammer_count == 0U;
}
