#include "game/world/world.h"
#include <stdio.h>
#include <string.h>
#define RECORD_BYTES 4112U
int main(int argc, char **argv)
{
    static const unsigned char magic[5]={'M','S','L','D',1U};
    struct mysmb_game game; unsigned char head[8],record[RECORD_BYTES];
    unsigned int i; FILE *f;
    if(argc != 2) return 64;
    f=fopen(argv[1],"rb"); if(f==NULL)return 65;
    if(fread(head,1U,sizeof(head),f)!=sizeof(head)||memcmp(head,magic,sizeof(magic))!=0||head[5]!=2U){fclose(f);return 66;}
    for(i=0U;i<2U;++i){
        if(fread(record,1U,sizeof(record),f)!=sizeof(record)||record[0]!=0x4fU||record[1]!=0xe1U||record[3]!=2U||record[11]!=i||record[12]!=1U||record[13]!=0x80U){fclose(f);return 67;}
        memset(&game,0,sizeof(game)); memcpy(game.ram,record+16U,2048U); mysmb_world_land_enemy(&game,2U);
        if(game.ram[0x00a2U]!=record[2064U+0x00a2U]||game.ram[0x0436U]!=record[2064U+0x0436U]||game.ram[0x00d1U]!=record[2064U+0x00d1U]){fclose(f);return 1;}
    }
    fclose(f); return 0;
}
