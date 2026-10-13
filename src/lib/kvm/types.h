#ifndef MYGAMES_KVM_TYPES_H
#define MYGAMES_KVM_TYPES_H

/* Host-neutral C90 contract widths; no original RAM, application or device ownership. */
typedef unsigned char mygames_kvm_u8;
typedef unsigned short mygames_kvm_u16;

/* Bounded borrowed storage need not be in DGROUP.
 * Only the pointer representation changes for the real-mode compiler. */
#ifdef MYGAMES_DOS16_TARGET
#define MYGAMES_KVM_FAR __far
#else
#define MYGAMES_KVM_FAR
#endif

typedef char mygames_kvm_byte_width[(sizeof(mygames_kvm_u8) == 1U) ? 1 : -1];
typedef char mygames_kvm_word_width[(sizeof(mygames_kvm_u16) == 2U) ? 1 : -1];

#endif
