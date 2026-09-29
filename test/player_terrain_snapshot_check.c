#include "game/player.h"
#include "game/player/terrain_children.h"
#include "game/objects.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

static unsigned char records[16][4098];
static unsigned int count, calls, failures;
static void compare(const unsigned char *actual, const unsigned char *expected)
{
    unsigned int i;
    for (i = 0U; i < 2048U; ++i) {
        if (i >= 0x100U && i < 0x200U && (i < 0x109U || i > 0x139U)) continue;
        if (actual[i] != expected[i]) {
            printf("call %u RAM %04x original=%02x native=%02x\n", calls,
                i, (unsigned int)expected[i], (unsigned int)actual[i]);
            ++failures;
        }
    }
}
/* Compare complete child RAM and every consumed register argument before
 * installing that child's original return. This proves only the caller;
 * enemy_loop_actual_check separately runs the real native descendants. */
static mysmb_u8 child(struct mysmb_game *game, unsigned int id, mysmb_u8 arg)
{
    unsigned char *record;
    if (calls >= count) { ++failures; return 0U; }
    record = records[calls++];
    if ((record[0] & 0x7fU) != id ||
        ((id <= 5U || id == 8U || id == 9U || id == 11U) && record[1] != arg)) {
        printf("child %u original=%u/%u native=%u/%u\n", calls,
            record[0] & 0x7fU, (unsigned int)record[1], id, (unsigned int)arg);
        ++failures;
    }
    compare(game->ram, record + 2U);
    memcpy(game->ram, record + 2050U, 2048U);
    return (mysmb_u8)(record[0] >> 7U);
}
mysmb_u8 mysmb_world_query_player_probe(struct mysmb_game *game,
    mysmb_u8 *index, mysmb_u8 entry, struct mysmb_player_terrain *terrain)
{
    (void)child(game, (unsigned int)entry + 1U, *index);
    if (entry == MYSMB_TERRAIN_FEET) ++*index;
    terrain->metatile = game->ram[3U];
    terrain->contact_low_nibble = game->ram[4U];
    terrain->block_address_low = game->ram[6U];
    terrain->block_row_offset = game->ram[2U];
    return 1U;
}
mysmb_u8 mysmb_player_coin_metatile(struct mysmb_game *game, mysmb_u8 tile)
{ return child(game, 4U, tile); }
/* GetMTileAttrib changes only registers; this classifier has no RAM effects.
 * The bound original table supplies all four groups, without fixture copies. */
mysmb_u8 mysmb_world_is_climbable(const struct mysmb_game *game, mysmb_u8 tile)
{ (void)game; return tile >= mysmb_local_prg[0x5f96U + (tile >> 6U)] ? 1U : 0U; }
mysmb_u8 mysmb_world_is_solid(const struct mysmb_game *game, mysmb_u8 tile)
{ (void)game; return tile >= mysmb_local_prg[0x5f8bU + (tile >> 6U)] ? 1U : 0U; }
static void coordinates(struct mysmb_game *game, mysmb_u8 low, mysmb_u8 row)
{
    if (low != game->ram[6U] || row != game->ram[2U]) ++failures;
}
mysmb_u8 mysmb_objects_start_head_bump(struct mysmb_game *game,
    mysmb_u8 tile, mysmb_u8 low, mysmb_u8 row)
{
    coordinates(game, low, row);
    (void)child(game, 5U, tile);
    return 1U;
}
void mysmb_objects_collect_coin(struct mysmb_game *game,
    mysmb_u8 low, mysmb_u8 row)
{
    coordinates(game, low, row);
    (void)child(game, 6U, 0U);
}
void mysmb_player_handle_axe_metatile(struct mysmb_game *game,
    mysmb_u8 low, mysmb_u8 row)
{
    coordinates(game, low, row);
    (void)child(game, 7U, 0U);
}
mysmb_u8 mysmb_player_handle_climbing(struct mysmb_game *game,
    const struct mysmb_player_terrain *terrain)
{
    coordinates(game, terrain->block_address_low, terrain->block_row_offset);
    if (terrain->contact_low_nibble != game->ram[4U]) ++failures;
    (void)child(game, 8U, terrain->metatile);
    return 1U;
}
void mysmb_player_land_jumpspring(struct mysmb_game *game, mysmb_u8 tile)
{ (void)child(game, 9U, tile); }
mysmb_u8 mysmb_player_handle_vertical_pipe(struct mysmb_game *game,
    mysmb_u8 left, mysmb_u8 right)
{
    if (left != game->ram[1U] || right != game->ram[0U]) ++failures;
    (void)child(game, 10U, 0U);
    return 0U;
}
void mysmb_player_impede_move(struct mysmb_game *game, mysmb_u8 side)
{ (void)child(game, 11U, side); }

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    FILE *file;
    if (argc != 3) return 64;
    file = fopen(argv[2], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS$C\1", 5) ||
        header[5] > 16U) return 66;
    count = header[5];
    if (fread(records, 4098, count, file) != count || fgetc(file) != EOF) return 66;
    fclose(file); file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS$P\1", 5) ||
        fread(game.ram, 1, 2048, file) != 2048 ||
        fread(expected, 1, 2048, file) != 2048 || fgetc(file) != EOF) return 66;
    fclose(file);
    game.area_prg = mysmb_local_prg; game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    mysmb_player_background_collision(&game);
    compare(game.ram, expected);
    if (calls != count) ++failures;
    return failures ? 1 : 0;
}

/* Isolated terrain caller contracts. The real pure leaves are verified
 * independently by the S4 original-ROM and native predicate checks. */
mysmb_u8 mysmb_player_invisible_metatile(mysmb_u8 tile)
{ return tile == 0x5fU || tile == 0x60U ? 1U : 0U; }
mysmb_u8 mysmb_player_jumpspring_metatile(mysmb_u8 tile)
{ return tile == 0x67U || tile == 0x68U ? 1U : 0U; }
