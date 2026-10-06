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
typedef char text_storage_fits_band[sizeof(struct text_storage)>=2560U+MYSMB_VGA_PAGE_COUNT*MYSMB_VGA_BATCH_SIZE &&
    sizeof(struct text_storage)<=MYSMB_IO_VIDEO_PIXELS?1:-1];
static struct text_storage MYSMB_IO_FAR *text_storage;
static mysmb_io_u8 MYSMB_IO_FAR *plane_pixels;

static void read_input(void *context, struct mysmb_io_input *input)
{
    (void)context;
    mysmb_dos16_devices_input(input);
}
static int present_rows(void *context,const struct mysmb_io_palette_video_source *indexed)
{
    mysmb_io_u16 plane,first,source_first,source_rows;
    struct mysmb_io_video_band band;
    const struct mysmb_io_video_source *source=&indexed->rows;
    (void)context;
    mysmb_dos16_devices_palette(indexed->master_colors);
    for(first=0U;first<MYSMB_VGA_HEIGHT;first+=MYSMB_VGA_BATCH_ROWS) {
        source_first=(mysmb_io_u16)(first*3U/5U);
        source_rows=(mysmb_io_u16)((first+MYSMB_VGA_BATCH_ROWS-1U)*3U/5U-source_first+1U);
        if(!source->read_rows(source->context,source_first,source_rows,&band))return 0;
        if(!mysmb_io_planar_build_band(&band,first,MYSMB_VGA_BATCH_ROWS,
            plane_pixels,MYSMB_VGA_PAGE_COUNT*MYSMB_VGA_BATCH_SIZE,
            mysmb_dos16_pack_planar_band))return 0;
        for(plane=0U;plane<MYSMB_VGA_PAGE_COUNT;++plane)
            mysmb_dos16_devices_present_rows(plane,first,MYSMB_VGA_BATCH_ROWS,
                plane_pixels+plane*MYSMB_VGA_BATCH_SIZE);
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
    /* Graphics source occupies at most2560bytes. A5120-byte four-plane view
     * borrow its unused tail until submission;text owns the whole store later. */
    plane_pixels=root.ppu_frame.pixels+2560U;
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
    text_storage=0;plane_pixels=0;
    return 0;
}
