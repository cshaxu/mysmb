#include "ppu/frame.h"
#include <string.h>
#include "io/palette_expand.h"
/* Internal visible Y<=239 plus byte scroll<=255 gives at most494.
 * Bounded subtraction preserves the exact modulo domain without division. */
#define FOLD_240(value) do { if((value)>=240U)(value)-=240U; \
    if((value)>=240U)(value)-=240U; } while(0)
/* Private stack scratch uses the original /AL runtime's SS=DS contract.
 * Public state/output/resource pointers keep their existing far ABI. */
#ifdef MYSMB_DOS16_TARGET
#define MYSMB_PPU_LOCAL_NEAR __near
#else
#define MYSMB_PPU_LOCAL_NEAR
#endif
static mysmb_io_u8 mysmb_ppu_slot_at(const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *,mysmb_io_u16,mysmb_io_u16,
    mysmb_io_u8,mysmb_io_u8,mysmb_io_u8);
void mysmb_ppu_frame_workspace_bind(struct mysmb_ppu_frame_workspace *workspace,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded)
{
    workspace->decoded=decoded;workspace->chr=0;
    workspace->chr_size=0U;workspace->valid=0U;workspace->bg=0;workspace->bg_second=0;workspace->bg_valid=0U;workspace->bg_damage.full=0U;workspace->bg_damage.count=0U;memset(workspace->bg_damage.tiles,0,MYSMB_PPU_BACKGROUND_DAMAGE_BYTES);workspace->expand=mysmb_io_palette_expand_portable;workspace->expand_context=0;workspace->nibble_expand=mysmb_io_nibble_expand;workspace->slot_rows_copy=0;
}
void mysmb_ppu_frame_expansion_bind(struct mysmb_ppu_frame_workspace *w,
    mysmb_io_palette_expand expand,void *context)
{
    if(w){w->expand=expand?expand:mysmb_io_palette_expand_portable;w->expand_context=context;}
}
void mysmb_ppu_frame_nibble_bind(struct mysmb_ppu_frame_workspace *w,
    mysmb_io_nibble_expander expand)
{if(w)w->nibble_expand=expand?expand:mysmb_io_nibble_expand;}
void mysmb_ppu_frame_slot_rows_bind(struct mysmb_ppu_frame_workspace *w,
    mysmb_ppu_slot_rows_copier copy)
{if(w)w->slot_rows_copy=copy;}
void mysmb_ppu_frame_palette(const struct mysmb_ppu_state *s,
    mysmb_io_u8 MYSMB_IO_FAR *palette)
{
    memcpy(palette,s->palette,32U);
    palette[4]=palette[8]=palette[12]=palette[0];
}
static void mysmb_ppu_prepare_chr(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame_workspace *workspace)
{
    mysmb_io_u16 row,p;
    /* Spread a reversed nibble into four two-bit pixel lanes. */
    static const mysmb_io_u8 spread[16]={0U,64U,16U,80U,4U,68U,20U,84U,
        1U,65U,17U,81U,5U,69U,21U,85U};
    mysmb_io_u8 low,high;
    if(workspace==0 || workspace->decoded==0)return;
    if(workspace->valid && workspace->chr==state->chr_data &&
        workspace->chr_size==state->chr_data_size)return;
    for(row=0U;row<4096U;++row) {
        p=(mysmb_io_u16)((row/8U)*16U+(row&7U));
        low=(state->chr_data && p<state->chr_data_size)?state->chr_data[p]:0U;
        high=(state->chr_data && p+8U<state->chr_data_size)?state->chr_data[p+8U]:0U;
        workspace->decoded[row*2U]=(mysmb_io_u8)(spread[low>>4U]|(spread[high>>4U]<<1U));
        workspace->decoded[row*2U+1U]=(mysmb_io_u8)(spread[low&15U]|(spread[high&15U]<<1U));
    }
    workspace->chr=state->chr_data;workspace->chr_size=state->chr_data_size;
    workspace->valid=1U;
}

#ifdef MYSMB_DOS16_TARGET
void mysmb_ppu_frame_bind_pixels(struct mysmb_ppu_frame *frame,
                                 mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels)
{
    frame->pixels = pixels;
}
#endif
static const mysmb_io_u8 mysmb_ppu_master_color[64] = {
    0x00U,0x01U,0x02U,0x03U,0x04U,0x05U,0x06U,0x07U,
    0x08U,0x09U,0x0aU,0x0bU,0x0cU,0x0dU,0x0eU,0x0fU,
    0x10U,0x11U,0x12U,0x13U,0x14U,0x15U,0x16U,0x17U,
    0x18U,0x19U,0x1aU,0x1bU,0x1cU,0x1dU,0x1eU,0x1fU,
    0x20U,0x21U,0x22U,0x23U,0x24U,0x25U,0x26U,0x27U,
    0x28U,0x29U,0x2aU,0x2bU,0x2cU,0x2dU,0x2eU,0x2fU,
    0x30U,0x31U,0x32U,0x33U,0x34U,0x35U,0x36U,0x37U,
    0x38U,0x39U,0x3aU,0x3bU,0x3cU,0x3dU,0x3eU,0x3fU
};

static mysmb_io_u8 mysmb_ppu_pattern(const struct mysmb_ppu_state *state,
                                   mysmb_io_u16 offset)
{
    if (state->chr_data == 0 || offset >= state->chr_data_size) return 0U;
    return state->chr_data[offset];
}

static void mysmb_ppu_background_opaque(const struct mysmb_ppu_state *state,
                                            mysmb_io_u16 screen_x,
                                            mysmb_io_u16 screen_y,
                                            mysmb_io_u8 scroll_x,
                                            mysmb_io_u8 scroll_y,
                                            mysmb_io_u8 name_table,
                                            mysmb_io_u8 *opaque,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded_chr)
{
    mysmb_io_u16 source_x;
    mysmb_io_u16 source_y;
    mysmb_io_u16 row;
    mysmb_io_u16 column;
    mysmb_io_u16 table;
    mysmb_io_u16 pattern;
    mysmb_io_u8 low;
    mysmb_io_u8 high;
    mysmb_io_u8 color;

    source_x = (mysmb_io_u16)((screen_x + scroll_x) & 0x01ffU);
    source_y = (mysmb_io_u16)(screen_y + scroll_y);
    if(source_y>=480U)source_y-=480U;
    table = (mysmb_io_u16)(name_table & 3U);
    if (source_x >= 256U) table ^= 1U;
    if (source_y >= 240U) table ^= 2U;
    /* SMB1 vertical mirroring: logical 0/2 and 1/3 share CIRAM. */
    table &= 1U;
    row=source_y;FOLD_240(row);row>>=3U;
    column = (source_x & 0xffU) / 8U;
    pattern = (mysmb_io_u16)(((state->visible_ppu_control_0 & 0x10U) != 0U ?
        0x1000U : 0U) + state->name_table[table][row * 32U + column] * 16U +
        (source_y & 7U));
    if(decoded_chr)color=(mysmb_io_u8)((decoded_chr[(pattern/16U)*16U+
        (pattern&7U)*2U+(source_x&7U)/4U]>>((source_x&3U)*2U))&3U);
    else {
        low = mysmb_ppu_pattern(state, pattern);
        high = mysmb_ppu_pattern(state, (mysmb_io_u16)(pattern + 8U));
        color = (mysmb_io_u8)(((low >> (7U - (source_x & 7U))) & 1U) |
                        (((high >> (7U - (source_x & 7U))) & 1U) << 1U));
    }
    *opaque = color == 0U ? 0U : 1U;
}

/* Persistent palette slots retain raw opacity independently of display color.
 * Snapshot all attribute bytes only after their dependent tiles are updated. */
void mysmb_ppu_frame_background_bind(struct mysmb_ppu_frame_workspace *w,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *storage,mysmb_io_u16 capacity)
{
    if(!w)return;
    w->bg=capacity>=MYSMB_PPU_BACKGROUND_BYTES?storage:0;w->bg_second=0;w->bg_valid=0U;
    w->bg_chr=0;w->bg_size=0U;w->bg_pattern=0U;w->bg_visible=0U;w->bg_tiles=0UL;
    w->bg_damage.full=0U;w->bg_damage.count=0U;memset(w->bg_damage.tiles,0,MYSMB_PPU_BACKGROUND_DAMAGE_BYTES);
}
void mysmb_ppu_frame_background_byte_bind(struct mysmb_ppu_frame_workspace *w,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *first,mysmb_io_u16 first_capacity,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *second,mysmb_io_u16 second_capacity)
{
    mysmb_ppu_frame_background_bind(w,first,first_capacity);
    if(w && w->bg && second && second_capacity>=MYSMB_PPU_BACKGROUND_SECOND_BYTES)
        w->bg_second=second;
}
static void mysmb_ppu_slot_prepare(const struct mysmb_ppu_state *s,
    struct mysmb_ppu_frame_workspace *w)
{
    mysmb_io_u16 t,ty,tx,a,ai,base,fy,p,dest,i,decoded_offset;
    mysmb_io_u8 tile,attr,pal,lo,hi,c0,c1;
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *old,*image;
    int all;
    if(!w || !w->bg)return;
    w->bg_damage.full=0U;w->bg_damage.count=0U;memset(w->bg_damage.tiles,0,MYSMB_PPU_BACKGROUND_DAMAGE_BYTES);
    all=!w->bg_valid || w->bg_chr!=s->chr_data || w->bg_size!=s->chr_data_size ||
        w->bg_pattern!=(s->visible_ppu_control_0&16U) ||
        w->bg_visible!=(mysmb_io_u8)(s->visible_ppu_mask&8U);
    if(!all && memcmp(w->bg,s->name_table,2048U)==0)return;
    if(all) {
        w->bg_damage.full=1U;
        w->bg_damage.count=1920U;
        memset(w->bg_damage.tiles,255,MYSMB_PPU_BACKGROUND_DAMAGE_BYTES);
    }
    base=(s->visible_ppu_control_0&16U)?4096U:0U;
    old=w->bg;image=w->bg+2048U;
    for(t=0U;t<2U;++t)for(ty=0U;ty<30U;++ty) {
        /* Reject an unchanged tile row and its shared attribute row in bulk.
         * Snapshot remains old until all dependent tiles have been refreshed. */
        if(!all && memcmp(old+t*1024U+ty*32U,
            s->name_table[t]+ty*32U,32U)==0 &&
            memcmp(old+t*1024U+960U+(ty>>2U)*8U,
                s->name_table[t]+960U+(ty>>2U)*8U,8U)==0)continue;
        for(tx=0U;tx<32U;++tx) {
        a=(mysmb_io_u16)(ty*32U+tx);
        ai=(mysmb_io_u16)(960U+(ty>>2U)*8U+(tx>>2U));
        tile=s->name_table[t][a];attr=s->name_table[t][ai];
        if(!all && old[t*1024U+a]==tile && old[t*1024U+ai]==attr)continue;
        ++w->bg_tiles;
        if(!all)++w->bg_damage.count;
        w->bg_damage.tiles[(t*960U+ty*32U+tx)>>3U]|=
            (mysmb_io_u8)(1U<<((t*960U+ty*32U+tx)&7U));
        pal=(mysmb_io_u8)(((attr>>(((ty&2U)<<1U)+(tx&2U)))&3U)*4U);
        for(fy=0U;fy<8U;++fy) {
            p=(mysmb_io_u16)(base+tile*16U+fy);
            if(w->bg_second) {
                image=t?w->bg_second:w->bg+2048U;
                dest=(mysmb_io_u16)((ty*8U+fy)*256U+tx*8U);
            }else dest=(mysmb_io_u16)(t*30720U+(ty*8U+fy)*128U+tx*4U);
            if(w->decoded) {
                decoded_offset=(mysmb_io_u16)(base+tile*16U+fy*2U);
                lo=w->decoded[decoded_offset];hi=w->decoded[decoded_offset+1U];
            } else {
                lo=mysmb_ppu_pattern(s,p);hi=mysmb_ppu_pattern(s,(mysmb_io_u16)(p+8U));
            }
            for(i=0U;i<4U;++i) {
                if(w->decoded) {
                    c0=(mysmb_io_u8)(((i<2U?lo:hi)>>((i&1U)*4U))&3U);
                    c1=(mysmb_io_u8)(((i<2U?lo:hi)>>((i&1U)*4U+2U))&3U);
                } else {
                    c0=(mysmb_io_u8)(((lo>>(7U-i*2U))&1U)|(((hi>>(7U-i*2U))&1U)<<1U));
                    c1=(mysmb_io_u8)(((lo>>(6U-i*2U))&1U)|(((hi>>(6U-i*2U))&1U)<<1U));
                }
                if(c0)c0=(mysmb_io_u8)(c0+pal);
                if(c1)c1=(mysmb_io_u8)(c1+pal);
                if(w->bg_second) {
                    image[dest+i*2U]=c0;image[dest+i*2U+1U]=c1;
                }else image[dest+i]=(mysmb_io_u8)(c0|(c1<<4U));
            }
        }
        }
    }
    memcpy(old,s->name_table,2048U);
    w->bg_valid=1U;w->bg_chr=s->chr_data;w->bg_size=s->chr_data_size;
    w->bg_pattern=(mysmb_io_u8)(s->visible_ppu_control_0&16U);
    w->bg_visible=(mysmb_io_u8)(s->visible_ppu_mask&8U);
}
static mysmb_io_u8 mysmb_ppu_slot_at(
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *bg,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *second,mysmb_io_u16 x,mysmb_io_u16 y,
    mysmb_io_u8 scroll_x,mysmb_io_u8 scroll_y,mysmb_io_u8 name)
{
    mysmb_io_u16 sx,sy,t,p;
    mysmb_io_u8 pair;
    sx=(mysmb_io_u16)(x+scroll_x);sy=(mysmb_io_u16)(y+scroll_y);FOLD_240(sy);
    t=(mysmb_io_u16)((name^(sx>>8U))&1U);
    if(second)return (t?second:bg+2048U)[sy*256U+(sx&255U)];
    p=(mysmb_io_u16)(2048U+t*30720U+sy*128U+((sx&255U)>>1U));
    pair=bg[p];return (mysmb_io_u8)((pair>>((sx&1U)*4U))&15U);
}
/* Shared expansion always publishes the complete row directly.
 * An unavailable host accelerator selects the portable span implementation. */
static void mysmb_ppu_slot_row(const struct mysmb_ppu_state *s,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *bg,mysmb_io_u16 y,
    mysmb_io_u8 sx,mysmb_io_u8 sy,mysmb_io_u8 nt,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *out,
    const mysmb_io_u8 MYSMB_PPU_LOCAL_NEAR *colors,
    struct mysmb_ppu_frame_workspace *w,mysmb_io_u8 slots)
{
    mysmb_io_u16 x=0U,source_x=sx,source_y,t,count,even;
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *in;

    source_y=(mysmb_io_u16)(y+sy);FOLD_240(source_y);
    if(w && w->bg_second) {
        while(x<256U) {
            t=(mysmb_io_u16)((nt^(source_x>>8U))&1U);
            in=(t?w->bg_second:bg+2048U)+source_y*256U+(source_x&255U);
            count=(mysmb_io_u16)(256U-(source_x&255U));
            if(count>256U-x)count=(mysmb_io_u16)(256U-x);
            if(slots)memcpy(out+x,in,count);
            else for(even=0U;even<count;++even)out[x+even]=colors[in[even]];
            source_x=(mysmb_io_u16)(source_x+count);x=(mysmb_io_u16)(x+count);
        }
        if((s->visible_ppu_mask&2U)==0U)memset(out,colors[0U],8U);
        return;
    }
    while(x<256U){
        t=(mysmb_io_u16)((nt^(source_x>>8U))&1U);
        in=bg+2048U+t*30720U+source_y*128U+((source_x&255U)>>1U);
        if(source_x&1U){out[x++]=colors[*in>>4U];++source_x;continue;}
        count=(mysmb_io_u16)(256U-(source_x&255U));
        if(count>256U-x)count=(mysmb_io_u16)(256U-x);
        even=(mysmb_io_u16)(count&0xfffeU);
        if(slots){
            if(even && (!w || !w->nibble_expand || !w->nibble_expand(in,out+x,even)))
                (void)mysmb_io_nibble_expand(in,out+x,even);
        }else if(even && (!w || !w->expand ||
            !w->expand(w->expand_context,in,out+x,even,colors)))
            (void)mysmb_io_palette_expand_portable(0,in,out+x,even,colors);
        x+=even;source_x+=even;
        if(count&1U){out[x++]=colors[in[even/2U]&15U];++source_x;}
    }
    if(!(s->visible_ppu_mask&2U))memset(out,colors[0],8U);
}

/* Globally invisible prefixes/suffixes have no rows to draw. Interior gaps
 * retain the original scan;the compositor still consumes descending OAM. */
static void mysmb_ppu_sprite_range(const struct mysmb_ppu_state *s,
    mysmb_io_u8 MYSMB_IO_FAR *range)
{
    mysmb_io_u16 i;range[0]=range[1]=0U;
    if(s->visible_ppu_mask&16U)for(i=0U;i<64U;++i)
        if(s->visible_oam[i*4U]<239U){
            if(range[1]==0U)range[0]=(mysmb_io_u8)i;
            range[1]=(mysmb_io_u8)(i+1U);
        }
}

void mysmb_ppu_frame_begin(const struct mysmb_ppu_state *s,
    struct mysmb_ppu_frame_workspace *w,struct mysmb_ppu_frame_view *v)
{
    if(!v)return;
    v->active=0U;v->state=0;v->workspace=0;v->sprite_range[0]=v->sprite_range[1]=0U;
    if(!s)return;
    mysmb_ppu_prepare_chr(s,w);mysmb_ppu_slot_prepare(s,w);
    mysmb_ppu_sprite_range(s,v->sprite_range);
    v->state=s;v->workspace=w;v->active=1U;
}
void mysmb_ppu_frame_end(struct mysmb_ppu_frame_view *v)
{
    if(v){v->active=0U;v->state=0;v->workspace=0;v->sprite_range[0]=v->sprite_range[1]=0U;}
}
int mysmb_ppu_frame_background_damage(const struct mysmb_ppu_frame_view *v,
    struct mysmb_ppu_background_damage *damage)
{
    if(!v || !damage || !v->active || !v->workspace || !v->workspace->bg ||
        !v->workspace->bg_valid)return 0;
    memcpy(damage,&v->workspace->bg_damage,sizeof(*damage));
    return 1;
}
int mysmb_ppu_frame_background_tile_slots(const struct mysmb_ppu_frame_view *v,
    mysmb_io_u8 table,mysmb_io_u8 row,mysmb_io_u8 column,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *slots,mysmb_io_u16 capacity)
{
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *image;
    mysmb_io_u16 y,source;
    mysmb_io_u8 pair;
    if(!v || !v->active || !v->workspace || !v->workspace->bg ||
        !v->workspace->bg_valid || !slots || capacity<64U || table>=2U ||
        row>=30U || column>=32U)return 0;
    if(v->workspace->bg_second) {
        image=table?v->workspace->bg_second:v->workspace->bg+2048U;
        for(y=0U;y<8U;++y)
            memcpy(slots+y*8U,image+(row*8U+y)*256U+column*8U,8U);
        return 1;
    }
    image=v->workspace->bg+2048U+table*30720U;
    for(y=0U;y<8U;++y)for(source=0U;source<4U;++source) {
        pair=image[(row*8U+y)*128U+column*4U+source];
        slots[y*8U+source*2U]=(mysmb_io_u8)(pair&15U);
        slots[y*8U+source*2U+1U]=(mysmb_io_u8)(pair>>4U);
    }
    return 1;
}
int mysmb_ppu_frame_scene_viewport(const struct mysmb_ppu_frame_view *v,
    struct mysmb_ppu_scene_viewport *viewport)
{
    if(!v || !v->active || !v->state || !viewport)return 0;
    viewport->background_enabled=(mysmb_io_u8)((v->state->visible_ppu_mask&8U)!=0U);
    viewport->fixed_top=(mysmb_io_u8)(v->state->visible_sprite0_split!=0U);
    viewport->scene_page=v->state->visible_ppu_name_table;
    viewport->output_origin_x=v->state->visible_scroll_x;
    viewport->output_origin_y=v->state->visible_scroll_y;
    return 1;
}
static int mysmb_ppu_sprite_tile(const struct mysmb_ppu_frame_view *v,
    mysmb_io_u16 sprite,mysmb_io_u8 MYSMB_PPU_FRAME_FAR *slots,
    mysmb_io_u8 *sprite_x,mysmb_io_u8 *sprite_y)
{
    const struct mysmb_ppu_state *state=v->state;
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded_sprite_row;
    mysmb_io_u16 pixel_x,pixel_y,pattern,x,y;
    mysmb_io_u8 attributes,low,high,color,opaque,scroll_x,scroll_y;
    mysmb_io_u16 fixed_top_height;
    int visible=0;
    memset(slots,255,64U);
    y=(mysmb_io_u16)state->visible_oam[sprite*4U]+1U;
    x=state->visible_oam[sprite*4U+3U];
    if(y>=MYSMB_PPU_FRAME_HEIGHT || x>=MYSMB_PPU_FRAME_WIDTH)return 0;
    *sprite_x=(mysmb_io_u8)x;*sprite_y=(mysmb_io_u8)y;
    attributes=state->visible_oam[sprite*4U+2U];
    fixed_top_height=state->visible_sprite0_split?MYSMB_PPU_STATUS_BAR_HEIGHT:0U;
    for(pixel_y=0U;pixel_y<8U && y+pixel_y<MYSMB_PPU_FRAME_HEIGHT;++pixel_y) {
        pattern=(mysmb_io_u16)(((state->visible_ppu_control_0&8U)?0x1000U:0U)+
            state->visible_oam[sprite*4U+1U]*16U+
            ((attributes&0x80U)?7U-pixel_y:pixel_y));
        if(v->workspace && v->workspace->decoded)
            decoded_sprite_row=v->workspace->decoded+(pattern&0xfff0U)+(pattern&7U)*2U;
        else {low=mysmb_ppu_pattern(state,pattern);high=mysmb_ppu_pattern(state,(mysmb_io_u16)(pattern+8U));}
        for(pixel_x=0U;pixel_x<8U && x+pixel_x<MYSMB_PPU_FRAME_WIDTH;++pixel_x) {
            if(v->workspace && v->workspace->decoded) {
                color=(mysmb_io_u8)((attributes&0x40U)?7U-pixel_x:pixel_x);
                color=(mysmb_io_u8)((decoded_sprite_row[color>>2U]>>((color&3U)*2U))&3U);
            } else color=(mysmb_io_u8)(((low>>((attributes&0x40U)?pixel_x:7U-pixel_x))&1U)|
                (((high>>((attributes&0x40U)?pixel_x:7U-pixel_x))&1U)<<1U));
            if(!color)continue;
            if(x+pixel_x<8U && (state->visible_ppu_mask&4U)==0U)continue;
            if((attributes&0x20U) && (state->visible_ppu_mask&8U) &&
                (x+pixel_x>=8U || (state->visible_ppu_mask&2U))) {
                scroll_x=y+pixel_y<fixed_top_height?0U:state->visible_scroll_x;
                scroll_y=y+pixel_y<fixed_top_height?0U:state->visible_scroll_y;
                if(v->workspace && v->workspace->bg)
                    opaque=(mysmb_io_u8)((mysmb_ppu_slot_at(v->workspace->bg,
                        v->workspace->bg_second,x+pixel_x,y+pixel_y,scroll_x,scroll_y,
                        y+pixel_y<fixed_top_height?0U:state->visible_ppu_name_table)&3U)!=0U);
                else mysmb_ppu_background_opaque(state,x+pixel_x,y+pixel_y,scroll_x,scroll_y,
                    y+pixel_y<fixed_top_height?0U:state->visible_ppu_name_table,&opaque,
                    v->workspace?v->workspace->decoded:0);
                if(opaque)continue;
            }
            slots[pixel_y*8U+pixel_x]=(mysmb_io_u8)(0x10U+(attributes&3U)*4U+color);
            visible=1;
        }
    }
    return visible;
}
int mysmb_ppu_frame_sprite_tiles(const struct mysmb_ppu_frame_view *v,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *slots,mysmb_io_u16 capacity,
    mysmb_ppu_sprite_tile_writer writer,void *context)
{
    mysmb_io_u16 sprite;
    mysmb_io_u8 x,y;
    if(!v || !v->active || !v->state || !slots || capacity<64U || !writer)return 0;
    for(sprite=v->sprite_range[1];sprite!=v->sprite_range[0];) {
        --sprite;
        if(mysmb_ppu_sprite_tile(v,sprite,slots,&x,&y) &&
            !writer(context,(mysmb_io_u8)sprite,x,y,slots))return 0;
    }
    return 1;
}

/* Decode once per visible tile row,not once per pixel. The partial first and
 * last tiles retain exact scroll,mirroring,CHR bounds and left-edge semantics. */
static void mysmb_ppu_background_row(const struct mysmb_ppu_state *state,
    mysmb_io_u16 y,mysmb_io_u8 scroll_x,mysmb_io_u8 scroll_y,mysmb_io_u8 name_table,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *out,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded_chr,
    const mysmb_io_u8 MYSMB_PPU_LOCAL_NEAR *colors)
{
    mysmb_io_u16 source_y,row,source_x,x,column,table,pattern,count,i,row_offset,attr_offset;
    mysmb_io_u8 attribute,palette,low,high,color,phase,fine_y,row_shift;
    mysmb_io_u8 pixels[MYSMB_PPU_FRAME_WIDTH];
    const mysmb_io_u8 *chr;
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *name_row,*attribute_row;
    mysmb_io_u8 MYSMB_PPU_LOCAL_NEAR *target;
    const mysmb_io_u8 MYSMB_PPU_LOCAL_NEAR *quad;
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded=decoded_chr;
    mysmb_io_u16 chr_size,pattern_base,blank_start=0U,blank_count=0U;
    /* Palette and row staging are stack-owned. Avoid a far state/pixel access
     * for every output dot; one bounded copy publishes the completed row. */
    chr=state->chr_data;chr_size=state->chr_data_size;
    pattern_base=(state->visible_ppu_control_0&0x10U)?0x1000U:0U;
    source_y=(mysmb_io_u16)(y+scroll_y);
    if(source_y>=480U)source_y-=480U;
    row=source_y;FOLD_240(row);row>>=3U;
    row_offset=(mysmb_io_u16)(row*32U);
    attr_offset=(mysmb_io_u16)(0x3c0U+(row>>2U)*8U);
    fine_y=(mysmb_io_u8)(source_y&7U);row_shift=(mysmb_io_u8)((row&2U)<<1U);
    source_x=scroll_x;x=0U;
    /* A 256-pixel row crosses this borrowed nametable span at most once. */
    table=(mysmb_io_u16)(name_table&1U);
    name_row=state->name_table[table]+row_offset;
    attribute_row=state->name_table[table]+attr_offset;
    while(x<MYSMB_PPU_FRAME_WIDTH) {
        if(source_x==256U) {
            table=(mysmb_io_u16)((name_table^((source_x>>8U)&1U))&1U);
            name_row=state->name_table[table]+row_offset;
            attribute_row=state->name_table[table]+attr_offset;
        }
        column=(mysmb_io_u16)((source_x&255U)>>3U);
        pattern=(mysmb_io_u16)(pattern_base+
            name_row[column]*16U+fine_y);
        phase=(mysmb_io_u8)(source_x&7U);
        count=(mysmb_io_u16)(8U-phase);
        if(count>MYSMB_PPU_FRAME_WIDTH-x)count=(mysmb_io_u16)(MYSMB_PPU_FRAME_WIDTH-x);
        if(decoded_chr) {
            decoded=decoded_chr+(pattern&0xfff0U)+(pattern&7U)*2U;
            low=decoded[0U];high=decoded[1U];
            /* Index zero ignores the attribute palette. Merge adjacent blank
             * spans; raw opacity is still queried independently for sprites. */
            if((low|high)==0U) {
                if(blank_count==0U)blank_start=x;
                blank_count=(mysmb_io_u16)(blank_count+count);
                x=(mysmb_io_u16)(x+count);source_x=(mysmb_io_u16)((source_x+count)&511U);
                continue;
            }
        }
        else {
            low=(mysmb_io_u8)((chr!=0 && pattern<chr_size?chr[pattern]:0U)<<phase);
            high=(mysmb_io_u8)((chr!=0 && pattern+8U<chr_size?chr[pattern+8U]:0U)<<phase);
        }
        if(blank_count) {
            memset(pixels+blank_start,colors[0U],blank_count);blank_count=0U;
        }
        attribute=attribute_row[column>>2U];
        palette=(mysmb_io_u8)((attribute>>(row_shift+(column&2U)))&3U);
        palette=(mysmb_io_u8)(palette*4U);
        if(decoded_chr) {
            if(count==8U) {
                target=pixels+x;quad=colors+palette;
                target[0U]=quad[low&3U];
                target[1U]=quad[low>>2U&3U];
                target[2U]=quad[low>>4U&3U];
                target[3U]=quad[low>>6U&3U];
                target[4U]=quad[high&3U];
                target[5U]=quad[high>>2U&3U];
                target[6U]=quad[high>>4U&3U];
                target[7U]=quad[high>>6U&3U];
            }else for(i=0U;i<count;++i)pixels[x+i]=colors[palette+
                ((decoded[(phase+i)/4U]>>(((phase+i)%4U)*2U))&3U)];
        } else if(count==8U) {
            pixels[x+0U]=colors[palette+(((low>>7U)&1U)|((high>>6U)&2U))];
            pixels[x+1U]=colors[palette+(((low>>6U)&1U)|((high>>5U)&2U))];
            pixels[x+2U]=colors[palette+(((low>>5U)&1U)|((high>>4U)&2U))];
            pixels[x+3U]=colors[palette+(((low>>4U)&1U)|((high>>3U)&2U))];
            pixels[x+4U]=colors[palette+(((low>>3U)&1U)|((high>>2U)&2U))];
            pixels[x+5U]=colors[palette+(((low>>2U)&1U)|((high>>1U)&2U))];
            pixels[x+6U]=colors[palette+(((low>>1U)&1U)|((high>>0U)&2U))];
            pixels[x+7U]=colors[palette+((low&1U)|((high<<1U)&2U))];
        } else for(i=0U;i<count;++i) {
            color=(mysmb_io_u8)((low>>7U)|((high>>6U)&2U));
            pixels[x+i]=colors[palette+color];
            low=(mysmb_io_u8)(low<<1U);high=(mysmb_io_u8)(high<<1U);
        }
        x=(mysmb_io_u16)(x+count);source_x=(mysmb_io_u16)((source_x+count)&511U);
    }
    if(blank_count)memset(pixels+blank_start,colors[0U],blank_count);
    if((state->visible_ppu_mask&2U)==0U)
        for(x=0U;x<8U;++x)pixels[x]=colors[0U];
    memcpy(out,pixels,MYSMB_PPU_FRAME_WIDTH);
}

/* The byte cache owns two linear 256x240 slot surfaces. Group only rows with
 * one unchanged scroll/name-table relation and no vertical wrap;the host sees
 * bytes already selected by the shared PPU and cannot choose any visual or
 * game state. A rejected group falls back to the existing exact row path. */
static int mysmb_ppu_slot_rows_copy(const struct mysmb_ppu_state *state,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *bg,
    struct mysmb_ppu_frame_workspace *workspace,mysmb_io_u16 first,
    mysmb_io_u16 rows,mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels)
{
    mysmb_io_u16 y,run,remain,source_y,t,a_count,b_count;
    mysmb_io_u8 sx,sy,nt;
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *a,*b;
    if(!workspace || !workspace->bg_second || !workspace->slot_rows_copy)return 0;
    y=first;remain=rows;
    while(remain) {
        sx=y<MYSMB_PPU_STATUS_BAR_HEIGHT && state->visible_sprite0_split?0U:
            state->visible_scroll_x;
        sy=y<MYSMB_PPU_STATUS_BAR_HEIGHT && state->visible_sprite0_split?0U:
            state->visible_scroll_y;
        nt=y<MYSMB_PPU_STATUS_BAR_HEIGHT && state->visible_sprite0_split?0U:
            state->visible_ppu_name_table;
        source_y=(mysmb_io_u16)(y+sy);FOLD_240(source_y);
        run=remain;
        if(y<MYSMB_PPU_STATUS_BAR_HEIGHT && state->visible_sprite0_split &&
            run>MYSMB_PPU_STATUS_BAR_HEIGHT-y)run=(mysmb_io_u16)(MYSMB_PPU_STATUS_BAR_HEIGHT-y);
        if(run>240U-source_y)run=(mysmb_io_u16)(240U-source_y);
        t=(mysmb_io_u16)((nt^(sx>>8U))&1U);
        a=(t?workspace->bg_second:bg+2048U)+source_y*256U+(sx&255U);
        a_count=(mysmb_io_u16)(256U-(sx&255U));
        b_count=(mysmb_io_u16)(256U-a_count);
        b=b_count?((t?bg+2048U:workspace->bg_second)+source_y*256U):0;
        if(!workspace->slot_rows_copy(a,b,pixels+(y-first)*256U,
            a_count,b_count,run))return 0;
        y=(mysmb_io_u16)(y+run);remain=(mysmb_io_u16)(remain-run);
    }
    if((state->visible_ppu_mask&2U)==0U)
        for(y=0U;y<rows;++y)memset(pixels+y*256U,0,8U);
    return 1;
}

static void mysmb_ppu_frame_build_internal(const struct mysmb_ppu_state *state,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels,mysmb_io_u16 first,mysmb_io_u16 rows,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded_chr,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *bg,
    struct mysmb_ppu_frame_workspace *workspace,mysmb_io_u8 slots,
    mysmb_io_u16 sprite_first,mysmb_io_u16 sprite_last)
{
    mysmb_io_u8 colors[16];
    mysmb_io_u16 x;
    mysmb_io_u16 y;
    mysmb_io_u16 sprite;
    mysmb_io_u16 fixed_top_height;
    mysmb_io_u16 sprite_x;
    mysmb_io_u16 sprite_y;
    mysmb_io_u16 pixel_x;
    mysmb_io_u16 pixel_y;
    mysmb_io_u16 pattern;
    mysmb_io_u8 attributes;
    mysmb_io_u8 low;
    mysmb_io_u8 high;
    mysmb_io_u8 color;
    mysmb_io_u8 opaque;
    mysmb_io_u8 scroll_x;
    mysmb_io_u8 scroll_y;
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded_sprite_row;

    /* Source flag zero reaches SkipSprite0 during VBlank, so the entire
     * visible frame uses scene scroll. A synchronized frame retains its
     * fixed top region; never reread the following frame's RAM flag here. */
    /* One immutable frame/band call shares its background palette across rows.
     * Rebuild on every call; sprite colors still read their original entries. */
    if(slots)for(x=0U;x<16U;++x)colors[x]=(mysmb_io_u8)x;
    else memcpy(colors,state->palette,16U);
    colors[4]=colors[8]=colors[12]=colors[0];
    fixed_top_height = state->visible_sprite0_split != 0U ?
        MYSMB_PPU_STATUS_BAR_HEIGHT : 0U;
    if(!(slots && bg && (state->visible_ppu_mask&8U)!=0U &&
        mysmb_ppu_slot_rows_copy(state,bg,workspace,first,rows,pixels)))
        for (y = first; y < first+rows; ++y) {
            scroll_x = y < fixed_top_height ? 0U : state->visible_scroll_x;
            scroll_y = y < fixed_top_height ? 0U : state->visible_scroll_y;
            if(bg && (state->visible_ppu_mask&8U)!=0U)
                mysmb_ppu_slot_row(state,bg,y,scroll_x,scroll_y,
                    y<fixed_top_height?0U:state->visible_ppu_name_table,
                    pixels+(y-first)*256U,colors,workspace,slots);
            else if((state->visible_ppu_mask&8U)!=0U)
                mysmb_ppu_background_row(state,y,scroll_x,scroll_y,
                    y<fixed_top_height?0U:state->visible_ppu_name_table,
                    pixels+(y-first)*MYSMB_PPU_FRAME_WIDTH,decoded_chr,colors);
            else memset(pixels+(y-first)*MYSMB_PPU_FRAME_WIDTH,colors[0U],MYSMB_PPU_FRAME_WIDTH);
        }
    if ((state->visible_ppu_mask & 0x10U) == 0U) return;
    for (sprite = sprite_last; sprite != sprite_first;) {
        --sprite;
        sprite_y = (mysmb_io_u16)state->visible_oam[sprite * 4U] + 1U;
        if (sprite_y >= first+rows || sprite_y+8U <= first) continue;
        sprite_x = state->visible_oam[sprite * 4U + 3U];
        attributes = state->visible_oam[sprite * 4U + 2U];
        for (pixel_y = 0U; pixel_y < 8U && sprite_y + pixel_y < MYSMB_PPU_FRAME_HEIGHT;
             ++pixel_y) {
            if(sprite_y+pixel_y<first || sprite_y+pixel_y>=first+rows)continue;
            pattern = (mysmb_io_u16)(((state->visible_ppu_control_0 & 0x08U) != 0U ?
                0x1000U : 0U) + state->visible_oam[sprite * 4U + 1U] * 16U +
                ((attributes & 0x80U) != 0U ? 7U - pixel_y : pixel_y));
            if(decoded_chr)
                decoded_sprite_row=decoded_chr+(pattern&0xfff0U)+(pattern&7U)*2U;
            else {
                low = mysmb_ppu_pattern(state, pattern);
                high = mysmb_ppu_pattern(state, (mysmb_io_u16)(pattern + 8U));
            }
            for (pixel_x = 0U; pixel_x < 8U && sprite_x + pixel_x < MYSMB_PPU_FRAME_WIDTH;
                 ++pixel_x) {
                if(decoded_chr) {
                    color=(mysmb_io_u8)((attributes&0x40U)?7U-pixel_x:pixel_x);
                    color=(mysmb_io_u8)((decoded_sprite_row[color>>2U]>>
                        ((color&3U)*2U))&3U);
                }
                else color = (mysmb_io_u8)(((low >> ((attributes & 0x40U) != 0U ? pixel_x :
                    7U - pixel_x)) & 1U) | (((high >> ((attributes & 0x40U) != 0U ?
                    pixel_x : 7U - pixel_x)) & 1U) << 1U));
                if (color == 0U) continue;
                y = (mysmb_io_u16)(sprite_y + pixel_y);
                x = (mysmb_io_u16)(sprite_x + pixel_x);
                if (x < 8U && (state->visible_ppu_mask & 0x04U) == 0U) continue;
                if ((attributes & 0x20U) != 0U &&
                    (state->visible_ppu_mask & 0x08U) != 0U &&
                    (x >= 8U || (state->visible_ppu_mask & 0x02U) != 0U)) {
                    scroll_x = y < fixed_top_height ? 0U : state->visible_scroll_x;
                    scroll_y = y < fixed_top_height ? 0U : state->visible_scroll_y;
                    if(bg)opaque=(mysmb_io_u8)((mysmb_ppu_slot_at(bg,workspace?workspace->bg_second:0,x,y,scroll_x,scroll_y,
                        y<fixed_top_height?0U:state->visible_ppu_name_table)&3U)!=0U);
                    else mysmb_ppu_background_opaque(state,x,y,scroll_x,scroll_y,
                        y<fixed_top_height?0U:state->visible_ppu_name_table,&opaque,decoded_chr);
                    if (opaque != 0U) continue;
                }
                pixels[(y-first) * MYSMB_PPU_FRAME_WIDTH + x] = slots?
                    (mysmb_io_u8)(0x10U+(attributes&3U)*4U+color):
                    state->palette[0x10U+(attributes&3U)*4U+color];
            }
        }
    }
    (void)mysmb_ppu_master_color[0];
}

void mysmb_ppu_frame_build(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame *frame)
{
    mysmb_ppu_frame_build_internal(state,frame->pixels,0U,240U,0,0,0,0U,0U,64U);
}
void mysmb_ppu_frame_build_cached(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame *frame,struct mysmb_ppu_frame_workspace *workspace)
{
    mysmb_ppu_prepare_chr(state,workspace);mysmb_ppu_slot_prepare(state,workspace);
    mysmb_ppu_frame_build_internal(state,frame->pixels,0U,240U,workspace?workspace->decoded:0,workspace?workspace->bg:0,workspace,0U,0U,64U);
}

int mysmb_ppu_frame_build_rows_cached(const struct mysmb_ppu_state *state,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows,struct mysmb_ppu_frame_workspace *workspace)
{
    if(state==0 || pixels==0 || first>=240U || rows>240U-first ||
        rows>capacity/MYSMB_PPU_FRAME_WIDTH)return 0;
    if(rows==0U)return 1;
    mysmb_ppu_prepare_chr(state,workspace);mysmb_ppu_slot_prepare(state,workspace);
    mysmb_ppu_frame_build_internal(state,pixels,first,rows,
        workspace?workspace->decoded:0,workspace?workspace->bg:0,workspace,0U,0U,64U);
    return 1;
}

int mysmb_ppu_frame_rows(const struct mysmb_ppu_frame_view *v,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows)
{
    if(!v || !v->active || !v->state || !pixels || first>=240U || rows>240U-first || rows>capacity/256U)return 0;
    if(rows)mysmb_ppu_frame_build_internal(v->state,pixels,first,rows,
        v->workspace?v->workspace->decoded:0,v->workspace?v->workspace->bg:0,v->workspace,0U,v->sprite_range[0],v->sprite_range[1]);
    return 1;
}

void mysmb_ppu_frame_build_slots_cached(const struct mysmb_ppu_state *s,
    struct mysmb_ppu_frame *frame,struct mysmb_ppu_frame_workspace *w)
{
    mysmb_ppu_prepare_chr(s,w);mysmb_ppu_slot_prepare(s,w);
    mysmb_ppu_frame_build_internal(s,frame->pixels,0U,240U,
        w?w->decoded:0,w?w->bg:0,w,1U,0U,64U);
}
int mysmb_ppu_frame_slot_rows(const struct mysmb_ppu_frame_view *v,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows)
{
    if(!v || !v->active || !v->state || !pixels || first>=240U ||
        rows>240U-first || rows>capacity/256U)return 0;
    if(rows)mysmb_ppu_frame_build_internal(v->state,pixels,first,rows,
        v->workspace?v->workspace->decoded:0,v->workspace?v->workspace->bg:0,
        v->workspace,1U,v->sprite_range[0],v->sprite_range[1]);
    return 1;
}
int mysmb_ppu_frame_background_rows(const struct mysmb_ppu_frame_view *v,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows)
{
    if(!v || !v->active || !v->state || !pixels || first>=240U ||
        rows>240U-first || rows>capacity/256U)return 0;
    if(rows)mysmb_ppu_frame_build_internal(v->state,pixels,first,rows,
        v->workspace?v->workspace->decoded:0,v->workspace?v->workspace->bg:0,
        v->workspace,1U,0U,0U);
    return 1;
}
int mysmb_ppu_frame_background_rect(const struct mysmb_ppu_frame_view *v,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u8 x,mysmb_io_u8 y,mysmb_io_u8 width,mysmb_io_u8 height)
{
    const struct mysmb_ppu_state *state;
    mysmb_io_u16 px,py,scroll_x,scroll_y;
    mysmb_io_u8 table;
    if(!v || !v->active || !v->state || !v->workspace || !v->workspace->bg ||
        !pixels || !width || !height || (mysmb_io_u16)x+width>256U ||
        (mysmb_io_u16)y+height>240U || (mysmb_io_u16)width*height>capacity)return 0;
    state=v->state;
    for(py=0U;py<height;++py) {
        mysmb_io_u16 screen_y=(mysmb_io_u16)y+py;
        scroll_x=screen_y<MYSMB_PPU_STATUS_BAR_HEIGHT && state->visible_sprite0_split?0U:
            state->visible_scroll_x;
        scroll_y=screen_y<MYSMB_PPU_STATUS_BAR_HEIGHT && state->visible_sprite0_split?0U:
            state->visible_scroll_y;
        table=screen_y<MYSMB_PPU_STATUS_BAR_HEIGHT && state->visible_sprite0_split?0U:
            state->visible_ppu_name_table;
        for(px=0U;px<width;++px) {
            mysmb_io_u16 screen_x=(mysmb_io_u16)x+px;
            if((state->visible_ppu_mask&8U)==0U ||
                (screen_x<8U && (state->visible_ppu_mask&2U)==0U))
                pixels[py*width+px]=0U;
            else pixels[py*width+px]=mysmb_ppu_slot_at(v->workspace->bg,
                v->workspace->bg_second,screen_x,screen_y,(mysmb_io_u8)scroll_x,
                (mysmb_io_u8)scroll_y,table);
        }
    }
    return 1;
}
int mysmb_ppu_frame_scene_rows(const struct mysmb_ppu_frame_view *v,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows)
{
    const struct mysmb_ppu_state *state;
    mysmb_io_u16 y;
    mysmb_io_u8 colors[16];
    if(!v || !v->active || !v->state || !pixels || first>=240U ||
        rows>240U-first || rows>capacity/256U)return 0;
    state=v->state;
    if(!rows)return 1;
    for(y=0U;y<16U;++y)colors[y]=(mysmb_io_u8)y;
    colors[4]=colors[8]=colors[12]=colors[0];
    if((state->visible_ppu_mask&8U)==0U) {
        for(y=0U;y<rows;++y)memset(pixels+y*256U,colors[0],256U);
        return 1;
    }
    for(y=first;y<first+rows;++y) {
        if(v->workspace && v->workspace->bg)
            mysmb_ppu_slot_row(state,v->workspace->bg,y,state->visible_scroll_x,
                state->visible_scroll_y,state->visible_ppu_name_table,
                pixels+(y-first)*256U,colors,v->workspace,1U);
        else mysmb_ppu_background_row(state,y,state->visible_scroll_x,
            state->visible_scroll_y,state->visible_ppu_name_table,
            pixels+(y-first)*256U,v->workspace?v->workspace->decoded:0,colors);
    }
    if((state->visible_ppu_mask&2U)==0U)
        for(y=0U;y<rows;++y)memset(pixels+y*256U,0,8U);
    return 1;
}
