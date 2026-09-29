#include "game/objects.h"
#include <stdio.h>
#include <string.h>

/* ProcessBowserHalf -> RunRetainerObj original child records.  The source
 * graphics path is selected only while BowserGfxFlag is nonzero; zero-flag
 * records belong to the generic enemy handler branch. */
static struct mysmb_game game;
static unsigned char record[4098];

int main(int argc, char **argv)
{
    unsigned int scenario, count, index, slot, byte, differences;
    unsigned int cases = 0U;
    unsigned int failures = 0U;
    unsigned char header[8];
    FILE *stream;
    char path[1024];

    if (argc != 2 || strlen(argv[1]) + 40U >= sizeof(path)) return 64;
    for (scenario = 0U; scenario < 512U; ++scenario) {
        sprintf(path, "%s/bowser-graphics-%u.calls", argv[1], scenario);
        stream = fopen(path, "rb");
        if (stream == NULL) return 65;
        if (fread(header, 1U, 8U, stream) != 8U ||
            memcmp(header, "MSmC\1", 5U) != 0) return 66;
        count = header[5];
        for (index = 0U; index < count; ++index) {
            if (fread(record, 1U, sizeof(record), stream) != sizeof(record))
                return 66;
            if (record[0] != 1U || record[2U + 0x036aU] == 0U) continue;
            ++cases;
            slot = record[1];
            memset(&game, 0, sizeof(game));
            memcpy(game.ram, record + 2U, 2048U);
            mysmb_objects_draw_retainer(&game, (mysmb_u8)slot);
            differences = 0U;
            for (byte = 0U; byte < 2048U; ++byte) {
                if (byte >= 0x100U && byte < 0x200U) continue;
                if (game.ram[byte] != record[2050U + byte]) {
                    ++differences;
                    if (differences <= 8U && failures < 8U)
                        printf("scenario=%u child=%u slot=%u RAM=%04x ROM=%02x native=%02x\n",
                            scenario, index, slot, byte,
                            record[2050U + byte], game.ram[byte]);
                }
            }
            if (differences != 0U) ++failures;
        }
        if (fgetc(stream) != EOF) return 66;
        fclose(stream);
    }
    printf("Bowser child comparisons=%u differing=%u\n", cases, failures);
    return cases == 768U && failures == 0U ? 0 : 1;
}
