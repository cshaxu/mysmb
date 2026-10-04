#include <stdio.h>
#include <string.h>
#include "platform/dos16/dos16_root.h"
#include "platform/dos16/keyboard.h"
#include "platform/file/snapshot_files.h"
#include "platform/file/executable_path.h"
#include "game/area.h"
#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif
static struct mysmb_dos16_root root;
static struct mysmb_snapshot_store store;
static struct mysmb_file_storage storage;
static struct mysmb_io_snapshot expected,actual;
struct host {unsigned int presents,resets;mysmb_io_u8 buttons,requests;};
static void input(void *context,struct mysmb_io_input *out)
{
    struct host *host=(struct host *)context;
    out->buttons=host->buttons;out->buttons2=0U;out->requests=host->requests;
    host->requests=0U;
}
static void present(void *context,const struct mysmb_io_video_frame *frame)
{if(frame->pixels)++((struct host *)context)->presents;}
static void reset(void *context){++((struct host *)context)->resets;}
int main(int argc,char **argv)
{
    struct mysmb_dos16_hooks hooks;
    struct mysmb_snapshot_files files;
    struct mysmb_dos16_keyboard keyboard;
    struct mysmb_io_input keys;
    struct host host;
    char directory[260],path[300];
    unsigned int i;
    if(argc!=2)return 1;
    if(!mysmb_file_executable_directory("C:\\GAMES\\MYSMB.EXE",directory,sizeof(directory)) ||
        strcmp(directory,"C:\\GAMES\\") ||
        !mysmb_file_executable_directory("C:\\MYSMB.EXE",directory,sizeof(directory)) ||
        strcmp(directory,"C:\\") ||
        mysmb_file_executable_directory("MYSMB.EXE",directory,sizeof(directory)) ||
        mysmb_file_executable_directory("C:MYSMB.EXE",directory,sizeof(directory)) ||
        mysmb_file_executable_directory("C:\\X.EXE",directory,5U))return 2;
    mysmb_dos16_keyboard_initialize(&keyboard);
    mysmb_dos16_keyboard_scan(&keyboard,0x19U);mysmb_dos16_keyboard_scan(&keyboard,0x19U);
    mysmb_dos16_keyboard_input(&keyboard,&keys);
    if(keys.requests!=MYSMB_IO_REQUEST_SAVE || keys.buttons)return 3;
    mysmb_dos16_keyboard_input(&keyboard,&keys);if(keys.requests)return 4;
    mysmb_dos16_keyboard_scan(&keyboard,0x18U);
    mysmb_dos16_keyboard_after_load(&keyboard);
    mysmb_dos16_keyboard_scan(&keyboard,0x18U);
    mysmb_dos16_keyboard_input(&keyboard,&keys);if(keys.requests)return 5;
    mysmb_dos16_keyboard_scan(&keyboard,0x98U);mysmb_dos16_keyboard_scan(&keyboard,0x18U);
    mysmb_dos16_keyboard_input(&keyboard,&keys);
    if(keys.requests!=MYSMB_IO_REQUEST_LOAD || keys.buttons)return 6;
    memset(&host,0,sizeof(host));hooks.context=&host;hooks.read_input=input;
    hooks.present_video=present;hooks.submit_audio=0;
    if(!mysmb_dos16_root_initialize(&root,&hooks))return 7;
#ifdef MYSMB_LOCAL_TITLE
    mysmb_game_bind_area_source(&root.game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&root.game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&root.game,mysmb_local_title_data,MYSMB_LOCAL_TITLE_DATA_SIZE,
        mysmb_local_title_icon_data,MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
#endif
    if(!mysmb_file_storage_initialize(&storage,argv[1],mysmb_win32_snapshot_replace,&files) ||
        !mysmb_snapshot_store_initialize(&store,&files))return 8;
    mysmb_dos16_root_bind_snapshot(&root,&store,reset,&host);
    for(i=0U;i<1200U && !root.snapshot_cache.valid;++i){
        host.buttons=i==100U?MYSMB_IO_BUTTON_START:0U;
        mysmb_dos16_root_step(&root);
    }
    if(!root.snapshot_cache.valid)return 9;
    host.buttons=0U;
    for(i=0U;i<100U;++i)mysmb_dos16_root_step(&root);
    expected=root.snapshot_cache.last_running;
    host.requests=MYSMB_IO_REQUEST_SAVE;mysmb_dos16_root_step(&root);
    for(i=0U;i<50U;++i)mysmb_dos16_root_step(&root);
    host.requests=MYSMB_IO_REQUEST_LOAD;mysmb_dos16_root_step(&root);
    if(host.resets!=1U || mysmb_game_is_paused(&root.game))return 10;
    mysmb_game_snapshot_capture(&root.game,&actual,root.snapshot_fingerprint);
    memset(actual.payload+MYSMB_SNAPSHOT_CORE_BYTES,0,MYSMB_SNAPSHOT_AUDIO_BYTES);
    if(memcmp(&expected,&actual,sizeof(actual)))return 11;
    sprintf(path,"%s/mysmb.sav",argv[1]);remove(path);
    i=(unsigned int)root.game.frame_number;host.requests=MYSMB_IO_REQUEST_LOAD;
    mysmb_dos16_root_step(&root);
    if(root.game.frame_number!=i+1U || host.resets!=1U)return 12;
    sprintf(path,"%s/mysmb.log",argv[1]);remove(path);
    mysmb_dos16_root_shutdown(&root);
    return 0;
}
