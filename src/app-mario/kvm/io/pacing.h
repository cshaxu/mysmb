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
/* A separate publication clock bounds suppression during sustained lateness.
 * This never rebases the logical tick clock or drops game/audio updates. */
int mysmb_io_pacing_video_due(struct mysmb_io_pacing *publication,
    unsigned long now, int on_time);
#endif
