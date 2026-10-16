/* Independent diagnostic composition; never linked as a product entry.
 * Mask bits A=1,B=2,C=4. C needs B; A is independently selectable. */
#include <dos.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "core/area.h"
#include "core/observation.h"
#include "app/game_io.h"
#include "platform/dos16/devices.h"
#include "platform/dos16/nibble_expand.h"
#include "platform/dos16/slot_copy.h"
#include "dos16/host.h"
#include "dos16/vga.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

static struct mysmb_game game;
static struct mysmb_frame frame;
static struct mysmb_ppu_frame_workspace workspace;
static struct mysmb_io_audio_frame audio;
static unsigned char far band[4096];
static unsigned char far *a,*b,*c;
static unsigned char palette[32];
static unsigned long overhead,raw_prepare,raw_compose,raw_publish;
static unsigned long prepare,compose,publish;
static unsigned mask,play_frames,title_samples,play_samples;
static FILE *pixels,*timing;

static unsigned long elapsed(unsigned long start,unsigned long *raw)
{
    unsigned long delta=mygames_dos16_clock_stamp()-start;
    *raw+=delta;return delta>overhead?delta-overhead:0UL;
}
static int draw(unsigned phase,unsigned sample)
{
    struct mysmb_ppu_frame_view view;
    struct mygames_kvm_video_band output;
    unsigned first;
    unsigned long start;
    raw_prepare=raw_compose=raw_publish=prepare=compose=publish=0UL;
    start=mygames_dos16_clock_stamp();
    mysmb_ppu_frame_begin(&game.ppu,&workspace,&view);
    prepare=elapsed(start,&raw_prepare);
    start=mygames_dos16_clock_stamp();
    mysmb_ppu_frame_palette(&game.ppu,palette);
    mysmb_dos16_devices_palette(palette);
    publish+=elapsed(start,&raw_publish);
    for(first=0;first<240U;first+=16U) {
        start=mygames_dos16_clock_stamp();
        if(!mysmb_ppu_frame_slot_rows(&view,band,sizeof(band),first,16U))return 0;
        compose+=elapsed(start,&raw_compose);
        output.pixels=band;output.first=first;output.rows=16U;
        output.width=output.stride=256U;output.capacity=sizeof(band);
        start=mygames_dos16_clock_stamp();
        if(!mysmb_dos16_devices_present_band(&output))return 0;
        publish+=elapsed(start,&raw_publish);
    }
    mysmb_ppu_frame_end(&view);
    if(sample) {
        /* Exact physical slot pixels, active palette and original RAM.
         * File I/O and VGA readback are outside all measured kernels. */
        if(fwrite(palette,1,32,pixels)!=32U ||
            fwrite(game.ram,1,2048,pixels)!=2048U ||
            fwrite(mygames_dos16_vga_memory(),1,61440U,pixels)!=61440U)return 0;
        fprintf(timing,"phase=%u frame=%lu prepare=%lu compose=%lu publish=%lu raw_prepare=%lu raw_compose=%lu raw_publish=%lu\n",
            phase,game.frame_number,prepare,compose,publish,raw_prepare,raw_compose,raw_publish);
        if(phase)++play_samples;else ++title_samples;
    }
    return 1;
}
static int run(void)
{
    struct mysmb_io_input decoded;
    struct mysmb_input input;
    unsigned steps;
    int active;
    unsigned long start,delta;
    mysmb_game_power_on(&game);mysmb_game_frame_initialize(&frame);
    mysmb_game_bind_area_source(&game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&game,mysmb_local_title_data,MYSMB_LOCAL_TITLE_DATA_SIZE,
        mysmb_local_title_icon_data,MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    mysmb_text_observer_enable(&game,1U);
    if(mask&1U)a=(unsigned char far *)_fmalloc(8192U);
    if(mask&2U)b=(unsigned char far *)_fmalloc(63488U);
    if(mask&4U)c=(unsigned char far *)_fmalloc(61440U);
    if(((mask&1U)&&!a)||((mask&2U)&&!b)||((mask&4U)&&!c))return 2;
    mysmb_ppu_frame_workspace_bind(&workspace,a);
    if(c)mysmb_ppu_frame_background_byte_bind(&workspace,b,63488U,c,61440U);
    else mysmb_ppu_frame_background_bind(&workspace,b,63488U);
    mysmb_ppu_frame_nibble_bind(&workspace,mysmb_dos16_nibble_expand);
    mysmb_ppu_frame_slot_rows_bind(&workspace,mysmb_dos16_slot_rows_copy);
    overhead=0xffffffffUL;
    for(steps=0;steps<32U;++steps) {
        start=mygames_dos16_clock_stamp();delta=mygames_dos16_clock_stamp()-start;
        if(delta<overhead)overhead=delta;
    }
    fprintf(timing,"mask=%u overhead=%lu PIT_HZ=1193182\n",mask,overhead);
    for(steps=0;steps<600U && play_samples<8U;++steps) {
        memset(&decoded,0,sizeof(decoded));
        active=game.ram[0x770U]==1U && game.ram[0x772U]==3U && game.ram[0x0eU]==8U;
        if(game.frame_number==130UL)decoded.buttons=MYSMB_IO_BUTTON_START;
        if(active) {
            decoded.buttons=MYSMB_IO_BUTTON_RIGHT|MYSMB_IO_BUTTON_B;
            if(play_frames>=4U && play_frames<7U)decoded.buttons|=MYSMB_IO_BUTTON_A;
        }
        if(!mysmb_game_startup_step(&game,1U))continue;
        mysmb_game_io_input(&decoded,&input);mysmb_game_tick(&game,&input,&frame);
        mysmb_game_io_audio(&game,&audio);(void)mysmb_dos16_devices_audio(&audio);
        if(game.frame_number>=90UL && game.frame_number<106UL)
            if(!draw(0U,game.frame_number>=98UL))return 3;
        if(active) {
            ++play_frames;
            if(play_frames<=16U && !draw(1U,play_frames>8U))return 4;
        }
    }
    fprintf(timing,"done title=%u gameplay=%u ticks=%lu submitted=32 bytes=1966080\n",title_samples,play_samples,game.frame_number);
    return title_samples==8U && play_samples==8U?0:5;
}
int main(void)
{
    unsigned i,value,result;
    char far *tail=(char far *)(((unsigned long)_psp<<16)|0x81UL);
    unsigned length=*(unsigned char far *)(((unsigned long)_psp<<16)|0x80UL);
    for(i=0;i<length;++i)if(tail[i]!=' ') {
        value=(unsigned)(tail[i]>='A'?tail[i]-'A'+10:tail[i]-'0');
        if(value>7U)return 10;mask=value;break;
    }
    if((mask&4U)&&!(mask&2U))return 11;
    pixels=fopen("FRAME.BIN","wb");timing=fopen("TIME.LOG","w");
    if(!pixels || !timing)return 12;
    if(!mysmb_dos16_devices_open())return 13;
    result=(unsigned)run();
    while(!mysmb_dos16_devices_close())mysmb_dos16_devices_wait();
    if(a)_ffree(a);if(b)_ffree(b);if(c)_ffree(c);
    if(fclose(pixels) || fclose(timing))return 14;
    return (int)result;
}
