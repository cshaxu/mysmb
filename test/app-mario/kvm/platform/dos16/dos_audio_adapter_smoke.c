/* App owns synthesis continuity and dropping a partially accepted device write. */
#include <string.h>
#include "platform/dos16/dos_audio.h"
#include "dos16/pcm.h"
static int ready,partial,calls;
static unsigned char actual[184];
static unsigned short length;
int mygames_dos16_pcm_dos_open(unsigned short rate){ready=rate==MYSMB_AUDIO_SAMPLE_RATE;return ready;}
int mygames_dos16_pcm_dos_close(void){ready=0;return 1;}
void mygames_dos16_pcm_dos_reset(void){}
int mygames_dos16_pcm_dos_prepared(void){return ready;}
mygames_kvm_u16 mygames_dos16_pcm_dos_submit(const mygames_kvm_u8 *samples,unsigned short count)
{++calls;memcpy(actual,samples,count);length=count;return partial?count/2:count;}
int main(void)
{
 struct mysmb_io_audio_frame frame;struct mysmb_audio_renderer reference;
 unsigned char expected[184];unsigned short n;int i;
 memset(&frame,0,sizeof(frame));frame.channel_enable=1;frame.registers[0]=0x9f;frame.registers[2]=253;
 frame.write_count=4;frame.writes[0].index=21;frame.writes[0].value=1;
 frame.writes[1].index=0;frame.writes[1].value=0x9f;frame.writes[2].index=2;frame.writes[2].value=253;
 frame.writes[3].index=3;frame.writes[3].value=0;
 if(mysmb_dos16_audio_dos_submit(&frame)!=MYSMB_IO_AUDIO_UNAVAILABLE || calls)return 1;
 if(!mysmb_dos16_audio_dos_open())return 2;mysmb_audio_renderer_initialize(&reference);
 for(i=0;i<12;++i){partial=i==3;n=mysmb_audio_renderer_render(&reference,&frame,expected,sizeof(expected));
  if(mysmb_dos16_audio_dos_submit(&frame)!=(partial?MYSMB_IO_AUDIO_UNAVAILABLE:MYSMB_IO_AUDIO_AVAILABLE))return 3;
  if(calls!=i+1 || length!=n || memcmp(actual,expected,n))return 4;frame.write_count=0;
 }
 mysmb_dos16_audio_dos_after_load();mysmb_audio_renderer_initialize(&reference);
 n=mysmb_audio_renderer_render(&reference,&frame,expected,sizeof(expected));
 if(mysmb_dos16_audio_dos_submit(&frame)!=MYSMB_IO_AUDIO_AVAILABLE || memcmp(actual,expected,n))return 5;
 return !mysmb_dos16_audio_dos_close();
}
