#include "core/enemy/distance.h"
#include <stdio.h>
#include <string.h>

#define RECORD_BYTES 4112U

int main(int argc, char **argv)
{
    static const unsigned char magic[5] = { 'M', 'S', 'P', 'D', 1U };
    struct mysmb_game game;
    unsigned char header[8];
    unsigned char record[RECORD_BYTES];
    unsigned int index;
    FILE *file;
    mysmb_u8 slot;
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb");
    if (file == NULL) return 65;
    if (fread(header, 1U, sizeof(header), file) != sizeof(header) ||
        memcmp(header, magic, sizeof(magic)) != 0 || header[5] != 4U) {
        fclose(file);
        return 66;
    }
    for (index = 0U; index < 4U; ++index) {
        if (fread(record, 1U, sizeof(record), file) != sizeof(record) ||
            record[0] != 0x43U || record[1] != 0xe1U || record[11] != index ||
            record[12] != 1U || record[13] != 0x80U) {
            fclose(file);
            return 67;
        }
        slot = record[3];
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record + 16U, 2048U);
        if (mysmb_enemy_player_difference(&game, slot) != record[6] ||
            game.ram[0U] != record[2064U]) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
