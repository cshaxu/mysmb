#include "game/presentation/text/background_scene.h"
#include "game/presentation/text/elements.h"
#include "io/color.h"

/* Visual classifications of reviewed metatile positions, not gameplay IDs.
 * Graphics are read from the existing immutable resource binding. No CHR
 * patterns, collision buffers or pixel-to-character conversion are used. */
enum { UNKNOWN, BLANK, BRICK, GROUND, QUESTION, EMPTY, COIN, PIPE,
    CLOUD, BUSH, HILL, WATER, LEDGE, TRUNK, CASTLE, ROPE, FLAG, CANNON };

static unsigned char kind(unsigned short group,unsigned short index)
{
    if(group==0U) {
        if(index==0U || index==35U || index==38U)return BLANK;
        if(index>=2U && index<=4U)return BUSH;
        if(index>=5U && index<=10U)return HILL;
        if(index>=13U && index<=15U)return BUSH;
        if((index>=16U && index<=21U) || (index>=28U && index<=33U))return PIPE;
        if(index>=22U && index<=27U)return LEDGE;
        if(index==11U)return LEDGE;
        if(index==12U)return ROPE;
        if(index==36U || index==37U)return FLAG;
    } else if(group==1U) {
        if(index==4U || index==31U || index==32U || index==39U)return BLANK;
        if(index<=3U)return ROPE;
        /* Castle walls and ordinary bricks share a visual alias. Both use
         * the same brick presentation instead of inventing their identity. */
        if(index==7U || (index>=17U && index<=19U) ||
            (index>=21U && index<=30U) || index==40U || index==42U)return BRICK;
        if(index>=5U && index<=11U)return CASTLE;
        if(index>=12U && index<=16U)return TRUNK;
        if(index==20U || index==33U || index==34U || index==41U)return GROUND;
        if(index==35U)return LEDGE;
        if(index>=36U && index<=38U)return CANNON;
        if(index==43U || index==44U)return PIPE;
        if(index==45U)return FLAG;
    } else if(group==2U) {
        if(index<=5U)return CLOUD;
        if(index==6U || index==7U)return WATER;
        if(index==8U)return GROUND;
        if(index==9U)return LEDGE;
    } else {
        if(index<=1U)return QUESTION;
        if(index==2U || index==3U)return COIN;
        if(index==4U)return EMPTY;
    }
    return UNKNOWN;
}

static unsigned char decode(const struct mysmb_game *g,unsigned short column,
    unsigned short row,unsigned char table,unsigned char *palette,
    unsigned char *ambiguous)
{
    static const unsigned char counts[4]={39U,46U,10U,6U};
    unsigned short tile_row,tile_col,a,base,index,j,offset;
    unsigned char tiles[4],found,candidate,attribute;
    tile_row=(unsigned short)(row*2U);tile_col=(unsigned short)(column*2U);
    a=(unsigned short)(tile_row*32U+tile_col);
    tiles[0]=g->name_table[table][a];tiles[1]=g->name_table[table][a+32U];
    tiles[2]=g->name_table[table][a+1U];tiles[3]=g->name_table[table][a+33U];
    attribute=g->name_table[table][0x3c0U+(tile_row/4U)*8U+tile_col/4U];
    *palette=(unsigned char)((attribute>>(((tile_row&2U)<<1U)+(tile_col&2U)))&3U);
    *ambiguous=0U;
    if(tiles[0]==0x24U && tiles[1]==0x24U &&
        tiles[2]==0x24U && tiles[3]==0x24U)return BLANK;
    base=(unsigned short)(g->area_prg[0x0b08U+*palette] |
        ((unsigned short)g->area_prg[0x0b0cU+*palette]<<8U));
    if(base<0x8000U)return UNKNOWN;
    base=(unsigned short)(base-0x8000U);found=UNKNOWN;
    for(index=0U;index<counts[*palette];++index) {
        offset=(unsigned short)(base+index*4U);
        if((unsigned long)base+index*4UL+4UL>g->area_prg_size)break;
        for(j=0U;j<4U;++j)if(tiles[j]!=g->area_prg[offset+j])break;
        if(j!=4U)continue;
        candidate=kind(*palette,index);
        if(candidate==UNKNOWN)continue;
        if(found!=UNKNOWN && found!=candidate) {*ambiguous=1U;return UNKNOWN;}
        found=candidate;
    }
    return found;
}

static int grouped(unsigned char k)
{
    return k==PIPE || k==CLOUD || k==BUSH || k==HILL || k==WATER ||
        k==LEDGE || k==TRUNK || k==CASTLE || k==ROPE || k==FLAG || k==CANNON;
}

static unsigned short inset(unsigned char k,unsigned short y,
    unsigned short width,unsigned short height)
{
    if(k==HILL)return (unsigned short)((unsigned long)(height-1U-y)*width/(2UL*height));
    if(k==CLOUD)return y==0U?width/4U:y==1U?width/8U:0U;
    if(k==BUSH)return y==0U?width/8U:0U;
    return 0U;
}

static void enqueue(struct mysmb_text_background_workspace MYSMB_IO_FAR *w,
    unsigned short n,unsigned char k,unsigned char p,unsigned short *tail)
{
    if(w->visited[n]!=0U || w->kinds[n]!=k || w->palettes[n]!=p)return;
    w->visited[n]=1U;w->queue[(*tail)++]=n;
}

/* Authored scalable object silhouettes, borders and interior fill. The
 * connected semantic parts select one whole-object geometry, not one glyph
 * per source tile. Repeated terrain blocks remain separate brick objects. */
static unsigned char glyph(unsigned char k,unsigned short x,unsigned short y,
    unsigned short width,unsigned short height)
{
    unsigned short margin;
    if(k==COIN)return (x==width/2U)?'$':' ';
    if(k==ROPE || k==FLAG)return x==width/2U?'|':' ';
    if(k==CLOUD || k==BUSH || k==HILL) {
        margin=inset(k,y,width,height);
        if(y==0U)return k==CLOUD?'_':'^';
        if(x==margin)return k==HILL?'/':'(';
        if(x+margin+1U==width)return k==HILL?'\\':')';
        return y+1U==height?'_':' ';
    }
    if(k==WATER)return y==0U?'~':' ';
    if(k==PIPE) {
        if(y==0U || (height>3U && y==2U))return '=';
        return x==0U || x+1U==width?'|':' ';
    }
    if(k==LEDGE)return y==0U?'=':' ';
    if(k==TRUNK)return x==0U || x+1U==width?'|':':';
    if(k==CANNON)return y==0U?'=':x==0U || x+1U==width?'|':' ';
    if(x==0U || x+1U==width)return y==0U || y+1U==height?'+':'|';
    if(y==0U || y+1U==height)return '-';
    if(k==QUESTION)return x==width/2U && y==height/2U?'?':' ';
    if(k==BRICK || k==CASTLE)return '#';
    if(k==GROUND)return ':';
    return ' ';
}

static void object(const struct mysmb_game *g,
    struct mysmb_text_background_workspace MYSMB_IO_FAR *w,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,unsigned char k,
    unsigned char palette,short left,short top,short right,short bottom)
{
    long x0,y0,x1,y1,x,y;
    unsigned short cell,width,height;
    unsigned char c,color;
    x0=left>=0?(long)left*80L/256L:-((-(long)left*80L+255L)/256L);
    y0=top>=0?(long)top*50L/240L:-((-(long)top*50L+239L)/240L);
    x1=(long)right*80L/256L;y1=(long)bottom*50L/240L;
    if(g->visible_sprite0_split!=0U && top>=32 && y0<7L)y0=7L;
    if(x1<=x0 || y1<=y0)return;
    width=(unsigned short)(x1-x0);height=(unsigned short)(y1-y0);
    color=mysmb_io_color_text16(g->palette[palette*4U+
        (k==CLOUD?1U:k==COIN || k==QUESTION?3U:2U)]);
    for(y=y0;y<y1;++y)for(x=x0;x<x1;++x) {
        if(x<0L || x>=80L || y<0L || y>=50L)continue;
        if(g->visible_sprite0_split!=0U && (y*240L+120L)/50L<32L)continue;
        if((g->visible_ppu_mask&2U)==0U && (x*256L+128L)/80L<8L)continue;
        c=glyph(k,(unsigned short)(x-x0),(unsigned short)(y-y0),width,height);
        if((k==COIN || k==ROPE || k==FLAG) && c==' ')continue;
        if((unsigned short)(x-x0)<inset(k,(unsigned short)(y-y0),width,height) ||
            (unsigned short)(width-1U-(x-x0))<
                inset(k,(unsigned short)(y-y0),width,height))continue;
        cell=(unsigned short)(y*80L+x);
        w->opaque[cell/8U]|=(unsigned char)(1U<<(cell%8U));
        frame->cells[cell].character=c;
        frame->cells[cell].foreground=k==CLOUD?8U:15U;
        frame->cells[cell].background=color;
    }
}

static unsigned char letter(unsigned char tile)
{
    if(tile<10U)return (unsigned char)('0'+tile);
    if(tile<36U)return (unsigned char)('A'+tile-10U);
    if(tile==0x28U)return '-';
    if(tile==0x29U)return 'x';
    return 0U;
}

int mysmb_text_background_scene_build(const struct mysmb_game *g,
    struct mysmb_text_background_workspace MYSMB_IO_FAR *w,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    struct mysmb_text_background_receipt *receipt)
{
    unsigned short i,row,col,head,tail,n,minx,maxx,miny,maxy,cell;
    unsigned char p,k,ambiguous,table,c;
    short left,top,right,bottom;
    if(g==0 || w==0 || frame==0 || receipt==0 || g->area_prg==0 ||
        g->area_prg_size<0x0b10U)return 0;
    receipt->recognized=receipt->unsupported=receipt->ambiguous=0U;
    receipt->objects=receipt->letters=0U;
    for(i=0U;i<500U;++i)w->opaque[i]=0U;
    (void)mysmb_text_elements_build(0,0U,mysmb_io_color_text16(g->palette[0]),frame);
    if((g->visible_ppu_mask&8U)==0U)return 1;
    for(i=0U;i<480U;++i) {
        row=i/32U;col=i%32U;table=(unsigned char)((col/16U)^(g->visible_ppu_name_table&1U));
        k=decode(g,col%16U,row,table,&p,&ambiguous);
        w->kinds[i]=k;w->palettes[i]=p;w->visited[i]=0U;
        if(ambiguous!=0U)receipt->ambiguous++;
        if(k==UNKNOWN)receipt->unsupported++;else receipt->recognized++;
    }
    for(i=0U;i<480U;++i) {
        k=w->kinds[i];p=w->palettes[i];
        if(w->visited[i]!=0U || k==UNKNOWN || k==BLANK)continue;
        head=tail=0U;enqueue(w,i,k,p,&tail);
        minx=maxx=i%32U;miny=maxy=i/32U;
        while(head<tail) {
            n=w->queue[head++];row=n/32U;col=n%32U;
            if(col<minx)minx=col;
            if(col>maxx)maxx=col;
            if(row<miny)miny=row;
            if(row>maxy)maxy=row;
            if(!grouped(k))continue;
            if(col!=0U)enqueue(w,(unsigned short)(n-1U),k,p,&tail);
            if(col!=31U)enqueue(w,(unsigned short)(n+1U),k,p,&tail);
            if(row!=0U)enqueue(w,(unsigned short)(n-32U),k,p,&tail);
            if(row!=14U)enqueue(w,(unsigned short)(n+32U),k,p,&tail);
        }
        left=(short)(minx*16U)-(short)g->visible_scroll_x;
        right=(short)((maxx+1U)*16U)-(short)g->visible_scroll_x;
        top=(short)(miny*16U)-(short)g->visible_scroll_y;
        bottom=(short)((maxy+1U)*16U)-(short)g->visible_scroll_y;
        object(g,w,frame,k,p,left,top,right,bottom);
        object(g,w,frame,k,p,left,(short)(top+240),right,(short)(bottom+240));
        receipt->objects++;
    }
    /* Fixed HUD letters use the committed table-zero region, never RAM digits.
     * Other strings/title logo await an explicit semantic text-owner mapping. */
    if(g->visible_sprite0_split!=0U)for(row=0U;row<4U;++row)for(col=0U;col<32U;++col) {
        if(col==0U && (g->visible_ppu_mask&2U)==0U)continue;
        c=letter(g->name_table[0U][row*32U+col]);if(c==0U)continue;
        cell=(unsigned short)((row*8UL*50UL/240UL)*80UL+col*8UL*80UL/256UL);
        frame->cells[cell].character=c;frame->cells[cell].foreground=15U;
        w->opaque[cell/8U]|=(unsigned char)(1U<<(cell%8U));
        receipt->letters++;
    }
    return 1;
}
