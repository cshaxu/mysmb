#include "game/world/world.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    unsigned char header[8];
    unsigned char record[4098];
    struct mysmb_player_terrain terrain;
    FILE *file;
    mysmb_u8 index;
    unsigned int checked = 0U;
    unsigned int failures = 0U;
    mysmb_u8 probe;

    if (argc != 2) return 64;
    file = fopen(argv[1], "rb");
    if (file == 0) return 65;
    if (fread(header, 1U, sizeof(header), file) != sizeof(header) ||
        memcmp(header, "MS$C\1", 5U) != 0 || header[5] > 16U) return 66;
    game.area_prg = mysmb_local_prg;
    game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    while (checked < header[5]) {
        if (fread(record, 1U, sizeof(record), file) != sizeof(record)) return 66;
        probe = (mysmb_u8)(record[0] & 0x7fU);
        if (probe > 3U) {
            ++checked;
            continue;
        }
        memcpy(game.ram, record + 2U, sizeof(game.ram));
        index = record[1U];
        memset(&terrain, 0, sizeof(terrain));
        (void)mysmb_world_query_player_probe(&game, &index,
            (mysmb_u8)(probe - 1U), &terrain);
        if (index != (mysmb_u8)(record[1U] + (probe == 2U ? 1U : 0U)) ||
            terrain.metatile != record[2053U] || terrain.contact_low_nibble != record[2054U] ||
            terrain.block_address_low != record[2056U] || terrain.block_row_offset != record[2052U] ||
            game.ram[2U] != record[2052U] || game.ram[3U] != record[2053U] ||
            game.ram[4U] != record[2054U] || game.ram[5U] != record[2055U] ||
            game.ram[6U] != record[2056U] || game.ram[7U] != record[2057U]) ++failures;
        ++checked;
    }
    if (fgetc(file) != EOF) return 66;
    fclose(file);
    printf("records=%u failures=%u\n", checked, failures);
    return failures != 0U;
}
