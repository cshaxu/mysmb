/* Owner-ROM integration fixture, not a product or default CTest.
 * Caller supplies build-contained output paths and a qualified entry wrapper.
 * Bounded:720 ticks,2,949,120 state bytes and61,440 final pixel bytes. */
#include <stdio.h>
#include "core/game.h"
#include "core/area.h"
#include "ppu/frame.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

static struct mysmb_game game;
static struct mysmb_frame frame;
static unsigned char pixels[2048];

int mysmb_test_cross_width_replay(const char *states_path,const char *pixels_path)
{
    struct mysmb_input input;
    struct mysmb_ppu_frame_workspace workspace;
    struct mysmb_ppu_frame_view view;
    unsigned short i;
    FILE *file;
    mysmb_game_power_on(&game);mysmb_game_frame_initialize(&frame);
    mysmb_game_bind_area_source(&game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&game,mysmb_local_title_data,
        MYSMB_LOCAL_TITLE_DATA_SIZE,mysmb_local_title_icon_data,
        MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    while(!mysmb_game_startup_step(&game,1U)){}
    file=fopen(states_path,"wb");if(!file)return 1;
    for(i=0U;i<720U;++i) {
        input.buttons=i==100U?MYSMB_BUTTON_START:
            (i>=300U && i<340U?MYSMB_BUTTON_RIGHT:0U);
        input.buttons2=0U;mysmb_game_tick(&game,&input,&frame);
        if(fwrite(game.ram,1,2048,file)!=2048 ||
            fwrite(game.ppu.name_table,1,2048,file)!=2048) {
            fclose(file);return 2;
        }
    }
    if(fclose(file))return 2;
    file=fopen(pixels_path,"wb");if(!file)return 3;
    mysmb_ppu_frame_workspace_bind(&workspace,0);
    mysmb_ppu_frame_begin(&game.ppu,&workspace,&view);
    for(i=0U;i<240U;i+=8U) {
        if(!mysmb_ppu_frame_rows(&view,pixels,sizeof(pixels),i,8U) ||
            fwrite(pixels,1,sizeof(pixels),file)!=sizeof(pixels)) {
            mysmb_ppu_frame_end(&view);fclose(file);return 4;
        }
    }
    mysmb_ppu_frame_end(&view);
    return fclose(file)?4:0;
}
