#include "platform/win32/audio_snapshot.h"
#include "platform/win32/audio_snapshot_real.h"
#include <string.h>

int mysmb_win32_audio_capture(const struct mysmb_win32_audio_renderer *r,
    mysmb_io_u8 *bytes)
{
    mysmb_io_u8 candidate[MYSMB_SNAPSHOT_AUDIO_BYTES];
    mysmb_io_u8 *out;
    unsigned int i;
    memset(candidate,0,sizeof(candidate));out=candidate;
    *out++=1U;memcpy(out,r->registers,24U);out+=24;*out++=r->enabled;
#define WORD_ARRAY(field,count) for(i=0U;i<count;++i){mysmb_snapshot_put16(out,(mysmb_io_u16)r->field[i]);out+=2;}
#define BYTE_ARRAY(field,count) for(i=0U;i<count;++i)*out++=r->field[i]
    WORD_ARRAY(length,4U);WORD_ARRAY(envelope_level,3U);WORD_ARRAY(envelope_divider,3U);
    WORD_ARRAY(pulse_timer,2U);WORD_ARRAY(sweep_divider,2U);
    mysmb_snapshot_put16(out,(mysmb_io_u16)r->triangle_linear);out+=2;
    BYTE_ARRAY(envelope_start,3U);BYTE_ARRAY(sweep_reload,2U);*out++=r->triangle_reload;
    mysmb_snapshot_put16(out,r->noise_shift);out+=2;
#undef WORD_ARRAY
#undef BYTE_ARRAY
#define REAL(value) if(!mysmb_snapshot_put_real(out,value))return 0;out+=10
    REAL(r->pulse_phase[0]);REAL(r->pulse_phase[1]);REAL(r->triangle_phase);
    REAL(r->noise_phase);REAL(r->highpass_input);REAL(r->highpass_output);
#undef REAL
    if (out!=candidate+MYSMB_SNAPSHOT_AUDIO_BYTES) return 0;
    memcpy(bytes,candidate,sizeof(candidate));return 1;
}
int mysmb_win32_audio_restore(struct mysmb_win32_audio_renderer *renderer,
    const mysmb_io_u8 *bytes)
{
    struct mysmb_win32_audio_renderer candidate;
    const mysmb_io_u8 *in;
    unsigned int i;
    if (bytes[0]>1U) return 0;
    if (bytes[0]==0U) {
        for(i=1U;i<MYSMB_SNAPSHOT_AUDIO_BYTES;++i)if(bytes[i]!=0U)return 0;
        mysmb_win32_audio_renderer_initialize(renderer);return 1;
    }
    memset(&candidate,0,sizeof(candidate));in=bytes+1;
    memcpy(candidate.registers,in,24U);in+=24;candidate.enabled=*in++;
#define WORD_ARRAY(field,count) for(i=0U;i<count;++i){candidate.field[i]=mysmb_snapshot_get16(in);in+=2;}
#define BYTE_ARRAY(field,count) for(i=0U;i<count;++i)candidate.field[i]=*in++
    WORD_ARRAY(length,4U);WORD_ARRAY(envelope_level,3U);WORD_ARRAY(envelope_divider,3U);
    WORD_ARRAY(pulse_timer,2U);WORD_ARRAY(sweep_divider,2U);
    candidate.triangle_linear=mysmb_snapshot_get16(in);in+=2;
    BYTE_ARRAY(envelope_start,3U);BYTE_ARRAY(sweep_reload,2U);candidate.triangle_reload=*in++;
    candidate.noise_shift=mysmb_snapshot_get16(in);in+=2;
#undef WORD_ARRAY
#undef BYTE_ARRAY
#define REAL(value) if(!mysmb_snapshot_get_real(in,&value))return 0;in+=10
    REAL(candidate.pulse_phase[0]);REAL(candidate.pulse_phase[1]);
    REAL(candidate.triangle_phase);REAL(candidate.noise_phase);
    REAL(candidate.highpass_input);REAL(candidate.highpass_output);
#undef REAL
    for(i=0U;i<2U;++i)if(candidate.pulse_phase[i]<0.0 || candidate.pulse_phase[i]>=1.0 ||
        candidate.pulse_timer[i]>0x7ffU || candidate.sweep_divider[i]>7U ||
        candidate.sweep_reload[i]>1U)return 0;
    for(i=0U;i<3U;++i)if(candidate.envelope_level[i]>15U ||
        candidate.envelope_divider[i]>15U || candidate.envelope_start[i]>1U)return 0;
    for(i=0U;i<4U;++i)if(candidate.length[i]>254U)return 0;
    if(candidate.triangle_linear>127U || candidate.triangle_reload>1U ||
        candidate.noise_shift==0U || candidate.noise_shift>0x7fffU ||
        candidate.triangle_phase<0.0 || candidate.triangle_phase>=1.0 ||
        candidate.noise_phase<0.0 || candidate.noise_phase>=1.0)return 0;
    *renderer=candidate;return 1;
}
