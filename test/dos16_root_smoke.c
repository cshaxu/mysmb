#include "platform/dos16/dos16_root.h"
#include "platform/dos16/keyboard.h"
#include <string.h>
struct host { unsigned calls; unsigned audio_calls; mysmb_io_u8 requests; };
static unsigned mode_allowed,text_calls;
static int mode(void *context,mysmb_io_u8 text)
{(void)context;(void)text;return mode_allowed;}
static void text_present(void *context,const struct mysmb_io_text_frame *frame)
{(void)context;(void)frame;++text_calls;}
static void read_input(void *context, struct mysmb_io_input *input)
{ input->buttons=0U; input->buttons2=0U; input->requests=((struct host *)context)->requests; }
static void present(void *context, const struct mysmb_io_video_frame *frame)
{ if (frame->pixels!=0) ++((struct host *)context)->calls; }
static mysmb_io_u8 audio(void *context, const struct mysmb_io_audio_frame *frame)
{
    if (frame->write_count<=MYSMB_IO_AUDIO_WRITE_CAPACITY)
        ++((struct host *)context)->audio_calls;
    return MYSMB_IO_AUDIO_UNAVAILABLE;
}
static int failed_text_recovery(void)
{
    static struct mysmb_dos16_root borrowed,baseline;
    struct mysmb_dos16_hooks hooks;
    struct host actual,expected;
    unsigned i;
    memset(&actual,0,sizeof(actual));memset(&expected,0,sizeof(expected));
    hooks.read_input=read_input;hooks.present_video=present;hooks.submit_audio=audio;
    hooks.context=&actual;
    if(!mysmb_dos16_root_initialize(&borrowed,&hooks))return 20;
    hooks.context=&expected;
    if(!mysmb_dos16_root_initialize(&baseline,&hooks))return 21;
    mysmb_dos16_root_bind_text(&borrowed,
        (struct mysmb_text_scene_workspace *)borrowed.ppu_frame.pixels,
        (struct mysmb_io_text_frame *)(borrowed.ppu_frame.pixels+
            sizeof(struct mysmb_text_scene_workspace)),mode,text_present);
    for(i=0U;i<3U;++i){
        mysmb_dos16_root_step(&borrowed);mysmb_dos16_root_step(&baseline);
    }
    /* Missing resources force text construction failure after an aliased view.
     * A failed mode reset submits nothing;recovery rebuilds every pixel. */
    memset(borrowed.ppu_frame.pixels,0xa5,sizeof(borrowed.ppu_frame.pixels));
    borrowed.text_mode=1U;mode_allowed=0U;text_calls=0U;
    mysmb_dos16_root_step(&borrowed);mysmb_dos16_root_step(&baseline);
    if(borrowed.text_mode!=1U || actual.calls!=1U || text_calls)return 22;
    mode_allowed=1U;
    mysmb_dos16_root_step(&borrowed);mysmb_dos16_root_step(&baseline);
    if(borrowed.text_mode!=0U || actual.calls!=2U || text_calls ||
        memcmp(borrowed.ppu_frame.pixels,baseline.ppu_frame.pixels,
            sizeof(baseline.ppu_frame.pixels)))return 23;
    if(memcmp(borrowed.game.ram,baseline.game.ram,sizeof(baseline.game.ram)) ||
        borrowed.game.frame_number!=baseline.game.frame_number ||
        actual.audio_calls!=expected.audio_calls)return 24;
    mysmb_dos16_root_shutdown(&borrowed);mysmb_dos16_root_shutdown(&baseline);
    return 0;
}

static struct mysmb_dos16_root row_root;
static struct mysmb_ppu_frame row_reference;
static unsigned row_calls,row_failure;
static int rows_present(void *context,const struct mysmb_io_video_source *source)
{
    struct mysmb_io_video_band band;
    unsigned short first,rows;
    unsigned char *pixels=row_root.ppu_frame.pixels;
    (void)context;
    mysmb_ppu_frame_build(&row_root.game.ppu,&row_reference);
    pixels[2560]=0xa5U;
    for(first=0U;first<240U;first=(unsigned short)(first+rows)) {
        rows=(unsigned short)(240U-first);if(rows>10U)rows=10U;
        if(!source->read_rows(source->context,first,rows,&band) || band.first!=first ||
            band.rows!=rows || memcmp(band.pixels,row_reference.pixels+first*256U,
                rows*256U) || pixels[2560]!=0xa5U)return 0;
    }
    /* The callback must reject oversized requests before changing its view. */
    if(source->read_rows(source->context,0U,11U,&band) ||
        source->read_rows(source->context,239U,2U,&band))return 0;
    ++row_calls;return !row_failure;
}
static int row_lifetime(void)
{
    struct mysmb_dos16_hooks hooks;
    struct host host;
    memset(&host,0,sizeof(host));row_calls=0U;row_failure=0U;
    hooks.context=&host;hooks.read_input=read_input;
    hooks.present_video=0;hooks.submit_audio=audio;
    if(mysmb_dos16_root_initialize_rows(&row_root,&hooks,255U,rows_present) ||
        mysmb_dos16_root_initialize_rows(&row_root,&hooks,2560U,0))return 30;
    if(!mysmb_dos16_root_initialize_rows(&row_root,&hooks,2560U,rows_present))return 31;
    mysmb_dos16_root_step(&row_root);mysmb_dos16_root_step(&row_root);
    mysmb_dos16_root_step(&row_root);
    if(row_calls!=1U || row_root.control.exit_requested || host.audio_calls!=1U)return 32;
    row_failure=1U;mysmb_dos16_root_step(&row_root);
    if(row_calls!=2U || !row_root.control.exit_requested)return 33;
    mysmb_dos16_root_step(&row_root);if(row_calls!=2U)return 34;
    mysmb_dos16_root_shutdown(&row_root);mysmb_dos16_root_shutdown(&row_root);
    return 0;
}
int main(void)
{
    static struct mysmb_dos16_root root;
    struct mysmb_dos16_hooks hooks;
    struct mysmb_dos16_keyboard keyboard;
    struct mysmb_io_input input;
    struct host host;
    mysmb_dos16_keyboard_initialize(&keyboard);
    mysmb_dos16_keyboard_scan(&keyboard,0x20U);
    mysmb_dos16_keyboard_scan(&keyboard,0x24U);
    mysmb_dos16_keyboard_scan(&keyboard,0x25U);
    mysmb_dos16_keyboard_scan(&keyboard,0x2aU);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.buttons!=(MYSMB_IO_BUTTON_RIGHT|MYSMB_IO_BUTTON_B|MYSMB_IO_BUTTON_A|MYSMB_IO_BUTTON_SELECT)) return 1;
    mysmb_dos16_keyboard_scan(&keyboard,0xa0U);
    mysmb_dos16_keyboard_scan(&keyboard,0xa4U);
    mysmb_dos16_keyboard_scan(&keyboard,0xa5U);
    mysmb_dos16_keyboard_scan(&keyboard,0xaaU);
    mysmb_dos16_keyboard_scan(&keyboard,0x36U);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.buttons!=MYSMB_IO_BUTTON_SELECT) return 2;
    mysmb_dos16_keyboard_scan(&keyboard,0xb6U);
    mysmb_dos16_keyboard_scan(&keyboard,0xe0U);
    mysmb_dos16_keyboard_scan(&keyboard,0x4bU);
    mysmb_dos16_keyboard_scan(&keyboard,0xe0U);
    mysmb_dos16_keyboard_scan(&keyboard,0x2aU);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.buttons!=MYSMB_IO_BUTTON_LEFT) return 3;
    mysmb_dos16_keyboard_scan(&keyboard,0xe0U);
    mysmb_dos16_keyboard_scan(&keyboard,0xcbU);
    mysmb_dos16_keyboard_scan(&keyboard,0xe1U);
    mysmb_dos16_keyboard_scan(&keyboard,0x1dU);
    mysmb_dos16_keyboard_scan(&keyboard,0x45U);
    mysmb_dos16_keyboard_scan(&keyboard,0xe1U);
    mysmb_dos16_keyboard_scan(&keyboard,0x9dU);
    mysmb_dos16_keyboard_scan(&keyboard,0xc5U);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.buttons!=0U || input.buttons2!=0U) return 4;
    mysmb_dos16_keyboard_scan(&keyboard,1U);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.requests!=MYSMB_IO_REQUEST_EXIT || input.buttons!=0U) return 10;
    mysmb_dos16_keyboard_scan(&keyboard,0x81U);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.requests!=0U) return 11;
    mysmb_dos16_keyboard_scan(&keyboard,1U);
    mysmb_dos16_keyboard_scan(&keyboard,0x81U);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.requests!=MYSMB_IO_REQUEST_EXIT) return 13;
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.requests!=0U) return 14;
    mysmb_dos16_keyboard_scan(&keyboard,0x0fU);
    mysmb_dos16_keyboard_scan(&keyboard,0x0fU);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if(input.requests!=MYSMB_IO_REQUEST_TOGGLE || input.buttons)return 15;
    mysmb_dos16_keyboard_after_load(&keyboard);
    mysmb_dos16_keyboard_scan(&keyboard,0x0fU);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if(input.requests)return 16;
    mysmb_dos16_keyboard_scan(&keyboard,0x8fU);
    mysmb_dos16_keyboard_scan(&keyboard,0x0fU);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if(input.requests!=MYSMB_IO_REQUEST_TOGGLE)return 17;
    host.calls=0U; host.audio_calls=0U;host.requests=0U;
    hooks.context=&host; hooks.read_input=read_input; hooks.present_video=present;
    hooks.submit_audio=audio;
    if (mysmb_dos16_root_initialize(&root,0)!=0) return 5;
    if (!mysmb_dos16_root_initialize(&root,&hooks)) return 6;
    /* Startup descriptors may expire before the first frame. */
    memset(&hooks,0,sizeof(hooks));
    if(root.text_mode!=0U)return 18;
    mysmb_dos16_root_step(&root); mysmb_dos16_root_step(&root);
    if (root.game.frame_number!=0UL || host.calls!=0U) return 7;
    mysmb_dos16_root_step(&root);
    if (root.game.frame_number!=1UL || host.calls!=1U || host.audio_calls!=1U ||
        root.audio_available!=MYSMB_IO_AUDIO_UNAVAILABLE) return 8;
    host.requests=MYSMB_IO_REQUEST_EXIT;
    mysmb_dos16_root_step(&root);
    host.requests=0U;mysmb_dos16_root_step(&root);
    if (root.control.exit_requested==0U || root.game.frame_number!=1UL ||
        host.calls!=1U || host.audio_calls!=1U) return 12;
    mysmb_dos16_root_shutdown(&root); mysmb_dos16_root_shutdown(&root);
    mysmb_dos16_root_step(&root);
    if(host.calls!=1U || host.audio_calls!=1U)return 9;
    if(failed_text_recovery())return 25;
    return row_lifetime();
}
