#include "io/input.h"
#include "io/control.h"
#include "io/video.h"
#include "io/audio.h"
#include "core/game.h"

static mysmb_io_u8 MYSMB_IO_FAR pixels[MYSMB_IO_VIDEO_PIXELS];
static struct mysmb_io_text_frame text_frame;

int main(void)
{
    struct mysmb_io_input input;
    struct mysmb_io_control control;
    struct mysmb_io_video_frame video;
    struct mysmb_io_audio_frame audio;
    mysmb_io_u16 offset;

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
