#include "game/world/world.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;

static unsigned int u16_at(const unsigned char *r, unsigned int offset)
{
    return (unsigned int)r[offset] + 256U * (unsigned int)r[offset + 1U];
}

static void check_under(const unsigned char *r)
{
    struct mysmb_game game;
    struct mysmb_enemy_terrain terrain;
    const unsigned char *after;

    memset(&game, 0, sizeof(game));
    memcpy(game.ram, r + 16U, 2048U);
    (void)mysmb_world_query_enemy_under(&game, r[3], &terrain);
    after = r + 2064U;
    /* BlockBufferChk_Enemy returns the metatile in A.  Zero is therefore a
     * successful, empty-block result rather than an unavailable C call. */
    if (terrain.metatile != r[6] ||
        terrain.block_row_offset != after[2U] ||
        terrain.contact_low_nibble != after[4U] ||
        terrain.block_address_low != after[6U] ||
        terrain.block_address != (mysmb_u16)(after[6U] +
            256U * after[7U] + after[2U])) {
        if (failures == 0U) printf("under got=%u,%u,%u,%u expected=%u,%u,%u,%u,%u\n",
            terrain.metatile, terrain.block_row_offset,
            terrain.contact_low_nibble, terrain.block_address_low, r[6], after[2U],
            after[4U], after[6U], after[7U]);
        ++failures;
    }
}

static void check_non_solid(const unsigned char *r)
{
    mysmb_u8 is_match;
    is_match = mysmb_world_enemy_metatile_is_non_solid(r[2]);
    if (is_match != (mysmb_u8)((r[9] & 2U) != 0U)) {
        if (failures == 0U) printf("non-solid a=%u got=%u p=%u\n", r[2],
            is_match, r[9]);
        ++failures;
    }
}

int main(int argc, char **argv)
{
    FILE *file;
    unsigned char header[8];
    unsigned char record[4112];
    unsigned int count;
    unsigned int index;
    unsigned int under = 0U;
    unsigned int non_solids = 0U;

    if (argc != 2) return 64;
    file = fopen(argv[1], "rb");
    if (file == 0) return 65;
    if (fread(header, 1U, 8U, file) != 8U ||
        memcmp(header, "MS!B\1", 5U) != 0) return 66;
    count = header[5];
    for (index = 0U; index <= count; ++index) {
        if (fread(record, 1U, sizeof(record), file) != sizeof(record)) return 66;
        if (u16_at(record, 0U) == 0xe1aeU) {
            check_under(record);
            ++under;
        }
        if (u16_at(record, 0U) == 0xe1b5U) {
            check_non_solid(record);
            ++non_solids;
        }
    }
    if (fgetc(file) != EOF) return 66;
    if ((under == 0U && non_solids == 0U) || failures != 0U) {
        printf("under=%u non-solids=%u failures=%u\n", under, non_solids,
               failures);
        return 1;
    }
    printf("under=%u non-solids=%u\n", under, non_solids);
    return 0;
}
