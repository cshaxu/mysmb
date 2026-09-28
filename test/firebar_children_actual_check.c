#include "game/enemy/firebar.h"
#include "game/objects.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

/* Diagnose each real dependency from its own original entry state. No
 * recorded child return is substituted into another native execution. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char record[4098];
    unsigned char header[8];
    unsigned int n, i, differences, failures;
    mysmb_u8 result, slot;
    FILE *file;
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb");
    if (file == NULL) return 65;
    if (fread(header, 1, 8, file) != 8 ||
        memcmp(header, "MShC\1", 5) != 0 || header[5] > 64U) return 66;
    failures = 0U;
    for (n = 0U; n < header[5]; ++n) {
        if (fread(record, 1, sizeof(record), file) != sizeof(record)) return 66;
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record + 2U, 2048U);
        game.area_prg = mysmb_local_prg;
        game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
        game.ppu_control_0 = game.ram[0x778U];
        slot = game.ram[8U];
        result = record[1];
        switch (record[0]) {
        case 1U: mysmb_firebar_offscreen(&game, slot); break;
        case 2U: result = mysmb_firebar_spin(&game, slot, game.ram[0x388U + slot]); break;
        case 3U: result = mysmb_firebar_relative(&game, slot); break;
        case 4U: result = mysmb_oam_draw_firebar(&game, record[1]); break;
        case 5U: mysmb_objects_force_injury(&game); break;
        default: return 66;
        }
        differences = 0U;
        printf("%u %u", n, (unsigned int)record[0]);
        if (result != record[1]) { printf(" return"); ++differences; }
        for (i = 0U; i < 2048U; ++i) {
            if (i >= 0x100U && i < 0x200U && (i < 0x109U || i > 0x139U)) continue;
            if (game.ram[i] != record[2050U + i]) {
                printf(" %04x", i);
                ++differences;
            }
        }
        printf("\n");
        if (differences != 0U) ++failures;
    }
    if (fgetc(file) != EOF) return 66;
    fclose(file);
    return failures != 0U ? 1 : 0;
}
