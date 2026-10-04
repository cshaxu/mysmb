#include "game/presentation/text/caption_scene.h"
#include "io/color.h"

static unsigned char character(unsigned char tile)
{
    if(tile<10U)return (unsigned char)('0'+tile);
    if(tile<36U)return (unsigned char)('A'+tile-10U);
    if(tile==0x28U)return '-';
    if(tile==0x29U)return 'x';
    if(tile==0x2bU)return '!';
    if(tile==0x2eU)return '$'; /* Authored status coin. */
    if(tile==0xafU)return '.';
    if(tile==0xcfU)return '@'; /* Authored ASCII copyright marker. */
    if(tile==0x9fU)return '^'; /* Original more-than-nine-lives crown. */
    return 0U;
}

static long first(short pixel,long scale,long extent)
{
    long n;
    n=(long)pixel*scale-extent/2L;
    return n>0L?(n+extent-1L)/extent:n/extent;
}

static int cell(const struct mysmb_game *g,
    struct mysmb_text_background_workspace MYSMB_IO_FAR *w,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,long x,long y,
    unsigned char c,unsigned char bg)
{
    unsigned short i;
    if(x<0L || x>=80L || y<0L || y>=50L)return 0;
    if((g->visible_ppu_mask&2U)==0U && (x*256L+128L)/80L<8L)return 0;
    i=(unsigned short)(y*80L+x);
    frame->cells[i].character=c;
    frame->cells[i].foreground=mysmb_io_color_text_contrast(bg);
    frame->cells[i].background=bg;
    w->opaque[i/8U]|=(unsigned char)(1U<<(i%8U));return 1;
}

/* DrawTitleScreen's immutable command stream declares the sign at source
 * rows4..14. Match final writes,including overlaps,not the first RLE fill.
 * This interprets output declarations only;it does not execute game logic. */
static int title_matches(const struct mysmb_game *g,
    struct mysmb_text_background_workspace MYSMB_IO_FAR *w)
{
    unsigned char MYSMB_IO_FAR *expected;
    unsigned short cursor,address,offset,index,count,bytes,i,matched;
    unsigned char control,value;
    if(g->title_data==0 || g->title_data_size==0U)return 0;
    expected=(unsigned char MYSMB_IO_FAR *)w->queue;
    for(i=0U;i<120U;++i)w->visited[i]=0U;
    cursor=matched=0U;
    while(cursor<g->title_data_size && g->title_data[cursor]!=0U) {
        if((unsigned short)(g->title_data_size-cursor)<3U)return 0;
        address=(unsigned short)(((unsigned short)g->title_data[cursor]<<8U)|
            g->title_data[cursor+1U]);control=g->title_data[cursor+2U];
        if(address<0x2000U || address>=0x4000U)return 0;
        count=control&63U;bytes=(unsigned short)((control&64U)!=0U?1U:count);
        if(count==0U || (unsigned short)(g->title_data_size-cursor)<3U+bytes)return 0;
        for(index=0U;index<count;++index) {
            value=g->title_data[cursor+3U+((control&64U)!=0U?0U:index)];
            if(address>=0x2080U && address<0x21e0U) {
                offset=(unsigned short)(address-0x2000U);
                if(offset%32U<5U || offset%32U>26U)return 0;
                expected[offset]=value;
                w->visited[offset/8U]|=(unsigned char)(1U<<(offset%8U));
            }
            address=(unsigned short)((address+((control&128U)!=0U?32U:1U))&0x3fffU);
        }
        cursor=(unsigned short)(cursor+3U+bytes);
    }
    if(cursor==g->title_data_size)return 0;
    for(i=128U;i<480U;++i)if((w->visited[i/8U]&(1U<<(i%8U)))!=0U) {
        if(g->name_table[0U][i]!=expected[i])return 0;
        ++matched;
    }
    return matched==242U;
}

static void sign_line(const struct mysmb_game *g,
    struct mysmb_text_background_workspace MYSMB_IO_FAR *w,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,long left,long right,long y,
    const char *text,unsigned char bg)
{
    unsigned short length,i;
    if(g->visible_sprite0_split && (y*240L+120L)/50L<32L)return;
    for(length=0U;text[length]!='\0';++length){}
    left+=(right-left-length)/2L;
    for(i=0U;i<length;++i)(void)cell(g,w,frame,left+i,y,(unsigned char)text[i],bg);
}

static int title_sign(const struct mysmb_game *g,
    struct mysmb_text_background_workspace MYSMB_IO_FAR *w,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{
    long x,y,left,right,top,bottom;
    unsigned short part;
    unsigned char bg,attribute,palette,c;
    if(!title_matches(g,w))return 0;
    /* Table zero's sign participates in the same scene scroll as its source. */
    left=first((short)(40-(short)g->visible_scroll_x),80L,256L);
    right=first((short)(216-(short)g->visible_scroll_x),80L,256L);
    if((g->visible_ppu_name_table&1U)!=0U){left+=80L;right+=80L;}
    attribute=g->name_table[0U][0x3c9U];palette=(unsigned char)(attribute&3U);
    bg=mysmb_io_color_text16(g->palette[palette*4U+2U]);
    for(part=0U;part<2U;++part) {
    top=first((short)(32-(short)g->visible_scroll_y+part*240U),50L,240L);
    bottom=first((short)(120-(short)g->visible_scroll_y+part*240U),50L,240L);
    for(y=top;y<bottom;++y)for(x=left;x<right;++x) {
        if(g->visible_sprite0_split && (y*240L+120L)/50L<32L)continue;
        c=y==top || y+1L==bottom?'-':x==left || x+1L==right?'|':' ';
        if((y==top || y+1L==bottom) && (x==left || x+1L==right))c='+';
        (void)cell(g,w,frame,x,y,c,bg);
    }
    sign_line(g,w,frame,left,right,top+(bottom-top)/3L,"SUPER",bg);
    sign_line(g,w,frame,left,right,top+(bottom-top)*2L/3L,"MARIO BROS.",bg);
    }
    return 1;
}

static int menu_token(const struct mysmb_game *g,unsigned short table,
    unsigned short offset,unsigned char tile)
{
    unsigned short address,start,count,step;
    if(g->title_icon_data==0 || g->title_icon_data_size!=8U ||
        tile!=g->title_icon_data[4U])return 0;
    address=(unsigned short)(0x2000U+table*0x400U+offset);
    start=(unsigned short)(((unsigned short)g->title_icon_data[1U]<<8U)|
        g->title_icon_data[2U]);count=g->title_icon_data[3U]&63U;
    step=(g->title_icon_data[3U]&128U)!=0U?32U:1U;
    return address>=start && (address-start)%step==0U &&
        (address-start)/step<count;
}

unsigned short mysmb_text_caption_scene_draw(const struct mysmb_game *g,
    struct mysmb_text_background_workspace MYSMB_IO_FAR *w,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{
    unsigned short row,col,table,offset,n,drawn,part;
    unsigned char tile,c,bg;
    int sign;
    short px,py;
    long x,y;
    if((g->visible_ppu_mask&8U)==0U)return 0U;
    drawn=0U;sign=title_sign(g,w,frame);bg=mysmb_io_color_text16(g->palette[0U]);
    for(row=0U;row<30U;++row)for(col=0U;col<64U;++col) {
        table=(unsigned short)((col/32U)^(g->visible_ppu_name_table&1U));
        offset=(unsigned short)(row*32U+col%32U);
        tile=g->name_table[table][offset];n=(unsigned short)((row/2U)*32U+col/2U);
        if(sign && table==0U && row>=4U && row<=14U &&
            col%32U>=5U && col%32U<=26U)continue;
        if(g->visible_sprite0_split && row<4U)continue;
        /* A recognized terrain object takes precedence over font-like IDs. */
        if(w->kinds[n]!=0U)continue;
        px=(short)(col*8U)-(short)g->visible_scroll_x;
        py=(short)(row*8U)-(short)g->visible_scroll_y;
        for(part=0U;part<2U;++part) {
            x=first(px,80L,256L);y=first((short)(py+part*240U),50L,240L);
            if(g->visible_sprite0_split && (y*240L+120L)/50L<32L)continue;
            if(menu_token(g,table,offset,tile)) {
                drawn+=(unsigned short)cell(g,w,frame,x,y,'(',bg);
                if(((x+1L)*256L+128L)/80L<(long)px+8L)
                    drawn+=(unsigned short)cell(g,w,frame,x+1L,y,')',bg);
                if(((y+1L)*240L+120L)/50L<(long)py+part*240L+8L) {
                    drawn+=(unsigned short)cell(g,w,frame,x,y+1L,'/',bg);
                    if(((x+1L)*256L+128L)/80L<(long)px+8L)
                        drawn+=(unsigned short)cell(g,w,frame,x+1L,y+1L,'\\',bg);
                }
            } else {
                c=character(tile);if(c==0U)continue;
                drawn+=(unsigned short)cell(g,w,frame,x,y,c,bg);
            }
        }
    }
    if(g->visible_sprite0_split)for(row=0U;row<4U;++row)for(col=0U;col<32U;++col) {
        c=character(g->name_table[0U][row*32U+col]);if(c==0U)continue;
        x=col*8UL*80UL/256UL;y=row*8UL*50UL/240UL;
        drawn+=(unsigned short)cell(g,w,frame,x,y,c,bg);
    }
    return drawn;
}
