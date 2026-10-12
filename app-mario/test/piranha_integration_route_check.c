#include "core/objects.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char header[12],record[4100];FILE *file;unsigned int n,a,kind,slot,failures=0U;
    if(argc!=2)return 64;
    file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,12U,file)!=12U||memcmp(header,"MSPI\1\0\0\0\200\7\0\0",12U)!=0)return 66;
    for(n=0U;n<1920U;++n){
        kind=n>=1536U;slot=kind==0U?n/256U:(n-1536U)/64U;
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||record[0]!=kind||record[1]!=slot)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+4U,2048U);
        mysmb_objects_step_piranha_plants_slot(&game,(mysmb_u8)slot);
        for(a=0U;a<2048U;++a){
            /* Compare all scratch and lower-stack game aliases. */
            if(a>=0x100U&&a<0x200U&&!(a>=0x109U&&a<=0x139U))continue;
            if(game.ram[a]!=record[2052U+a]){
                if(failures<24U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,record[2052U+a],game.ram[a]);++failures;
            }
        }
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("checked=1920 compared-bytes=1841 failures=%u\n",failures);return failures!=0U;
}
