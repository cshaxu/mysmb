#include "platform/dos16/planar_row.h"
#include "platform/dos16/executable_path.h"
#include "platform/dos16/snapshot_replace.h"
#include "platform/dos16/dos16_root.h"
#include "platform/dos16/devices.h"
#include "core/area.h"
#include <stdio.h>
#include <malloc.h>
#include "io/file/snapshot_files.h"
#include "io/file/executable_path.h"
#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

static struct mysmb_dos16_root root;
static struct mysmb_snapshot_store *snapshot_store;
static struct mysmb_file_storage snapshot_storage;
struct text_storage {
    struct mysmb_text_scene_workspace workspace;
    struct mysmb_io_text_frame frame;
};
typedef char text_storage_fits_band[sizeof(struct text_storage)>=8192U &&
    sizeof(struct text_storage)<=MYSMB_IO_VIDEO_PIXELS?1:-1];
static struct text_storage MYSMB_IO_FAR *text_storage;

static void read_input(void *context, struct mysmb_io_input *input)
{
    (void)context;
    mysmb_dos16_devices_input(input);
}
static int present_rows(void *context,const struct mysmb_io_palette_video_source *indexed)
{
    mysmb_io_u16 first;
    struct mysmb_io_video_band band;
    const struct mysmb_io_video_source *source=&indexed->rows;
    (void)context;
    mysmb_dos16_devices_palette(indexed->master_colors);
    for(first=0U;first<MYSMB_PLANAR_NATIVE_HEIGHT;first+=MYSMB_VGA_BATCH_ROWS) {
        if(!source->read_rows(source->context,first,MYSMB_VGA_BATCH_ROWS,&band))return 0;
        if(!mysmb_dos16_devices_present_band(&band))return 0;
    }
    return 1;
}
static mysmb_io_u8 submit_audio(void *context, const struct mysmb_io_audio_frame *frame)
{
    (void)context;
    return mysmb_dos16_devices_audio(frame);
}
static void reset_output(void *context)
{
    (void)context;mysmb_dos16_devices_after_load();
}
static void resume_clock(void *context)
{(void)context;mysmb_dos16_devices_resume_clock();}
static int set_mode(void *context,mysmb_io_u8 text)
{(void)context;return mysmb_dos16_devices_mode(text);}
static void present_text(void *context,const struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{(void)context;mysmb_dos16_devices_text(frame);}
/* Startup scratch expires before the game loop and its render/file calls.
 * The root/store copy hooks and file services;directory bytes are copied. */
static int initialize(void)
{
    struct mysmb_dos16_hooks hooks;
    struct mysmb_snapshot_files files;
    char path[260],directory[260];
    hooks.context=0;
    hooks.read_input=read_input;
    hooks.present_video=0;
    hooks.submit_audio=submit_audio;
    if (!mysmb_dos16_root_initialize_palette_rows(&root,&hooks,
        (mysmb_io_u16)sizeof(struct text_storage),present_rows)) return 0;
    mysmb_dos16_root_bind_clock(&root,resume_clock);
    /* Graphics borrows4096bytes and submits them directly;text owns the
     * complete shared store later. No scaled or planar scratch is needed. */
    snapshot_store=(struct mysmb_snapshot_store *)_fmalloc(sizeof(*snapshot_store));
    if(snapshot_store==0) {mysmb_dos16_root_shutdown(&root);return 0;}
#ifdef MYSMB_LOCAL_TITLE
    mysmb_game_bind_area_source(&root.game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&root.game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&root.game,mysmb_local_title_data,
        MYSMB_LOCAL_TITLE_DATA_SIZE,mysmb_local_title_icon_data,MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
#endif
    if(mysmb_dos16_executable_path(path,sizeof(path)) &&
        mysmb_file_executable_directory(path,directory,sizeof(directory)) &&
        mysmb_file_storage_initialize(&snapshot_storage,directory,
            mysmb_dos16_snapshot_replace,&files) &&
        mysmb_snapshot_store_initialize(snapshot_store,&files))
        mysmb_dos16_root_bind_snapshot(&root,snapshot_store,reset_output,0);
    if(!mysmb_dos16_devices_open()) {
        mysmb_dos16_root_shutdown(&root);_ffree(snapshot_store);return 0;
    }
    /* Synchronous presenters are exclusive. Graphics rebuilds every band on
     * return from text;only the root owns and frees this shared allocation. */
    text_storage=(struct text_storage MYSMB_IO_FAR *)root.ppu_frame.pixels;
    mysmb_dos16_root_bind_text(&root,&text_storage->workspace,
        &text_storage->frame,set_mode,present_text);
    return 1;
}

int main(void)
{
    if(!initialize())return 1;
    while (root.control.exit_requested==0U) {
        mysmb_dos16_root_step(&root);
        if (root.control.exit_requested==0U) mysmb_dos16_devices_wait();
    }
    mysmb_dos16_devices_close();
    mysmb_dos16_root_shutdown(&root);
    _ffree(snapshot_store);
    text_storage=0;
    return 0;
}
