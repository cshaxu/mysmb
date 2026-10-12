#include "core/objects.h"
#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Original RunNormalEnemies -> EnemyGfxHandler child records.  Compare every
 * non-stack RAM byte, including all six OAM sprite entries. */
static struct mysmb_game game;
static unsigned char record[4098];

int main(int argc, char **argv)
{
    unsigned int scenario, index, slot, byte, differences, cases, failures;
    unsigned int scenario_count, expected_cases;
    unsigned char header[8];
    FILE *stream;
    char path[1024];

    if (argc == 2) {
        if (strlen(argv[1]) + 40U >= sizeof(path)) return 64;
        scenario_count = 126U;
        expected_cases = 84U;
    } else if (argc >= 3 && strcmp(argv[1], "--files") == 0) {
        scenario_count = (unsigned int)(argc - 2);
        expected_cases = scenario_count;
    } else return 64;
    cases = failures = 0U;
    for (scenario = 0U; scenario < scenario_count; ++scenario) {
        if (argc == 2) sprintf(path, "%s/normal-actor-%u.calls", argv[1], scenario);
        else {
            if (strlen(argv[scenario + 2U]) >= sizeof(path)) return 64;
            strcpy(path, argv[scenario + 2U]);
        }
        stream = fopen(path, "rb");
        if (stream == NULL) return 65;
        if (fread(header, 1U, 8U, stream) != 8U ||
            memcmp(header, "MS8C\1", 5U) != 0) return 66;
        for (index = 0U; index < header[5]; ++index) {
            if (fread(record, 1U, sizeof(record), stream) != sizeof(record))
                return 66;
            if (record[0] != 3U) continue;
            ++cases;
            slot = record[1];
            memset(&game, 0, sizeof(game));
            memcpy(game.ram, record + 2U, 2048U);
            (void)mysmb_objects_draw_normal_enemy_graphics(&game,
                                                             (mysmb_u8)slot);
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
    printf("Normal enemy graphics cases=%u differing=%u\n", cases, failures);
    return cases == expected_cases && failures == 0U ? 0 : 1;
}
