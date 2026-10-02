/* Controlled original vine/OAM entries; no product emulator dependency. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 16384u
#define LIMIT 524288u
static int ready(core_machine *m)
{
    core_run_result r; unsigned int n;
    for (n=0u;n<LIMIT;++n) {
        if (m->pc==0x8181u) return 1;
        if (core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid) return 0;
    }
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char allocations[4]={0u,0x20u,0xc0u,0xe8u};
    static const unsigned char stack_offsets[16]={0u,1u,3u,4u,0x20u,0x7fu,0x80u,0xc0u,0xe8u,0xecu,0xf0u,0xf4u,0xf8u,0xfcu,0xfeu,0xffu};
    static const unsigned short watched[8]={0xe435u,0xe479u,0xe490u,0xe492u,0xe4a2u,0xe4aeu,0xe4b0u,0xe449u};
    unsigned char header[12]={'M','S','V','G',1u,0u,0u,0u,0u,0x40u,0u,0u};
    unsigned char record[4100],kind,index,offset,value;
    unsigned int n,k,slot,i,step,maxstep=0u,seen[8]={0u},reads[2]={0u};
    unsigned int cap_skip=0u,cap_set=0u,clip_keep=0u,clip_hide=0u,returns=0u,pc;
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
        kind=n<12288u?0u:1u;k=n%256u;value=(unsigned char)k;
        if(kind==0u){
            index=(unsigned char)(n/6144u);slot=(n/256u)%6u;offset=allocations[(n/1536u)%4u];
            d->machine->ram[0x039au+index]=(unsigned char)slot;
            d->machine->ram[0x06e5u+slot]=offset;
            d->machine->ram[0x03b9u]=(unsigned char)(k*13u);
            d->machine->ram[0x03aeu]=(unsigned char)(k*17u);
            d->machine->ram[0x039du]=(unsigned char)(k*38u);
            d->machine->pc=0xe435u;d->machine->y=index;
        }else{
            index=0u;offset=stack_offsets[(n-12288u)/256u];
            d->machine->ram[2u]=(unsigned char)(offset^0x55u);
            d->machine->pc=0xe4aeu;d->machine->y=offset;
        }
        d->machine->a=value;d->machine->x=0xadu;d->machine->s=0xfdu;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        record[0]=kind;record[1]=index;record[2]=offset;record[3]=value;
        memcpy(record+4u,d->machine->ram,2048u);
        for(step=0u;step<LIMIT&&d->machine->pc!=0x8001u;++step){
            pc=d->machine->pc;for(i=0u;i<8u;++i)if(pc==watched[i])++seen[i];
            if(pc==0xe43bu){if(d->machine->y>1u){ok=0;break;}++reads[d->machine->y];}
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
            if(pc==0xe489u){if(d->machine->pc==0xe490u)++cap_skip;else ++cap_set;}
            if(pc==0xe49bu){if(d->machine->pc==0xe4a2u)++clip_keep;else ++clip_hide;}
            if(pc==0xe4bfu&&kind==0u){if(d->machine->pc!=0xe449u){ok=0;break;}++returns;}
        }
        if(step>maxstep)maxstep=step;
        if(d->machine->pc!=0x8001u)ok=0;
        if(kind==0u){if(d->machine->y!=index||d->machine->x!=6u)ok=0;}
        else if(d->machine->y!=d->machine->ram[2u]||d->machine->x!=0u||d->machine->a!=(unsigned char)(value+48u))ok=0;
        memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u actual-child-returns=%u\n",n,maxstep,returns);
    for(i=0u;i<8u;++i){printf("pc=%04x observed=%u\n",watched[i],seen[i]);if(!seen[i])ok=0;}
    printf("table-reads=%u,%u cap-set=%u cap-skip=%u clip-keep=%u clip-hide=%u\n",reads[0],reads[1],cap_set,cap_skip,clip_keep,clip_hide);
    if(n!=CASES||returns!=12288u||!reads[0]||!reads[1]||!cap_set||!cap_skip||!clip_keep||!clip_hide)ok=0;
    return ok?0:66;
}
