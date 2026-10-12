#ifndef MYSMB_IO_EXECUTABLE_PATH_H
#define MYSMB_IO_EXECUTABLE_PATH_H
#include "kvm/types.h"
int mysmb_file_executable_directory(const char *path,char *directory,
    mygames_kvm_u16 capacity);
#endif
