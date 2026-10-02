#include "game/world/world.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char head[12],rec[4100];FILE *f;
    unsigned int n,a,failures=0U,address;
    unsigned char obj,rel,x,y,control;
    if(argc!=2)return 64;
    f=fopen(argv[1],"rb");if(f==0)return 65;
    if(fread(head,1U,sizeof(head),f)!=sizeof(head)||
       memcmp(head,"MSBC\1\0\0\0\0\14\0\0",12U)!=0)return 66;
    for(n=0U;n<3072U;++n) {
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec))return 66;
        obj=rec[0];rel=rec[1];if(obj!=n%18U||rel!=n%7U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,rec+4U,2048U);
        x=game.ram[0x03adU+rel];y=game.ram[0x03b8U+rel];
        control=game.ram[0x0499U+obj];address=0x04acU+obj*4U;
        if(control!=n/256U||x!=(unsigned char)n||y!=(unsigned char)(255U-x))return 66;
        mysmb_world_set_bounding_box(&game,(mysmb_u16)address,control,x,y);
        /* Original X restoration, Y box offset and scratch-to-argument seam.
         * C does not expose CPU registers/stack or retain transient scratch. */
        if(rec[2]!=obj||rec[3]!=(unsigned char)(obj*4U)||
           rec[2052U]!=obj||rec[2053U]!=x||rec[2054U]!=y)++failures;
        for(a=3U;a<8U;++a)if(rec[2052U+a]!=rec[4U+a])++failures;
        for(a=8U;a<2048U;++a)if(!(a>=0x100U&&a<0x200U)&&game.ram[a]!=rec[2052U+a]) {
            if(failures<16U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,rec[2052U+a],game.ram[a]);
            ++failures;
        }
    }
    if(fgetc(f)!=EOF)return 66;
    fclose(f);printf("checked=3072 persistent-bytes=1784 failures=%u\n",failures);
    return failures!=0U;
}
