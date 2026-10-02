/* Real platform movement and rider return consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 1728u
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
    static const unsigned short roots[6]={0xd5d3u,0xd607u,0xd631u,0xd63du,0xd64fu,0xd655u};
    static const unsigned short seams[8]={0xd5f8u,0xd5feu,0xd606u,0xd630u,0xd639u,0xd63cu,0xd640u,0xd679u};
    static const unsigned char ids[6]={0x25u,0x28u,0x29u,0x2au,0x26u,0x2bu};
    static const unsigned char ys[6]={0x1fu,0x20u,0x7fu,0x80u,0xffu,0u};
    static const unsigned char amounts[4]={0u,1u,0x80u,0xffu};
    static const unsigned char speeds[4]={0u,1u,0x0eu,0xffu};
    unsigned char header[12]={'M','S','P','M',1u,0u,0u,0u,0xc0u,6u,0u,0u};
    unsigned char record[4100],slot,kind,delta,speed,fraction,previous_opcode;
    unsigned int n,k,i,steps,maxsteps=0u,observed[8]={0u},gates[2]={0u},counter[3]={0u};
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
        kind=(unsigned char)(n%6u);k=n%288u/6u;slot=(unsigned char)(n/288u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;d->machine->ram[0x000fu+slot]=1u;
        d->machine->ram[0x0016u+slot]=ids[kind];
        d->machine->ram[0x00a0u+slot]=(unsigned char)(k%4u==0u?0u:k%4u==1u?1u:k%4u==2u?2u:0xffu);
        d->machine->ram[0x0058u+slot]=speeds[k/12u%4u];
        d->machine->ram[0x006eu+slot]=1u;d->machine->ram[0x0087u+slot]=(unsigned char)(k*17u);
        d->machine->ram[0x006du]=(unsigned char)(k/12u%2u);
        d->machine->ram[0x0086u]=(unsigned char)(k*13u);
        d->machine->ram[0x0401u+slot]=amounts[k/12u%4u];
        d->machine->ram[0x0417u+slot]=amounts[k/12u%4u];
        d->machine->ram[0x0434u+slot]=amounts[k%4u];
        d->machine->ram[0x00b6u+slot]=(unsigned char)(1u+k/8u%2u);
        d->machine->ram[0x00cfu+slot]=ys[k/8u];
        d->machine->ram[0x03a2u+slot]=(unsigned char)(kind==5u?k%3u:k/4u%2u==0u?0u:0x80u);
        d->machine->ram[0x000eu]=(unsigned char)(k/16u==2u?11u:8u);
        d->machine->ram[0x0747u]=(unsigned char)(k/8u%2u);
        d->machine->ram[9u]=(unsigned char)k;
        d->machine->ram[0x00ceu]=0xa5u;d->machine->ram[0x00b5u]=0x5au;
        d->machine->ram[0x009fu]=3u;d->machine->ram[0x0433u]=0x77u;
        if(kind==0u){
            d->machine->ram[0x0058u+slot]=(unsigned char)(ys[k/8u]+(k%2u==0u?1u:0xffu));
            if(k%8u<2u){
                d->machine->ram[0x00a0u+slot]=0u;d->machine->ram[0x0434u+slot]=0u;
                d->machine->ram[0x0401u+slot]=(unsigned char)(ys[k/8u]+1u);
            }
        }
        for(i=0x109u;i<=0x139u;++i)d->machine->ram[i]=0x55u;
        speed=d->machine->ram[0x0058u+slot];fraction=(unsigned char)(speed<<4u);
        delta=(unsigned char)(speed>>4u);if(delta>=8u)delta|=0xf0u;
        delta=(unsigned char)(delta+((unsigned int)d->machine->ram[0x0401u+slot]+fraction>255u));
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=roots[kind];d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        previous_opcode=0u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            for(i=0u;i<8u;++i)if(previous_opcode==0x60u&&d->machine->pc==seams[i]){
                ++observed[i];if(d->machine->x!=slot)ok=0;
                if(i==6u&&d->machine->a!=delta)ok=0;
            }
            if(d->machine->pc==0xd603u)++gates[(d->machine->ram[0x03a2u+slot]&0x80u)!=0u];
            if(d->machine->pc==0xdc19u){
                if(d->machine->a>2u)ok=0;else ++counter[d->machine->a];
            }
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x\n",n,d->machine->pc,d->machine->x);break;}
            previous_opcode=d->machine->pc>=0x8000u?prg[d->machine->pc-0x8000u]:0u;
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u||d->machine->x!=slot)ok=0;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->x;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u small-counter-one/two=%u/%u\n",n,maxsteps,counter[1],counter[2]);
    for(i=0u;i<8u;++i){printf("return=%04x observed=%u\n",seams[i],observed[i]);if(observed[i]==0u)ok=0;}
    if(n!=CASES||counter[1]==0u||counter[2]==0u)ok=0;
    return ok?0:66;
}
