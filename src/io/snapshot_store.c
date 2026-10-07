#include "io/snapshot_store.h"
#include <string.h>

static const char pending_name[]="mysmb.tmp";
static const char final_name[]="mysmb.sav";
static const char log_name[]="mysmb.log";

static int write_exact(struct mysmb_snapshot_files *files,void *handle,
    const mysmb_io_u8 *data,mysmb_io_u16 count)
{
    mysmb_io_u16 actual;
    while(count) {
        actual=0U;
        if(!files->write(handle,data,count,&actual) || !actual || actual>count)return 0;
        data+=actual;count=(mysmb_io_u16)(count-actual);
    }
    return 1;
}
static int read_exact(struct mysmb_snapshot_files *files,void *handle,
    mysmb_io_u8 *data,mysmb_io_u16 count)
{
    mysmb_io_u16 actual;
    while(count) {
        actual=0U;
        if(!files->read(handle,data,count,&actual) || !actual || actual>count)return 0;
        data+=actual;count=(mysmb_io_u16)(count-actual);
    }
    return 1;
}

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
    mysmb_io_u8 header[MYSMB_SNAPSHOT_HEADER_BYTES];
    int ok;
    if (snapshot==0) return 0;
    files=&store->files;
    handle=0;ok=0;
    if (mysmb_snapshot_encode_header(snapshot,header)!=0)
        goto failed;
    if (!files->open(files->context,pending_name,MYSMB_SNAPSHOT_WRITE,&handle))
        goto failed;
    ok=write_exact(files,handle,header,MYSMB_SNAPSHOT_HEADER_BYTES) &&
        write_exact(files,handle,snapshot->payload,MYSMB_SNAPSHOT_PAYLOAD_BYTES);
    if(!files->close(handle,MYSMB_SNAPSHOT_WRITE))ok=0;
    handle=0;
    if (!ok) goto failed;
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
    mysmb_io_u8 header[MYSMB_SNAPSHOT_HEADER_BYTES],extra;
    mysmb_io_u16 payload,actual;
    int ok;
    files=&store->files;handle=0;payload=0U;ok=0;
    if (!files->open(files->context,final_name,MYSMB_SNAPSHOT_READ,&handle))
        goto failed;
    if(read_exact(files,handle,header,MYSMB_SNAPSHOT_HEADER_BYTES))
        payload=mysmb_snapshot_header_payload(header);
    if(payload && read_exact(files,handle,store->staging.payload,payload)) {
        actual=0U;
        ok=files->read(handle,&extra,1U,&actual) && actual==0U;
    }
    if (!files->close(handle,MYSMB_SNAPSHOT_READ)) ok=0;
    if (!ok || mysmb_snapshot_check_parts(header,store->staging.payload,payload,
        fingerprint)!=0) goto failed;
    memcpy(store->staging.fingerprint,header+16,16U);
    if(payload==MYSMB_SNAPSHOT_PRESENTATION_OFFSET)
        memset(store->staging.payload+MYSMB_SNAPSHOT_PRESENTATION_OFFSET,0,
            MYSMB_SNAPSHOT_PRESENTATION_BYTES);
    return &store->staging;
failed:
    files->log(files->context,log_name,MYSMB_SNAPSHOT_LOAD_ERROR);
    return 0;
}
