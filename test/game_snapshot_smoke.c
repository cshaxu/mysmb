#include <string.h>
#include "app/game_snapshot.h"
#include "io/snapshot_keys.h"
#include "game/ppu_frame.h"

static struct mysmb_game first,second,before;
static struct mysmb_io_snapshot saved,again;
static struct mysmb_ppu_frame pixels1,pixels2;
static unsigned char resource1[32],resource2[32];
int main(void)
{
    unsigned int i;
    unsigned char fingerprint[16];
    struct mysmb_input input;
    struct mysmb_frame frame1,frame2;
    struct mysmb_snapshot_keys keys;
    struct mysmb_io_snapshot_cache cache;
    /* Every mutable byte differs from the destination. Resources have equal
     * bytes but distinct addresses: restore must retain destination bindings. */
    memset(&first,0x35,sizeof(first));memset(&second,0x96,sizeof(second));
    first.area_prg=resource1;second.area_prg=resource2;
    first.area_prg_size=second.area_prg_size=sizeof(resource1);
    first.ppu.chr_data=second.ppu.chr_data=0;first.ppu.chr_data_size=second.ppu.chr_data_size=0;
    first.title_data=second.title_data=0;first.title_data_size=second.title_data_size=0;
    first.title_icon_data=second.title_icon_data=0;
    first.title_icon_data_size=second.title_icon_data_size=0;
    first.frame_number=0xabcdef12UL;first.startup_phase=4U;
    first.oam_dma_primed=first.ppu.visible_sprite0_split=1U;
    first.apu_write_count=64U;first.area_command_count=16U;
    for(i=0U;i<64U;++i)first.apu_writes[i].index=(unsigned char)(i%24U);
    mysmb_game_snapshot_fingerprint(&first,fingerprint);
    if(!mysmb_game_snapshot_capture(&first,&saved,fingerprint) ||
        !mysmb_game_snapshot_restore(&second,&saved))return 1;
    if(second.area_prg!=resource2 || second.area_prg_size!=32U)return 2;
    if(!mysmb_game_snapshot_capture(&second,&again,fingerprint) ||
        memcmp(saved.payload,again.payload,MYSMB_SNAPSHOT_CORE_BYTES))return 3;
    before=second;saved.payload[4428]=65U;
    if(mysmb_game_snapshot_restore(&second,&saved) || memcmp(&second,&before,sizeof(second)))return 4;
    saved.payload[4428]=64U;resource2[0]=1U;
    if(mysmb_game_snapshot_restore(&second,&saved) || memcmp(&second,&before,sizeof(second)))return 5;
    /* Execute from a legitimate ROM-free reset, then compare every persisted
     * state byte and composed pixel after each subsequent identical input. */
    mysmb_game_initialize(&first);mysmb_game_initialize(&second);
    mysmb_game_snapshot_fingerprint(&first,fingerprint);
    input.buttons=0U;input.buttons2=0U;
    for(i=0U;i<100U;++i)mysmb_game_tick(&first,&input,&frame1);
    if(!mysmb_game_snapshot_capture(&first,&saved,fingerprint) ||
        !mysmb_game_snapshot_restore(&second,&saved))return 6;
    for(i=0U;i<240U;++i){
        input.buttons=(unsigned char)((i%31U)==0U?MYSMB_BUTTON_START:0U);
        mysmb_game_tick(&first,&input,&frame1);mysmb_game_tick(&second,&input,&frame2);
        mysmb_game_snapshot_capture(&first,&saved,fingerprint);
        mysmb_game_snapshot_capture(&second,&again,fingerprint);
        if(memcmp(saved.payload,again.payload,MYSMB_SNAPSHOT_CORE_BYTES))return 7;
        mysmb_ppu_frame_build(&first,&pixels1);mysmb_ppu_frame_build(&second,&pixels2);
        if(memcmp(pixels1.pixels,pixels2.pixels,sizeof(pixels1.pixels)))return 8;
    }
    mysmb_snapshot_keys_reset(&keys);
    if(mysmb_snapshot_keys_transition(&keys,MYSMB_IO_REQUEST_SAVE,1U,1U)!=MYSMB_IO_REQUEST_SAVE ||
        mysmb_snapshot_keys_transition(&keys,MYSMB_IO_REQUEST_SAVE,1U,1U)!=0U)return 9;
    mysmb_snapshot_keys_transition(&keys,MYSMB_IO_REQUEST_SAVE,0U,1U);
    if(mysmb_snapshot_keys_transition(&keys,MYSMB_IO_REQUEST_SAVE,1U,0U)!=0U)return 10;
    mysmb_snapshot_cache_initialize(&cache);
    if(mysmb_snapshot_cache_current(&cache)!=0)return 11;
    mysmb_snapshot_cache_update(&cache,&saved,1U);
    again.payload[0]^=1U;mysmb_snapshot_cache_update(&cache,&again,0U);
    if(memcmp(mysmb_snapshot_cache_current(&cache),&saved,sizeof(saved)))return 12;
    return 0;
}
