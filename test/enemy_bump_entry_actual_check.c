#include "core/objects.h"
#include <stdio.h>
#include <string.h>

#define RECORD_BYTES 4112U

static int read_record(FILE *file, unsigned char *record)
{
    return fread(record, 1U, RECORD_BYTES, file) == RECORD_BYTES;
}

int main(int argc, char **argv)
{
    static const unsigned char header_expected[5] = { 'M', 'S', 'B', 'P', 1U };
    struct mysmb_game game;
    unsigned char header[8];
    unsigned char record[RECORD_BYTES];
    unsigned int count;
    unsigned int index;
    mysmb_u8 slot;
    unsigned int endpoint;
    FILE *file;

    if (argc != 2) return 64;
    file = fopen(argv[1], "rb");
    if (file == NULL) return 65;
    if (fread(header, 1U, sizeof(header), file) != sizeof(header) ||
        memcmp(header, header_expected, sizeof(header_expected)) != 0 ||
        header[5] != 5U) {
        fclose(file);
        return 66;
    }
    count = 0U;
    for (index = 0U; index < 5U; ++index) {
        if (!read_record(file, record)) {
            fclose(file);
            return 67;
        }
        slot = record[3];
        endpoint = (unsigned int)record[12] + 256U * (unsigned int)record[13];
        if (record[0] != 0x24U || record[1] != 0xe1U || record[11] != index ||
            (index < 3U && endpoint != 0x8001U) ||
            (index >= 3U && endpoint != 0xca37U)) {
            fclose(file);
            return 68;
        }
        memset(&game, 0, sizeof(game));
        memcpy(game.ram, record + 16U, 2048U);
        mysmb_objects_bump_enemy(&game, slot);
        if (index < 3U) {
            if (game.ram[0x00ffU] != record[2064U + 0x00ffU] ||
                game.ram[0x0058U + slot] != record[2064U + 0x0058U + slot] ||
                game.ram[0x0046U + slot] != record[2064U + 0x0046U + slot]) {
                fclose(file);
                return 1;
            }
        } else {
            if (record[2064U] != 0U || record[8] != 0xfaU ||
                game.ram[0U] != 0U || game.ram[0x00ffU] != record[2064U + 0x00ffU] ||
                game.ram[0x00a0U + slot] != 0xfaU) {
                fclose(file);
                return 2;
            }
        }
        ++count;
    }
    fclose(file);
    return count == 5U ? 0 : 69;
}
