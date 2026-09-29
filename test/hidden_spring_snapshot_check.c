#include "game/player/terrain_children.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char record[4098];
    unsigned char header[8];
    unsigned int i, n, id, failures, abi, total_failures;
    mysmb_u8 result;
    FILE *file;
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS(C\1", 5) ||
        header[5] > 16U) return 66;
    total_failures = 0U;
    for (n = 0U; n < header[5]; ++n) {
        if (fread(record, 1, 4098, file) != 4098) return 66;
        memcpy(game.ram, record + 2U, 2048U);
        id = record[0] & 0x7fU; abi = 0U; result = 0U;
        if (id == 1U) result = mysmb_player_invisible_metatile(record[1]);
        else if (id == 2U) mysmb_player_land_jumpspring(&game, record[1]);
        else if (id == 3U) result = mysmb_player_jumpspring_metatile(record[1]);
        else return 66;
        if (id != 2U && result != (mysmb_u8)(record[0] >> 7U)) abi = 1U;
        failures = abi;
        printf("%u tile=%02x abi=%u", id, (unsigned int)record[1], abi);
        for (i = 0U; i < 2048U; ++i) {
            if (i >= 0x100U && i < 0x200U && (i < 0x109U || i > 0x139U)) continue;
            if (game.ram[i] != record[2050U + i]) {
                ++failures;
                printf(" %04x:%02x/%02x", i,
                    (unsigned int)record[2050U + i], (unsigned int)game.ram[i]);
            }
        }
        printf(" failures=%u\n", failures);
        total_failures += failures;
    }
    if (fgetc(file) != EOF) return 66;
    fclose(file);
    return total_failures ? 1 : 0;
}
