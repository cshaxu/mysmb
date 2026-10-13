#include "app/game_io.h"
#include "core/area.h"
#include "core/audio.h"
#include "core/game.h"
#include "platform/dos16/dos_audio.h"
#include "smb1_local_rom.h"

static unsigned int average_deviation(const mygames_kvm_u8 *samples,unsigned short count)
{
    unsigned short index;
    unsigned long total=0UL;
    for(index=0U;index<count;++index)
        total+=(unsigned long)(samples[index]>128U?samples[index]-128U:128U-samples[index]);
    return (unsigned int)(total/count);
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_io_audio_frame audio;
    struct mysmb_audio_renderer renderer;
    mygames_kvm_u8 samples[184];
    unsigned short count;
    unsigned int frame,level;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    game.ram[0x0770U]=1U;game.ram[0x00fcU]=1U;
    mysmb_audio_renderer_initialize(&renderer);
    for(frame=0U;frame<180U;++frame) {
        mysmb_audio_step(&game);
        if(game.apu_write_count>=MYSMB_APU_WRITE_CAPACITY)return 1;
        mysmb_game_io_audio(&game,&audio);
        count=mysmb_audio_renderer_render(&renderer,&audio,samples,sizeof(samples));
        if(count<183U || count>184U)return 2;
        level=average_deviation(samples,count);
        if(frame==0U && level<4U)return 3;
        if(frame==25U && level>1U)return 4;
        if(frame==40U && level<4U)return 5;
        if(frame==175U && level>1U)return 6;
    }
    return 0;
}
