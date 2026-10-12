#include "platform/dos16/dos_audio.h"
#include <string.h>

struct fake { unsigned probes,reserves,releases; unsigned fail_probe,fail_reserve; };
static int probe(void *context,const struct mysmb_dos16_audio_config *config)
{struct fake *fake=(struct fake *)context;++fake->probes;return !fake->fail_probe && config->base_port==0x220U;}
static int reserve(void *context,const struct mysmb_dos16_audio_config *config)
{struct fake *fake=(struct fake *)context;(void)config;++fake->reserves;return !fake->fail_reserve;}
static void release(void *context)
{++((struct fake *)context)->releases;}
static const struct mysmb_dos16_audio_ops ops={probe,reserve,release};
int main(void)
{
    struct mysmb_dos16_audio_config config;
    struct mysmb_dos16_audio_state state;
    struct fake fake;
    struct mysmb_dos16_audio_renderer renderer;
    struct mysmb_io_audio_frame frame;
    mygames_kvm_u8 samples[MYSMB_DOS16_AUDIO_BLOCK_BYTES];
    unsigned short count;
    unsigned ticks,total=0U,non_silent=0U;
    memset(&fake,0,sizeof(fake));
    if(!mysmb_dos16_audio_parse_blaster("A220 I5 D1 T6",&config) ||
        config.base_port!=0x220U || config.irq!=5U || config.dma_channel!=1U)return 1;
    if(!mysmb_dos16_audio_parse_blaster("t6 a240 d3 i10",&config) ||
        config.base_port!=0x240U || config.irq!=10U || config.dma_channel!=3U)return 2;
    if(mysmb_dos16_audio_parse_blaster("A220 I5",&config) ||
        mysmb_dos16_audio_parse_blaster("A220 I5 D1 D3",&config) ||
        mysmb_dos16_audio_parse_blaster("A100 I5 D1",&config) ||
        mysmb_dos16_audio_parse_blaster("A220 I5 D2",&config))return 3;
    mysmb_dos16_audio_initialize(&state);
    if(!mysmb_dos16_audio_open(&state,"A220 I5 D1",&ops,&fake) || !state.ready ||
        !state.reserved || fake.probes!=1U || fake.reserves!=1U)return 4;
    if(!mysmb_dos16_audio_reprobe(&state) || fake.probes!=2U)return 5;
    fake.fail_probe=1U;
    if(mysmb_dos16_audio_reprobe(&state) || state.ready || state.reserved ||
        fake.releases!=1U)return 6;
    fake.fail_probe=0U;fake.fail_reserve=1U;
    if(mysmb_dos16_audio_open(&state,"A220 I5 D1",&ops,&fake) || state.ready ||
        fake.releases!=1U)return 7;
    fake.fail_reserve=0U;
    if(!mysmb_dos16_audio_open(&state,"A220 I5 D1",&ops,&fake))return 8;
    mysmb_dos16_audio_close(&state);mysmb_dos16_audio_close(&state);
    if(fake.releases!=2U)return 9;
    memset(&frame,0,sizeof(frame));
    frame.write_count=5U;
    frame.writes[0].index=21U;frame.writes[0].value=1U;
    frame.writes[1].index=0U;frame.writes[1].value=0xdfU;
    frame.writes[2].index=2U;frame.writes[2].value=0x40U;
    frame.writes[3].index=2U;frame.writes[3].value=0x41U;
    frame.writes[4].index=3U;frame.writes[4].value=0xf8U;
    mysmb_dos16_audio_renderer_initialize(&renderer);
    if(mysmb_dos16_audio_renderer_render(&renderer,&frame,samples,1U)!=0U ||
        renderer.sample_remainder!=0UL)return 10;
    for(ticks=0U;ticks<60U;++ticks) {
        count=mysmb_dos16_audio_renderer_render(&renderer,&frame,samples,sizeof(samples));
        if(count<183U || count>184U)return 11;
        total+=count;
        if(samples[0]!=128U || samples[count-1U]!=128U)++non_silent;
        frame.write_count=0U;
    }
    if(total!=MYSMB_DOS16_AUDIO_SAMPLE_RATE || renderer.registers[2U]!=0x41U ||
        renderer.registers[3U]!=0xf8U || !non_silent)return 12;
    return 0;
}
