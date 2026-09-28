#include "game/player.h"
#include "game/area.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

static unsigned int compare_control(const unsigned char *entry,
                                    const unsigned char *expected)
{
    static struct mysmb_game game;
    unsigned int address, failures;
    memset(&game, 0, sizeof(game));
    memcpy(game.ram, entry, 2048U);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    game.ppu_control_0 = game.ram[0x778U];
    mysmb_player_step(&game, game.ram[0x6fcU]);
    failures = 0U;
    for (address = 8U; address < 2048U; ++address) {
        if (address >= 0x100U && address < 0x200U) continue;
        if (game.ram[address] != expected[address]) {
            printf("%04x original=%02x native=%02x\n", address,
                   (unsigned int)expected[address], (unsigned int)game.ram[address]);
            ++failures;
        }
    }
    return failures;
}

/* Actual PlayerCtrlRoutine children captured by the read-only T31 observer.
 * This executes production children and preserves every persistent mismatch. */
int main(int argc, char **argv)
{
    static unsigned char record[4098];
    unsigned char header[8];
    unsigned int count, index, failures, checked;
    FILE *input;
    if (argc != 2) return 64;
    input = fopen(argv[1], "rb");
    if (input == NULL) return 65;
    if (fread(header, 1, 8, input) != 8) { fclose(input); return 66; }
    if (memcmp(header, "MSPC\1\0\0\0", 8) == 0) {
        if (fread(record, 1, 4096U, input) != 4096U || fgetc(input) != EOF) {
            fclose(input); return 66;
        }
        fclose(input);
        return compare_control(record, record + 2048U) != 0U ? 1 : 0;
    }
    if (memcmp(header, "MSEC\1", 5) != 0 ||
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
        failures += compare_control(record + 2U, record + 2050U);
    }
    if (fgetc(input) != EOF) { fclose(input); return 66; }
    fclose(input);
    if (checked == 0U) return 3;
    return failures != 0U ? 1 : 0;
}
