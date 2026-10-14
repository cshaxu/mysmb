/* Exercises the production hardware owner through ports, IVT, memory and FLAGS. */
#include <stdio.h>
#include <string.h>
#include "dos16/pcm.h"
static unsigned char memory[4096],master=255,slave=255;
static unsigned short flags=0x200,segment=0x1000;
static unsigned allocated,release_error,restore_error,alloc_fail,signature=1;
static unsigned writes,polls,busy_after=9999,busy_always,masked=1,reset_port;
static unsigned pending,other_pending,poll_command,irq=5,inject_irq;
static void (*vector)(void);
static const char *environment="A220 I5 D1";
#define CHECK(c) do {if(!(c)){fprintf(stderr,"DOS PCM line %d\n",__LINE__);return 1;}}while(0)
unsigned short pcm_irq_save(void){unsigned short old=flags;flags=0;return old;}
void pcm_irq_restore(unsigned short old){flags=old;if(old && vector && (inject_irq || pending)){inject_irq=pending=0;flags=0;vector();flags=old;}}
unsigned char *pcm_segment(unsigned short s){(void)s;return memory;}
int current_blaster(char *out,unsigned short count)
{if(!environment || strlen(environment)>=count)return 0;strcpy(out,environment);return 1;}
unsigned _dos_allocmem(unsigned paragraphs,unsigned short *s)
{if(alloc_fail || paragraphs!=256)return 1;++allocated;*s=segment;return 0;}
unsigned _dos_freemem(unsigned s)
{(void)s;if(!masked || vector)release_error=1;--allocated;return 0;}
void (*_dos_getvect(unsigned n))(void){(void)n;return vector;}
void _dos_setvect(unsigned n,void (*p)(void))
{(void)n;if(flags)restore_error=1;vector=p;}
int inp(unsigned port)
{
    if(port==0x21)return master;if(port==0xa1)return slave;
    if(port==0x20)return pending && irq<8?(1U<<irq):other_pending?2:0;
    if(port==0xa0)return pending && irq>=8?(1U<<(irq-8)):0;
    if(port==0x22e)return signature?0x80:0;
    if(port==0x22a)return 0xaa;
    if(port==0x22c){++polls;return busy_always || writes>=busy_after?0x80:0;}
    return 0;
}
int outp(unsigned port,int value)
{
    if(port==0x21)master=(unsigned char)value;
    if(port==0xa1)slave=(unsigned char)value;
    if((port==0x20 || port==0xa0) && value==0x0c)poll_command=port;
    if(port==0xa && (value&3)==1)masked=(value&4)!=0;
    if(port==0x226){reset_port=(unsigned)value;if(!value)writes=0;}
    if(port==0x22c)++writes;
    return value;
}
static void complete(void)
{unsigned short old=flags;flags=0;if(vector)vector();flags=old;}
static void fresh(void)
{
    mygames_dos16_pcm_dos_close();writes=polls=0;busy_always=0;busy_after=9999;signature=1;
    flags=0x200;master=slave=255;irq=5;environment="A220 I5 D1";segment=0x1000;
}
int main(void)
{
    static unsigned char data[5000];unsigned i,n,accepted;unsigned short old;
    memset(data,42,sizeof(data));
    CHECK(!mygames_dos16_pcm_dos_open(0));environment=0;CHECK(!mygames_dos16_pcm_dos_open(11025));
    fresh();signature=0;CHECK(!mygames_dos16_pcm_dos_open(11025) && !allocated);
    fresh();alloc_fail=1;CHECK(!mygames_dos16_pcm_dos_open(11025) && !allocated);alloc_fail=0;
    fresh();segment=0x1f01;CHECK(!mygames_dos16_pcm_dos_open(11025) && !allocated);
    fresh();CHECK(mygames_dos16_pcm_dos_open(11025));
    CHECK(!mygames_dos16_pcm_dos_submit(0,1) && !mygames_dos16_pcm_dos_submit(data,0));
    accepted=mygames_dos16_pcm_dos_submit(data,5000);CHECK(accepted==4096 && !memcmp(memory,data,4096));
    CHECK(!mygames_dos16_pcm_dos_submit(data,1) && vector && !masked);
    complete();CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);complete();complete();
    /* Spurious IRQ cannot free a filling block or start it early. */
    CHECK(mygames_dos16_pcm_dos_submit(data,200)==200);n=writes;complete();CHECK(writes==n);
    CHECK(mygames_dos16_pcm_dos_submit(data,1848)==1848);
    mygames_dos16_pcm_dos_reset();CHECK(masked && !vector && mygames_dos16_pcm_dos_prepared());
    CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);
    pending=1;other_pending=1;master&=(unsigned char)~2U;mygames_dos16_pcm_dos_close();
    CHECK(!allocated && !pending && other_pending && master==253 && flags==0x200 && !release_error && !restore_error);
    fresh();CHECK(mygames_dos16_pcm_dos_open(11025));CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);
    inject_irq=1;CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);
    CHECK(writes==12 && flags==0x200 && !memcmp(memory+2048,data,2048));
    complete();CHECK(mygames_dos16_pcm_dos_submit(data,4096)==4096);mygames_dos16_pcm_dos_close();
    fresh();CHECK(mygames_dos16_pcm_dos_open(11025));CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);
    flags=0;pending=1;CHECK(!mygames_dos16_pcm_dos_close());
    CHECK(allocated && vector && masked && flags==0 && mygames_dos16_pcm_dos_phase()==MYGAMES_AUDIO_STOPPING);
    pcm_irq_restore(0x200);mygames_dos16_pcm_dos_service(0);CHECK(!allocated && !vector);
    /* Every partial start failure masks DMA, latches once and leaves no retry. */
    for(i=0;i<6;++i) {
        fresh();CHECK(mygames_dos16_pcm_dos_open(11025));busy_after=i;polls=0;
        CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);
        CHECK(polls<=128 && masked && mygames_dos16_pcm_dos_phase()==MYGAMES_AUDIO_FAILED);
        n=polls;CHECK(!mygames_dos16_pcm_dos_submit(data,1) && polls==n);
        mygames_dos16_pcm_dos_service(100);CHECK(!allocated && !vector && mygames_dos16_pcm_dos_error()==MYGAMES_DOS16_PCM_DSP_BUSY);
    }
    fresh();CHECK(mygames_dos16_pcm_dos_open(11025));CHECK(mygames_dos16_pcm_dos_submit(data,4096)==4096);
    busy_always=1;polls=0;complete();CHECK(polls==128 && masked && !mygames_dos16_pcm_dos_prepared());
    mygames_dos16_pcm_dos_close();CHECK(!allocated && !vector);
    fresh();CHECK(mygames_dos16_pcm_dos_open(11025));CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);
    mygames_dos16_pcm_dos_service(0xfffffff0UL);mygames_dos16_pcm_dos_service(0x100UL);CHECK(allocated);
    mygames_dos16_pcm_dos_service(1000000UL);CHECK(!allocated && mygames_dos16_pcm_dos_error()==MYGAMES_DOS16_PCM_LOST_IRQ);
    fresh();CHECK(mygames_dos16_pcm_dos_open(11025));flags=0;old=flags;
    CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048 && flags==old);
    mygames_dos16_pcm_dos_reset();CHECK(flags==old && allocated);
    CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);signature=0;mygames_dos16_pcm_dos_reset();CHECK(!allocated && flags==old);
    fresh();environment="A220 I10 D1";irq=10;CHECK(mygames_dos16_pcm_dos_open(11025));
    CHECK(mygames_dos16_pcm_dos_submit(data,2048)==2048);pending=1;mygames_dos16_pcm_dos_close();CHECK(!pending && master==255 && slave==255);
    CHECK(!release_error && !restore_error && !allocated);puts("DOS PCM hardware lifecycle passed");return 0;
}
