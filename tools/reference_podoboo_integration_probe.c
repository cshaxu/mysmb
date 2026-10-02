/* Original-ROM Podoboo initialization-return and gravity integration proof. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"

#define CASES 3072u
#define LIMIT 524288u

static int ready(core_machine *machine)
{
    core_run_result result;
    unsigned int i;
    for (i = 0u; i < LIMIT; ++i) {
        if (machine->pc == 0x8181u) return 1;
        if (core_machine_debug_step(machine, 1u, 1024u, &result) !=
                LIB_STATUS_OK || result.trap_valid) return 0;
    }
    return 0;
}

int main(int argc, char **argv)
{
    static core_machine baseline;
    static const unsigned short init_fields[8] = {
        0x00b6u, 0x00cfu, 0x0796u, 0x001eu,
        0x049au, 0x0046u, 0x00a0u, 0x0434u
    };
    static const unsigned char init_values[8] = {2u,2u,1u,0u,9u,2u,0u,0u};
    static const unsigned char speeds[8] = {0u,1u,3u,0x7fu,0x80u,0xf9u,0xfeu,0xffu};
    unsigned char header[12] = {'M','S','P','D',1u,0u,0u,0u,0u,12u,0u,0u};
    unsigned char record[4100];
    core_driver *driver = NULL;
    core_driver_options options = {0u, LIB_FALSE};
    core_run_result result;
    FILE *file;
    unsigned int n, i, j, steps, max_steps = 0u, returns = 0u;
    unsigned int gravity = 0u, expected_returns, case_returns;
    unsigned char slot, random_value, timer, expected;
    int ok = 1;
    time_t start = time(NULL);

    if (argc != 3) return 64;
    if (core_driver_create(&driver, &options) != LIB_STATUS_OK ||
        !core_driver_set_media(driver, argv[1], LIB_STORAGE_MEDIUM_READONLY) ||
        !ready(driver->machine)) return 65;
    memcpy(&baseline, driver->machine, sizeof(baseline));
    file = fopen(argv[2], "wb");
    if (file == NULL) return 65;
    if (fwrite(header, 1u, sizeof(header), file) != sizeof(header)) ok = 0;
    for (n = 0u; n < CASES && ok; ++n) {
        if (time(NULL) - start > 120) {ok = 0; break;}
        memcpy(driver->machine, &baseline, sizeof(baseline));
        memset(driver->machine->ram, 0, 2048u);
        slot = (unsigned char)(n / 512u);
        random_value = (unsigned char)n;
        timer = n % 512u < 256u ? 0u :
            (unsigned char)(n % 3u == 0u ? 0xffu : n % 3u + 1u);
        driver->machine->ram[8u] = slot;
        driver->machine->ram[0x000fu + slot] = 1u;
        driver->machine->ram[0x0016u + slot] = 12u;
        driver->machine->ram[0x0796u + slot] = timer;
        driver->machine->ram[0x07a8u + slot] = random_value;
        driver->machine->ram[0x001eu + slot] = (unsigned char)(n * 17u);
        driver->machine->ram[0x049au + slot] = 0x0bu;
        driver->machine->ram[0x0046u + slot] = 1u;
        driver->machine->ram[0x00b6u + slot] = (unsigned char)(1u + n % 2u);
        driver->machine->ram[0x00cfu + slot] = (unsigned char)(n * 13u);
        driver->machine->ram[0x00a0u + slot] = speeds[n % 8u];
        driver->machine->ram[0x0434u + slot] = (unsigned char)(n * 29u);
        driver->machine->ram[0x0417u + slot] = (unsigned char)(n * 31u);
        driver->machine->ram[0x01feu] = 0u;
        driver->machine->ram[0x01ffu] = 0x80u;
        driver->machine->pc = 0xc9b0u;
        driver->machine->x = slot;
        driver->machine->a = 0x77u;
        driver->machine->y = 0x44u;
        driver->machine->s = 0xfdu;
        record[0] = slot; record[1] = timer;
        memcpy(record + 4u, driver->machine->ram, 2048u);
        case_returns = 0u;
        for (steps = 0u; steps < LIMIT && driver->machine->pc != 0x8001u; ++steps) {
            if (driver->machine->pc == 0xc9b8u) {
                ++returns; ++case_returns;
                if (timer != 0u || driver->machine->x != slot ||
                    driver->machine->a != 0u || driver->machine->y != 0x44u) ok = 0;
                /* The real initializer changes exactly eight persistent fields.
                 * Check all remaining fields too, not merely the expected writes. */
                for (i = 8u; i < 2048u; ++i) {
                    if (i >= 0x100u && i < 0x200u) continue;
                    expected = record[4u + i];
                    for (j = 0u; j < 8u; ++j)
                        if (i == init_fields[j] + slot) expected = init_values[j];
                    if (driver->machine->ram[i] != expected) ok = 0;
                }
            }
            if (driver->machine->pc == 0xbf92u) {
                ++gravity;
                if (driver->machine->x != slot) ok = 0;
            }
            if (!ok || core_machine_debug_step(driver->machine, 1u, 1024u, &result) !=
                    LIB_STATUS_OK || result.trap_valid) {ok = 0; break;}
        }
        expected_returns = timer == 0u ? 1u : 0u;
        if (case_returns != expected_returns || driver->machine->pc != 0x8001u) ok = 0;
        if (steps > max_steps) max_steps = steps;
        record[2] = driver->machine->x; record[3] = driver->machine->y;
        memcpy(record + 2052u, driver->machine->ram, 2048u);
        if (fwrite(record, 1u, sizeof(record), file) != sizeof(record)) ok = 0;
    }
    if (fclose(file) != 0) ok = 0;
    (void)core_driver_destroy(driver);
    printf("cases=%u init-returns=%u gravity-tails=%u maxsteps=%u\n",
        n, returns, gravity, max_steps);
    if (returns != 1536u || gravity != CASES || n != CASES) ok = 0;
    return ok ? 0 : 66;
}
