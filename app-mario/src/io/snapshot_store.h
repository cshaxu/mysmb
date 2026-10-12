#ifndef MYSMB_IO_SNAPSHOT_STORE_H
#define MYSMB_IO_SNAPSHOT_STORE_H
#include "io/snapshot.h"

enum {
    MYSMB_SNAPSHOT_READ=0, MYSMB_SNAPSHOT_WRITE=1,
    MYSMB_SNAPSHOT_SAVE_ERROR=10, MYSMB_SNAPSHOT_LOAD_ERROR=11
};
struct mysmb_snapshot_files {
    void *context;
    int (*open)(void *context,const char *name,int write,void **handle);
    int (*read)(void *handle,mygames_kvm_u8 *data,mygames_kvm_u16 count,
        mygames_kvm_u16 *actual);
    int (*write)(void *handle,const mygames_kvm_u8 *data,mygames_kvm_u16 count,
        mygames_kvm_u16 *actual);
    /* Flush writes and close,including failure paths. */
    int (*close)(void *handle,int write);
    int (*replace)(void *context,const char *pending,const char *final_name);
    void (*remove)(void *context,const char *name);
    void (*log)(void *context,const char *name,int error);
};
struct mysmb_snapshot_store {
    struct mysmb_snapshot_files files;
    struct mysmb_io_snapshot staging;
};
int mysmb_snapshot_store_initialize(struct mysmb_snapshot_store *store,
    const struct mysmb_snapshot_files *files);
int mysmb_snapshot_save(struct mysmb_snapshot_store *store,
    const struct mysmb_io_snapshot *snapshot);
/* Staging is scratch:the next operation invalidates a borrowed result,even on
 * failure. Only a successful load may be committed to live game state. */
const struct mysmb_io_snapshot *mysmb_snapshot_load(
    struct mysmb_snapshot_store *store,const mygames_kvm_u8 *fingerprint);
#endif
