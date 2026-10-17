#include "io/video.h"
#include "platform/dos16/planar_row.h"
#include "dos16/file.h"
#include "dos16/command_line.h"
#include "app/runtime_options.h"
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
/* Graphics borrows only the prefix of this root-owned allocation.  The
 * snapshot store begins after the exclusive text/row storage, so graphics
 * row submission cannot overwrite a pending save/load transaction. */
struct runtime_storage {
    struct text_storage text;
    struct mysmb_snapshot_store snapshot;
};
typedef char text_storage_fits_band[sizeof(struct text_storage)>=8192U &&
    sizeof(struct text_storage)<=MYSMB_VIDEO_PIXELS?1:-1];
typedef char runtime_storage_fits_band[
    sizeof(struct runtime_storage)<=MYSMB_VIDEO_PIXELS?1:-1];
static struct runtime_storage MYGAMES_KVM_FAR *runtime_storage;
static struct text_storage MYGAMES_KVM_FAR *text_storage;

static void read_input(void *context, struct mysmb_io_input *input)
{
    (void)context;
    mysmb_dos16_devices_input(input);
}
static int should_present(void *context)
{(void)context;return mysmb_dos16_devices_should_present();}
static int present_rows(void *context,const struct mysmb_palette_video_source *indexed)
{
    mygames_kvm_u16 first;
    struct mygames_kvm_video_band band;
    const struct mygames_kvm_video_source *source=&indexed->rows;
    (void)context;
    mysmb_dos16_devices_palette(indexed->master_colors);
    for(first=0U;first<MYSMB_PLANAR_NATIVE_HEIGHT;first+=MYSMB_VGA_BATCH_ROWS) {
        if(!source->read_rows(source->context,first,MYSMB_VGA_BATCH_ROWS,&band))return 0;
        if(!mysmb_dos16_devices_present_band(&band))return 0;
    }
    return 1;
}
static mygames_kvm_u8 submit_audio(void *context, const struct mysmb_io_audio_frame *frame)
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
static int set_mode(void *context,mygames_kvm_u8 text)
{(void)context;return mysmb_dos16_devices_mode(text);}
static void present_text(void *context,const struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame)
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
    /* Reserve the device-owned Sound Blaster DMA ring before the root asks
     * DOS for its optional PPU/text/snapshot workspaces.  ISA DMA must use a
     * single low-memory span; doing this last can leave a playable product
     * silently without a suitable 4 KiB block even though the same card is
     * otherwise present.  Device open remains platform-only and no game
     * state has started before it succeeds. */
    if(!mysmb_dos16_devices_open())return 0;
    if (!mysmb_dos16_root_initialize_palette_rows(&root,&hooks,
        (mygames_kvm_u16)sizeof(struct runtime_storage),present_rows)) {
        mysmb_dos16_devices_close();return 0;
    }
    mysmb_dos16_root_bind_clock(&root,resume_clock);
    mysmb_dos16_root_bind_video_gate(&root,should_present);
    /* Graphics borrows4096 bytes and submits them directly.  Text and the
     * single on-demand snapshot transaction occupy disjoint suffixes of the
     * same required root allocation; no scaled or planar scratch is needed. */
    runtime_storage=(struct runtime_storage MYGAMES_KVM_FAR *)root.ppu_frame.pixels;
    text_storage=&runtime_storage->text;
    snapshot_store=&runtime_storage->snapshot;
#ifdef MYSMB_LOCAL_TITLE
    mysmb_game_bind_area_source(&root.game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&root.game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&root.game,mysmb_local_title_data,
        MYSMB_LOCAL_TITLE_DATA_SIZE,mysmb_local_title_icon_data,MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
#endif
    if(mygames_dos16_executable_path(path,sizeof(path)) &&
        mysmb_file_executable_directory(path,directory,sizeof(directory)) &&
        mysmb_file_storage_initialize(&snapshot_storage,directory,
            mygames_dos16_file_replace,&files) &&
        mysmb_snapshot_store_initialize(snapshot_store,&files))
        mysmb_dos16_root_bind_snapshot(&root,snapshot_store,reset_output,0);
    /* Synchronous presenters are exclusive. Graphics rebuilds every band on
     * return from text;only the root owns and frees this shared allocation. */
    mysmb_dos16_root_bind_text(&root,&text_storage->workspace,
        &text_storage->frame,set_mode,present_text);
    return 1;
}

static int configure_options(void)
{
    char command[128];
    int policy;
    if(!mygames_dos16_command_line(command,sizeof(command)))return 0;
    policy=mysmb_app_runtime_options(command);
    if(policy<0)return 0;
    mysmb_dos16_devices_set_turbo(policy);
    return 1;
}

int main(void)
{
    if(!configure_options()) {
        fputs("Usage: MYSMB16 [--turbo]\n",stderr);return 2;
    }
    if(!initialize())return 1;
    for (;;) {
        /* A latched IRQ may finish after stop intent. Keep the application
         * and vector alive until the device reports completed cleanup. */
        if(root.control.exit_requested) {
            if(mysmb_dos16_devices_close())break;
            mysmb_dos16_devices_wait();continue;
        }
        mysmb_dos16_root_step(&root);
        if (root.control.exit_requested==0U) mysmb_dos16_devices_wait();
    }
    mysmb_dos16_root_shutdown(&root);
    runtime_storage=0;text_storage=0;snapshot_store=0;
    return 0;
}
