/* Original large-platform child inputs, returns and column decisions. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define COUNT 6144u
#define SIZE 28736u
static int ready(core_machine *m)
{
    core_run_result r;unsigned int i;
    for(i=0u;i<524288u;++i){if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;static unsigned char rec[SIZE],prg[32768];
    static const unsigned short entries[6]={0xe4aeu,0xe5bbu,0xe5b5u,0xe5b5u,0xf1f6u,0xe5b3u};
    static const unsigned short returns[6]={0xe5d6u,0xe5ddu,0xe603u,0xe609u,0xe60du,0xe654u};
    static const unsigned short labels[11]={0xe5c8u,0xe5e9u,0xe5ebu,0xe5fdu,0xe61au,0xe624u,0xe62eu,0xe638u,0xe642u,0xe64bu,0xe654u};
    unsigned int visits[11]={0u},children[6]={0u},taken[10]={0u},fall[10]={0u};
    static const unsigned short branches[10]={0xe5e2u,0xe5e7u,0xe5f9u,0xe613u,0xe61du,0xe627u,0xe631u,0xe63bu,0xe644u,0xe64fu};
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};core_run_result result;
    unsigned char head[12]={'M','S','L','P',1u,0u,0u,0u,0u,0x18u,0u,0u};
    unsigned int n,i,k,profile,slot,pc,steps,pending,position,maxsteps=0u,saved_s=0u;
    unsigned int hide=0u,keep=0u;int ok=1;FILE *file;time_t start=time(NULL);
    if(argc!=3)return 64;
    file=fopen(argv[1],"rb");if(!file||fseek(file,16L,SEEK_SET)!=0||fread(prg,1u,sizeof(prg),file)!=sizeof(prg))return 65;fclose(file);
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));file=fopen(argv[2],"wb");if(!file)return 65;
    if(fwrite(head,1u,12u,file)!=12u)ok=0;
    for(n=0u;n<COUNT&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*19u+n*7u);
        k=n%128u;profile=(n/128u)%8u;slot=n/1024u;
        d->machine->ram[8u]=(unsigned char)slot;d->machine->ram[0x06e5u+slot]=(unsigned char)(k>=64u?0xe8u:0x20u+slot*24u);
        d->machine->ram[0x03aeu]=(unsigned char)(k*17u+slot*128u);
        d->machine->ram[0x00cfu+slot]=(unsigned char)(k*13u+slot*128u);
        d->machine->ram[0x074eu]=(unsigned char)((profile&1u)?3u:1u);
        d->machine->ram[0x06ccu]=(unsigned char)((profile&2u)?0x80u:0u);
        d->machine->ram[0x0743u]=(unsigned char)((profile&4u)?0x80u:0u);
        d->machine->ram[0x03d1u]=(unsigned char)(k*29u+(slot&1u)*128u);
        d->machine->ram[0x006eu+slot]=(unsigned char)(profile%3u);
        d->machine->ram[0x0087u+slot]=(unsigned char)(k*17u+slot*128u);
        d->machine->ram[0x071au]=1u;d->machine->ram[0x071bu]=2u;
        d->machine->ram[0x071cu]=0x80u;d->machine->ram[0x071du]=0x7fu;
        d->machine->pc=0xe5c8u;d->machine->x=(unsigned char)slot;d->machine->s=0xfdu;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        memset(rec,0,sizeof(rec));rec[0]=(unsigned char)slot;pending=0u;
        memcpy(rec+16u,d->machine->ram,2048u);
        for(steps=0u;steps<524288u&&d->machine->pc!=0x8001u;++steps){
            pc=d->machine->pc;
            for(i=0u;i<11u;++i)if(pc==labels[i])++visits[i];
            if(!pending&&rec[3]<6u&&pc==entries[rec[3]]){
                position=4112u+rec[3]*4104u;pending=rec[3]+1u;saved_s=d->machine->s;
                rec[position]=(unsigned char)pending;rec[position+1u]=d->machine->a;rec[position+2u]=d->machine->x;rec[position+3u]=d->machine->y;
                memcpy(rec+position+8u,d->machine->ram,2048u);++rec[3];
            }
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
            for(i=0u;i<10u;++i)if(pc==branches[i]){if(d->machine->pc==pc+2u)++fall[i];else ++taken[i];}
            if(pc==0xe64fu){if(d->machine->pc==0xe654u)++keep;else ++hide;}
            if(pending&&prg[pc-0x8000u]==0x60u&&d->machine->s==(unsigned char)(saved_s+2u)){
                if(d->machine->pc!=returns[pending-1u])ok=0;
                position=4112u+(pending-1u)*4104u;rec[position+4u]=d->machine->a;rec[position+5u]=d->machine->x;rec[position+6u]=d->machine->y;
                memcpy(rec+position+2056u,d->machine->ram,2048u);++children[pending-1u];pending=0u;
            }
        }
        if(steps>maxsteps)maxsteps=steps;
        if(d->machine->pc!=0x8001u||pending||rec[3]!=(d->machine->ram[0x03d1u]&0x80u?6u:5u))ok=0;
        memcpy(rec+2064u,d->machine->ram,2048u);if(fwrite(rec,1u,sizeof(rec),file)!=sizeof(rec))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("roots=%u maxsteps=%u vertical-keep=%u hide=%u\n",n,maxsteps,keep,hide);
    for(i=0u;i<11u;++i){printf("node=%04x visits=%u\n",labels[i],visits[i]);if(!visits[i])ok=0;}
    for(i=0u;i<6u;++i){printf("child=%u continuation=%04x returns=%u\n",i+1u,returns[i],children[i]);if(!children[i])ok=0;}
    for(i=0u;i<10u;++i){printf("branch=%04x taken=%u fall=%u\n",branches[i],taken[i],fall[i]);if(!taken[i]||!fall[i])ok=0;}
    return ok&&n==COUNT?0:66;
}
