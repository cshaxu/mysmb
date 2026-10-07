#include "platform/dos16/dos16_root.h"
#include <string.h>
#ifdef MYSMB_DOS16_TARGET
#include <malloc.h>
#include "platform/dos16/palette_expand.h"
#include "platform/dos16/nibble_expand.h"
#endif
static int initialize(struct mysmb_dos16_root *root,
    const struct mysmb_dos16_hooks *hooks,mysmb_io_u16 storage_bytes,
    int (*present_rows)(void *,const struct mysmb_io_video_source *))
{
#ifdef MYSMB_DOS16_TARGET
    mysmb_u8 __far *pixels;
#endif
    mysmb_ppu_frame_workspace_bind(&root->ppu_workspace,0);
    mysmb_ppu_frame_end(&root->ppu_view);
    root->ppu_cache_attempted=0U;root->ppu_cache_near=0U;
    root->ppu_pairs=0;
    root->initialized=0U;
    root->present_rows=0;root->video_storage_bytes=storage_bytes;
    root->present_palette_rows=0;
    root->snapshot_store=0;root->reset_output=0;root->reset_context=0;root->resume_clock=0;
    root->text_workspace=0;root->text_frame=0;root->set_mode=0;
    root->present_text=0;root->text_mode=0U;
    mysmb_io_control_initialize(&root->control);
    root->audio_available=MYSMB_IO_AUDIO_UNAVAILABLE;
    if (hooks==0 || hooks->read_input==0 ||
        (present_rows==0 && hooks->present_video==0) || storage_bytes<256U)return 0;
#ifdef MYSMB_DOS16_TARGET
    pixels=(mysmb_u8 __far *)_fmalloc(storage_bytes);
    if (pixels==0) return 0;
    mysmb_ppu_frame_bind_pixels(&root->ppu_frame,pixels);

#endif
    root->hooks=*hooks;root->present_rows=present_rows;
    mysmb_game_power_on(&root->game);
    mysmb_game_frame_initialize(&root->game_frame);
    root->initialized=1U;
    return 1;
}
int mysmb_dos16_root_initialize(struct mysmb_dos16_root *root,
    const struct mysmb_dos16_hooks *hooks)
{
    return initialize(root,hooks,MYSMB_IO_VIDEO_PIXELS,0);
}
int mysmb_dos16_root_initialize_rows(struct mysmb_dos16_root *root,
    const struct mysmb_dos16_hooks *hooks,mysmb_io_u16 storage_bytes,
    int (*present_rows)(void *,const struct mysmb_io_video_source *))
{
    if(present_rows==0)storage_bytes=0U;
    return initialize(root,hooks,storage_bytes,present_rows);
}
static int read_rows(void *context,mysmb_io_u16 first,mysmb_io_u16 rows,
    struct mysmb_io_video_band *band)
{
    struct mysmb_dos16_root *root=(struct mysmb_dos16_root *)context;
    if(band==0)return 0;
    if(!(root->present_palette_rows?
        mysmb_ppu_frame_slot_rows(&root->ppu_view,root->ppu_frame.pixels,
            root->video_storage_bytes,first,rows):
        mysmb_ppu_frame_rows(&root->ppu_view,root->ppu_frame.pixels,
            root->video_storage_bytes,first,rows)))return 0;
    band->pixels=root->ppu_frame.pixels;band->first=first;band->rows=rows;
    return 1;
}

static int present_palette(void *context,const struct mysmb_io_video_source *source)
{
    struct mysmb_dos16_root *root=(struct mysmb_dos16_root *)source->context;
    struct mysmb_io_palette_video_source view;
    (void)context;view.rows=*source;view.master_colors=root->video_palette;
    return root->present_palette_rows(root->hooks.context,&view);
}
int mysmb_dos16_root_initialize_palette_rows(struct mysmb_dos16_root *root,
    const struct mysmb_dos16_hooks *hooks,mysmb_io_u16 storage_bytes,
    int (*present)(void *,const struct mysmb_io_palette_video_source *))
{
    if(!present || !initialize(root,hooks,storage_bytes,present_palette))return 0;
    root->present_palette_rows=present;return 1;
}

void mysmb_dos16_root_bind_text(struct mysmb_dos16_root *root,
    struct mysmb_text_scene_workspace MYSMB_IO_FAR *workspace,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    int (*set_mode)(void *,mysmb_io_u8),
    void (*present_text)(void *,const struct mysmb_io_text_frame MYSMB_IO_FAR *))
{
    if(!workspace || !frame || !set_mode || !present_text)return;
    root->text_workspace=workspace;root->text_frame=frame;
    root->set_mode=set_mode;root->present_text=present_text;
    mysmb_text_observer_enable(&root->game,1U);
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
    struct mysmb_io_video_source source;
    struct mysmb_io_input failure;
#ifdef MYSMB_DOS16_TARGET
    mysmb_u8 __near *near_cache;
    mysmb_u8 __far *decoded;
    mysmb_u8 __far *background;
    struct mysmb_io_palette_pairs __near *pairs;
#endif
    if(root->text_mode) {
        if(mysmb_text_scene_build_profile(&root->game,root->text_workspace,root->text_frame,25U)) {
            root->present_text(root->hooks.context,root->text_frame);return;
        }
        if(!root->set_mode(root->hooks.context,0U))return;
        root->text_mode=0U;
    }
#ifdef MYSMB_DOS16_TARGET
    /* Allocate only after normal root/text/snapshot initialization. This
     * optional buffer must never displace required product storage. */
    if(!root->ppu_cache_attempted) {
        root->ppu_cache_attempted=1U;
        /* Preserve the compact background tier before spending memory on CHR.
         * The shared compositor supports packed backgrounds with raw CHR. */
        background=(mysmb_u8 __far *)_fmalloc(MYSMB_PPU_BACKGROUND_BYTES);
        /* Reuse the primary-block reserve before requesting another DOS block.
         * Preserve allocation provenance for the matching shutdown operation. */
        near_cache=(mysmb_u8 __near *)_nmalloc(MYSMB_PPU_CHR_DECODED_BYTES);
        root->ppu_cache_near=(mysmb_io_u8)(near_cache!=0);
        decoded=near_cache?(mysmb_u8 __far *)near_cache:
            (mysmb_u8 __far *)_fmalloc(MYSMB_PPU_CHR_DECODED_BYTES);
        mysmb_ppu_frame_workspace_bind(&root->ppu_workspace,decoded);
        mysmb_ppu_frame_background_bind(&root->ppu_workspace,
            background,
            MYSMB_PPU_BACKGROUND_BYTES);
        /* One additional optional plane:failure retains packed storage.
         * Mandatory text/snapshot/device allocations have already succeeded. */
        if(root->ppu_workspace.bg)
            mysmb_ppu_frame_background_byte_bind(&root->ppu_workspace,
                root->ppu_workspace.bg,MYSMB_PPU_BACKGROUND_BYTES,
                (mysmb_u8 __far *)_fmalloc(MYSMB_PPU_BACKGROUND_SECOND_BYTES),
                MYSMB_PPU_BACKGROUND_SECOND_BYTES);
        if(root->present_palette_rows){
            mysmb_ppu_frame_nibble_bind(&root->ppu_workspace,mysmb_dos16_nibble_expand);
        }else if(root->ppu_workspace.bg) {
            pairs=(struct mysmb_io_palette_pairs __near *)_nmalloc(sizeof(*pairs));
            if(pairs) {
                pairs->valid=0U;root->ppu_pairs=pairs;
                mysmb_ppu_frame_expansion_bind(&root->ppu_workspace,
                    mysmb_dos16_palette_expand,pairs);
            }
        }
    }
#endif
    if(root->present_rows) {
        if(root->present_palette_rows)
            mysmb_ppu_frame_palette(&root->game.ppu,root->video_palette);
        mysmb_ppu_frame_begin(&root->game.ppu,&root->ppu_workspace,&root->ppu_view);
        source.context=root;source.read_rows=read_rows;
        if(!root->present_rows(root->hooks.context,&source)) {
            failure.buttons=0U;failure.buttons2=0U;failure.requests=MYSMB_IO_REQUEST_EXIT;
            mysmb_io_control_input(&root->control,&failure);
        }
        mysmb_ppu_frame_end(&root->ppu_view);
        return;
    }
    mysmb_ppu_frame_build_cached(&root->game.ppu,&root->ppu_frame,&root->ppu_workspace);
    mysmb_game_io_video(&root->ppu_frame,&video);
    root->hooks.present_video(root->hooks.context,&video);
}
static int capture_snapshot(struct mysmb_dos16_root *root)
{
    struct mysmb_io_snapshot *staged;
    if(!root->snapshot_store || !mysmb_game_snapshot_available(&root->game,&root->game_frame))return 0;
    staged=&root->snapshot_store->staging;
    if(!mysmb_game_snapshot_capture(&root->game,staged,root->snapshot_fingerprint))return 0;
    memset(staged->payload+MYSMB_SNAPSHOT_CORE_BYTES,0,MYSMB_SNAPSHOT_AUDIO_BYTES);
    return 1;
}
void mysmb_dos16_root_bind_clock(struct mysmb_dos16_root *root,void (*resume)(void *))
{root->resume_clock=resume;}
static int snapshot_request(struct mysmb_dos16_root *root,mysmb_io_u8 requests)
{
    const struct mysmb_io_snapshot *candidate;
    if(!root->snapshot_store)return 0;
    if(requests&MYSMB_IO_REQUEST_LOAD){
        candidate=mysmb_snapshot_load(root->snapshot_store,root->snapshot_fingerprint);
        if(root->resume_clock)root->resume_clock(root->reset_context);
        if(!candidate)return 0;
        if(!mysmb_game_snapshot_restore(&root->game,candidate)){
            root->snapshot_store->files.log(root->snapshot_store->files.context,
                "mysmb.log",MYSMB_SNAPSHOT_LOAD_ERROR);return 0;
        }
        mysmb_game_snapshot_resume_frame(&root->game,&root->game_frame);
        if(root->reset_output)root->reset_output(root->reset_context);
        present_current(root);return 1;
    }
    if(requests&MYSMB_IO_REQUEST_SAVE) {
        candidate=0;
        if(capture_snapshot(root))candidate=&root->snapshot_store->staging;
        (void)mysmb_snapshot_save(root->snapshot_store,candidate);
        if(root->resume_clock)root->resume_clock(root->reset_context);
        return 1;
    }
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
    if((decoded.requests&MYSMB_IO_REQUEST_TOGGLE)!=0U && root->set_mode &&
        root->set_mode(root->hooks.context,(mysmb_io_u8)!root->text_mode))
        root->text_mode=(mysmb_io_u8)!root->text_mode;
    if(snapshot_request(root,decoded.requests))return;
    if (mysmb_game_startup_step(&root->game,1U)==0U) return;
    mysmb_game_io_input(&decoded,&input);
    mysmb_game_tick(&root->game,&input,&root->game_frame);
    present_current(root);
    mysmb_game_io_audio(&root->game,&root->audio_frame);
    if (root->hooks.submit_audio!=0)
        root->audio_available=root->hooks.submit_audio(root->hooks.context,&root->audio_frame);
}
void mysmb_dos16_root_shutdown(struct mysmb_dos16_root *root)
{
    if (root->initialized==0U) return;
#ifdef MYSMB_DOS16_TARGET
    mysmb_ppu_frame_end(&root->ppu_view);
    if(root->ppu_pairs)_nfree((struct mysmb_io_palette_pairs __near *)root->ppu_pairs);
    root->ppu_pairs=0;
    if(root->ppu_workspace.bg_second)_ffree(root->ppu_workspace.bg_second);
    if(root->ppu_workspace.bg)_ffree(root->ppu_workspace.bg);
    if(root->ppu_workspace.decoded) {
        if(root->ppu_cache_near)_nfree((mysmb_u8 __near *)root->ppu_workspace.decoded);
        else _ffree(root->ppu_workspace.decoded);
    }
    root->ppu_cache_near=0U;
    mysmb_ppu_frame_workspace_bind(&root->ppu_workspace,0);
    _ffree(root->ppu_frame.pixels);
    root->ppu_frame.pixels=0;
#endif
    root->initialized=0U;
}
