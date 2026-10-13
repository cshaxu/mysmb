#include "core/enemy/x_counter.h"
#include "core/enemy/actor_slots.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char header[12],record[4100];FILE *file;
    unsigned int n,a,kind,local,failures=0U;
    if(argc!=2)return 64;
    file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,sizeof(header),file)!=sizeof(header)||
        memcmp(header,"MSXC\1\0\0\0\0\22\0\0",12U)!=0)return 66;
    for(n=0U;n<4608U;++n){
        kind=n<3072U?0U:1U;local=kind==0U?n:n-3072U;
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||
            record[0]!=kind||record[1]!=local/(kind==0U?512U:256U))return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+4U,2048U);
        if(kind==0U)mysmb_enemy_move_with_x_counters(&game,record[1]);
        else mysmb_objects_step_flying_green_paratroopas_slot(&game,record[1]);
        for(a=0U;a<2048U;++a){
            /* Returned $00 is compared; other transient scratch is excluded.
             * Lower-stack game arrays are persistent and remain included. */
            if(a>0U&&a<8U)continue;
            if(a>=0x100U&&a<0x200U&&!(a>=0x110U&&a<0x116U)&&!(a>=0x125U&&a<0x12bU))continue;
            if(game.ram[a]!=record[2052U+a]){
                if(failures<24U)printf("case=%u ram=%04x ROM=%02x C=%02x\n",n,a,record[2052U+a],game.ram[a]);
                ++failures;
            }
        }
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("checked=4608 compared-bytes=1797 failures=%u\n",failures);return failures!=0U;
}
