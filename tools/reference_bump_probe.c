/*
 * Owner-local controlled ROM probe for M2 T64 S21.  It is compiled only
 * against a local nnes checkout.  The probe enters $e124 with a real RTS
 * sentinel after reset, records the five finite branch cases, and writes raw
 * output only to an ignored caller-selected path.
 */
#include <stdio.h>
#include <string.h>

#include "core/driver.h"
#include "core/machine.h"

#define PROBE_ENTRY 0xe124u
#define PROBE_SET_HJ 0xca37u
#define PROBE_RETURN 0x8001u
#define PROBE_NMI_RETURN 0x8181u
#define PROBE_RECORD_BYTES 4112u
#define PROBE_CASES 5u
#define PROBE_MAX_STEPS 524288u

static int write_bytes(FILE *file, const void *data, size_t size)
{
    return fwrite(data, 1u, size, file) == size;
}

static int reach_nmi_return(core_machine *machine)
{
    core_run_result result;
    unsigned int step;

    for (step = 0u; step < PROBE_MAX_STEPS; ++step) {
        if (machine->pc == PROBE_NMI_RETURN) return 1;
        if (core_machine_debug_step(machine, 1u, 1024u, &result) !=
            LIB_STATUS_OK || result.trap_valid) return 0;
    }
    return 0;
}

static void prepare_case(core_machine *machine, unsigned int variant)
{
    unsigned char slot = variant == 2u || variant == 4u ? 5u : 0u;

    memset(machine->ram, 0, 2048u);
    machine->ram[0x0016u + slot] = variant >= 3u ? 5u : 1u;
    machine->ram[0x001eu + slot] = variant == 1u || variant == 2u ||
        variant == 4u ? 0x80u : 0u;
    machine->ram[0x0058u + slot] = 0x10u;
    machine->ram[0x0046u + slot] = 1u;
    machine->ram[0x00ffu] = 0x55u;
    machine->ram[0u] = 0x77u;
    machine->ram[0x01feu] = 0u;
    machine->ram[0x01ffu] = 0x80u;
    machine->a = 0u;
    machine->x = slot;
    machine->y = 0u;
    machine->s = 0xfdu;
    machine->pc = PROBE_ENTRY;
}

int main(int argc, char **argv)
{
    static const unsigned char header[8] = {
        'M', 'S', 'B', 'P', 1u, PROBE_CASES, 0u, 0u
    };
    core_driver *driver;
    core_run_result result;
    FILE *file;
    unsigned char record[PROBE_RECORD_BYTES];
    unsigned int variant;
    unsigned int step;
    unsigned int endpoint;
    int ok;

    if (argc != 3) return 64;
    file = fopen(argv[2], "wb");
    if (file == NULL) return 65;
    if (!write_bytes(file, header, sizeof(header))) {
        fclose(file);
        return 66;
    }
    ok = 1;
    for (variant = 0u; variant < PROBE_CASES && ok; ++variant) {
        driver = NULL;
        if (core_driver_create(&driver, &(core_driver_options){ 0u, LIB_FALSE }) !=
            LIB_STATUS_OK || !core_driver_set_media(driver, argv[1],
            LIB_STORAGE_MEDIUM_READONLY) || !reach_nmi_return(driver->machine)) {
            if (driver != NULL) (void)core_driver_destroy(driver);
            ok = 0;
            break;
        }
        prepare_case(driver->machine, variant);
        memset(record, 0, sizeof(record));
        record[0] = (unsigned char)PROBE_ENTRY;
        record[1] = (unsigned char)(PROBE_ENTRY >> 8u);
        record[2] = driver->machine->a;
        record[3] = driver->machine->x;
        record[4] = driver->machine->y;
        record[5] = driver->machine->p;
        record[11] = (unsigned char)variant;
        memcpy(record + 16u, driver->machine->ram, 2048u);
        endpoint = 0u;
        for (step = 0u; step < PROBE_MAX_STEPS; ++step) {
            if (driver->machine->pc == PROBE_SET_HJ ||
                driver->machine->pc == PROBE_RETURN) {
                endpoint = driver->machine->pc;
                break;
            }
            if (core_machine_debug_step(driver->machine, 1u, 1024u, &result) !=
                LIB_STATUS_OK || result.trap_valid) break;
        }
        if (endpoint == 0u ||
            ((variant < 3u && endpoint != PROBE_RETURN) ||
             (variant >= 3u && endpoint != PROBE_SET_HJ))) {
            (void)core_driver_destroy(driver);
            ok = 0;
            break;
        }
        record[6] = driver->machine->a;
        record[7] = driver->machine->x;
        record[8] = driver->machine->y;
        record[9] = driver->machine->p;
        record[10] = driver->machine->s;
        record[12] = (unsigned char)endpoint;
        record[13] = (unsigned char)(endpoint >> 8u);
        memcpy(record + 2064u, driver->machine->ram, 2048u);
        ok = write_bytes(file, record, sizeof(record));
        (void)core_driver_destroy(driver);
    }
    if (fclose(file) != 0) ok = 0;
    return ok ? 0 : 68;
}
