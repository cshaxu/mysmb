#include "game/audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
    static struct mysmb_game g; static unsigned char prg[32768], h[16], sh[8], r[4144];
    static const unsigned int ra[]={0xf9,0x7b8,0x7b9};
    static const unsigned int aa[]={8,10,11};
    FILE *f; unsigned int c,i,n=0,e=0;
    if(argc!=4||(c=(unsigned int)atoi(argv[3]))<111U||c>114U)return 64;
    f=fopen(argv[2],"rb"); if(!f)return 65;
    if(fread(h,1,16,f)!=16||memcmp(h,"NES\032",4)||h[4]!=2||fread(prg,1,32768,f)!=32768)return 66; fclose(f);
    f=fopen(argv[1],"rb"); if(!f||fread(sh,1,8,f)!=8||memcmp(sh,"MSSN\1",5)||!sh[5]||sh[5]>8)return 66;
    for(n=0;n<sh[5];n++){if(fread(r,1,4144,f)!=4144)return 66;memset(&g,0,sizeof(g));memcpy(g.ram,r,2048);memcpy(g.apu_registers,r+2048,24);g.area_prg=prg;g.area_prg_size=32768;mysmb_audio_step(&g);for(i=0;i<3;i++)if(g.ram[ra[i]]!=r[2072+ra[i]])e++;for(i=0;i<3;i++)if(g.apu_registers[aa[i]]!=r[4120+aa[i]])e++;} fclose(f);printf("triangle case=%u children=%u failures=%u\n",c,n,e);return e!=0;}
