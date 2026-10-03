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
static unsigned long material_consumptions[3];
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
    }else if(mode>=94u&&mode<=101u){
        unsigned int j,slot=p%6u;
        m->ram[8u]=(unsigned char)slot;m->ram[9u]=(unsigned char)p;
        m->ram[0x57u]=(unsigned char)(p%3u==0u?0u:(p%3u==1u?7u:0x20u));
        m->ram[0x86u]=(unsigned char)n;m->ram[0x6du]=(unsigned char)p;
        m->ram[0xceu]=(unsigned char)n;m->ram[0x775u]=(unsigned char)(p%3u);
        m->ram[0x71du]=(unsigned char)n;m->ram[0x71bu]=(unsigned char)p;
        m->ram[0x78fu]=(unsigned char)((p&8u)?1u:0u);
        m->ram[0x6cbu]=(unsigned char)((p&1u)?0x12u:0u);
        m->ram[0x6d1u]=(unsigned char)(p%9u);
        m->ram[0x6ccu]=(unsigned char)(p&1u);
        for(j=0u;j<6u;++j){
            m->ram[0xfu+j]=(unsigned char)((p>>j)&1u);
            m->ram[0x16u+j]=0u;m->ram[0x1eu+j]=0u;
            m->ram[0x6eu+j]=(unsigned char)p;m->ram[0x87u+j]=(unsigned char)n;
            m->ram[0xcfu+j]=(unsigned char)n;m->ram[0xb6u+j]=1u;
            m->ram[0xa0u+j]=(unsigned char)n;m->ram[0x58u+j]=(unsigned char)p;
            m->ram[0x401u+j]=(unsigned char)n;m->ram[0x417u+j]=(unsigned char)n;
            m->ram[0x434u+j]=(unsigned char)p;
            m->ram[0x7a7u+j]=(unsigned char)(n*17u+j*7u+p);
        }
        if(mode==95u&&(p&16u)){
            unsigned int lak=p%5u;
            m->ram[0x16u+lak]=0x11u;m->ram[0x1eu+lak]=(unsigned char)((p&32u)?1u:0u);
        }
        if(mode==96u||mode==97u){
            m->ram[0x16u+slot]=(unsigned char)(mode==96u?0x1fu:0x1bu+p%5u);
            m->ram[0x15u]=0u; /* bounded original duplicate search */
        }
        if(mode==99u)m->ram[0x796u+slot]=(unsigned char)((p&1u)?1u:0u);
        if(mode==100u){m->ram[0x16u+slot]=0x0fu;m->p&=0xfeu;}
        if(mode==101u)m->ram[0x16u+slot]=(unsigned char)(0x0au+(p&1u));
    }else if(mode>=90u&&mode<=93u){
        static const unsigned short records[5]={0x9d70u,0x9d8cu,0x9d96u,0x9e21u,0x9e24u};
        unsigned int j,slot=p%6u,index=p%11u,offset=(p&32u)?0x80u:0u;
        unsigned short pointer=(unsigned short)(records[p%5u]-offset);
        m->ram[8u]=(unsigned char)slot;m->ram[9u]=(unsigned char)p;
        m->ram[0xe9u]=(unsigned char)pointer;m->ram[0xeau]=(unsigned char)(pointer>>8u);
        m->ram[0x739u]=(unsigned char)offset;m->ram[0x73au]=2u;
        m->ram[0x73bu]=(unsigned char)((p&16u)?1u:0u);
        m->ram[0x71bu]=2u;m->ram[0x71du]=(unsigned char)n;
        m->ram[0x71au]=1u;m->ram[0x71cu]=0u;m->ram[0x71fu]=(unsigned char)(p%8u);
        m->ram[0x74eu]=(unsigned char)(p%4u);m->ram[0x76au]=(unsigned char)(p&1u);
        m->ram[0x6ccu]=(unsigned char)((p>>1u)&1u);m->ram[0x78fu]=1u;
        m->ram[0x6cbu]=(unsigned char)((p&8u)?0x17u:0u);
        m->ram[0x6cdu]=(unsigned char)((p&4u)?0x2eu:0u);
        m->ram[0x398u]=(unsigned char)(p&1u);m->ram[0x3a0u]=(unsigned char)n;
        m->ram[0x3d0u]=0xffu;m->ram[0x747u]=1u;
        m->ram[0x86u]=(unsigned char)n;m->ram[0x6du]=6u;
        m->ram[0xceu]=(unsigned char)(p*13u);m->ram[0xb5u]=1u;
        m->ram[0x753u]=(unsigned char)(p&1u);m->ram[0x754u]=1u;
        m->ram[0x756u]=(unsigned char)(p%3u);m->ram[0x39u]=(unsigned char)(p%4u);
        for(j=0u;j<6u;++j){
            m->ram[0xfu+j]=(unsigned char)((p>>j)&1u);
            m->ram[0x16u+j]=17u;m->ram[0x1eu+j]=(unsigned char)n;
            m->ram[0x6eu+j]=(unsigned char)p;m->ram[0x87u+j]=(unsigned char)n;
            m->ram[0xcfu+j]=(unsigned char)(n*13u);m->ram[0xb6u+j]=1u;
            m->ram[0x7a7u+j]=(unsigned char)(n*17u);m->ram[0x6e5u+j]=(unsigned char)(j*24u);
            m->ram[0x496u+j]=(unsigned char)n;
        }
        if(mode==90u){m->ram[0x16u+slot]=(unsigned char)(n%55u);m->ram[0xfu+slot]=1u;}
        else m->ram[0xfu+slot]=0u;
        if(mode==91u&&(p&8u)) {m->ram[0xfu+slot]=1u;m->ram[0x16u+slot]=0x2eu;m->ram[0x23u]=0u;}
        if(mode==92u){
            m->ram[0x745u]=1u;m->ram[0x726u]=0u;
            /* Fixture parameters come from unchanged owner-local tables;
             * no table bytes become a tracked fixture or product input. */
            m->ram[0x75fu]=prg[0x406bu+index];m->ram[0x725u]=prg[0x4076u+index];
            m->ram[0xceu]=(unsigned char)((p&16u)?prg[0x4081u+index]:n);
            m->ram[0x1du]=(unsigned char)((p&32u)?1u:0u);
            m->ram[0x6d9u]=(unsigned char)(n%4u);m->ram[0x6dau]=(unsigned char)((n>>2u)%4u);
        }
    }else if(mode>=82u&&mode<=89u){
        unsigned int j,slot=p&1u;
        static const unsigned char tiles[16]={0xc1u,0xc0u,0x5fu,0x60u,0x55u,0x56u,0x57u,0x58u,0x59u,0x5au,0x5bu,0x5cu,0x5du,0x5eu,0x51u,0u};
        m->ram[8u]=(unsigned char)slot;m->ram[9u]=(unsigned char)p;
        m->ram[0x3eeu]=(unsigned char)slot;
        if(mode>=87u)m->ram[0x770u]=(unsigned char)((p&8u)?0u:1u);m->ram[0x753u]=(unsigned char)(p&1u);
        m->ram[0x754u]=(unsigned char)((p>>1u)&1u);
        m->ram[0x756u]=(unsigned char)((p>>2u)%3u);
        m->ram[0x747u]=(unsigned char)((p&16u)?1u:0u);
        m->ram[0x70eu]=(unsigned char)((p&32u)?1u:0u);
        m->ram[0x709u]=(unsigned char)n;
        m->ram[0x71au]=2u;m->ram[0x71cu]=(unsigned char)(p*7u);
        m->ram[0x71bu]=(unsigned char)(2u+(m->ram[0x71cu]?1u:0u));
        m->ram[0x71du]=(unsigned char)(m->ram[0x71cu]-1u);
        m->ram[0x86u]=(unsigned char)n;m->ram[0x6du]=2u;
        m->ram[0xceu]=(unsigned char)(p*13u);m->ram[0xb5u]=1u;
        m->ram[0x9fu]=(unsigned char)(p*17u);
        m->ram[0x416u]=(unsigned char)n;m->ram[0x433u]=(unsigned char)(p*7u);
        m->ram[0x3d0u]=0xffu;m->ram[0x3d1u]=0xffu;
        m->ram[0x23u]=(unsigned char)n;m->ram[0x39u]=(unsigned char)(p%4u);
        m->ram[0x1bu]=0x2eu;m->ram[0x14u]=1u;m->ram[0x4bu]=(unsigned char)((p&1u)+1u);
        m->ram[0x5du]=(unsigned char)(p*17u);m->ram[0x8cu]=(unsigned char)n;
        m->ram[0x73u]=2u;m->ram[0xd4u]=(unsigned char)(p*13u);m->ram[0xbbu]=1u;
        m->ram[0xa5u]=(unsigned char)(p*17u);m->ram[0x49au]=3u;m->ram[0x6eau]=0x40u;
        m->ram[0x400u+6u]=(unsigned char)n;m->ram[0x416u+6u]=(unsigned char)n;
        m->ram[0x433u+6u]=(unsigned char)(p*7u);
        m->ram[6u]=(unsigned char)(p%16u);m->ram[7u]=5u;
        m->ram[2u]=(unsigned char)((p%13u)*16u);
        for(j=0u;j<416u;++j)m->ram[0x500u+j]=0u;
        m->ram[0x500u+m->ram[6u]+m->ram[2u]]=tiles[(p>>2u)%16u];
        if(m->ram[2u]!=0u&&((p&64u)!=0u))m->ram[0x500u+m->ram[6u]+m->ram[2u]-16u]=0xc2u;
        m->ram[0x300u]=(unsigned char)((p%8u)*7u);
        m->ram[0x301u]=(unsigned char)((p&128u)?1u:0u);
        for(j=0u;j<4u;++j){
            m->ram[0x76u+j]=2u;m->ram[0x8fu+j]=(unsigned char)n;
            m->ram[0xd7u+j]=(unsigned char)(n+j*8u);m->ram[0xbeu+j]=1u;
            m->ram[0x60u+j]=(unsigned char)(p*17u);m->ram[0xa8u+j]=(unsigned char)(p*13u);
            m->ram[0x400u+9u+j]=(unsigned char)n;m->ram[0x416u+9u+j]=(unsigned char)n;
            m->ram[0x433u+9u+j]=(unsigned char)(p*7u);
        }
        for(j=0u;j<2u;++j){
            m->ram[0x26u+j]=(unsigned char)((p&4u)?0x12u:0x11u);
            m->ram[0x3e4u+j]=(unsigned char)((p%13u)*16u);
            m->ram[0x3e6u+j]=(unsigned char)(p%16u);
            m->ram[0x3e8u+j]=0xc4u;m->ram[0x3ecu+j]=(unsigned char)((p>>j)&1u);
            m->ram[0x6f1u+j]=(unsigned char)(0x80u+j*16u);
        }
        if(mode>=87u) {m->ram[0x3ecu]=0u;m->ram[0x3edu]=0u;}
        if(mode==88u)m->ram[0x26u+slot]=0x12u;
        if(mode==89u)m->ram[0x26u+slot]=0x11u;
    }else if(mode==76u||mode==77u){
        static const unsigned char hammer_states[4]={0x80u,0x81u,0x82u,0x90u};
        static const unsigned char misc_states[10]={0u,1u,2u,0x2fu,0x30u,0x7fu,0x80u,0x81u,0x82u,0x90u};
        unsigned int j,slot=p%9u,parent=4u+(p&1u);
        m->ram[8u]=(unsigned char)slot;m->ram[9u]=(unsigned char)p;
        m->ram[0x747u]=(unsigned char)((p&8u)?1u:0u);m->ram[0x3d6u]=0xffu;
        m->ram[0x71au]=2u;m->ram[0x71cu]=(unsigned char)(p*7u);
        m->ram[0x71bu]=(unsigned char)(2u+(m->ram[0x71cu]?1u:0u));
        m->ram[0x71du]=(unsigned char)(m->ram[0x71cu]-1u);
        m->ram[0x775u]=(unsigned char)(p*3u);
        for(j=0u;j<9u;++j){
            m->ram[0x6aeu+j]=(unsigned char)parent;
            m->ram[0x7au+j]=2u;m->ram[0x93u+j]=(unsigned char)n;
            m->ram[0xdbu+j]=(unsigned char)(p*13u);m->ram[0xc2u+j]=1u;
            m->ram[0xacu+j]=(unsigned char)((p&16u)?5u:0xfbu);
            m->ram[0x64u+j]=(unsigned char)((p&1u)?0xf0u:0x10u);
            m->ram[0x4a2u+j]=7u;m->ram[0x6f3u+j]=(unsigned char)(0x20u+j*8u);
            m->ram[0x416u+13u+j]=(unsigned char)n;
            m->ram[0x433u+13u+j]=(unsigned char)(p*17u);
            m->ram[0x400u+13u+j]=(unsigned char)(n*17u);
        }
        m->ram[0x2au+slot]=mode==76u?hammer_states[(p>>1u)&3u]:misc_states[(p>>1u)%10u];
        m->ram[0x87u+parent]=(unsigned char)n;m->ram[0x6eu+parent]=(unsigned char)((p&32u)?3u:2u);
        m->ram[0xcfu+parent]=(unsigned char)(p*13u);
        m->ram[0x46u+parent]=(unsigned char)((p&1u)+1u);m->ram[0x1eu+parent]=(unsigned char)n;
    }else if(mode>=78u&&mode<=81u){
        unsigned int j,slot=p&1u;
        m->ram[8u]=(unsigned char)slot;m->ram[0x753u]=(unsigned char)(p&1u);
        m->ram[0x770u]=(unsigned char)((p&16u)?0u:1u);
        m->ram[0x75eu]=(unsigned char)n;m->ram[0x75au]=(unsigned char)(p*13u);
        m->ram[0x300u]=(unsigned char)n;m->ram[0x748u]=(unsigned char)(n+p);
        m->ram[0x76u+slot]=(unsigned char)p;m->ram[0x8fu+slot]=(unsigned char)n;
        m->ram[0xd7u+slot]=(unsigned char)(p*13u);m->ram[0x3eau+slot]=(unsigned char)p;
        m->ram[6u]=(unsigned char)n;m->ram[2u]=(unsigned char)(p*16u);
        for(j=0u;j<3u;++j)m->ram[0x30u+j]=(unsigned char)((p&(4u<<j))?1u:0u);
        for(j=0u;j<36u;++j)m->ram[0x7d7u+j]=(unsigned char)((n+j+p)%10u);
        for(j=0u;j<6u;++j)m->ram[0x134u+j]=(unsigned char)(mode==81u?n+p*17u+j:0u);
        if(mode==78u)m->p=(unsigned char)((m->p&0xfeu)|((p>>1u)&1u));
    }else if(mode==73u){
        unsigned int j;
        m->ram[8u]=5u;m->ram[9u]=(unsigned char)p;
        m->ram[0x398u]=(unsigned char)((p&1u)+1u);
        m->ram[0x399u]=(unsigned char)n;m->ram[0x39au]=4u;m->ram[0x39bu]=5u;
        m->ram[0x39du]=(unsigned char)(p*13u);
        m->ram[0x6fu]=2u;m->ram[0x73u]=2u;
        m->ram[0x8cu]=(unsigned char)(p*17u);m->ram[0xd4u]=(unsigned char)(p*7u);
        m->ram[0xbbu]=1u;m->ram[0x14u]=1u;m->ram[0x13u]=1u;
        m->ram[0x71au]=2u;m->ram[0x71cu]=(unsigned char)n;
        m->ram[0x71bu]=(unsigned char)(2u+(n?1u:0u));m->ram[0x71du]=(unsigned char)(n-1u);
        m->ram[0x6e9u]=0x20u;m->ram[0x6eau]=0x40u;
        for(j=0u;j<416u;++j)m->ram[0x500u+j]=(unsigned char)((p&4u)?0x51u:0u);
    }else if(mode==74u||mode==75u){
        unsigned int j,slot=p%3u;
        m->ram[8u]=(unsigned char)slot;m->ram[9u]=(unsigned char)p;
        m->ram[0x747u]=(unsigned char)((p&8u)?1u:0u);m->ram[0x74eu]=1u;
        m->ram[0x6ccu]=(unsigned char)((p&16u)?1u:0u);
        m->ram[0x86u]=(unsigned char)n;m->ram[0x6du]=2u;
        m->ram[0xceu]=0x70u;m->ram[0xb5u]=2u;
        m->ram[0x71au]=2u;m->ram[0x71cu]=(unsigned char)(p*7u);
        m->ram[0x71bu]=(unsigned char)(2u+(m->ram[0x71cu]?1u:0u));
        m->ram[0x71du]=(unsigned char)(m->ram[0x71cu]-1u);
        m->ram[0x3d1u]=(unsigned char)((p&32u)?0x0cu:0u);
        for(j=0u;j<3u;++j){
            m->ram[0xfu+j]=(unsigned char)((p&1u)?0u:1u);
            m->ram[0x16u+j]=(unsigned char)((p&64u)?0u:0x33u);
            m->ram[0x1eu+j]=(unsigned char)((p&4u)?0x20u:((p&2u)?1u:0u));
            m->ram[0x6eu+j]=(unsigned char)((p&128u)?3u:2u);
            m->ram[0x87u+j]=(unsigned char)(n*13u+j*32u);
            m->ram[0xcfu+j]=(unsigned char)(0x60u+j*16u);m->ram[0xb6u+j]=1u;
            m->ram[0x58u+j]=(unsigned char)((p&1u)?0xe8u:0x18u);
            m->ram[0x46u+j]=(unsigned char)((p&1u)?2u:1u);
            m->ram[0x49au+j]=9u;m->ram[0x6e5u+j]=(unsigned char)(0x20u+j*24u);
            m->ram[0x7a8u+j]=(unsigned char)(n+j);
        }
        for(j=0u;j<6u;++j){m->ram[0x46bu+j]=2u;m->ram[0x471u+j]=(unsigned char)(n+j*32u);m->ram[0x477u+j]=0x90u;m->ram[0x47du+j]=(unsigned char)((p&2u)?1u:0u);}
    }else if(mode==70u){
        static const unsigned char states[4]={2u,1u,0u,0x80u};
        unsigned int slot=p&1u;
        m->ram[0x24u+slot]=states[(p>>4u)&3u];
        m->ram[0x86u]=(unsigned char)n;m->ram[0x6du]=3u;
        m->ram[0xceu]=(unsigned char)(p*13u);
        m->ram[0x33u]=(unsigned char)(((p>>1u)&1u)+1u);
        m->ram[0x74u+slot]=3u;m->ram[0x8du+slot]=(unsigned char)n;
        m->ram[0xd5u+slot]=(unsigned char)(p*13u);
        m->ram[0xbcu+slot]=1u;m->ram[0xa6u+slot]=(unsigned char)((p&4u)?0xfdu:4u);
        m->ram[0x5eu+slot]=(unsigned char)((p&2u)?0xc0u:0x40u);
        m->ram[0x4a0u+slot]=7u;
        m->ram[0x416u+7u+slot]=(unsigned char)n;
        m->ram[0x433u+7u+slot]=(unsigned char)(p*17u);
        m->ram[0x400u+7u+slot]=(unsigned char)(n*17u);
        m->ram[0x71au]=(unsigned char)((p&8u)?2u:3u);
        m->ram[0x71cu]=(unsigned char)(p*17u);
        m->ram[0x71bu]=(unsigned char)(m->ram[0x71au]+(m->ram[0x71cu]?1u:0u));
        m->ram[0x71du]=(unsigned char)(m->ram[0x71cu]-1u);
        m->ram[0x6ecu]=0x20u;m->ram[0x6edu]=0x24u;
        m->ram[9u]=(unsigned char)p;
    }else if(mode==71u||mode==72u){
        unsigned int j,slot=mode==71u?p%3u:p;
        for(j=0u;j<2048u;++j)m->ram[j]=(unsigned char)(n+j*17u+p*13u);
        m->ram[0x86u]=(unsigned char)n;m->ram[0x6du]=(unsigned char)p;
        m->ram[0xceu]=(unsigned char)(n*7u+p);
        m->ram[0x33u]=(unsigned char)((p&1u)+1u);
        m->ram[(unsigned char)(0xe4u+slot)]=(unsigned char)((p&8u)?0xf8u:n);
        m->ram[0x42cu+slot]=(unsigned char)(n*17u+p);
        m->ram[0x792u]=(unsigned char)((p&16u)?1u:0u);
        if(mode==71u)m->ram[0x7a8u+slot]=(unsigned char)(n+p*13u);
        m->ram[7u]=(unsigned char)n;
    }else if(mode>=66u&&mode<=69u){
        unsigned int j;
        for(j=0u;j<2048u;++j)m->ram[j]=(unsigned char)(n+j*17u+p*13u);
        m->ram[0x1du]=(unsigned char)(p&3u);
        m->ram[0x700u]=(unsigned char)n;
        m->ram[0x704u]=(unsigned char)((p>>2u)&1u);
        m->ram[0x47du]=(unsigned char)((p>>3u)&1u);
        m->ram[0x70eu]=0u;m->ram[0xau]=0x80u;m->ram[0xdu]=0u;
        m->ram[0x782u]=(unsigned char)((p>>4u)&1u);
        m->ram[0x9fu]=(unsigned char)((p&32u)?0xffu:4u);
        m->ram[0x74eu]=(unsigned char)((p>>6u)&1u);
        m->ram[0xbu]=(unsigned char)(((p>>2u)&3u)*4u);
        m->ram[0xcu]=(unsigned char)((p>>4u)&3u);
        m->ram[0x490u]=(unsigned char)((p&128u)?0u:0xffu);
        m->ram[0x33u]=(unsigned char)((p&1u)+1u);
        m->ram[0x45u]=(unsigned char)(((p>>1u)&1u)+1u);
        m->ram[0x783u]=(unsigned char)((p&8u)?10u:0u);
        m->ram[0x703u]=(unsigned char)((p&4u)?1u:0u);
        m->ram[0xeu]=(unsigned char)((p&2u)?7u:8u);
        m->ram[0x754u]=(unsigned char)((p>>7u)&1u);
        if(mode==69u){
            m->ram[0x70eu]=(unsigned char)((p&32u)?1u:0u);
            m->ram[0xau]=(unsigned char)((p&16u)?0x40u:0x80u);
            m->ram[0xdu]=(unsigned char)((p&8u)?0x80u:0u);
        }
        if(mode==67u){
            m->ram[0x86u]=(unsigned char)n;
            m->ram[0x789u]=(unsigned char)((p&64u)?1u:0u);
            m->ram[0xcu]=(unsigned char)((p>>1u)&3u);
            m->ram[0x33u]=(unsigned char)((p&1u)+1u);
            m->ram[0x9fu]=(unsigned char)(p*13u);
            m->ram[0x433u]=(unsigned char)n;
            m->ram[0x416u]=(unsigned char)p;
        }
        if(mode==68u){m->ram[0x6fcu]=(unsigned char)p;}
    }else if(mode==65u){
        /* Unchanged level pairs, through three resident parser slots and the
         * real DecodeAreaData vector. No ROM or child call is substituted. */
        static const unsigned short pairs[8]={0xa2d7u,0xa209u,0xa203u,0xa201u,
            0xa1b1u,0xa1bdu,0xa2f1u,0xa35eu};
        static const unsigned char foreground[4]={0u,0x17u,0xc0u,0x54u};
        unsigned int j,address=pairs[n&7u];
        m->ram[0xe7u]=(unsigned char)address;
        m->ram[0xe8u]=(unsigned char)(address>>8u);
        m->ram[0x74eu]=(unsigned char)((n>>3u)&3u);
        m->ram[0x743u]=(unsigned char)((n>>5u)&1u);
        for(j=0u;j<3u;++j)m->ram[0x730u+j]=(unsigned char)((n>>6u)&7u);
        for(j=0u;j<13u;++j)m->ram[0x6a1u+j]=foreground[(n>>9u)&3u];
    }else if(mode==64u){
        unsigned int j;
        for(j=0u;j<2048u;++j)m->ram[j]=(unsigned char)(n+j*17u+p*13u);
        m->ram[0x300u]=(unsigned char)p;
        m->ram[0x77au]=(unsigned char)((p&2u)?0xffu:0u);
        m->ram[0x753u]=(unsigned char)p;
        m->ram[0x770u]=(unsigned char)((p&4u)?3u:1u);
        m->ram[0x75au]=(unsigned char)(n*13u+p);
        m->ram[0x75fu]=(unsigned char)(p&7u);
        m->ram[0x75cu]=(unsigned char)(n&3u);
    }else if(mode==62u||mode==63u){
        unsigned int j;
        for(j=0u;j<2048u;++j)m->ram[j]=(unsigned char)(n+j*17u+p*13u);
        m->ram[0x770u]=3u;
        m->ram[0x75au]=(unsigned char)n;
        m->ram[0x75fu]=(unsigned char)(p&7u);
        m->ram[0x75cu]=(unsigned char)((p>>3u)&3u);
        m->ram[0x760u]=(unsigned char)((p>>3u)&3u);
        m->ram[0x77au]=(unsigned char)((p&32u)?0xffu:0u);
        m->ram[0x761u]=(unsigned char)((p&64u)?0xffu:2u);
        m->ram[0x766u]=(unsigned char)((p+3u)&7u);
        m->ram[0x767u]=(unsigned char)((p+1u)&3u);
        m->ram[0x753u]=(unsigned char)((p>>7u)&1u);
        m->ram[0x71au]=(unsigned char)((n>>1u)&15u);
        if(mode==63u){
            m->ram[0x772u]=(unsigned char)(n%3u);
            m->ram[0x73cu]=13u;
            m->ram[0x6fcu]=(unsigned char)n;
            m->ram[0x7a0u]=(unsigned char)((n&256u)?0u:3u);
        }
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
    if(mode==70u)m->x=(unsigned char)(p&1u);
    if(mode==71u)m->x=(unsigned char)(p%3u);
    if(mode==72u)m->x=(unsigned char)p;
    if(mode==73u)m->x=(unsigned char)((p&8u)?4u:5u);
    if(mode==74u)m->x=(unsigned char)(p%3u);
    if(mode==76u)m->x=(unsigned char)(p%9u);
    if(mode>=94u&&mode<=101u)m->x=(unsigned char)(p%6u);
    if(mode>=90u&&mode<=93u)m->x=(unsigned char)(p%6u);
    if(mode>=82u&&mode<=89u)m->x=(unsigned char)(p&1u);
    if(mode==78u||mode==79u)m->x=(unsigned char)(p&1u);
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
    if(mode>101u||!count||count>1024u||first+count>65536u)return 64;
    if(mode==51u&&first+count>768u)return 64;
    if(mode==24u&&(first%256u!=0u||first+count>4096u))return 64;
    if(mode==48u&&(first%1024u!=0u||count!=1024u||first+count>50176u))return 64;
    if(mode==49u&&(first!=0u||count!=1024u))return 64;
    if(mode==50u&&(first!=0u||count!=1u))return 64;
    f=fopen(argv[1],"rb");if(!f||fseek(f,16L,SEEK_SET)||fread(prg,1,32768u,f)!=32768u)return 65;fclose(f);
    if(core_driver_create(&d,&opts)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    baseline=*d->machine;
    if((mode>=55u&&mode<=59u)||mode==62u||mode==63u||mode>=70u){
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
        if(mode==62u)entry=0x91cdu;
        if(mode==63u)entry=0x9218u;
        if(mode==64u)entry=0x8808u;
        if(mode==65u)entry=0x9508u;
        if(mode==66u)entry=0xb450u;
        if(mode==67u)entry=0xb3cfu;
        if(mode==68u)entry=0xb58fu;
        if(mode==69u)entry=0xb450u;
        if(mode==70u)entry=0xb689u;
        if(mode==71u)entry=0xb6f9u;
        if(mode==72u)entry=0xb70bu;
        if(mode==73u)entry=0xb94bu;
        if(mode==74u)entry=0xba33u;
        if(mode==75u)entry=0xb9bcu;
        if(mode==76u)entry=0xbac3u;
        if(mode==77u)entry=0xbb96u;
        if(mode==78u)entry=0xbb38u;
        if(mode==79u)entry=0xbb51u;
        if(mode==80u)entry=0xbbfeu;
        if(mode==81u)entry=0xbc27u;
        if(mode==82u)entry=0xbc85u;
        if(mode==83u)entry=0xbcedu;
        if(mode==84u)entry=0xbe70u;
        if(mode==85u)entry=0xbed4u;
        if(mode==86u)entry=0xbf4du;
        if(mode==87u)entry=0xbe02u;
        if(mode==88u)entry=0xbe41u;
        if(mode==89u)entry=0xbe70u;
        if(mode==90u)entry=0xc26cu;
        if(mode==91u)entry=0xc047u;
        if(mode==92u)entry=0xc0ccu;
        if(mode==93u)entry=0xc144u;
        if(mode==94u)entry=0xc385u;
        if(mode==95u)entry=0xc3a4u;
        if(mode==96u)entry=0xc459u;
        if(mode==97u)entry=0xc45cu;
        if(mode==98u)entry=0xc4a8u;
        if(mode==99u)entry=0xc9b0u;
        if(mode==100u)entry=0xc34au;
        if(mode==101u)entry=0xc375u;
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
        if(mode==78u)record[7]=(unsigned char)(d->machine->p&1u);
        record[2]=d->machine->a;record[3]=d->machine->x;record[4]=d->machine->y;
        memcpy(record+16,d->machine->ram,2048u);memcpy(record+2064,d->machine->apu.registers,24u);
        writes=0;
        if(mode>=87u&&mode<=89u)record[8]=1u;
        if(mode==100u||mode==101u)record[8]=2u;
        for(steps=0;steps<524288u;++steps){
            if(d->machine->pc==(boundary?0xf73au:0x8001u)) {
                if(mode>=87u&&mode<=89u&&record[9]==0u) {
                    /* Sequential original producer/consumer roots. Keep all
                     * persistent RAM, registers and hardware intact; restore
                     * only the declared test return sentinel on stack. */
                    if(mode==88u)++material_consumptions[1];
                    else if(d->machine->ram[0x301u]==0u&&
                        d->machine->ram[0x3ecu+d->machine->ram[0x3eeu]]!=0u)
                        ++material_consumptions[mode==87u?0u:2u];
                    record[9]=1u;d->machine->pc=mode==88u?0xbe70u:0xbed4u;
                    d->machine->s=0xfdu;d->machine->ram[0x1feu]=0u;
                    d->machine->ram[0x1ffu]=0x80u;
                } else if((mode==100u||mode==101u)&&record[9]==0u){
                    record[9]=1u;d->machine->pc=mode==100u?0xcaffu:0xcc4au;
                    d->machine->s=0xfdu;d->machine->ram[0x1feu]=0u;
                    d->machine->ram[0x1ffu]=0x80u;
                } else break;
            }
            pc=d->machine->pc;if(pc<0x8000u){fprintf(stderr,"reference low PC mode=%u root=%u pc=%04x steps=%u stack=%02x nmi=%u pending=%u control=%02x\n",mode,n,pc,steps,d->machine->s,d->machine->nmi_asserted,d->machine->nmi_pending,d->machine->ppu.control);return 67;}op=prg[pc-0x8000u];++visits[pc];
            if(d->machine->s<minimum_stack)minimum_stack=d->machine->s;
            if(mode>=94u&&mode<=101u){
                unsigned int base=0u,offset=0u;
                if(op==0xbdu||op==0xfdu||op==0xddu){
                    base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                    offset=d->machine->x;
                }else if(op==0xb5u||op==0xd5u||op==0xf5u){base=prg[pc-0x8000u+1u];offset=d->machine->x;}
                if(base&&(mode==99u||record[9]))++lookup_reads[6][base+offset];
            }
            if(mode>=90u&&(pc==0x8e0du||pc==0x8e12u)&&
                d->machine->ram[4u]==0x81u&&d->machine->ram[5u]==0xc2u)
                ++lookup_reads[5][0xc281u+d->machine->y];
            if(mode>=82u&&(pc==0x8e0du||pc==0x8e12u)&&
                d->machine->ram[4u]==0xbfu&&d->machine->ram[5u]==0xbdu)
                ++lookup_reads[4][0xbdbfu+d->machine->y];
            if(mode==60u&&pc==0x9110u&&op==0xb9u)
                ++setup_reads[0][0x90e7u+d->machine->y];
            if(mode==62u&&pc==0x91f6u&&op==0xbcu)
                ++setup_reads[0][0x91bdu+d->machine->x];
            if(mode>=78u&&pc>=0xbbfeu&&pc<0xbc36u&&(op==0xbcu||op==0xb9u)){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                unsigned int kind=base==0xbbf8u?0u:(base==0xbbfau?1u:(base==0xbbfcu?2u:3u));
                if(kind<3u)++lookup_reads[kind][base+(op==0xbcu?d->machine->x:d->machine->y)];
            }
            if(mode==73u&&pc==0xb956u&&op==0xd9u)++lookup_reads[0][0xb949u+d->machine->y];
            if(mode>=70u&&pc>=0xb689u&&pc<0xb74bu&&(op==0xb9u||op==0xf9u)){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                unsigned int kind=3u;
                if(base==0xb687u)kind=0u;
                else if(base==0xb74bu)kind=1u;
                else if(base==0xb74du)kind=2u;
                if(kind<3u)++lookup_reads[kind][base+d->machine->y];
            }
            if(mode>=66u&&mode<=69u&&pc>=0xb3cfu&&pc<0xb5c6u&&(op==0xb9u||op==0xbdu||op==0xbeu||op==0x7du)){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                unsigned int offset=(op==0xbdu||op==0x7du)?d->machine->x:d->machine->y;
                if(base>=0xb3c7u&&base<=0xb58cu)++lookup_reads[0][base+offset];
            }
            if(mode==65u&&pc>=0x99edu&&pc<0x9a69u&&(op==0xb9u||op==0xbeu)){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                unsigned int kind=5u;
                if(base==0x99eeu)kind=0u;
                else if(base==0x99f9u)kind=1u;
                else if(base==0x99fcu)kind=2u;
                else if(base==0x9a25u)kind=3u;
                else if(base==0x9a29u)kind=4u;
                if(kind<5u)++lookup_reads[kind][base+d->machine->y];
            }
            if(mode==64u&&pc>=0x8808u&&pc<0x889fu&&(op==0xb9u||op==0xbdu||op==0xbeu)){
                unsigned int base=prg[pc-0x8000u+1u]|((unsigned int)prg[pc-0x8000u+2u]<<8u);
                unsigned int offset=op==0xbdu?d->machine->x:d->machine->y;
                unsigned int kind=4u;
                if(base==0x87feu)kind=0u;
                else if(base==0x8752u)kind=1u;
                else if(base==0x87edu)kind=2u;
                else if(base==0x87f2u)kind=3u;
                if(kind<4u)++lookup_reads[kind][base+offset];
            }
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
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){fprintf(stderr,"reference trap mode=%u root=%u pc=%04x opcode=%02x next=%04x steps=%u stack=%02x\n",mode,n,pc,op,d->machine->pc,steps,d->machine->s);return 67;}
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
    for(i=0;i<3u;++i)if(material_consumptions[i])printf("material-chain=%u consumptions=%lu\n",i,material_consumptions[i]);
    core_driver_destroy(d);return 0;
}
