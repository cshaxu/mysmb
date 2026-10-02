/* Controlled original-ROM probe for M2 T64 S31 FireballBGCollision. */
#include <stdio.h>
#include <string.h>
#include "core/driver.h"
#include "core/machine.h"

#define ENTRY 0xe1c8u
#define RETURN_PC 0x8001u
#define NMI_RETURN 0x8181u
#define RECORD_BYTES 4098u
#define CASES 7u
#define MAX_STEPS 524288u

static int ready(core_machine *machine)
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

static void prepare(core_machine *machine, unsigned int index)
{
    static const unsigned char y[CASES] = { 0x17u, 0x50u, 0x50u, 0x50u,
        0x50u, 0x50u, 0x50u };
    static const unsigned char tile[CASES] = { 0u, 0u, 0xc2u, 0x51u,
        0x51u, 0x51u, 0x60u };
    static const unsigned char speed[CASES] = { 0u, 0u, 0u, 0u,
        0x80u, 0u, 0u };
    static const unsigned char bounce[CASES] = { 1u, 1u, 1u, 0u,
        0u, 1u, 1u };

    memset(machine->ram, 0, 2048u);
    machine->ram[0x0008u] = 0u;
    machine->ram[0x008du] = 0x40u;
    machine->ram[0x0074u] = 0u;
    machine->ram[0x00d5u] = y[index];
    machine->ram[0x00a6u] = speed[index];
    machine->ram[0x003au] = bounce[index];
    machine->ram[0x0024u] = 1u;
    machine->ram[0x0534u] = tile[index];
    machine->ram[0x01feu] = 0u;
    machine->ram[0x01ffu] = 0x80u;
    machine->a = 0x77u;
    machine->x = 0u;
    machine->y = 0x22u;
    machine->s = 0xfdu;
    machine->pc = ENTRY;
}

int main(int argc, char **argv)
{
    static const unsigned char header[8] = { 'M', 'S', 'F', 'C', 1u, CASES, 0u, 0u };
    core_driver *driver;
    core_run_result result;
    unsigned char record[RECORD_BYTES];
    FILE *file;
    unsigned int index;
    unsigned int step;
    int ok;

    if (argc != 3) return 64;
    file = fopen(argv[2], "wb");
    if (file == NULL || fwrite(header, 1u, sizeof(header), file) != sizeof(header)) {
        if (file != NULL) fclose(file);
        return 65;
    }
    ok = 1;
    for (index = 0u; index < CASES && ok; ++index) {
        driver = NULL;
        if (core_driver_create(&driver, &(core_driver_options){ 0u, LIB_FALSE }) != LIB_STATUS_OK ||
            !core_driver_set_media(driver, argv[1], LIB_STORAGE_MEDIUM_READONLY) ||
            !ready(driver->machine)) {
            if (driver != NULL) (void)core_driver_destroy(driver);
            ok = 0;
            break;
        }
        prepare(driver->machine, index);
        memset(record, 0, sizeof(record));
        record[0] = 6u;
        record[1] = 0u;
        memcpy(record + 2u, driver->machine->ram, 2048u);
        for (step = 0u; step < MAX_STEPS && driver->machine->pc != RETURN_PC; ++step) {
            if (core_machine_debug_step(driver->machine, 1u, 1024u, &result) != LIB_STATUS_OK ||
                result.trap_valid) break;
        }
        if (driver->machine->pc != RETURN_PC) ok = 0;
        memcpy(record + 2050u, driver->machine->ram, 2048u);
        if (fwrite(record, 1u, sizeof(record), file) != sizeof(record)) ok = 0;
        (void)core_driver_destroy(driver);
    }
    if (fclose(file) != 0) ok = 0;
    return ok ? 0 : 66;
}
