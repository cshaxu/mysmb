#include "io/snapshot_store.h"

static const char pending_name[]="mysmb.tmp";
static const char final_name[]="mysmb.sav";
static const char log_name[]="mysmb.log";

int mysmb_snapshot_store_initialize(struct mysmb_snapshot_store *store,
    const struct mysmb_snapshot_files *files)
{
    if (files==0 || files->open==0 || files->read==0 || files->write==0 ||
        files->close==0 || files->replace==0 || files->remove==0 || files->log==0)
        return 0;
    store->files=*files;
    return 1;
}
int mysmb_snapshot_save(struct mysmb_snapshot_store *store,
    const struct mysmb_io_snapshot *snapshot)
{
    struct mysmb_snapshot_files *files;
    void *handle;
    mysmb_io_u16 offset,actual;
    int ok;
    if (snapshot==0) return 0;
    files=&store->files;
    handle=0;ok=0;
    if (mysmb_snapshot_encode(snapshot,store->wire,MYSMB_SNAPSHOT_FILE_BYTES)!=0)
        goto failed;
    if (!files->open(files->context,pending_name,MYSMB_SNAPSHOT_WRITE,&handle))
        goto failed;
    offset=0U;
    while (offset<MYSMB_SNAPSHOT_FILE_BYTES) {
        actual=0U;
        if (!files->write(handle,store->wire+offset,
            (mysmb_io_u16)(MYSMB_SNAPSHOT_FILE_BYTES-offset),&actual) ||
            actual==0U || actual>MYSMB_SNAPSHOT_FILE_BYTES-offset) break;
        offset=(mysmb_io_u16)(offset+actual);
    }
    ok=files->close(handle,MYSMB_SNAPSHOT_WRITE);
    handle=0;
    if (!ok || offset!=MYSMB_SNAPSHOT_FILE_BYTES) goto failed;
    if (!files->replace(files->context,pending_name,final_name)) goto failed;
    return 1;
failed:
    files->remove(files->context,pending_name);
    files->log(files->context,log_name,MYSMB_SNAPSHOT_SAVE_ERROR);
    return 0;
}
const struct mysmb_io_snapshot *mysmb_snapshot_load(
    struct mysmb_snapshot_store *store,const mysmb_io_u8 *fingerprint)
{
    struct mysmb_snapshot_files *files;
    void *handle;
    mysmb_io_u16 offset,actual;
    int ok;
    files=&store->files;handle=0;offset=0U;
    if (!files->open(files->context,final_name,MYSMB_SNAPSHOT_READ,&handle))
        goto failed;
    while (offset<MYSMB_SNAPSHOT_FILE_BYTES) {
        actual=0U;
        if (!files->read(handle,store->wire+offset,
            (mysmb_io_u16)(MYSMB_SNAPSHOT_FILE_BYTES-offset),&actual) ||
            actual==0U || actual>MYSMB_SNAPSHOT_FILE_BYTES-offset) break;
        offset=(mysmb_io_u16)(offset+actual);
    }
    actual=0U;ok=0;
    if (offset==MYSMB_SNAPSHOT_FILE_BYTES)
        ok=files->read(handle,store->wire+offset,1U,&actual) && actual==0U;
    if (!files->close(handle,MYSMB_SNAPSHOT_READ)) ok=0;
    if (!ok || mysmb_snapshot_decode(store->wire,offset,fingerprint,
        &store->staging)!=0) goto failed;
    return &store->staging;
failed:
    files->log(files->context,log_name,MYSMB_SNAPSHOT_LOAD_ERROR);
    return 0;
}
