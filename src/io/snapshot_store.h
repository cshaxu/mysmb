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
    int (*read)(void *handle,mysmb_io_u8 *data,mysmb_io_u16 count,
        mysmb_io_u16 *actual);
    int (*write)(void *handle,const mysmb_io_u8 *data,mysmb_io_u16 count,
        mysmb_io_u16 *actual);
    /* Flush writes and close,including failure paths. */
    int (*close)(void *handle,int write);
    int (*replace)(void *context,const char *pending,const char *final_name);
    void (*remove)(void *context,const char *name);
    void (*log)(void *context,const char *name,int error);
};
struct mysmb_snapshot_store {
    struct mysmb_snapshot_files files;
    mysmb_io_u8 wire[MYSMB_SNAPSHOT_FILE_BYTES+1U];
    struct mysmb_io_snapshot staging;
};
int mysmb_snapshot_store_initialize(struct mysmb_snapshot_store *store,
    const struct mysmb_snapshot_files *files);
int mysmb_snapshot_save(struct mysmb_snapshot_store *store,
    const struct mysmb_io_snapshot *snapshot);
/* A successful result borrows staging until the next operation. */
const struct mysmb_io_snapshot *mysmb_snapshot_load(
    struct mysmb_snapshot_store *store,const mysmb_io_u8 *fingerprint);
#endif
