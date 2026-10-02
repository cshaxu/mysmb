/* Actual original coin/floating-score roots and DumpTwoSpr boundary. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
static int ready(core_machine *m)
{
    core_run_result r;unsigned int i;
    for(i=0u;i<524288u;++i){if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;static unsigned char rec[8216],prg[32768];
    static const unsigned char states[4]={0u,1u,2u,0x80u};
    unsigned char h[12]={'M','S','C','O',1u,0u,0u,0u,0u,0x24u,0u,0u};
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};core_run_result r;
    unsigned int n,i,k,slot,profile,steps,pc,pending,maxsteps=0u,returns[2]={0u},tiles[4]={0u},raised=0u,held=0u,notrs=0u,exits=0u;
    int ok=1;FILE *f;time_t start=time(NULL);
    if(argc!=3)return 64;f=fopen(argv[1],"rb");if(!f||fseek(f,16L,SEEK_SET)!=0||fread(prg,1u,sizeof(prg),f)!=sizeof(prg))return 65;fclose(f);
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));f=fopen(argv[2],"wb");if(!f)return 65;
    if(fwrite(h,1u,12u,f)!=12u)ok=0;
    for(n=0u;n<9216u&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*19u+n*7u);
        k=n%256u;profile=(n/256u)%4u;slot=n/1024u;
        d->machine->ram[8u]=(unsigned char)slot;d->machine->ram[9u]=(unsigned char)k;
        d->machine->ram[0x002au+slot]=states[profile];d->machine->ram[0x06f3u+slot]=(unsigned char)(k>=128u?0xf8u:0x20u+slot*8u);
        d->machine->ram[0x00dbu+slot]=(unsigned char)(k*13u);d->machine->ram[0x03b3u]=(unsigned char)(k*17u);
        d->machine->pc=0xe686u;d->machine->x=(unsigned char)slot;d->machine->s=0xfdu;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        memset(rec,0,sizeof(rec));rec[0]=(unsigned char)slot;rec[1]=(unsigned char)profile;pending=0u;memcpy(rec+16u,d->machine->ram,2048u);
        for(steps=0u;steps<524288u&&d->machine->pc!=0x8001u;++steps){
            pc=d->machine->pc;
            if(pc==0xe65cu)++notrs;if(pc==0xe6bdu)++exits;
            if(pc==0xe5c1u){if(pending||rec[3]){ok=0;break;}pending=1u;rec[3]=1u;
                rec[4112u]=d->machine->a;rec[4113u]=d->machine->x;rec[4114u]=d->machine->y;memcpy(rec+4120u,d->machine->ram,2048u);}
            if(pc==0xe6a9u){if(d->machine->x>=4u){ok=0;break;}++tiles[d->machine->x];}
            if(pc==0xe655u){if(k&1u)++held;else ++raised;}
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid){ok=0;break;}
            if(pc==0xe5c7u){if(!pending||d->machine->pc!=(profile>=2u?0xe661u:0xe6b0u)){ok=0;break;}
                ++returns[profile>=2u?1u:0u];memcpy(rec+6168u,d->machine->ram,2048u);pending=0u;}
        }
        if(steps>maxsteps)maxsteps=steps;if(d->machine->pc!=0x8001u||pending||rec[3]!=1u||d->machine->x!=slot)ok=0;
        memcpy(rec+2064u,d->machine->ram,2048u);if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f)!=0)ok=0;(void)core_driver_destroy(d);
    printf("roots=%u maxsteps=%u coin-return-e6b0=%u score-return-e661=%u raised=%u held=%u\n",n,maxsteps,returns[0],returns[1],raised,held);
    printf("NotRsNum=%u ExJCGfx=%u\n",notrs,exits);
    if(returns[0]!=4608u||returns[1]!=4608u||raised!=2304u||held!=2304u||notrs!=4608u||exits!=9216u)ok=0;
    for(i=0u;i<4u;++i){printf("tile-index=%u reads=%u\n",i,tiles[i]);if(!tiles[i])ok=0;}
    return ok&&n==9216u?0:66;
}
