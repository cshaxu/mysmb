#include "core/world/world.h"
#include "core/player/terrain_children.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char record[4112];

int main(int argc, char **argv)
{
    FILE *file;
    unsigned char header[8], tile, carry, group, result, a, x, y, p, limit;
    unsigned int n, i, pc, failures, stack1, stack2;
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1U, 8U, file) != 8U || memcmp(header, "MSMC\1", 5U)) return 66;
    game.area_prg = mysmb_local_prg; game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    failures = 0U;
    for (n = 0U; n < header[5]; ++n) {
        if (fread(record, 1U, sizeof(record), file) != sizeof(record)) return 66;
        memcpy(game.ram, record + 16U, 2048U);
        pc = record[0] + 256U * record[1]; tile = record[2];
        a = tile; x = record[3]; y = record[4]; p = record[5];
        carry = 0U; result = tile; stack1 = stack2 = 2048U;
        if (pc == 0xdf8fU || pc == 0xdf9aU) {
            group = mysmb_world_metatile_attribute(tile);
            carry = pc == 0xdf8fU ? mysmb_world_is_solid(&game, tile) :
                mysmb_world_is_climbable(&game, tile);
            limit = mysmb_local_prg[(pc == 0xdf8fU ? 0x5f8bU : 0x5f96U) + group];
            result = (unsigned char)(tile - limit); x = group; y = tile;
            /* Only the original JSR GetMTileAttrib return-address writes
             * lack a native C RAM counterpart. No other RAM is excluded. */
            stack1 = 0x100U + record[10];
            stack2 = 0x100U + (unsigned char)(record[10] - 1U);
        } else if (pc == 0xdfa1U) {
            carry = mysmb_player_coin_metatile(&game, tile);
            if (carry) { a = 1U; result = a; }
            else result = (unsigned char)(tile - 0xc3U);
        } else if (pc == 0xdfb0U) {
            x = mysmb_world_metatile_attribute(tile); y = tile;
        } else return 67;
        /* C is the live native predicate. A/X/Y and N/Z express the source
         * register contract; callers retain arguments instead of CPU state. */
        p = (unsigned char)((p & 0x7cU) | carry | (result & 0x80U) |
            (result == 0U ? 2U : 0U));
        if (record[6] != a || record[7] != x || record[8] != y || record[9] != p) {
            printf("call %u pc=%04x tile=%02x register contract mismatch\n", n, pc, tile);
            ++failures;
        }
        for (i = 0U; i < 2048U; ++i) {
            if (i == stack1 || i == stack2) continue;
            if (game.ram[i] != record[2064U + i]) {
                printf("call %u RAM %04x mismatch\n", n, i); ++failures;
            }
        }
    }
    if (fgetc(file) != EOF) return 66;
    fclose(file);
    return failures ? 1 : 0;
}
