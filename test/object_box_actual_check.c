#include "game/objects.h"
#include "game/enemy/platform.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char head[8],rec[4098];FILE *f;
    unsigned int n,a,failures=0U;
    if(argc!=2)return 64;
    f=fopen(argv[1],"rb");if(f==0)return 65;
    if(fread(head,1U,8U,f)!=8U||memcmp(head,"MSBX\1",5U)!=0||head[5]!=60U)return 66;
    for(n=0U;n<60U;++n) {
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec)||rec[0]!=n/12U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,rec+2U,2048U);
        switch(rec[0]) {
        case 0U:mysmb_world_get_fireball_bounding_box(&game,rec[1]);break;
        case 1U:mysmb_objects_get_coin_bounding_box(&game,rec[1]);break;
        case 2U:mysmb_objects_update_enemy_bounding_box(&game,rec[1]);break;
        case 3U:mysmb_platform_box_small(&game,rec[1]);break;
        case 4U:mysmb_platform_box_large(&game,rec[1]);break;
        default:return 66;
        }
        /* Scratch $00-$07 and CPU stack are the separately audited child ABI.
         * Every persistent byte is compared even when ROM did not change it. */
        for(a=8U;a<2048U;++a)if(!(a>=0x100U&&a<0x200U)&&game.ram[a]!=rec[2050U+a]) {
            if(failures<16U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,rec[2050U+a],game.ram[a]);
            ++failures;
        }
        if(rec[0]==1U) {
            memset(&game,0,sizeof(game));memcpy(game.ram,rec+2U,2048U);
            mysmb_objects_get_hammer_bounding_box(&game,rec[1]);
            for(a=8U;a<2048U;++a)if(!(a>=0x100U&&a<0x200U)&&game.ram[a]!=rec[2050U+a])++failures;
        }
    }
    if(fgetc(f)!=EOF)return 66;
    fclose(f);printf("checked=60 plus 12 misc hammer counterparts failures=%u\n",failures);
    return failures!=0U;
}
