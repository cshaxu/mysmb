#include "core/objects.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;

static void compare_byte(const unsigned char *before, const unsigned char *after,
                         const struct mysmb_game *game, unsigned int address)
{
    if (before[address] != after[address] && game->ram[address] != after[address]) {
        if (failures == 0U) printf("%04x original=%02x native=%02x\n", address,
            (unsigned int)after[address], (unsigned int)game->ram[address]);
        ++failures;
    }
}

int main(int argc, char **argv)
{
    unsigned char header[8], record[4098], *before, *after;
    struct mysmb_game game;
    FILE *file;
    unsigned int count, index, checked, address;
    mysmb_u8 slot;

    if (argc != 2) return 64;
    file = fopen(argv[1], "rb");
    if (file == 0) return 65;
    if (fread(header, 1U, sizeof(header), file) != sizeof(header) ||
        memcmp(header, "MS8C\1", 5U) != 0) return 66;
    count = header[5]; checked = 0U;
    for (index = 0U; index < count; ++index) {
        if (fread(record, 1U, sizeof(record), file) != sizeof(record)) return 66;
        if (record[0] != 4U) continue;
        slot = record[1]; if (slot >= 6U) return 66;
        before = record + 2U; after = record + 2050U;
        memset(&game, 0, sizeof(game)); memcpy(game.ram, before, 2048U);
        mysmb_objects_update_enemy_bounding_box(&game, slot);
        compare_byte(before, after, &game, 0x03d8U + slot);
        address = 0x04b0U + 4U * slot;
        compare_byte(before, after, &game, address);
        compare_byte(before, after, &game, address + 1U);
        compare_byte(before, after, &game, address + 2U);
        compare_byte(before, after, &game, address + 3U);
        ++checked;
    }
    if (fgetc(file) != EOF) return 66;
    printf("checked=%u failures=%u\n", checked, failures);
    return checked == 0U || failures != 0U;
}
