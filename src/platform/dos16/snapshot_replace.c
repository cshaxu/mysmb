#include "platform/file/snapshot_files.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
int mysmb_dos16_snapshot_replace(const char *pending,const char *final_name)
{
    /* DOS rename cannot atomically replace. Preserve the old slot until this
     * final close-complete window,then report any rename failure to shared IO. */
    if (remove(final_name)!=0 && errno!=ENOENT) return 0;
    return rename(pending,final_name)==0;
}
