#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Original BlockObjectsCore child records: require exact RAM/OAM after the
 * DrawBlock or DrawBrickChunks leaf, excluding only the 6502 CPU stack. */
static struct mysmb_game game;
static unsigned char record[4098];

int main(int argc, char **argv)
{
    unsigned int scenario, entry, byte, compared, failures, differences;
    unsigned int scenario_count, expected_calls;
    unsigned char header[8];
    char path[1024];
    FILE *stream;

    if (argc == 2) {
        if (strlen(argv[1]) + 40U >= sizeof(path)) return 64;
        scenario_count = 32U;
        expected_calls = 30U;
    } else if (argc >= 3 && strcmp(argv[1], "--files") == 0) {
        scenario_count = (unsigned int)(argc - 2);
        expected_calls = scenario_count;
    } else return 64;
    compared = failures = 0U;
    for (scenario = 0U; scenario < scenario_count; ++scenario) {
        if (argc == 2)
            sprintf(path, "%s/block-lifetime-%u.calls", argv[1], scenario);
        else {
            if (strlen(argv[scenario + 2U]) >= sizeof(path)) return 64;
            strcpy(path, argv[scenario + 2U]);
        }
        stream = fopen(path, "rb");
        if (stream == NULL) return 65;
        if (fread(header, 1U, 8U, stream) != 8U ||
            memcmp(header, "MSLC\1", 5U) != 0) return 66;
        for (entry = 0U; entry < header[5]; ++entry) {
            if (fread(record, 1U, sizeof(record), stream) != sizeof(record))
                return 66;
            if (record[0] != 5U && record[0] != 6U) continue;
            ++compared;
            memset(&game, 0, sizeof(game));
            memcpy(game.ram, record + 2U, 2048U);
            if (record[0] == 5U)
                mysmb_objects_draw_bouncing_block(&game, record[1]);
            else
                mysmb_objects_draw_brick_chunks(&game, record[1]);
            differences = 0U;
            for (byte = 0U; byte < 2048U; ++byte) {
                if (byte >= 0x100U && byte < 0x200U) continue;
                if (game.ram[byte] != record[2050U + byte]) {
                    if (differences < 6U && failures < 8U)
                        printf("case=%u child=%u RAM=%04x ROM=%02x C=%02x\n",
                               scenario, record[0], byte,
                               record[2050U + byte], game.ram[byte]);
                    ++differences;
                }
            }
            if (differences != 0U) ++failures;
        }
        if (fgetc(stream) != EOF) return 66;
        fclose(stream);
    }
    printf("Block graphics child calls=%u differing=%u\n", compared, failures);
    return compared == expected_calls && failures == 0U ? 0 : 1;
}
