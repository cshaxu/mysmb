#include "io/color.h"
#include <windows.h>
#include "win16/host.h"
#include "platform/win16/scheduler.h"
#include "win16/audio.h"
#include "win16/file.h"
#include "app/game_io.h"
#include "app/game_snapshot.h"
#include "io/audio_renderer.h"
#include "io/snapshot_keys.h"
#include "io/file/snapshot_files.h"
#include "io/file/executable_path.h"
#include <string.h>
#include "app/input_mapping.h"
#include "io/input_latch.h"
#include "io/control.h"
#include "core/game.h"
#include "core/area.h"
#include "ppu/frame.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

static struct mysmb_win16_scheduler scheduler;
static int focused;
static struct mysmb_game game;
static struct mysmb_frame frame;
static struct mysmb_app_input_mapping mapping;
static struct mysmb_io_input mapped;
static struct mysmb_ppu_frame_workspace workspace;
static struct mysmb_ppu_frame_view view;
static struct mysmb_io_input_latch input_latch;
static struct mysmb_io_control control;
static unsigned char decoded[8192],rows[2048];
static struct mysmb_audio_renderer renderer;
static struct mysmb_io_audio_frame audio_frame;
static struct mysmb_snapshot_store *snapshot_store;
static struct mysmb_file_storage file_storage;
static struct mysmb_snapshot_keys snapshot_keys;
static unsigned char fingerprint[16],samples[184];


static void snapshot_request(mygames_kvm_u8 request)
{
    const struct mysmb_io_snapshot *loaded;
    if(request&MYSMB_IO_REQUEST_SAVE) {
        if(mysmb_game_snapshot_available(&game,&frame) &&
            mysmb_game_snapshot_capture(&game,&snapshot_store->staging,fingerprint)) {
            /* Match DOS's portable save contract: game/APU state is complete;
             * physical renderer phase is absent and rebuilt on restore. */
            memset(snapshot_store->staging.payload+MYSMB_SNAPSHOT_CORE_BYTES,0,
                MYSMB_SNAPSHOT_AUDIO_BYTES);
            (void)mysmb_snapshot_save(snapshot_store,&snapshot_store->staging);
        }
    } else if(request&MYSMB_IO_REQUEST_LOAD) {
        loaded=mysmb_snapshot_load(snapshot_store,fingerprint);
        if(loaded && mysmb_game_snapshot_restore(&game,loaded)) {
            mysmb_game_snapshot_resume_frame(&game,&frame);
            mysmb_game_io_audio(&game,&audio_frame);
            mysmb_audio_renderer_sync(&renderer,&audio_frame);
            mysmb_io_input_latch_clear(&input_latch);
            mysmb_app_input_mapping_initialize(&mapping);
            mapped.buttons=mapped.buttons2=mapped.requests=0U;
        }
    }
    /* File I/O is synchronous between logical ticks. Never catch up the
     * elapsed disk time or play stale pre-load buffers afterwards. */
    (void)mygames_win16_audio_reset();mysmb_win16_scheduler_reset(&scheduler,GetTickCount());
}


static void input(void *context,const struct mygames_kvm_input_event *event)
{
    mygames_kvm_u8 request;
    (void)context;
    if(event->kind==MYGAMES_KVM_INPUT_FOCUS) {
        focused=event->down!=0U;
        mysmb_win16_scheduler_reset(&scheduler,GetTickCount());
        mysmb_app_input_mapping_initialize(&mapping);
        mapped.buttons=mapped.buttons2=mapped.requests=0U;
        mysmb_io_input_latch_clear(&input_latch);
        mysmb_snapshot_keys_reset(&snapshot_keys);
        if(!event->down)(void)mygames_win16_audio_reset();
        return;
    }
    mapped.requests=0U;
    mysmb_app_input_mapping_event(&mapping,event,&mapped);
    /* A down/up pair can be drained before a coarse USER timer arrives.
     * Retain the physical press for one controller sample, never a new
     * game action or a repeated synthetic press. */
    mysmb_io_input_latch_event(&input_latch,&mapped,(mygames_kvm_u8)(
        event->kind==MYGAMES_KVM_INPUT_KEY && event->down && !event->repeat));
    request=mysmb_snapshot_keys_transition(&snapshot_keys,mapped.requests,
        event->down,1U);
    if(request)snapshot_request(request);
    mapped.requests&=MYSMB_IO_REQUEST_EXIT;
    mysmb_io_control_input(&control,&mapped);
    /* Win16 is graphical-only in this admission. Tab is deliberately inert. */
}
static void tick(void *context)
{
    struct mysmb_input controller;
    struct mysmb_io_input sampled;
    unsigned short count;
    (void)context;
    if(!mysmb_game_startup_step(&game,1U))return;
    mysmb_io_input_latch_sample(&input_latch,&sampled);
    controller.buttons=sampled.buttons;controller.buttons2=sampled.buttons2;
    mysmb_game_tick(&game,&controller,&frame);
    mysmb_game_io_audio(&game,&audio_frame);
    count=mysmb_audio_renderer_render(&renderer,&audio_frame,samples,sizeof(samples));
    if(count)(void)mygames_win16_audio_submit(samples,count);
}
static void update(void *context,unsigned long now,struct mygames_win16_update *result)
{
    unsigned short ticks,i;
    result->wake_ms=0U;result->dirty=0U;
    if(!focused)return;
    result->wake_ms=16U;
    ticks=mysmb_win16_scheduler_step(&scheduler,now);
    for(i=0U;i<ticks;++i)tick(context);
    /* Original app cadence: drain bounded debt and compose only current state. */
    result->dirty=(mygames_kvm_u8)(ticks && scheduler.credit<1000UL);
}
static int graphics(void *context,struct mygames_kvm_video_band *band)
{
    int result;
    (void)context;
    if(band->first==0U)mysmb_ppu_frame_begin(&game.ppu,&workspace,&view);
    result=mysmb_ppu_frame_rows(&view,rows,sizeof(rows),band->first,band->rows);
    if(!result || band->first+band->rows==240U)mysmb_ppu_frame_end(&view);
    band->pixels=rows;band->width=band->stride=256U;
    band->capacity=sizeof(rows);return result;
}
static mygames_kvm_u8 exit_requested(void *context)
{(void)context;return control.exit_requested;}

int PASCAL WinMain(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show)
{
    struct mygames_win16_application application;
    HGLOBAL background,snapshot_memory;
    struct mysmb_snapshot_files files;
    char path[260],directory[260];
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
    mysmb_snapshot_keys_reset(&snapshot_keys);
    mysmb_game_snapshot_fingerprint(&game,fingerprint);
    snapshot_memory=GlobalAlloc(GMEM_MOVEABLE,sizeof(struct mysmb_snapshot_store));
    snapshot_store=snapshot_memory?(struct mysmb_snapshot_store *)GlobalLock(snapshot_memory):0;
    if(!snapshot_store || !mygames_win16_executable_path(instance,path,sizeof(path)) ||
        !mysmb_file_executable_directory(path,directory,sizeof(directory)) ||
        !mysmb_file_storage_initialize(&file_storage,directory,mygames_win16_file_replace,&files) ||
        !mysmb_snapshot_store_initialize(snapshot_store,&files)) {
        if(snapshot_store)GlobalUnlock(snapshot_memory);
        if(snapshot_memory)GlobalFree(snapshot_memory);
        return 2;
    }
    mysmb_audio_renderer_initialize(&renderer);
    (void)mygames_win16_audio_open(MYSMB_AUDIO_SAMPLE_RATE);
    mysmb_ppu_frame_workspace_bind(&workspace,decoded);
    background=GlobalAlloc(GMEM_MOVEABLE,MYSMB_PPU_BACKGROUND_BYTES);
    background_bytes=background?(unsigned char FAR *)GlobalLock(background):0;
    if(background_bytes)mysmb_ppu_frame_background_bind(&workspace,
        background_bytes,MYSMB_PPU_BACKGROUND_BYTES);
    application.palette=mysmb_io_source_colors;application.palette_count=64U;
    application.width=256U;application.height=240U;
    application.context=0;application.title="MySMB";
    application.available_views=MYGAMES_WIN16_VIEW_GRAPHICS;
    application.input=input;application.update=update;
    application.presentation=0;application.exit_requested=exit_requested;
    application.text=0;application.graphics=graphics;
    result=mygames_win16_run(instance,previous,show,&application);
    mygames_win16_audio_close();
    GlobalUnlock(snapshot_memory);GlobalFree(snapshot_memory);snapshot_store=0;
    if(background_bytes)GlobalUnlock(background);
    if(background)GlobalFree(background);
    return result;
}
