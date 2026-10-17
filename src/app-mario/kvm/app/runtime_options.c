#include "app/runtime_options.h"
#include <string.h>
int mysmb_app_runtime_options(const char *tail)
{
    const char *first;
    unsigned short length;
    int turbo=0;
    if(!tail)return -1;
    while(*tail) {
        while(*tail==' ' || *tail=='\t')++tail;
        if(!*tail)break;
        first=tail;length=0U;
        while(*tail && *tail!=' ' && *tail!='\t') {
            if(length==126U)return -1;
            ++tail;++length;
        }
        if(length!=7U || strncmp(first,"--turbo",7U)!=0)return -1;
        turbo=1;
    }
    return turbo;
}
