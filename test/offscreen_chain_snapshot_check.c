#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Full RAM/OAM comparison of original GameEngine offscreen children.
 * Input records are owner-local and stay under ignored build/. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    unsigned char header[8];
    unsigned char record[4100];
    FILE *input;
    unsigned int child;
    unsigned int address;
    unsigned int failures;
    if (argc != 2) return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1U, 8U, input) != 8U ||
        memcmp(header, "MSRC\2", 5U) != 0 ||
        header[5] == 0U || header[5] > 8U) return 66;
    failures = 0U;
    for (child = 0U; child < header[5]; ++child) {
        mysmb_u8 kind;
        mysmb_u8 slot;
        if (fread(record, 1U, sizeof(record), input) != sizeof(record))
            return 66;
        kind = record[0];
        slot = record[1];
        if (kind < 7U || kind > 12U) return 66;
        if (record[2] != record[4U + 0x0008U]) {
            if (failures < 20U)
                printf("child=%u kind=%u return X=%02x ObjectOffset=%02x\n",
                       child, kind, record[2], record[4U + 0x0008U]);
            ++failures;
        }
        memcpy(game.ram, record + 4U, 2048U);
        if (kind == 7U) mysmb_oam_get_player_offscreen_bits(&game);
        else if (kind == 8U) mysmb_oam_get_fireball_offscreen_bits(&game, slot);
        else if (kind == 9U) mysmb_oam_get_bubble_offscreen_bits(&game, slot);
        else if (kind == 10U) mysmb_oam_get_misc_offscreen_bits(&game, slot);
        else if (kind == 11U) mysmb_oam_get_enemy_offscreen_bits(&game, slot);
        else mysmb_oam_get_block_offscreen_bits(&game, slot);
        for (address = 0U; address < 2048U; ++address) {
            if (address >= 0x100U && address < 0x200U) continue;
            if (game.ram[address] != record[2052U + address]) {
                if (failures < 20U)
                    printf("child=%u kind=%u slot=%u RAM=%04x ROM=%02x C=%02x\n",
                           child, kind, slot, address,
                           record[2052U + address], game.ram[address]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("offscreen children=%u failures=%u\n", child, failures);
    return failures != 0U;
}
