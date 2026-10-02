/* Actual flagpole children, carried ADC input, and direct dump entry roots. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define LIMIT 524288u
static int ready(core_machine *m)
{
    core_run_result r;unsigned int i;
    for(i=0u;i<LIMIT;++i){if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static unsigned char prg[32768],record[12312],dump[4104];
    static const unsigned short entries[6]={0xe5b3u,0xe5b5u,0xe5bbu,0xe5beu,0xe5c1u,0xe5c7u};
    static const unsigned char offsets[8]={0u,1u,0x20u,0x7fu,0xe8u,0xf4u,0xfcu,0xffu};
    unsigned char head[12]={'M','S','F','G',1u,0u,0u,0u,0u,0x12u,0u,0u};
    unsigned char slot,oam,carry,opcode;unsigned int n,k,profile,i,steps,pc,maxsteps=0u,pending,position;
    unsigned int two_returns=0u,row_returns=0u,carry_seen[2]={0u},score_reads[10]={0u},score_skip=0u;
    unsigned int off_keep=0u,off_hide=0u,dump_visits[6]={0u};
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};core_run_result result;
    FILE *file;time_t start=time(NULL);int ok=1;
    if(argc!=4)return 64;
    file=fopen(argv[1],"rb");if(!file||fseek(file,16L,SEEK_SET)!=0||fread(prg,1u,sizeof(prg),file)!=sizeof(prg))return 65;fclose(file);
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));file=fopen(argv[2],"wb");if(!file)return 65;
    if(fwrite(head,1u,12u,file)!=12u)ok=0;
    for(n=0u;n<4608u&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*19u+n*7u);
        k=n%128u;profile=(n/128u)%6u;slot=(unsigned char)(n/768u);
        oam=(unsigned char)(k>=64u?0xe8u:0x20u+slot*24u);
        d->machine->ram[8u]=slot;d->machine->ram[0x06e5u+slot]=oam;
        d->machine->ram[0x03aeu]=(unsigned char)(k*17u+slot*128u);
        d->machine->ram[0x00cfu+slot]=(unsigned char)(k*13u+slot*128u);
        d->machine->ram[0x010du]=(unsigned char)(k*23u);
        d->machine->ram[0x070fu]=(unsigned char)(profile==0u?0u:1u);
        d->machine->ram[0x010fu]=(unsigned char)(profile==0u?0u:profile-1u);
        d->machine->ram[0x03d1u]=(unsigned char)(k*29u+(profile&1u)*128u);
        d->machine->pc=0xe54bu;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        memset(record,0,sizeof(record));record[0]=slot;record[1]=oam;pending=0u;
        memcpy(record+16u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            pc=d->machine->pc;
            if((pc==0xe5c1u&&record[3]==0u)||pc==0xebb2u){
                if(pending||record[3]>=2u){ok=0;break;}
                position=4112u+record[3]*4100u;pending=record[3]+1u;
                record[position]=pc==0xe5c1u?1u:2u;
                record[position+1u]=d->machine->a;record[position+2u]=d->machine->x;record[position+3u]=d->machine->y;
                memcpy(record+position+4u,d->machine->ram,2048u);++record[3];
                if(pending==1u){record[4]=d->machine->p&1u;++carry_seen[record[4]];}
            }
            if(pc==0xe59cu||pc==0xe5a1u){
                i=d->machine->x+(pc==0xe5a1u?1u:0u);if(i>=10u){ok=0;break;}++score_reads[i];
            }
            opcode=prg[pc-0x8000u];
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
            if(pc==0xe590u&&d->machine->pc==0xe5a7u)++score_skip;
            if(pc==0xe5b1u){if(d->machine->pc==0xe5c7u)++off_keep;else ++off_hide;}
            if(opcode==0x60u&&(d->machine->pc==0xe567u||d->machine->pc==0xe5a7u)){
                if(!pending){ok=0;break;}
                position=4112u+(pending-1u)*4100u;
                memcpy(record+position+2052u,d->machine->ram,2048u);
                if(d->machine->pc==0xe567u){if(pending!=1u||(d->machine->p&1u)!=record[4])ok=0;++two_returns;}
                else{if(pending!=2u)ok=0;++row_returns;}
                pending=0u;
            }
        }
        if(steps>maxsteps)maxsteps=steps;
        if(d->machine->pc!=0x8001u||pending||d->machine->x!=slot||d->machine->y!=oam||record[3]!=(profile==0u?1u:2u))ok=0;
        memcpy(record+2064u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;
    printf("flag-cases=%u maxsteps=%u dump-returns=%u row-returns=%u carry-zero=%u carry-one=%u\n",n,maxsteps,two_returns,row_returns,carry_seen[0],carry_seen[1]);
    printf("score-skip=%u offscreen-keep=%u offscreen-hide=%u\n",score_skip,off_keep,off_hide);
    for(i=0u;i<10u;++i){printf("score-index=%u reads=%u\n",i,score_reads[i]);if(!score_reads[i])ok=0;}
    if(n!=4608u||two_returns!=4608u||row_returns!=3840u||!carry_seen[0]||!carry_seen[1]||!off_keep||!off_hide)ok=0;
    file=fopen(argv[3],"wb");if(!file)return 65;
    memcpy(head,"MSDP",4u);head[9]=0x30u;if(fwrite(head,1u,12u,file)!=12u)ok=0;
    for(n=0u;n<12288u&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*19u+n*7u);
        k=n%256u;profile=n/2048u;oam=offsets[(n/256u)%8u];carry=(unsigned char)(k>>7u);
        d->machine->pc=entries[profile];d->machine->a=(unsigned char)k;d->machine->x=0xadu;d->machine->y=oam;d->machine->s=0xfdu;
        d->machine->p=(unsigned char)((d->machine->p&0xfeu)|carry);
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        memset(dump,0,8u);dump[0]=(unsigned char)profile;dump[1]=(unsigned char)k;dump[2]=oam;dump[3]=carry;
        memcpy(dump+8u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            for(i=0u;i<6u;++i)if(d->machine->pc==entries[i])++dump_visits[i];
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u||d->machine->x!=0xadu||d->machine->y!=oam||(d->machine->p&1u)!=carry||d->machine->a!=(profile==0u?0xf8u:k))ok=0;
        memcpy(dump+2056u,d->machine->ram,2048u);
        if(fwrite(dump,1u,sizeof(dump),file)!=sizeof(dump))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("dump-cases=%u\n",n);for(i=0u;i<6u;++i){printf("dump-pc=%04x observed=%u\n",entries[i],dump_visits[i]);if(!dump_visits[i])ok=0;}
    return ok&&n==12288u?0:66;
}
