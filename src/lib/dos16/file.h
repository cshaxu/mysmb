#ifndef MYGAMES_DOS16_FILE_H
#define MYGAMES_DOS16_FILE_H
#include "kvm/types.h"
int mygames_dos16_executable_path(char *path,mygames_kvm_u16 capacity);
int mygames_dos16_file_replace(const char *pending,const char *final_name);
#endif
