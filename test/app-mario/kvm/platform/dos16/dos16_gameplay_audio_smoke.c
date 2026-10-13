#include "app/game_io.h"
#include "core/game.h"
#include "platform/dos16/dos_audio.h"
#include "smb1_local_rom.h"

static unsigned long sample_energy(const mygames_kvm_u8 *samples,
                                   unsigned short count)
{
    unsigned short index;
    unsigned long total=0UL;
    for(index=0U;index<count;++index)
        total+=(unsigned long)(samples[index]>128U ? samples[index]-128U :
            128U-samples[index]);
    return total;
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_io_audio_frame audio;
    struct mysmb_audio_renderer renderer;
    mygames_kvm_u8 samples[184];
    unsigned int tick;
    unsigned short count;
    unsigned long energy=0UL;

    /* This is the normal product route: title input starts World 1, then
     * GameEngine produces audio from its real area/music state.  It does not
     * call a music routine or insert any synthetic APU write. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_audio_renderer_initialize(&renderer);
    input.buttons=MYSMB_BUTTON_START;
    input.buttons2=0U;
    for(tick=0U;tick<180U;++tick) {
        mysmb_game_tick(&game,&input,&frame);
        mysmb_game_io_audio(&game,&audio);
        count=mysmb_audio_renderer_render(&renderer,&audio,samples,
            sizeof(samples));
        if(count<183U || count>184U)return 1;
        /* The Start edge is one logical frame only, as supplied by the DOS
         * keyboard adapter. */
        input.buttons=0U;
        if(tick>=30U)energy+=sample_energy(samples,count);
    }
    if(game.ram[0x0770U]!=1U)return 2;
    if(energy==0UL)return 3;
    return 0;
}
