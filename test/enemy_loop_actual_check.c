#include "game/enemy/core.h"
#include "game/enemy/stream.h"
#include "game/enemy/init.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

/* Integrated diagnostic: no child substitutions or scratch-byte masking. */
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    struct mysmb_area_source source;
    unsigned char header[8];
    unsigned int i,failures;
    FILE *file;
    if(argc!=2) return 64;
    file=fopen(argv[1],"rb");if(file==NULL) return 65;
    if(fread(header,1,8,file)!=8 || memcmp(header,"MSEP\1",5)!=0) return 66;
    if(fread(game.ram,1,2048,file)!=2048 || fread(expected,1,2048,file)!=2048 ||
        fgetc(file)!=EOF) return 66;
    fclose(file);
    game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    game.ppu_control_0=game.ram[0x778U];
    source.prg=mysmb_local_prg;source.prg_size=MYSMB_LOCAL_PRG_SIZE;
    if(header[7]==0U) mysmb_enemy_core_step_slot(&game,&source,header[6]);
    else if(header[7]==1U) {
        switch(header[5]) {
        case 1U: (void)mysmb_enemy_stream_process_current(&game,&source,header[6]);break;
        case 2U: mysmb_enemy_checkpoint_loaded(&game,header[6]);break;
        case 3U: mysmb_enemy_run_objects(&game);break;
        default:return 66;
        }
    } else return 66;
    failures=0U;
    for(i=0U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U && (i<0x133U || i>0x139U)) continue;
        if(game.ram[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)game.ram[i]);
            ++failures;
        }
    }
    return failures?1:0;
}
