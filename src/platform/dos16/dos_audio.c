#include "platform/dos16/dos_audio.h"
#include <string.h>

static int is_space(char value)
{ return value==' ' || value=='\t'; }

static int hex_digit(char value,unsigned long *digit)
{
    if(value>='0' && value<='9') {*digit=(unsigned long)(value-'0');return 1;}
    if(value>='a' && value<='f') {*digit=(unsigned long)(value-'a'+10);return 1;}
    if(value>='A' && value<='F') {*digit=(unsigned long)(value-'A'+10);return 1;}
    return 0;
}

static int decimal_digit(char value,unsigned long *digit)
{
    if(value<'0' || value>'9')return 0;
    *digit=(unsigned long)(value-'0');return 1;
}

static int parse_number(const char **cursor,unsigned long radix,unsigned long *value)
{
    unsigned long digit,total=0UL;
    unsigned char seen=0U;
    while((radix==16UL?hex_digit(**cursor,&digit):decimal_digit(**cursor,&digit))) {
        if(total>(0xffffUL-digit)/radix)return 0;
        total=total*radix+digit;++*cursor;seen=1U;
    }
    if(!seen)return 0;
    *value=total;return 1;
}

int mysmb_dos16_audio_parse_blaster(const char *value,
    struct mysmb_dos16_audio_config *config)
{
    unsigned long number;
    unsigned char base=0U,irq=0U,dma=0U;
    char key;
    if(!value || !config)return 0;
    while(*value) {
        while(is_space(*value))++value;
        if(!*value)break;
        key=*value++;
        if(key>='a' && key<='z')key=(char)(key-'a'+'A');
        if(key=='A') {
            if(base || !parse_number(&value,16UL,&number) || number<0x200UL ||
                number>0x3ffUL)return 0;
            config->base_port=(mysmb_io_u16)number;base=1U;
        }
        else if(key=='I') {
            if(irq || !parse_number(&value,10UL,&number) || number<2UL ||
                number>15UL)return 0;
            config->irq=(mysmb_io_u8)number;irq=1U;
        }
        else if(key=='D') {
            if(dma || !parse_number(&value,10UL,&number) || number>3UL)return 0;
            config->dma_channel=(mysmb_io_u8)number;dma=1U;
        }
        else {
            while(*value && !is_space(*value))++value;
        }
        if(*value && !is_space(*value))return 0;
    }
    return base && irq && dma;
}

void mysmb_dos16_audio_initialize(struct mysmb_dos16_audio_state *state)
{
    if(state)memset(state,0,sizeof(*state));
}

void mysmb_dos16_audio_close(struct mysmb_dos16_audio_state *state)
{
    if(!state)return;
    if(state->reserved && state->ops && state->ops->release)
        state->ops->release(state->context);
    mysmb_dos16_audio_initialize(state);
}

int mysmb_dos16_audio_open(struct mysmb_dos16_audio_state *state,
    const char *blaster,const struct mysmb_dos16_audio_ops *ops,void *context)
{
    struct mysmb_dos16_audio_config config;
    if(!state || !ops || !ops->probe || !ops->reserve || !ops->release)return 0;
    mysmb_dos16_audio_close(state);
    if(!mysmb_dos16_audio_parse_blaster(blaster,&config))return 0;
    if(!ops->probe(context,&config))return 0;
    if(!ops->reserve(context,&config))return 0;
    state->config=config;state->ops=ops;state->context=context;
    state->reserved=1U;state->ready=1U;
    return 1;
}

int mysmb_dos16_audio_reprobe(struct mysmb_dos16_audio_state *state)
{
    if(!state || !state->ready || !state->ops || !state->ops->probe ||
        !state->ops->probe(state->context,&state->config)) {
        mysmb_dos16_audio_close(state);return 0;
    }
    return 1;
}
