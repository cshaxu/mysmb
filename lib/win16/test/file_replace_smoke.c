#include <stdio.h>
#include <string.h>
#include "win16/file.h"
static int put(const char *name,const char *value){FILE *f=fopen(name,"wb");if(!f)return 0;fputs(value,f);return fclose(f)==0;}
static int is(const char *name,const char *value){char b[16];FILE *f=fopen(name,"rb");unsigned n;if(!f)return 0;n=(unsigned)fread(b,1,15,f);fclose(f);b[n]=0;return !strcmp(b,value);}
int main(void)
{
    remove("slot.sav");remove("slot.bak");remove("slot.tmp");
    if(mygames_win16_file_replace(0,"slot.sav") || mygames_win16_file_replace("slot.tmp","slot.tmp"))return 1;
    if(!put("slot.tmp","first") || !mygames_win16_file_replace("slot.tmp","slot.sav") || !is("slot.sav","first"))return 2;
    if(mygames_win16_file_replace("missing.tmp","slot.sav") || !is("slot.sav","first"))return 3;
    if(!put("slot.tmp","second") || !mygames_win16_file_replace("slot.tmp","slot.sav") || !is("slot.sav","second"))return 4;
    if(mygames_win16_file_replace("slot.tmp","slot.bak") ||
        mygames_win16_file_replace("slot.tmp","slot.BAK") ||
        mygames_win16_file_replace("slot.TMP","slot.tmp"))return 5;
    remove("slot.sav");return 0;
}
