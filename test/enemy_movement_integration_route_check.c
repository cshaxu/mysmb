#include "game/enemy/movement.h"
#include <stdio.h>
#include <string.h>

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char header[12],record[4100];
    FILE *file;
    unsigned int n,a,kind,local,failures=0U;
    if(argc!=2)return 64;
    file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,sizeof(header),file)!=sizeof(header)||
        memcmp(header,"MSEM\1\0\0\0\0\44\0\0",12U)!=0)return 66;
    for(n=0U;n<9216U;++n){
        kind=n<6144U?0U:n<7680U?1U:2U;
        local=kind==0U?n:kind==1U?n-6144U:n-7680U;
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||
            record[0]!=kind||record[1]!=local/(kind==0U?1024U:256U))return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+4U,2048U);
        if(kind==0U)mysmb_enemy_move_normal(&game,record[1]);
        else if(kind==1U)mysmb_enemy_move_defeated(&game,record[1]);
        else mysmb_enemy_move_jumping(&game,record[1]);
        for(a=8U;a<2048U;++a){
            /* Game-owned lower-stack aliases are included explicitly. */
            if(a>=0x100U&&a<0x200U&&!(a>=0x110U&&a<0x116U)&&
                !(a>=0x125U&&a<0x12bU))continue;
            if(game.ram[a]!=record[2052U+a]){
                if(failures<24U)printf("case=%u kind=%u ram=%04x ROM=%02x C=%02x\n",
                    n,kind,a,record[2052U+a],game.ram[a]);
                ++failures;
            }
        }
    }
    if(fgetc(file)!=EOF)return 66;
    fclose(file);
    printf("checked=9216 persistent-bytes=1796 failures=%u\n",failures);
    return failures!=0U;
}
