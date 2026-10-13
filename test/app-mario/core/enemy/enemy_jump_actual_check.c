#include "core/objects.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>
#define RECORD_BYTES 4112U
#define CASES 4U

static int equal_ram(const unsigned char *actual, const unsigned char *expected)
{
    unsigned int i;
    for (i=0U;i<2048U;++i) {
        if (i >= 0x100U && i < 0x200U) continue;
        if (actual[i] != expected[i]) return 0;
    }
    return 1;
}
int main(int argc, char **argv)
{
    static const unsigned char magic[5]={'M','S','J','P',1U};
    struct mysmb_game game; unsigned char head[8],record[RECORD_BYTES];
    unsigned int i; FILE *f;
    if(argc != 2) return 64;
    f=fopen(argv[1],"rb"); if(f==NULL)return 65;
    if(fread(head,1U,sizeof(head),f)!=sizeof(head)||memcmp(head,magic,sizeof(magic))!=0||head[5]!=CASES){fclose(f);return 66;}
    for(i=0U;i<CASES;++i){
        if(fread(record,1U,sizeof(record),f)!=sizeof(record)||record[0]!=0x63U||record[1]!=0xe1U||record[3]!=2U||record[11]!=i||record[12]!=1U||record[13]!=0x80U){fclose(f);return 67;}
        memset(&game,0,sizeof(game)); memcpy(game.ram,record+16U,2048U);
        game.area_prg=mysmb_local_prg; game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
        mysmb_objects_step_enemy_jump_terrain(&game,2U);
        if(!equal_ram(game.ram,record+2064U)){fclose(f);return (int)(i+1U);}
    }
    fclose(f);return 0;
}