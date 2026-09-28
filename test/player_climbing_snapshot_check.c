#include "game/player.h"
#include <stdio.h>
#include <string.h>

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char header[8];
    static unsigned char record[4098];
    unsigned int i,j,count,found,failures;
    FILE *input;
    if(argc!=2) return 64;
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSWC\1",5)!=0 ||
       header[5]>8U || header[6]!=0U || header[7]!=0U) return 66;
    count=header[5];found=0U;failures=0U;
    for(i=0U;i<count;++i) {
        if(fread(record,1,4098,input)!=4098) return 66;
        if(record[0]!=6U) continue;
        ++found;memcpy(game.ram,record+2U,2048U);
        mysmb_player_climb(&game);
        for(j=8U;j<2048U;++j) {
            if(j>=0x100U && j<0x200U) continue;
            if(game.ram[j]!=record[2050U+j]) {
                printf("%04x original=%02x native=%02x\n",j,
                       (unsigned int)record[2050U+j],(unsigned int)game.ram[j]);
                ++failures;
            }
        }
    }
    if(fgetc(input)!=EOF) return 66;
    fclose(input);
    return found!=1U || failures!=0U?1:0;
}
