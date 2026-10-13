#ifndef MYGAMES_DOS16_HOST_H
#define MYGAMES_DOS16_HOST_H

#include "kvm/types.h"

/* One synchronous scan sink. The application owns scan-to-command policy. */
typedef void (*mygames_dos16_scan_sink)(void *,mygames_kvm_u8);
int mygames_dos16_keyboard_open(mygames_dos16_scan_sink sink,void *context);
void mygames_dos16_keyboard_close(void);
/* BIOS-owned channel-zero timestamp; leaves its rate and vector unchanged. */
unsigned long mygames_dos16_clock_stamp(void);
struct mygames_dos16_video_state {
    mygames_kvm_u8 mode,rows,font;
    mygames_kvm_u16 cursor;
};
void mygames_dos16_video_capture(struct mygames_dos16_video_state *state);
void mygames_dos16_video_restore(const struct mygames_dos16_video_state *state);
int mygames_dos16_text_mode(mygames_kvm_u16 rows);

#endif
