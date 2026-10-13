#include "io/video.h"
#include "io/color.h"
#include "platform/dos16/devices.h"
#include "platform/dos16/compact_vga_layout.h"
#include "platform/dos16/retained_background.h"
#include "platform/dos16/keyboard.h"
#include "dos16/host.h"
#include "dos16/vga.h"
#include "dos16/text_cells.h"
#include "platform/dos16/dos_audio.h"
#include "ppu/frame.h"
#include "kvm/color.h"
#include "io/pacing.h"
#include <dos.h>
#include <conio.h>
#include <string.h>

static struct mysmb_dos16_keyboard keyboard;
static struct mygames_dos16_video_state old_video;
static unsigned char video_ready;
/* DOS binds this shared deadline to a frame-dropping policy.  Other hosts may
 * retain ordinary pacing without binding a video gate. */
static struct mysmb_io_pacing pacing;
/* The current logical tick may compose only when it was reached at its
 * scheduled deadline.  Catch-up ticks preserve game/audio/input timing but
 * leave their already-stale images unpublished. */
static unsigned char present_due=1U;
static unsigned char opened;
static unsigned char text_mode;
static unsigned short text_rows=25U;
static mygames_kvm_u8 palette_shadow[MYSMB_VIDEO_PALETTE_COLORS],palette_valid;
static unsigned char retained_mode;
static unsigned char compact_mode,compact_page;
static unsigned char ram_mode;
struct retained_viewport {mygames_kvm_u8 table,x,y;};
struct retained_sprite_backup {mygames_kvm_u8 x,y,active,pixels[64];};
/* Bounded transient coverage only: 32*256 fixed-HUD bytes plus at most
 * 64 complete 8-by-8 sprite rectangles. No conventional full frame. */
/* The two 32-by-256 transient HUD surfaces remain bounded at 8KiB each.
 * They are packed in physical-plane order after PPU selection, so restore and
 * redraw can use contiguous VGA spans instead of 16,384 pixel address walks. */
static mygames_kvm_u8 retained_hud[8192],retained_hud_slots[8192],retained_hud_valid;
static mygames_kvm_u8 retained_hud_line[256];
static mygames_kvm_u8 retained_tile_plane;
static struct retained_viewport retained_hud_view;
static struct retained_sprite_backup retained_sprites[64];
static struct retained_sprite_backup MYGAMES_KVM_FAR retained_next_sprites[64];
static mygames_kvm_u8 retained_sprite_count,retained_next_count;
/* PPU-owned source rows plus one temporary OAM tile. This replaces slow VGA
 * plane readback; it is bounded transient overlay storage, not a frame. */
/* All sprites captured in one presentation share this PPU-selected viewport.
 * Keep it until their reverse restoration during the next presentation. */
static struct retained_viewport retained_sprite_view;

/* The physical VGA adapter owns this byte move.  It is intentionally below
 * all PPU decisions: callers already selected the source slots and target
 * plane.  The byte tail handles the viewport's possible 128-byte wrap. */


static void keyboard_scan(void *context,mygames_kvm_u8 scan)
{
    mysmb_dos16_keyboard_scan((struct mysmb_dos16_keyboard *)context,scan);
}

/* Independent native256x240 timing:25.175MHz,800dots/525lines,approximately
 * 60Hz. VGA repeats each stored row twice;chain4 exposes61440linear bytes.
 * BIOS13h supplies initial graphics/attribute state;restore uses original mode. */


/* The S5-proven unchained timing is retained here but not selected by the
 * ordinary presenter. S8 must first restore/draw HUD and sprites. */


static int vga_retained_tile(void *context,mygames_kvm_u8 plane,mygames_kvm_u8 table,
    mygames_kvm_u8 row,mygames_kvm_u8 column,const mygames_kvm_u8 MYGAMES_KVM_FAR *slots)
{
    volatile unsigned char far *video=mygames_dos16_vga_memory();
    unsigned char copy,expected;
    unsigned short base,y;
    (void)context;
    if(!slots)return 0;
    if(retained_tile_plane!=plane) {
        mygames_dos16_vga_plane(plane);retained_tile_plane=plane;
    }
    for(copy=0U;copy<2U;++copy) {
        if(!mysmb_dos16_retained_tile_address(table,row,column,copy,&expected,&base) ||
            expected!=0U)return 0;
        for(y=0U;y<8U;++y) {
            video[base+y*MYSMB_DOS16_RETAINED_STRIDE]=slots[y*8U+plane];
            video[base+y*MYSMB_DOS16_RETAINED_STRIDE+1U]=slots[y*8U+4U+plane];
        }
    }
    return 1;
}
static int vga_retained_tile_all(void *context,mygames_kvm_u8 table,mygames_kvm_u8 row,
    mygames_kvm_u8 column,const mygames_kvm_u8 MYGAMES_KVM_FAR *slots)
{
    mygames_kvm_u8 plane;
    retained_tile_plane=0xffU;
    for(plane=0U;plane<4U;++plane)
        if(!vga_retained_tile(context,plane,table,row,column,slots))return 0;
    return 1;
}
static void vga_retained_viewport(mygames_kvm_u8 table,mygames_kvm_u8 x,mygames_kvm_u8 y)
{
    unsigned short source=(unsigned short)((unsigned short)table*256U+x);
    unsigned short start=(unsigned short)((unsigned short)y*64U+(source>>3U));
    mygames_dos16_vga_viewport(start,(unsigned char)(source&7U));
}

/* Compact layout: one 512-by-240 cache period followed by two 264-by-240
 * composition pages.  The pages are never visible while being assembled.
 * All coordinates below are already PPU-selected output coordinates. */


static void vga_compact_viewport(mygames_kvm_u8 page,mygames_kvm_u8 pan)
{
    mygames_kvm_u16 base=(page==0U?MYSMB_DOS16_COMPACT_PAGE_A:
        MYSMB_DOS16_COMPACT_PAGE_B);
    mygames_kvm_u16 start=(mygames_kvm_u16)(base>>1U);
    mygames_dos16_vga_viewport(start,pan);
}

static int vga_compact_tile(void *context,mygames_kvm_u8 plane,mygames_kvm_u8 table,
    mygames_kvm_u8 row,mygames_kvm_u8 column,const mygames_kvm_u8 MYGAMES_KVM_FAR *slots)
{
    volatile unsigned char far *video=mygames_dos16_vga_memory();
    mygames_kvm_u16 base,y,x;
    (void)context;
    if(!slots || table>=2U || row>=30U || column>=32U)return 0;
    if(retained_tile_plane!=plane) {
        mygames_dos16_vga_plane(plane);retained_tile_plane=plane;
    }
    x=(mygames_kvm_u16)table*256U+(mygames_kvm_u16)column*8U;
    base=(mygames_kvm_u16)((mygames_kvm_u16)row*8U*
        MYSMB_DOS16_COMPACT_CACHE_STRIDE+(x>>2U));
    for(y=0U;y<8U;++y) {
        video[base+y*MYSMB_DOS16_COMPACT_CACHE_STRIDE]=slots[y*8U+plane];
        video[base+y*MYSMB_DOS16_COMPACT_CACHE_STRIDE+1U]=slots[y*8U+4U+plane];
    }
    return 1;
}

/* VGA write mode 1 writes the latches loaded by the source read to every
 * plane at once.  It moves the complete four-plane row without a RAM frame
 * or one sequencer pass per plane. */
static int vga_compact_copy_viewport(const struct retained_viewport *view,
    mygames_kvm_u8 page)
{
    volatile unsigned char far *video=mygames_dos16_vga_memory();
    mygames_kvm_u16 row,source,target,i;
    mygames_kvm_u8 first,second;
    volatile unsigned char loaded;
    target=(page==0U?MYSMB_DOS16_COMPACT_PAGE_A:MYSMB_DOS16_COMPACT_PAGE_B);
    mygames_dos16_vga_register(0x3c4,2,15);mygames_dos16_vga_register(0x3ce,5,0x41U);
    for(row=0U;row<MYSMB_DOS16_COMPACT_PAGE_HEIGHT;++row) {
        if(!mysmb_dos16_compact_viewport_row(view->table,view->x,view->y,
            (mygames_kvm_u8)row,&source,&first,&second))goto failed;
        for(i=0U;i<first;++i) {
            loaded=video[source+i];video[target+row*MYSMB_DOS16_COMPACT_PAGE_STRIDE+i]=loaded;
        }
        for(i=0U;i<second;++i) {
            loaded=video[i];video[target+row*MYSMB_DOS16_COMPACT_PAGE_STRIDE+first+i]=loaded;
        }
    }
    mygames_dos16_vga_register(0x3ce,5,0);return 1;
failed:
    mygames_dos16_vga_register(0x3ce,5,0);return 0;
}

static mygames_kvm_u16 compact_page_offset(mygames_kvm_u8 page,mygames_kvm_u8 pan,
    mygames_kvm_u8 x,mygames_kvm_u8 y)
{
    mygames_kvm_u16 base=(page==0U?MYSMB_DOS16_COMPACT_PAGE_A:
        MYSMB_DOS16_COMPACT_PAGE_B);
    return (mygames_kvm_u16)(base+(mygames_kvm_u16)y*MYSMB_DOS16_COMPACT_PAGE_STRIDE+
        (((mygames_kvm_u16)pan+x)>>2U));
}

static void compact_write_slots(mygames_kvm_u8 page,mygames_kvm_u8 pan,
    mygames_kvm_u8 x,mygames_kvm_u8 y,mygames_kvm_u8 width,mygames_kvm_u8 rows,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *slots,mygames_kvm_u8 transparent)
{
    volatile unsigned char far *video=mygames_dos16_vga_memory();
    mygames_kvm_u16 py,i;
    mygames_kvm_u8 plane,first,logical;
    if(!slots)return;
    for(plane=0U;plane<4U;++plane) {
        first=(mygames_kvm_u8)((plane+4U-((pan+x)&3U))&3U);mygames_dos16_vga_plane(plane);
        for(py=0U;py<rows;++py)for(i=first;i<width;i=(mygames_kvm_u16)(i+4U)) {
            logical=(mygames_kvm_u8)i;
            if(!transparent || slots[py*8U+logical]!=255U)
                video[compact_page_offset(page,pan,(mygames_kvm_u8)(x+logical),
                    (mygames_kvm_u8)(y+py))]=slots[py*8U+logical];
        }
    }
}

static void compact_write_hud(mygames_kvm_u8 page,mygames_kvm_u8 pan,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *slots)
{
    volatile unsigned char far *video=mygames_dos16_vga_memory();
    mygames_kvm_u16 base,y,i,offset;
    mygames_kvm_u8 plane,first;
    if(!slots)return;
    base=(page==0U?MYSMB_DOS16_COMPACT_PAGE_A:
        MYSMB_DOS16_COMPACT_PAGE_B);
    for(plane=0U;plane<4U;++plane) {
        first=(mygames_kvm_u8)((plane+4U-(pan&3U))&3U);mygames_dos16_vga_plane(plane);
        offset=(mygames_kvm_u16)((pan+first)>>2U);
        for(y=0U;y<32U;++y) {
            volatile unsigned char far *target=video+base+
                y*MYSMB_DOS16_COMPACT_PAGE_STRIDE+offset;
            const mygames_kvm_u8 MYGAMES_KVM_FAR *source=slots+y*256U+first;
            for(i=0U;i<64U;++i)target[i]=source[i*4U];
        }
    }
}

struct compact_sprite_context {mygames_kvm_u8 page,pan;};
static int compact_draw_sprite(void *context,mygames_kvm_u8 sprite,mygames_kvm_u8 x,
    mygames_kvm_u8 y,const mygames_kvm_u8 MYGAMES_KVM_FAR *slots)
{
    struct compact_sprite_context *draw=(struct compact_sprite_context *)context;
    mygames_kvm_u8 width=8U,rows=8U;
    (void)sprite;
    if(!draw || !slots)return 0;
    if((mygames_kvm_u16)x+width>256U)width=(mygames_kvm_u8)(256U-x);
    if((mygames_kvm_u16)y+rows>240U)rows=(mygames_kvm_u8)(240U-y);
    compact_write_slots(draw->page,draw->pan,x,y,width,rows,slots,1U);
    return 1;
}
static void retained_viewport_from(const struct mysmb_ppu_scene_viewport *source,
    struct retained_viewport *target)
{
    target->table=source->scene_page;target->x=source->output_origin_x;target->y=source->output_origin_y;
    if(target->y>=240U)target->y=(mygames_kvm_u8)(target->y-240U);
}
static mygames_kvm_u16 retained_offset(const struct retained_viewport *view,
    mygames_kvm_u8 x,mygames_kvm_u8 y)
{
    mygames_kvm_u16 physical_x=(mygames_kvm_u16)view->table*256U+view->x+x;
    mygames_kvm_u16 physical_y=(mygames_kvm_u16)view->y+y;
    if(physical_x>=512U)physical_x=(mygames_kvm_u16)(physical_x-512U);
    return (mygames_kvm_u16)(physical_y*MYSMB_DOS16_RETAINED_STRIDE+(physical_x>>2U));
}
static mygames_kvm_u8 retained_plane(const struct retained_viewport *view,mygames_kvm_u8 x)
{
    return (mygames_kvm_u8)((view->table*256U+view->x+x)&3U);
}
/* A plane owns two positions in each complete 8-pixel sprite row. */
static mygames_kvm_u8 retained_sprite_plane_first(const struct retained_viewport *view,
    mygames_kvm_u8 x,mygames_kvm_u8 plane)
{return (mygames_kvm_u8)((plane+4U-retained_plane(view,x))&3U);}

/* Convert one neutral 32-row source into the same physical plane/order that
 * the current viewport addresses.  The source is still PPU-owned; this is
 * only the transient VGA layout used by the next restore or HUD write. */
static void retained_hud_pack(const struct retained_viewport *view,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *source,mygames_kvm_u8 MYGAMES_KVM_FAR *packed)
{
    mygames_kvm_u16 y,i;
    mygames_kvm_u8 plane,first;
    for(plane=0U;plane<4U;++plane) {
        first=retained_sprite_plane_first(view,0U,plane);
        for(y=0U;y<32U;++y)for(i=0U;i<64U;++i)
            packed[plane*2048U+y*64U+i]=source[y*256U+first+i*4U];
    }
}

/* One logical 256-pixel line is 64 bytes in each plane.  It can cross the
 * retained 512-pixel row boundary once, never a scanline or PPU boundary. */
static void retained_hud_write_plane(const struct retained_viewport *view,
    mygames_kvm_u8 plane,const mygames_kvm_u8 MYGAMES_KVM_FAR *packed)
{
    volatile unsigned char far *video=mygames_dos16_vga_memory();
    mygames_kvm_u16 y,offset,first_count,second_count,physical;
    mygames_kvm_u8 first;
    first=retained_sprite_plane_first(view,0U,plane);
    physical=(mygames_kvm_u16)view->table*256U+view->x+first;
    if(physical>=512U)physical=(mygames_kvm_u16)(physical-512U);
    offset=(mygames_kvm_u16)(physical>>2U);
    first_count=(mygames_kvm_u16)(128U-offset);
    if(first_count>64U)first_count=64U;
    second_count=(mygames_kvm_u16)(64U-first_count);
    mygames_dos16_vga_plane(plane);
    for(y=0U;y<32U;++y) {
        const mygames_kvm_u8 MYGAMES_KVM_FAR *source=packed+plane*2048U+y*64U;
        mygames_dos16_copy_bytes((unsigned char far *)video+y*128U+offset,source,first_count);
        if(second_count)mygames_dos16_copy_bytes((unsigned char far *)video+y*128U,
            source+first_count,second_count);
    }
}
static void retained_restore_hud(void)
{
    mygames_kvm_u8 plane;
    if(!retained_hud_valid)return;
    for(plane=0U;plane<4U;++plane)
        retained_hud_write_plane(&retained_hud_view,plane,retained_hud);
    retained_hud_valid=0U;
}
static int retained_hud_rows(const struct mysmb_ppu_frame_view *view,
    const struct retained_viewport *viewport)
{
    mygames_kvm_u8 plane;
    /* Save the PPU-selected scrollable scene, not a VGA readback.  It is the
     * exact surface covered by the fixed HUD and is restored next frame at
     * the old viewport. */
    if(!mysmb_ppu_frame_scene_rows(view,retained_hud_slots,sizeof(retained_hud_slots),0U,32U))return 0;
    retained_hud_pack(viewport,retained_hud_slots,retained_hud);
    if(!mysmb_ppu_frame_background_rows(view,retained_hud_slots,sizeof(retained_hud_slots),0U,32U))return 0;
    /* One line is packed and committed before the scratch is reused.  Select
     * the VGA plane once per 32-row HUD pass; slot extraction stays in this
     * original caller, avoiding a DOS large-model far-slot helper. */
    for(plane=0U;plane<4U;++plane) {
        mygames_kvm_u16 y,i;
        mygames_kvm_u8 first=retained_sprite_plane_first(viewport,0U,plane);
        mygames_dos16_vga_plane(plane);
        for(y=0U;y<32U;++y) {
            volatile unsigned char far *video=mygames_dos16_vga_memory();
            mygames_kvm_u16 offset,first_count,second_count,physical;
            for(i=0U;i<64U;++i)retained_hud_line[i]=retained_hud_slots[y*256U+first+i*4U];
            physical=(mygames_kvm_u16)viewport->table*256U+viewport->x+first;
            if(physical>=512U)physical=(mygames_kvm_u16)(physical-512U);
            offset=(mygames_kvm_u16)(physical>>2U);
            first_count=(mygames_kvm_u16)(128U-offset);if(first_count>64U)first_count=64U;
            second_count=(mygames_kvm_u16)(64U-first_count);
            mygames_dos16_copy_bytes((unsigned char far *)video+y*128U+offset,retained_hud_line,first_count);
            if(second_count)mygames_dos16_copy_bytes((unsigned char far *)video+y*128U,
                retained_hud_line+first_count,second_count);
        }
    }
    retained_hud_view=*viewport;retained_hud_valid=1U;return 1;
}
struct retained_collect_context {struct retained_sprite_backup *items;mygames_kvm_u8 *count;};
static int retained_collect_sprite(void *context,mygames_kvm_u8 sprite,mygames_kvm_u8 x,
    mygames_kvm_u8 y,const mygames_kvm_u8 MYGAMES_KVM_FAR *slots)
{
    struct retained_collect_context *collect=(struct retained_collect_context *)context;
    struct retained_sprite_backup *item;
    (void)sprite;
    if(*collect->count>=64U)return 0;
    item=&collect->items[(*collect->count)++];
    item->x=x;item->y=y;item->active=1U;memcpy(item->pixels,slots,64U);
    return 1;
}
static void retained_mark_sprite_tiles(const struct retained_sprite_backup *items,
    mygames_kvm_u8 count,mygames_kvm_u8 *marks)
{
    mygames_kvm_u16 n,y,last,column,last_column;
    for(n=0U;n<count;++n) {
        if(!items[n].active)continue;
        column=(mygames_kvm_u16)(items[n].x>>3U);last_column=(mygames_kvm_u16)((items[n].x+7U)>>3U);
        y=items[n].y;last=(mygames_kvm_u16)y+7U;if(last>=240U)last=239U;
        for(;y<=last;++y) {
            mygames_kvm_u16 band=(mygames_kvm_u16)(y>>4U);
            marks[band*32U+column]=1U;marks[band*32U+last_column]=1U;
        }
    }
}
static int retained_repaint_tiles(const struct mysmb_ppu_frame_view *view,
    const struct retained_viewport *viewport,const mygames_kvm_u8 *marks)
{
    volatile unsigned char far *video=mygames_dos16_vga_memory();
    mygames_kvm_u16 band,row,column,offset;
    mygames_kvm_u8 plane,first,x,y;
    static mygames_kvm_u8 MYGAMES_KVM_FAR slots[64];
    for(band=0U;band<240U;band=(mygames_kvm_u16)(band+16U)) {
        for(row=0U;row<16U;row=(mygames_kvm_u16)(row+8U))for(column=0U;column<32U;++column) {
            if(!marks[(band>>4U)*32U+column])continue;
            if(!mysmb_ppu_frame_background_rect(view,slots,sizeof(slots),
                (mygames_kvm_u8)(column*8U),(mygames_kvm_u8)(band+row),8U,8U))return 0;
            for(plane=0U;plane<4U;++plane) {
                first=retained_sprite_plane_first(viewport,(mygames_kvm_u8)(column*8U),plane);
                mygames_dos16_vga_plane(plane);
                for(y=0U;y<8U;++y) {
                    x=first;
                    offset=retained_offset(viewport,(mygames_kvm_u8)(column*8U+x),
                        (mygames_kvm_u8)(band+row+y));
                    video[offset]=slots[y*8U+x];
                    x=(mygames_kvm_u8)(first+4U);
                    offset=retained_offset(viewport,(mygames_kvm_u8)(column*8U+x),
                        (mygames_kvm_u8)(band+row+y));
                    video[offset]=slots[y*8U+x];
                }
            }
        }
    }
    return 1;
}
static void retained_draw_sprites(const struct retained_viewport *view,
    const struct retained_sprite_backup *items,mygames_kvm_u8 count)
{
    volatile unsigned char far *video=mygames_dos16_vga_memory();
    mygames_kvm_u16 n,py,offset;
    mygames_kvm_u8 plane,first,width,rows;
    for(n=0U;n<count;++n) {
        const struct retained_sprite_backup *item=&items[n];
        if(!item->active)continue;
        width=8U;if((mygames_kvm_u16)item->x+width>256U)width=(mygames_kvm_u8)(256U-item->x);
        rows=8U;if((mygames_kvm_u16)item->y+rows>240U)rows=(mygames_kvm_u8)(240U-item->y);
        for(plane=0U;plane<4U;++plane) {
            first=retained_sprite_plane_first(view,item->x,plane);mygames_dos16_vga_plane(plane);
            for(py=0U;py<rows;++py) {
                if(first<width && item->pixels[py*8U+first]!=255U) {
                    offset=retained_offset(view,(mygames_kvm_u8)(item->x+first),(mygames_kvm_u8)(item->y+py));
                    video[offset]=item->pixels[py*8U+first];
                }
                if(first+4U<width && item->pixels[py*8U+first+4U]!=255U) {
                    offset=retained_offset(view,(mygames_kvm_u8)(item->x+first+4U),(mygames_kvm_u8)(item->y+py));
                    video[offset]=item->pixels[py*8U+first+4U];
                }
            }
        }
    }
}
static int try_mode(mygames_kvm_u8 text)
{
    unsigned short i;
    palette_valid=0U;
    if(text)return mygames_dos16_text_mode(text_rows);
    if(!mygames_dos16_vga_bios_mode(0x13U))return 0;
    mygames_dos16_vga_native();
    for(i=0U;i<64U;++i)
        mygames_dos16_vga_color((unsigned char)i,mysmb_io_color_rgb((mygames_kvm_u8)i));
    return 1;
}
int mysmb_dos16_devices_mode(mygames_kvm_u8 text)
{
    if(!opened || !video_ready)return 0;
    text=(mygames_kvm_u8)(text!=0U);
    if(text==text_mode)return 1;
    if(try_mode(text)) {
        text_mode=text;retained_mode=0U;compact_mode=0U;ram_mode=0U;retained_hud_valid=0U;retained_sprite_count=0U;
        return 1;
    }
    /* A failed BIOS setup may already have changed the physical mode. */
    video_ready=(unsigned char)try_mode(text_mode);
    return 0;
}
void mysmb_dos16_devices_palette(const mygames_kvm_u8 MYGAMES_KVM_FAR *palette)
{
    unsigned short i;
    if(!video_ready || text_mode || !palette)return;
    for(i=0U;i<MYSMB_VIDEO_PALETTE_COLORS;++i){
        if(palette_valid && palette_shadow[i]==palette[i])continue;
        mygames_dos16_vga_color((unsigned char)i,mysmb_io_color_rgb(palette[i]));
        palette_shadow[i]=palette[i];
    }
    palette_valid=1U;
}
int mysmb_dos16_devices_open(void)
{
    if(opened)return video_ready;
    mygames_dos16_video_capture(&old_video);
    if(!try_mode(0U)) {mygames_dos16_video_restore(&old_video);return 0;}
    text_mode=0U;retained_mode=0U;compact_mode=0U;ram_mode=0U;retained_hud_valid=0U;retained_sprite_count=0U;video_ready=1U;
    mysmb_dos16_keyboard_initialize(&keyboard);
    if(!mygames_dos16_keyboard_open(keyboard_scan,&keyboard)) {
        mygames_dos16_video_restore(&old_video);video_ready=0U;return 0;
    }
    mysmb_io_pacing_initialize(&pacing,mygames_dos16_clock_stamp(),19886UL);
    /* Audio is independent of graphics/text mode.  An absent Sound Blaster is
     * nonfatal; S3 will make a prepared device audible. */
    (void)mysmb_dos16_audio_dos_open();
    present_due=1U;
    opened=1U;
    return 1;
}

void mysmb_dos16_devices_close(void)
{
    if (opened==0U) return;
    mysmb_dos16_audio_dos_close();
    mygames_dos16_keyboard_close();
    mygames_dos16_video_restore(&old_video);opened=video_ready=text_mode=retained_mode=compact_mode=ram_mode=retained_hud_valid=retained_sprite_count=0U;
}

void mysmb_dos16_devices_input(struct mysmb_io_input *input)
{
    _disable();
    mysmb_dos16_keyboard_input(&keyboard,input);
    if(!video_ready)input->requests|=MYSMB_IO_REQUEST_EXIT;
    _enable();
}

/* All validated plane transfers contain a multiple of four bytes.
 * USE16 addressing, DWORD operands only; original DOS segment ABI retained. */



int mysmb_dos16_devices_present_band(const struct mygames_kvm_video_band *band)
{
    unsigned char far *video;
    if(!video_ready || text_mode || !mygames_kvm_band_valid(band,240U) ||
        band->width!=256U || band->stride!=256U || band->rows>16U)return 0;
    video=mygames_dos16_vga_memory();
    /* A composition root may have written this exact logical band directly
     * to the chain-4 aperture. Keep the same synchronous ownership and
     * validation contract without copying it onto itself. */
    if(band->pixels==video+band->first*256U)return 1;
    /* Chain4 handles the plane selector/address from each CPU byte address.
     * Every band fits both segments;last source pixel is A000:EFFF. */
    mygames_dos16_copy_dwords(video+band->first*256U,band->pixels,band->rows*256U);
    return 1;
}
int mysmb_dos16_devices_present_screen(const mygames_kvm_u8 MYGAMES_KVM_FAR *screen)
{
    unsigned char far *video;
    if(!video_ready || text_mode || !screen)return 0;
    if(!ram_mode) {
        mygames_dos16_vga_native();ram_mode=1U;retained_mode=0U;compact_mode=0U;
        retained_hud_valid=0U;retained_sprite_count=0U;
    }
    video=mygames_dos16_vga_memory();
    mygames_dos16_copy_dwords(video,screen,MYSMB_VIDEO_PIXELS);
    return 1;
}
mygames_kvm_u8 MYGAMES_KVM_FAR *mysmb_dos16_devices_direct_band(mygames_kvm_u16 first,
    mygames_kvm_u16 rows)
{
    if(!video_ready || text_mode || !rows || first>=240U || rows>16U ||
        rows>240U-first)return 0;
    return mygames_dos16_vga_memory()+first*256U;
}
void mysmb_dos16_devices_text(const struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame)
{
    volatile unsigned short far *video;
    struct mygames_kvm_text_frame view;
    if(!video_ready || !text_mode || !frame)return;
    if(text_rows!=MYSMB_IO_TEXT_FRAME_ROWS(frame)) {
        text_rows=(unsigned short)MYSMB_IO_TEXT_FRAME_ROWS(frame);
        if(!try_mode(1U))return;
    }
    video=mygames_dos16_text_memory();
    mysmb_text_frame_view(frame,&view);
    mygames_dos16_text_cells(&view,video);
}

void mysmb_dos16_devices_wait(void)
{
    unsigned long now,elapsed;
    /* Move one logical deadline at a time.  If composition made this tick
     * late, following root steps catch up game/input/audio state without
     * composing stale images.  Rebasing here slows the game to the renderer.
     * The signed-half-range check also treats the BIOS midnight reset as a
     * new clock origin rather than a catch-up burst. */
    now=mygames_dos16_clock_stamp();
    elapsed=(now-pacing.last)&0xffffffffUL;
    if(elapsed>0x7fffffffUL)pacing.last=now;
    pacing.last=(pacing.last+pacing.period)&0xffffffffUL;
    now=mygames_dos16_clock_stamp();
    elapsed=(now-pacing.last)&0xffffffffUL;
    if(elapsed<=0x7fffffffUL) {present_due=0U;return;}
    do {
        now=mygames_dos16_clock_stamp();
        elapsed=(now-pacing.last)&0xffffffffUL;
    } while(elapsed>0x7fffffffUL);
    present_due=1U;
}
int mysmb_dos16_devices_should_present(void)
{
    return present_due!=0U;
}
void mysmb_dos16_devices_after_load(void)
{
    palette_valid=0U;
    /* A load may have taken long enough for physical DSP state to be lost;
     * this probe never changes game audio state or video presentation. */
    mysmb_dos16_audio_dos_after_load();
    _disable();mysmb_dos16_keyboard_after_load(&keyboard);_enable();
    mysmb_io_pacing_initialize(&pacing,mygames_dos16_clock_stamp(),19886UL);present_due=1U;
}
void mysmb_dos16_devices_resume_clock(void)
{mysmb_io_pacing_initialize(&pacing,mygames_dos16_clock_stamp(),19886UL);present_due=1U;}

int mysmb_dos16_devices_retained_background(const struct mysmb_ppu_frame_view *view)
{
    struct mysmb_ppu_scene_viewport viewport;
    if(!video_ready || text_mode || !mysmb_ppu_frame_scene_viewport(view,&viewport) ||
        !viewport.background_enabled || viewport.fixed_top)return 0;
    if(!retained_mode) {mygames_dos16_vga_planar512();retained_mode=1U;}
    if(!mysmb_dos16_retained_background_apply(view,vga_retained_tile_all,0))return 0;
    vga_retained_viewport(viewport.scene_page,viewport.output_origin_x,viewport.output_origin_y);
    return 1;
}

/* The PPU selects every pixel. DOS merely restores its former transient
 * coverage, applies cache-provided background changes, then records/draws
 * the current fixed HUD and descending OAM overlays. */
static int retained_frame_legacy(const struct mysmb_ppu_frame_view *view)
{
    struct mysmb_ppu_scene_viewport source;
    struct retained_viewport viewport;
    static mygames_kvm_u8 MYGAMES_KVM_FAR sprite_slots[64];
    struct retained_collect_context collect;
    mygames_kvm_u8 marks[15U*32U];
    if(!video_ready || text_mode || !mysmb_ppu_frame_scene_viewport(view,&source) ||
        !source.background_enabled)return 0;
    if(!retained_mode) {
        mygames_dos16_vga_planar512();retained_mode=1U;retained_hud_valid=0U;
        retained_sprite_count=0U;
    }
    /* The old sprite area is reconstructed from current PPU background below;
     * no prior VGA/background pixel is authoritative. */
    retained_restore_hud();
    retained_tile_plane=0xffU;
    if(!mysmb_dos16_retained_background_apply_planes(view,vga_retained_tile,0))goto fallback;
    retained_viewport_from(&source,&viewport);
    if(source.fixed_top && !retained_hud_rows(view,&viewport))goto fallback;
    memset(marks,0,sizeof(marks));
    retained_mark_sprite_tiles(retained_sprites,retained_sprite_count,marks);
    retained_next_count=0U;collect.items=retained_next_sprites;collect.count=&retained_next_count;
    if(!mysmb_ppu_frame_sprite_tiles(view,sprite_slots,sizeof(sprite_slots),
        retained_collect_sprite,&collect))goto fallback;
    retained_mark_sprite_tiles(retained_next_sprites,retained_next_count,marks);
    if(!retained_repaint_tiles(view,&viewport,marks))goto fallback;
    retained_draw_sprites(&viewport,retained_next_sprites,retained_next_count);
    memcpy(retained_sprites,retained_next_sprites,sizeof(retained_sprites));
    retained_sprite_count=retained_next_count;retained_sprite_view=viewport;
    vga_retained_viewport(viewport.table,viewport.x,viewport.y);
    return 1;
fallback:
    mygames_dos16_vga_native();retained_mode=0U;retained_hud_valid=0U;retained_sprite_count=0U;
    return 0;
}

/* A complete compact page is built before its CRTC start address changes.
 * This replaces the legacy visible-page restore/repaint path but consumes the
 * same immutable PPU view and changed-tile feed. */
int mysmb_dos16_devices_retained_frame(const struct mysmb_ppu_frame_view *view)
{
    struct mysmb_ppu_scene_viewport source;
    struct retained_viewport viewport;
    struct compact_sprite_context sprites;
    static mygames_kvm_u8 MYGAMES_KVM_FAR sprite_slots[64];
    mygames_kvm_u8 page,pan;
    if(!video_ready || text_mode || !mysmb_ppu_frame_scene_viewport(view,&source) ||
        !source.background_enabled)return 0;
    if(!compact_mode) {
        mygames_dos16_vga_planar264(MYSMB_DOS16_COMPACT_PAGE_A);compact_mode=1U;compact_page=0U;
    }
    retained_tile_plane=0xffU;
    if(!mysmb_dos16_retained_background_apply_planes(view,vga_compact_tile,0))goto fallback;
    retained_viewport_from(&source,&viewport);
    page=(mygames_kvm_u8)(compact_page^1U);
    if(!vga_compact_copy_viewport(&viewport,page))goto fallback;
    pan=(mygames_kvm_u8)(viewport.x&7U);
    if(source.fixed_top) {
        if(!mysmb_ppu_frame_background_rows(view,retained_hud_slots,
            sizeof(retained_hud_slots),0U,32U))goto fallback;
        compact_write_hud(page,pan,retained_hud_slots);
    }
    sprites.page=page;sprites.pan=pan;
    if(!mysmb_ppu_frame_sprite_tiles(view,sprite_slots,sizeof(sprite_slots),
        compact_draw_sprite,&sprites))goto fallback;
    vga_compact_viewport(page,pan);compact_page=page;retained_mode=0U;
    return 1;
fallback:
    /* The neutral row presenter remains the safe output fallback.  It will
     * reconfigure the adapter through its ordinary native-row path. */
    compact_mode=0U;retained_mode=0U;retained_hud_valid=0U;retained_sprite_count=0U;
    return retained_frame_legacy(view);
}

mygames_kvm_u8 mysmb_dos16_devices_audio(const struct mysmb_io_audio_frame *frame)
{
    return mysmb_dos16_audio_dos_submit(frame);
}
