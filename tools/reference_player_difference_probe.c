/* Controlled original-ROM probe for M2 T64 S23.  It enters PlayerEnemyDiff
 * with a real RTS sentinel and emits only ignored caller-selected evidence. */
#include <stdio.h>
#include <string.h>

#include "core/driver.h"
#include "core/machine.h"

#define ENTRY 0xe143u
#define RETURN_PC 0x8001u
#define NMI_RETURN 0x8181u
#define RECORD_BYTES 4112u
#define CASES 4u
#define MAX_STEPS 524288u

static int reach_nmi_return(core_machine *machine)
{
    core_run_result result;
    unsigned int step;
    for (step = 0u; step < MAX_STEPS; ++step) {
        if (machine->pc == NMI_RETURN) return 1;
        if (core_machine_debug_step(machine, 1u, 1024u, &result) != LIB_STATUS_OK ||
            result.trap_valid) return 0;
    }
    return 0;
}

static void prepare_case(core_machine *machine, unsigned int variant)
{
    static const unsigned char enemy_x[CASES] = { 0x20u, 0x10u, 0x00u, 0xffu };
    static const unsigned char player_x[CASES] = { 0x10u, 0x20u, 0xffu, 0x00u };
    static const unsigned char enemy_page[CASES] = { 0x02u, 0x02u, 0x00u, 0x0fu };
    static const unsigned char player_page[CASES] = { 0x01u, 0x01u, 0x01u, 0x00u };
    unsigned char slot = 3u;
    memset(machine->ram, 0, 2048u);
    machine->ram[0x0087u + slot] = enemy_x[variant];
    machine->ram[0x0086u] = player_x[variant];
    machine->ram[0x006eu + slot] = enemy_page[variant];
    machine->ram[0x006du] = player_page[variant];
    machine->ram[0u] = 0x55u;
    machine->ram[0x01feu] = 0u;
    machine->ram[0x01ffu] = 0x80u;
    machine->a = 0u;
    machine->x = slot;
    machine->y = 0u;
    machine->s = 0xfdu;
    machine->pc = ENTRY;
}

int main(int argc, char **argv)
{
    static const unsigned char header[8] = { 'M', 'S', 'P', 'D', 1u, CASES, 0u, 0u };
    core_driver *driver;
    core_run_result result;
    unsigned char record[RECORD_BYTES];
    FILE *file;
    unsigned int variant;
    unsigned int step;
    int ok;
    if (argc != 3) return 64;
    file = fopen(argv[2], "wb");
    if (file == NULL || fwrite(header, 1u, sizeof(header), file) != sizeof(header)) {
        if (file != NULL) fclose(file);
        return 65;
    }
    ok = 1;
    for (variant = 0u; variant < CASES && ok; ++variant) {
        driver = NULL;
        if (core_driver_create(&driver, &(core_driver_options){ 0u, LIB_FALSE }) != LIB_STATUS_OK ||
            !core_driver_set_media(driver, argv[1], LIB_STORAGE_MEDIUM_READONLY) ||
            !reach_nmi_return(driver->machine)) {
            if (driver != NULL) (void)core_driver_destroy(driver);
            ok = 0;
            break;
        }
        prepare_case(driver->machine, variant);
        memset(record, 0, sizeof(record));
        record[0] = (unsigned char)ENTRY;
        record[1] = (unsigned char)(ENTRY >> 8u);
        record[3] = driver->machine->x;
        record[11] = (unsigned char)variant;
        memcpy(record + 16u, driver->machine->ram, 2048u);
        for (step = 0u; step < MAX_STEPS && driver->machine->pc != RETURN_PC; ++step) {
            if (core_machine_debug_step(driver->machine, 1u, 1024u, &result) != LIB_STATUS_OK ||
                result.trap_valid) break;
        }
        if (driver->machine->pc != RETURN_PC) ok = 0;
        record[6] = driver->machine->a;
        record[12] = (unsigned char)driver->machine->pc;
        record[13] = (unsigned char)(driver->machine->pc >> 8u);
        memcpy(record + 2064u, driver->machine->ram, 2048u);
        if (fwrite(record, 1u, sizeof(record), file) != sizeof(record)) ok = 0;
        (void)core_driver_destroy(driver);
    }
    if (fclose(file) != 0) ok = 0;
    return ok ? 0 : 66;
}
