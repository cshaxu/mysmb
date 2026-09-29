#include "game/oam/oam.h"
#include "game/enemy/firebar.h"
#include <stdio.h>
#include <string.h>

/* Compare a naturally reached original-ROM child call with the shared C
 * graphics leaf. The input is the recorder's ignored MSFC/MShC child stream. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    unsigned char header[8];
    unsigned char record[4098];
    unsigned int i, call, count, matched;
    int kind;
    FILE *input;
    if (argc != 3) return 64;
    kind = argv[2][0] == 'f' ? 1 : argv[2][0] == 'b' ? 2 :
           argv[2][0] == 'w' ? 3 : 0;
    if (kind == 0 || argv[2][1] != '\0') return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1U, 8U, input) != 8U ||
        (kind == 1 && memcmp(header, "MSFC\1", 5U) != 0) ||
        (kind == 2 && memcmp(header, "MShC\1", 5U) != 0) ||
        (kind == 3 && memcmp(header, "MSoC\1", 5U) != 0)) {
        fclose(input);
        return 66;
    }
    count = header[5];
    matched = 0U;
    for (call = 0U; call < count; ++call) {
        if (fread(record, 1U, sizeof(record), input) != sizeof(record)) {
            fclose(input);
            return 66;
        }
        if ((kind == 1 && record[0] != 8U && record[0] != 9U) ||
            (kind == 2 && record[0] != 4U) ||
            (kind == 3 && record[0] != 2U)) continue;
        ++matched;
        memcpy(game.ram, record + 2U, 2048U);
        if (kind == 3)
            mysmb_oam_draw_fireworks_explosion(
                &game, game.ram[0x0058U + record[1]],
                game.ram[0x06e5U + record[1]]);
        else if (kind == 2)
            (void)mysmb_oam_draw_firebar(&game, record[1]);
        else if (record[0] == 8U)
            mysmb_oam_draw_fireball(&game, record[1]);
        else
            mysmb_oam_draw_fireball_explosion(&game, record[1]);
        for (i = 0U; i < 2048U; ++i) {
            if (i >= 0x100U && i < 0x200U) continue;
            if (game.ram[i] != record[2050U + i]) {
                fprintf(stderr, "call=%u id=%u ram=%04x ROM=%02x C=%02x\n",
                        call, record[0], i, record[2050U + i], game.ram[i]);
                fclose(input);
                return 1;
            }
        }
    }
    if (fgetc(input) != EOF) {
        fclose(input);
        return 66;
    }
    fclose(input);
    printf("matched=%u kind=%c\n", matched, argv[2][0]);
    return matched == 0U ? 2 : 0;
}
