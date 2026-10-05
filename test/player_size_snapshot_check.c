#include "core/area.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Owner ROM and naturally reached size/attribute child records are local. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    unsigned char header[8], record[4098];
    FILE *input;
    unsigned int child, i, failures;
    mysmb_u8 result;
    if (argc != 3) return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1U, 8U, input) != 8U ||
        memcmp(header, "NES\032", 4U) != 0 || header[4] != 2U ||
        fseek(input, 16L, SEEK_SET) != 0 ||
        fread(prg, 1U, sizeof(prg), input) != sizeof(prg)) return 66;
    fclose(input);
    input = fopen(argv[2], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1U, 8U, input) != 8U ||
        memcmp(header, "MSSC\1", 5U) != 0 ||
        header[5] == 0U || header[5] > 8U) return 66;
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    failures = 0U;
    for (child = 0U; child < header[5]; ++child) {
        if (fread(record, 1U, sizeof(record), input) != sizeof(record) ||
            (record[0] != 1U && record[0] != 2U)) return 66;
        memcpy(game.ram, record + 2U, 2048U);
        if (record[0] == 1U) {
            result = mysmb_oam_handle_change_size(&game);
            if (result != record[1]) {
                if (failures < 24U)
                    printf("child=%u A ROM=%02x C=%02x\n", child,
                           record[1], result);
                ++failures;
            }
        }
        else {
            mysmb_oam_check_player_attributes(&game);
        }
        for (i = 0U; i < 2048U; ++i) {
            if (i >= 0x100U && i < 0x200U) continue;
            if (game.ram[i] != record[2050U + i]) {
                if (failures < 24U)
                    printf("child=%u type=%u RAM=%04x ROM=%02x C=%02x\n",
                           child, record[0], i,
                           record[2050U + i], game.ram[i]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("size/attribute children=%u failures=%u\n", child, failures);
    return failures != 0U;
}
