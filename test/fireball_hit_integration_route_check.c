#include "game/world/world.h"
#include "game/enemy/actor_slots.h"
#include "game/oam/oam.h"
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
    if(fread(header,1U,12U,file)!=12U||memcmp(header,"MSFH\1\0\0\0\0\16\0\0",12U)!=0)return 66;
    for(n=0U;n<3584U;++n){
        kind=n>=3072U;slot=kind==0U?n/512U:(n-3072U)/256U;
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||record[0]!=kind||record[1]!=slot)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+4U,2048U);
        game.area_prg=prg;game.area_prg_size=32768U;
        if(kind==0U)mysmb_world_handle_fireball_enemy_hit(&game,(mysmb_u8)slot);
        else mysmb_world_fireball_enemy_collision(&game,(mysmb_u8)slot);
        for(a=0U;a<2048U;++a){
            /* Compare all scratch and lower-stack game arrays. */
            if(a>=0x100U&&a<0x200U&&!(a>=0x109U&&a<=0x139U))continue;
            if(game.ram[a]!=record[2052U+a]){
                if(failures<24U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,record[2052U+a],game.ram[a]);++failures;
            }
        }
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("checked=3584 compared-bytes=1841 failures=%u\n",failures);return failures!=0U;
}
