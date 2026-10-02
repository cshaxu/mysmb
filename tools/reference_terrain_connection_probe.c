/* Original terrain entry/hidden call and table-consumer proof, local ROM only. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 800u
#define LIMIT 524288u
static int ready(core_machine *m)
{
    core_run_result r;unsigned int n;
    for(n=0u;n<LIMIT;++n){if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char tiles[4]={0u,0x5fu,0x60u,0x61u};
    unsigned char head[12]={'M','S','T','C',1u,0u,0u,0u,0x20u,3u,0u,0u},rec[4105];
    core_driver *d=NULL;core_driver_options opts={0u,LIB_FALSE};core_run_result r;
    FILE *f;unsigned int n,k,input,i,step,pc,beq=0u,fall=0u,sidecalls=0u,sidereturns=0u,maxstep=0u;
    int ok=1;time_t start=time(NULL);
    if(argc!=3)return 64;
    if(core_driver_create(&d,&opts)!=LIB_STATUS_OK||
       !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));f=fopen(argv[2],"wb");if(f==NULL)return 65;
    if(fwrite(head,1u,sizeof(head),f)!=sizeof(head))ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        k=n<32u?0u:1u+(n-32u)/256u;input=k==0u?n:(n-32u)%256u;
        memset(d->machine->ram,0,2048u);
        if(k==0u){
            d->machine->ram[0x000eu]=8u;d->machine->ram[0x006du]=1u;
            d->machine->ram[0x0086u]=0x80u;d->machine->ram[0x00b5u]=1u;d->machine->ram[0x00ceu]=0x80u;
            d->machine->ram[0x0754u]=(unsigned char)(input&1u);
            d->machine->ram[0x0714u]=(unsigned char)((input>>1u)&1u);
            d->machine->ram[0x0704u]=(unsigned char)((input>>2u)&1u);
            d->machine->ram[0x074eu]=1u;d->machine->ram[0x071au]=1u;d->machine->ram[0x071bu]=1u;
            for(i=0u;i<208u;++i){d->machine->ram[0x0500u+i]=tiles[input/8u];d->machine->ram[0x0600u+i]=tiles[input/8u];}
        }
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->a=(unsigned char)input;d->machine->x=0x55u;d->machine->y=0x44u;
        d->machine->s=0xfdu;d->machine->pc=k==0u?0xdc64u:(k==1u?0xdf8fu:(k==2u?0xdf9au:0xdebdu));
        rec[0]=(unsigned char)k;rec[1]=(unsigned char)input;rec[6]=rec[7]=rec[8]=0xffu;
        memcpy(rec+9u,d->machine->ram,2048u);
        for(step=0u;step<LIMIT&&d->machine->pc!=0x8001u;++step){
            pc=d->machine->pc;if(k==0u&&pc==0xdcbau)rec[6]=d->machine->x;
            if(k==0u&&pc==0xdd9cu){rec[7]=d->machine->a;++sidecalls;}
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid){ok=0;break;}
            if(k==0u&&pc==0xdcb7u){if(d->machine->pc==0xdcb9u)++fall;else ++beq;}
            if(k==0u&&pc==0xdec3u&&d->machine->pc==0xdd9fu){++sidereturns;rec[8]=d->machine->p&2u;}
        }
        if(d->machine->pc!=0x8001u)ok=0;if(step>maxstep)maxstep=step;
        rec[2]=d->machine->a;rec[3]=d->machine->x;rec[4]=d->machine->y;rec[5]=d->machine->p;
        memcpy(rec+2057u,d->machine->ram,2048u);
        if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u GBB-head-taken=%u fallthrough=%u side-calls=%u returns=%u\n",n,maxstep,beq,fall,sidecalls,sidereturns);
    return ok?0:66;
}
