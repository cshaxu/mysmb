/* Bounded owner-ROM helper contracts; raw snapshots are local-only. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define RECORD_BYTES 28736u
static int ready(core_machine *m)
{
    core_run_result r; unsigned int i;
    for(i=0u;i<524288u;++i){
        if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    }
    return 0;
}
static unsigned int event_kind(unsigned int mode,unsigned int pc)
{
    if(mode==0u){if(pc==0xebc1u)return 1u;if(pc==0xebb7u)return 2u;if(pc==0xc998u)return 3u;}
    if(mode==1u&&pc==0xec4au)return 4u;
    if(mode==2u&&pc==0xe5c1u)return 5u;
    if(mode==3u&&pc==0xebb2u)return 6u;
    if(mode==4u&&pc==0xf282u)return 7u;
    if(mode==5u&&pc==0xe5b5u)return 8u;
    if(mode==6u){if(pc==0xebb2u)return 6u;if(pc==0xe5bbu)return 9u;if(pc==0xec46u)return 10u;}
    if(mode==7u||mode==9u){if(pc==0xe5bbu)return 9u;if(pc==0xe5c1u)return 5u;if(pc==0xec46u)return 10u;}
    if(mode==8u&&pc==0xec4au)return 4u;
    if(mode==10u&&pc==0xecedu)return 11u;
    if(mode==12u&&pc==0xed17u)return 12u;
    if(mode==13u&&pc==0xe5bbu)return 9u;
    if(mode==14u){if(pc==0xe5b5u)return 8u;if(pc==0xe5beu)return 13u;}
    if((mode==16u||mode==17u)&&pc==0xebb2u)return 6u;
    if(mode==19u&&pc==0xe5c1u)return 5u;
    return 0u;
}
static void player_fixture(core_machine *m,unsigned int n,unsigned int mode)
{
    static const unsigned char offsets[4]={0u,4u,0xe8u,0xffu};
    unsigned int kind=n%16u,profile=n/16u,action=kind%7u;
    m->ram[0x754u]=(unsigned char)(kind/7u);
    m->ram[0x1du]=0u;m->ram[0x704u]=0u;m->ram[0x714u]=0u;
    m->ram[0x57u]=0u;m->ram[0xcu]=0u;m->ram[0x700u]=1u;
    m->ram[0x9fu]=1u;m->ram[0x70bu]=0u;m->ram[0xeu]=8u;
    m->ram[0x711u]=0u;m->ram[0x79eu]=0u;m->ram[0x3d0u]=0u;
    m->ram[0x70du]=(unsigned char)(profile%3u);
    m->ram[0x781u]=1u;m->ram[0x70cu]=4u;m->ram[0x782u]=1u;
    m->ram[0xau]=0x80u;m->ram[9u]=(unsigned char)(profile%4u);
    m->ram[0x33u]=(unsigned char)(1u+(profile&1u));m->ram[0x45u]=m->ram[0x33u];
    m->ram[0x6e4u]=offsets[(profile>>1u)%4u];
    m->ram[0x3adu]=(unsigned char)(n*13u);m->ram[0x3b8u]=(unsigned char)(n*17u);
    m->ram[0x3c4u]=2u;
    if(action==0u)m->ram[0x1du]=1u;
    if(action==1u){m->ram[0x1du]=1u;m->ram[0x704u]=1u;}
    if(action==3u){m->ram[0x57u]=1u;m->ram[0x700u]=9u;m->ram[0x45u]=(unsigned char)(3u-m->ram[0x33u]);}
    if(action==4u)m->ram[0x57u]=1u;
    if(action==5u){m->ram[0x1du]=3u;m->ram[0x70du]=(unsigned char)(profile%2u);}
    if(action==6u)m->ram[0x714u]=1u;
    if(kind==14u){m->ram[0xeu]=0xbu;m->ram[0x754u]=(unsigned char)(profile&1u);}
    if(kind==15u){m->ram[0x70bu]=1u;m->ram[0x754u]=(unsigned char)((profile/10u)%2u);m->ram[0x70du]=(unsigned char)(profile%10u);}
    if(mode==18u){
        m->ram[0x754u]=(unsigned char)((n>>1u)&1u);m->ram[0x1du]=0u;m->ram[0x704u]=0u;m->ram[0x714u]=0u;
        m->ram[0x57u]=(unsigned char)(n&1u);m->ram[0xcu]=0u;m->ram[0x70bu]=0u;m->ram[0xeu]=8u;
        m->ram[0x70du]=0u;m->ram[0x711u]=3u;m->ram[0x781u]=2u;m->ram[0x6e4u]=(unsigned char)n;
    }
    if(mode==19u){
        unsigned int profile=n>>12u;
        m->ram[0x6e4u]=(unsigned char)n;
        m->ram[0x3d0u]=(unsigned char)(((n>>8u)<<4u)|(n&15u));
        if(profile==1u||profile==2u){m->ram[0x79eu]=1u;m->ram[9u]=(unsigned char)(profile==1u);}
        if(profile==3u){m->ram[0x704u]=1u;m->ram[0x1du]=1u;m->ram[9u]=4u;}
        if(profile==4u){m->ram[0x704u]=1u;m->ram[0x1du]=0u;}
        if(profile==5u){m->ram[0x1du]=0u;m->ram[0x714u]=0u;m->ram[0x57u]=1u;m->ram[0x700u]=9u;m->ram[0x45u]=m->ram[0x33u];}
        if(profile==6u){m->ram[0x70bu]=1u;m->ram[0x70du]=9u;m->ram[9u]=0u;}
        if(profile==7u)m->ram[0xeu]=0xbu;
        if(profile>=8u&&profile<=10u){m->ram[0x711u]=3u;m->ram[0x781u]=(unsigned char)(profile==8u?3u:2u);m->ram[0x57u]=(unsigned char)(profile==10u);m->ram[0xcu]=0u;}
        if(profile==11u){m->ram[0x1du]=1u;m->ram[0x704u]=0u;m->ram[0x714u]=1u;}
        if(profile==12u){m->ram[0x1du]=3u;m->ram[0x9fu]=0u;}
        if(profile==13u)m->ram[0x1du]=2u;
        if(profile==14u){m->ram[0x1du]=1u;m->ram[0x704u]=1u;m->ram[0x782u]=0u;m->ram[0x70du]=0u;m->ram[0xau]=0u;}
        if(profile==15u){m->ram[0x1du]=1u;m->ram[0x704u]=1u;m->ram[0x782u]=0u;m->ram[0x70du]=0u;m->ram[0xau]=0x80u;m->ram[0x781u]=0u;}
    }
    if(mode==20u){
        unsigned int profile=n>>8u;
        m->ram[0x70du]=(unsigned char)n;
        m->ram[0x781u]=(unsigned char)(profile&1u);
        if(profile>=16u){m->ram[0x70bu]=1u;m->ram[0x754u]=(unsigned char)(profile&1u);m->ram[9u]=(unsigned char)((profile>>1u)&3u);m->ram[0xeu]=8u;}
    }
}
static void enemy_fixture(core_machine *m,unsigned int n)
{
    static const unsigned char states[16]={0u,1u,2u,3u,4u,5u,8u,9u,0x20u,0x24u,0x25u,0x40u,0x60u,0x80u,0xa0u,0xffu};
    static const unsigned char intervals[4]={0u,1u,4u,5u};
    unsigned int k=n%16u,kind=(n/16u)%32u,profile=n/512u,slot=n%6u;
    unsigned int id=kind<27u?kind:(kind==27u?50u:(kind==28u?51u:(kind==29u?53u:45u)));
    m->ram[8u]=(unsigned char)slot;m->ram[0x16u+slot]=(unsigned char)id;
    m->ram[0x1eu+slot]=states[k];m->ram[0x46u+slot]=(unsigned char)(1u+(profile&1u));
    m->ram[0xcfu+slot]=(unsigned char)(n*13u);m->ram[0x3aeu]=(unsigned char)(n*17u);
    m->ram[0x6e5u+slot]=(unsigned char)n;
    m->ram[0x3c5u+slot]=(unsigned char)((profile&1u)?0x20u:0u);
    m->ram[0x36au]=(unsigned char)(kind>=30u?kind-29u:0u);
    m->ram[0x363u]=(unsigned char)((profile&1u)|((profile&2u)?0x80u:0u));
    m->ram[0x70eu]=(unsigned char)(profile%5u);
    m->ram[0x58u+slot]=(unsigned char)((profile&1u)?0x80u:0u);
    m->ram[0xa0u+slot]=(unsigned char)((profile&1u)?0x80u:0u);
    m->ram[0x78au+slot]=(unsigned char)((profile&2u)?1u:0u);
    m->ram[0x796u+slot]=intervals[profile%4u];
    m->ram[9u]=(unsigned char)((profile&4u)?8u:0u);
    m->ram[0x747u]=(unsigned char)((profile&8u)?1u:0u);
    m->ram[0x75fu]=(unsigned char)((profile&1u)?7u:6u);
    m->ram[0x78fu]=(unsigned char)((profile&2u)?0x10u:0x0fu);
    m->ram[0x3d1u]=(unsigned char)(n*29u);
    m->ram[0xb6u+slot]=(unsigned char)((profile&4u)?2u:1u);
}
static void relative_fixture(core_machine *m,unsigned int n,unsigned int mode)
{
    static const unsigned char displacements[6]={0u,22u,7u,13u,1u,9u};
    static const unsigned char counts[6]={6u,3u,2u,9u,6u,2u};
    unsigned int kind=mode-21u,slot=n%counts[kind],source=slot+displacements[kind];
    m->x=(unsigned char)slot;m->ram[8u]=(unsigned char)(kind==5u?((n>>1u)&1u):n%6u);
    if(kind==0u)source=0u;
    m->ram[0x86u+source]=(unsigned char)n;
    m->ram[0xceu+source]=(unsigned char)((n>>8u)*13u+7u);
    m->ram[0x6du+source]=(unsigned char)(n>>3u);
    m->ram[0xb5u+source]=(unsigned char)(n>>4u);
    m->ram[0x71cu]=(unsigned char)(n>>8u);
    if(kind==5u){
        source=m->ram[8u]+11u;
        m->ram[0x86u+source]=(unsigned char)(n*3u+1u);
        m->ram[0xceu+source]=(unsigned char)((n>>8u)*17u+3u);
    }
}
static void offscreen_fixture(core_machine *m,unsigned int n,unsigned int mode)
{
    static const unsigned char displacements[6]={0u,7u,22u,13u,1u,9u};
    static const unsigned char counts[6]={1u,2u,3u,9u,6u,2u};
    static const unsigned char page_delta[5]={0xffu,0u,1u,2u,0x80u};
    static const unsigned char high[4]={0u,1u,2u,0xffu};
    unsigned int kind=mode-27u,slot=n%counts[kind],source=slot+displacements[kind];
    unsigned char left=(unsigned char)(n*13u),page=(unsigned char)((n>>11u)&3u);
    m->x=(unsigned char)slot;m->ram[8u]=(unsigned char)((n/7u)%6u);
    m->ram[0x86u+source]=(unsigned char)n;
    m->ram[0xceu+source]=(unsigned char)(n>>8u);
    m->ram[0x6du+source]=(unsigned char)(page+page_delta[(n/257u)%5u]);
    m->ram[0xb5u+source]=high[(n/251u)%4u];
    m->ram[0x71cu]=left;m->ram[0x71du]=(unsigned char)(left-1u);
    m->ram[0x71au]=page;m->ram[0x71bu]=(unsigned char)(page+(left!=0u));
}
static void horizontal_fixture(core_machine *m,unsigned int n,unsigned int mode)
{
    unsigned int source=n%25u;
    unsigned char left=(unsigned char)(mode==33u?0u:0x83u);
    unsigned char page=(unsigned char)(mode==33u?0u:0xfeu);
    m->x=(unsigned char)source;m->ram[8u]=(unsigned char)((n/7u)%6u);
    m->ram[0x86u+source]=(unsigned char)n;
    m->ram[0x6du+source]=(unsigned char)(n>>8u);
    m->ram[0x71cu]=left;m->ram[0x71du]=(unsigned char)(left-1u);
    m->ram[0x71au]=page;m->ram[0x71bu]=(unsigned char)(page+(left!=0u));
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static unsigned char rec[RECORD_BYTES],prg[32768];
    static unsigned int hits[4096],taken[4096],fell[4096],events[14],continuations[65536],offset_reads[16],graphic_reads[208],kick_reads[2],size_reads[20],intermediate_reads[6],proper_reads[3],xmask_reads[16],xdefault_reads[3];
    static unsigned long transfer_keys[8192];
    static unsigned int transfer_counts[8192];
    static const unsigned int entries[35]={0xeb64u,0xebc1u,0xebb7u,0xebaau,0xebb2u,0xe87du,0xebd1u,0xec53u,0xec46u,0xec53u,0xecdeu,0xecedu,0xed09u,0xed17u,0xed66u,0xede1u,0xeee9u,0xefa4u,0xeee9u,0xeee9u,0xeee9u,0xf12au,0xf131u,0xf13bu,0xf148u,0xf152u,0xf159u,0xf180u,0xf187u,0xf191u,0xf19bu,0xf1afu,0xf1b6u,0xf1f6u,0xf1f6u};
    unsigned char h[16]={'M','S','O','H',1u};
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};core_run_result r;
    unsigned int mode,first,count,n,i,slot,pc,steps,k,pos,pending,continuation,maxsteps=0u,returns=0u;
    int ok=1;FILE *f;time_t start=time(NULL);
    if(argc!=6)return 64;
    mode=(unsigned int)strtoul(argv[3],NULL,0);first=(unsigned int)strtoul(argv[4],NULL,0);count=(unsigned int)strtoul(argv[5],NULL,0);
    if(mode>34u||count==0u||count>2048u||first+count>(mode>=21u?65536u:(mode>=19u?(mode==19u?65536u:8192u):(mode>=16u?(mode==16u?1024u:(mode==17u?32u:256u)):(mode==15u?131072u:(mode==14u?69632u:(mode==13u?196608u:(mode==0u?67072u:(mode==5u?8192u:(mode==6u?263168u:((mode==7u||mode==9u)?131072u:65536u)))))))))))return 64;
    h[5]=(unsigned char)mode;for(i=0u;i<4u;++i){h[8u+i]=(unsigned char)(count>>(i*8u));h[12u+i]=(unsigned char)(first>>(i*8u));}
    f=fopen(argv[1],"rb");if(!f||fseek(f,16L,SEEK_SET)||fread(prg,1u,sizeof(prg),f)!=sizeof(prg))return 65;fclose(f);
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));f=fopen(argv[2],"wb");if(!f)return 65;
    if(fwrite(h,1u,sizeof(h),f)!=sizeof(h))ok=0;
    for(n=first;n<first+count&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*19u+n*7u);
        slot=n%6u;d->machine->ram[8u]=(unsigned char)slot;
        d->machine->ram[0x6e5u+slot]=(unsigned char)n;
        d->machine->ram[0x16u+slot]=6u;d->machine->ram[0xb6u+slot]=1u;
        d->machine->ram[0x3d1u]=(unsigned char)(n>>8u);
        d->machine->a=(unsigned char)(n>>8u);d->machine->x=(unsigned char)slot;d->machine->y=(unsigned char)n;
        if(mode==0u&&n>=65536u){
            k=(n-65536u)/512u;
            d->machine->ram[0x6e5u+slot]=(unsigned char)(((n-65536u)&256u)?0xffu:0xe8u);
            d->machine->ram[0x3d1u]=(unsigned char)n;
            d->machine->ram[0x16u+slot]=(unsigned char)(k==0u?12u:6u);
            d->machine->ram[0xb6u+slot]=(unsigned char)(k==2u?3u:2u);
        }
        if(mode==3u||mode==4u)d->machine->x=(unsigned char)(n>>8u);
        if(mode==5u){enemy_fixture(d->machine,n);d->machine->x=(unsigned char)slot;}
        if(mode==6u||mode==7u||mode==9u){
            slot=n%2u;d->machine->x=(unsigned char)slot;d->machine->ram[8u]=(unsigned char)slot;
            d->machine->ram[0x6ecu+slot]=(unsigned char)n;
            d->machine->ram[0x3d4u]=(unsigned char)(n>>8u);
            d->machine->ram[0x74eu]=(unsigned char)((n>>16u)&1u);
            d->machine->ram[0x3e8u+slot]=(unsigned char)((n&0x20000u)?0xc4u:0x51u);
            d->machine->ram[0xeu]=(unsigned char)((n&0x10000u)?5u:6u);
            d->machine->ram[0x9u]=(unsigned char)(n>>4u);
            d->machine->ram[0x3bcu]=(unsigned char)(n>>8u);
            d->machine->ram[0x3bdu]=(unsigned char)(n>>3u);
            d->machine->ram[0x3b1u]=(unsigned char)(n>>8u);
            d->machine->ram[0x3b2u]=(unsigned char)(n>>3u);
            d->machine->ram[0x71cu]=(unsigned char)(n>>11u);
            d->machine->ram[0x3f1u+slot]=(unsigned char)((n>>8u)+(n>>11u)+(n>>16u)*37u);
            if(mode==6u&&n>=262144u){
                d->machine->ram[0x74eu]=(unsigned char)(2u+((n>>9u)&1u));
                d->machine->ram[0x3e8u+slot]=(unsigned char)((n&0x100u)?0xc4u:0x51u);
                d->machine->ram[0x3d4u]=(unsigned char)n;
            }
            if(mode==9u){
                d->machine->ram[0x6ecu+slot]=(unsigned char)((n&0x10000u)?0xffu:0xe8u);
                d->machine->ram[0x3f1u+slot]=(unsigned char)(n+(n>>11u));
                d->machine->ram[0x3d4u]=(unsigned char)(n>>9u);
            }
        }
        if(mode>=10u){
            slot=n%2u;d->machine->x=(unsigned char)slot;d->machine->ram[8u]=(unsigned char)slot;
            d->machine->ram[0x6f1u+slot]=(unsigned char)n;
            d->machine->ram[0x6ecu+slot]=(unsigned char)n;
            d->machine->ram[9u]=(unsigned char)(n>>8u);
            d->machine->ram[0x24u+slot]=(unsigned char)(n>>8u);
            d->machine->ram[0x3afu]=(unsigned char)(n>>8u);
            d->machine->ram[0x3bau]=(unsigned char)((n>>8u)*13u+7u);
            if(mode==13u)d->machine->a=(unsigned char)(n>>16u);
        }
        if(mode==14u){
            slot=n%6u;d->machine->x=(unsigned char)slot;d->machine->ram[8u]=(unsigned char)slot;
            d->machine->ram[0x6e5u+slot]=(unsigned char)n;
            d->machine->ram[0xcfu+slot]=(unsigned char)(n>>8u);
            d->machine->ram[0x3aeu]=(unsigned char)((n>>8u)*13u+7u);
            d->machine->ram[0x3d1u]=(unsigned char)(n>>4u);
            if(n>=65536u){
                k=n-65536u;
                d->machine->ram[0x6e5u+slot]=(unsigned char)((k&8u)?0xffu:0xe8u);
                d->machine->ram[0xcfu+slot]=(unsigned char)(k>>4u);
                d->machine->ram[0x3aeu]=(unsigned char)(k>>4u);
                d->machine->ram[0x3d1u]=(unsigned char)(k&15u);
            }
        }
        if(mode==15u){
            slot=n%3u;d->machine->x=(unsigned char)slot;d->machine->ram[8u]=(unsigned char)slot;
            d->machine->ram[0x6eeu+slot]=(unsigned char)n;
            d->machine->ram[0xb5u]=(unsigned char)(n>>8u);
            d->machine->ram[0x3d3u]=(unsigned char)n;
            d->machine->ram[0x3b0u]=(unsigned char)(n>>8u);
            d->machine->ram[0x3bbu]=(unsigned char)((n>>8u)*13u+7u);
            if(n>=65536u){d->machine->ram[0xb5u]=1u;d->machine->ram[0x3d3u]=(unsigned char)(n&0xf7u);}
        }
        if(mode>=16u&&mode<=20u)player_fixture(d->machine,n,mode);
        if(mode>=21u&&mode<=26u)relative_fixture(d->machine,n,mode);
        if(mode>=27u&&mode<=32u)offscreen_fixture(d->machine,n,mode);
        if(mode==33u||mode==34u)horizontal_fixture(d->machine,n,mode);
        d->machine->pc=(unsigned short)entries[mode];d->machine->s=0xfdu;
        d->machine->ram[0x1feu]=0u;d->machine->ram[0x1ffu]=0x80u;
        memset(rec,0,sizeof(rec));rec[0]=d->machine->a;rec[1]=d->machine->x;rec[2]=d->machine->y;
        memcpy(rec+16u,d->machine->ram,2048u);pending=0u;continuation=0u;
        for(steps=0u;steps<524288u&&d->machine->pc!=0x8001u;++steps){
            pc=d->machine->pc;if(pc>=0xe900u&&pc<0xf900u)++hits[pc-0xe900u];
            if(mode>=16u&&(prg[pc-0x8000u]==0xbdu||prg[pc-0x8000u]==0xb9u||prg[pc-0x8000u]==0x79u||prg[pc-0x8000u]==0xbeu)){
                unsigned int address=(unsigned int)(prg[pc-0x8000u+1u]|(prg[pc-0x8000u+2u]<<8u));
                address=(address+(prg[pc-0x8000u]==0xbdu?d->machine->x:d->machine->y))&65535u;
                if(address>=0xee07u&&address<0xee17u)++offset_reads[address-0xee07u];
                if(address>=0xee17u&&address<0xeee7u)++graphic_reads[address-0xee17u];
                if(address>=0xeee7u&&address<0xeee9u)++kick_reads[address-0xeee7u];
                if(address>=0xf09cu&&address<0xf0b0u)++size_reads[address-0xf09cu];
                if(address>=0xf1e3u&&address<0xf1f3u)++xmask_reads[address-0xf1e3u];
                if(address>=0xf1f3u&&address<0xf1f6u)++xdefault_reads[address-0xf1f3u];
                if(address>=0xf1a5u&&address<0xf1a8u)++proper_reads[address-0xf1a5u];
                if(address>=0xef9eu&&address<0xefa4u)++intermediate_reads[address-0xef9eu];
            }
            k=event_kind(mode,pc);
            /* Record the selected boundary, not nested fallthrough leaves. */
            if(k&&!pending){
                if(rec[3]>=6u){ok=0;break;}
                pos=4112u+rec[3]*4104u;pending=rec[3]+1u;rec[pos]=(unsigned char)k;
                rec[pos+1u]=d->machine->a;rec[pos+2u]=d->machine->x;rec[pos+3u]=d->machine->y;
                continuation=(unsigned int)(d->machine->ram[0x100u+(unsigned char)(d->machine->s+1u)]|
                    (d->machine->ram[0x100u+(unsigned char)(d->machine->s+2u)]<<8u))+1u;
                continuation&=65535u;rec[pos+6u]=(unsigned char)continuation;rec[pos+7u]=(unsigned char)(continuation>>8u);
                memcpy(rec+pos+8u,d->machine->ram,2048u);++rec[3];++events[k];
            }
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid){ok=0;break;}
            if((mode>=16u&&mode<=20u&&pc>=0xeee9u&&pc<0xf12au)||
               (mode>=21u&&mode<=26u&&pc>=0xf12au&&pc<0xf1b7u)||
               (mode>=27u&&pc>=0xf180u&&pc<0xf282u)){
                unsigned long key=(((unsigned long)pc<<16u)|d->machine->pc)+1u;
                unsigned int bucket=(unsigned int)((key^(key>>13u))&8191u),attempt;
                for(attempt=0u;attempt<8192u;++attempt){
                    if(!transfer_keys[bucket]||transfer_keys[bucket]==key)break;
                    bucket=(bucket+1u)&8191u;
                }
                if(attempt==8192u){ok=0;break;}
                transfer_keys[bucket]=key;++transfer_counts[bucket];
            }
            if(pc>=0xe900u&&pc<0xf900u&&(prg[pc-0x8000u]&0x1fu)==0x10u){
                if(d->machine->pc==(unsigned short)(pc+2u))++fell[pc-0xe900u];else ++taken[pc-0xe900u];
            }
            if(pending&&prg[pc-0x8000u]==0x60u&&d->machine->pc==continuation){
                pos=4112u+(pending-1u)*4104u;rec[pos+4u]=d->machine->x;rec[pos+5u]=d->machine->y;
                memcpy(rec+pos+2056u,d->machine->ram,2048u);++returns;++continuations[continuation];pending=0u;
            }
        }
        if(steps>maxsteps)maxsteps=steps;
        if(d->machine->pc!=0x8001u||pending)ok=0;
        rec[4]=d->machine->x;rec[5]=d->machine->y;rec[6]=d->machine->a;
        memcpy(rec+2064u,d->machine->ram,2048u);if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f))ok=0;(void)core_driver_destroy(d);
    printf("mode=%u first=%u roots=%u maxsteps=%u child-returns=%u bytes=%u\n",mode,first,n-first,maxsteps,returns,16u+(n-first)*RECORD_BYTES);
    for(i=0u;i<4096u;++i)if(hits[i])printf("pc=%04x visits=%u taken=%u fall=%u\n",0xe900u+i,hits[i],taken[i],fell[i]);
    for(i=1u;i<14u;++i)if(events[i])printf("event=%u count=%u\n",i,events[i]);
    for(i=0u;i<65536u;++i)if(continuations[i])printf("continuation=%04x count=%u\n",i,continuations[i]);
    for(i=0u;i<16u;++i)if(offset_reads[i])printf("table=offset index=%u reads=%u\n",i,offset_reads[i]);
    for(i=0u;i<208u;++i)if(graphic_reads[i])printf("table=graphics index=%u reads=%u\n",i,graphic_reads[i]);
    for(i=0u;i<2u;++i)if(kick_reads[i])printf("table=kick index=%u reads=%u\n",i,kick_reads[i]);
    for(i=0u;i<20u;++i)if(size_reads[i])printf("table=size index=%u reads=%u\n",i,size_reads[i]);
    for(i=0u;i<6u;++i)if(intermediate_reads[i])printf("table=intermediate index=%u reads=%u\n",i,intermediate_reads[i]);
    for(i=0u;i<3u;++i)if(proper_reads[i])printf("table=proper index=%u reads=%u\n",i,proper_reads[i]);
    for(i=0u;i<16u;++i)if(xmask_reads[i])printf("table=xmask index=%u reads=%u\n",i,xmask_reads[i]);
    for(i=0u;i<3u;++i)if(xdefault_reads[i])printf("table=xdefault index=%u reads=%u\n",i,xdefault_reads[i]);
    for(i=0u;i<8192u;++i)if(transfer_keys[i]){
        unsigned long key=transfer_keys[i]-1u;
        printf("transfer=%04x next=%04x count=%u\n",(unsigned int)(key>>16u),(unsigned int)(key&65535u),transfer_counts[i]);
    }
    return ok&&n==first+count?0:66;
}
