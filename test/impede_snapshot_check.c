#include "game/player.h"
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
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS*P\1", 5) ||
        fread(game.ram, 1, 2048, file) != 2048 ||
        fread(expected, 1, 2048, file) != 2048 || fgetc(file) != EOF) return 66;
    fclose(file);
    mysmb_player_impede_move(&game, game.ram[0U]);
    failures = 0U;
    for (i = 0U; i < 2048U; ++i) {
        if (game.ram[i] != expected[i]) {
            printf("%04x original=%02x native=%02x\n", i,
                (unsigned int)expected[i], (unsigned int)game.ram[i]);
            ++failures;
        }
    }
    return failures ? 1 : 0;
}
