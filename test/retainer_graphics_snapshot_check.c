#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* RunRetainerObj -> EnemyGfxHandler original child records, both worlds and
 * every recorded position, compared over all non-stack RAM and OAM bytes. */
static struct mysmb_game game;
static unsigned char record[4098];

int main(int argc, char **argv)
{
    unsigned int scenario, index, slot, byte, differences, cases, failures;
    unsigned char header[8];
    FILE *stream;
    char path[1024];
    if (argc != 2 || strlen(argv[1]) + 40U >= sizeof(path)) return 64;
    cases = failures = 0U;
    for (scenario = 108U; scenario < 180U; ++scenario) {
        sprintf(path, "%s/actor-dispatch-%u.calls", argv[1], scenario);
        stream = fopen(path, "rb");
        if (stream == NULL) return 65;
        if (fread(header, 1U, 8U, stream) != 8U ||
            memcmp(header, "MS7C\1", 5U) != 0) return 66;
        for (index = 0U; index < header[5]; ++index) {
            if (fread(record, 1U, sizeof(record), stream) != sizeof(record))
                return 66;
            if (record[0] != 3U) continue;
            ++cases;
            slot = record[1];
            memset(&game, 0, sizeof(game));
            memcpy(game.ram, record + 2U, 2048U);
            mysmb_oam_draw_retainer(&game, (mysmb_u8)slot);
            differences = 0U;
            for (byte = 0U; byte < 2048U; ++byte) {
                if (byte >= 0x100U && byte < 0x200U) continue;
                if (game.ram[byte] != record[2050U + byte]) {
                    ++differences;
                    if (differences <= 6U && failures < 8U)
                        printf("scenario=%u slot=%u RAM=%04x ROM=%02x native=%02x\n",
                            scenario, slot, byte, record[2050U + byte],
                            game.ram[byte]);
                }
            }
            if (differences != 0U) ++failures;
        }
        if (fgetc(stream) != EOF) return 66;
        fclose(stream);
    }
    printf("Retainer graphics cases=%u differing=%u\n", cases, failures);
    return cases == 72U && failures == 0U ? 0 : 1;
}
