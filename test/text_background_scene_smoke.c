#include "text/background_scene.h"
#include "io/text_glyph.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game,before;
static struct mysmb_text_background_workspace workspace;
static struct mysmb_io_text_frame frame,original;
static unsigned char prg[0x8000U];
#define CHECK(c) do {if(!(c)){fprintf(stderr,"background check %d\n",__LINE__);return 1;}}while(0)

static void put(unsigned short table,unsigned short col,unsigned short row,
    unsigned short group,unsigned short index)
{
    unsigned short base,a,shift;
    base=(unsigned short)(0x1000U+group*0x100U+index*4U);
    a=(unsigned short)(row*64U+col*2U);
    game.ppu.name_table[table][a]=prg[base];
    game.ppu.name_table[table][a+32U]=prg[base+1U];
    game.ppu.name_table[table][a+1U]=prg[base+2U];
    game.ppu.name_table[table][a+33U]=prg[base+3U];
    a=(unsigned short)(0x3c0U+(row/2U)*8U+col/2U);
    shift=(unsigned short)((row%2U)*4U+(col%2U)*2U);
    game.ppu.name_table[table][a]=(unsigned char)((game.ppu.name_table[table][a]&
        ~(3U<<shift))|(group<<shift));
}

int main(void)
{
    struct mysmb_text_background_receipt r;
    unsigned short g,i,j,row;
    static const unsigned short counts[4]={39U,46U,10U,6U};
    memset(&game,0,sizeof(game));memset(prg,0,sizeof(prg));
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    memset(game.ppu.name_table[0]+0x3c0U,0,64U);
    memset(game.ppu.name_table[1]+0x3c0U,0,64U);
    for(g=0U;g<4U;++g) {
        prg[0x0b08U+g]=0U;prg[0x0b0cU+g]=(unsigned char)(0x90U+g);
        for(i=0U;i<46U;++i)for(j=0U;j<4U;++j)
            prg[0x1000U+g*0x100U+i*4U+j]=(unsigned char)(0x40U+i*4U+j);
    }
    game.area_prg=prg;game.area_prg_size=sizeof(prg);
    game.ppu.visible_ppu_mask=0x1eU;game.ppu.visible_sprite0_split=1U;
    game.ppu.palette[0U]=0x22U;game.ppu.palette[2U]=0x1aU;game.ppu.palette[6U]=0x17U;
    /* Unique owner-authored spent tuple,independent of table group. */
    prg[0x1310U]=0x31U;prg[0x1311U]=0x99U;
    prg[0x1312U]=0x33U;prg[0x1313U]=0x88U;
    /* The spent graphic remains visible with every inherited attribute.
     * The source replacement changes tiles,not attribute bytes. */
    for(g=0U;g<4U;++g) {
        put(0U,4U,8U,3U,4U);
        i=0x3c0U+4U*8U+2U;
        game.ppu.name_table[0][i]=(unsigned char)((game.ppu.name_table[0][i]&0xfcU)|g);
        game.ppu.palette[g*4U+2U]=0x17U;
        before=game;
        CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
        CHECK(r.unsupported==0U && r.objects==1U);
        CHECK(frame.cells[27U*80U+20U].character==MYSMB_IO_GLYPH_TOP_LEFT);
        CHECK(frame.cells[28U*80U+22U].background!=frame.cells[0U].background);
        CHECK(memcmp(&before,&game,sizeof(game))==0);
        /* Blank replacement stays blank;hidden blocks are not invented. */
        game.ppu.name_table[0][8U*64U+8U]=game.ppu.name_table[0][8U*64U+9U]=0x24U;
        game.ppu.name_table[0][8U*64U+40U]=game.ppu.name_table[0][8U*64U+41U]=0x24U;
        CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
        CHECK(r.objects==0U);
    }
    for(row=9U;row<12U;++row) {
        put(0U,6U,row,0U,row==9U?16U:20U);
        put(0U,7U,row,0U,row==9U?17U:21U);
    }
    before=game;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(r.recognized==480U && r.unsupported==0U && r.objects==1U);
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    CHECK(frame.cells[30U*80U+30U].character==MYSMB_IO_GLYPH_TOP_LEFT);
    CHECK(frame.cells[34U*80U+30U].character==MYSMB_IO_GLYPH_VERTICAL);
    CHECK(frame.cells[34U*80U+34U].background==frame.cells[34U*80U+30U].background);
    CHECK(frame.cells[34U*80U+34U].background!=frame.cells[0U].background);
    original=frame;
    game.ram[0x0500U]=0xc0U; /* Collision/live state cannot reveal hidden blocks. */
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(memcmp(&frame,&original,sizeof(frame))==0);
    game.ppu.palette[9U]=0x30U;game.ppu.palette[10U]=0x22U;
    for(i=0U;i<3U;++i) {
        put(0U,(unsigned short)(10U+i),5U,2U,i);
        put(0U,(unsigned short)(10U+i),6U,2U,(unsigned short)(i+3U));
    }
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(frame.cells[19U*80U+55U].background==15U);
    CHECK(frame.cells[19U*80U+55U].foreground==0U);
    i=19U*80U+55U;
    CHECK((workspace.opaque[i/8U]&(1U<<(i%8U)))!=0U);
    /* A visual alias with conflicting meanings is explicit,never guessed. */
    memcpy(prg+0x1040U,prg+0x1008U,4U);
    put(0U,1U,5U,0U,2U);
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(r.ambiguous==1U);
    /* HUD stays table zero and unscrolled while table one is the scene. */
    game.ppu.name_table[0U][2U*32U+3U]=22U; /* M */
    game.ppu.name_table[0U][2U*32U+4U]=10U; /* A */
    game.ppu.visible_ppu_name_table=1U;game.ppu.visible_scroll_x=64U;
    put(1U,6U,10U,1U,20U);
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(frame.cells[3U*80U+7U].character=='M');
    CHECK(frame.cells[3U*80U+10U].character=='A');
    CHECK(frame.cells[34U*80U+12U].character==':');
    CHECK(r.letters==2U);
    /* Distinct semantic writers,using authored tuples rather than CHR art. */
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    memset(game.ppu.name_table[0]+0x3c0U,0,64U);
    memset(game.ppu.name_table[1]+0x3c0U,0,64U);
    game.ppu.visible_ppu_name_table=0U;game.ppu.visible_scroll_x=0U;
    for(i=0U;i<3U;++i) {
        put(0U,(unsigned short)(4U+i),8U,0U,(unsigned short)(28U+i));
        put(0U,(unsigned short)(4U+i),9U,0U,(unsigned short)(31U+i));
    }
    before=game;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    CHECK(frame.cells[28U*80U+20U].character==MYSMB_IO_GLYPH_VERTICAL);
    CHECK(frame.cells[27U*80U+25U].character==MYSMB_IO_GLYPH_HORIZONTAL);
    CHECK(frame.cells[30U*80U+25U].character==' ');
    CHECK(frame.cells[30U*80U+25U].background!=frame.cells[0U].background);
    /* A shaft alone has no invented mouth. Connected geometry never fills
     * the missing top-right member of an L-shaped pipe. */
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    memset(game.ppu.name_table[0]+0x3c0U,0,64U);
    memset(game.ppu.name_table[1]+0x3c0U,0,64U);
    put(0U,4U,8U,0U,20U);put(0U,4U,9U,0U,20U);
    put(0U,5U,9U,0U,21U);
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(r.objects==1U);
    CHECK(frame.cells[27U*80U+24U].character==' ');
    CHECK(frame.cells[27U*80U+27U].background==frame.cells[0U].background);
    i=27U*80U+27U;
    CHECK((workspace.opaque[i/8U]&(1U<<(i%8U)))==0U);
    /* A completely enclosed hole is absent too,not merely an edge gap. */
    for(row=8U;row<11U;++row)for(i=4U;i<7U;++i)
        if(row!=9U || i!=5U)put(0U,i,row,0U,20U);
    /* The earlier L fixture populated this cell;clear its four source tiles. */
    game.ppu.name_table[0U][9U*64U+10U]=0x24U;
    game.ppu.name_table[0U][9U*64U+42U]=0x24U;
    game.ppu.name_table[0U][9U*64U+11U]=0x24U;
    game.ppu.name_table[0U][9U*64U+43U]=0x24U;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(r.objects==1U);
    CHECK(frame.cells[32U*80U+27U].background==frame.cells[0U].background);
    i=32U*80U+27U;
    CHECK((workspace.opaque[i/8U]&(1U<<(i%8U)))==0U);
    /* Horizontal rope and pulley stay horizontal/separate;chain and plant
     * are narrow authored silhouettes rather than filled rectangles. */
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    memset(game.ppu.name_table[0]+0x3c0U,0,64U);
    memset(game.ppu.name_table[1]+0x3c0U,0,64U);
    put(0U,4U,8U,1U,1U);put(0U,5U,8U,1U,1U);
    put(0U,6U,8U,1U,2U);put(0U,8U,8U,0U,12U);
    put(0U,10U,8U,0U,34U);put(0U,12U,8U,3U,5U);
    put(0U,14U,8U,0U,1U);
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(r.unsupported==0U);
    CHECK(frame.cells[28U*80U+20U].character=='=');
    CHECK(frame.cells[28U*80U+27U].character=='=');
    CHECK(frame.cells[27U*80U+24U].character==' ');
    CHECK(frame.cells[28U*80U+32U].character=='O');
    CHECK(frame.cells[28U*80U+42U].character=='o');
    CHECK(frame.cells[27U*80U+52U].character=='^');
    /* Source coral ink3 is pink;ink2 is water blue. Glyphs must carry the
     * coral role,while gaps retain water and later palette changes survive. */
    game.ppu.palette[2U]=0x12U;game.ppu.palette[3U]=0x25U;
    before=game;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(frame.cells[27U*80U+52U].foreground==13U);
    CHECK(frame.cells[27U*80U+52U].background==frame.cells[0U].background);
    CHECK(frame.cells[27U*80U+50U].background==frame.cells[0U].background);
    CHECK(frame.cells[28U*80U+51U].foreground==13U);
    CHECK(frame.cells[28U*80U+51U].background==frame.cells[0U].background);
    CHECK(memcmp(&before,&game,sizeof(game))==0);
    game.ppu.palette[3U]=0x30U;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(frame.cells[27U*80U+52U].foreground==15U);
    CHECK(frame.cells[27U*80U+52U].background==frame.cells[0U].background);
    game.ppu.palette[3U]=0x0fU;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(frame.cells[27U*80U+52U].foreground==0U);
    CHECK(frame.cells[27U*80U+52U].background==frame.cells[0U].background);
    CHECK(frame.cells[28U*80U+62U].character=='|');
    CHECK(frame.cells[28U*80U+72U].background==0U);
    /* Fractional scroll keeps the first covered row's outline. */
    game.ppu.visible_scroll_x=7U;game.ppu.visible_scroll_y=1U;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(frame.cells[26U*80U+50U].character=='^');
    /* Every reviewed metatile position has a semantic class. Author-owned
     * unique tuples test the classifier without importing original art. */
    game.ppu.visible_scroll_x=game.ppu.visible_scroll_y=0U;
    /* Restore the intentional alias fixture before the unique-tuple census. */
    for(j=0U;j<4U;++j)prg[0x1040U+j]=(unsigned char)(0x80U+j);
    for(g=0U;g<4U;++g)for(i=0U;i<counts[g];++i) {
        memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
        memset(game.ppu.name_table[0]+0x3c0U,0,64U);
        memset(game.ppu.name_table[1]+0x3c0U,0,64U);
        put(0U,4U,8U,g,i);
        CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
        if(r.unsupported!=0U || r.ambiguous!=0U)
            fprintf(stderr,"class group=%u index=%u unsupported=%u ambiguous=%u\n",
                g,i,r.unsupported,r.ambiguous);
        CHECK(r.recognized==480U && r.unsupported==0U && r.ambiguous==0U);
    }
    /* Tree canopy/trunk and fence are distinct source positions,not bushes,
     * generic stumps or terrain. These tuples are authored fixture data. */
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    memset(game.ppu.name_table[0]+0x3c0U,0,64U);
    memset(game.ppu.name_table[1]+0x3c0U,0,64U);
    game.ppu.palette[1U]=0x30U;game.ppu.palette[2U]=0x00U;game.ppu.palette[3U]=0x0fU;
    game.ppu.palette[5U]=0x36U;game.ppu.palette[6U]=0x17U;game.ppu.palette[7U]=0x0fU;
    put(0U,4U,8U,0U,13U);put(0U,4U,9U,0U,15U);
    put(0U,4U,10U,1U,14U);put(0U,4U,11U,1U,14U);
    put(0U,8U,9U,0U,14U);put(0U,8U,10U,1U,14U);
    put(0U,10U,10U,1U,13U);put(0U,11U,10U,1U,13U);
    put(0U,12U,10U,1U,20U);
    before=game;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(memcmp(&before,&game,sizeof(game))==0);
    CHECK(r.unsupported==0U && r.objects==6U);
    CHECK(frame.cells[27U*80U+21U].character=='/');
    CHECK(frame.cells[29U*80U+22U].background==15U);
    CHECK(frame.cells[27U*80U+20U].background==frame.cells[0U].background);
    CHECK(frame.cells[33U*80U+21U].character=='|');
    CHECK(frame.cells[33U*80U+20U].background==frame.cells[0U].background);
    CHECK(frame.cells[30U*80U+41U].character=='/');
    CHECK(frame.cells[33U*80U+50U].character=='|');
    CHECK(frame.cells[34U*80U+51U].character=='=');
    CHECK(frame.cells[33U*80U+50U].background==14U);
    CHECK(frame.cells[34U*80U+51U].background==14U);
    CHECK(frame.cells[34U*80U+51U].foreground==6U);
    CHECK(frame.cells[34U*80U+51U].background!=frame.cells[34U*80U+62U].background);
    CHECK(frame.cells[33U*80U+51U].background==frame.cells[0U].background);
    CHECK(frame.cells[34U*80U+62U].character==':');
    /* Dynamic palette changes update the canopy role without copying colors
     * into the template;fractional scroll must preserve decorative holes. */
    game.ppu.palette[1U]=0x1aU;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(frame.cells[29U*80U+22U].background!=15U);
    game.ppu.visible_scroll_x=7U;game.ppu.visible_scroll_y=1U;
    before=game;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(memcmp(&before,&game,sizeof(game))==0);
    CHECK(frame.cells[33U*80U+49U].background==frame.cells[0U].background);
    /* Disabled background produces only the universal color. */
    game.ppu.visible_ppu_mask=0U;
    CHECK(mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(r.objects==0U && frame.cells[3U*80U+7U].character==' ');
    for(i=0U;i<500U;++i)CHECK(workspace.opaque[i]==0U);
    before=game;original=frame;game.area_prg_size=0U;
    CHECK(!mysmb_text_background_scene_build(&game,&workspace,&frame,&r));
    CHECK(memcmp(&frame,&original,sizeof(frame))==0);
    puts("semantic background: grouped pipe/fill/alias/hidden/HUD/scroll/read-only passed");
    return 0;
}
