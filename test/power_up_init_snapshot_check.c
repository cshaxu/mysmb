#include "game/objects.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    FILE *input;
    unsigned int i,failures;
    if(argc!=2) return 64;
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MS6P\1",5)!=0 ||
       (header[5]!=1U && header[5]!=2U) || header[6]>1U ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    if(header[5]==1U) mysmb_objects_start_power_up(&game,header[6]);
    else mysmb_objects_initialize_power_up(&game);
    failures=header[6]!=header[7]?1U:0U;
    for(i=0U;i<2048U;++i) if(game.ram[i]!=expected[i]) {
        printf("%04x original=%02x native=%02x\n",i,(unsigned int)expected[i],(unsigned int)game.ram[i]);++failures;
    }
    return failures?1:0;
}
