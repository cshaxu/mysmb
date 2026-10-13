#include "core/player/terrain_children.h"
#include "core/area.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;
static void compare(const unsigned char *actual, const unsigned char *expected)
{
    unsigned int i;
    for (i = 0U; i < 2048U; ++i) {
        if (i >= 0x100U && i < 0x200U && (i < 0x109U || i > 0x139U)) continue;
        if (actual[i] != expected[i]) {
            printf("%04x original=%02x native=%02x\n", i,
                (unsigned int)expected[i], (unsigned int)actual[i]);
            ++failures;
        }
    }
}
#ifdef MYSMB_CALLER_CHECK
static unsigned char child[4098];
static unsigned int count, calls;
void mysmb_area_kill_enemies(struct mysmb_game *game, mysmb_u8 id)
{
    ++calls;
    if (count != 1U || calls != 1U || child[0] != 1U || child[1] != id) {
        ++failures; return;
    }
    compare(game->ram, child + 2U);
    memcpy(game->ram, child + 2050U, 2048U);
}
#endif

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    struct mysmb_player_terrain terrain;
    unsigned char header[8];
    FILE *file;
#ifdef MYSMB_CHILD_CHECK
    static unsigned char record[4098];
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS&C\1", 5) ||
        header[5] > 1U) return 66;
    if (header[5] == 0U) {
        if (fgetc(file) != EOF) return 66;
        fclose(file); return 0;
    }
    if (fread(record, 1, 4098, file) != 4098 || fgetc(file) != EOF ||
        record[0] != 1U) return 66;
    fclose(file);
    memcpy(game.ram, record + 2U, 2048U);
    mysmb_area_kill_enemies(&game, record[1]);
    compare(game.ram, record + 2050U);
    printf("child failures=%u\n", failures);
    return failures ? 1 : 0;
#endif
#ifdef MYSMB_CALLER_CHECK
    if (argc != 3) return 64;
    file = fopen(argv[2], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS&C\1", 5) ||
        header[5] > 1U) return 66;
    count = header[5];
    if (fread(child, 4098, count, file) != count || fgetc(file) != EOF) return 66;
    fclose(file);
#else
    if (argc != 2) return 64;
#endif
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS&P\1", 5) ||
        fread(game.ram, 1, 2048, file) != 2048 ||
        fread(expected, 1, 2048, file) != 2048 || fgetc(file) != EOF) return 66;
    fclose(file);
    game.area_prg = mysmb_local_prg; game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    terrain.metatile = header[7]; terrain.contact_low_nibble = game.ram[4U];
    terrain.block_address_low = game.ram[6U]; terrain.block_row_offset = game.ram[2U];
    (void)mysmb_player_handle_climbing(&game, &terrain);
    compare(game.ram, expected);
#ifdef MYSMB_CALLER_CHECK
    if (calls != count) ++failures;
#endif
    return failures ? 1 : 0;
}
