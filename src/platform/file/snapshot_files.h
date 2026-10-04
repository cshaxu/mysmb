#ifndef MYSMB_PLATFORM_SNAPSHOT_FILES_H
#define MYSMB_PLATFORM_SNAPSHOT_FILES_H
#include "io/snapshot_store.h"

struct mysmb_file_storage {
    char directory[260];
    int (*replace)(const char *pending,const char *final_name);
};
int mysmb_file_storage_initialize(struct mysmb_file_storage *storage,
    const char *directory,int (*replace)(const char *,const char *),
    struct mysmb_snapshot_files *files);
int mysmb_win32_snapshot_replace(const char *pending,const char *final_name);
int mysmb_dos16_snapshot_replace(const char *pending,const char *final_name);
#endif
