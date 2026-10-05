#include "ppu/frame.h"
#include <string.h>
void mysmb_ppu_frame_workspace_bind(struct mysmb_ppu_frame_workspace *workspace,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded)
{
    workspace->decoded=decoded;workspace->chr=0;
    workspace->chr_size=0U;workspace->valid=0U;
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
    source_y = (mysmb_io_u16)((screen_y + scroll_y) % 480U);
    table = (mysmb_io_u16)(name_table & 3U);
    if (source_x >= 256U) table ^= 1U;
    if (source_y >= 240U) table ^= 2U;
    /* SMB1 vertical mirroring: logical 0/2 and 1/3 share CIRAM. */
    table &= 1U;
    row = (source_y % 240U) / 8U;
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

/* Decode once per visible tile row,not once per pixel. The partial first and
 * last tiles retain exact scroll,mirroring,CHR bounds and left-edge semantics. */
static void mysmb_ppu_background_row(const struct mysmb_ppu_state *state,
    mysmb_io_u16 y,mysmb_io_u8 scroll_x,mysmb_io_u8 scroll_y,mysmb_io_u8 name_table,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *out,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded_chr)
{
    mysmb_io_u16 source_y,row,source_x,x,column,table,pattern,count,i;
    mysmb_io_u8 attribute,palette,low,high,color,phase;
    mysmb_io_u8 pixels[MYSMB_PPU_FRAME_WIDTH],colors[16];
    const mysmb_io_u8 *chr;
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded;
    mysmb_io_u16 chr_size,pattern_base;
    /* Palette and row staging are stack-owned. Avoid a far state/pixel access
     * for every output dot; one bounded copy publishes the completed row. */
    for(i=0U;i<16U;++i)colors[i]=state->palette[i];
    colors[4]=colors[8]=colors[12]=colors[0];
    chr=state->chr_data;chr_size=state->chr_data_size;
    pattern_base=(state->visible_ppu_control_0&0x10U)?0x1000U:0U;
    source_y=(mysmb_io_u16)((y+scroll_y)%480U);
    row=(mysmb_io_u16)((source_y%240U)/8U);
    source_x=scroll_x;x=0U;
    while(x<MYSMB_PPU_FRAME_WIDTH) {
        table=(mysmb_io_u16)((name_table^((source_x>>8U)&1U))&1U);
        column=(mysmb_io_u16)((source_x&255U)>>3U);
        attribute=state->name_table[table][0x3c0U+(row>>2U)*8U+(column>>2U)];
        palette=(mysmb_io_u8)((attribute>>(((row&2U)<<1U)+(column&2U)))&3U);
        pattern=(mysmb_io_u16)(pattern_base+
            state->name_table[table][row*32U+column]*16U+(source_y&7U));
        phase=(mysmb_io_u8)(source_x&7U);
        low=(mysmb_io_u8)((chr!=0 && pattern<chr_size?chr[pattern]:0U)<<phase);
        high=(mysmb_io_u8)((chr!=0 && pattern+8U<chr_size?chr[pattern+8U]:0U)<<phase);
        palette=(mysmb_io_u8)(palette*4U);
        count=(mysmb_io_u16)(8U-phase);
        if(count>MYSMB_PPU_FRAME_WIDTH-x)count=(mysmb_io_u16)(MYSMB_PPU_FRAME_WIDTH-x);
        if(decoded_chr) {
            decoded=decoded_chr+(pattern/16U)*16U+(pattern&7U)*2U;
            if(count==8U) {
                low=decoded[0U];high=decoded[1U];
                pixels[x+0U]=colors[palette+((low>>0U)&3U)];
                pixels[x+1U]=colors[palette+((low>>2U)&3U)];
                pixels[x+2U]=colors[palette+((low>>4U)&3U)];
                pixels[x+3U]=colors[palette+((low>>6U)&3U)];
                pixels[x+4U]=colors[palette+((high>>0U)&3U)];
                pixels[x+5U]=colors[palette+((high>>2U)&3U)];
                pixels[x+6U]=colors[palette+((high>>4U)&3U)];
                pixels[x+7U]=colors[palette+((high>>6U)&3U)];
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
    if((state->visible_ppu_mask&2U)==0U)
        for(x=0U;x<8U;++x)pixels[x]=colors[0U];
    memcpy(out,pixels,MYSMB_PPU_FRAME_WIDTH);
}

static void mysmb_ppu_frame_build_internal(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame *frame,const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded_chr)
{
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

    /* Source flag zero reaches SkipSprite0 during VBlank, so the entire
     * visible frame uses scene scroll. A synchronized frame retains its
     * fixed top region; never reread the following frame's RAM flag here. */
    fixed_top_height = state->visible_sprite0_split != 0U ?
        MYSMB_PPU_STATUS_BAR_HEIGHT : 0U;
    for (y = 0U; y < MYSMB_PPU_FRAME_HEIGHT; ++y) {
        scroll_x = y < fixed_top_height ? 0U : state->visible_scroll_x;
        scroll_y = y < fixed_top_height ? 0U : state->visible_scroll_y;
        if((state->visible_ppu_mask&8U)!=0U)
            mysmb_ppu_background_row(state,y,scroll_x,scroll_y,
                y<fixed_top_height?0U:state->visible_ppu_name_table,
                frame->pixels+y*MYSMB_PPU_FRAME_WIDTH,decoded_chr);
        else for(x=0U;x<MYSMB_PPU_FRAME_WIDTH;++x)
            frame->pixels[y*MYSMB_PPU_FRAME_WIDTH+x]=state->palette[0U];
    }
    if ((state->visible_ppu_mask & 0x10U) == 0U) return;
    for (sprite = 64U; sprite != 0U;) {
        --sprite;
        sprite_y = (mysmb_io_u16)state->visible_oam[sprite * 4U] + 1U;
        sprite_x = state->visible_oam[sprite * 4U + 3U];
        attributes = state->visible_oam[sprite * 4U + 2U];
        if (sprite_y >= MYSMB_PPU_FRAME_HEIGHT) continue;
        for (pixel_y = 0U; pixel_y < 8U && sprite_y + pixel_y < MYSMB_PPU_FRAME_HEIGHT;
             ++pixel_y) {
            pattern = (mysmb_io_u16)(((state->visible_ppu_control_0 & 0x08U) != 0U ?
                0x1000U : 0U) + state->visible_oam[sprite * 4U + 1U] * 16U +
                ((attributes & 0x80U) != 0U ? 7U - pixel_y : pixel_y));
            low = mysmb_ppu_pattern(state, pattern);
            high = mysmb_ppu_pattern(state, (mysmb_io_u16)(pattern + 8U));
            for (pixel_x = 0U; pixel_x < 8U && sprite_x + pixel_x < MYSMB_PPU_FRAME_WIDTH;
                 ++pixel_x) {
                if(decoded_chr) {
                    color=(mysmb_io_u8)((attributes&0x40U)?7U-pixel_x:pixel_x);
                    color=(mysmb_io_u8)((decoded_chr[(pattern/16U)*16U+
                        (pattern&7U)*2U+color/4U]>>((color%4U)*2U))&3U);
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
                    mysmb_ppu_background_opaque(state, x, y, scroll_x, scroll_y,
                        y < fixed_top_height ? 0U : state->visible_ppu_name_table,
                        &opaque,decoded_chr);
                    if (opaque != 0U) continue;
                }
                frame->pixels[y * MYSMB_PPU_FRAME_WIDTH + x] = state->palette[
                    0x10U + (mysmb_io_u16)((attributes & 3U) * 4U + color)];
            }
        }
    }
    (void)mysmb_ppu_master_color[0];
}

void mysmb_ppu_frame_build(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame *frame)
{
    mysmb_ppu_frame_build_internal(state,frame,0);
}
void mysmb_ppu_frame_build_cached(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame *frame,struct mysmb_ppu_frame_workspace *workspace)
{
    mysmb_ppu_prepare_chr(state,workspace);
    mysmb_ppu_frame_build_internal(state,frame,workspace?workspace->decoded:0);
}
