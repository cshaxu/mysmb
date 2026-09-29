#include "game/area.h"
#include "game/fireball/fireball.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];
    unsigned char header[8], record[4098];
    FILE *input;
    unsigned int call, count, i, failures, bubbles, players;
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
        memcmp(header, "MSBC\1", 5U) != 0) return 66;
    count = header[5];
    if (count == 0U || count > 16U) return 66;
    failures = 0U;
    bubbles = 0U;
    players = 0U;
    for (call = 0U; call < count; ++call) {
        if (fread(record, 1U, sizeof(record), input) != sizeof(record)) return 66;
        memcpy(game.ram, record + 2U, 2048U);
        mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
        if (record[0] == 1U) {
            ++bubbles;
            mysmb_fireball_draw_bubble(&game, record[1]);
        }
        else if (record[0] == 2U) {
            ++players;
            mysmb_oam_render_player(&game);
        }
        else return 67;
        for (i = 0U; i < 2048U; ++i) {
            if (i >= 0x100U && i < 0x200U) continue;
            if (game.ram[i] != record[2050U + i]) {
                if (failures < 20U)
                    printf("child=%u call=%u RAM=%04x ROM=%02x C=%02x\n",
                           record[0], call, i, record[2050U + i], game.ram[i]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) return 66;
    fclose(input);
    printf("calls=%u bubbles=%u players=%u failures=%u\n",
           count, bubbles, players, failures);
    return failures != 0U || bubbles == 0U || players == 0U;
}
