#include "core/world/world.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    static struct mysmb_game g;
    unsigned char header[8], expected[2048];
    unsigned int i, failures;
    FILE *f;
    if (argc != 2) return 64;
    f = fopen(argv[1], "rb"); if (f == NULL) return 65;
    if (fread(header, 1, 8, f) != 8 || memcmp(header, "MS9P\1", 5) != 0) return 66;
    memset(&g, 0, sizeof(g));
    if (fread(g.ram, 1, 2048, f) != 2048 ||
        fread(expected, 1, 2048, f) != 2048 || fgetc(f) != EOF) return 66;
    fclose(f);
    switch (header[5]) {
    case 0U:
        if (header[6] < 9U) return 66;
        mysmb_world_impose_gravity_block(&g, (mysmb_u8)(header[6] - 9U)); break;
    case 1U: mysmb_world_move_platform_vertically(&g, header[6], 0U); break;
    case 2U: mysmb_world_move_platform_vertically(&g, header[6], 1U); break;
    case 3U: mysmb_world_impose_gravity(&g, header[6], header[7]); break;
    default: return 66;
    }
    failures = 0U;
    for (i = 0U; i < 2048U; ++i) {
        if (i >= 0x100U && i < 0x200U && (i < 0x133U || i > 0x139U)) continue;
        if (g.ram[i] != expected[i]) {
            printf("%04x original=%02x native=%02x\n", i,
                   (unsigned int)expected[i], (unsigned int)g.ram[i]);
            ++failures;
        }
    }
    return failures ? 1 : 0;
}
