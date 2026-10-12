#include <string.h>
#include "platform/win32/audio_snapshot.h"
static struct mysmb_win32_audio_renderer first,second,before;
static struct mysmb_io_audio_frame frame;
static unsigned char saved[MYSMB_SNAPSHOT_AUDIO_BYTES],again[MYSMB_SNAPSHOT_AUDIO_BYTES];
static short samples1[735],samples2[735];
static void write_register(unsigned int index,unsigned char value)
{
    frame.registers[index]=value;
    frame.writes[frame.write_count].index=(unsigned char)index;
    frame.writes[frame.write_count++].value=value;
}
int main(void)
{
    unsigned int i,j,nonzero;
    mysmb_win32_audio_renderer_initialize(&first);
    write_register(21U,15U);
    for(i=0U;i<4U;++i){
        write_register(i*4U,(unsigned char)(i==2U?0x9fU:0xbfU));
        write_register(i*4U+2U,(unsigned char)(i==3U?3U:123U+i));
        write_register(i*4U+3U,0x08U);
    }
    nonzero=0U;
    for(i=0U;i<64U;++i){
        mysmb_win32_audio_render(&first,&frame,samples1,735U,44100U);frame.write_count=0U;
        for(j=0U;j<735U;++j)if(samples1[j])++nonzero;
        if(!mysmb_win32_audio_capture(&first,saved) ||
            !mysmb_win32_audio_restore(&second,saved) ||
            !mysmb_win32_audio_capture(&second,again) || memcmp(saved,again,sizeof(saved)))return 1;
        /* No replay of the consumed register writes. Next-frame PCM must
         * match with active oscillators, envelopes and filter history. */
        mysmb_win32_audio_render(&first,&frame,samples1,735U,44100U);
        mysmb_win32_audio_render(&second,&frame,samples2,735U,44100U);
        if(memcmp(samples1,samples2,sizeof(samples1)))return 2;
    }
    if(!nonzero)return 3;
    before=second;saved[62]=saved[63]=0U;
    if(mysmb_win32_audio_restore(&second,saved) || memcmp(&second,&before,sizeof(second)))return 4;
    memset(saved,0,sizeof(saved));saved[123]=1U;
    if(mysmb_win32_audio_restore(&second,saved) || memcmp(&second,&before,sizeof(second)))return 5;
    saved[123]=0U;
    if(!mysmb_win32_audio_restore(&second,saved))return 6;
    return 0;
}
