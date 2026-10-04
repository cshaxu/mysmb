#ifndef MYSMB_IO_PACING_H
#define MYSMB_IO_PACING_H
/* Monotonic host clock stamps use the low 32 bits; no system clock access. */
struct mysmb_io_pacing { unsigned long last; unsigned long period; };
void mysmb_io_pacing_initialize(struct mysmb_io_pacing *pacing,
    unsigned long now, unsigned long period);
unsigned long mysmb_io_pacing_remaining(struct mysmb_io_pacing *pacing,
    unsigned long now);
#endif
