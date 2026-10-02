#include "game/player.h"
#include "game/player/terrain_children.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768];unsigned char head[12],rec[4105];FILE *f;
    unsigned int n,a,k,failures=0U;mysmb_u8 actual,expected;
    if(argc!=3)return 64;
    f=fopen(argv[2],"rb");if(f==0||fseek(f,16L,SEEK_SET)!=0||fread(prg,1U,sizeof(prg),f)!=sizeof(prg))return 65;
    fclose(f);f=fopen(argv[1],"rb");if(f==0)return 65;
    if(fread(head,1U,sizeof(head),f)!=sizeof(head)||memcmp(head,"MSTC\1\0\0\0\40\3\0\0",12U)!=0)return 66;
    for(n=0U;n<800U;++n){
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec))return 66;
        k=rec[0];if(k!=(n<32U?0U:1U+(n-32U)/256U))return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,rec+9U,2048U);
        game.area_prg=prg;game.area_prg_size=32768U;
        if(k==0U){
            expected=(mysmb_u8)(game.ram[0x0754U]+(game.ram[0x0714U]!=0U?1U:0U));
            if(rec[6]!=expected)++failures;
            if(rec[7]!=0xffU&&rec[8]!=(mysmb_player_invisible_metatile(rec[7])!=0U?2U:0U))++failures;
            mysmb_player_background_collision(&game);
        }else {
            actual=k==1U?mysmb_world_is_solid(&game,rec[1]):(k==2U?mysmb_world_is_climbable(&game,rec[1]):mysmb_player_invisible_metatile(rec[1]));
            expected=(mysmb_u8)((rec[5]&(k==3U?2U:1U))!=0U);
            if(actual!=expected||rec[2]!=rec[1]||(k!=3U&&(rec[3]!=rec[1]/64U||rec[4]!=rec[1])))++failures;
            game.area_prg=0;game.area_prg_size=0U;
            if(k==1U&&mysmb_world_is_solid(&game,rec[1])!=expected)++failures;
            if(k==2U&&mysmb_world_is_climbable(&game,rec[1])!=expected)++failures;
        }
        /* Terrain query scratch is an explicit struct/register ABI. Direct
         * pure predicates compare all non-stack RAM, without scratch exclusions. */
        for(a=k==0U?8U:0U;a<2048U;++a)if(!(a>=0x100U&&a<0x200U)&&game.ram[a]!=rec[2057U+a]){
            if(failures<16U)printf("case=%u kind=%u ram=%04x ROM=%02x C=%02x\n",n,k,a,rec[2057U+a],game.ram[a]);++failures;
        }
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);
    printf("checked=800 terrain=32 predicates=768 failures=%u\n",failures);return failures!=0U;
}
