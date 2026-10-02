/* Original power-up rows, indexed tables and offscreen tail input. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
static int ready(core_machine *m)
{
    core_run_result r;unsigned int i;for(i=0u;i<524288u;++i){if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;static unsigned char rec[14368],prg[32768];
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};core_run_result r;
    unsigned char h[12]={'M','S','P','U',1u,0u,0u,0u,0u,0x20u,0u,0u};
    unsigned int n,i,k,t,profile,pc,steps,pending=0u,pos,maxsteps=0u,row_returns=0u,tail_entries=0u,erases=0u;
    unsigned int tile_reads[16]={0u},attr_reads[4]={0u},flip=0u,mushroom=0u,oneup=0u;
    unsigned int loop_taken=0u,loop_exit=0u,flower=0u,star=0u;
    int ok=1;FILE *f;time_t start=time(NULL);
    if(argc!=3)return 64;f=fopen(argv[1],"rb");if(!f||fseek(f,16L,SEEK_SET)!=0||fread(prg,1u,sizeof(prg),f)!=sizeof(prg))return 65;fclose(f);
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));f=fopen(argv[2],"wb");if(!f)return 65;if(fwrite(h,1u,12u,f)!=12u)ok=0;
    for(n=0u;n<8192u&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}memcpy(d->machine,&baseline,sizeof(baseline));
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*19u+n*7u);
        k=n%256u;profile=(n/256u)%8u;t=n/2048u;
        d->machine->ram[8u]=5u;d->machine->ram[9u]=(unsigned char)k;d->machine->ram[0x0039u]=(unsigned char)t;
        d->machine->ram[0x06eau]=(unsigned char)(k>=128u?0xe8u:0x20u);
        d->machine->ram[0x03aeu]=(unsigned char)(k*17u);d->machine->ram[0x03b9u]=(unsigned char)(k*13u);
        d->machine->ram[0x03cau]=(unsigned char)((profile&1u)?0x20u:0u);
        d->machine->ram[0x03d1u]=(unsigned char)(k*29u);
        d->machine->ram[0x001bu]=(unsigned char)((profile&4u)?12u:0x2eu);
        d->machine->ram[0x00bbu]=(unsigned char)((profile&2u)?2u:1u);
        d->machine->pc=0xe6d2u;d->machine->x=5u;d->machine->s=0xfdu;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        memset(rec,0,sizeof(rec));rec[0]=(unsigned char)t;pending=0u;memcpy(rec+16u,d->machine->ram,2048u);
        for(steps=0u;steps<524288u&&d->machine->pc!=0x8001u;++steps){
            pc=d->machine->pc;
            if(pc==0xebb2u){if(pending||rec[3]>=2u){ok=0;break;}pos=4112u+rec[3]*4104u;pending=rec[3]+1u;
                rec[pos]=d->machine->a;rec[pos+1u]=d->machine->x;rec[pos+2u]=d->machine->y;
                memcpy(rec+pos+8u,d->machine->ram,2048u);++rec[3];}
            if(pc==0xeb64u){if(pending||rec[3]!=2u){ok=0;break;}memcpy(rec+12320u,d->machine->ram,2048u);++tail_entries;}
            if(pc==0xc998u)++erases;
            if(pc==0xe6e4u){if(d->machine->x>=4u){ok=0;break;}++attr_reads[d->machine->x];}
            if(pc==0xe6f7u||pc==0xe6fcu){i=d->machine->x+(pc==0xe6fcu?1u:0u);if(i>=16u){ok=0;break;}++tile_reads[i];}
            if(pc==0xe72bu)++flip;
            if(pc==0xe70au&&t==0u)++mushroom;if(pc==0xe70eu&&t==3u)++oneup;
            if(pc==0xe723u){if(t==1u)++flower;else ++star;}
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid){ok=0;break;}
            if(pc==0xe704u){if(d->machine->pc==0xe6f7u)++loop_taken;else ++loop_exit;}
            if(pending&&prg[pc-0x8000u]==0x60u&&d->machine->pc==0xe702u){
                pos=4112u+(pending-1u)*4104u;memcpy(rec+pos+2056u,d->machine->ram,2048u);++row_returns;pending=0u;}
        }
        if(steps>maxsteps)maxsteps=steps;if(d->machine->pc!=0x8001u||pending||rec[3]!=2u)ok=0;
        memcpy(rec+2064u,d->machine->ram,2048u);if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f)!=0)ok=0;(void)core_driver_destroy(d);
    printf("roots=%u maxsteps=%u row-returns=%u tail-entries=%u erases=%u flip=%u mushroom=%u oneup=%u\n",n,maxsteps,row_returns,tail_entries,erases,flip,mushroom,oneup);
    printf("loop-taken=%u exit=%u flower=%u star=%u\n",loop_taken,loop_exit,flower,star);
    for(i=0u;i<16u;++i){printf("tile-index=%u reads=%u\n",i,tile_reads[i]);if(!tile_reads[i])ok=0;}
    for(i=0u;i<4u;++i){printf("attribute-index=%u reads=%u\n",i,attr_reads[i]);if(!attr_reads[i])ok=0;}
    return ok&&n==8192u&&row_returns==16384u&&tail_entries==8192u&&erases==1024u&&mushroom==2048u&&oneup==2048u&&loop_taken==8192u&&loop_exit==8192u&&flower==2048u&&star==2048u?0:66;
}
