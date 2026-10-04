#include "io/snapshot_store.h"
#include "platform/file/snapshot_files.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_snapshot_store store;
static struct mysmb_io_snapshot state,live;
static mysmb_io_u8 pending[MYSMB_SNAPSHOT_FILE_BYTES+1U],final_file[MYSMB_SNAPSHOT_FILE_BYTES+1U],prior[MYSMB_SNAPSHOT_FILE_BYTES+1U];
static unsigned int pending_size,final_size,offset,write_calls,logs,removed;
static int fault;
static int fake_open(void *ctx,const char *name,int write,void **handle)
{
    (void)ctx;
    if (strcmp(name,write!=0 ? "mysmb.tmp":"mysmb.sav")!=0) return 0;
    if (fault==(write!=0 ? 1:5)) return 0;
    offset=0U;write_calls=0U;
    if (write!=0) pending_size=0U;
    *handle=write!=0 ? pending:final_file;
    return 1;
}
static int fake_write(void *handle,const mysmb_io_u8 *data,mysmb_io_u16 count,
    mysmb_io_u16 *actual)
{
    if (handle!=pending || (fault==2 && ++write_calls>2U)) return 0;
    *actual=count>17U ? 17U:count;
    memcpy(pending+offset,data,*actual);offset+=*actual;pending_size=offset;
    return 1;
}
static int fake_read(void *handle,mysmb_io_u8 *data,mysmb_io_u16 count,
    mysmb_io_u16 *actual)
{
    if (handle!=final_file || fault==6 ||
        (fault==8 && offset>=MYSMB_SNAPSHOT_LEGACY_FILE_BYTES)) return 0;
    if (count>23U) count=23U;
    if (count>final_size-offset) count=(mysmb_io_u16)(final_size-offset);
    memcpy(data,final_file+offset,count);offset+=count;*actual=count;
    return 1;
}
static int fake_close(void *handle,int write)
{
    (void)handle;
    return fault!=(write!=0 ? 3:7);
}
static int fake_replace(void *ctx,const char *from,const char *to)
{
    (void)ctx;
    if (fault==4 || strcmp(from,"mysmb.tmp") || strcmp(to,"mysmb.sav")) return 0;
    memcpy(final_file,pending,pending_size);final_size=pending_size;
    return 1;
}
static void fake_remove(void *ctx,const char *name)
{
    (void)ctx;if (!strcmp(name,"mysmb.tmp")) {pending_size=0U;removed++;}
}
static void fake_log(void *ctx,const char *name,int error)
{
    (void)ctx;
    if (!strcmp(name,"mysmb.log") && (error==10 || error==11)) logs++;
    /* No callback failure can recurse into this log sink. */
}
int main(int argc,char **argv)
{
    struct mysmb_snapshot_files files;
    struct mysmb_file_storage disk;
    const struct mysmb_io_snapshot *loaded;
    unsigned int i;
    char path[300];
    FILE *file;
    if (argc!=2) return 1;
    memset(&state,0,sizeof(state));state.payload[0]=23U;
    files.context=0;files.open=fake_open;files.read=fake_read;files.write=fake_write;
    files.close=fake_close;files.replace=fake_replace;files.remove=fake_remove;
    files.log=fake_log;
    if (!mysmb_snapshot_store_initialize(&store,&files)) return 2;
    if (!mysmb_snapshot_save(&store,&state) || final_size!=MYSMB_SNAPSHOT_FILE_BYTES) return 3;
    loaded=mysmb_snapshot_load(&store,state.fingerprint);
    if (!loaded || memcmp(loaded,&state,sizeof(state))) return 4;
    memcpy(prior,final_file,MYSMB_SNAPSHOT_FILE_BYTES);live=state;state.payload[0]=29U;
    for (fault=1;fault<=4;++fault) {
        logs=0U;removed=0U;
        if (mysmb_snapshot_save(&store,&state) || logs!=1U || removed!=1U ||
            memcmp(prior,final_file,MYSMB_SNAPSHOT_FILE_BYTES) || memcmp(&live,&store.staging,sizeof(live)))
            return 5;
    }
    for (fault=5;fault<=7;++fault) {
        logs=0U;
        if (mysmb_snapshot_load(&store,state.fingerprint) || logs!=1U ||
            memcmp(&live,&store.staging,sizeof(live))) return 6;
    }
    fault=0;final_size=17U;logs=0U;
    if (mysmb_snapshot_load(&store,state.fingerprint) || logs!=1U) return 7;
    final_size=MYSMB_SNAPSHOT_FILE_BYTES+1U;logs=0U;
    if (mysmb_snapshot_load(&store,state.fingerprint) || logs!=1U) return 8;
    final_size=MYSMB_SNAPSHOT_FILE_BYTES;final_file[100]^=1U;
    if (mysmb_snapshot_load(&store,state.fingerprint) ||
        memcmp(&live,&store.staging,sizeof(live))) return 9;
    /* Legacy short EOF is valid, a read error at that boundary is not. */
    memcpy(final_file,prior,MYSMB_SNAPSHOT_LEGACY_FILE_BYTES);
    final_size=MYSMB_SNAPSHOT_LEGACY_FILE_BYTES;
    mysmb_snapshot_put16(final_file+8,1U);mysmb_snapshot_put16(final_file+10,1U);
    mysmb_snapshot_put32(final_file+12,MYSMB_SNAPSHOT_PRESENTATION_OFFSET);
    memcpy(pending,final_file,32U);
    memcpy(pending+32,final_file+36,MYSMB_SNAPSHOT_PRESENTATION_OFFSET);
    mysmb_snapshot_put32(final_file+32,mysmb_snapshot_crc(pending,
        MYSMB_SNAPSHOT_LEGACY_FILE_BYTES-4U));
    fault=8;
    if(mysmb_snapshot_load(&store,state.fingerprint) ||
        memcmp(&live,&store.staging,sizeof(live)))return 20;
    fault=0;loaded=mysmb_snapshot_load(&store,state.fingerprint);
    if(!loaded || memcmp(&live,loaded,sizeof(live)))return 21;
    /* Actual file services: same directory despite arbitrary working dir. */
    if (!mysmb_file_storage_initialize(&disk,argv[1],mysmb_win32_snapshot_replace,
        &files) || !mysmb_snapshot_store_initialize(&store,&files)) return 10;
    if (!mysmb_snapshot_save(&store,&state)) return 11;
    state.payload[0]=31U;
    if (!mysmb_snapshot_save(&store,&state)) return 12;
    loaded=mysmb_snapshot_load(&store,state.fingerprint);
    if (!loaded || memcmp(loaded,&state,sizeof(state))) return 13;
    sprintf(path,"%s/mysmb.sav",argv[1]);file=fopen(path,"ab");
    if (!file || fputc(0x55,file)==EOF || fclose(file)!=0) return 14;
    if (mysmb_snapshot_load(&store,state.fingerprint)) return 15;
    (void)remove(path);
    if (mysmb_snapshot_load(&store,state.fingerprint)) return 16;
    sprintf(path,"%s/mysmb.log",argv[1]);file=fopen(path,"rb");
    if (!file) return 17;i=0U;while (fgetc(file)!=EOF) ++i;(void)fclose(file);
    if (i==0U) return 18;
    (void)remove(path);
    /* A missing directory makes both save and log fail silently. */
    sprintf(path,"%s/nonexistent",argv[1]);
    if (!mysmb_file_storage_initialize(&disk,path,mysmb_win32_snapshot_replace,
        &files) || !mysmb_snapshot_store_initialize(&store,&files) ||
        mysmb_snapshot_save(&store,&state)) return 19;
    return 0;
}
