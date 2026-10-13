#include "io/audio_renderer.h"
#include <string.h>

static const mygames_kvm_u16 length_periods[32]={
    10U,254U,20U,2U,40U,4U,80U,6U,160U,8U,60U,10U,14U,12U,26U,14U,
    12U,16U,24U,18U,48U,20U,96U,22U,192U,24U,72U,26U,16U,28U,32U,30U
};
static const mygames_kvm_u16 noise_periods[16]={
    4U,8U,16U,32U,64U,96U,128U,160U,202U,254U,380U,508U,762U,1016U,2034U,4068U
};
static const mygames_kvm_u8 pulse_duty[4]={1U,2U,4U,6U};

void mysmb_audio_renderer_initialize(
    struct mysmb_audio_renderer *renderer)
{
    if(!renderer)return;
    memset(renderer,0,sizeof(*renderer));
    renderer->noise_shift=1U;
}

static void renderer_clock_length(struct mysmb_audio_renderer *renderer)
{
    static const mygames_kvm_u8 control[4]={0U,4U,8U,12U};
    mygames_kvm_u8 channel;
    for(channel=0U;channel<4U;++channel)
        if((renderer->registers[control[channel]]&0x20U)==0U &&
            renderer->length[channel]!=0U)--renderer->length[channel];
}

static void renderer_clock_sweep(struct mysmb_audio_renderer *renderer,
    mygames_kvm_u8 channel)
{
    mygames_kvm_u16 control,timer,change,target;
    control=renderer->registers[channel*4U+1U];timer=renderer->pulse_timer[channel];
    change=(mygames_kvm_u16)(timer>>(control&7U));
    target=(control&8U)?(mygames_kvm_u16)(timer-change-(channel==0U?1U:0U)):
        (mygames_kvm_u16)(timer+change);
    if(renderer->sweep_divider[channel]==0U && (control&0x80U) && (control&7U) &&
        timer>=8U && target<=0x7ffU)renderer->pulse_timer[channel]=target;
    if(renderer->sweep_divider[channel]==0U || renderer->sweep_reload[channel]) {
        renderer->sweep_divider[channel]=(mygames_kvm_u16)((control>>4U)&7U);
        renderer->sweep_reload[channel]=0U;
    } else --renderer->sweep_divider[channel];
}

static void renderer_clock_quarter(struct mysmb_audio_renderer *renderer)
{
    static const mygames_kvm_u8 control[3]={0U,4U,12U};
    mygames_kvm_u8 channel,period;
    for(channel=0U;channel<3U;++channel) {
        period=(mygames_kvm_u8)(renderer->registers[control[channel]]&15U);
        if(renderer->envelope_start[channel]) {
            renderer->envelope_start[channel]=0U;renderer->envelope_level[channel]=15U;
            renderer->envelope_divider[channel]=period;
        } else if(renderer->envelope_divider[channel])--renderer->envelope_divider[channel];
        else {
            renderer->envelope_divider[channel]=period;
            if(renderer->envelope_level[channel])--renderer->envelope_level[channel];
            else if(renderer->registers[control[channel]]&0x20U)
                renderer->envelope_level[channel]=15U;
        }
    }
    if(renderer->triangle_reload)renderer->triangle_linear=renderer->registers[8U]&0x7fU;
    else if(renderer->triangle_linear)--renderer->triangle_linear;
    if((renderer->registers[8U]&0x80U)==0U)renderer->triangle_reload=0U;
}

static void renderer_apply_writes(struct mysmb_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame)
{
    mygames_kvm_u8 event,index,value,channel;
    for(event=0U;event<frame->write_count && event<MYSMB_IO_AUDIO_WRITE_CAPACITY;++event) {
        index=frame->writes[event].index;value=frame->writes[event].value;
        if(index>=MYSMB_IO_AUDIO_REGISTER_COUNT)continue;
        renderer->registers[index]=value;
        if(index<8U) {
            channel=(mygames_kvm_u8)(index>>2U);
            if((index&3U)==1U)renderer->sweep_reload[channel]=1U;
            else if((index&3U)==2U)renderer->pulse_timer[channel]=
                (mygames_kvm_u16)((renderer->pulse_timer[channel]&0x700U)|value);
            else if((index&3U)==3U)renderer->pulse_timer[channel]=
                (mygames_kvm_u16)((renderer->pulse_timer[channel]&0xffU)|((mygames_kvm_u16)(value&7U)<<8U));
        }
        if(index==21U) {
            renderer->enabled=(mygames_kvm_u8)(value&15U);
            for(channel=0U;channel<4U;++channel)
                if((renderer->enabled&(1U<<channel))==0U)renderer->length[channel]=0U;
        } else if(index==23U) {
            if(value&0x80U)renderer_clock_length(renderer);
        } else if(index==3U || index==7U || index==11U || index==15U) {
            channel=(mygames_kvm_u8)(index>>2U);
            if(renderer->enabled&(1U<<channel))renderer->length[channel]=length_periods[value>>3U];
            if(index==3U || index==7U) {
                renderer->pulse_phase[channel]=0UL;renderer->envelope_start[channel]=1U;
            } else if(index==11U)renderer->triangle_reload=1U;
            else if(renderer->enabled&8U)renderer->envelope_start[2U]=1U;
        }
    }
}

static mygames_kvm_u8 pulse_sample(struct mysmb_audio_renderer *renderer,
    mygames_kvm_u8 channel)
{
    mygames_kvm_u16 timer,volume;unsigned long period,position;
    timer=renderer->pulse_timer[channel];
    if((renderer->enabled&(1U<<channel))==0U || !renderer->length[channel] || timer<8U)return 0U;
    volume=(renderer->registers[channel*4U]&0x10U)?(renderer->registers[channel*4U]&15U):renderer->envelope_level[channel];
    if(!volume)return 0U;
    period=16UL*(timer+1U)*MYSMB_AUDIO_SAMPLE_RATE;
    renderer->pulse_phase[channel]+=1789773UL;
    while(renderer->pulse_phase[channel]>=period)renderer->pulse_phase[channel]-=period;
    position=renderer->pulse_phase[channel]/(period/8UL);
    return position<pulse_duty[renderer->registers[channel*4U]>>6U]?(mygames_kvm_u8)volume:0U;
}

static mygames_kvm_u8 triangle_sample(struct mysmb_audio_renderer *renderer)
{
    mygames_kvm_u16 timer;unsigned long period,position;
    if((renderer->enabled&4U)==0U || !renderer->length[2U] || !renderer->triangle_linear)return 0U;
    timer=(mygames_kvm_u16)(renderer->registers[10U]|((mygames_kvm_u16)(renderer->registers[11U]&7U)<<8U));
    if(timer<2U)return 0U;
    period=32UL*(timer+1U)*MYSMB_AUDIO_SAMPLE_RATE;
    renderer->triangle_phase+=1789773UL;
    while(renderer->triangle_phase>=period)renderer->triangle_phase-=period;
    position=renderer->triangle_phase/(period/32UL);
    return position<16UL?(mygames_kvm_u8)position:(mygames_kvm_u8)(31UL-position);
}

static mygames_kvm_u8 noise_sample(struct mysmb_audio_renderer *renderer)
{
    mygames_kvm_u16 volume,feedback,tap;unsigned long period;
    if((renderer->enabled&8U)==0U || !renderer->length[3U])return 0U;
    volume=(renderer->registers[12U]&0x10U)?(renderer->registers[12U]&15U):renderer->envelope_level[2U];
    if(!volume)return 0U;
    period=(unsigned long)(noise_periods[renderer->registers[14U]&15U]+1U)*MYSMB_AUDIO_SAMPLE_RATE;
    renderer->noise_phase+=1789773UL;tap=(renderer->registers[14U]&0x80U)?6U:1U;
    while(renderer->noise_phase>=period) {
        feedback=(mygames_kvm_u16)((renderer->noise_shift^(renderer->noise_shift>>tap))&1U);
        renderer->noise_shift=(mygames_kvm_u16)((renderer->noise_shift>>1U)|(feedback<<14U));
        renderer->noise_phase-=period;
    }
    return (renderer->noise_shift&1U)==0U?(mygames_kvm_u8)volume:0U;
}

static mygames_kvm_u8 renderer_sample(struct mysmb_audio_renderer *renderer)
{
    long input,output;
    input=(long)pulse_sample(renderer,0U)*20L+(long)pulse_sample(renderer,1U)*20L+
        (long)triangle_sample(renderer)*16L+(long)noise_sample(renderer)*4L;
    output=input-renderer->highpass_input+(renderer->highpass_output*255L)/256L;
    renderer->highpass_input=input;renderer->highpass_output=output;
    output/=6L;if(output>127L)output=127L;if(output< -128L)output= -128L;
    return (mygames_kvm_u8)(128L+output);
}

unsigned short mysmb_audio_renderer_render(
    struct mysmb_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame,mygames_kvm_u8 *samples,
    unsigned short capacity)
{
    unsigned short count,index,quarter,half;
    if(!renderer || !frame || !samples)return 0U;
    count=(unsigned short)((renderer->sample_remainder+MYSMB_AUDIO_SAMPLE_RATE)/60UL);
    if(count>capacity)return 0U;
    renderer->sample_remainder=(renderer->sample_remainder+MYSMB_AUDIO_SAMPLE_RATE)%60UL;
    renderer_apply_writes(renderer,frame);renderer->started=1U;
    quarter=(unsigned short)(count/4U);half=(unsigned short)(count/2U);
    for(index=0U;index<count;++index) {
        if(index==quarter || index==half || index==(unsigned short)(quarter+half)) {
            renderer_clock_quarter(renderer);
            if(index==half) {renderer_clock_length(renderer);renderer_clock_sweep(renderer,0U);renderer_clock_sweep(renderer,1U);}
        }
        samples[index]=renderer_sample(renderer);
    }
    if((renderer->registers[23U]&0x80U)==0U) {
        renderer_clock_quarter(renderer);renderer_clock_length(renderer);
        renderer_clock_sweep(renderer,0U);renderer_clock_sweep(renderer,1U);
    }
    return count;
}

void mysmb_audio_renderer_sync(struct mysmb_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame)
{
    struct mysmb_io_audio_frame restored;
    unsigned short i;
    mysmb_audio_renderer_initialize(renderer);
    memset(&restored,0,sizeof(restored));
    restored.writes[0].index=21U;restored.writes[0].value=frame->registers[21];
    for(i=0U;i<24U;++i){
        restored.writes[i+1U].index=(mygames_kvm_u8)i;
        restored.writes[i+1U].value=frame->registers[i];
    }
    restored.write_count=25U;renderer_apply_writes(renderer,&restored);
}
