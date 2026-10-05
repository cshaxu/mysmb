#include "game/player.h"
#include <stdio.h>
#include <string.h>

/* Original natural entry/return RAM. No fixture correction or excluded
 * persistent graphics/control bytes may hide a disagreement. */
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned int i,failures;
    FILE *input;
    if(argc!=2) return 64;
    input=fopen(argv[1],"rb");
    if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSSC\1\0\0\0",8)!=0 ||
       fread(game.ram,1,2048,input)!=2048 ||
       fread(expected,1,2048,input)!=2048 || fgetc(input)!=EOF) {
        fclose(input);return 66;
    }
    fclose(input);
    game.ppu.ppu_control_0=game.ram[0x778U];
    mysmb_player_update_scroll(&game);
    failures=0U;
    for(i=0U;i<2048U;++i) {
        /* CPU scratch and hardware call stack are not native C ABI state. */
        if(i<8U || (i>=0x100U && i<0x200U)) continue;
        if(game.ram[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                   (unsigned int)expected[i],(unsigned int)game.ram[i]);
            ++failures;
        }
    }
    return failures!=0U ? 1:0;
}
