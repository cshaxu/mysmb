#ifndef MYGAMES_WIN16_FILE_H
#define MYGAMES_WIN16_FILE_H
#include "kvm/types.h"
int mygames_win16_executable_path(mygames_kvm_u16 instance,char *path,mygames_kvm_u16 capacity);
/* Close-complete rename with an 8.3 backup; failed promotion restores old slot.
 * A filesystem failure during rollback leaves the old bytes in the .bak file. */
int mygames_win16_file_replace(const char *pending,const char *final_name);
#endif
