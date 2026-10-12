#include "core/enemy/actor_slots.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;static unsigned char prg[32768];
    unsigned char header[12],record[4100];FILE *file;unsigned int n,a,failures=0U;
    if(argc!=3)return 64;
    file=fopen(argv[2],"rb");
    if(file==0||fseek(file,16L,SEEK_SET)!=0||fread(prg,1U,sizeof(prg),file)!=sizeof(prg))return 65;
    fclose(file);file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,sizeof(header),file)!=sizeof(header)||memcmp(header,"MSFI\1\0\0\0\0\2\0\0",12U)!=0)return 66;
    for(n=0U;n<512U;++n){
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||record[0]!=n%6U||record[1]>1U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+4U,2048U);
        game.area_prg=prg;game.area_prg_size=32768U;
        (void)mysmb_enemy_proc_firebar(&game,record[0]);
        for(a=0U;a<2048U;++a){
            /* $00 is a live loop result after drawing, but child-owned query
             * scratch on early-offscreen exits. Game stack aliases stay included. */
            if(a<8U&&(a!=0U||record[1]==0U))continue;
            if(a>=0x100U&&a<0x200U&&!(a>=0x110U&&a<0x116U)&&!(a>=0x125U&&a<0x12bU))continue;
            if(game.ram[a]!=record[2052U+a]){
                if(failures<24U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,record[2052U+a],game.ram[a]);
                ++failures;
            }
        }
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("checked=512 persistent-bytes=1796 plus-visible-loop failures=%u\n",failures);return failures!=0U;
}
