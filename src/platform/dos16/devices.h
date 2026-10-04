#ifndef MYSMB_DOS16_DEVICES_H
#define MYSMB_DOS16_DEVICES_H
#include "io/input.h"
#include "platform/vga/vga_frame.h"
void mysmb_dos16_devices_open(void);
void mysmb_dos16_devices_close(void);
void mysmb_dos16_devices_input(struct mysmb_io_input *input);
int mysmb_dos16_devices_exit_requested(void);
void mysmb_dos16_devices_present(const struct mysmb_vga_frame *frame);
void mysmb_dos16_devices_wait(void);
#endif
