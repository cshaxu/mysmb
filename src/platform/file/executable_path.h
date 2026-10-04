#ifndef MYSMB_PLATFORM_EXECUTABLE_PATH_H
#define MYSMB_PLATFORM_EXECUTABLE_PATH_H
#include "io/types.h"
int mysmb_file_executable_directory(const char *path,char *directory,
    mysmb_io_u16 capacity);
int mysmb_dos16_executable_path(char *path,mysmb_io_u16 capacity);
#endif
