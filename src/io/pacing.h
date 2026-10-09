#ifndef MYSMB_IO_PACING_H
#define MYSMB_IO_PACING_H
/* Monotonic host clock stamps use the low 32 bits; no system clock access. */
struct mysmb_io_pacing { unsigned long last; unsigned long period; };
void mysmb_io_pacing_initialize(struct mysmb_io_pacing *pacing,
    unsigned long now, unsigned long period);
/* Deadline helpers do not sleep or select a presentation policy.  Hosts may
 * use them to retain missed logical-tick debt while choosing to drop video. */
int mysmb_io_pacing_late(const struct mysmb_io_pacing *pacing,
    unsigned long now);
void mysmb_io_pacing_advance(struct mysmb_io_pacing *pacing,
    unsigned long now);
unsigned long mysmb_io_pacing_remaining(struct mysmb_io_pacing *pacing,
    unsigned long now);
#endif
