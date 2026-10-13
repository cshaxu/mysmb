#include "win16/file.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
static int same_name(const char *a,const char *b)
{
    unsigned char x,y;
    do {
        x=(unsigned char)*a++;y=(unsigned char)*b++;
        if(x>='a' && x<='z')x=(unsigned char)(x-'a'+'A');
        if(y>='a' && y<='z')y=(unsigned char)(y-'a'+'A');
        if(x=='/')x='\\';if(y=='/')y='\\';
        if(x!=y)return 0;
    }while(x);
    return 1;
}
int mygames_win16_file_replace(const char *pending,const char *final_name)
{
    char backup[260];
    unsigned short i,last=0U;
    int had_old=0;
    if(!pending || !final_name || same_name(pending,final_name))return 0;
    for(i=0U;final_name[i];++i) {
        if(i>=sizeof(backup)-5U)return 0;
        backup[i]=final_name[i];
        if(final_name[i]=='/' || final_name[i]=='\\')last=0U;
        if(final_name[i]=='.')last=i;
    }
    if(!i)return 0;
    if(last)i=last;
    memcpy(backup+i,".bak",5U);
    if(same_name(backup,final_name) || same_name(backup,pending))return 0;
    /* Check the completed candidate before touching an existing slot. */
    {FILE *file=fopen(pending,"rb");if(!file)return 0;if(fclose(file))return 0;}
    if(remove(backup)!=0 && errno!=ENOENT)return 0;
    if(rename(final_name,backup)==0)had_old=1;
    else if(errno!=ENOENT)return 0;
    if(rename(pending,final_name)!=0) {
        if(had_old)(void)rename(backup,final_name);
        return 0;
    }
    if(had_old)(void)remove(backup);
    return 1;
}
