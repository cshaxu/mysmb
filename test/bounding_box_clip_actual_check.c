#include "core/world/world.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char head[12],rec[4100];FILE *f;
    unsigned int n,a,failures=0U,address;
    unsigned char obj,middle_x,middle_page;
    if(argc!=2)return 64;
    f=fopen(argv[1],"rb");if(f==0)return 65;
    if(fread(head,1U,sizeof(head),f)!=sizeof(head)||
       memcmp(head,"MSCL\1\0\0\0\0\20\0\0",12U)!=0)return 66;
    for(n=0U;n<4096U;++n) {
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec))return 66;
        obj=rec[0];if(obj!=n%18U||rec[1]!=n%9U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,rec+4U,2048U);
        address=0x04acU+obj*4U;
        middle_x=(unsigned char)(game.ram[0x071cU]+128U);
        middle_page=(unsigned char)(game.ram[0x071aU]+(game.ram[0x071cU]>=128U?1U:0U));
        mysmb_world_clip_bounding_box_to_screen(&game,(mysmb_u16)address,
            game.ram[0x006dU+obj],game.ram[0x0086U+obj]);
        /* Explicit register/scratch argument seam; stack and flags are CPU ABI. */
        if(rec[2]!=rec[1]||rec[3]!=(unsigned char)(obj*4U)||
           rec[2053U]!=middle_page||rec[2054U]!=middle_x)++failures;
        for(a=0U;a<8U;++a)if(a!=1U&&a!=2U&&rec[2052U+a]!=rec[4U+a])++failures;
        for(a=8U;a<2048U;++a)if(!(a>=0x100U&&a<0x200U)&&game.ram[a]!=rec[2052U+a]) {
            if(failures<16U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,rec[2052U+a],game.ram[a]);
            ++failures;
        }
    }
    if(fgetc(f)!=EOF)return 66;
    fclose(f);printf("checked=4096 persistent-bytes=1784 failures=%u\n",failures);
    return failures!=0U;
}
