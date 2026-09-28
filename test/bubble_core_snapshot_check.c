#include "game/fireball/fireball.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned int i,failures;
    FILE *input;
    if(argc!=2) return 64;
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSBP\1",5)!=0 ||
       (header[5]!=1U && header[5]!=2U) || header[6]>2U || header[7]!=0U ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    if(header[5]==1U) mysmb_fireball_check_bubble(&game,header[6]);
    else mysmb_fireball_setup_bubble(&game,header[6]);
    failures=0U;
    /* $07 is the explicit random-bit input/output of this chain. */
    for(i=7U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U) continue;
        if(game.ram[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)game.ram[i]);++failures;
        }
    }
    return failures!=0U;
}
