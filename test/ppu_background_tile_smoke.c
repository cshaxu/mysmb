#include "ppu/frame.h"
#include <stdio.h>
#include <string.h>

static mysmb_io_u8 background[MYSMB_PPU_BACKGROUND_BYTES];
static mysmb_io_u8 second[MYSMB_PPU_BACKGROUND_SECOND_BYTES];
static mysmb_io_u8 chr[8192];
static void state(struct mysmb_ppu_state *s)
{
    mysmb_io_u16 i;
    memset(s,0,sizeof(*s));
    s->chr_data=chr;s->chr_data_size=sizeof(chr);s->visible_ppu_mask=10U;
    for(i=0U;i<2048U;++i)
        s->name_table[i/1024U][i&1023U]=(mysmb_io_u8)(i*7U);
    for(i=0U;i<8192U;++i)chr[i]=(mysmb_io_u8)(i*13U+i/7U);
}
static int check_tile(const struct mysmb_ppu_frame_view *view,
    struct mysmb_ppu_state *state,mysmb_io_u8 table,mysmb_io_u8 row,
    mysmb_io_u8 column)
{
    mysmb_io_u8 tile[64],rows[2048];
    mysmb_io_u16 y,x;
    if(!mysmb_ppu_frame_background_tile_slots(view,table,row,column,tile,sizeof(tile)))return 0;
    state->visible_ppu_name_table=table;
    state->visible_scroll_x=0U;state->visible_scroll_y=0U;
    if(!mysmb_ppu_frame_slot_rows(view,rows,sizeof(rows),(mysmb_io_u16)row*8U,8U))return 0;
    for(y=0U;y<8U;++y)for(x=0U;x<8U;++x)
        if(tile[y*8U+x]!=rows[y*256U+column*8U+x]) {
            printf("mismatch t%u r%u c%u y%u x%u %u/%u\n",(unsigned)table,
                (unsigned)row,(unsigned)column,(unsigned)y,(unsigned)x,
                (unsigned)tile[y*8U+x],(unsigned)rows[y*256U+column*8U+x]);
            return 0;
        }
    return 1;
}
static int check_rect(const struct mysmb_ppu_frame_view *view,mysmb_io_u8 x,
    mysmb_io_u8 y,mysmb_io_u8 width,mysmb_io_u8 height)
{
    mysmb_io_u8 rows[2048],rect[64];
    mysmb_io_u16 py,px;
    if((mysmb_io_u16)width*height>sizeof(rect) ||
        !mysmb_ppu_frame_background_rows(view,rows,sizeof(rows),y,height) ||
        !mysmb_ppu_frame_background_rect(view,rect,sizeof(rect),x,y,width,height))return 0;
    for(py=0U;py<height;++py)for(px=0U;px<width;++px)
        if(rect[py*width+px]!=rows[py*256U+x+px])return 0;
    return 1;
}
int main(void)
{
    struct mysmb_ppu_state s;
    struct mysmb_ppu_state scene;
    struct mysmb_ppu_frame_workspace w;
    struct mysmb_ppu_frame_view v;
    struct mysmb_ppu_scene_viewport viewport;
    mysmb_io_u8 tile[64],guard[64],scene_rows[8192],expected_rows[8192];
    state(&s);mysmb_ppu_frame_workspace_bind(&w,0);
    mysmb_ppu_frame_background_byte_bind(&w,background,sizeof(background),second,sizeof(second));
    mysmb_ppu_frame_begin(&s,&w,&v);
    if(!mysmb_ppu_frame_scene_viewport(&v,&viewport) || !viewport.background_enabled ||
        viewport.fixed_top || viewport.scene_page!=0U)return 5;
    if(!check_tile(&v,&s,0U,0U,0U) || !check_tile(&v,&s,0U,29U,31U) ||
        !check_tile(&v,&s,1U,7U,19U) || !check_rect(&v,5U,7U,8U,8U) ||
        !check_rect(&v,248U,39U,8U,8U))return 1;
    memset(guard,0xa5U,sizeof(guard));
    if(mysmb_ppu_frame_background_tile_slots(&v,2U,30U,0U,guard,sizeof(guard)) ||
        memcmp(guard,"\245\245\245\245\245\245\245\245",8U)!=0)return 2;
    if(mysmb_ppu_frame_background_tile_slots(&v,3U,0U,0U,tile,sizeof(tile)))return 3;
    /* Fixed status uses zero scroll, while the retained HUD must restore the
     * scrolling scene it covered.  Verify that PPU-provided scene rows equal
     * the same latched state without the split. */
    scene=s;scene.visible_sprite0_split=1U;scene.visible_scroll_x=37U;
    scene.visible_scroll_y=19U;scene.visible_ppu_name_table=1U;
    mysmb_ppu_frame_end(&v);mysmb_ppu_frame_begin(&scene,&w,&v);
    if(!check_rect(&v,0U,0U,8U,8U) || !check_rect(&v,123U,31U,8U,8U) ||
        !check_rect(&v,248U,224U,8U,8U))return 8;
    if(!mysmb_ppu_frame_scene_rows(&v,scene_rows,sizeof(scene_rows),0U,32U))return 6;
    scene.visible_sprite0_split=0U;
    mysmb_ppu_frame_end(&v);mysmb_ppu_frame_begin(&scene,&w,&v);
    if(!mysmb_ppu_frame_slot_rows(&v,expected_rows,sizeof(expected_rows),0U,32U) ||
        memcmp(scene_rows,expected_rows,sizeof(scene_rows))!=0)return 7;
    printf("byte tiles=3 invalid=2\n");
    mysmb_ppu_frame_end(&v);
    mysmb_ppu_frame_workspace_bind(&w,0);
    mysmb_ppu_frame_background_bind(&w,background,sizeof(background));
    mysmb_ppu_frame_begin(&s,&w,&v);
    if(!check_tile(&v,&s,0U,4U,7U) || !check_tile(&v,&s,1U,24U,28U))return 4;
    printf("packed tiles=2\n");
    return 0;
}
