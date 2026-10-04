#ifndef MYSMB_IO_SNAPSHOT_H
#define MYSMB_IO_SNAPSHOT_H

#include "io/types.h"

/* Fixed byte counts are schema contracts, never sizeof native state. */
#define MYSMB_SNAPSHOT_CORE_BYTES 4622U
#define MYSMB_SNAPSHOT_AUDIO_BYTES 124U
#define MYSMB_SNAPSHOT_PRESENTATION_BYTES 5253U
#define MYSMB_SNAPSHOT_PRESENTATION_OFFSET 4746U
#define MYSMB_SNAPSHOT_PAYLOAD_BYTES 9999U
#define MYSMB_SNAPSHOT_HEADER_BYTES 36U
#define MYSMB_SNAPSHOT_FILE_BYTES 10035U
#define MYSMB_SNAPSHOT_LEGACY_FILE_BYTES 4782U
#define MYSMB_SNAPSHOT_REAL_BYTES 10U
#define MYSMB_SNAPSHOT_AUDIO_REAL_OFFSET 64U

enum {
    MYSMB_SNAPSHOT_OK = 0,
    MYSMB_SNAPSHOT_INVALID = 1,
    MYSMB_SNAPSHOT_RESOURCE = 2,
    MYSMB_SNAPSHOT_INTEGRITY = 3
};

struct mysmb_io_snapshot {
    mysmb_io_u8 fingerprint[16];
    /* Program bytes are opaque to IO. Composition binds schema fields. */
    mysmb_io_u8 payload[MYSMB_SNAPSHOT_PAYLOAD_BYTES];
};

struct mysmb_io_snapshot_cache {
    mysmb_io_u8 valid;
    struct mysmb_io_snapshot last_running;
};

void mysmb_snapshot_put16(mysmb_io_u8 *bytes, mysmb_io_u16 value);
mysmb_io_u16 mysmb_snapshot_get16(const mysmb_io_u8 *bytes);
void mysmb_snapshot_put32(mysmb_io_u8 *bytes, unsigned long value);
unsigned long mysmb_snapshot_get32(const mysmb_io_u8 *bytes);
unsigned long mysmb_snapshot_crc(const mysmb_io_u8 *bytes, mysmb_io_u16 size);

/* Validate the canonical sign/exponent/mantissa bytes using integers only. */
int mysmb_snapshot_real_valid(const mysmb_io_u8 *bytes);

/* Buffers must not overlap. A rejected encode/decode leaves output intact. */
int mysmb_snapshot_encode(const struct mysmb_io_snapshot *snapshot,
    mysmb_io_u8 *file, mysmb_io_u16 size);
int mysmb_snapshot_decode(const mysmb_io_u8 *file, mysmb_io_u16 size,
    const mysmb_io_u8 *fingerprint, struct mysmb_io_snapshot *snapshot);

void mysmb_snapshot_cache_initialize(struct mysmb_io_snapshot_cache *cache);
/* running_boundary is supplied by composition; IO knows no game modes. */
void mysmb_snapshot_cache_update(struct mysmb_io_snapshot_cache *cache,
    const struct mysmb_io_snapshot *snapshot, mysmb_io_u8 running_boundary);
const struct mysmb_io_snapshot *mysmb_snapshot_cache_current(
    const struct mysmb_io_snapshot_cache *cache);

#endif
