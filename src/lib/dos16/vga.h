#ifndef MYGAMES_DOS16_VGA_H
#define MYGAMES_DOS16_VGA_H
#include "kvm/types.h"
/* Borrowed physical apertures. Caller supplies device-layout offsets and
 * bounded spans; no game/PPU state or storage policy lives in this device. */
#define mygames_dos16_vga_memory() ((mygames_kvm_u8 MYGAMES_KVM_FAR *)0xa0000000UL)
#define mygames_dos16_text_memory() ((volatile unsigned short MYGAMES_KVM_FAR *)0xb8000000UL)
void mygames_dos16_copy_bytes(unsigned char MYGAMES_KVM_FAR *destination,
    const unsigned char MYGAMES_KVM_FAR *source,unsigned short bytes);
/* Both segment spans must contain bytes; dword count must be divisible by4. */
void mygames_dos16_copy_dwords(unsigned char MYGAMES_KVM_FAR *destination,
    const unsigned char MYGAMES_KVM_FAR *source,unsigned short bytes);
void mygames_dos16_vga_register(unsigned short port,unsigned char index,unsigned char value);
int mygames_dos16_vga_bios_mode(unsigned char mode);
void mygames_dos16_vga_color(unsigned char index,unsigned long rgb);
void mygames_dos16_vga_native(void);
void mygames_dos16_vga_planar512(void);
void mygames_dos16_vga_planar264(unsigned short start);
void mygames_dos16_vga_plane(unsigned char plane);
void mygames_dos16_vga_viewport(unsigned short start,unsigned char pan);
#endif
