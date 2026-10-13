#ifndef MYSMB_PLATFORM_DOS16_DOS_AUDIO_H
#define MYSMB_PLATFORM_DOS16_DOS_AUDIO_H
#include "io/audio_renderer.h"
int mysmb_dos16_audio_dos_open(void);
void mysmb_dos16_audio_dos_close(void);
void mysmb_dos16_audio_dos_after_load(void);
int mysmb_dos16_audio_dos_prepared(void);
mygames_kvm_u8 mysmb_dos16_audio_dos_submit(const struct mysmb_io_audio_frame *frame);
#endif
