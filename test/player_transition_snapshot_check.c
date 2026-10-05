#include "game/player.h"
#include "game/area.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>
/* Production whole-call checker; all child discrepancies remain failures. */
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned int i,failures;
    FILE *input;
    if(argc!=2) return 64;
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSTP\1",5)!=0 ||
       header[5]<1U || header[5]>4U || header[7]!=0U ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    mysmb_game_bind_area_source(&game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    game.ppu.ppu_control_0=game.ram[0x778U];
    switch(header[5]) {
    case 1U: mysmb_player_step_auto_climb(&game);break;
    case 2U: mysmb_player_step_side_pipe(&game);break;
    case 3U: mysmb_player_step_vertical_pipe(&game);break;
    default: mysmb_player_move_y_axis(&game,header[6]);break;
    }
    failures=0U;
    for(i=8U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U) continue;
        if(game.ram[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                   (unsigned int)expected[i],(unsigned int)game.ram[i]);
            ++failures;
        }
    }
    return failures!=0U ? 1:0;
}
