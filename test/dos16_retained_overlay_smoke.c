#include "platform/dos16/retained_background.h"
#include "ppu/frame.h"
#include <stdio.h>
#include <string.h>

/* Host-side exact model of the bounded DOS retained surface.  It deliberately
 * uses the same public PPU descriptors as devices.c and never reads PPU state
 * while restoring an old presentation. */
struct viewport { mysmb_io_u8 page,x,y; };
struct sprite_backup { mysmb_io_u8 x,y,pixels[64]; };
static mysmb_io_u8 surface[480][512],hud[8192],chr[8192];
static mysmb_io_u8 expected[61440],scratch[256],sprite_slots[64];
static struct viewport hud_view,sprite_view,current;
static struct sprite_backup sprites[64];
static mysmb_io_u8 hud_valid,sprite_count;

static void point(const struct viewport *v,mysmb_io_u8 x,mysmb_io_u8 y,
    mysmb_io_u16 *px,mysmb_io_u16 *py)
{
    *px=(mysmb_io_u16)(v->page*256U+v->x+x);if(*px>=512U)*px-=512U;
    *py=(mysmb_io_u16)(v->y+y);
}
static void restore(void)
{
    mysmb_io_u16 x,y,px,py;struct sprite_backup *s;
    while(sprite_count) {
        s=&sprites[--sprite_count];
        for(y=0U;y<8U && s->y+y<240U;++y)for(x=0U;x<8U && s->x+x<256U;++x) {
            point(&sprite_view,(mysmb_io_u8)(s->x+x),(mysmb_io_u8)(s->y+y),&px,&py);
            surface[py][px]=s->pixels[y*8U+x];
        }
    }
    if(hud_valid) {
        for(y=0U;y<32U;++y)for(x=0U;x<256U;++x) {
            point(&hud_view,(mysmb_io_u8)x,(mysmb_io_u8)y,&px,&py);
            surface[py][px]=hud[y*256U+x];
        }
        hud_valid=0U;
    }
}
static int tile(void *context,mysmb_io_u8 table,mysmb_io_u8 row,
    mysmb_io_u8 column,const mysmb_io_u8 MYSMB_IO_FAR *slots)
{
    mysmb_io_u16 copy,x,y,px,py;
    (void)context;
    for(copy=0U;copy<2U;++copy)for(y=0U;y<8U;++y)for(x=0U;x<8U;++x) {
        px=(mysmb_io_u16)(table*256U+column*8U+x);
        py=(mysmb_io_u16)(copy*240U+row*8U+y);
        surface[py][px]=slots[y*8U+x];
    }
    return 1;
}
static int sprite(void *context,mysmb_io_u8 index,mysmb_io_u8 x,mysmb_io_u8 y,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *slots)
{
    struct sprite_backup *s;mysmb_io_u16 px,py,tx,ty;
    (void)context;(void)index;
    if(sprite_count>=64U)return 0;
    s=&sprites[sprite_count++];s->x=x;s->y=y;
    for(ty=0U;ty<8U && y+ty<240U;++ty)for(tx=0U;tx<8U && x+tx<256U;++tx) {
        point(&current,(mysmb_io_u8)(x+tx),(mysmb_io_u8)(y+ty),&px,&py);
        s->pixels[ty*8U+tx]=surface[py][px];
        if(slots[ty*8U+tx]!=255U)surface[py][px]=slots[ty*8U+tx];
    }
    return 1;
}
static int frame(struct mysmb_ppu_state *state,struct mysmb_ppu_frame_workspace *work)
{
    struct mysmb_ppu_frame_view view;struct mysmb_ppu_scene_viewport scene;
    mysmb_io_u16 x,y,px,py;
    mysmb_ppu_frame_begin(state,work,&view);restore();
    if(!mysmb_dos16_retained_background_apply(&view,tile,0) ||
        !mysmb_ppu_frame_scene_viewport(&view,&scene))return 0;
    current.page=scene.scene_page;current.x=scene.output_origin_x;current.y=scene.output_origin_y;
    if(current.y>=240U)current.y=(mysmb_io_u8)(current.y-240U);
    if(scene.fixed_top) {
        for(y=0U;y<32U;++y) {
            if(!mysmb_ppu_frame_background_rows(&view,scratch,sizeof(scratch),y,1U))return 0;
            for(x=0U;x<256U;++x) {
                point(&current,(mysmb_io_u8)x,(mysmb_io_u8)y,&px,&py);
                hud[y*256U+x]=surface[py][px];surface[py][px]=scratch[x];
            }
        }
        hud_view=current;hud_valid=1U;
    }
    sprite_view=current;
    if(!mysmb_ppu_frame_sprite_tiles(&view,sprite_slots,sizeof(sprite_slots),sprite,0) ||
        !mysmb_ppu_frame_slot_rows(&view,expected,sizeof(expected),0U,240U))return 0;
    for(y=0U;y<240U;++y)for(x=0U;x<256U;++x) {
        point(&current,(mysmb_io_u8)x,(mysmb_io_u8)y,&px,&py);
        if(surface[py][px]!=expected[y*256U+x])return 0;
    }
    mysmb_ppu_frame_end(&view);return 1;
}
int main(void)
{
    struct mysmb_ppu_state state;struct mysmb_ppu_frame_workspace work;
    static mysmb_io_u8 background[MYSMB_PPU_BACKGROUND_BYTES];
    static mysmb_io_u8 second[MYSMB_PPU_BACKGROUND_SECOND_BYTES];
    mysmb_io_u16 i;
    memset(&state,0,sizeof(state));
    for(i=0U;i<8192U;++i)chr[i]=(mysmb_io_u8)(i*11U+i/7U);
    for(i=0U;i<2048U;++i)state.name_table[i/1024U][i&1023U]=(mysmb_io_u8)(i*3U);
    state.chr_data=chr;state.chr_data_size=sizeof(chr);state.visible_ppu_mask=30U;
    state.visible_sprite0_split=1U;state.visible_ppu_name_table=1U;
    state.visible_scroll_x=19U;state.visible_scroll_y=23U;memset(state.visible_oam,0xefU,sizeof(state.visible_oam));
    state.visible_oam[0]=76U;state.visible_oam[1]=9U;state.visible_oam[3]=64U;
    state.visible_oam[4]=76U;state.visible_oam[5]=11U;state.visible_oam[6]=0x20U;state.visible_oam[7]=68U;
    mysmb_ppu_frame_workspace_bind(&work,0);
    mysmb_ppu_frame_background_byte_bind(&work,background,sizeof(background),second,sizeof(second));
    if(!frame(&state,&work))return 1;
    state.visible_scroll_x=43U;state.visible_scroll_y=37U;state.visible_oam[3]=90U;
    state.name_table[1][9U*32U+4U]^=1U;
    if(!frame(&state,&work))return 2;
    state.visible_sprite0_split=0U;state.visible_oam[0]=239U;state.visible_oam[4]=239U;
    state.visible_ppu_name_table=0U;state.visible_scroll_x=3U;state.visible_scroll_y=0U;
    if(!frame(&state,&work))return 3;
    printf("retained overlay frames=3 exact=1\n");return 0;
}
