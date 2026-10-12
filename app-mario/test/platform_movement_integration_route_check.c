#include "core/enemy/platform.h"
#include "core/enemy/actor_slots.h"
#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;static unsigned char prg[32768];
    unsigned char header[12],record[4100];FILE *file;unsigned int n,a,kind,slot,failures=0U;
    if(argc!=3)return 64;
    file=fopen(argv[2],"rb");
    if(file==0||fseek(file,16L,SEEK_SET)!=0||fread(prg,1U,sizeof(prg),file)!=sizeof(prg))return 65;
    fclose(file);file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,12U,file)!=12U||memcmp(header,"MSPM\1\0\0\0\300\6\0\0",12U)!=0)return 66;
    for(n=0U;n<1728U;++n){
        kind=n%6U;slot=n/288U;
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||record[0]!=kind||record[1]!=slot)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+4U,2048U);
        game.area_prg=prg;game.area_prg_size=32768U;
        switch(kind){
        case 0U:mysmb_platform_move_y(&game,(mysmb_u8)slot);break;
        case 1U:mysmb_platform_move_x(&game,(mysmb_u8)slot);break;
        case 2U:mysmb_platform_move_drop(&game,(mysmb_u8)slot);break;
        case 3U:mysmb_platform_move_right(&game,(mysmb_u8)slot);break;
        case 4U:mysmb_platform_move_large_lift(&game,(mysmb_u8)slot);break;
        default:mysmb_platform_move_small(&game,(mysmb_u8)slot);break;
        }
        for(a=0U;a<2048U;++a){
            /* Compare all scratch and lower-stack game arrays. */
            if(a>=0x100U&&a<0x200U&&!(a>=0x109U&&a<=0x139U))continue;
            if(game.ram[a]!=record[2052U+a]){
                if(failures<24U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,record[2052U+a],game.ram[a]);++failures;
            }
        }
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("checked=1728 compared-bytes=1841 failures=%u\n",failures);return failures!=0U;
}
