#ifndef MYSMB_WIN32_AUDIO_SNAPSHOT_REAL_H
#define MYSMB_WIN32_AUDIO_SNAPSHOT_REAL_H
#include "io/snapshot.h"
/* Convert host numeric values without copying their floating memory layout. */
int mysmb_snapshot_put_real(mysmb_io_u8 *bytes, double value);
int mysmb_snapshot_get_real(const mysmb_io_u8 *bytes, double *value);
#endif
