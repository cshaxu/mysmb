#include "platform/dos16/dos16_root.h"
#include "platform/dos16/devices.h"
#include "game/area.h"
#include <stdio.h>
#include <malloc.h>
#include "platform/file/snapshot_files.h"
#include "platform/file/executable_path.h"
#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

static struct mysmb_dos16_root root;
static struct mysmb_vga_frame vga;
static struct mysmb_snapshot_store *snapshot_store;
static struct mysmb_file_storage snapshot_storage;
struct text_storage {
    struct mysmb_text_scene_workspace workspace;
    struct mysmb_io_text_frame frame;
};
static struct text_storage MYSMB_IO_FAR *text_storage;
static mysmb_io_u8 MYSMB_IO_FAR pages0[MYSMB_VGA_PAGE_SIZE];
static mysmb_io_u8 MYSMB_IO_FAR pages1[MYSMB_VGA_PAGE_SIZE];
static mysmb_io_u8 MYSMB_IO_FAR pages2[MYSMB_VGA_PAGE_SIZE];
static mysmb_io_u8 MYSMB_IO_FAR pages3[MYSMB_VGA_PAGE_SIZE];

static void read_input(void *context, struct mysmb_io_input *input)
{
    (void)context;
    mysmb_dos16_devices_input(input);
}
static void present_video(void *context, const struct mysmb_io_video_frame *frame)
{
    (void)context;
    mysmb_vga_frame_build(frame,&vga);
    mysmb_dos16_devices_present(&vga);
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
int main(void)
{
    struct mysmb_dos16_hooks hooks;
    struct mysmb_snapshot_files files;
    char path[260],directory[260];
    hooks.context=0;
    hooks.read_input=read_input;
    hooks.present_video=present_video;
    hooks.submit_audio=submit_audio;
    if (!mysmb_dos16_root_initialize(&root,&hooks)) return 1;
    snapshot_store=(struct mysmb_snapshot_store *)_fmalloc(sizeof(*snapshot_store));
    if(snapshot_store==0) {mysmb_dos16_root_shutdown(&root);return 1;}
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
    mysmb_vga_frame_initialize(&vga,pages0,pages1,pages2,pages3);
    if(!mysmb_dos16_devices_open()) {
        mysmb_dos16_root_shutdown(&root);_ffree(snapshot_store);return 1;
    }
    text_storage=(struct text_storage MYSMB_IO_FAR *)_fmalloc(sizeof(*text_storage));
    if(text_storage)mysmb_dos16_root_bind_text(&root,&text_storage->workspace,
        &text_storage->frame,set_mode,present_text);
    while (root.control.exit_requested==0U) {
        mysmb_dos16_root_step(&root);
        if (root.control.exit_requested==0U) mysmb_dos16_devices_wait();
    }
    mysmb_dos16_devices_close();
    mysmb_dos16_root_shutdown(&root);
    _ffree(snapshot_store);
    if(text_storage)_ffree(text_storage);
    return 0;
}
