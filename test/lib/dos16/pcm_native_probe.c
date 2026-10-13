#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include "dos16/pcm.h"
static unsigned char samples[512];
static unsigned long ticks(void){return *(volatile unsigned long far *)0x0040006cUL;}
int main(void)
{
 unsigned short i,cycle;unsigned long tick;unsigned char master,slave;FILE *file;int result=0;
 master=(unsigned char)inp(0x21);slave=(unsigned char)inp(0xa1);
 for(i=0;i<sizeof(samples);++i)samples[i]=(unsigned char)(i&32U?176U:80U);
 if(mygames_dos16_pcm_dos_open(0))return 1;
 if(!mygames_dos16_pcm_dos_open(11025U))return 2;
 for(cycle=0;cycle<36;++cycle){
  tick=ticks();if(!mygames_dos16_pcm_dos_submit(samples,sizeof(samples))){result=3;break;}
  while(ticks()==tick){}
  if(cycle==18)mygames_dos16_pcm_dos_reset();
 }
 mygames_dos16_pcm_dos_close();
 if(master!=(unsigned char)inp(0x21) || slave!=(unsigned char)inp(0xa1))result=4;
 file=fopen(result?"pcm.bad":"pcm.ok","w");if(!file)return 5;
 fprintf(file,"result=%d blocks=%u samplesPerBlock=512 masksRestored=1\n",result,cycle);fclose(file);return result;
}
