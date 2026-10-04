#include "platform/file/snapshot_files.h"
#include <stdio.h>
#include <string.h>

static int path(struct mysmb_file_storage *storage,const char *name,char *out)
{
    size_t n,m;
    n=strlen(storage->directory);m=strlen(name);
    if (n==0U || n+m+2U>260U) return 0;
    memcpy(out,storage->directory,n);
    if (out[n-1U]!='/' && out[n-1U]!='\\') out[n++]='/';
    memcpy(out+n,name,m+1U);
    return 1;
}
static int open_file(void *context,const char *name,int write,void **handle)
{
    char filename[260];
    FILE *file;
    if (!path(context,name,filename)) return 0;
    file=fopen(filename,write!=0 ? "wb":"rb");
    if (file==0) return 0;
    *handle=file;return 1;
}
static int read_file(void *handle,mysmb_io_u8 *data,mysmb_io_u16 count,
    mysmb_io_u16 *actual)
{
    *actual=(mysmb_io_u16)fread(data,1U,count,(FILE *)handle);
    return ferror((FILE *)handle)==0;
}
static int write_file(void *handle,const mysmb_io_u8 *data,mysmb_io_u16 count,
    mysmb_io_u16 *actual)
{
    *actual=(mysmb_io_u16)fwrite(data,1U,count,(FILE *)handle);
    return ferror((FILE *)handle)==0;
}
static int close_file(void *handle,int write)
{
    int ok;
    ok=write==0 || fflush((FILE *)handle)==0;
    if (fclose((FILE *)handle)!=0) ok=0;
    return ok;
}
static int replace_file(void *context,const char *pending,const char *final_name)
{
    struct mysmb_file_storage *storage;
    char from[260],to[260];
    storage=context;
    if (!path(storage,pending,from) || !path(storage,final_name,to)) return 0;
    return storage->replace(from,to);
}
static void remove_file(void *context,const char *name)
{
    char filename[260];
    if (path(context,name,filename)) (void)remove(filename);
}
static void log_file(void *context,const char *name,int error)
{
    char filename[260];
    FILE *file;
    if (!path(context,name,filename)) return;
    file=fopen(filename,"ab");
    if (file==0) return;
    (void)fprintf(file,"snapshot error %d\n",error);
    (void)fclose(file);
}
int mysmb_file_storage_initialize(struct mysmb_file_storage *storage,
    const char *directory,int (*replace)(const char *,const char *),
    struct mysmb_snapshot_files *files)
{
    size_t size;
    if (directory==0 || replace==0) return 0;
    size=strlen(directory);
    if (size==0U || size>=sizeof(storage->directory)) return 0;
    memcpy(storage->directory,directory,size+1U);storage->replace=replace;
    files->context=storage;files->open=open_file;files->read=read_file;
    files->write=write_file;files->close=close_file;files->replace=replace_file;
    files->remove=remove_file;files->log=log_file;
    return 1;
}
