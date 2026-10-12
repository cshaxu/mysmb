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
    memset(&fake,0,sizeof(fake));
    if(!mysmb_dos16_audio_parse_blaster("A220 I5 D1 T6",&config) ||
        config.base_port!=0x220U || config.irq!=5U || config.dma_channel!=1U)return 1;
    if(!mysmb_dos16_audio_parse_blaster("t6 a240 d3 i10",&config) ||
        config.base_port!=0x240U || config.irq!=10U || config.dma_channel!=3U)return 2;
    if(mysmb_dos16_audio_parse_blaster("A220 I5",&config) ||
        mysmb_dos16_audio_parse_blaster("A220 I5 D1 D3",&config) ||
        mysmb_dos16_audio_parse_blaster("A100 I5 D1",&config))return 3;
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
    return fake.releases==2U?0:9;
}
