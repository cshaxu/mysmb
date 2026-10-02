#include "game/player.h"
#include "game/player/terrain_children.h"
#include "game/objects.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

/* Independently execute each real child from its untouched original input.
 * No original return state is installed into this execution. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char record[4098];
    unsigned char header[8];
    struct mysmb_player_terrain terrain;
    unsigned int i, n, id, failures, abi, total_failures;
    mysmb_u8 index;
    FILE *file;
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MS$C\1", 5) ||
        header[5] > 16U) return 66;
    game.area_prg = mysmb_local_prg; game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    total_failures = 0U;
    for (n = 0U; n < header[5]; ++n) {
        if (fread(record, 1, 4098, file) != 4098) return 66;
        memcpy(game.ram, record + 2U, 2048U);
        game.ppu_control_0 = game.ram[0x778U];
        id = record[0] & 0x7fU; abi = 0U;
        if (id <= 3U) {
            index = record[1];
            memset(&terrain, 0, sizeof(terrain));
            (void)mysmb_world_query_player_probe(&game, &index,
                (mysmb_u8)(id - 1U), &terrain);
            /* The original A return is the metatile itself.  A zero tile is
             * a successful empty probe, not an unavailable C call. */
            if (index != (mysmb_u8)(record[1] + (id == 2U ? 1U : 0U)) ||
                terrain.metatile != record[2053U] ||
                terrain.contact_low_nibble != record[2054U] ||
                terrain.block_address_low != record[2056U] ||
                terrain.block_row_offset != record[2052U]) abi = 1U;
        }
        else if (id == 4U) {
            if (mysmb_player_coin_metatile(&game, record[1]) !=
                (mysmb_u8)(record[0] >> 7U)) abi = 1U;
        }
        else if (id == 5U)
            (void)mysmb_objects_start_head_bump(&game, record[1], game.ram[6U], game.ram[2U]);
        else if (id == 6U)
            mysmb_objects_collect_coin(&game, game.ram[6U], game.ram[2U]);
        else if (id == 7U)
            mysmb_player_handle_axe_metatile(&game, game.ram[6U], game.ram[2U]);
        else if (id == 8U) {
            terrain.metatile = record[1]; terrain.contact_low_nibble = game.ram[4U];
            terrain.block_address_low = game.ram[6U]; terrain.block_row_offset = game.ram[2U];
            (void)mysmb_player_handle_climbing(&game, &terrain);
        }
        else if (id == 9U) mysmb_player_land_jumpspring(&game, record[1]);
        else if (id == 10U)
            (void)mysmb_player_handle_vertical_pipe(&game, game.ram[1U], game.ram[0U]);
        else if (id == 11U) mysmb_player_impede_move(&game, record[1]);
        else return 66;
        failures = abi;
        printf("%u abi=%u", id, abi);
        for (i = 0U; i < 2048U; ++i) {
            if (i >= 0x100U && i < 0x200U && (i < 0x109U || i > 0x139U)) continue;
            if (game.ram[i] != record[2050U + i]) {
                ++failures;
                printf(" %04x:%02x/%02x", i,
                    (unsigned int)record[2050U + i], (unsigned int)game.ram[i]);
            }
        }
        printf(" failures=%u\n", failures);
        total_failures += failures;
    }
    if (fgetc(file) != EOF) return 66;
    fclose(file);
    return total_failures == 0U ? 0 : 1;
}
