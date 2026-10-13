#include "core/world/world.h"
#include <stdio.h>
#include <string.h>

/* Consume the original S7 child records directly, without child replay. */
static struct mysmb_game game;
static unsigned char record[4098];

int main(int argc, char **argv)
{
    FILE *f;
    unsigned char header[8];
    unsigned int file, n, i, id, checked, object_entry;
    mysmb_u8 mask, result;
    checked = 0U;
    for (file = 1U; file < (unsigned int)argc; ++file) {
        f = fopen(argv[file], "rb");
        if (!f) return 65;
        if (fread(header, 1U, 8U, f) != 8U ||
            (memcmp(header, "MS@C\1", 5U) != 0 &&
             memcmp(header, "MS~C\1", 5U) != 0)) return 66;
        object_entry = header[2] == '~';
        for (n = 0U; n < header[5]; ++n) {
            if (fread(record, 1U, sizeof(record), f) != sizeof(record))
                return 66;
            id = record[0] & (object_entry ? 127U : 15U);
            if (id != 1U && id != 2U) continue;
            memcpy(game.ram, record + 2U, 2048U);
            if (id == 1U) {
                result = mysmb_world_player_vertical_carry(&game);
                if (result != record[1]) return 1;
            } else if (object_entry) {
                result = mysmb_world_enemy_box_offset(&game);
                if (result != record[1]) return 2;
            } else {
                result = mysmb_world_enemy_box_offset_arg(&game,
                    record[1], &mask);
                /* Recorder independently checks original returned Y. */
                if (result != (mysmb_u8)(record[1] * 4U + 4U) ||
                    mask != (record[0] >> 4U)) return 2;
            }
            for (i = 0U; i < 2048U; ++i) {
                if (i >= 0x100U && i < 0x200U &&
                    (i < 0x109U || i > 0x139U)) continue;
                if (game.ram[i] != record[2050U + i]) return 3;
            }
            ++checked;
        }
        if (fgetc(f) != EOF) return 66;
        fclose(f);
    }
    printf("original preflight calls=%u passed\n", checked);
    return checked == 0U ? 67 : 0;
}
