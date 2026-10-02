/* Real pickup floating-score, palette and routine return consumers. */
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
    static unsigned char prg[32768];
    static const unsigned short seams[3]={0xd808u,0xd833u,0xd84cu};
    static const unsigned char types[8]={0u,1u,2u,3u,4u,127u,128u,255u};
    static const unsigned char statuses[4]={0u,1u,2u,255u};
    static const unsigned char offsets[4]={0u,7u,0xf0u,0xf8u};
    unsigned char header[12]={'M','S','P','U',1u,0u,0u,0u,0u,6u,0u,0u};
    unsigned char record[4100],slot,kind,previous_opcode,offset;
    unsigned int n,k,i,steps,maxsteps=0u,observed[3]={0u};
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
        kind=0u;k=n%256u;slot=(unsigned char)(n/256u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=(unsigned char)((slot+k/128u)%6u);
        d->machine->ram[0x000fu+slot]=1u;d->machine->ram[0x0016u+slot]=0x2eu;
        d->machine->ram[0x001eu+slot]=0x80u;
        d->machine->ram[0x03c5u+slot]=3u;d->machine->ram[0x078au+slot]=0x22u;
        d->machine->ram[0x0796u+slot]=0x33u;
        d->machine->ram[0x00cfu+slot]=(unsigned char)(k*13u);
        d->machine->ram[0x03aeu]=(unsigned char)(k*17u);
        d->machine->ram[0x0039u]=types[k%8u];
        d->machine->ram[0x0756u]=statuses[k/8u%4u];
        d->machine->ram[0x0753u]=(unsigned char)(k/32u%2u);
        d->machine->ram[0x074eu]=(unsigned char)(k/64u%4u);
        d->machine->ram[0x0744u]=(unsigned char)(k/32u%8u);
        offset=offsets[k/64u%4u];d->machine->ram[0x0300u]=offset;
        d->machine->ram[0x000eu]=8u;d->machine->ram[0x001du]=2u;
        d->machine->ram[0x0747u]=0u;d->machine->ram[0x0775u]=0x77u;
        d->machine->ram[0x00fbu]=0x55u;d->machine->ram[0x00feu]=0x66u;
        d->machine->ram[0u]=0xa5u;
        for(i=0x109u;i<=0x139u;++i)d->machine->ram[i]=0x55u;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=0xd800u;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        previous_opcode=0u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            for(i=0u;i<3u;++i)if(previous_opcode==0x60u&&d->machine->pc==seams[i]){
                ++observed[i];
                if(i==0u&&(d->machine->x!=slot||d->machine->a!=d->machine->ram[0x03aeu]||
                           d->machine->ram[0x0110u+slot]!=6u||d->machine->ram[0x012cu+slot]!=0x30u))ok=0;
                if(i==1u&&(d->machine->x!=offset||d->machine->a!=(unsigned char)(offset+7u)||
                           d->machine->ram[0u]!=0xffu||d->machine->ram[0x0756u]!=2u))ok=0;
                if(i==2u&&(d->machine->x!=d->machine->ram[8u]||d->machine->ram[0x001du]!=0u||
                           d->machine->ram[0x0747u]!=0xffu||d->machine->ram[0x0775u]!=0u))ok=0;
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
    for(i=0u;i<3u;++i){printf("return=%04x observed=%u\n",seams[i],observed[i]);if(observed[i]==0u)ok=0;}
    if(n!=CASES||observed[0]!=1536u||observed[1]!=96u||observed[2]!=192u)ok=0;
    return ok?0:66;
}
