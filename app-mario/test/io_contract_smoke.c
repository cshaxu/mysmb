#include "kvm/color.h"
#include "io/input.h"
#include "io/control.h"
#include "kvm/video.h"
#include "io/audio.h"
#include "core/game.h"
#include "io/palette_expand.h"
#include <string.h>

static mygames_kvm_u8 MYGAMES_KVM_FAR pixels[MYGAMES_KVM_VIDEO_PIXELS];
static struct mygames_kvm_text_frame text_frame;

static int palette_expansion_contract(void)
{
    struct mysmb_io_palette_pairs pairs,before;
    mygames_kvm_u8 packed[132],colors[16],out[292];
    mygames_kvm_u16 palette,phase,count,mode,i,offset;
    memset(&pairs,0,sizeof(pairs));
    for(palette=0U;palette<8U;++palette){
        for(i=0U;i<16U;++i)colors[i]=(mygames_kvm_u8)(palette*31U+i*19U+107U);
        for(phase=0U;phase<5U;++phase){
            for(i=0U;i<132U;++i)packed[i]=(mygames_kvm_u8)(i*17U+palette*7U);
            if(phase>=2U){memset(packed,0,sizeof(packed));
                if(phase==3U)packed[127U]=240U;
                if(phase==4U)packed[0U]=15U;}
            for(count=0U;count<=256U;count+=2U)for(mode=0U;mode<2U;++mode){
                offset=(mygames_kvm_u16)(16U+(phase&3U));
                memset(out,165,sizeof(out));
                if(!mysmb_io_palette_expand_portable(mode?&pairs:0,
                    packed,out+offset,count,colors))return 1;
                for(i=0U;i<count;++i)
                    if(out[offset+i]!=colors[(packed[i/2U]>>((i&1U)*4U))&15U])return 2;
                for(i=0U;i<offset;++i)if(out[i]!=165U)return 3;
                for(i=(mygames_kvm_u16)(offset+count);i<sizeof(out);++i)
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
    mygames_kvm_u8 input[132],out[292];mygames_kvm_u16 phase,count,i,offset;
    for(i=0U;i<256U;++i)
        if(mysmb_io_nibble_pairs[i*2U]!=(i&15U) ||
            mysmb_io_nibble_pairs[i*2U+1U]!=(i>>4U))return 7;
    for(phase=0U;phase<4U;++phase){
        for(i=0U;i<132U;++i)input[i]=(mygames_kvm_u8)(i*17U+phase);
        for(count=0U;count<=256U;count+=2U){
            memset(out,165,sizeof(out));offset=(mygames_kvm_u16)(16U+phase);
            if(!mysmb_io_nibble_expand(input+phase,out+offset,count))return 1;
            for(i=0U;i<count;++i)
                if(out[offset+i]!=((input[phase+i/2U]>>((i&1U)*4U))&15U))return 2;
            for(i=0U;i<offset;++i)if(out[i]!=165U)return 3;
            for(i=(mygames_kvm_u16)(offset+count);i<sizeof(out);++i)if(out[i]!=165U)return 4;
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
        rgb=mygames_kvm_color_rgb((mygames_kvm_u8)index);
        best=0xffffffffUL;choice=0U;
        for(i=0U;i<16U;++i) {
            text=mygames_kvm_color_text_rgb((mygames_kvm_u8)i);
            r=(long)((rgb>>16U)&255UL)-(long)((text>>16U)&255UL);
            g=(long)((rgb>>8U)&255UL)-(long)((text>>8U)&255UL);
            b=(long)(rgb&255UL)-(long)(text&255UL);
            distance=(unsigned long)(r*r+g*g+b*b);
            if(distance<best) {best=distance;choice=i;}
        }
        if(mygames_kvm_color_text16((mygames_kvm_u8)index)!=choice)return 1;
        text=mygames_kvm_color_text_rgb((mygames_kvm_u8)index);
        brightness=((text>>16U)&255UL)*299UL+((text>>8U)&255UL)*587UL+
            (text&255UL)*114UL;
        if(mygames_kvm_color_text_contrast((mygames_kvm_u8)index)!=
            (brightness>=128000UL?0U:15U))return 2;
        if(rgb!=mygames_kvm_color_rgb((mygames_kvm_u8)(index&63U)) ||
            text!=mygames_kvm_color_text_rgb((mygames_kvm_u8)(index&15U)))return 3;
    }
    return 0;
}

int main(void)
{
    struct mysmb_io_input input;
    struct mysmb_io_control control;
    struct mygames_kvm_video_frame video;
    struct mysmb_io_audio_frame audio;
    mygames_kvm_u16 offset;

    if(color_contract()!=0)return 10;
    if(palette_expansion_contract()!=0)return 11;
    if(nibble_contract()!=0)return 12;

    /* Check the actual game boundary, not only duplicated IO declarations. */
    if (MYGAMES_KVM_VIDEO_WIDTH != MYSMB_SCREEN_WIDTH ||
        MYGAMES_KVM_VIDEO_HEIGHT != MYSMB_SCREEN_HEIGHT ||
        MYSMB_IO_AUDIO_WRITE_CAPACITY != MYSMB_APU_WRITE_CAPACITY)
        return 1;
    if ((mygames_kvm_u8)MYSMB_IO_BUTTON_RIGHT != (mygames_kvm_u8)MYSMB_BUTTON_RIGHT ||
        (mygames_kvm_u8)MYSMB_IO_BUTTON_LEFT != (mygames_kvm_u8)MYSMB_BUTTON_LEFT ||
        (mygames_kvm_u8)MYSMB_IO_BUTTON_DOWN != (mygames_kvm_u8)MYSMB_BUTTON_DOWN ||
        (mygames_kvm_u8)MYSMB_IO_BUTTON_UP != (mygames_kvm_u8)MYSMB_BUTTON_UP ||
        (mygames_kvm_u8)MYSMB_IO_BUTTON_START != (mygames_kvm_u8)MYSMB_BUTTON_START ||
        (mygames_kvm_u8)MYSMB_IO_BUTTON_SELECT != (mygames_kvm_u8)MYSMB_BUTTON_SELECT ||
        (mygames_kvm_u8)MYSMB_IO_BUTTON_B != (mygames_kvm_u8)MYSMB_BUTTON_B ||
        (mygames_kvm_u8)MYSMB_IO_BUTTON_A != (mygames_kvm_u8)MYSMB_BUTTON_A)
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
    for (offset = 0U; offset < MYGAMES_KVM_VIDEO_PIXELS; ++offset)
        pixels[offset] = (mygames_kvm_u8)(offset & 0x3fU);
    video.pixels = pixels;
    if (video.pixels[0U] != 0U || video.pixels[61439U] != 0x3fU)
        return 4;
    text_frame.cells[3999U].character = ' ';
    text_frame.cells[3999U].foreground = 15U;
    text_frame.cells[3999U].background = 1U;
    if (sizeof(text_frame.cells) != 12000U || sizeof(input) != 3U) return 5;
    text_frame.rows=25U;
    if(MYGAMES_KVM_TEXT_FRAME_ROWS(&text_frame)!=25U ||
        MYGAMES_KVM_TEXT_FRAME_CELLS(&text_frame)!=2000U)return 5;
    text_frame.rows=50U;
    if(MYGAMES_KVM_TEXT_FRAME_CELLS(&text_frame)!=4000U)return 5;

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
