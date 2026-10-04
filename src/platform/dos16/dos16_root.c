#include "platform/dos16/dos16_root.h"
#include <string.h>
#ifdef MYSMB_DOS16_TARGET
#include <malloc.h>
#endif
int mysmb_dos16_root_initialize(struct mysmb_dos16_root *root,
                                const struct mysmb_dos16_hooks *hooks)
{
#ifdef MYSMB_DOS16_TARGET
    mysmb_u8 __far *pixels;
#endif
    root->initialized=0U;
    root->snapshot_store=0;root->reset_output=0;root->reset_context=0;
    mysmb_snapshot_cache_initialize(&root->snapshot_cache);
    mysmb_io_control_initialize(&root->control);
    root->audio_available=MYSMB_IO_AUDIO_UNAVAILABLE;
    if (hooks==0 || hooks->read_input==0 || hooks->present_video==0) return 0;
#ifdef MYSMB_DOS16_TARGET
    pixels=(mysmb_u8 __far *)_fmalloc(MYSMB_IO_VIDEO_PIXELS);
    if (pixels==0) return 0;
    mysmb_ppu_frame_bind_pixels(&root->ppu_frame,pixels);
#endif
    root->hooks=*hooks;
    mysmb_game_power_on(&root->game);
    mysmb_game_frame_initialize(&root->game_frame);
    root->initialized=1U;
    return 1;
}
void mysmb_dos16_root_bind_snapshot(struct mysmb_dos16_root *root,
    struct mysmb_snapshot_store *store,void (*reset_output)(void *),void *context)
{
    root->snapshot_store=store;root->reset_output=reset_output;root->reset_context=context;
    mysmb_game_snapshot_fingerprint(&root->game,root->snapshot_fingerprint);
}
static void present_current(struct mysmb_dos16_root *root)
{
    struct mysmb_io_video_frame video;
    mysmb_ppu_frame_build(&root->game,&root->ppu_frame);
    mysmb_game_io_video(&root->ppu_frame,&video);
    root->hooks.present_video(root->hooks.context,&video);
}
static int snapshot_request(struct mysmb_dos16_root *root,mysmb_io_u8 requests)
{
    const struct mysmb_io_snapshot *candidate;
    if(!root->snapshot_store)return 0;
    if(requests&MYSMB_IO_REQUEST_LOAD){
        candidate=mysmb_snapshot_load(root->snapshot_store,root->snapshot_fingerprint);
        if(!candidate)return 0;
        if(!mysmb_game_snapshot_restore(&root->game,candidate)){
            root->snapshot_store->files.log(root->snapshot_store->files.context,
                "mysmb.log",MYSMB_SNAPSHOT_LOAD_ERROR);return 0;
        }
        mysmb_snapshot_cache_update(&root->snapshot_cache,candidate,1U);
        mysmb_game_frame_initialize(&root->game_frame);
        if(root->reset_output)root->reset_output(root->reset_context);
        present_current(root);return 1;
    }
    if(requests&MYSMB_IO_REQUEST_SAVE)
        (void)mysmb_snapshot_save(root->snapshot_store,
            mysmb_snapshot_cache_current(&root->snapshot_cache));
    return 0;
}
void mysmb_dos16_root_step(struct mysmb_dos16_root *root)
{
    struct mysmb_io_input decoded;
    struct mysmb_input input;
    if (root->initialized==0U || root->control.exit_requested!=0U) return;
    decoded.requests=0U;
    root->hooks.read_input(root->hooks.context,&decoded);
    mysmb_io_control_input(&root->control,&decoded);
    if (root->control.exit_requested!=0U) return;
    if(snapshot_request(root,decoded.requests))return;
    if (mysmb_game_startup_step(&root->game,1U)==0U) return;
    mysmb_game_io_input(&decoded,&input);
    mysmb_game_tick(&root->game,&input,&root->game_frame);
    present_current(root);
    mysmb_game_io_audio(&root->game,&root->audio_frame);
    if (root->hooks.submit_audio!=0)
        root->audio_available=root->hooks.submit_audio(root->hooks.context,&root->audio_frame);
    if(root->snapshot_store && mysmb_game_snapshot_running(&root->game,&root->game_frame) &&
        mysmb_game_snapshot_capture(&root->game,&root->snapshot,root->snapshot_fingerprint)){
        /* There is no DOS audio renderer. Never claim preserved PCM history. */
        memset(root->snapshot.payload+MYSMB_SNAPSHOT_CORE_BYTES,0,MYSMB_SNAPSHOT_AUDIO_BYTES);
        mysmb_snapshot_cache_update(&root->snapshot_cache,&root->snapshot,1U);
    }
}
void mysmb_dos16_root_shutdown(struct mysmb_dos16_root *root)
{
    if (root->initialized==0U) return;
#ifdef MYSMB_DOS16_TARGET
    _ffree(root->ppu_frame.pixels);
    root->ppu_frame.pixels=0;
#endif
    root->initialized=0U;
}
