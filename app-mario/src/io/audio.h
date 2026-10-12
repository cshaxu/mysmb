#ifndef MYSMB_IO_AUDIO_H
#define MYSMB_IO_AUDIO_H

#include "io/types.h"

enum { MYSMB_IO_AUDIO_UNAVAILABLE=0, MYSMB_IO_AUDIO_AVAILABLE=1 };

#define MYSMB_IO_AUDIO_REGISTER_COUNT 24U
#define MYSMB_IO_AUDIO_WRITE_CAPACITY 64U

struct mysmb_io_audio_write {
    mysmb_io_u8 index;
    mysmb_io_u8 value;
};

/* Owned output snapshot for one logical tick. Writes retain source order,
 * including repeated equal values; they are never a deduplicated register
 * diff. A presenter consumes a tick once. Registers are the final state,
 * useful to synchronize a newly opened device, not a substitute for writes.
 * Physical synthesis state and device support remain adapter capabilities. */
struct mysmb_io_audio_frame {
    mysmb_io_u8 registers[MYSMB_IO_AUDIO_REGISTER_COUNT];
    mysmb_io_u8 delta_counter_load;
    mysmb_io_u8 channel_enable;
    mysmb_io_u8 frame_counter;
    mysmb_io_u8 write_count;
    struct mysmb_io_audio_write writes[MYSMB_IO_AUDIO_WRITE_CAPACITY];
};

#endif
