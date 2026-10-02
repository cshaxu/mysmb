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
static unsigned long visits[65536],transfers[65536];
static unsigned long transition_keys[8192],transition_counts[8192];
static int ready(core_machine *m)
{
    core_run_result r;unsigned int i;
    for(i=0;i<524288u;++i){
        if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    }
    return 0;
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
    }
    m->a=(unsigned char)n;m->x=(unsigned char)(p%3u*4u);m->y=(unsigned char)(n*13u);
}
int main(int argc,char **argv)
{
    static const unsigned short entries[10]={0xf2d0u,0xf381u,0xf388u,0xf38bu,0xf38du,0xf39eu,0xf39fu,0xf3a6u,0xf3a9u,0xf3adu};
    core_driver *d=0;core_driver_options opts={0u,LIB_FALSE};core_run_result result;
    FILE *f;unsigned int mode,first,count,n,i,pc,op,addr,value,writes,steps,entry,index,bucket,attempt;
    unsigned long key;
    time_t start=time(0);
    unsigned char h[16]={'M','S','C','M',1u};
    if(argc!=6)return 64;
    mode=(unsigned int)strtoul(argv[3],0,0);first=(unsigned int)strtoul(argv[4],0,0);count=(unsigned int)strtoul(argv[5],0,0);
    if(mode>13u||!count||count>1024u||first+count>65536u)return 64;
    f=fopen(argv[1],"rb");if(!f||fseek(f,16L,SEEK_SET)||fread(prg,1,32768u,f)!=32768u)return 65;fclose(f);
    if(core_driver_create(&d,&opts)!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    baseline=*d->machine;
    h[5]=(unsigned char)mode;for(i=0;i<4;++i)h[8+i]=(unsigned char)(count>>(i*8u));
    f=fopen(argv[2],"wb");if(!f||fwrite(h,1,16,f)!=16)return 65;
    for(n=first;n<first+count;++n){
        *d->machine=baseline;fixture(d->machine,n,mode);memset(record,0,sizeof(record));
        index=mode<5u?0u:mode-4u;entry=entries[index];
        d->machine->pc=(unsigned short)entry;d->machine->s=0xfdu;
        d->machine->ram[0x1feu]=0u;d->machine->ram[0x1ffu]=0x80u;
        record[0]=(unsigned char)entry;record[1]=(unsigned char)(entry>>8u);
        record[2]=d->machine->a;record[3]=d->machine->x;record[4]=d->machine->y;
        memcpy(record+16,d->machine->ram,2048u);memcpy(record+2064,d->machine->apu.registers,24u);
        writes=0;
        for(steps=0;steps<524288u&&d->machine->pc!=0x8001u;++steps){
            pc=d->machine->pc;if(pc<0x8000u)return 67;op=prg[pc-0x8000u];++visits[pc];
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
        if(d->machine->pc!=0x8001u)return 67;
        record[5]=d->machine->a;record[6]=(unsigned char)writes;
        memcpy(record+2088,d->machine->ram,2048u);memcpy(record+4136,d->machine->apu.registers,24u);
        if(fwrite(record,1,sizeof(record),f)!=sizeof(record))return 65;
    }
    fclose(f);
    printf("mode=%u roots=%u\n",mode,count);
    for(i=0;i<65536u;++i)if(visits[i])printf("pc=%04x visits=%lu transfers=%lu\n",i,visits[i],transfers[i]);
    for(i=0;i<8192u;++i)if(transition_keys[i]){
        key=transition_keys[i]-1u;
        printf("transition=%04x-%04x count=%lu\n",(unsigned int)(key>>16u),(unsigned int)(key&65535u),transition_counts[i]);
    }
    core_driver_destroy(d);return 0;
}
