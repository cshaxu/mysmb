#include "game/area.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Compare a naturally reached original DrawPlayer_Intermediate child
 * with the shared C owner. Input ROM and raw child record are local only. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    unsigned char header[8], record[4098];
    FILE *input;
    unsigned int i, failures;
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
        memcmp(header, "MSIC\1", 5U) != 0 || header[5] != 1U ||
        fread(record, 1U, sizeof(record), input) != sizeof(record) ||
        record[0] != 1U || fgetc(input) != EOF) return 66;
    fclose(input);
    memcpy(game.ram, record + 2U, 2048U);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    mysmb_oam_draw_intermediate_player(&game);
    failures = 0U;
    for (i = 0U; i < 2048U; ++i) {
        if (i >= 0x100U && i < 0x200U) continue;
        if (game.ram[i] != record[2050U + i]) {
            if (failures < 24U)
                printf("RAM=%04x ROM=%02x C=%02x\n", i,
                       record[2050U + i], game.ram[i]);
            ++failures;
        }
    }
    printf("intermediate child failures=%u\n", failures);
    return failures != 0U;
}
