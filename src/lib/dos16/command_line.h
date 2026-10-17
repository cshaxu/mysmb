#ifndef MYGAMES_DOS16_COMMAND_LINE_H
#define MYGAMES_DOS16_COMMAND_LINE_H
#include "kvm/types.h"
/* Copy a PSP length-prefixed tail to a bounded NUL-terminated buffer.
 * No option interpretation belongs to this physical boundary. */
int mygames_dos16_command_tail_copy(
    const mygames_kvm_u8 MYGAMES_KVM_FAR *tail,char *output,
    unsigned short capacity);
/* Current process PSP; available only on the physical DOS host. */
int mygames_dos16_command_line(char *output,unsigned short capacity);
#endif
