#include "platform/dos16/dos16_root.h"
#include "platform/dos16/devices.h"
#include "game/area.h"
#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

static struct mysmb_dos16_root root;
static struct mysmb_vga_frame vga;
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
int main(void)
{
    struct mysmb_dos16_hooks hooks;
    hooks.context=0;
    hooks.read_input=read_input;
    hooks.present_video=present_video;
    if (!mysmb_dos16_root_initialize(&root,&hooks)) return 1;
#ifdef MYSMB_LOCAL_TITLE
    mysmb_game_bind_area_source(&root.game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&root.game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&root.game,mysmb_local_title_data,
        MYSMB_LOCAL_TITLE_DATA_SIZE,mysmb_local_title_icon_data,MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
#endif
    mysmb_vga_frame_initialize(&vga,pages0,pages1,pages2,pages3);
    mysmb_dos16_devices_open();
    while (!mysmb_dos16_devices_exit_requested()) {
        mysmb_dos16_root_step(&root);
        mysmb_dos16_devices_wait();
    }
    mysmb_dos16_devices_close();
    mysmb_dos16_root_shutdown(&root);
    return 0;
}
