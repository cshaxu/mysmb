#include "core/player/terrain_children.h"
#include "core/objects.h"
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
static unsigned char children[2][4098];
static unsigned int count, calls;
static void child(struct mysmb_game *game, unsigned int id)
{
    unsigned char *record;
    if (calls >= count) { ++failures; return; }
    record = children[calls++];
    if (record[0] != id) ++failures;
    compare(game->ram, record + 2U);
    memcpy(game->ram, record + 2050U, 2048U);
}
void mysmb_area_remove_coin_axe(struct mysmb_game *game,
    mysmb_u8 low, mysmb_u8 row)
{
    if (low != game->ram[6U] || row != game->ram[2U]) ++failures;
    child(game, 1U);
}
void mysmb_objects_give_one_coin(struct mysmb_game *game)
{ child(game, 2U); }
#endif

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    FILE *file;
#ifdef MYSMB_CHILD_CHECK
    static unsigned char record[4098];
    unsigned int i, child_count;
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS%C\1", 5) ||
        header[5] > 2U) return 66;
    child_count = header[5];
    for (i = 0U; i < child_count; ++i) {
        if (fread(record, 1, sizeof(record), file) != sizeof(record)) return 66;
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record + 2U, 2048U);
        memcpy(expected, record + 2050U, 2048U);
        game.area_prg = mysmb_local_prg;
        game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
        game.ppu.ppu_control_0 = game.ram[0x778U];
        failures = 0U;
        printf("child=%u\n", (unsigned int)record[0]);
        if (record[0] == 1U)
            mysmb_area_remove_coin_axe(&game, game.ram[6U], game.ram[2U]);
        else if (record[0] == 2U) mysmb_objects_give_one_coin(&game);
        else return 66;
        compare(game.ram, expected);
        printf("failures=%u\n", failures);
    }
    if (fgetc(file) != EOF) return 66;
    fclose(file);
    return 0;
#endif
#ifdef MYSMB_CALLER_CHECK
    if (argc != 3) return 64;
    file = fopen(argv[2], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS%C\1", 5) ||
        header[5] > 2U) return 66;
    count = header[5];
    if (fread(children, 4098, count, file) != count || fgetc(file) != EOF) return 66;
    fclose(file);
#else
    if (argc != 2) return 64;
#endif
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS%P\1", 5) ||
        fread(game.ram, 1, 2048, file) != 2048 ||
        fread(expected, 1, 2048, file) != 2048 || fgetc(file) != EOF) return 66;
    fclose(file);
    game.area_prg = mysmb_local_prg; game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    game.ppu.ppu_control_0 = game.ram[0x778U];
    if (header[5] == 1U) mysmb_objects_collect_coin(&game, game.ram[6U], game.ram[2U]);
    else if (header[5] == 2U)
        mysmb_player_handle_axe_metatile(&game, game.ram[6U], game.ram[2U]);
    else return 66;
    compare(game.ram, expected);
#ifdef MYSMB_CALLER_CHECK
    if (calls != count) ++failures;
#endif
    return failures ? 1 : 0;
}
