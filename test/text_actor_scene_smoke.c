#include "io/text_glyph.h"
#include "game/presentation/text/actor_scene.h"
#include "game/frame_root.h"
#include "io/color.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_text_actor_workspace actor_workspace;
static struct mysmb_game game,before;
static struct mysmb_io_text_frame frame,original;
static unsigned char prg[0x8000U];
static unsigned char opaque[500];
#define CHECK(c) do {if(!(c)){fprintf(stderr,"scene check %d\n",__LINE__);return 1;}}while(0)

static void sprite(unsigned short index,unsigned char x,unsigned char y)
{
    game.ram[0x0200U+index*4U]=y;
    game.ram[0x0201U+index*4U]=1U;
    game.ram[0x0202U+index*4U]=0U;
    game.ram[0x0203U+index*4U]=x;
}

/* Information sprites must remain readable whole words,including fractional
 * anchors and white source ink. Covers11float values plus5flag values. */
static int dynamic_words(void)
{
    static const char *labels[16]={"100","200","400","500","800","1000",
        "2000","4000","5000","8000","1UP","5000","2000","800","400","100"};
    struct mysmb_text_actor_receipt receipt;
    unsigned short value,bg,dx,dy,i,first,row,index,cases;
    cases=0U;
    for(value=0U;value<16U;++value)for(bg=0U;bg<16U;++bg)
        for(dx=0U;dx<8U;++dx)for(dy=0U;dy<8U;++dy) {
            memset(&game,0,sizeof(game));game.visible_ppu_mask=0x1eU;
            game.palette[0x12U]=0x30U;
            for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
            mysmb_text_observer_enable(&game,1U);
            if(value<11U) {
                sprite(8U,(unsigned char)(80U+dx),(unsigned char)(95U+dy));
                sprite(9U,(unsigned char)(88U+dx),(unsigned char)(95U+dy));
                mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_SCORE,
                    0U,0U,(unsigned char)(value+1U),1U,32U,2U,0U);
            } else {
                sprite(8U,32U,159U);sprite(9U,40U,159U);sprite(10U,40U,167U);
                sprite(11U,(unsigned char)(80U+dx),(unsigned char)(95U+dy));
                sprite(12U,(unsigned char)(88U+dx),(unsigned char)(95U+dy));
                mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_FLAG,
                    0U,0U,(unsigned char)(value-11U),1U,32U,5U,0U);
            }
            mysmb_game_submit_oam(&game);before=game;
            CHECK(mysmb_text_elements_build(0,0U,(mysmb_io_u8)bg,&frame));
            CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
            CHECK(receipt.drawn==1U && receipt.unsupported==0U);
            CHECK(memcmp(&game,&before,sizeof(game))==0);
            first=(unsigned short)(((80UL+dx)*80UL+127UL)/256UL);
            row=(unsigned short)(((96UL+dy)*50UL+119UL)/240UL);
            for(i=0U;labels[value][i]!='\0';++i) {
                index=(unsigned short)(row*80U+first+i);
                CHECK(frame.cells[index].character==(unsigned char)labels[value][i]);
                CHECK(frame.cells[index].background==bg);
                CHECK(frame.cells[index].foreground!=bg);
            }
            ++cases;
        }
    printf("dynamic score words: %u value/background/fractional-position cases passed\n",cases);
    return 0;
}

static int mushroom_colors(void)
{
    struct mysmb_text_actor_receipt receipt;
    unsigned short palette,identity,i;
    unsigned char cap,mark,stem;
    for(identity=0U;identity<=3U;++identity)for(palette=0U;palette<4U;++palette) {
        memset(&game,0,sizeof(game));
        for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
        game.visible_ppu_mask=0x1eU;
        game.palette[0x11U+palette*4U]=identity==0U?0x16U:0x1aU;
        game.palette[0x12U+palette*4U]=0x30U;
        game.palette[0x13U+palette*4U]=0x27U;
        mysmb_text_observer_enable(&game,1U);
        sprite(8U,80U,95U);sprite(9U,88U,95U);
        sprite(10U,80U,103U);sprite(11U,88U,103U);
        for(i=8U;i<12U;++i)game.ram[0x0202U+i*4U]=(unsigned char)palette;
        mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_POWERUP,
            (unsigned char)identity,5U,0U,1U,32U,4U,0U);
        mysmb_game_submit_oam(&game);
        /* Live producer changes cannot recolor the committed actor. */
        for(i=8U;i<12U;++i)game.ram[0x0202U+i*4U]=(unsigned char)((palette+1U)&3U);
        before=game;
        CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
        CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
        cap=mysmb_io_color_text16(0x27U);
        mark=mysmb_io_color_text16(identity==0U?0x16U:0x1aU);
        stem=mysmb_io_color_text16(0x30U);
        CHECK(memcmp(&before,&game,sizeof(game))==0);
        if(identity==1U) {
            CHECK(frame.cells[20U*80U+27U].background==stem);
            CHECK(frame.cells[20U*80U+27U].foreground==cap);
            CHECK(frame.cells[22U*80U+27U].background==mark);
            game.palette[0x13U+palette*4U]=0x1aU;
            CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
            CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
            CHECK(frame.cells[20U*80U+27U].foreground==mark);
            continue;
        }
        if(identity==2U) {
            CHECK(frame.cells[21U*80U+27U].background==cap);
            CHECK(frame.cells[21U*80U+27U].foreground==mark);
            game.palette[0x13U+palette*4U]=0x16U;
            CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
            CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
            CHECK(frame.cells[21U*80U+27U].background==mysmb_io_color_text16(0x16U));
            continue;
        }
        CHECK(cap!=stem && mark!=cap);
        CHECK(frame.cells[20U*80U+27U].foreground==cap);
        CHECK(frame.cells[21U*80U+27U].background==cap);
        CHECK(frame.cells[21U*80U+27U].foreground==mark);
        CHECK(frame.cells[22U*80U+27U].background==stem);
        CHECK(memcmp(&before,&game,sizeof(game))==0);
        /* Palette changes recolor the same committed template without a
         * selector rerun or another DMA. */
        game.palette[0x13U+palette*4U]=0x12U;
        CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
        CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
        /* A cap quantized to the sky uses the existing visible-ink fallback. */
        CHECK(mysmb_io_color_text16(0x12U)==9U);
        CHECK(frame.cells[20U*80U+27U].foreground==mark);
        game.palette[0x13U+palette*4U]=0x1aU;
        CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
        CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
        CHECK(frame.cells[20U*80U+27U].foreground==mysmb_io_color_text16(0x1aU));
    }
    return 0;
}

static int retainer_details(void)
{
    struct mysmb_text_actor_receipt receipt;
    unsigned short form,p,i,c,colors,dy,row;
    unsigned char red,white,skin;
    for(form=0U;form<2U;++form)for(p=0U;p<4U;++p)for(dy=0U;dy<8U;++dy) {
        memset(&game,0,sizeof(game));game.visible_ppu_mask=0x1eU;
        for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
        game.palette[0x11U+p*4U]=0x16U;
        game.palette[0x12U+p*4U]=0x30U;
        game.palette[0x13U+p*4U]=0x27U;
        red=mysmb_io_color_text16(0x16U);
        white=mysmb_io_color_text16(0x30U);
        skin=mysmb_io_color_text16(0x27U);
        mysmb_text_observer_enable(&game,1U);
        for(i=0U;i<6U;++i) {
            sprite((unsigned short)(8U+i),(unsigned char)(80U+(i%2U)*8U),
                (unsigned char)(95U+dy+(i/2U)*8U));
            game.ram[0x0202U+(8U+i)*4U]=(unsigned char)p;
        }
        mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_ENEMY,53U,0U,
            form==0U?0x9cU:0xa2U,1U,32U,6U,255U);
        mysmb_game_submit_oam(&game);
        /* Live producer changes must not change the committed retainer. */
        game.ram[0x0202U+32U]=(unsigned char)((p+1U)&3U);
        before=game;
        CHECK(mysmb_text_elements_build(0,0U,0U,&frame));
        CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
        CHECK(receipt.drawn==1U && receipt.unsupported==0U);
        CHECK(memcmp(&before,&game,sizeof(game))==0);
        colors=0U;
        for(c=0U;c<4000U;++c)if(frame.cells[c].character!=' ') {
            if(frame.cells[c].background==red)colors|=1U;
            if(frame.cells[c].background==white)colors|=2U;
            if(frame.cells[c].foreground==skin)colors|=4U;
        }
        if(colors!=7U)fprintf(stderr,"retainer form=%u palette=%u dy=%u roles=%u\n",
            (unsigned int)form,(unsigned int)p,(unsigned int)dy,(unsigned int)colors);
        CHECK(colors==7U);
        row=(unsigned short)(((96U+dy)*50U-120U+239U)/240U);
        if(form==0U) {
            CHECK(frame.cells[row*80U+27U].character=='P');
            CHECK(frame.cells[row*80U+27U].background==red);
            CHECK(frame.cells[(row+4U)*80U+27U].background==white);
        } else CHECK(frame.cells[row*80U+27U].character=='T');
    }
    return 0;
}

static int object_forms(void)
{
    /* Neutral selected-graphics metadata,not original tile/art bytes. */
    static const unsigned char forms[][3]={
        {0U,0x0cU,255U},{0U,0x12U,255U},{0U,0x5aU,255U},{0U,0x66U,255U},
        {2U,0U,255U},{2U,6U,255U},{2U,0x7eU,255U},{2U,0x84U,255U},
        {3U,0x0cU,255U},{3U,0x12U,255U},{3U,0x60U,255U},{3U,0x6cU,255U},
        {5U,0xa8U,255U},{5U,0xaeU,255U},{5U,0xb4U,255U},{5U,0xbaU,255U},
        {6U,0x54U,255U},{6U,0x8aU,255U},{7U,0x3cU,255U},{7U,0x42U,255U},
        {8U,0xeaU,255U},{51U,0xeaU,255U},
        {9U,0x18U,255U},{10U,0x48U,255U},{10U,0x4eU,255U},
        {11U,0x48U,255U},{11U,0x4eU,255U},{20U,0x48U,255U},{20U,0x4eU,255U},
        {12U,0xccU,255U},{13U,0xc0U,255U},{13U,0xc6U,255U},
        {14U,0x18U,255U},{14U,0x1eU,255U},{15U,0x18U,255U},{15U,0x1eU,255U},
        {16U,0x18U,255U},{16U,0x1eU,255U},{17U,0x90U,255U},{17U,0x96U,255U},
        {18U,0x24U,255U},{18U,0x2aU,255U},{18U,0x30U,255U},{18U,0x36U,255U},
        {53U,0x9cU,255U},{53U,0xa2U,255U},
        {1U,0xd2U,22U},{1U,0xdeU,22U},{1U,0xd8U,23U},{1U,0xe4U,23U},
        {1U,0xf0U,24U},{1U,0xf6U,25U},{1U,0xfcU,26U},
        {4U,0x0cU,255U}
    };
    struct mysmb_text_actor_receipt receipt;
    unsigned short n,p,flip,facing,i,c,visible;
    for(n=0U;n<sizeof(forms)/sizeof(forms[0]);++n)
    for(p=0U;p<4U;++p)for(flip=0U;flip<2U;++flip)for(facing=1U;facing<3U;++facing) {
        memset(&game,0,sizeof(game));
        for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
        game.visible_ppu_mask=0x1eU;
        game.palette[0x11U+p*4U]=0x16U;
        game.palette[0x12U+p*4U]=0x30U;
        game.palette[0x13U+p*4U]=0x27U;
        mysmb_text_observer_enable(&game,1U);
        for(i=0U;i<6U;++i) {
            sprite((unsigned short)(8U+i),(unsigned char)(80U+(i%2U)*8U),
                (unsigned char)(95U+(i/2U)*8U));
            game.ram[0x0202U+(8U+i)*4U]=(unsigned char)(p|(flip!=0U?0x80U:0U));
        }
        mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_ENEMY,forms[n][0],0U,
            forms[n][1],(unsigned char)facing,32U,6U,forms[n][2]);
        mysmb_game_submit_oam(&game);before=game;
        CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
        CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
        CHECK(receipt.unsupported==0U && receipt.drawn==1U);
        CHECK(memcmp(&before,&game,sizeof(game))==0);
        visible=0U;
        for(c=0U;c<4000U;++c)if(frame.cells[c].character!=' ')++visible;
        CHECK(visible!=0U);
        if(p==0U && flip==0U && facing==1U) {
            if(forms[n][0]>=14U && forms[n][0]<=16U) {
                if(forms[n][1]==0x18U)CHECK(frame.cells[20U*80U+25U].character=='\\');
                if(forms[n][1]==0x1eU)CHECK(frame.cells[20U*80U+26U].character=='/');
            }
            if(forms[n][2]>=24U && forms[n][2]<=26U)
                CHECK(visible==(forms[n][2]==24U?12U:forms[n][2]==25U?10U:5U));
            if(forms[n][0]==5U && forms[n][1]==0xb4U)
                CHECK(frame.cells[22U*80U+29U].character=='>');
            if(forms[n][0]==5U && forms[n][1]==0xbaU)
                CHECK(frame.cells[20U*80U+25U].character=='^');
            if(forms[n][0]==18U && forms[n][1]==0x36U)
                CHECK(frame.cells[21U*80U+26U].character=='O');
            if(forms[n][0]==53U)
                CHECK(frame.cells[20U*80U+27U].character==
                    (forms[n][1]==0x9cU?'P':'T'));
        }
        /* Canonical palette roles must actually occur in the visible art. */
        if(forms[n][0]==6U || forms[n][0]==13U || forms[n][0]==8U || forms[n][0]==2U) {
            unsigned char color;
            color=mysmb_io_color_text16(forms[n][0]==6U?0x27U:0x16U);
            visible=0U;
            for(c=0U;c<4000U;++c)if(frame.cells[c].background==color ||
                frame.cells[c].foreground==color)++visible;
            CHECK(visible!=0U);
        }
    }
    printf("object forms: %u selected enemy forms x4 palettes x2 vertical/facing states passed\n",
        (unsigned int)(sizeof(forms)/sizeof(forms[0])));
    return 0;
}

int main(void)
{
    struct mysmb_text_actor_receipt receipt;
    unsigned short i;
    CHECK(dynamic_words()==0);
    CHECK(mushroom_colors()==0);
    CHECK(retainer_details()==0);
    CHECK(object_forms()==0);
    memset(&game,0,sizeof(game));
    for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
    game.visible_ppu_mask=0x1eU;
    game.palette[0x11U]=0x16U;game.palette[0x12U]=0x30U;game.palette[0x13U]=0x27U;
    mysmb_text_observer_enable(&game,1U);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    sprite(8U,80U,95U);sprite(9U,88U,95U);
    sprite(10U,80U,103U);sprite(11U,88U,103U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_POWERUP,
        0U,5U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    before=game;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    CHECK(receipt.unowned_sprites==0U);
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    CHECK(frame.cells[20U*80U+26U].character==MYSMB_IO_GLYPH_LOWER);
    CHECK(frame.cells[20U*80U+26U].foreground==mysmb_io_color_text16(0x27U) &&
        frame.cells[20U*80U+26U].background==9U);
    CHECK(frame.cells[0U].background==9U);
    original=frame;
    game.ram[0x0201U+32U]=2U;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(memcmp(&frame,&original,sizeof(frame))==0);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+26U].character==' ');
    /* Losing a source column clips it rather than shifting the object. */
    game.visible_oam[32U+9U]=2U;
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+29U].character==MYSMB_IO_GLYPH_LOWER);
    CHECK(frame.cells[20U*80U+31U].character==' ');

    /* Unknown types remain explicit and do not paint a fabricated object. */
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_ENEMY,
        45U,0U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.unsupported==1U);
    /* Already-selected player graphics are interpreted via immutable table. */
    game.area_prg=prg;game.area_prg_size=sizeof(prg);
    prg[0x6e11U]=24U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        0U,0U,24U,1U,32U,4U,1U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    game.visible_ppu_mask=0U;original=frame;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.drawn==0U && memcmp(&frame,&original,sizeof(frame))==0);
    /* A shared selected offset cannot classify the original death branch. */
    game.visible_ppu_mask=0x1eU;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_DEATH_FLAG,0U,24U,1U,32U,4U,1U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[21U*80U+27U].character=='_');
    /* Independent chunks and interleaved original entry priority. */
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
    game.palette[0x17U]=0x1aU;
    sprite(8U,80U,95U);sprite(9U,120U,95U);sprite(10U,120U,95U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_CHUNKS,
        0U,0U,0U,1U,32U,3U,0U);
    game.ram[0x0202U+9U*4U]=1U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_CHUNKS,
        0U,1U,0U,1U,36U,1U,0U);
    sprite(11U,80U,95U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_CHUNKS,
        0U,2U,0U,1U,44U,1U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+25U].character=='#');
    CHECK(frame.cells[20U*80U+37U].character=='#');
    CHECK(frame.cells[20U*80U+37U].background==mysmb_io_color_text16(0x1aU));
    /* The winning behind-background entry also suppresses later sprites. */
    game.ram[0x0202U+8U*4U]=0x20U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_CHUNKS,
        0U,0U,0U,1U,32U,1U,0U);
    mysmb_game_submit_oam(&game);
    memset(opaque,0,sizeof(opaque));i=20U*80U+25U;
    CHECK(game.text_observer.visible.owners[10U]==0U);
    opaque[i/8U]=(unsigned char)(1U<<(i%8U));
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    frame.cells[i].character=' ';frame.cells[i].background=5U;
    before=game;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,opaque,&frame,&receipt));
    CHECK(frame.cells[i].character==' ' && frame.cells[i].background==5U);
    CHECK(memcmp(&before,&game,sizeof(game))==0);
    /* Two separated platform rows and every leaf of a vine remain visible. */
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
    for(i=0U;i<6U;++i)sprite((unsigned short)(8U+i),
        (unsigned char)(80U+(i%3U)*8U),(unsigned char)(79U+(i/3U)*128U));
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLATFORM,
        0U,0U,0U,1U,32U,6U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[17U*80U+25U].character=='[');
    CHECK(frame.cells[43U*80U+30U].character=='=');
    CHECK(frame.cells[43U*80U+31U].character==']');
    for(i=26U;i<31U;++i)CHECK(frame.cells[17U*80U+i].character=='=');
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<6U;++i) {
        sprite((unsigned short)(8U+i),80U,(unsigned char)(79U+i*8U));
        game.ram[0x0201U+(8U+i)*4U]=i==0U?0xe0U:0xe1U;
    }
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_VINE,
        0U,0U,0U,1U,32U,6U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[17U*80U+25U].character=='^');
    CHECK(frame.cells[25U*80U+25U].character=='|');
    /* Flag score is a separate subcomponent, not the flag's anchor. */
    sprite(8U,80U,95U);sprite(9U,88U,95U);sprite(10U,88U,103U);
    sprite(11U,100U,47U);sprite(12U,108U,47U);
    mysmb_text_observer_enable(&game,1U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_FLAG,
        0U,0U,0U,1U,32U,5U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[10U*80U+31U].character=='5');
    CHECK(frame.cells[20U*80U+25U].character=='|');
    /* Moving throw keeps base legs; a full throw replaces those legs. */
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<8U;++i)sprite((unsigned short)(8U+i),
        (unsigned char)(80U+(i%2U)*8U),(unsigned char)(79U+(i/2U)*8U));
    prg[0x6e0bU]=32U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_THROW_FLAG|MYSMB_TEXT_PLAYER_MIXED_FLAG,
        48U,56U,1U,32U,8U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[22U*80U+26U].character==' ');
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_THROW_FLAG,48U,56U,1U,32U,8U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[22U*80U+26U].character=='_');
    /* Only the source-replaced swim side gets the kick silhouette. */
    prg[0x6e08U]=8U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_KICK_FLAG,8U,8U,1U,32U,8U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[22U*80U+25U].character=='~');
    CHECK(frame.cells[22U*80U+29U].character==' ');
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_KICK_FLAG,8U,8U,2U,32U,8U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[22U*80U+25U].character==' ');
    CHECK(frame.cells[22U*80U+29U].character=='~');
    /* Source byte X wraps across the screen seam without moving the whole
     * mushroom to the smaller numeric column. Both fragments use one art. */
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
    sprite(8U,250U,95U);sprite(9U,2U,95U);
    sprite(10U,250U,103U);sprite(11U,2U,103U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_POWERUP,
        0U,5U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    before=game;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(memcmp(&before,&game,sizeof(game))==0);
    CHECK(frame.cells[21U*80U+1U].background!=9U);
    CHECK(frame.cells[21U*80U+79U].background!=9U);
    CHECK(frame.cells[21U*80U+4U].character==' ');
    original=frame;
    /* The first source entry can be the other column (horizontal ordering
     * is not part of the anchor contract). */
    sprite(8U,2U,95U);sprite(9U,250U,95U);
    sprite(10U,2U,103U);sprite(11U,250U,103U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_POWERUP,
        0U,5U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(memcmp(&frame,&original,sizeof(frame))==0);
    /* Hidden rows retain the original lower silhouette, not a relocated cap. */
    sprite(8U,80U,95U);sprite(9U,88U,95U);
    sprite(10U,80U,103U);sprite(11U,88U,103U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_POWERUP,
        0U,5U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    original=frame;
    game.ram[0x0200U+32U]=0xf8U;game.ram[0x0204U+32U]=0xf8U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_POWERUP,
        0U,5U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(memcmp(&frame.cells[22U*80U+25U],
        &original.cells[22U*80U+25U],5U*sizeof(frame.cells[0]))==0);
    CHECK(frame.cells[20U*80U+26U].character==' ');
    /* An object above the screen has negative authored Y, with only its
     * surviving lower source row at Y=1. No cap is invented at the top. */
    game.ram[0x0208U+32U]=0U;game.ram[0x020cU+32U]=0U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_POWERUP,
        0U,5U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[25U].character==' ');
    CHECK(frame.cells[27U].character=='|' && frame.cells[27U].background!=9U);
    /* Blank top rows are deliberately absent in small-player source layouts;
     * they must not add sixteen pixels above the authored small silhouette. */
    game.ram[0x0201U+32U]=0xfcU;game.ram[0x0205U+32U]=0xfcU;
    game.ram[0x0208U+32U]=101U;game.ram[0x020cU+32U]=101U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        0U,24U,24U,1U,32U,4U,1U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[21U*80U+27U].character=='M');
    /* Luigi comes from the source-selected identity,not live player RAM. */
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        1U,24U,24U,1U,32U,4U,1U);
    mysmb_game_submit_oam(&game);game.ram[0x0753U]=0U;
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[21U*80U+27U].character=='L');
    /* Scores keep their selected value after live control changes. A later
     * partial writer removes only its entry,not the whole number or anchor. */
    mysmb_text_observer_invalidate(&game);
    for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
    sprite(8U,80U,95U);sprite(9U,88U,95U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_SCORE,
        6U,0U,6U,0U,32U,2U,0U);
    mysmb_game_submit_oam(&game);game.ram[0x0110U]=11U;
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+25U].character=='1');
    CHECK(frame.cells[20U*80U+28U].character=='0');
    game.ram[0x0205U+32U]=2U;mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+25U].character=='1');
    CHECK(frame.cells[20U*80U+27U].character==' ');
    /* Byte-wrapped second halves retain the original number's right digit. */
    sprite(8U,250U,95U);sprite(9U,2U,95U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_SCORE,
        6U,0U,6U,0U,32U,2U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+78U].character=='1');
    CHECK(frame.cells[20U*80U+1U].character=='0');
    game.ram[0x0200U+32U]=game.ram[0x0204U+32U]=0xf8U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_SCORE,
        6U,0U,6U,0U,32U,2U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.drawn==0U);
    puts("observed actor scene: whole templates/fill/latch/clipping/seam/hidden/read-only passed");
    return 0;
}
