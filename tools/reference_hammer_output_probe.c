/* Original DrawHammer with indexed tables and actual DumpTwoSpr returns. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 13824u
#define LIMIT 524288u
static int ready(core_machine *m)
{
    core_run_result r;unsigned int i;
    for(i=0u;i<LIMIT;++i){
        if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    }
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char states[6]={1u,1u,0x81u,0u,2u,0xffu};
    static const unsigned char timers[6]={0u,1u,0u,0u,0u,0x80u};
    static const unsigned short table_pc[7]={0xe50cu,0xe4fbu,0xe513u,0xe502u,0xe519u,0xe51fu,0xe525u};
    unsigned char header[12]={'M','S','H','G',1u,0u,0u,0u,0u,0x36u,0u,0u};
    unsigned char record[6152],slot,oam;unsigned int n,k,scenario,i,j,steps,pc,maxsteps=0u;
    unsigned int reads[7][4]={{0u}},timer_skip=0u,state_animate=0u,state_force=0u;
    unsigned int forced=0u,animated=0u,rendered=0u,visible=0u,hidden=0u,returns=0u;
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};core_run_result result;
    FILE *file;time_t start=time(NULL);int ok=1;
    if(argc!=3)return 64;
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||
       !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));file=fopen(argv[2],"wb");if(!file)return 65;
    if(fwrite(header,1u,12u,file)!=12u)ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*19u+n*7u);
        k=n%256u;scenario=(n/256u)%6u;slot=(unsigned char)(n/1536u);
        oam=(unsigned char)(k>=128u?0xf8u:0x20u+slot*8u);
        d->machine->ram[8u]=slot;d->machine->ram[0x06f3u+slot]=oam;
        d->machine->ram[0x002au+slot]=states[scenario];d->machine->ram[0x0747u]=timers[scenario];
        d->machine->ram[9u]=(unsigned char)k;
        d->machine->ram[0x03b3u]=(unsigned char)(k*17u);d->machine->ram[0x03beu]=(unsigned char)(k*13u);
        d->machine->ram[0x03d6u]=(unsigned char)(k*29u);
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=0xe4dcu;d->machine->x=slot;d->machine->y=0xadu;d->machine->a=0x55u;d->machine->s=0xfdu;
        memset(record,0,sizeof(record));record[0]=slot;record[2]=oam;
        memcpy(record+8u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            pc=d->machine->pc;
            if(pc==0xe4ecu)++forced;
            if(pc==0xe4f0u){if(timers[scenario]!=0u||(states[scenario]&0x7fu)!=1u){ok=0;break;}++animated;}
            if(pc==0xe4f7u)++rendered;
            for(i=0u;i<7u;++i)if(pc==table_pc[i]){
                if(d->machine->x>=4u){ok=0;break;}++reads[i][d->machine->x];
            }
            if(pc==0xe5c1u){
                if(record[1]!=0u||d->machine->a!=0xf8u||d->machine->y!=oam){ok=0;break;}
                record[1]=1u;record[3]=d->machine->a;
                memcpy(record+4104u,d->machine->ram,2048u);
            }
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
            if(pc==0xe4e2u&&d->machine->pc==0xe4ecu)++timer_skip;
            if(pc==0xe4eau){if(d->machine->pc==0xe4f0u)++state_animate;else ++state_force;}
            if(pc==0xe4eeu&&d->machine->pc!=0xe4f7u){ok=0;break;}
            if(pc==0xe535u){if(d->machine->pc==0xe540u)++visible;else ++hidden;}
            if(pc==0xe5c7u){if(d->machine->pc!=0xe540u){ok=0;break;}++returns;}
        }
        if(steps>maxsteps)maxsteps=steps;
        if(d->machine->pc!=0x8001u||d->machine->x!=slot||d->machine->y!=oam)ok=0;
        record[4]=d->machine->x;record[5]=d->machine->y;record[6]=d->machine->a;
        memcpy(record+2056u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u forced=%u animated=%u rendered=%u\n",n,maxsteps,forced,animated,rendered);
    printf("timer-skip=%u state-animate=%u state-force=%u visible=%u hidden=%u actual-child-returns=%u\n",timer_skip,state_animate,state_force,visible,hidden,returns);
    for(i=0u;i<7u;++i){printf("table=%u reads=",i);for(j=0u;j<4u;++j){printf("%u%s",reads[i][j],j==3u?"\n":",");if(!reads[i][j])ok=0;}}
    if(n!=CASES||rendered!=CASES||!forced||!animated||!visible||!hidden||returns!=hidden)ok=0;
    return ok?0:66;
}
