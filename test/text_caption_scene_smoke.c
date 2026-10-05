#include "game/presentation/text/caption_scene.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game,before;
static struct mysmb_text_background_workspace workspace;
static struct mysmb_io_text_frame frame;
static unsigned char title[64],icon[8];
#define CHECK(c) do {if(!(c)){fprintf(stderr,"caption check %d\n",__LINE__);return 1;}}while(0)

static void reset(void)
{
    memset(&game,0,sizeof(game));memset(&workspace,0,sizeof(workspace));
    memset(&frame,0,sizeof(frame));
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    game.ppu.visible_ppu_mask=0x1eU;
}

static int word(const char *s)
{
    unsigned short i,j;
    for(i=0U;i<4000U;++i) {
        for(j=0U;s[j]!='\0' && i+j<4000U &&
            frame.cells[i+j].character==(unsigned char)s[j];++j){}
        if(s[j]=='\0')return 1;
    }
    return 0;
}

static void draw(void)
{
    memset(&frame,0,sizeof(frame));memset(workspace.opaque,0,sizeof(workspace.opaque));
    (void)mysmb_text_caption_scene_draw(&game,&workspace,&frame);
}

int main(void)
{
    unsigned short row,col,cursor,offset;
    reset();cursor=0U;
    /* Project-owned synthetic command declaration,not a ROM fixture. */
    for(row=4U;row<=14U;++row) {
        offset=(unsigned short)(0x2000U+row*32U+5U);
        title[cursor++]=(unsigned char)(offset>>8U);
        title[cursor++]=(unsigned char)offset;
        title[cursor++]=0x56U;title[cursor++]=0x60U;
    }
    title[cursor++]=0x20U;title[cursor++]=0x85U;
    title[cursor++]=1U;title[cursor++]=0x61U;title[cursor++]=0U;
    game.title_data=title;game.title_data_size=cursor;
    draw();CHECK(!word("SUPER"));
    for(row=4U;row<=14U;++row)for(col=5U;col<=26U;++col)
        game.ppu.name_table[0U][row*32U+col]=0x60U;
    draw();CHECK(!word("SUPER")); /* Last overlapping write not committed. */
    game.ppu.name_table[0U][0x85U]=0x61U;
    before=game;draw();CHECK(word("SUPER") && word("MARIO BROS."));
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    CHECK(game.ppu.chr_data==0); /* No bitmap/pattern binding required. */
    game.ppu.name_table[0U][0x85U]=0x24U;draw();CHECK(!word("SUPER"));
    game.ppu.name_table[0U][0x85U]=0x61U;
    game.ppu.visible_ppu_mask=0U;draw();CHECK(!word("SUPER"));
    game.ppu.visible_ppu_mask=0x1eU;game.title_data_size=cursor-1U;
    draw();CHECK(!word("SUPER"));
    game.title_data_size=cursor;game.ppu.visible_scroll_x=40U;
    draw();CHECK(word("SUPER"));
    game.ppu.visible_scroll_y=200U;draw();CHECK(word("SUPER"));

    reset();game.ppu.name_table[1U][10U*32U+8U]=0xafU;
    game.ppu.name_table[1U][10U*32U+9U]=0x2bU;
    game.ppu.visible_ppu_name_table=1U;game.ppu.visible_scroll_x=64U;
    draw();CHECK(frame.cells[17U*80U].character=='.');
    CHECK(frame.cells[17U*80U+2U].character=='!');
    CHECK((workspace.opaque[17U*10U]&1U)!=0U);
    game.ppu.name_table[1U][10U*32U+8U]=0x24U;draw();
    CHECK(frame.cells[17U*80U].character==0U);

    reset();game.ppu.name_table[1U][10U*32U+8U]=22U; /* M */
    game.ppu.visible_ppu_name_table=1U;game.ppu.visible_scroll_x=64U;
    draw();CHECK(frame.cells[17U*80U].character=='M');
    workspace.kinds[5U*32U+4U]=1U;draw();
    CHECK(frame.cells[17U*80U].character==0U);
    workspace.kinds[5U*32U+4U]=0U;
    game.ppu.visible_sprite0_split=1U;game.ppu.name_table[0U][2U*32U+3U]=22U;
    draw();CHECK(frame.cells[3U*80U+7U].character=='M');
    game.ppu.visible_scroll_x=96U;draw();
    CHECK(frame.cells[3U*80U+7U].character=='M');
    /* A source-backed caption must stay readable on every presentation
     * background,including a white intermediate-screen palette. */
    for(col=0U;col<64U;++col) {
        game.ppu.palette[0U]=(unsigned char)col;draw();
        CHECK(frame.cells[3U*80U+7U].foreground!=frame.cells[3U*80U+7U].background);
    }
    game.ppu.visible_ppu_mask=8U;game.ppu.visible_scroll_x=64U;draw();
    CHECK(frame.cells[17U*80U].character==0U); /* Left-edge mask. */

    reset();icon[1]=0x22U;icon[2]=0x49U;icon[3]=0x83U;icon[4]=0xceU;
    game.title_icon_data=icon;game.title_icon_data_size=sizeof(icon);
    game.ppu.name_table[0U][18U*32U+9U]=0xceU;
    before=game;draw();CHECK(frame.cells[30U*80U+22U].character=='(');
    game.ram[0x077aU]=1U;draw();
    CHECK(frame.cells[30U*80U+22U].character=='('); /* Queued selection is not visible. */
    game.ppu.name_table[0U][18U*32U+9U]=0x24U;
    game.ppu.name_table[0U][20U*32U+9U]=0xceU;draw();
    CHECK(frame.cells[30U*80U+22U].character==0U);
    CHECK(frame.cells[33U*80U+22U].character=='(');
    game.title_icon_data_size=7U;draw();
    CHECK(frame.cells[33U*80U+22U].character==0U);
    puts("committed title/overlap/menu/font/scroll/mask/read-only contracts pass");
    return 0;
}
