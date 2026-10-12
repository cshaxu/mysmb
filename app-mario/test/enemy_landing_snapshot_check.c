#include "core/enemy/background.h"
#include "core/world/world.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char record[4112];
    unsigned char header[8];
    unsigned int i, failures, target, slot;
    FILE *file;
    if (argc != 3) return 64;
    target = (unsigned int)strtoul(argv[2], 0, 16);
    if (target != 0xe067U && target != 0xe0e2U) return 64;
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1U, 8U, file) != 8U || memcmp(header, "MS!B\1", 5U)) return 66;
    failures = 0U;
    for (i = 1U; i <= header[5]; ++i) {
        if (fread(record, 1U, sizeof(record), file) != sizeof(record)) return 66;
        if ((unsigned int)record[0] + 256U * record[1] != target) continue;
        slot = record[3];
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record + 16U, 2048U);
        game.area_prg = mysmb_local_prg; game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
        if (target == 0xe067U) {
            struct mysmb_enemy_terrain terrain;
            memset(&terrain, 0, sizeof(terrain));
            terrain.contact_low_nibble = game.ram[4U];
            mysmb_objects_enemy_land_from_probe(&game, (mysmb_u8)slot, &terrain);
        } else mysmb_objects_enemy_no_ground(&game, (mysmb_u8)slot);
        if (game.ram[0x001eU + slot] != record[2064U + 0x001eU + slot]) ++failures;
    }
    fclose(file);
    return failures ? 1 : 0;
}
