#include "game/enemy/movement.h"
#include <stdio.h>
#include <string.h>

/* Compare the existing native movement owner from an observed original
 * entry state. The reference must reach both boundaries through NMI. */
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char magic[8];
    unsigned int i,failures;
    FILE *input;
    if(argc!=2) return 64;
    input=fopen(argv[1],"rb");
    if(input==NULL) return 65;
    if(fread(magic,1,8,input)!=8 || memcmp(magic,"MSNM\1\0\0\0",8)!=0 ||
       fread(game.ram,1,2048,input)!=2048 ||
       fread(expected,1,2048,input)!=2048 || fgetc(input)!=EOF) {
        fclose(input);return 66;
    }
    fclose(input);
    if(game.ram[8]>=6U) return 67;
    mysmb_enemy_move_normal(&game,game.ram[8]);
    failures=0U;
    for(i=0U;i<2048U;++i) {
        /* The same established persistent-RAM contract as NMI records;
         * graphics work bytes and OAM are explicitly included. */
        if(i<8U || (i>=0x100U && i<0x200U) || i==0x778U || i==0x779U)
            continue;
        if(game.ram[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                   (unsigned int)expected[i],(unsigned int)game.ram[i]);
            ++failures;
        }
    }
    return failures!=0U ? 1 : 0;
}
