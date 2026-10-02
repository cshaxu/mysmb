/* Real enemy terrain, landing and side return consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 12288u
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
    static const unsigned short seams[13]={0xdfcau,0xdff5u,0xdffdu,0xe016u,0xe01bu,0xe051u,0xe0a4u,0xe0c2u,0xe0cdu,0xe0d0u,0xe115u,0xe11au,0xe152u};
    static const unsigned char ids[4]={0u,3u,6u,18u};
    static const unsigned char states[8]={0u,1u,2u,3u,5u,0x40u,0x80u,0xc0u};
    static const unsigned char tiles[4]={0u,0x61u,0x23u,0x26u};
    unsigned char header[12]={'M','S','E','T',1u,0u,0u,0u,0u,48u,0u,0u};
    unsigned char record[4100],slot,kind,previous_opcode,offset;
    unsigned int n,k,i,steps,maxsteps=0u,observed[13]={0u};
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
        kind=0u;k=n%2048u;slot=(unsigned char)(n/2048u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;
        d->machine->ram[0x000fu+slot]=1u;
        d->machine->ram[0x0016u+slot]=ids[k/512u];
        d->machine->ram[0x001eu+slot]=states[k/16u%8u];
        d->machine->ram[0x00cfu+slot]=(unsigned char)(0x80u+k%16u);
        d->machine->ram[0x00a0u+slot]=2u;d->machine->ram[0x0434u+slot]=0x77u;
        d->machine->ram[0x0046u+slot]=(unsigned char)(1u+k/128u%2u);
        d->machine->ram[0x0058u+slot]=0x20u;
        d->machine->ram[0x006eu+slot]=1u;d->machine->ram[0x0087u+slot]=0x70u;
        d->machine->ram[0x006du]=1u;d->machine->ram[0x0086u]=(k&1u)?0x80u:0x40u;
        d->machine->ram[0x074eu]=(unsigned char)(k/16u%2u);
        d->machine->ram[9u]=(unsigned char)(k%8u);
        d->machine->ram[0x03aeu]=(unsigned char)(k*17u);
        for(i=0x500u;i<0x6a0u;++i)d->machine->ram[i]=tiles[k/128u%4u];
        for(i=0x109u;i<=0x139u;++i)d->machine->ram[i]=0x55u;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=0xdfc1u;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        previous_opcode=0u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            for(i=0u;i<13u;++i)if(previous_opcode==0x60u&&d->machine->pc==seams[i]){
                ++observed[i];
                if(d->machine->x!=slot){ok=0;break;}
                if(i==1u&&d->machine->a!=d->machine->ram[3u])ok=0;
                if((i==5u||i==7u)&&d->machine->ram[0u]!=(unsigned char)(0x70u-d->machine->ram[0x86u]))ok=0;
                if((i==6u||i==9u)&&(d->machine->ram[0xa0u+slot]!=0u||d->machine->ram[0x434u+slot]!=0u||(d->machine->ram[0xcfu+slot]&15u)!=8u))ok=0;
                if(i==12u&&(d->machine->a!=0u||d->machine->ram[0xa0u+slot]!=0u||d->machine->ram[0x434u+slot]!=0u))ok=0;
            }
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x\n",n,d->machine->pc,d->machine->x);break;}
            previous_opcode=d->machine->pc>=0x8000u?prg[d->machine->pc-0x8000u]:0u;
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u)ok=0;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->x;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u\n",n,maxsteps);
    for(i=0u;i<13u;++i){printf("return=%04x observed=%u\n",seams[i],observed[i]);if(observed[i]==0u)ok=0;}
    if(n!=CASES)ok=0;
    return ok?0:66;
}
