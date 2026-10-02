/* Real shared block-buffer entries and tables return consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 18944u
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
    static unsigned char prg[32768];
    static const unsigned short watched[14]={0xe388u,0xe392u,0xe39cu,0xe3a3u,0xe3a5u,0xe3e8u,0xe3e9u,0xe3ecu,0xe3eeu,0xe3f0u,0xe429u,0xe42bu,0xe40bu,0xe3a8u};
    unsigned char header[12]={'M','S','B','Q',1u,0u,0u,0u,0u,74u,0u,0u};
    unsigned char record[4100],slot,kind,previous_opcode,offset,adder,selector;
    unsigned int n,k,i,object,root,steps,maxsteps=0u,observed[14]={0u};
    unsigned int x_reads[28]={0u},y_reads[28]={0u},address_returns=0u,query_returns=0u;
    core_driver *d=NULL;core_driver_options opt={0u,LIB_FALSE};
    core_run_result result;FILE *file;time_t start=time(NULL);int ok=1;
    if(argc!=3)return 64;
    file=fopen(argv[1],"rb");
    if(!file||fseek(file,16L,SEEK_SET)!=0||fread(prg,1u,sizeof(prg),file)!=sizeof(prg))return 65;
    fclose(file);
    if(core_driver_create(&d,&opt)!=LIB_STATUS_OK||
        !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(!file)return 65;
    if(fwrite(header,1u,12u,file)!=12u)ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        if(n<7168u){kind=0u;k=n;adder=(unsigned char)(k/256u);selector=(unsigned char)(k%256u>=128u);slot=(unsigned char)(k%6u);root=0xe388u;object=slot+1u;}
        else if(n<17536u){k=n-7168u;kind=(unsigned char)(1u+k/3456u);k%=3456u;adder=(unsigned char)(k/128u);selector=kind==3u?1u:0u;slot=0u;object=0u;root=kind==1u?0xe3e8u:(kind==2u?0xe3e9u:0xe3ecu);}
        else if(n<18688u){kind=4u;k=n-17536u;slot=(unsigned char)(k/128u);adder=27u;selector=0u;object=slot+13u;root=0xe392u;}
        else{kind=5u;k=n-18688u;slot=(unsigned char)(k/128u);adder=26u;selector=0u;object=slot+7u;root=0xe39cu;}
        for(i=0x500u;i<0x800u;++i)d->machine->ram[i]=(unsigned char)(i*37u+n*13u);
        d->machine->ram[8u]=slot;
        d->machine->ram[0x86u+object]=(unsigned char)(k*17u);
        d->machine->ram[0x6du+object]=(unsigned char)(k*3u);
        d->machine->ram[0xceu+object]=(unsigned char)(k*13u);
        for(i=0x109u;i<=0x139u;++i)d->machine->ram[i]=0x55u;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=(unsigned short)root;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=selector;d->machine->y=adder;
        previous_opcode=0u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            for(i=0u;i<14u;++i)if(d->machine->pc==watched[i])++observed[i];
            if(d->machine->pc==0xe3f3u||d->machine->pc==0xe410u){
                if(d->machine->y>=28u){ok=0;break;}
                if(d->machine->pc==0xe3f3u)++x_reads[d->machine->y];
                else ++y_reads[d->machine->y];
            }
            if(previous_opcode==0x60u&&d->machine->pc==0xe40bu)++address_returns;
            if(kind==1u||kind==2u){if(d->machine->pc==0xe3ecu){ok=0;break;}}
            if(previous_opcode==0x60u&&d->machine->pc==0xe3a8u){
                ++query_returns;
                if(d->machine->a!=d->machine->ram[3u])ok=0;
            }
            previous_opcode=d->machine->pc>=0x8000u?prg[d->machine->pc-0x8000u]:0u;
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u)ok=0;if(steps>maxsteps)maxsteps=steps;
        if(d->machine->a!=d->machine->ram[3u]||(kind==0u||kind>=4u)&&d->machine->x!=slot)ok=0;
        record[2]=d->machine->a;record[3]=d->machine->x;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u\n",n,maxsteps);
    for(i=0u;i<14u;++i){printf("pc=%04x observed=%u\n",watched[i],observed[i]);if(observed[i]==0u)ok=0;}
    for(i=0u;i<28u;++i){
        printf("index=%u x-reads=%u y-reads=%u\n",i,x_reads[i],y_reads[i]);
        if(x_reads[i]==0u||y_reads[i]==0u)ok=0;
    }
    printf("actual-address-returns=%u actual-query-returns=%u\n",address_returns,query_returns);
    if(address_returns!=CASES||query_returns!=8576u)ok=0;
    if(n!=CASES)ok=0;
    return ok?0:66;
}
