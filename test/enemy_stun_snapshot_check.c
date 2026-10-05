#include "core/world/world.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned int i, failures;
    FILE *file;
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1U, 8U, file) != 8U || memcmp(header, "MSsP\1", 5U) ||
        fread(game.ram, 1U, 2048U, file) != 2048U ||
        fread(expected, 1U, 2048U, file) != 2048U || fgetc(file) != EOF) return 66;
    fclose(file);
    game.area_prg = mysmb_local_prg; game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    if (header[5] == 1U) mysmb_world_stun_enemy(&game, header[6], header[7]);
    else if (header[5] == 2U) mysmb_world_set_stun(&game, header[6]);
    else return 67;
    failures = 0U;
    for (i = 0U; i < 2048U; ++i) {
        if (i >= 0x100U && i < 0x200U && (i < 0x109U || i > 0x139U)) continue;
        if (game.ram[i] != expected[i]) {
            printf("%04x original=%02x native=%02x\n", i,
                (unsigned int)expected[i], (unsigned int)game.ram[i]); ++failures;
        }
    }
    return failures ? 1 : 0;
}
