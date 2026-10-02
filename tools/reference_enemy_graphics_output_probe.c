/* Bounded original EnemyGfxHandler family batch and real row contracts. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define ROOTS 8192u
#define RECORD_BYTES 16424u
static int ready(core_machine *m)
{
    core_run_result r;unsigned int i;
    for(i=0u;i<524288u;++i){if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static unsigned char rec[RECORD_BYTES],prg[32768];
    static unsigned int hits[768],taken[768],fell[768],tiles[258],offsets[54],attrs[54],spring[5],timing[2];
    static const unsigned char states[16]={0u,1u,2u,3u,4u,5u,8u,9u,0x20u,0x24u,0x25u,0x40u,0x60u,0x80u,0xa0u,0xffu};
    static const unsigned char intervals[4]={0u,1u,4u,5u};
    unsigned char h[12]={'M','S','E','G',1u,0u,0u,0u,0u,0x20u,0u,0u};
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};core_run_result r;
    unsigned int n,i,k,profile,kind,slot,id,steps,pc,pos,pending=0u,maxsteps=0u,returns=0u,early=0u,addr,index;
    int ok=1;FILE *f;time_t start=time(NULL);
    if(argc!=3)return 64;
    f=fopen(argv[1],"rb");if(!f||fseek(f,16L,SEEK_SET)||fread(prg,1u,sizeof(prg),f)!=sizeof(prg))return 65;fclose(f);
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));f=fopen(argv[2],"wb");if(!f)return 65;
    if(fwrite(h,1u,sizeof(h),f)!=sizeof(h))ok=0;
    for(n=0u;n<ROOTS&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*19u+n*7u);
        k=n%16u;kind=(n/16u)%32u;profile=n/512u;slot=n%6u;
        id=kind<27u?kind:(kind==27u?50u:(kind==28u?51u:(kind==29u?53u:45u)));
        d->machine->ram[8u]=(unsigned char)slot;d->machine->ram[0x16u+slot]=(unsigned char)id;
        d->machine->ram[0x1eu+slot]=states[k];d->machine->ram[0x46u+slot]=(unsigned char)(1u+(profile&1u));
        d->machine->ram[0xcfu+slot]=(unsigned char)(n*13u);d->machine->ram[0x3aeu]=(unsigned char)(n*17u);
        d->machine->ram[0x6e5u+slot]=(unsigned char)(profile>=8u?0xe8u:0x20u);
        d->machine->ram[0x3c5u+slot]=(unsigned char)((profile&1u)?0x20u:0u);
        d->machine->ram[0x36au]=(unsigned char)(kind>=30u?kind-29u:0u);
        d->machine->ram[0x363u]=(unsigned char)((profile&1u)|((profile&2u)?0x80u:0u));
        d->machine->ram[0x70eu]=(unsigned char)(profile%5u);
        d->machine->ram[0x58u+slot]=(unsigned char)((profile&1u)?0x80u:0u);
        d->machine->ram[0xa0u+slot]=(unsigned char)((profile&1u)?0x80u:0u);
        d->machine->ram[0x78au+slot]=(unsigned char)((profile&2u)?1u:0u);
        d->machine->ram[0x796u+slot]=intervals[profile%4u];
        d->machine->ram[9u]=(unsigned char)((profile&4u)?8u:0u);
        d->machine->ram[0x747u]=(unsigned char)((profile&8u)?1u:0u);
        d->machine->ram[0x75fu]=(unsigned char)((profile&1u)?7u:6u);
        d->machine->ram[0x78fu]=(unsigned char)((profile&2u)?0x10u:0x0fu);
        d->machine->ram[0x3d1u]=(unsigned char)(n*29u);
        d->machine->ram[0xb6u+slot]=(unsigned char)((profile&4u)?2u:1u);
        d->machine->pc=0xe87du;d->machine->x=(unsigned char)slot;d->machine->s=0xfdu;
        d->machine->ram[0x1feu]=0u;d->machine->ram[0x1ffu]=0x80u;
        memset(rec,0,sizeof(rec));rec[0]=(unsigned char)slot;rec[1]=(unsigned char)kind;
        memcpy(rec+16u,d->machine->ram,2048u);pending=0u;
        for(steps=0u;steps<524288u&&d->machine->pc!=0x8001u;++steps){
            pc=d->machine->pc;if(pc>=0xe87du&&pc<0xeb7du)++hits[pc-0xe87du];
            if(pc==0xebb2u){if(pending||rec[3]>=3u){ok=0;break;}
                pos=4112u+rec[3]*4104u;pending=rec[3]+1u;
                rec[pos]=d->machine->a;rec[pos+1u]=d->machine->x;rec[pos+2u]=d->machine->y;
                memcpy(rec+pos+8u,d->machine->ram,2048u);++rec[3];}
            if(pc>=0x8000u&&(prg[pc-0x8000u]==0xbdu||prg[pc-0x8000u]==0xb9u||prg[pc-0x8000u]==0x39u)){
                addr=prg[pc-0x8000u+1u]|(prg[pc-0x8000u+2u]<<8u);
                index=prg[pc-0x8000u]==0xbdu?d->machine->x:d->machine->y;
                if(addr==0xe73eu||addr==0xe73fu)++tiles[index+(addr==0xe73fu?1u:0u)];
                if(addr==0xe840u&&index<54u)++offsets[index];
                if(addr==0xe85bu&&index<54u)++attrs[index];
                if(addr==0xe878u&&index<5u)++spring[index];
                if(addr==0xe876u&&index<2u)++timing[index];
            }
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid){ok=0;break;}
            if(pc>=0xe87du&&pc<0xeb7du&&(prg[pc-0x8000u]&0x1fu)==0x10u){
                if(d->machine->pc==(unsigned short)(pc+2u))++fell[pc-0xe87du];else ++taken[pc-0xe87du];}
            if(pending&&prg[pc-0x8000u]==0x60u&&
               (d->machine->pc==0xea50u||d->machine->pc==0xea53u||d->machine->pc==0xea56u)){
                pos=4112u+(pending-1u)*4104u;
                rec[pos+3u]=d->machine->x;rec[pos+4u]=d->machine->y;
                memcpy(rec+pos+2056u,d->machine->ram,2048u);++returns;pending=0u;}
        }
        if(steps>maxsteps)maxsteps=steps;
        if(d->machine->pc!=0x8001u||pending||(rec[3]!=0u&&rec[3]!=3u))ok=0;
        if(rec[3]==0u)++early;
        memcpy(rec+2064u,d->machine->ram,2048u);if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f))ok=0;(void)core_driver_destroy(d);
    printf("roots=%u maxsteps=%u row-returns=%u early=%u bytes=%u\n",n,maxsteps,returns,early,12u+n*RECORD_BYTES);
    for(i=0u;i<768u;++i)if(hits[i])printf("pc=%04x visits=%u taken=%u fall=%u\n",0xe87du+i,hits[i],taken[i],fell[i]);
    for(i=0u;i<258u;++i)if(tiles[i])printf("tile=%u reads=%u\n",i,tiles[i]);
    for(i=0u;i<54u;++i)if(offsets[i]||attrs[i])printf("type=%u offsets=%u attributes=%u\n",i,offsets[i],attrs[i]);
    for(i=0u;i<5u;++i)printf("spring=%u reads=%u\n",i,spring[i]);
    for(i=0u;i<2u;++i)printf("timing=%u reads=%u\n",i,timing[i]);
    return ok&&n==ROOTS&&returns==(ROOTS-early)*3u?0:66;
}
