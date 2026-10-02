/* Real distance return and Lakitu speed/direction consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 1920u
#define LIMIT 524288u
static int ready(core_machine *m)
{
    core_run_result r;unsigned int n;
    for(n=0u;n<LIMIT;++n){
        if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    }
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char speeds[4]={0u,1u,0x18u,0x19u};
    static const unsigned char turn_speeds[4]={0u,1u,2u,0xffu};
    unsigned char header[12]={'M','S','L','I',1u,0u,0u,0u,0x80u,7u,0u,0u};
    unsigned char record[4100],slot,kind,low,high,borrow;
    unsigned int n,k,i,steps,maxsteps=0u,returns=0u,signs[2]={0u},borrows[2]={0u};
    unsigned int clamps=0u,early=0u,indices[3]={0u},loops=0u,outer[3]={0u};
    core_driver *d=NULL;core_driver_options opt={0u,LIB_FALSE};
    core_run_result result;FILE *file;time_t start=time(NULL);int ok=1;
    if(argc!=3)return 64;
    if(core_driver_create(&d,&opt)!=LIB_STATUS_OK||
        !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(!file)return 65;
    if(fwrite(header,1u,12u,file)!=12u)ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        kind=(unsigned char)(n>=1536u);k=kind==0u?n%256u:(n-1536u)%64u;
        slot=(unsigned char)(kind==0u?n/256u:(n-1536u)/64u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;d->machine->ram[0x0016u+slot]=(unsigned char)(k%2u==0u?17u:18u);
        d->machine->ram[0x001eu+slot]=(unsigned char)(kind==0u?0u:k%8u==0u?0x20u:k%8u==1u?1u:0u);
        d->machine->ram[0x0086u]=(unsigned char)(k*13u);
        d->machine->ram[0x0087u+slot]=(unsigned char)(d->machine->ram[0x0086u]+k);
        d->machine->ram[0x006du]=1u;
        d->machine->ram[0x006eu+slot]=(unsigned char)((k/32u)%3u);
        d->machine->ram[0x00a0u+slot]=(unsigned char)((k/4u)%3u);
        d->machine->ram[0x0058u+slot]=turn_speeds[(k/8u)%4u];
        d->machine->ram[0x0057u]=speeds[(k/16u)%4u];
        d->machine->ram[0x0775u]=(unsigned char)((k/2u)%3u);
        d->machine->ram[0x0401u+slot]=(unsigned char)(k*31u);
        d->machine->ram[0x00cfu+slot]=(unsigned char)(k*17u);d->machine->ram[0x00b6u+slot]=1u;
        d->machine->ram[0x0417u+slot]=(unsigned char)(k*19u);
        d->machine->ram[0x0434u+slot]=(unsigned char)(k*29u);
        d->machine->ram[1u]=(unsigned char)(21u+slot);d->machine->ram[2u]=(unsigned char)(48u-slot);d->machine->ram[3u]=0x40u;
        for(i=0u;i<6u;++i){d->machine->ram[0x0110u+i]=0x55u;d->machine->ram[0x0125u+i]=0xaau;}
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=kind==0u?0xcf6cu:0xcf28u;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        borrow=(unsigned char)(d->machine->ram[0x0087u+slot]<d->machine->ram[0x0086u]);
        low=(unsigned char)(d->machine->ram[0x0087u+slot]-d->machine->ram[0x0086u]);
        high=(unsigned char)(d->machine->ram[0x006eu+slot]-d->machine->ram[0x006du]-borrow);
        if(kind!=0u)++outer[d->machine->ram[0x001eu+slot]==0x20u?2u:d->machine->ram[0x001eu+slot]!=0u?1u:0u];
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            if(d->machine->pc==0xcf71u){
                ++returns;++signs[(high&0x80u)!=0u];++borrows[borrow];
                if(d->machine->x!=slot||d->machine->y!=0u||d->machine->ram[0u]!=low||d->machine->a!=high||
                   (d->machine->p&0x80u)!=(high&0x80u))ok=0;
            }
            /* Named source labels are counted at their decoded addresses. */
            if(d->machine->pc==0xcf83u)++clamps;
            if(d->machine->pc==0xcf9au&&d->machine->a!=0u)++early;
            if(d->machine->pc==0xcfd1u){if(d->machine->y>2u)ok=0;else ++indices[d->machine->y];}
            if(d->machine->pc==0xcfd6u)++loops;
            if(!ok){printf("seam failure case=%u pc=%04x\n",n,d->machine->pc);break;}
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u||d->machine->x!=slot)ok=0;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->y;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u distance-returns=%u sign-clear/set=%u/%u borrow-clear/set=%u/%u maxsteps=%u outer-live/special/defeated=%u/%u/%u\n",n,returns,signs[0],signs[1],borrows[0],borrows[1],maxsteps,outer[0],outer[1],outer[2]);
    printf("clamps=%u early=%u adjustment-indices=%u/%u/%u loop-visits=%u\n",clamps,early,indices[0],indices[1],indices[2],loops);
    if(n!=CASES||returns!=1824u||signs[0]==0u||signs[1]==0u||borrows[0]==0u||borrows[1]==0u||
        clamps==0u||early==0u||indices[0]==0u||indices[1]==0u||indices[2]==0u||loops==0u)ok=0;
    return ok?0:66;
}
