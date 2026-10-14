#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include "dos16/pcm.h"
#include "dos16/pit_clock.h"
#ifdef MYGAMES_PCM_BASELINE
#define mygames_dos16_pcm_dos_service(now) ((void)(now))
#endif
static unsigned short submit(const unsigned char *p,unsigned short n)
{
#ifdef MYGAMES_PCM_BASELINE
 return mygames_dos16_pcm_dos_submit(p,n)?n:0;
#else
 return mygames_dos16_pcm_dos_submit(p,n);
#endif
}
static unsigned char samples[2048];
static volatile unsigned short irq_count,gaps,busy_reads;
static volatile unsigned long irq_max,irq_start;
static unsigned short injected;
static unsigned long phase(void)
{
 unsigned short flags,lo,hi,value;unsigned char status;unsigned long ticks;
 _asm pushf
 _asm pop ax
 _asm mov flags,ax
 _asm cli
 ticks=*(volatile unsigned long far *)0x0040006cUL;
 outp(0x43,0xc2);status=(unsigned char)inp(0x40);lo=inp(0x40);hi=inp(0x40);
 value=mygames_dos16_pit_phase(status,(unsigned short)(lo|(hi<<8)));
 outp(0x20,0x0a);if((inp(0x20)&1) && value<32768U)++ticks;
 _asm push flags
 _asm popf
 return (ticks<<16)+value;
}
int mygames_pcm_port_in(unsigned port)
{int value;if(injected && port==0x22c){++busy_reads;return 0x80;}value=inp(port);if(port==0x22c && (value&0x80))++busy_reads;return value;}
void mygames_pcm_irq_probe(int stage)
{unsigned long elapsed;if(!stage){irq_start=phase();return;}elapsed=phase()-irq_start;if(elapsed>irq_max)irq_max=elapsed;++irq_count;if(stage==2)++gaps;}
static unsigned long ticks(void){return *(volatile unsigned long far *)0x0040006cUL;}
int main(void)
{
 unsigned short i,cycle,accepted,normal_irq,normal_gaps,normal_polls,fault_irq_polls;
 unsigned long start,elapsed,submit_max=0,service_max=0,normal_max;
 unsigned long tick;unsigned char master,slave;FILE *file;int result=0;
 master=(unsigned char)inp(0x21);slave=(unsigned char)inp(0xa1);
 for(i=0;i<sizeof(samples);++i)samples[i]=(unsigned char)(i&32U?176U:80U);
 if(!mygames_dos16_pcm_dos_open(11025U))return 2;
 if(submit(samples,2048)!=2048 || submit(samples,2048)!=2048)return 8;
 tick=ticks();while(ticks()==tick){}
 for(cycle=0;cycle<60;++cycle){
  tick=ticks();start=phase();accepted=submit(samples,2048);
  elapsed=phase()-start;if(elapsed>submit_max)submit_max=elapsed;
  if(accepted!=0 && accepted!=2048){result=3;break;}
  start=phase();mygames_dos16_pcm_dos_service(tick<<16);
  elapsed=phase()-start;if(elapsed>service_max)service_max=elapsed;
  while(ticks()==tick){}
  if(cycle==30){mygames_dos16_pcm_dos_reset();submit(samples,2048);submit(samples,2048);tick=ticks();while(ticks()==tick){}}
 }
 normal_irq=irq_count;normal_gaps=gaps;normal_max=irq_max;normal_polls=busy_reads;
 fault_irq_polls=0;irq_max=0;
#ifndef MYGAMES_PCM_BASELINE
 mygames_dos16_pcm_dos_reset();
 if(submit(samples,2048)!=2048 || submit(samples,2048)!=2048)result=4;
 injected=1;busy_reads=0;irq_max=0;tick=ticks();
 while(ticks()-tick<10 && mygames_dos16_pcm_dos_prepared()){}
 if(mygames_dos16_pcm_dos_error()!=MYGAMES_DOS16_PCM_DSP_BUSY || busy_reads!=128)result=5;
 fault_irq_polls=busy_reads;mygames_dos16_pcm_dos_service(ticks()<<16);injected=0;
#endif
 mygames_dos16_pcm_dos_close();
 if(master!=(unsigned char)inp(0x21) || slave!=(unsigned char)inp(0xa1))result=6;
 file=fopen(result?"pcm.bad":"pcm.ok","w");if(!file)return 7;
 fprintf(file,"result=%d cycles=%u normal_irq=%u normal_gaps=%u normal_irq_max_ticks=%lu submit_max_ticks=%lu service_max_ticks=%lu normal_busy_polls=%u fault_irq_polls=%u fault_total_polls=%u fault_irq_ticks=%lu masks_restored=1\n",result,cycle,normal_irq,normal_gaps,normal_max,submit_max,service_max,normal_polls,fault_irq_polls,busy_reads,irq_max);
 fclose(file);return result;
}
