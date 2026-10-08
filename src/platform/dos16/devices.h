#ifndef MYSMB_DOS16_DEVICES_H
#define MYSMB_DOS16_DEVICES_H
#include "io/input.h"
#include "io/audio.h"
#include "io/planar_frame.h"
struct mysmb_ppu_frame_view;
int mysmb_dos16_devices_open(void);
void mysmb_dos16_devices_close(void);
void mysmb_dos16_devices_input(struct mysmb_io_input *input);
/* Native256x240 chain4 row-major view;never accepts a scaled/plane frame. */
int mysmb_dos16_devices_present_band(const struct mysmb_io_video_band *band);
/* Borrow the native chain-4 destination for one validated logical band.
 * The caller may write the original 256-wide color indices directly, then
 * still calls present_band to complete the ordinary synchronous contract. */
mysmb_io_u8 MYSMB_IO_FAR *mysmb_dos16_devices_direct_band(mysmb_io_u16 first,
    mysmb_io_u16 rows);
void mysmb_dos16_devices_wait(void);
void mysmb_dos16_devices_after_load(void);
void mysmb_dos16_devices_resume_clock(void);
int mysmb_dos16_devices_mode(mysmb_io_u8 text);
void mysmb_dos16_devices_palette(const mysmb_io_u8 MYSMB_IO_FAR *palette);
void mysmb_dos16_devices_text(const struct mysmb_io_text_frame MYSMB_IO_FAR *frame);
/* S7 background-only capability. It is intentionally not the product
 * presenter until S8 restores HUD and sprite damage over the same surface. */
int mysmb_dos16_devices_retained_background(const struct mysmb_ppu_frame_view *view);
/* Complete retained presenter with temporary fixed-HUD/OAM coverage. */
int mysmb_dos16_devices_retained_frame(const struct mysmb_ppu_frame_view *view);
mysmb_io_u8 mysmb_dos16_devices_audio(const struct mysmb_io_audio_frame *frame);
#endif
