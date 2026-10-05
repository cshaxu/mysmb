/* Timing is descriptive host evidence,never an acceptance threshold. */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "app/game_io.h"
#include "core/area.h"
#include "app/game_snapshot.h"
#include "text/scene.h"
#include "platform/vga/vga_frame.h"
#include "io/scale.h"
#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif
void mysmb_ppu_frame_reference(const struct mysmb_game *,struct mysmb_ppu_frame *);
static struct mysmb_game game,before;
static struct mysmb_ppu_frame actual,reference,cached;
static struct mysmb_ppu_frame_workspace cache_workspace,other_workspace;
static unsigned char cache_store[MYSMB_PPU_CHR_DECODED_BYTES+2U];
static unsigned char other_store[MYSMB_PPU_CHR_DECODED_BYTES+2U],other_chr[8192];
static struct mysmb_text_scene_workspace workspace;
static struct mysmb_io_text_frame text;
static union borrowed_surface {
    struct mysmb_ppu_frame graphics;
    struct {
        struct mysmb_text_scene_workspace workspace;
        struct mysmb_io_text_frame frame;
    } text;
} borrowed;
typedef char borrowed_text_fits[sizeof(borrowed.text)<=MYSMB_IO_VIDEO_PIXELS?1:-1];
static struct mysmb_io_snapshot snapshot;
static struct mysmb_io_snapshot_cache cache;
static struct mysmb_vga_frame vga;
static unsigned char pages[4][MYSMB_VGA_PAGE_SIZE],chr[8192],fingerprint[16];
static LARGE_INTEGER frequency;
static double stamp(void)
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);return (double)now.QuadPart/frequency.QuadPart;
}
static unsigned long random_state=1UL;
static unsigned char random_byte(void)
{
    random_state=(random_state*1664525UL+1013904223UL)&0xffffffffUL;
    return (unsigned char)(random_state>>24U);
}
static int compare_frames(unsigned int cases)
{
    unsigned int n,i,table;
    for(i=0U;i<8192U;++i)chr[i]=random_byte();
    memset(cache_store,0xa5,sizeof(cache_store));
    mysmb_ppu_frame_workspace_bind(&cache_workspace,cache_store+1U);
    mysmb_game_initialize(&game);
    for(n=0U;n<cases;++n) {
        game.ppu.chr_data=n%17U==0U?0:chr;
        game.ppu.chr_data_size=n%19U==0U?(mysmb_u16)(n*31U%8192U):8192U;
        for(table=0U;table<2U;++table)
            for(i=0U;i<1024U;++i)game.ppu.name_table[table][i]=random_byte();
        for(i=0U;i<32U;++i)game.ppu.palette[i]=random_byte();
        for(i=0U;i<256U;++i)game.ppu.visible_oam[i]=random_byte();
        game.ppu.visible_scroll_x=(unsigned char)n;
        game.ppu.visible_scroll_y=(unsigned char)(n*37U);
        game.ppu.visible_ppu_name_table=(unsigned char)(n%4U);
        game.ppu.visible_ppu_control_0=(unsigned char)((n/4U)%4U*8U);
        game.ppu.visible_ppu_mask=(unsigned char)(n%32U);
        game.ppu.visible_sprite0_split=(unsigned char)((n/32U)%2U);
        before=game;
        mysmb_ppu_frame_reference(&game,&reference);
        mysmb_ppu_frame_build(&game.ppu,&actual);
        mysmb_ppu_frame_build_cached(&game.ppu,&cached,&cache_workspace);
        if(memcmp(cached.pixels,actual.pixels,sizeof(actual.pixels)))return 9;
        if(cache_store[0]!=0xa5U || cache_store[MYSMB_PPU_CHR_DECODED_BYTES+1U]!=0xa5U)return 10;
        if(memcmp(&game,&before,sizeof(game)))return 1;
        if(memcmp(actual.pixels,reference.pixels,sizeof(actual.pixels))) {
            for(i=0U;i<sizeof(actual.pixels);++i)
                if(actual.pixels[i]!=reference.pixels[i])break;
            fprintf(stderr,"pixel mismatch case=%u offset=%u\n",n,i);return 2;
        }
    }
    printf("pixel_equal_cases=%u state_unchanged=1\n",cases);return 0;
}
static int cache_lifetimes(void)
{
    unsigned int i,n;
    unsigned char saved;
    for(i=0U;i<8192U;++i)other_chr[i]=(unsigned char)(chr[i]^0xffU);
    memset(other_store,0x5a,sizeof(other_store));
    mysmb_ppu_frame_workspace_bind(&other_workspace,other_store+1U);
    game.ppu.visible_ppu_mask=0x1eU;
    for(n=0U;n<6U;++n) {
        game.ppu.chr_data=n&1U?other_chr:chr;game.ppu.chr_data_size=8192U;
        mysmb_ppu_frame_build(&game.ppu,&reference);
        mysmb_ppu_frame_build_cached(&game.ppu,&cached,
            n&1U?&other_workspace:&cache_workspace);
        if(memcmp(reference.pixels,cached.pixels,sizeof(cached.pixels)))return 11;
    }
    /* Same-pointer mutation starts an explicitly new binding lifetime. */
    saved=chr[0];chr[0]^=0xffU;game.ppu.chr_data=chr;
    mysmb_ppu_frame_workspace_bind(&cache_workspace,cache_store+1U);
    mysmb_ppu_frame_build(&game.ppu,&reference);
    mysmb_ppu_frame_build_cached(&game.ppu,&cached,&cache_workspace);
    if(memcmp(reference.pixels,cached.pixels,sizeof(cached.pixels)))return 12;
    chr[0]=saved;mysmb_ppu_frame_workspace_bind(&cache_workspace,cache_store+1U);
    mysmb_ppu_frame_workspace_bind(&other_workspace,0);
    mysmb_ppu_frame_build(&game.ppu,&reference);
    mysmb_ppu_frame_build_cached(&game.ppu,&cached,&other_workspace);
    if(memcmp(reference.pixels,cached.pixels,sizeof(cached.pixels)))return 13;
    mysmb_ppu_frame_build_cached(&game.ppu,&cached,0);
    if(memcmp(reference.pixels,cached.pixels,sizeof(cached.pixels)))return 14;
    if(other_store[0]!=0x5aU || other_store[MYSMB_PPU_CHR_DECODED_BYTES+1U]!=0x5aU)return 15;
    printf("cache_lifetimes=two_instances_reset_resource_fallback guards=pass\n");
    return 0;
}
static int cache_priority_alias(void)
{
    unsigned int n;
    unsigned char saved[5];
    before=game;
    saved[0]=chr[0];saved[1]=chr[1];saved[2]=chr[16];saved[3]=chr[9];saved[4]=chr[24];
    memset(&game,0,sizeof(game));memset(game.ppu.visible_oam,0xffU,256U);
    game.ppu.chr_data=chr;game.ppu.chr_data_size=8192U;
    chr[0]=chr[1]=chr[16]=0x80U;chr[9]=chr[24]=0U;
    game.ppu.visible_oam[0]=0U;game.ppu.visible_oam[1]=1U;
    game.ppu.visible_oam[3]=0U;game.ppu.palette[0]=game.ppu.palette[1]=5U;
    game.ppu.palette[0x11U]=7U;
    mysmb_ppu_frame_workspace_bind(&cache_workspace,cache_store+1U);
    for(n=0U;n<4U;++n) {
        game.ppu.visible_ppu_mask=(unsigned char)(n<2U?0x1eU:0x1cU);
        game.ppu.visible_oam[2]=(unsigned char)(n%2U==0U?0x20U:0U);
        mysmb_ppu_frame_reference(&game,&reference);
        mysmb_ppu_frame_build_cached(&game.ppu,&cached,&cache_workspace);
        if(memcmp(reference.pixels,cached.pixels,sizeof(cached.pixels)))return 16;
        if(cached.pixels[256U]!=(n==0U?5U:7U))return 17;
    }
    chr[0]=saved[0];chr[1]=saved[1];chr[16]=saved[2];chr[9]=saved[3];chr[24]=saved[4];
    game=before;
    mysmb_ppu_frame_workspace_bind(&cache_workspace,cache_store+1U);
    printf("cache_priority_alias=4 cases raw-opacity/mask/front-behind pass\n");
    return 0;
}
static void scale_reference(const struct mysmb_io_video_frame *video)
{
    unsigned int x,y;
    /* Independent direct-enlargement oracle,including every source row. */
    for(y=0U;y<MYSMB_VGA_HEIGHT;++y)for(x=0U;x<MYSMB_VGA_WIDTH;++x)
        vga.pages[x%4U][y*80U+x/4U]=
            (unsigned char)(video->pixels[(y*3U/5U)*256U+x*4U/5U]&63U);
}
static unsigned char scaled_reference[4][MYSMB_VGA_PAGE_SIZE];
static int compare_scaling(const struct mysmb_io_video_frame *video)
{
    unsigned int page;
    scale_reference(video);
    for(page=0U;page<4U;++page)memcpy(scaled_reference[page],pages[page],MYSMB_VGA_PAGE_SIZE);
    mysmb_vga_frame_build(video,&vga);
    return memcmp(scaled_reference,pages,sizeof(pages))==0;
}
static void report(const char *name,double seconds,unsigned int count)
{
    printf("%s_us_per_frame=%.3f\n",name,seconds*1000000.0/count);
}
int main(void)
{
    struct mysmb_frame frame;
    struct mysmb_input input;
    struct mysmb_io_video_frame video;
    unsigned int i,n;
    double start,old_time,new_time,tick_time,graphics_time,text_time,scale_time,save_time;
    int result;
    QueryPerformanceFrequency(&frequency);
    result=compare_frames(2048U);if(result)return result;
    result=cache_lifetimes();if(result)return result;
    result=cache_priority_alias();if(result)return result;
    /* Identical densely populated fixture;timing never changes pass/fail. */
    game.ppu.chr_data=chr;game.ppu.chr_data_size=8192U;game.ppu.visible_ppu_mask=0x1eU;
    n=512U;start=stamp();
    for(i=0U;i<n;++i)mysmb_ppu_frame_reference(&game,&reference);
    old_time=stamp()-start;start=stamp();
    for(i=0U;i<n;++i)mysmb_ppu_frame_build(&game.ppu,&actual);
    new_time=stamp()-start;
    report("dense_reference_graphics",old_time,n);
    report("dense_current_graphics",new_time,n);
    printf("dense_graphics_speedup=%.3f\n",old_time/new_time);
    start=stamp();
    for(i=0U;i<n;++i)mysmb_ppu_frame_build_cached(&game.ppu,&cached,&cache_workspace);
    report("dense_cached_graphics",stamp()-start,n);
    mysmb_vga_frame_initialize(&vga,pages[0],pages[1],pages[2],pages[3]);
    mysmb_game_io_video(&actual,&video);
    if(!compare_scaling(&video))return 7;
    start=stamp();for(i=0U;i<n;++i)scale_reference(&video);old_time=stamp()-start;
    start=stamp();for(i=0U;i<n;++i)mysmb_vga_frame_build(&video,&vga);new_time=stamp()-start;
    report("reference_vga_scale",old_time,n);report("current_vga_scale",new_time,n);
    printf("vga_scale_speedup=%.3f\n",old_time/new_time);
#ifdef MYSMB_LOCAL_TITLE
    mysmb_game_power_on(&game);
    mysmb_game_bind_area_source(&game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&game,mysmb_local_title_data,MYSMB_LOCAL_TITLE_DATA_SIZE,
        mysmb_local_title_icon_data,MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    mysmb_text_observer_enable(&game,1U);
    mysmb_game_frame_initialize(&frame);
    mysmb_game_snapshot_fingerprint(&game,fingerprint);
    mysmb_snapshot_cache_initialize(&cache);
    mysmb_vga_frame_initialize(&vga,pages[0],pages[1],pages[2],pages[3]);
    tick_time=graphics_time=text_time=scale_time=save_time=0.0;n=0U;
    for(i=0U;i<1200U;++i) {
        if(!mysmb_game_startup_step(&game,1U))continue;
        input.buttons=i==120U?MYSMB_BUTTON_START:
            i>120U?(MYSMB_BUTTON_RIGHT|MYSMB_BUTTON_B|
                (i%50U<10U?MYSMB_BUTTON_A:0U)):0U;input.buttons2=0U;
        start=stamp();mysmb_game_tick(&game,&input,&frame);tick_time+=stamp()-start;
        before=game;
        start=stamp();mysmb_ppu_frame_build_cached(&game.ppu,&actual,&cache_workspace);graphics_time+=stamp()-start;
        mysmb_ppu_frame_reference(&game,&reference);
        if(memcmp(actual.pixels,reference.pixels,sizeof(actual.pixels)))return 3;
        start=stamp();
        if(!mysmb_text_scene_build(&game,&workspace,&text))return 4;
        text_time+=stamp()-start;
        /* Previous pixel bytes must not become text workspace state. */
        memcpy(borrowed.graphics.pixels,reference.pixels,sizeof(reference.pixels));
        borrowed.graphics.pixels[sizeof(borrowed.text)]=0xa5U;
        if(!mysmb_text_scene_build(&game,&borrowed.text.workspace,&borrowed.text.frame))return 18;
        if(memcmp(&text,&borrowed.text.frame,sizeof(text)) ||
            borrowed.graphics.pixels[sizeof(borrowed.text)]!=0xa5U)return 19;
        mysmb_ppu_frame_build_cached(&game.ppu,&borrowed.graphics,&cache_workspace);
        if(memcmp(borrowed.graphics.pixels,reference.pixels,sizeof(reference.pixels)))return 20;
        mysmb_game_io_video(&actual,&video);
        start=stamp();mysmb_vga_frame_build(&video,&vga);scale_time+=stamp()-start;
        if(!compare_scaling(&video))return 8;
        start=stamp();
        if(!mysmb_game_snapshot_capture(&game,&snapshot,fingerprint))return 5;
        mysmb_snapshot_cache_update(&cache,&snapshot,1U);save_time+=stamp()-start;
        if(memcmp(&game,&before,sizeof(game)))return 6;
        ++n;
    }
    printf("native_route_frames=%u\n",n);
    printf("borrowed_presenter_frames=%u text/graphics/extent/state pass\n",n);
    report("native_tick",tick_time,n);report("native_graphics",graphics_time,n);
    report("native_text",text_time,n);report("native_vga_scale",scale_time,n);
    report("native_snapshot",save_time,n);
#else
    (void)frame;(void)input;(void)video;(void)tick_time;(void)graphics_time;
    (void)text_time;(void)scale_time;(void)save_time;
#endif
    return 0;
}
