#include "core/enemy/core.h"
#include "core/enemy/platform.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;static unsigned char prg[32768];
    unsigned char head[12],rec[4100];FILE *f;unsigned int n,a,failures=0U;
    if(argc!=3)return 64;f=fopen(argv[2],"rb");
    if(f==0||fseek(f,16L,SEEK_SET)!=0||fread(prg,1U,sizeof(prg),f)!=sizeof(prg))return 65;
    fclose(f);f=fopen(argv[1],"rb");if(f==0)return 65;
    if(fread(head,1U,sizeof(head),f)!=sizeof(head)||memcmp(head,"MSPL\1\0\0\0\0\2\0\0",12U)!=0)return 66;
    for(n=0U;n<512U;++n){
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec)||rec[0]!=n/256U||rec[1]!=n%6U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,rec+4U,2048U);game.area_prg=prg;game.area_prg_size=32768U;
        if(rec[0]==0U)mysmb_enemy_run_small_platform(&game,rec[1]);else mysmb_enemy_run_large_platform(&game,rec[1]);
        /* Transient CPU scratch/stack are a separately checked child ABI;
         * every persistent byte including OAM is compared unconditionally. */
        for(a=8U;a<2048U;++a)if(!(a>=0x100U&&a<0x200U)&&game.ram[a]!=rec[2052U+a]){
            if(failures<24U)printf("case=%u kind=%u ram=%04x ROM=%02x C=%02x\n",n,rec[0],a,rec[2052U+a],game.ram[a]);++failures;
        }
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);
    printf("checked=512 persistent-bytes=1784 failures=%u\n",failures);return failures!=0U;
}
