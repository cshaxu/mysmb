#include "platform/dos16/devices.h"
#include "platform/dos16/retained_background.h"
#include "platform/dos16/keyboard.h"
#include "platform/dos16/pit_clock.h"
#include "ppu/frame.h"
#include "io/color.h"
#include "io/pacing.h"
#include <dos.h>
#include <conio.h>
#include <string.h>

static struct mysmb_dos16_keyboard keyboard;
static void (interrupt far *old_keyboard)();
static unsigned char old_mode;
static unsigned char old_rows;
static unsigned char old_font;
static unsigned short old_cursor;
static unsigned char video_ready;
static struct mysmb_io_pacing pacing;
static unsigned char opened;
static unsigned char text_mode;
static unsigned short text_rows=25U;
static unsigned char text_colors[16];
static mysmb_io_u8 palette_shadow[MYSMB_IO_VIDEO_PALETTE_COLORS],palette_valid;
static unsigned char retained_mode;
struct retained_viewport {mysmb_io_u8 table,x,y;};
struct retained_sprite_backup {mysmb_io_u8 x,y,active,pixels[64];};
/* Bounded transient coverage only: 32*256 fixed-HUD bytes plus at most
 * 64 complete 8-by-8 sprite rectangles. No conventional full frame. */
/* The two 32-by-256 transient HUD surfaces remain bounded at 8KiB each.
 * They are packed in physical-plane order after PPU selection, so restore and
 * redraw can use contiguous VGA spans instead of 16,384 pixel address walks. */
static mysmb_io_u8 retained_hud[8192],retained_hud_slots[8192],retained_hud_valid;
static mysmb_io_u8 retained_hud_line[256];
static mysmb_io_u8 retained_tile_plane;
static struct retained_viewport retained_hud_view;
static struct retained_sprite_backup retained_sprites[64];
static struct retained_sprite_backup MYSMB_IO_FAR retained_next_sprites[64];
static mysmb_io_u8 retained_sprite_count,retained_next_count;
/* PPU-owned source rows plus one temporary OAM tile. This replaces slow VGA
 * plane readback; it is bounded transient overlay storage, not a frame. */
/* All sprites captured in one presentation share this PPU-selected viewport.
 * Keep it until their reverse restoration during the next presentation. */
static struct retained_viewport retained_sprite_view;

/* The physical VGA adapter owns this byte move.  It is intentionally below
 * all PPU decisions: callers already selected the source slots and target
 * plane.  The byte tail handles the viewport's possible 128-byte wrap. */
static void copy_plane_bytes(unsigned char far *video,
    const unsigned char far *pixels,unsigned short count)
{
    _asm {
        push ds
        push es
        push bx
        lds si,pixels
        les di,video
        mov cx,count
        mov bx,cx
        shr cx,1
        shr cx,1
        cld
        _emit 0x66
        rep movsw
        mov cx,bx
        and cx,3
        rep movsb
        pop bx
        pop es
        pop ds
    }
}

static void interrupt far keyboard_interrupt(void)
{
    unsigned char scan, control;
    scan=(unsigned char)inp(0x60);
    control=(unsigned char)inp(0x61);
    outp(0x61,control|0x80U);
    outp(0x61,control);
    mysmb_dos16_keyboard_scan(&keyboard,scan);
    outp(0x20,0x20);
}

/* Latch BIOS-owned PIT channel zero; never change its rate or IRQ vector. */
static unsigned long timer_stamp(void)
{
    unsigned short low, high, phase;
    unsigned int attempt;
    unsigned char status;
    unsigned long ticks;
    volatile unsigned long far *bios_ticks;
    bios_ticks=(volatile unsigned long far *)0x0040006cUL;
    _disable();
    /* A zero reload count at an OUT transition is ambiguous in a sampled
     * read-back. Recapture the whole BIOS/PIT pair;never change its rate.
     * Bound interrupt-disabled work even if the device stops advancing. */
    for(attempt=0U;attempt<4U;++attempt) {
        ticks=*bios_ticks;
        outp(0x43,0xc2U);
        status=(unsigned char)inp(0x40);
        low=(unsigned short)inp(0x40);
        high=(unsigned short)inp(0x40);
        if((low|(high<<8U))!=0U)break;
    }
    phase=mysmb_dos16_pit_phase(status,(unsigned short)(low|(high<<8U)));
    /* A latched high count plus pending IRQ0 means a wrap not yet reflected
     * in the BIOS count. Leave the timer vector/rate and clock untouched. */
    outp(0x20,0x0aU);
    if ((inp(0x20)&1U)!=0U && phase<32768U) ++ticks;
    _enable();
    return (ticks<<16U)+phase;
}

/* Independent native256x240 timing:25.175MHz,800dots/525lines,approximately
 * 60Hz. VGA repeats each stored row twice;chain4 exposes61440linear bytes.
 * BIOS13h supplies initial graphics/attribute state;restore uses original mode. */
static void vga_register(unsigned short port,unsigned char index,unsigned char value)
{ outp(port,index);outp((unsigned short)(port+1U),value); }
static void vga_native_rows(void)
{
    unsigned char protect;
    vga_register(0x3c4,0,1);
    outp(0x3c2,0xe3);
    vga_register(0x3c4,4,14);
    outp(0x3d4,17);protect=(unsigned char)inp(0x3d5);
    vga_register(0x3d4,17,(unsigned char)(protect&0x7fU));
    vga_register(0x3d4,1,63);vga_register(0x3d4,2,64);
    vga_register(0x3d4,6,13);vga_register(0x3d4,7,62);
    vga_register(0x3d4,9,65);
    vga_register(0x3d4,16,234);vga_register(0x3d4,17,44);
    vga_register(0x3d4,18,223);vga_register(0x3d4,19,32);
    vga_register(0x3d4,20,64);
    vga_register(0x3d4,21,231);vga_register(0x3d4,22,6);
    vga_register(0x3d4,23,0xa3);
    vga_register(0x3c4,2,15);
    vga_register(0x3c4,0,3);
}
/* The S5-proven unchained timing is retained here but not selected by the
 * ordinary presenter. S8 must first restore/draw HUD and sprites. */
static void vga_retained_rows(void)
{
    unsigned char protect;
    vga_register(0x3c4,0,1);outp(0x3c2,0xe3);vga_register(0x3c4,4,6);
    outp(0x3d4,17);protect=(unsigned char)inp(0x3d5);
    vga_register(0x3d4,17,(unsigned char)(protect&0x7fU));
    vga_register(0x3d4,1,63);vga_register(0x3d4,2,64);
    vga_register(0x3d4,6,13);vga_register(0x3d4,7,62);
    vga_register(0x3d4,9,65);vga_register(0x3d4,16,234);
    vga_register(0x3d4,17,44);vga_register(0x3d4,18,223);
    vga_register(0x3d4,19,64);vga_register(0x3d4,20,64);
    vga_register(0x3d4,21,231);vga_register(0x3d4,22,6);
    vga_register(0x3d4,23,0xa3);vga_register(0x3d4,24,255);
    vga_register(0x3d4,12,0);vga_register(0x3d4,13,0);
    (void)inp(0x3da);outp(0x3c0,19);outp(0x3c0,0);outp(0x3c0,0x20);
    vga_register(0x3c4,2,15);vga_register(0x3c4,0,3);
}
static void vga_retained_plane(unsigned char plane)
{vga_register(0x3c4,2,(unsigned char)(1U<<plane));}
static int vga_retained_tile(void *context,mysmb_io_u8 plane,mysmb_io_u8 table,
    mysmb_io_u8 row,mysmb_io_u8 column,const mysmb_io_u8 MYSMB_IO_FAR *slots)
{
    volatile unsigned char far *video=(volatile unsigned char far *)0xa0000000UL;
    unsigned char copy,expected;
    unsigned short base,y;
    (void)context;
    if(!slots)return 0;
    if(retained_tile_plane!=plane) {
        vga_retained_plane(plane);retained_tile_plane=plane;
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
static int vga_retained_tile_all(void *context,mysmb_io_u8 table,mysmb_io_u8 row,
    mysmb_io_u8 column,const mysmb_io_u8 MYSMB_IO_FAR *slots)
{
    mysmb_io_u8 plane;
    retained_tile_plane=0xffU;
    for(plane=0U;plane<4U;++plane)
        if(!vga_retained_tile(context,plane,table,row,column,slots))return 0;
    return 1;
}
static void vga_retained_viewport(mysmb_io_u8 table,mysmb_io_u8 x,mysmb_io_u8 y)
{
    unsigned short source=(unsigned short)((unsigned short)table*256U+x);
    unsigned short start=(unsigned short)((unsigned short)y*64U+(source>>3U));
    vga_register(0x3d4,12,(unsigned char)(start>>8U));
    vga_register(0x3d4,13,(unsigned char)start);
    (void)inp(0x3da);outp(0x3c0,19);outp(0x3c0,(unsigned char)(source&7U));outp(0x3c0,0x20);
}
static void retained_viewport_from(const struct mysmb_ppu_scene_viewport *source,
    struct retained_viewport *target)
{
    target->table=source->scene_page;target->x=source->output_origin_x;target->y=source->output_origin_y;
    if(target->y>=240U)target->y=(mysmb_io_u8)(target->y-240U);
}
static mysmb_io_u16 retained_offset(const struct retained_viewport *view,
    mysmb_io_u8 x,mysmb_io_u8 y)
{
    mysmb_io_u16 physical_x=(mysmb_io_u16)view->table*256U+view->x+x;
    mysmb_io_u16 physical_y=(mysmb_io_u16)view->y+y;
    if(physical_x>=512U)physical_x=(mysmb_io_u16)(physical_x-512U);
    return (mysmb_io_u16)(physical_y*MYSMB_DOS16_RETAINED_STRIDE+(physical_x>>2U));
}
static mysmb_io_u8 retained_plane(const struct retained_viewport *view,mysmb_io_u8 x)
{
    return (mysmb_io_u8)((view->table*256U+view->x+x)&3U);
}
/* A plane owns two positions in each complete 8-pixel sprite row. */
static mysmb_io_u8 retained_sprite_plane_first(const struct retained_viewport *view,
    mysmb_io_u8 x,mysmb_io_u8 plane)
{return (mysmb_io_u8)((plane+4U-retained_plane(view,x))&3U);}

/* Convert one neutral 32-row source into the same physical plane/order that
 * the current viewport addresses.  The source is still PPU-owned; this is
 * only the transient VGA layout used by the next restore or HUD write. */
static void retained_hud_pack(const struct retained_viewport *view,
    const mysmb_io_u8 MYSMB_IO_FAR *source,mysmb_io_u8 MYSMB_IO_FAR *packed)
{
    mysmb_io_u16 y,i;
    mysmb_io_u8 plane,first;
    for(plane=0U;plane<4U;++plane) {
        first=retained_sprite_plane_first(view,0U,plane);
        for(y=0U;y<32U;++y)for(i=0U;i<64U;++i)
            packed[plane*2048U+y*64U+i]=source[y*256U+first+i*4U];
    }
}

/* One logical 256-pixel line is 64 bytes in each plane.  It can cross the
 * retained 512-pixel row boundary once, never a scanline or PPU boundary. */
static void retained_hud_write_plane(const struct retained_viewport *view,
    mysmb_io_u8 plane,const mysmb_io_u8 MYSMB_IO_FAR *packed)
{
    volatile unsigned char far *video=(volatile unsigned char far *)0xa0000000UL;
    mysmb_io_u16 y,offset,first_count,second_count,physical;
    mysmb_io_u8 first;
    first=retained_sprite_plane_first(view,0U,plane);
    physical=(mysmb_io_u16)view->table*256U+view->x+first;
    if(physical>=512U)physical=(mysmb_io_u16)(physical-512U);
    offset=(mysmb_io_u16)(physical>>2U);
    first_count=(mysmb_io_u16)(128U-offset);
    if(first_count>64U)first_count=64U;
    second_count=(mysmb_io_u16)(64U-first_count);
    vga_retained_plane(plane);
    for(y=0U;y<32U;++y) {
        const mysmb_io_u8 MYSMB_IO_FAR *source=packed+plane*2048U+y*64U;
        copy_plane_bytes((unsigned char far *)video+y*128U+offset,source,first_count);
        if(second_count)copy_plane_bytes((unsigned char far *)video+y*128U,
            source+first_count,second_count);
    }
}
static void retained_hud_write_line(const struct retained_viewport *view,
    mysmb_io_u8 plane,mysmb_io_u16 y,const mysmb_io_u8 MYSMB_IO_FAR *source)
{
    volatile unsigned char far *video=(volatile unsigned char far *)0xa0000000UL;
    mysmb_io_u16 offset,first_count,second_count,physical;
    mysmb_io_u8 first=retained_sprite_plane_first(view,0U,plane);
    physical=(mysmb_io_u16)view->table*256U+view->x+first;
    if(physical>=512U)physical=(mysmb_io_u16)(physical-512U);
    offset=(mysmb_io_u16)(physical>>2U);
    first_count=(mysmb_io_u16)(128U-offset);if(first_count>64U)first_count=64U;
    second_count=(mysmb_io_u16)(64U-first_count);
    vga_retained_plane(plane);
    copy_plane_bytes((unsigned char far *)video+y*128U+offset,source,first_count);
    if(second_count)copy_plane_bytes((unsigned char far *)video+y*128U,source+first_count,second_count);
}
static void retained_restore_hud(void)
{
    mysmb_io_u8 plane;
    if(!retained_hud_valid)return;
    for(plane=0U;plane<4U;++plane)
        retained_hud_write_plane(&retained_hud_view,plane,retained_hud);
    retained_hud_valid=0U;
}
static int retained_hud_rows(const struct mysmb_ppu_frame_view *view,
    const struct retained_viewport *viewport)
{
    mysmb_io_u8 plane;
    /* Save the PPU-selected scrollable scene, not a VGA readback.  It is the
     * exact surface covered by the fixed HUD and is restored next frame at
     * the old viewport. */
    if(!mysmb_ppu_frame_scene_rows(view,retained_hud_slots,sizeof(retained_hud_slots),0U,32U))return 0;
    retained_hud_pack(viewport,retained_hud_slots,retained_hud);
    if(!mysmb_ppu_frame_background_rows(view,retained_hud_slots,sizeof(retained_hud_slots),0U,32U))return 0;
    /* One line is packed and committed before the scratch is reused.  This
     * avoids aliasing the raw 256-byte rows with their planar layout. */
    for(plane=0U;plane<4U;++plane) {
        mysmb_io_u16 y,i;
        mysmb_io_u8 first=retained_sprite_plane_first(viewport,0U,plane);
        for(y=0U;y<32U;++y) {
            for(i=0U;i<64U;++i)retained_hud_line[i]=retained_hud_slots[y*256U+first+i*4U];
            retained_hud_write_line(viewport,plane,y,retained_hud_line);
        }
    }
    retained_hud_view=*viewport;retained_hud_valid=1U;return 1;
}
struct retained_collect_context {struct retained_sprite_backup *items;mysmb_io_u8 *count;};
static int retained_collect_sprite(void *context,mysmb_io_u8 sprite,mysmb_io_u8 x,
    mysmb_io_u8 y,const mysmb_io_u8 MYSMB_IO_FAR *slots)
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
    mysmb_io_u8 count,mysmb_io_u8 *marks)
{
    mysmb_io_u16 n,y,last,column,last_column;
    for(n=0U;n<count;++n) {
        if(!items[n].active)continue;
        column=(mysmb_io_u16)(items[n].x>>3U);last_column=(mysmb_io_u16)((items[n].x+7U)>>3U);
        y=items[n].y;last=(mysmb_io_u16)y+7U;if(last>=240U)last=239U;
        for(;y<=last;++y) {
            mysmb_io_u16 band=(mysmb_io_u16)(y>>4U);
            marks[band*32U+column]=1U;marks[band*32U+last_column]=1U;
        }
    }
}
static int retained_repaint_tiles(const struct mysmb_ppu_frame_view *view,
    const struct retained_viewport *viewport,const mysmb_io_u8 *marks)
{
    volatile unsigned char far *video=(volatile unsigned char far *)0xa0000000UL;
    mysmb_io_u16 band,row,column,offset;
    mysmb_io_u8 plane,first,x,y;
    static mysmb_io_u8 MYSMB_IO_FAR slots[64];
    for(band=0U;band<240U;band=(mysmb_io_u16)(band+16U)) {
        for(row=0U;row<16U;row=(mysmb_io_u16)(row+8U))for(column=0U;column<32U;++column) {
            if(!marks[(band>>4U)*32U+column])continue;
            if(!mysmb_ppu_frame_background_rect(view,slots,sizeof(slots),
                (mysmb_io_u8)(column*8U),(mysmb_io_u8)(band+row),8U,8U))return 0;
            for(plane=0U;plane<4U;++plane) {
                first=retained_sprite_plane_first(viewport,(mysmb_io_u8)(column*8U),plane);
                vga_retained_plane(plane);
                for(y=0U;y<8U;++y) {
                    x=first;
                    offset=retained_offset(viewport,(mysmb_io_u8)(column*8U+x),
                        (mysmb_io_u8)(band+row+y));
                    video[offset]=slots[y*8U+x];
                    x=(mysmb_io_u8)(first+4U);
                    offset=retained_offset(viewport,(mysmb_io_u8)(column*8U+x),
                        (mysmb_io_u8)(band+row+y));
                    video[offset]=slots[y*8U+x];
                }
            }
        }
    }
    return 1;
}
static void retained_draw_sprites(const struct retained_viewport *view,
    const struct retained_sprite_backup *items,mysmb_io_u8 count)
{
    volatile unsigned char far *video=(volatile unsigned char far *)0xa0000000UL;
    mysmb_io_u16 n,py,offset;
    mysmb_io_u8 plane,first,width,rows;
    for(n=0U;n<count;++n) {
        const struct retained_sprite_backup *item=&items[n];
        if(!item->active)continue;
        width=8U;if((mysmb_io_u16)item->x+width>256U)width=(mysmb_io_u8)(256U-item->x);
        rows=8U;if((mysmb_io_u16)item->y+rows>240U)rows=(mysmb_io_u8)(240U-item->y);
        for(plane=0U;plane<4U;++plane) {
            first=retained_sprite_plane_first(view,item->x,plane);vga_retained_plane(plane);
            for(py=0U;py<rows;++py) {
                if(first<width && item->pixels[py*8U+first]!=255U) {
                    offset=retained_offset(view,(mysmb_io_u8)(item->x+first),(mysmb_io_u8)(item->y+py));
                    video[offset]=item->pixels[py*8U+first];
                }
                if(first+4U<width && item->pixels[py*8U+first+4U]!=255U) {
                    offset=retained_offset(view,(mysmb_io_u8)(item->x+first+4U),(mysmb_io_u8)(item->y+py));
                    video[offset]=item->pixels[py*8U+first+4U];
                }
            }
        }
    }
}
static int try_mode(mysmb_io_u8 text)
{
    union REGS registers;
    unsigned short i;
    unsigned long rgb;
    palette_valid=0U;
    if(text) {
        registers.x.ax=0x1202U;registers.x.bx=0x30U;
        int86(0x10,&registers,&registers);
        registers.x.ax=3U;int86(0x10,&registers,&registers);
        registers.x.ax=text_rows==50U?0x1112U:0x1114U;registers.x.bx=0U;
        int86(0x10,&registers,&registers);
        registers.x.ax=0x1003U;registers.x.bx=0U;
        int86(0x10,&registers,&registers);
        registers.h.ah=1U;registers.h.ch=0x20U;registers.h.cl=0U;
        int86(0x10,&registers,&registers);
        registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
        return registers.h.al==3U && registers.h.ah==80U &&
            *(volatile unsigned char far *)0x00400084UL==(unsigned char)(text_rows-1U);
    }
    registers.h.ah=0U;
    registers.h.al=0x13U;
    int86(0x10,&registers,&registers);
    registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
    if(registers.h.al!=0x13U)return 0;
    vga_native_rows();
    outp(0x3c8,0U);
    for (i=0U;i<64U;++i) {
        rgb=mysmb_io_color_rgb((mysmb_io_u8)i);
        outp(0x3c9,(unsigned char)((rgb>>18U)&0x3fU));
        outp(0x3c9,(unsigned char)((rgb>>10U)&0x3fU));
        outp(0x3c9,(unsigned char)((rgb>>2U)&0x3fU));
    }
    return 1;
}
int mysmb_dos16_devices_mode(mysmb_io_u8 text)
{
    if(!opened || !video_ready)return 0;
    text=(mysmb_io_u8)(text!=0U);
    if(text==text_mode)return 1;
    if(try_mode(text)) {
        text_mode=text;retained_mode=0U;retained_hud_valid=0U;retained_sprite_count=0U;
        return 1;
    }
    /* A failed BIOS setup may already have changed the physical mode. */
    video_ready=(unsigned char)try_mode(text_mode);
    return 0;
}
void mysmb_dos16_devices_palette(const mysmb_io_u8 MYSMB_IO_FAR *palette)
{
    unsigned short i;unsigned long rgb;
    if(!video_ready || text_mode || !palette)return;
    for(i=0U;i<MYSMB_IO_VIDEO_PALETTE_COLORS;++i){
        if(palette_valid && palette_shadow[i]==palette[i])continue;
        rgb=mysmb_io_color_rgb(palette[i]);outp(0x3c8,i);
        outp(0x3c9,(unsigned char)((rgb>>18U)&63UL));
        outp(0x3c9,(unsigned char)((rgb>>10U)&63UL));
        outp(0x3c9,(unsigned char)((rgb>>2U)&63UL));
        palette_shadow[i]=palette[i];
    }
    palette_valid=1U;
}
static void restore_video(void)
{
    union REGS registers;
    if(old_mode<=3U || old_mode==7U) {
        /* 43 eight-pixel rows occupy344 of the350 scanlines. */
        registers.x.ax=(unsigned short)((old_rows+1U)*old_font>350U?0x1202U:
            (old_rows+1U)*old_font>200U?0x1201U:0x1200U);
        registers.x.bx=0x30U;int86(0x10,&registers,&registers);
    }
    registers.h.ah=0U;registers.h.al=old_mode;
    int86(0x10,&registers,&registers);
    if(old_mode<=3U || old_mode==7U) {
        if(old_font==8U || old_font==14U || old_font==16U) {
            registers.x.ax=old_font==8U?0x1112U:old_font==14U?0x1111U:0x1114U;
            registers.x.bx=0U;int86(0x10,&registers,&registers);
        }
        registers.h.ah=1U;registers.x.cx=old_cursor;
        int86(0x10,&registers,&registers);
    }
}
int mysmb_dos16_devices_open(void)
{
    union REGS registers;
    if(opened)return video_ready;
    registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
    old_mode=registers.h.al;
    old_rows=*(volatile unsigned char far *)0x00400084UL;
    old_font=*(volatile unsigned char far *)0x00400085UL;
    registers.h.ah=3U;registers.h.bh=0U;
    int86(0x10,&registers,&registers);old_cursor=registers.x.cx;
    if(!try_mode(0U)) {restore_video();return 0;}
    text_mode=0U;retained_mode=0U;retained_hud_valid=0U;retained_sprite_count=0U;video_ready=1U;
    mysmb_dos16_keyboard_initialize(&keyboard);
    old_keyboard=_dos_getvect(9U);
    _dos_setvect(9U,keyboard_interrupt);
    mysmb_io_pacing_initialize(&pacing,timer_stamp(),19886UL);
    opened=1U;
    return 1;
}

void mysmb_dos16_devices_close(void)
{
    if (opened==0U) return;
    _dos_setvect(9U,old_keyboard);
    restore_video();opened=video_ready=text_mode=retained_mode=retained_hud_valid=retained_sprite_count=0U;
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
static void copy_plane_dwords(unsigned char far *video,
    const unsigned char far *pixels,unsigned short count)
{
    _asm {
        push ds
        push es
        lds si,pixels
        les di,video
        mov cx,count
        shr cx,1
        shr cx,1
        cld
        _emit 0x66
        rep movsw
        pop es
        pop ds
    }
}


int mysmb_dos16_devices_present_band(const struct mysmb_io_video_band *band)
{
    unsigned char far *video;
    if(!video_ready || text_mode || !band || !band->pixels || !band->rows ||
        band->first>=240U || band->rows>16U || band->rows>240U-band->first)return 0;
    video=(unsigned char far *)0xa0000000UL;
    /* A composition root may have written this exact logical band directly
     * to the chain-4 aperture. Keep the same synchronous ownership and
     * validation contract without copying it onto itself. */
    if(band->pixels==video+band->first*256U)return 1;
    /* Chain4 handles the plane selector/address from each CPU byte address.
     * Every band fits both segments;last source pixel is A000:EFFF. */
    copy_plane_dwords(video+band->first*256U,band->pixels,band->rows*256U);
    return 1;
}
mysmb_io_u8 MYSMB_IO_FAR *mysmb_dos16_devices_direct_band(mysmb_io_u16 first,
    mysmb_io_u16 rows)
{
    if(!video_ready || text_mode || !rows || first>=240U || rows>16U ||
        rows>240U-first)return 0;
    return (mysmb_io_u8 MYSMB_IO_FAR *)0xa0000000UL+first*256U;
}
void mysmb_dos16_devices_text(const struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{
    unsigned short i;
    volatile unsigned short far *video;
    if(!video_ready || !text_mode || !frame)return;
    if(text_rows!=MYSMB_IO_TEXT_FRAME_ROWS(frame)) {
        text_rows=(unsigned short)MYSMB_IO_TEXT_FRAME_ROWS(frame);
        if(!try_mode(1U))return;
    }
    for(i=0U;i<16U;++i)
        text_colors[i]=mysmb_io_color_text_nearest(frame->colors[i]);
    video=(volatile unsigned short far *)0xb8000000UL;
    for(i=0U;i<MYSMB_IO_TEXT_FRAME_CELLS(frame);++i)
        video[i]=(unsigned short)(frame->cells[i].character|
            ((unsigned short)text_colors[frame->cells[i].foreground&15U]<<8U)|
            ((unsigned short)text_colors[frame->cells[i].background&15U]<<12U));
}

void mysmb_dos16_devices_wait(void)
{
    while (mysmb_io_pacing_remaining(&pacing,timer_stamp())!=0UL) { }
}
void mysmb_dos16_devices_after_load(void)
{
    palette_valid=0U;
    _disable();mysmb_dos16_keyboard_after_load(&keyboard);_enable();
    mysmb_io_pacing_initialize(&pacing,timer_stamp(),19886UL);
}
void mysmb_dos16_devices_resume_clock(void)
{mysmb_io_pacing_initialize(&pacing,timer_stamp(),19886UL);}

int mysmb_dos16_devices_retained_background(const struct mysmb_ppu_frame_view *view)
{
    struct mysmb_ppu_scene_viewport viewport;
    if(!video_ready || text_mode || !mysmb_ppu_frame_scene_viewport(view,&viewport) ||
        !viewport.background_enabled || viewport.fixed_top)return 0;
    if(!retained_mode) {vga_retained_rows();retained_mode=1U;}
    if(!mysmb_dos16_retained_background_apply(view,vga_retained_tile_all,0))return 0;
    vga_retained_viewport(viewport.scene_page,viewport.output_origin_x,viewport.output_origin_y);
    return 1;
}

/* The PPU selects every pixel. DOS merely restores its former transient
 * coverage, applies cache-provided background changes, then records/draws
 * the current fixed HUD and descending OAM overlays. */
int mysmb_dos16_devices_retained_frame(const struct mysmb_ppu_frame_view *view)
{
    struct mysmb_ppu_scene_viewport source;
    struct retained_viewport viewport;
    static mysmb_io_u8 MYSMB_IO_FAR sprite_slots[64];
    struct retained_collect_context collect;
    mysmb_io_u8 marks[15U*32U];
    if(!video_ready || text_mode || !mysmb_ppu_frame_scene_viewport(view,&source) ||
        !source.background_enabled)return 0;
    if(!retained_mode) {
        vga_retained_rows();retained_mode=1U;retained_hud_valid=0U;
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
    vga_native_rows();retained_mode=0U;retained_hud_valid=0U;retained_sprite_count=0U;
    return 0;
}

mysmb_io_u8 mysmb_dos16_devices_audio(const struct mysmb_io_audio_frame *frame)
{
    /* No DOS sound hardware adapter is installed;never claim audible output. */
    (void)frame;
    return MYSMB_IO_AUDIO_UNAVAILABLE;
}
