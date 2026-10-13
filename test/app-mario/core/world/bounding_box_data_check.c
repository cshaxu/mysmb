#include "core/world/world.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    struct mysmb_game game;
    unsigned char table[48];
    FILE *file;
    unsigned int control;
    unsigned int offset;
    const mysmb_u8 x = 0xf7U;
    const mysmb_u8 y = 0xe9U;

    if (argc != 2) return 64;
    file = fopen(argv[1], "rb");
    if (file == 0) return 65;
    if (fread(table, 1U, sizeof(table), file) != sizeof(table) ||
        fgetc(file) != EOF) {
        fclose(file);
        return 66;
    }
    fclose(file);
    for (control = 0U; control < 12U; ++control) {
        memset(&game, 0, sizeof(game));
        mysmb_world_set_bounding_box(&game, 0x04b0U, (mysmb_u8)control, x, y);
        offset = control * 4U;
        if (game.ram[0x04b0U] != (mysmb_u8)(x + table[offset]) ||
            game.ram[0x04b1U] != (mysmb_u8)(y + table[offset + 1U]) ||
            game.ram[0x04b2U] != (mysmb_u8)(x + table[offset + 2U]) ||
            game.ram[0x04b3U] != (mysmb_u8)(y + table[offset + 3U])) {
            printf("control=%u\n", control);
            return (int)(control + 1U);
        }
    }
    printf("checked=12\n");
    return 0;
}
