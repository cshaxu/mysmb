/* Controlled unchanged owner-ROM sound routes; raw data stays in build/. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define RECORD_BYTES 4290u
static core_machine baseline;
static unsigned char prg[32768],record[RECORD_BYTES];
static unsigned char live_ram[2048],live_apu[24];
static unsigned long visits[65536],transfers[65536];
static unsigned long transition_keys[8192],transition_counts[8192];
static unsigned long envelope_reads[256];
static unsigned long square2_table_reads[3][256];
static unsigned long noise_table_reads[3][256];
static unsigned long header_reads[7][256];
static unsigned long music_reads[4][65536];
/* Actual absolute-Y reads, grouped by source operand (not inferred song). */
static unsigned long lookup_reads[7][65536];
static unsigned long status_reads[2][65536];
static unsigned long setup_reads[2][65536];
static unsigned int minimum_stack=0xffu;
static int ready(core_machine *m)
{
    core_run_result r;unsigned int i;
    for(i=0;i<524288u;++i){
        if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    }
    return 0;
}
static int advance_audio(core_machine *m,unsigned int entry,unsigned int stop,unsigned int y)
{
    core_run_result r;unsigned int steps;
    memcpy(live_ram,m->ram,2048u);memcpy(live_apu,m->apu.registers,24u);
    *m=baseline;memcpy(m->ram,live_ram,2048u);memcpy(m->apu.registers,live_apu,24u);
    m->pc=(unsigned short)entry;m->y=(unsigned char)y;m->s=0xfdu;
    m->ram[0x1feu]=0u;m->ram[0x1ffu]=0x80u;
    for(steps=0;steps<524288u&&m->pc!=stop;++steps)
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    return m->pc==stop;
}
static void fixture(core_machine *m,unsigned int n,unsigned int mode)
{
    unsigned int p=n>>8u;
    memset(m->ram,0,2048u);
    m->ram[0x770u]=1u;
    m->ram[0x7c0u]=(unsigned char)n;
    m->ram[0xffu]=0x55u;m->ram[0xfeu]=0xaau;m->ram[0xfdu]=3u;
    m->ram[0xfbu]=0x77u;m->ram[0xfcu]=0x88u;
    if(mode==0u){
        m->ram[0x770u]=0u;m->ram[0xfau]=(unsigned char)p;
        m->ram[0x7c6u]=(unsigned char)p;m->ram[0x7b2u]=(unsigned char)n;
    }else if(mode==1u){
        m->ram[0xf4u]=(unsigned char)(p&3u);
        m->ram[0x7c6u]=1u;m->ram[0x7b2u]=(unsigned char)(p<4u?1u:2u);
        m->ram[0x7bbu]=(unsigned char)n;
    }else if(mode==2u){
        m->ram[0xf4u]=(unsigned char)(p&3u);
        m->ram[0xfau]=(unsigned char)(p<4u?1u:2u);
        m->ram[0x7c6u]=(unsigned char)(p<4u?0u:1u);
        m->ram[0xf1u]=0xffu;m->ram[0xf2u]=0xffu;m->ram[0xf3u]=0xffu;
    }else if(mode==3u){
        m->ram[0xf4u]=(unsigned char)(p&3u);m->ram[0x7c6u]=1u;
        m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==4u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0xf4u]=0u;m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==14u||mode==15u){
        m->ram[0xffu]=(unsigned char)(mode==14u?n:0u);
        m->ram[0xf1u]=(unsigned char)(mode==14u?(1u<<(p%8u)):p);
        m->ram[0x7bbu]=(unsigned char)(mode==14u?p*13u:n);
        m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0xf4u]=0u;m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode>=16u&&mode<=18u){
        static const unsigned char buffers[8]={0u,0x40u,0xc0u,0x41u,0x80u,3u,2u,4u};
        m->ram[0xffu]=0u;m->ram[0xfeu]=(unsigned char)(mode==16u?n:0u);
        m->ram[0xf2u]=(unsigned char)(mode==16u?buffers[p%8u]:(mode==17u?p:((p&1u)?4u:2u)));
        m->ram[0x7bdu]=(unsigned char)(mode==16u?p*13u:(mode==17u?n:p));
        m->ram[0x7beu]=(unsigned char)(mode==16u?p*17u:(mode==17u?n*17u:n));
        m->ram[0xfdu]=0u;m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0xf4u]=0u;m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==61u){
        m->ram[0x752u]=(unsigned char)(n&3u);
        m->ram[0x74eu]=(unsigned char)((n>>2u)&3u);
        m->ram[0x710u]=(unsigned char)((n>>4u)&7u);
        m->ram[0x715u]=(unsigned char)((n>>7u)&3u);
        m->ram[0x757u]=(unsigned char)((n&512u)?0xffu:0u);
        m->ram[0x758u]=(unsigned char)((n&1024u)?0xffu:0u);
        m->ram[0x753u]=(unsigned char)((n>>11u)&1u);
        m->ram[0x756u]=(unsigned char)((n>>12u)%3u);
        m->ram[0x300u]=(unsigned char)(n>>8u);
        m->ram[0x490u]=(unsigned char)(n*17u);
        m->ram[0x71au]=(unsigned char)(n*13u);
        m->ram[7u]=0u;
    }else if(mode==60u){
        unsigned int j;
        for(j=0u;j<2048u;++j)m->ram[j]=(unsigned char)(n+j*17u+p*13u);
        m->ram[0x770u]=(unsigned char)((p&16u)?0xffu:0u);
        m->ram[0x752u]=(unsigned char)((p&8u)?2u:0xffu);
        m->ram[0x743u]=(unsigned char)((p&4u)?0xffu:0u);
        m->ram[0x74eu]=(unsigned char)(p&3u);
        m->ram[0x710u]=(unsigned char)n;
    }else if(mode>=55u&&mode<=59u){
        unsigned int j;
        for(j=0u;j<2048u;++j)m->ram[j]=(unsigned char)(n+j*17u+p*13u);
        m->ram[0x770u]=1u;m->ram[0x772u]=(unsigned char)(n*17u);
        m->ram[0x778u]=(unsigned char)n;m->ram[0x71au]=(unsigned char)p;
        m->ram[0x74eu]=(unsigned char)(p&3u);m->ram[0x743u]=(unsigned char)((p>>2u)&1u);
        m->ram[0x752u]=(unsigned char)((p&2u)?2u:0u);
        m->ram[0x710u]=(unsigned char)((p&4u)?6u:0u);
        m->ram[0x75fu]=(unsigned char)((n>>5u)&7u);
        m->ram[0x760u]=(unsigned char)((n>>1u)&3u);
        m->ram[0x75cu]=(unsigned char)((n>>3u)&3u);
        m->ram[0x75bu]=(unsigned char)((n&1u)?0x11u:0u);
        m->ram[0x751u]=(unsigned char)(n*13u+3u);
        m->ram[0x76au]=(unsigned char)((n>>9u)&1u);
        if(mode==58u)m->ram[0x752u]=(unsigned char)((n&256u)?2u:0u);
    }else if(mode>=52u&&mode<=54u){
        unsigned int j;
        m->ram[0x770u]=1u;m->ram[0x300u]=(unsigned char)p;
        for(j=0u;j<36u;++j)m->ram[0x7d7u+j]=(unsigned char)((n+j)%10u);
        if(mode==53u){
            m->ram[0x770u]=(unsigned char)(p==0u?0u:1u);
            m->ram[0x7e2u]=(unsigned char)p;
            m->ram[0x139u]=(unsigned char)n;
        }
        if(mode==54u){
            for(j=0u;j<6u;++j){
                m->ram[0x7d7u+j]=(unsigned char)p;
                m->ram[0x7ddu+j]=(unsigned char)n;
                m->ram[0x7e3u+j]=(unsigned char)(n^0x55u);
            }
        }
    }else if(mode==51u){
        m->ram[0x7b1u]=(unsigned char)(p==0u?8u:0u);
        m->ram[0xf4u]=(unsigned char)(p==2u?0u:1u);
    }else if(mode==19u||mode==20u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;
        m->ram[0xfdu]=(unsigned char)(mode==19u?n:0u);
        m->ram[0xf3u]=(unsigned char)p;
        m->ram[0x7bfu]=(unsigned char)(mode==19u?p*17u:n);
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0xf4u]=0u;m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==21u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xf3u]=2u;m->ram[0x7bfu]=(unsigned char)(102u+(n&1u));
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;m->ram[0xf4u]=1u;
        m->ram[0x7b4u]=(unsigned char)(3u+(n>>1u));
        m->ram[0x7b6u]=(unsigned char)(3u+(n>>1u));
        m->ram[0xf8u]=1u;
        m->ram[0x7b9u]=(unsigned char)(3u+(n>>1u));
        m->ram[0x7bau]=(unsigned char)(3u+(n>>1u));
        m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode>=22u&&mode<=24u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=(unsigned char)(mode==23u?n:(mode==22u?p:(p>=8u?1u<<(p-8u):0u)));
        m->ram[0xfcu]=(unsigned char)(mode==22u?n:(mode==24u&&p<8u?1u<<p:0u));
        m->ram[0xf4u]=(unsigned char)(mode==24u?0u:1u<<(p%8u));
        m->ram[0xf1u]=(unsigned char)(mode==24u?0u:((p&1u)?0x40u:0u));
        m->ram[0xf2u]=(unsigned char)(mode==24u?0u:((p&2u)?0x80u:0u));
        m->ram[0x7bbu]=0x30u;m->ram[0x7bdu]=0x30u;
        m->ram[0x7b4u]=5u;m->ram[0x7b6u]=5u;m->ram[0x7b9u]=5u;m->ram[0x7bau]=5u;
        m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==25u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0x7b1u]=(unsigned char)n;
        m->ram[0xf4u]=(unsigned char)(1u<<(p%8u));
        m->ram[0x7c5u]=(unsigned char)(p<8u?1u<<p:0u);
        m->ram[0x7c7u]=0x31u;
        m->ram[0xf5u]=0u;m->ram[0xf6u]=2u;m->ram[0x7b4u]=1u;
        m->ram[0xf8u]=1u;m->ram[0x7b6u]=5u;m->ram[0x7b9u]=5u;m->ram[0x7bau]=5u;
        m->ram[0xf1u]=(unsigned char)((p&1u)?0x40u:0u);m->ram[0x7bbu]=0x30u;
        m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==26u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;m->ram[0xf4u]=1u;
        m->ram[0x7b1u]=(unsigned char)(p<<4u);
        m->ram[0xf1u]=(unsigned char)n;m->ram[0xf2u]=(unsigned char)p;
        m->ram[0x7bbu]=0x30u;m->ram[0x7bdu]=0x30u;
        m->ram[0xf8u]=1u;m->ram[0x7b4u]=5u;m->ram[0x7b6u]=5u;
        m->ram[0x7b9u]=5u;m->ram[0x7bau]=5u;
        m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==28u){
        m->ram[0xffu]=(unsigned char)n;m->ram[0xfeu]=(unsigned char)p;
        m->ram[0xfdu]=(unsigned char)(n*17u+p*3u);
        m->ram[0xfbu]=(unsigned char)(p<128u?1u<<(p&7u):0u);
        m->ram[0xfcu]=(unsigned char)((n&7u)==0u?1u<<(p&7u):0u);
        m->ram[0xf1u]=(unsigned char)((p&128u)?0x40u:0u);
        m->ram[0xf2u]=(unsigned char)((n&128u)?0x40u:0u);
        m->ram[0xf3u]=(unsigned char)(n^p);
        m->ram[0x7bbu]=(unsigned char)n;m->ram[0x7bdu]=(unsigned char)p;
        m->ram[0x7beu]=(unsigned char)(n+p);m->ram[0x7bfu]=(unsigned char)(n^p);
        m->ram[0xf4u]=0u;m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==29u){
        m->ram[0x770u]=(unsigned char)((p&16u)?0u:1u);
        m->ram[0x7c6u]=(unsigned char)(p&1u);
        m->ram[0xfau]=(unsigned char)((p>>1u)&3u);
        m->ram[0x7b2u]=(unsigned char)((p>>3u)&3u);
        m->ram[0x7bbu]=(unsigned char)n;
    }else if(mode>=48u&&mode<=50u){
        unsigned int selector=mode==49u?10u:(mode==50u?17u:n/1024u+1u);
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0xf4u]=(unsigned char)(selector<=8u?0u:(selector<=16u?1u<<(selector-9u):1u));
        m->ram[0x7b1u]=(unsigned char)(selector<=8u?1u<<(selector-1u):0u);
        m->ram[0x7c7u]=(unsigned char)(selector>=17u?selector:16u);
        m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode>=36u&&mode<=43u){
        m->ram[0xf0u]=(unsigned char)n;
        m->ram[0x7c4u]=(unsigned char)p;
    }else if(mode>=44u&&mode<=47u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0xf4u]=(unsigned char)(mode==45u||mode==47u?p:1u);
        m->ram[0x7b1u]=(unsigned char)(mode==45u||mode==47u?n:0u);
        m->ram[0xf5u]=0u;m->ram[0xf6u]=2u;
        m->ram[0xf8u]=1u;m->ram[0x7b4u]=(unsigned char)(mode==47u?1u:5u);m->ram[0x7b6u]=5u;
        m->ram[0x7b7u]=(unsigned char)(n+p);
        m->ram[0x7cau]=(unsigned char)(n^p);
        m->ram[0x7b9u]=(unsigned char)(mode==46u?1u:5u);
        m->ram[0x7b8u]=5u;
        m->ram[0x7bau]=(unsigned char)(mode==44u?1u:5u);
        m->ram[0x7b0u]=1u;m->ram[0x7c1u]=2u;
        m->ram[0x200u]=(unsigned char)(mode==46u?(0x80u|(n&7u)):2u);
        m->ram[0x201u]=(unsigned char)(mode==44u?n:2u);
        m->ram[0x202u]=0x11u;
        m->ram[0xf0u]=(unsigned char)p;
        m->ram[0x7c4u]=(unsigned char)(mode==44u?0xffu:n);
        m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }else if(mode==35u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0xf4u]=1u;m->ram[0x7b1u]=0u;
        m->ram[0xf5u]=(unsigned char)(n?0xb0u:0xf9u);
        m->ram[0xf6u]=(unsigned char)(n?7u:0u);
        m->ram[0xf8u]=0u;m->ram[0x7b4u]=5u;
        m->ram[0xf9u]=0u;m->ram[0x7b9u]=(unsigned char)(n?5u:1u);
        m->ram[0x7b8u]=5u;m->ram[0x7bau]=(unsigned char)(n?1u:5u);
        m->ram[0x7b0u]=0u;m->ram[0x7c1u]=2u;
        m->ram[0x7b2u]=0x11u;m->ram[0x7c6u]=0u;m->ram[0xfau]=0u;
    }else if(mode>=30u&&mode<=34u){
        m->ram[0xffu]=0u;m->ram[0xfeu]=0u;m->ram[0xfdu]=0u;
        m->ram[0xfbu]=0u;m->ram[0xfcu]=0u;
        m->ram[0xf4u]=(unsigned char)(mode==32u?p:(mode==33u?1u:((p&128u)?2u:1u)));
        m->ram[0x7b1u]=(unsigned char)(mode==32u?1u:(mode==31u?p:0u));
        m->ram[0xf5u]=0u;m->ram[0xf6u]=2u;
        m->ram[0xf8u]=1u;m->ram[0x7b4u]=5u;m->ram[0x7b6u]=5u;
        m->ram[0x7b7u]=(unsigned char)(mode==31u?n:0u);
        m->ram[0x7cau]=(unsigned char)p;
        m->ram[0x7b9u]=(unsigned char)(mode==30u?p:((mode==31u||mode==34u)?1u:5u));
        m->ram[0x7b8u]=(unsigned char)n;
        m->ram[0x7bau]=(unsigned char)((mode==32u||mode==33u)?1u:5u);
        m->ram[0x7b0u]=1u;m->ram[0x7c1u]=2u;
        m->ram[0x200u]=(unsigned char)(mode==30u?n:(mode==34u?(0x80u|(n&127u)):2u));
        m->ram[0x201u]=(unsigned char)(mode==32u?n:((p&2u)?0u:2u));
        m->ram[0x202u]=0x11u;
        if(mode==33u){
            unsigned int offset;
            for(offset=0u;offset<256u;++offset)m->ram[0x200u+offset]=0x11u;
            m->ram[0x201u]=0u;
            m->ram[0x7c1u]=(unsigned char)(n==0u?0u:n+1u);
        }
        if(mode==34u){m->ram[0xf0u]=(unsigned char)((p&7u)*8u);m->ram[0x7c4u]=(unsigned char)((p&8u)?8u:0u);}
        m->ram[0x7c6u]=0u;m->ram[0x7b2u]=0u;m->ram[0xfau]=0u;
    }
    m->a=(unsigned char)n;m->x=(unsigned char)(p%3u*4u);m->y=(unsigned char)(n*13u);
    if(mode==51u)m->y=(unsigned char)n;
    if(mode==53u)m->y=11u;
    if(mode==55u)m->y=(unsigned char)n;
}
int main(int argc,char **argv)
{
    static const unsigned short entries[10]={0xf2d0u,0xf381u,0xf388u,0xf38bu,0xf38du,0xf39eu,0xf39fu,0xf3a6u,0xf3a9u,0xf3adu};
    core_driver *d=0;core_driver_options opts={0u,LIB_FALSE};core_run_result result;
    FILE *f;unsigned int mode,first,count,n,i,pc,op,addr,value,writes,steps,entry,index,bucket,attempt,boundary;
    unsigned long key;
    time_t start=time(0);
    unsigned char h[16]={'M','S','C','M',1u};
    if(argc!=6)return 64;
    mode=(unsigned int)strtoul(argv[3],0,0);first=(unsigned int)strtoul(argv[4],0,0);count=(unsigned int)strtoul(argv[5],0,0);
    if(mode>61u||!count||count>1024u||first+count>65536u)return 64;
    if(mode==51u&&first+count>768u)return 64;
    if(mode==24u&&(first%256u!=0u||first+count>4096u))return 64;
    if(mode==48u&&(first%1024u!=0u||count!=1024u||first+count>50176u))return 64;
    if(mode==49u&&(first!=0u||count!=1024u))return 64;
    if(mode==50u&&(first!=0u||count!=1u))return 64;
    f=fopen(argv[1],"rb");if(!f||fseek(f,16L,SEEK_SET)||fread(prg,1,32768u,f)!=32768u)return 65;fclose(f);
    if(core_driver_create(&d,&opts)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    baseline=*d->machine;
    if(mode>=55u&&mode<=59u){
        /* These roots run inside NMI after its $2000 NMI-enable clear.
         * Match that hardware entry condition, so a long memory clear cannot
         * nest a new frame handler. No ROM, RAM, or child call is replaced. */
        core_ppu_cpu_write(&baseline.ppu,baseline.cartridge,0u,
            (unsigned char)(baseline.ppu.control&0x7fu));
        core_machine_set_ppu_nmi_line(&baseline,LIB_FALSE);
        baseline.nmi_pending=LIB_FALSE;
        baseline.nmi_defer_once=LIB_FALSE;
    }
    h[5]=(unsigned char)mode;for(i=0;i<4;++i)h[8+i]=(unsigned char)(count>>(i*8u));
    f=fopen(argv[2],"wb");if(!f||fwrite(h,1,16,f)!=16)return 65;
    for(n=first;n<first+count;++n){
        *d->machine=baseline;
        if((mode!=24u&&mode!=48u&&mode!=49u)||(mode==24u&&n%256u==0u)||(mode==48u&&n%1024u==0u)||(mode==49u&&n==0u))fixture(d->machine,n,mode);
        else{
            memcpy(d->machine->ram,live_ram,2048u);
            memcpy(d->machine->apu.registers,live_apu,24u);
        }
        if(mode==49u&&n==0u){
            if(!advance_audio(d->machine,0xf6f5u,0xf73au,10u))return 67;
            for(i=0;i<1023u;++i)if(!advance_audio(d->machine,0xf2d0u,0x8001u,0u))return 67;
        }
        if(mode==50u){
            if(!advance_audio(d->machine,0xf6f5u,0xf73au,17u))return 67;
            d->machine->ram[0x7b4u]=5u;d->machine->ram[0x7b6u]=5u;
            d->machine->ram[0x7b9u]=5u;d->machine->ram[0x7bau]=1u;
            d->machine->ram[0x7b0u]=43u;
        }
        if(mode==58u){
            if(!advance_audio(d->machine,0x9c03u,0x8001u,0u))return 67;
        }
        memset(record,0,sizeof(record));
        index=mode<5u||mode>=14u?0u:mode-4u;
        boundary=mode==27u||(mode==48u&&n%1024u==0u);
        entry=mode>=36u&&mode<=43u?0xf8cbu:(boundary?0xf6f5u:entries[index]);
        if(mode==51u)entry=0xf8f4u;
        if(mode>=52u&&mode<=54u)entry=mode==52u?0x8f06u:(mode==53u?0x8f5fu:0x8f97u);
        if(mode==60u)entry=0x90edu;
        if(mode==61u)entry=0x9131u;
        if(mode>=55u&&mode<=59u){
            static const unsigned short setup_entries[5]={0x90ccu,0x9071u,0x9061u,0x8fe4u,0x8fcfu};
            entry=setup_entries[mode-55u];
        }
        if(mode>=36u&&mode<=43u)d->machine->a=(unsigned char)(mode-36u);
        if(mode==27u)d->machine->y=(unsigned char)n;
        if(mode==48u&&boundary)d->machine->y=(unsigned char)(n/1024u+1u);
        d->machine->pc=(unsigned short)entry;d->machine->s=0xfdu;
        d->machine->ram[0x1feu]=0u;d->machine->ram[0x1ffu]=0x80u;
        record[0]=(unsigned char)entry;record[1]=(unsigned char)(entry>>8u);
        record[2]=d->machine->a;record[3]=d->machine->x;record[4]=d->machine->y;
        memcpy(record+16,d->machine->ram,2048u);memcpy(record+2064,d->machine->apu.registers,24u);
        writes=0;
        for(steps=0;steps<524288u&&d->machine->pc!=(boundary?0xf73au:0x8001u);++steps){
            pc=d->machine->pc;if(pc<0x8000u){fprintf(stderr,"reference low PC mode=%u root=%u pc=%04x steps=%u stack=%02x nmi=%u pending=%u control=%02x\n",mode,n,pc,steps,d->machine->s,d->machine->nmi_asserted,d->machine->nmi_pending,d->machine->ppu.control);return 67;}op=prg[pc-0x8000u];++visits[pc];
            if(d->machine->s<minimum_stack)minimum_stack=d->machine->s;
            if(mode==60u&&pc==0x9110u&&op==0xb9u)
                ++setup_reads[0][0x90e7u+d->machine->y];
            if(mode==61u&&pc>=0x9131u&&pc<0x91beu&&(op==0xb9u||op==0xbdu||op==0xbeu)){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                unsigned int offset=op==0xbdu?d->machine->x:d->machine->y;
                unsigned int kind=5u;
                if(base==0x9116u)kind=0u;
                else if(base==0x9118u)kind=1u;
                else if(base==0x911cu)kind=2u;
                else if(base==0x9125u)kind=3u;
                else if(base==0x912du)kind=4u;
                if(kind<5u)++lookup_reads[kind][base+offset];
            }
            if(pc>=0x9071u&&pc<0x90ccu&&(op==0xb9u||op==0xbdu)){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                unsigned int offset=op==0xb9u?d->machine->y:d->machine->x;
                if(base==0x8fbcu)++setup_reads[0][(base+offset)&65535u];
                if(base==0x8fcbu)++setup_reads[1][(base+offset)&65535u];
            }
            if((op==0xb9u||op==0xbdu)&&pc>=0x8f06u&&pc<0x8fb0u){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                unsigned int offset=op==0xb9u?d->machine->y:d->machine->x;
                if(base==0x8ef4u||base==0x8ef5u)++status_reads[0][(base+offset)&65535u];
                if(base==0x8f00u)++status_reads[1][(base+offset)&65535u];
            }
            if(op==0xb9u&&prg[pc-0x8000u+2u]==0xffu){
                unsigned int low=prg[pc-0x8000u+1u],kind=7u;
                if(low==0u||low==1u)kind=0u;
                else if(low==0x66u)kind=1u;
                else if(low==0x96u)kind=2u;
                else if(low==0x9au)kind=3u;
                else if(low==0xa2u)kind=4u;
                else if(low==0xc9u)kind=5u;
                else if(low==0xeau)kind=6u;
                if(kind<7u)++lookup_reads[kind][(0xff00u+low+d->machine->y)&65535u];
            }
            if(op==0xb9u&&prg[pc-0x8000u+1u]==0xb0u&&prg[pc-0x8000u+2u]==0xf3u)++envelope_reads[d->machine->y];
            if(op==0xb9u&&prg[pc-0x8000u+2u]==0xf4u){
                unsigned int low=prg[pc-0x8000u+1u];
                if(low==0xd3u)++square2_table_reads[0][d->machine->y];
                if(low==0xd9u)++square2_table_reads[1][d->machine->y];
                if(low==0xf8u)++square2_table_reads[2][d->machine->y];
            }
            if(op==0xbeu&&prg[pc-0x8000u+1u]==0x2bu&&prg[pc-0x8000u+2u]==0xf6u)++noise_table_reads[0][d->machine->y];
            if(op==0xb9u&&prg[pc-0x8000u+2u]==0xffu){
                if(prg[pc-0x8000u+1u]==0xeau)++noise_table_reads[1][d->machine->y];
                if(prg[pc-0x8000u+1u]==0xc9u)++noise_table_reads[2][d->machine->y];
            }
            if(pc>=0xf6f5u&&pc<0xf73au&&op==0xb9u){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                if(base>=0xf90cu&&base<=0xf912u)++header_reads[base-0xf90cu][d->machine->y];
            }
            if(pc>=0xf73au&&pc<0xf8c4u&&op==0xb1u&&prg[pc-0x8000u+1u]==0xf5u){
                unsigned int channel=pc<0xf7bcu?0u:(pc<0xf81au?1u:(pc<0xf86du?2u:3u));
                unsigned int base=d->machine->ram[0xf5u]|((unsigned int)d->machine->ram[0xf6u]<<8u);
                ++music_reads[channel][(base+d->machine->y)&65535u];
            }
            addr=0;value=0;
            if(op==0x8du||op==0x8eu||op==0x8cu||op==0x9du||op==0x99u){
                addr=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                if(op==0x9du)addr=(addr+d->machine->x)&65535u;
                if(op==0x99u)addr=(addr+d->machine->y)&65535u;
                value=op==0x8eu?d->machine->x:(op==0x8cu?d->machine->y:d->machine->a);
            }
            if(addr>=0x4000u&&addr<=0x4017u){
                if(writes>=64u)return 68;
                record[4160u+writes*2u]=(unsigned char)(addr-0x4000u);
                record[4161u+writes*2u]=(unsigned char)value;++writes;
            }
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid)return 67;
            if(op==0x20u||op==0x4cu||op==0x60u)++transfers[pc];
            key=(((unsigned long)pc<<16u)|d->machine->pc)+1u;
            bucket=(unsigned int)((key^(key>>13u))&8191u);
            for(attempt=0;attempt<8192u;++attempt){
                if(!transition_keys[bucket]||transition_keys[bucket]==key){transition_keys[bucket]=key;++transition_counts[bucket];break;}
                bucket=(bucket+1u)&8191u;
            }
            if(attempt==8192u)return 68;
            if(time(0)-start>110)return 69;
        }
        if(d->machine->pc!=(boundary?0xf73au:0x8001u)){fprintf(stderr,"reference step limit mode=%u root=%u pc=%04x stack=%02x nmi=%u pending=%u control=%02x\n",mode,n,d->machine->pc,d->machine->s,d->machine->nmi_asserted,d->machine->nmi_pending,d->machine->ppu.control);return 67;}
        record[5]=d->machine->a;record[6]=(unsigned char)writes;
        memcpy(record+2088,d->machine->ram,2048u);memcpy(record+4136,d->machine->apu.registers,24u);
        if(mode==24u||mode==48u||mode==49u){
            memcpy(live_ram,d->machine->ram,2048u);
            memcpy(live_apu,d->machine->apu.registers,24u);
        }
        if(fwrite(record,1,sizeof(record),f)!=sizeof(record))return 65;
    }
    fclose(f);
    printf("mode=%u roots=%u\n",mode,count);
    for(i=0;i<65536u;++i)if(visits[i])printf("pc=%04x visits=%lu transfers=%lu\n",i,visits[i],transfers[i]);
    for(i=0;i<8192u;++i)if(transition_keys[i]){
        key=transition_keys[i]-1u;
        printf("transition=%04x-%04x count=%lu\n",(unsigned int)(key>>16u),(unsigned int)(key&65535u),transition_counts[i]);
    }
    for(i=0;i<256u;++i)if(envelope_reads[i])printf("envelope-index=%u reads=%lu\n",i,envelope_reads[i]);
    for(n=0;n<3u;++n)for(i=0;i<256u;++i)if(square2_table_reads[n][i])printf("square2-table=%u index=%u reads=%lu\n",n,i,square2_table_reads[n][i]);
    for(n=0;n<3u;++n)for(i=0;i<256u;++i)if(noise_table_reads[n][i])printf("noise-table=%u index=%u reads=%lu\n",n,i,noise_table_reads[n][i]);
    for(n=0;n<7u;++n)for(i=0;i<256u;++i)if(header_reads[n][i])printf("header-field=%u index=%u reads=%lu\n",n,i,header_reads[n][i]);
    for(n=0;n<4u;++n)for(i=0;i<65536u;++i)if(music_reads[n][i])printf("music-channel=%u address=%04x reads=%lu\n",n,i,music_reads[n][i]);
    for(n=0;n<7u;++n)for(i=0;i<65536u;++i)if(lookup_reads[n][i])printf("lookup-kind=%u address=%04x reads=%lu\n",n,i,lookup_reads[n][i]);
    for(n=0;n<2u;++n)for(i=0;i<65536u;++i)if(status_reads[n][i])printf("status-table=%u address=%04x reads=%lu\n",n,i,status_reads[n][i]);
    for(n=0;n<2u;++n)for(i=0;i<65536u;++i)if(setup_reads[n][i])printf("setup-table=%u address=%04x reads=%lu\n",n,i,setup_reads[n][i]);
    printf("minimum-stack=%02x\n",minimum_stack);
    core_driver_destroy(d);return 0;
}
