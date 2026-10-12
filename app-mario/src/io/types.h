#ifndef MYSMB_IO_TYPES_H
#define MYSMB_IO_TYPES_H

/* Host-neutral C90 contract widths; no original RAM or device ownership. */
typedef unsigned char mysmb_io_u8;
typedef unsigned short mysmb_io_u16;

/* A 61,440-byte frame fits one segment, but its storage need not be in DGROUP.
 * Only the pointer representation changes for the real-mode compiler. */
#ifdef MYSMB_DOS16_TARGET
#define MYSMB_IO_FAR __far
#else
#define MYSMB_IO_FAR
#endif

typedef char mysmb_io_byte_width[(sizeof(mysmb_io_u8) == 1U) ? 1 : -1];
typedef char mysmb_io_word_width[(sizeof(mysmb_io_u16) == 2U) ? 1 : -1];

#endif
