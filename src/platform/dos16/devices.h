#ifndef MYSMB_DOS16_DEVICES_H
#define MYSMB_DOS16_DEVICES_H
#include "io/input.h"
#include "io/audio.h"
#include "io/planar_frame.h"
int mysmb_dos16_devices_open(void);
void mysmb_dos16_devices_close(void);
void mysmb_dos16_devices_input(struct mysmb_io_input *input);
/* Native256x240 chain4 row-major view;never accepts a scaled/plane frame. */
int mysmb_dos16_devices_present_band(const struct mysmb_io_video_band *band);
void mysmb_dos16_devices_wait(void);
void mysmb_dos16_devices_after_load(void);
int mysmb_dos16_devices_mode(mysmb_io_u8 text);
void mysmb_dos16_devices_palette(const mysmb_io_u8 MYSMB_IO_FAR *palette);
void mysmb_dos16_devices_text(const struct mysmb_io_text_frame MYSMB_IO_FAR *frame);
mysmb_io_u8 mysmb_dos16_devices_audio(const struct mysmb_io_audio_frame *frame);
#endif
