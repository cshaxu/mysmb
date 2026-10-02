/* Real Flying Cheep movement descendants and source return consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 1536u
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
    static const unsigned char speeds[8]={0u,1u,4u,5u,0x7fu,0x80u,0xfcu,0xffu};
    unsigned char header[12]={'M','S','C','I',1u,0u,0u,0u,0u,6u,0u,0u};
    unsigned char record[4100],slot,displacement=0u,speed;
    unsigned int n,k,i,steps,maxsteps=0u,hreturns=0u,vreturns=0u,dead=0u;
    unsigned int indices[16]={0u},thresholds[2]={0u},signs[3]={0u},integer;
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
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        slot=(unsigned char)(n/256u);k=n%256u;
        d->machine->ram[8u]=slot;
        d->machine->ram[0x001eu+slot]=(unsigned char)(k>=224u?0x20u:0u);
        d->machine->ram[0x0058u+slot]=(unsigned char)k;
        d->machine->ram[0x006eu+slot]=(unsigned char)(k%3u==0u?0u:k%3u==1u?1u:0xffu);
        d->machine->ram[0x0087u+slot]=(unsigned char)(k*31u);
        d->machine->ram[0x0401u+slot]=(unsigned char)(k*17u);
        d->machine->ram[0x00a0u+slot]=speeds[k%8u];
        d->machine->ram[0x00b6u+slot]=(unsigned char)(1u+k%2u);
        d->machine->ram[0x00cfu+slot]=(unsigned char)(k*13u);
        d->machine->ram[0x0417u+slot]=(unsigned char)(k*29u);
        d->machine->ram[0x0434u+slot]=(unsigned char)(k*7u);
        d->machine->ram[0x03c5u+slot]=0x55u;
        for(i=0u;i<6u;++i){d->machine->ram[0x0110u+i]=0x55u;d->machine->ram[0x0125u+i]=0xaau;}
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=0xcedfu;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        record[0]=slot;record[1]=(unsigned char)(k>=224u);
        memcpy(record+4u,d->machine->ram,2048u);
        speed=d->machine->ram[0x0058u+slot];integer=speed>>4u;if(integer>=8u)integer|=0xf0u;
        displacement=(unsigned char)(integer+((unsigned int)d->machine->ram[0x0401u+slot]+(unsigned char)(speed<<4u)>255u?1u:0u));
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            if(d->machine->pc==0xcef0u){
                ++hreturns;++signs[displacement==0u?0u:(displacement&0x80u)!=0u?2u:1u];
                if(d->machine->x!=slot||d->machine->a!=displacement)ok=0;
            }
            if(d->machine->pc==0xcef4u&&
                (d->machine->a!=5u||d->machine->y!=0x0du||d->machine->x!=slot))ok=0;
            if(d->machine->pc==0xcef7u){
                ++vreturns;if(d->machine->x!=slot||d->machine->ram[0u]!=0x0du||d->machine->ram[2u]!=5u)ok=0;
            }
            if(d->machine->pc==0xcf0cu)++thresholds[d->machine->a<8u?0u:1u];
            if(d->machine->pc==0xcf1eu){++indices[d->machine->y&15u];if(d->machine->x!=slot||d->machine->y>15u)ok=0;}
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x\n",n,d->machine->pc,d->machine->x);break;}
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u||d->machine->x!=slot)ok=0;
        if(record[1]!=0u)++dead;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->x;record[3]=d->machine->y;
        memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u horizontal/vertical-returns=%u/%u defeated=%u maxsteps=%u signs=%u/%u/%u threshold-below/above=%u/%u\n",n,hreturns,vreturns,dead,maxsteps,signs[0],signs[1],signs[2],thresholds[0],thresholds[1]);
    printf("priority-index-counts=");for(i=0u;i<16u;++i){printf("%u%s",indices[i],i==15u?"\n":"/");if(indices[i]==0u)ok=0;}
    if(n!=CASES||hreturns!=1344u||vreturns!=1344u||dead!=192u||thresholds[0]==0u||thresholds[1]==0u||signs[0]==0u||signs[1]==0u||signs[2]==0u)ok=0;
    return ok?0:66;
}
