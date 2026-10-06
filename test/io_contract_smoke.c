#include "io/color.h"
#include "io/input.h"
#include "io/control.h"
#include "io/video.h"
#include "io/audio.h"
#include "core/game.h"
#include "io/palette_expand.h"
#include <string.h>

static mysmb_io_u8 MYSMB_IO_FAR pixels[MYSMB_IO_VIDEO_PIXELS];
static struct mysmb_io_text_frame text_frame;

static int palette_expansion_contract(void)
{
    struct mysmb_io_palette_pairs pairs,before;
    mysmb_io_u8 packed[132],colors[16],out[292];
    mysmb_io_u16 palette,phase,count,mode,i,offset;
    memset(&pairs,0,sizeof(pairs));
    for(palette=0U;palette<8U;++palette){
        for(i=0U;i<16U;++i)colors[i]=(mysmb_io_u8)(palette*31U+i*19U+107U);
        for(phase=0U;phase<5U;++phase){
            for(i=0U;i<132U;++i)packed[i]=(mysmb_io_u8)(i*17U+palette*7U);
            if(phase>=2U){memset(packed,0,sizeof(packed));
                if(phase==3U)packed[127U]=240U;
                if(phase==4U)packed[0U]=15U;}
            for(count=0U;count<=256U;count+=2U)for(mode=0U;mode<2U;++mode){
                offset=(mysmb_io_u16)(16U+(phase&3U));
                memset(out,165,sizeof(out));
                if(!mysmb_io_palette_expand_portable(mode?&pairs:0,
                    packed,out+offset,count,colors))return 1;
                for(i=0U;i<count;++i)
                    if(out[offset+i]!=colors[(packed[i/2U]>>((i&1U)*4U))&15U])return 2;
                for(i=0U;i<offset;++i)if(out[i]!=165U)return 3;
                for(i=(mysmb_io_u16)(offset+count);i<sizeof(out);++i)
                    if(out[i]!=165U)return 4;
            }
        }
    }
    before=pairs;memset(out,165,sizeof(out));
    if(mysmb_io_palette_expand_portable(&pairs,packed,out,3U,colors) ||
        mysmb_io_palette_expand_portable(&pairs,packed,out,258U,colors) ||
        mysmb_io_palette_expand_portable(&pairs,0,out,2U,colors) ||
        mysmb_io_palette_expand_portable(&pairs,packed,0,2U,colors) ||
        mysmb_io_palette_expand_portable(&pairs,packed,out,2U,0))return 5;
    if(memcmp(&before,&pairs,sizeof(pairs)))return 6;
    for(i=0U;i<sizeof(out);++i)if(out[i]!=165U)return 7;
    return 0;
}

static int nibble_contract(void)
{
    mysmb_io_u8 input[132],out[292];mysmb_io_u16 phase,count,i,offset;
    for(phase=0U;phase<4U;++phase){
        for(i=0U;i<132U;++i)input[i]=(mysmb_io_u8)(i*17U+phase);
        for(count=0U;count<=256U;count+=2U){
            memset(out,165,sizeof(out));offset=(mysmb_io_u16)(16U+phase);
            if(!mysmb_io_nibble_expand(input+phase,out+offset,count))return 1;
            for(i=0U;i<count;++i)
                if(out[offset+i]!=((input[phase+i/2U]>>((i&1U)*4U))&15U))return 2;
            for(i=0U;i<offset;++i)if(out[i]!=165U)return 3;
            for(i=(mysmb_io_u16)(offset+count);i<sizeof(out);++i)if(out[i]!=165U)return 4;
        }
    }
    memset(out,165,sizeof(out));
    if(mysmb_io_nibble_expand(input,out,3U) || mysmb_io_nibble_expand(input,out,258U) ||
        mysmb_io_nibble_expand(0,out,2U) || mysmb_io_nibble_expand(input,0,2U))return 5;
    for(i=0U;i<sizeof(out);++i)if(out[i]!=165U)return 6;
    return 0;
}

/* Derive the contract from RGB values, independently of stored choices. */
static int color_contract(void)
{
    unsigned short index,i,choice;
    unsigned long rgb,text,best,distance,brightness;
    long r,g,b;
    for(index=0U;index<256U;++index) {
        rgb=mysmb_io_color_rgb((mysmb_io_u8)index);
        best=0xffffffffUL;choice=0U;
        for(i=0U;i<16U;++i) {
            text=mysmb_io_color_text_rgb((mysmb_io_u8)i);
            r=(long)((rgb>>16U)&255UL)-(long)((text>>16U)&255UL);
            g=(long)((rgb>>8U)&255UL)-(long)((text>>8U)&255UL);
            b=(long)(rgb&255UL)-(long)(text&255UL);
            distance=(unsigned long)(r*r+g*g+b*b);
            if(distance<best) {best=distance;choice=i;}
        }
        if(mysmb_io_color_text16((mysmb_io_u8)index)!=choice)return 1;
        text=mysmb_io_color_text_rgb((mysmb_io_u8)index);
        brightness=((text>>16U)&255UL)*299UL+((text>>8U)&255UL)*587UL+
            (text&255UL)*114UL;
        if(mysmb_io_color_text_contrast((mysmb_io_u8)index)!=
            (brightness>=128000UL?0U:15U))return 2;
        if(rgb!=mysmb_io_color_rgb((mysmb_io_u8)(index&63U)) ||
            text!=mysmb_io_color_text_rgb((mysmb_io_u8)(index&15U)))return 3;
    }
    return 0;
}

int main(void)
{
    struct mysmb_io_input input;
    struct mysmb_io_control control;
    struct mysmb_io_video_frame video;
    struct mysmb_io_audio_frame audio;
    mysmb_io_u16 offset;

    if(color_contract()!=0)return 10;
    if(palette_expansion_contract()!=0)return 11;
    if(nibble_contract()!=0)return 12;

    /* Check the actual game boundary, not only duplicated IO declarations. */
    if (MYSMB_IO_VIDEO_WIDTH != MYSMB_SCREEN_WIDTH ||
        MYSMB_IO_VIDEO_HEIGHT != MYSMB_SCREEN_HEIGHT ||
        MYSMB_IO_AUDIO_WRITE_CAPACITY != MYSMB_APU_WRITE_CAPACITY)
        return 1;
    if ((mysmb_io_u8)MYSMB_IO_BUTTON_RIGHT != (mysmb_io_u8)MYSMB_BUTTON_RIGHT ||
        (mysmb_io_u8)MYSMB_IO_BUTTON_LEFT != (mysmb_io_u8)MYSMB_BUTTON_LEFT ||
        (mysmb_io_u8)MYSMB_IO_BUTTON_DOWN != (mysmb_io_u8)MYSMB_BUTTON_DOWN ||
        (mysmb_io_u8)MYSMB_IO_BUTTON_UP != (mysmb_io_u8)MYSMB_BUTTON_UP ||
        (mysmb_io_u8)MYSMB_IO_BUTTON_START != (mysmb_io_u8)MYSMB_BUTTON_START ||
        (mysmb_io_u8)MYSMB_IO_BUTTON_SELECT != (mysmb_io_u8)MYSMB_BUTTON_SELECT ||
        (mysmb_io_u8)MYSMB_IO_BUTTON_B != (mysmb_io_u8)MYSMB_BUTTON_B ||
        (mysmb_io_u8)MYSMB_IO_BUTTON_A != (mysmb_io_u8)MYSMB_BUTTON_A)
        return 2;
    input.buttons = MYSMB_IO_BUTTON_LEFT | MYSMB_IO_BUTTON_B;
    input.buttons2 = MYSMB_IO_BUTTON_A | MYSMB_IO_BUTTON_SELECT;
    if (input.buttons != 0x42U || input.buttons2 != 0xa0U) return 3;
    mysmb_io_control_initialize(&control);
    if(mysmb_io_control_toggle(&control,1U,0U)!=0U ||
        mysmb_io_control_toggle(&control,1U,1U)!=MYSMB_IO_REQUEST_TOGGLE ||
        mysmb_io_control_toggle(&control,1U,1U)!=0U ||
        mysmb_io_control_toggle(&control,0U,0U)!=0U ||
        mysmb_io_control_toggle(&control,1U,1U)!=MYSMB_IO_REQUEST_TOGGLE)return 9;
    input.requests=0x80U;
    mysmb_io_control_input(&control,&input);
    if (control.exit_requested!=0U) return 7;
    input.requests=MYSMB_IO_REQUEST_EXIT;
    mysmb_io_control_input(&control,&input);
    input.requests=0U;
    mysmb_io_control_input(&control,&input);
    if (control.exit_requested==0U || input.buttons!=0x42U || input.buttons2!=0xa0U) return 8;

    /* Last row and byte offsets must remain representable by a 16-bit word. */
    for (offset = 0U; offset < MYSMB_IO_VIDEO_PIXELS; ++offset)
        pixels[offset] = (mysmb_io_u8)(offset & 0x3fU);
    video.pixels = pixels;
    if (video.pixels[0U] != 0U || video.pixels[61439U] != 0x3fU)
        return 4;
    text_frame.cells[3999U].character = ' ';
    text_frame.cells[3999U].foreground = 15U;
    text_frame.cells[3999U].background = 1U;
    if (sizeof(text_frame) != 12000U || sizeof(input) != 3U) return 5;

    /* Preserve repeated timer-high writes: each can retrigger a channel. */
    audio.write_count = 2U;
    audio.writes[0].index = 3U;
    audio.writes[0].value = 8U;
    audio.writes[1] = audio.writes[0];
    audio.registers[3] = 8U;
    if (audio.write_count != 2U || audio.writes[1].index != 3U ||
        audio.writes[0].value != audio.writes[1].value) return 6;
    return 0;
}
