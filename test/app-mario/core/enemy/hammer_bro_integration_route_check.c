#include "core/enemy/actor_slots.h"
#include <stdio.h>
#include <string.h>

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char header[12],record[4100];
    FILE *file;
    unsigned int n,a,failures=0U;
    if(argc!=2)return 64;
    file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,sizeof(header),file)!=sizeof(header)||
        memcmp(header,"MSHB\1\0\0\0\0\14\0\0",12U)!=0)return 66;
    for(n=0U;n<3072U;++n){
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||
            record[0]!=n/512U||record[1]!=(n/128U)%4U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+4U,2048U);
        mysmb_objects_step_hammer_bros_slot(&game,record[0]);
        /* All persistent RAM is compared; CPU scratch/stack are explicit ABI exclusions. */
        for(a=8U;a<2048U;++a){
            if(a>=0x100U&&a<0x200U)continue;
            if(game.ram[a]!=record[2052U+a]){
                if(failures<24U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,record[2052U+a],game.ram[a]);
                ++failures;
            }
        }
    }
    if(fgetc(file)!=EOF)return 66;
    fclose(file);
    printf("checked=3072 persistent-bytes=1784 failures=%u\n",failures);
    return failures!=0U;
}
