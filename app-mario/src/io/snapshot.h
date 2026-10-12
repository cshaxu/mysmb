#ifndef MYSMB_IO_SNAPSHOT_H
#define MYSMB_IO_SNAPSHOT_H

#include "kvm/types.h"

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
    mygames_kvm_u8 fingerprint[16];
    /* Program bytes are opaque to IO. Composition binds schema fields. */
    mygames_kvm_u8 payload[MYSMB_SNAPSHOT_PAYLOAD_BYTES];
};

struct mysmb_io_snapshot_cache {
    mygames_kvm_u8 valid;
    struct mysmb_io_snapshot last_running;
    struct mysmb_io_snapshot *published;
};

void mysmb_snapshot_put16(mygames_kvm_u8 *bytes, mygames_kvm_u16 value);
mygames_kvm_u16 mysmb_snapshot_get16(const mygames_kvm_u8 *bytes);
void mysmb_snapshot_put32(mygames_kvm_u8 *bytes, unsigned long value);
unsigned long mysmb_snapshot_get32(const mygames_kvm_u8 *bytes);
unsigned long mysmb_snapshot_crc(const mygames_kvm_u8 *bytes, mygames_kvm_u16 size);

/* Validate the canonical sign/exponent/mantissa bytes using integers only. */
int mysmb_snapshot_real_valid(const mygames_kvm_u8 *bytes);

/* Buffers must not overlap. A rejected encode/decode leaves output intact. */
int mysmb_snapshot_encode(const struct mysmb_io_snapshot *snapshot,
    mygames_kvm_u8 *file, mygames_kvm_u16 size);
int mysmb_snapshot_decode(const mygames_kvm_u8 *file, mygames_kvm_u16 size,
    const mygames_kvm_u8 *fingerprint, struct mysmb_io_snapshot *snapshot);
/* Split codec for synchronous streaming;checks never modify payload storage. */
int mysmb_snapshot_encode_header(const struct mysmb_io_snapshot *snapshot,
    mygames_kvm_u8 *header);
mygames_kvm_u16 mysmb_snapshot_header_payload(const mygames_kvm_u8 *header);
int mysmb_snapshot_check_parts(const mygames_kvm_u8 *header,
    const mygames_kvm_u8 *payload,mygames_kvm_u16 size,const mygames_kvm_u8 *fingerprint);

void mysmb_snapshot_cache_initialize(struct mysmb_io_snapshot_cache *cache);
/* Two persistent caller-owned slots:write the inactive one,then publish only
 * after every capture stage succeeds. Failed staging leaves current intact.
 * Copy-update/load resets publication to the cache-owned slot. */
struct mysmb_io_snapshot *mysmb_snapshot_cache_staging(struct mysmb_io_snapshot_cache *cache,
    struct mysmb_io_snapshot *spare);
void mysmb_snapshot_cache_publish(struct mysmb_io_snapshot_cache *cache,
    struct mysmb_io_snapshot *completed);
/* running_boundary is supplied by composition; IO knows no game modes. */
void mysmb_snapshot_cache_update(struct mysmb_io_snapshot_cache *cache,
    const struct mysmb_io_snapshot *snapshot, mygames_kvm_u8 running_boundary);
const struct mysmb_io_snapshot *mysmb_snapshot_cache_current(
    const struct mysmb_io_snapshot_cache *cache);

#endif
