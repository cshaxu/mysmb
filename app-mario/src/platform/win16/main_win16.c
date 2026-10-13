#include <windows.h>
#include "win16/host.h"
#include "app/input_mapping.h"
#include "io/input_latch.h"
#include "io/control.h"
#include "core/game.h"
#include "core/area.h"
#include "ppu/frame.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

static struct mysmb_game game;
static struct mysmb_frame frame;
static struct mysmb_app_input_mapping mapping;
static struct mysmb_io_input mapped;
static struct mysmb_ppu_frame_workspace workspace;
static struct mysmb_ppu_frame_view view;
static struct mysmb_io_input_latch input_latch;
static struct mysmb_io_control control;
static unsigned char decoded[8192],rows[2048];

static void input(void *context,const struct mygames_kvm_input_event *event)
{
    (void)context;
    if(event->kind==MYGAMES_KVM_INPUT_FOCUS) {
        mysmb_app_input_mapping_initialize(&mapping);
        mapped.buttons=mapped.buttons2=mapped.requests=0U;
        mysmb_io_input_latch_clear(&input_latch);return;
    }
    mapped.requests=0U;
    mysmb_app_input_mapping_event(&mapping,event,&mapped);
    /* A down/up pair can be drained before a coarse USER timer arrives.
     * Retain the physical press for one controller sample, never a new
     * game action or a repeated synthetic press. */
    mysmb_io_input_latch_event(&input_latch,&mapped,(mygames_kvm_u8)(
        event->kind==MYGAMES_KVM_INPUT_KEY && event->down && !event->repeat));
    mapped.requests&=MYSMB_IO_REQUEST_EXIT;
    mysmb_io_control_input(&control,&mapped);
    /* Win16 is graphical-only in this admission. Tab is deliberately inert. */
}
static void tick(void *context)
{
    struct mysmb_input controller;
    struct mysmb_io_input sampled;
    (void)context;
    if(!mysmb_game_startup_step(&game,1U))return;
    mysmb_io_input_latch_sample(&input_latch,&sampled);
    controller.buttons=sampled.buttons;controller.buttons2=sampled.buttons2;
    mysmb_game_tick(&game,&controller,&frame);
}
static int graphics(void *context,struct mygames_kvm_video_band *band)
{
    int result;
    (void)context;
    if(band->first==0U)mysmb_ppu_frame_begin(&game.ppu,&workspace,&view);
    result=mysmb_ppu_frame_rows(&view,rows,sizeof(rows),band->first,band->rows);
    if(!result || band->first+band->rows==240U)mysmb_ppu_frame_end(&view);
    band->pixels=rows;return result;
}
static mygames_kvm_u8 exit_requested(void *context)
{(void)context;return control.exit_requested;}

int PASCAL WinMain(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show)
{
    struct mygames_win16_application application;
    HGLOBAL background;
    unsigned char FAR *background_bytes;
    int result;
    (void)command;
    mysmb_game_power_on(&game);mysmb_game_frame_initialize(&frame);
    mysmb_game_bind_area_source(&game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&game,mysmb_local_title_data,
        MYSMB_LOCAL_TITLE_DATA_SIZE,mysmb_local_title_icon_data,
        MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    mysmb_app_input_mapping_initialize(&mapping);
    mysmb_io_input_latch_clear(&input_latch);
    mysmb_io_control_initialize(&control);
    mysmb_ppu_frame_workspace_bind(&workspace,decoded);
    background=GlobalAlloc(GMEM_MOVEABLE,MYSMB_PPU_BACKGROUND_BYTES);
    background_bytes=background?(unsigned char FAR *)GlobalLock(background):0;
    if(background_bytes)mysmb_ppu_frame_background_bind(&workspace,
        background_bytes,MYSMB_PPU_BACKGROUND_BYTES);
    application.context=0;application.title="MySMB";
    application.available_views=MYGAMES_WIN16_VIEW_GRAPHICS;
    application.input=input;application.tick=tick;
    application.presentation=0;application.exit_requested=exit_requested;
    application.text=0;application.graphics=graphics;
    result=mygames_win16_run(instance,previous,show,&application);
    if(background_bytes)GlobalUnlock(background);
    if(background)GlobalFree(background);
    return result;
}
