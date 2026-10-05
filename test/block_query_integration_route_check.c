#include "core/objects.h"
#include "core/enemy/actor_slots.h"
#include "core/world/world.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;static unsigned char prg[32768];
    struct mysmb_enemy_terrain terrain;struct mysmb_player_terrain player;
    mysmb_u8 index,flag,result;unsigned int k;
    unsigned char header[12],record[4100];FILE *file;unsigned int n,a,kind,slot,failures=0U;
    if(argc!=3)return 64;
    file=fopen(argv[2],"rb");
    if(file==0||fseek(file,16L,SEEK_SET)!=0||fread(prg,1U,sizeof(prg),file)!=sizeof(prg))return 65;
    fclose(file);file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,12U,file)!=12U||memcmp(header,"MSBQ\1\0\0\0\0\112\0\0",12U)!=0)return 66;
    for(n=0U;n<18944U;++n){
        if(n<7168U){kind=0U;k=n;slot=k%6U;index=(mysmb_u8)(k/256U);flag=(mysmb_u8)(k%256U>=128U);}
        else if(n<17536U){k=n-7168U;kind=1U+k/3456U;k%=3456U;slot=0U;index=(mysmb_u8)(k/128U);flag=0U;}
        else if(n<18688U){kind=4U;k=n-17536U;slot=k/128U;index=27U;flag=0U;}
        else{kind=5U;k=n-18688U;slot=k/128U;index=26U;flag=0U;}
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||record[0]!=kind||record[1]!=slot)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+4U,2048U);
        game.area_prg=prg;game.area_prg_size=32768U;
        if(kind==0U)result=mysmb_world_query_enemy_block(&game,(mysmb_u8)slot,index,flag,&terrain);
        else if(kind<4U)result=mysmb_world_query_player_probe(&game,&index,
            (mysmb_u8)(kind==1U?MYSMB_TERRAIN_FEET:(kind==2U?MYSMB_TERRAIN_HEAD:MYSMB_TERRAIN_SIDE)),&player);
        else if(kind==4U)result=mysmb_world_query_misc_block(&game,(mysmb_u8)slot,&terrain);
        else result=mysmb_world_query_fireball_block(&game,(mysmb_u8)slot,&terrain);
        if(result!=(record[2]!=0U?1U:0U)||(kind<4U&&kind!=0U?player.metatile:terrain.metatile)!=record[2])++failures;
        for(a=0U;a<2048U;++a){
            /* Compare all scratch and lower-stack game arrays. */
            if(a>=0x100U&&a<0x200U&&!(a>=0x109U&&a<=0x139U))continue;
            if(game.ram[a]!=record[2052U+a]){
                if(failures<24U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,record[2052U+a],game.ram[a]);++failures;
            }
        }
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("checked=18944 compared-bytes=1841 failures=%u\n",failures);return failures!=0U;
}
