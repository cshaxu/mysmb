/* Real fireworks relative return, phase, drawing and score consumers. */
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
    static const unsigned char oam[4]={0x20u,0xf0u,0xf8u,0xfcu};
    unsigned char header[12]={'M','S','F','W',1u,0u,0u,0u,0u,6u,0u,0u};
    unsigned char record[4100],slot,kind;
    unsigned int n,k,i,steps,maxsteps=0u,relative=0u,draws=0u,terminal=0u;
    unsigned int phases[3]={0u,0u,0u};
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
        kind=0u;k=n%256u;slot=(unsigned char)(n/256u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;d->machine->ram[0x000fu+slot]=1u;
        d->machine->ram[0x0016u+slot]=0x16u;
        d->machine->ram[0x00a0u+slot]=(unsigned char)(k%4u==0u?0u:k%4u==1u?1u:k%4u==2u?2u:8u);
        d->machine->ram[0x0058u+slot]=(unsigned char)(k/4u%3u);
        if(k==253u)d->machine->ram[0x0058u+slot]=0xffu;
        if(k==249u)d->machine->ram[0x0058u+slot]=0xfeu;
        d->machine->ram[0x006eu+slot]=(unsigned char)(k/32u%3u);
        d->machine->ram[0x0087u+slot]=(unsigned char)(k*13u);
        d->machine->ram[0x00b6u+slot]=(unsigned char)(1u+k/64u%2u);
        d->machine->ram[0x00cfu+slot]=(unsigned char)(k*7u);
        d->machine->ram[0x06e5u+slot]=oam[k/64u%4u];
        d->machine->ram[0x071au]=1u;d->machine->ram[0x071bu]=2u;
        d->machine->ram[0x071cu]=0x80u;d->machine->ram[0x071du]=0x7fu;
        d->machine->ram[0x0753u]=(unsigned char)(k/8u%2u);
        d->machine->ram[0x0770u]=(unsigned char)(k/16u%2u);
        for(i=0x07ddu;i<=0x07e8u;++i)d->machine->ram[i]=(unsigned char)(k/32u%2u==0u?0u:9u);
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=0xd295u;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            if(d->machine->pc==0xd2a8u){++relative;
                if(d->machine->x!=slot||d->machine->a!=d->machine->ram[0x03aeu])ok=0;
            }
            if(d->machine->pc==0xd2b9u){++draws;
                if(d->machine->x!=slot||d->machine->y!=d->machine->ram[0x06e5u+slot]||
                   d->machine->a!=d->machine->ram[0x0058u+slot]||d->machine->a>=3u||
                   d->machine->ram[0x03bau]!=d->machine->ram[0x03b9u]||
                   d->machine->ram[0x03afu]!=d->machine->ram[0x03aeu])ok=0;
                if(d->machine->a<3u)++phases[d->machine->a];
            }
            if(d->machine->pc==0xd2bdu)++terminal;
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x\n",n,d->machine->pc,d->machine->x);break;}
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u )ok=0;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->x;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u relative/draw=%u/%u score-tail=%u phases=%u/%u/%u maxsteps=%u\n",n,relative,draws,terminal,phases[0],phases[1],phases[2],maxsteps);
    if(n!=CASES||relative!=draws||terminal==0u||relative+terminal!=CASES||phases[0]==0u||phases[1]==0u||phases[2]==0u)ok=0;
    return ok?0:66;
}
