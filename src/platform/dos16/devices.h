#ifndef MYSMB_DOS16_DEVICES_H
#define MYSMB_DOS16_DEVICES_H
#include "io/input.h"
#include "io/audio.h"
#include "io/planar_frame.h"
int mysmb_dos16_devices_open(void);
void mysmb_dos16_devices_close(void);
void mysmb_dos16_devices_input(struct mysmb_io_input *input);
void mysmb_dos16_devices_present(const struct mysmb_vga_frame *frame);
void mysmb_dos16_devices_present_rows(mysmb_io_u16 plane,
    mysmb_io_u16 first,mysmb_io_u16 rows,
    const mysmb_io_u8 MYSMB_VGA_FAR *pixels);
void mysmb_dos16_devices_wait(void);
void mysmb_dos16_devices_after_load(void);
int mysmb_dos16_devices_mode(mysmb_io_u8 text);
void mysmb_dos16_devices_text(const struct mysmb_io_text_frame MYSMB_IO_FAR *frame);
mysmb_io_u8 mysmb_dos16_devices_audio(const struct mysmb_io_audio_frame *frame);
#endif
