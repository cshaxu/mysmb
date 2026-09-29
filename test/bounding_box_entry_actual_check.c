#include "game/world/world.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;

static void compare_box(const unsigned char *before, const unsigned char *after,
                        const struct mysmb_game *game, unsigned int address)
{
    unsigned int offset;

    for (offset = 0U; offset < 4U; ++offset) {
        if (before[address + offset] != after[address + offset] &&
            game->ram[address + offset] != after[address + offset]) {
            if (failures == 0U) {
                printf("%04x original=%02x native=%02x\n", address + offset,
                       (unsigned int)after[address + offset],
                       (unsigned int)game->ram[address + offset]);
            }
            ++failures;
        }
    }
}

int main(int argc, char **argv)
{
    unsigned char header[8];
    unsigned char record[4098];
    unsigned char *before;
    unsigned char *after;
    struct mysmb_game game;
    FILE *file;
    unsigned int index;
    unsigned int count;
    unsigned int checked;
    mysmb_u8 slot;

    if (argc != 2) return 64;
    file = fopen(argv[1], "rb");
    if (file == 0) return 65;
    if (fread(header, 1U, sizeof(header), file) != sizeof(header) ||
        memcmp(header, "MSFC\1", 5U) != 0) return 66;
    count = header[5];
    checked = 0U;
    for (index = 0U; index < count; ++index) {
        if (fread(record, 1U, sizeof(record), file) != sizeof(record)) return 66;
        if (record[0] != 5U) continue;
        slot = record[1];
        if (slot >= 2U) return 66;
        before = record + 2U;
        after = record + 2050U;
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, before, 2048U);
        mysmb_world_get_fireball_bounding_box(&game, slot);
        compare_box(before, after, &game, 0x04c8U + 4U * slot);
        ++checked;
    }
    if (fgetc(file) != EOF) return 66;
    printf("checked=%u failures=%u\n", checked, failures);
    return checked == 0U || failures != 0U;
}
