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
int mysmb_dos16_devices_present_band(const struct mygames_kvm_video_band *band);
/* Commit one complete, native 256x240 slot surface in one Chain-4 transfer.
 * PPU selection and composition are complete before this physical call. */
int mysmb_dos16_devices_present_screen(const mygames_kvm_u8 MYGAMES_KVM_FAR *screen);
/* Borrow the native chain-4 destination for one validated logical band.
 * The caller may write the original 256-wide color indices directly, then
 * still calls present_band to complete the ordinary synchronous contract. */
mygames_kvm_u8 MYGAMES_KVM_FAR *mysmb_dos16_devices_direct_band(mygames_kvm_u16 first,
    mygames_kvm_u16 rows);
void mysmb_dos16_devices_wait(void);
/* Default DOS presentation policy: logical work continues while a late
 * display frame is dropped. */
int mysmb_dos16_devices_should_present(void);
void mysmb_dos16_devices_after_load(void);
void mysmb_dos16_devices_resume_clock(void);
int mysmb_dos16_devices_mode(mygames_kvm_u8 text);
void mysmb_dos16_devices_palette(const mygames_kvm_u8 MYGAMES_KVM_FAR *palette);
void mysmb_dos16_devices_text(const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame);
/* S7 background-only capability. It is intentionally not the product
 * presenter until S8 restores HUD and sprite damage over the same surface. */
int mysmb_dos16_devices_retained_background(const struct mysmb_ppu_frame_view *view);
/* Complete retained presenter with temporary fixed-HUD/OAM coverage. */
int mysmb_dos16_devices_retained_frame(const struct mysmb_ppu_frame_view *view);
mygames_kvm_u8 mysmb_dos16_devices_audio(const struct mysmb_io_audio_frame *frame);
#endif
