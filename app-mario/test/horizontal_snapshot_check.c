#include "core/world/world.h"
#include "core/player.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned char header[8];
    mysmb_u8 result;
    unsigned int i,failures;
    FILE *f;
    if(argc!=2) return 64;
    f=fopen(argv[1],"rb");if(f==NULL) return 65;
    if(fread(header,1,8,f)!=8 || memcmp(header,"MSXP\1",5)!=0) return 66;
    memset(&g,0,sizeof(g));
    if(fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF) return 66;
    fclose(f);
    switch(header[5]) {
    case 1U: result=mysmb_player_move_horizontally(&g);break;
    case 2U: result=mysmb_world_move_enemy_horizontally(&g,header[6]);break;
    case 3U: result=mysmb_world_move_spr_object_horizontally(&g,header[6]);break;
    default:return 66;
    }
    failures=0U;
    for(i=0U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U && (i<0x133U || i>0x139U)) continue;
        if(g.ram[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,(unsigned int)expected[i],(unsigned int)g.ram[i]);
            ++failures;
        }
    }
    if(result!=header[7]) { printf("return-A original=%02x native=%02x\n",(unsigned int)header[7],(unsigned int)result);++failures; }
    return failures?1:0;
}
