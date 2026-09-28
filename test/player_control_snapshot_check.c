#include "game/player.h"
#include "game/area.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

/* Actual PlayerCtrlRoutine children captured by the read-only T31 observer.
 * This executes production children and preserves every persistent mismatch. */
int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char record[4098];
    unsigned char header[8];
    unsigned int count, index, address, failures, checked;
    FILE *input;
    if (argc != 2) return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1, 8, input) != 8 || memcmp(header, "MSEC\1", 5) != 0 ||
        header[5] > 4U || header[6] != 0U || header[7] != 0U) {
        fclose(input); return 66;
    }
    count = header[5]; failures = 0U; checked = 0U;
    for (index = 0U; index < count; ++index) {
        if (fread(record, 1, sizeof(record), input) != sizeof(record)) {
            fclose(input); return 66;
        }
        if (record[0] != 1U) continue;
        ++checked;
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record + 2U, 2048U);
        mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
        game.ppu_control_0 = game.ram[0x778U];
        mysmb_player_step(&game, game.ram[0x6fcU]);
        for (address = 8U; address < 2048U; ++address) {
            if (address >= 0x100U && address < 0x200U) continue;
            if (game.ram[address] != record[2050U + address]) {
                printf("%04x original=%02x native=%02x\n", address,
                       (unsigned int)record[2050U + address],
                       (unsigned int)game.ram[address]);
                ++failures;
            }
        }
    }
    if (fgetc(input) != EOF) { fclose(input); return 66; }
    fclose(input);
    if (checked == 0U) return 3;
    return failures != 0U ? 1 : 0;
}
