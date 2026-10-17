#include "app/runtime_options.h"
int main(void)
{
    if(mysmb_app_runtime_options(0)!=-1)return 1;
    if(mysmb_app_runtime_options("")!=0 ||
        mysmb_app_runtime_options(" \t ")!=0)return 2;
    if(mysmb_app_runtime_options(" --turbo\t")!=1)return 3;
    /* Repeated idempotent flag is allowed; no other token is accepted. */
    if(mysmb_app_runtime_options("--turbo --turbo")!=1)return 4;
    if(mysmb_app_runtime_options("--turb")!=-1 ||
        mysmb_app_runtime_options("--turbo=1")!=-1 ||
        mysmb_app_runtime_options("--turbo x")!=-1 ||
        mysmb_app_runtime_options("--TURBO")!=-1)return 5;
    {
        char long_token[129];unsigned short i;
        for(i=0U;i<128U;++i)long_token[i]='a';
        long_token[128]='\0';
        if(mysmb_app_runtime_options(long_token)!=-1)return 6;
    }
    return 0;
}
