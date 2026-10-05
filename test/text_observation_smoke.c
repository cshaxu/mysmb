#include "core/game.h"
#include "core/frame_root.h"
#include "ppu/frame.h"
#include "core/oam/oam.h"
#include "core/objects.h"
#include "core/enemy/actor_slots.h"
#include "game/presentation/text/actor_scene.h"
#include "game/presentation/text/background_scene.h"
#include "game/presentation/text/observer_snapshot.h"
#include "app/game_snapshot.h"
#include "io/color.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#ifdef MYSMB_LOCAL_TITLE
#include "core/area.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

static struct mysmb_text_actor_workspace actor_workspace;
static struct mysmb_game observed,plain,before,restored;
static struct mysmb_io_snapshot first,second;
static struct mysmb_ppu_frame pixels1,pixels2;
static struct mysmb_io_text_frame text,loaded_text;
static unsigned char snapshot_wire[MYSMB_SNAPSHOT_FILE_BYTES];
static struct mysmb_text_background_workspace background;
static struct mysmb_text_background_receipt caption_receipt;
static unsigned long checked_caption_glyphs;
static unsigned char checking_title;
#define CHECK(c) do { if (!(c)) { \
    fprintf(stderr,"observation check line %d\n",__LINE__); return 1; \
} } while (0)

static void bind(struct mysmb_game *game)
{
    mysmb_game_power_on(game);
#ifdef MYSMB_LOCAL_TITLE
    mysmb_game_bind_area_source(game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(game,mysmb_local_title_data,
        MYSMB_LOCAL_TITLE_DATA_SIZE,mysmb_local_title_icon_data,
        MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
#endif
}

#ifdef MYSMB_LOCAL_TITLE
static void caption_setup(void)
{
    bind(&observed);observed.startup_phase=4U;
    mysmb_text_observer_enable(&observed,1U);
    memset(observed.ppu.name_table,0x24,sizeof(observed.ppu.name_table));
    memset(observed.ppu.name_table[0]+0x3c0U,0,64U);
    memset(observed.ppu.name_table[1]+0x3c0U,0,64U);
    observed.ppu.visible_ppu_mask=0x1eU;observed.ram[0x0779U]=0x1eU;
    observed.ram[0x0773U]=0U;observed.ppu.visible_sprite0_split=1U;
}

static int caption_word(unsigned short row,unsigned short col,const char *word)
{
    unsigned short i,x,y;
    for(i=0U;word[i]!='\0';++i) {
        if(word[i]==' ')continue;
        if(row<4U && observed.ppu.visible_sprite0_split) {
            x=(unsigned short)((col+i)*8UL*80UL/256UL);
            y=(unsigned short)(row*8UL*50UL/240UL);
        } else {
            x=(unsigned short)(((col+i)*8UL*80UL-128UL+255UL)/256UL);
            y=(unsigned short)((row*8UL*50UL-120UL+239UL)/240UL);
        }
        if(x>=80U || y>=50U || text.cells[y*80U+x].character!=(unsigned char)word[i])
            return 0;
    }
    return 1;
}

static int caption_render_restore(void)
{
    unsigned char fingerprint[16];
    unsigned short row,col,table,tile,x,y;
    unsigned char expected;
    before=observed;
    CHECK(mysmb_text_background_scene_build(&observed,&background,&text,&caption_receipt));
    {
        struct mysmb_text_actor_receipt actors;
        CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,background.opaque,&text,&actors));
    }
    /* These fixtures start with cleared tables and invoke original text
     * producers. Check every committed font token,not selected words. */
    for(row=0U;row<30U;++row)for(col=0U;col<32U;++col) {
        table=row<4U && observed.ppu.visible_sprite0_split?0U:observed.ppu.visible_ppu_name_table&1U;
        tile=observed.ppu.name_table[table][row*32U+col];expected=0U;
        if(tile<36U)expected=(unsigned char)"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[tile];
        else if(tile==0x28U)expected='-';
        else if(tile==0x29U)expected='x';
        else if(tile==0x2bU)expected='!';
        else if(tile==0x2eU)expected='$';
        else if(tile==0xafU)expected='.';
        else if(tile==0xcfU)expected='@';
        else if(tile==0x9fU)expected='^';
        if(tile==0x24U)continue;
        /* The title sign is authored artwork,not a stream of font tokens.
         * Outside that declared rectangle,no unrecognized token is ignored. */
        if(checking_title && row>=4U && row<=14U && col>=5U && col<=26U)continue;
        if(expected==0U)fprintf(stderr,"unclassified text token row=%u col=%u tile=%u\n",row,col,tile);
        CHECK(expected!=0U);
        if(row<4U && observed.ppu.visible_sprite0_split) {
            x=(unsigned short)(col*8UL*80UL/256UL);
            y=(unsigned short)(row*8UL*50UL/240UL);
        } else {
            x=(unsigned short)((col*8UL*80UL+127UL)/256UL);
            y=(unsigned short)((row*8UL*50UL+119UL)/240UL);
        }
        if(text.cells[y*80U+x].character!=expected)
            fprintf(stderr,"missing caption row=%u col=%u expected=%c actual=%c\n",
                row,col,expected,text.cells[y*80U+x].character);
        CHECK(text.cells[y*80U+x].character==expected);
        CHECK(text.cells[y*80U+x].foreground!=text.cells[y*80U+x].background);
        ++checked_caption_glyphs;
    }
    CHECK(memcmp(&observed,&before,sizeof(observed))==0);
    mysmb_game_snapshot_fingerprint(&observed,fingerprint);
    CHECK(mysmb_game_snapshot_capture(&observed,&first,fingerprint));
    bind(&restored);mysmb_text_observer_enable(&restored,1U);
    CHECK(mysmb_game_snapshot_restore(&restored,&first));
    CHECK(mysmb_text_background_scene_build(&restored,&background,&loaded_text,&caption_receipt));
    {
        struct mysmb_text_actor_receipt actors;
        CHECK(mysmb_text_actor_scene_draw(&restored,&actor_workspace,background.opaque,&loaded_text,&actors));
    }
    CHECK(memcmp(&text,&loaded_text,sizeof(text))==0);
    return 0;
}

static int caption_routes(void)
{
    static const unsigned short rows[7]={10U,10U,14U,13U,15U,18U,20U};
    static const unsigned short cols[7]={8U,8U,5U,7U,3U,10U,8U};
    static const char *words[7]={"THANK YOU MARIO!","THANK YOU LUIGI!",
        "BUT OUR PRINCESS IS IN","YOUR QUEST IS OVER.",
        "WE PRESENT YOU A NEW QUEST.","PUSH BUTTON B","TO SELECT A WORLD"};
    unsigned short i;
    struct mysmb_input input;
    struct mysmb_frame output;
    /* Original title declaration includes both menu lines,copyright and TOP;
     * combine it with status producers before checking every font token. */
    caption_setup();observed.ppu.visible_sprite0_split=0U;
    observed.ram[0x0770U]=0U;observed.ram[0x073cU]=12U;
    mysmb_game_step_screen_routine(&observed);
    mysmb_game_commit_vram_buffer(&observed);
    checking_title=1U;CHECK(caption_render_restore()==0);checking_title=0U;
    CHECK(caption_word(18U,11U,"1 PLAYER GAME"));
    CHECK(caption_word(20U,11U,"2 PLAYER GAME"));
    for(i=0U;i<10U;++i) {
        unsigned short digit;
        caption_setup();observed.ram[0x0753U]=(unsigned char)(i&1U);
        observed.ram[0x077aU]=1U;
        for(digit=0U;digit<36U;++digit)observed.ram[0x07d7U+digit]=(unsigned char)i;
        CHECK(mysmb_area_queue_top_status_line(&observed));
        mysmb_game_commit_vram_buffer(&observed);
        CHECK(mysmb_area_queue_bottom_status_line(&observed));
        mysmb_game_commit_vram_buffer(&observed);
        CHECK(mysmb_area_queue_title_score(&observed));
        mysmb_game_commit_vram_buffer(&observed);
        CHECK(caption_render_restore()==0);
    }
    for(i=0U;i<32U;++i) {
        caption_setup();
        observed.ram[0x0753U]=(unsigned char)(i&1U);
        observed.ram[0x077aU]=(unsigned char)((i>>1U)&1U);
        observed.ram[0x0770U]=(unsigned char)((i&4U)!=0U?3U:1U);
        CHECK(mysmb_area_queue_game_text(&observed,(unsigned char)(i/8U)));
        mysmb_game_commit_vram_buffer(&observed);
        CHECK(caption_render_restore()==0);
    }
    for(i=0U;i<7U;++i) {
        caption_setup();observed.ram[0x0773U]=(unsigned char)(12U+i);
        CHECK(mysmb_text_background_scene_build(&observed,&background,&text,&caption_receipt));
        CHECK(!caption_word(rows[i],cols[i],words[i]));
        mysmb_game_commit_vram_buffer(&observed);
        observed.ppu.visible_ppu_name_table=1U;
        CHECK(caption_render_restore()==0);
        CHECK(caption_word(rows[i],cols[i],words[i]));
        if(i==2U)CHECK(caption_word(16U,5U,"ANOTHER CASTLE!"));
        memset(observed.ppu.name_table[1],0x24,960U);
        CHECK(mysmb_text_background_scene_build(&observed,&background,&text,&caption_receipt));
        CHECK(!caption_word(rows[i],cols[i],words[i]));
    }
    for(i=0U;i<7U;++i) {
        caption_setup();observed.ram[0x077aU]=1U;
        observed.ram[0x0753U]=1U;observed.ram[0x0770U]=3U;
        observed.ram[0x075aU]=10U;observed.ram[0x075fU]=3U;
        observed.ram[0x075cU]=1U;
        CHECK(mysmb_area_queue_game_text(&observed,(unsigned char)i));
        mysmb_game_commit_vram_buffer(&observed);
        if(i>=4U)observed.ppu.visible_ppu_name_table=1U;
        CHECK(caption_render_restore()==0);
        if(i==0U) {
            CHECK(caption_word(2U,3U,"LUIGI"));
            CHECK(caption_word(3U,11U,"$x"));
        }
        if(i==1U) {
            CHECK(caption_word(10U,11U,"WORLD 4-2"));
            CHECK(caption_word(14U,17U,"^1"));
        }
        if(i==2U)CHECK(caption_word(16U,12U,"TIME UP"));
        if(i==3U)CHECK(caption_word(16U,11U,"GAME OVER"));
        if(i>=4U)CHECK(caption_word(12U,4U,"WELCOME TO WARP ZONE!"));
    }
    /* Original pause freezes the committed scene;no invented pause label. */
    observed.ram[0x0770U]=1U;observed.ram[0x0772U]=3U;
    observed.ram[0x0776U]=1U;observed.ram[0x0774U]=0U;
    observed.ram[0x0722U]=0U;observed.ram[0x0778U]=1U;
    observed.ppu.ppu_control_0=1U;observed.ppu.visible_sprite0_split=0U;
    input.buttons=0U;input.buttons2=0U;
    CHECK(mysmb_text_background_scene_build(&observed,&background,&loaded_text,&caption_receipt));
    mysmb_game_tick(&observed,&input,&output);
    CHECK(mysmb_text_background_scene_build(&observed,&background,&text,&caption_receipt));
    CHECK(memcmp(&text,&loaded_text,sizeof(text))==0);
    /* Exercise the final background/actor join at every world/level and
     * ordinary life digit,not just an isolated crown fixture. */
    for(i=0U;i<32U;++i) {
        unsigned short lives;
        char world[10],count[5];
        for(lives=1U;lives<=11U;++lives) {
            caption_setup();observed.ppu.visible_sprite0_split=0U;
            observed.ram[0x075aU]=(unsigned char)(lives-1U);
            observed.ram[0x075fU]=(unsigned char)(i/4U);
            observed.ram[0x075cU]=(unsigned char)(i%4U);
            mysmb_oam_draw_intermediate_player(&observed);
            CHECK(mysmb_area_queue_game_text(&observed,1U));
            mysmb_game_commit_vram_buffer(&observed);
            mysmb_game_submit_oam(&observed);
            CHECK(caption_render_restore()==0);
            sprintf(world,"WORLD %u-%u",i/4U+1U,i%4U+1U);
            CHECK(caption_word(10U,11U,world));
            CHECK(caption_word(14U,15U,"x"));
            if(lives<10U) {
                sprintf(count,"%u",lives);CHECK(caption_word(14U,18U,count));
            } else {
                sprintf(count,"^%u",lives-10U);CHECK(caption_word(14U,17U,count));
            }
        }
    }
    printf("409 title/HUD/name/terminal/world-lives final-composed restores; %lu committed glyphs checked; pause passed\n",checked_caption_glyphs);
    return 0;
}

static int player_phase_routes(void)
{
    unsigned short i;
    struct mysmb_text_actor_receipt receipt;
    for(i=0U;i<6U;++i) {
        caption_setup();observed.ram[0x0753U]=(unsigned char)(i%2U);
        observed.ram[0x0754U]=(unsigned char)(i/2U==0U?0U:1U);
        observed.ram[0x000eU]=0x0bU;observed.ram[0x06e4U]=32U;
        observed.ram[0x03adU]=80U;observed.ram[0x03b8U]=64U;
        observed.ram[0x0033U]=1U;plain=observed;
        mysmb_text_observer_enable(&plain,0U);
        if(i<4U) {
            mysmb_oam_render_player(&observed);mysmb_oam_render_player(&plain);
            CHECK((observed.text_observer.producer.items[0].identity&
                MYSMB_TEXT_PLAYER_DEATH_FLAG)!=0U);
        } else {
            mysmb_oam_draw_intermediate_player(&observed);
            mysmb_oam_draw_intermediate_player(&plain);
        }
        CHECK(memcmp(&plain,&observed,offsetof(struct mysmb_game,text_observer))==0);
        mysmb_game_submit_oam(&observed);
        CHECK(caption_render_restore()==0);
        CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,
            background.opaque,&text,&receipt));
        CHECK(receipt.drawn==1U && receipt.unsupported==0U);
        CHECK(mysmb_text_actor_scene_draw(&restored,&actor_workspace,
            background.opaque,&loaded_text,&receipt));
        CHECK(memcmp(&text,&loaded_text,sizeof(text))==0);
        observed.ram[0x0753U]^=1U;observed.ram[0x000eU]=8U;
        CHECK(mysmb_text_background_scene_build(&observed,&background,&loaded_text,&caption_receipt));
        CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,
            background.opaque,&loaded_text,&receipt));
        CHECK(memcmp(&text,&loaded_text,sizeof(text))==0);
    }
    puts("six actual Mario/Luigi death/intermission owners preserve outputs and restored scene");
    return 0;
}
#endif

static int snapshot_case(void)
{
    unsigned char fingerprint[16],saved;
    unsigned short i;
    static const unsigned short bad_offsets[]={0U,1U,2U,3U,67U,72U,73U};
    mysmb_game_initialize(&observed);observed.startup_phase=4U;
    mysmb_text_observer_enable(&observed,1U);
    observed.ram[0x0200U]=80U;observed.ram[0x0201U]=1U;
    observed.ram[0x0203U]=40U;observed.ram[0x0204U]=80U;
    observed.ram[0x0205U]=1U;observed.ram[0x0207U]=48U;
    mysmb_text_observer_record(&observed,3U,0U,0U,0U,1U,0U,2U,0U);
    /* An unobserved later write must stay unowned after loading. Its old
     * entry still anchors the original whole-object template. */
    observed.ram[0x0203U]=100U;
    mysmb_game_submit_oam(&observed);
    CHECK(mysmb_text_observer_visible_mask(&observed,0U)==2U);
    mysmb_text_observer_clear_producer(&observed);
    mysmb_text_observer_record(&observed,4U,0U,0U,0U,1U,4U,1U,0U);
    mysmb_game_snapshot_fingerprint(&observed,fingerprint);
    CHECK(mysmb_game_snapshot_capture(&observed,&first,fingerprint));
    CHECK(mysmb_snapshot_encode(&first,snapshot_wire,sizeof(snapshot_wire))==0);
    CHECK(mysmb_snapshot_decode(snapshot_wire,sizeof(snapshot_wire),fingerprint,&second)==0);
    mysmb_game_initialize(&restored);
    CHECK(mysmb_game_snapshot_restore(&restored,&second));
    CHECK(memcmp(&observed.text_observer,&restored.text_observer,
        sizeof(observed.text_observer))==0);
    CHECK(mysmb_text_observer_visible_mask(&restored,0U)==2U);
    before=restored;
    for(i=0U;i<sizeof(bad_offsets)/sizeof(bad_offsets[0]);++i) {
        saved=second.payload[MYSMB_SNAPSHOT_PRESENTATION_OFFSET+bad_offsets[i]];
        second.payload[MYSMB_SNAPSHOT_PRESENTATION_OFFSET+bad_offsets[i]]=255U;
        CHECK(!mysmb_game_snapshot_restore(&restored,&second));
        CHECK(memcmp(&before,&restored,sizeof(restored))==0);
        second.payload[MYSMB_SNAPSHOT_PRESENTATION_OFFSET+bad_offsets[i]]=saved;
    }
    return 0;
}

static int star_flag_case(void)
{
    struct mysmb_text_actor_receipt receipt;
    mysmb_game_initialize(&observed);
    observed.ppu.visible_ppu_mask=0x1eU;observed.ppu.palette[0x1aU]=0x27U;
    observed.ram[0x0746U]=3U;observed.ram[0x00cfU]=0x72U;
    observed.ram[0x0087U]=80U;observed.ram[0x06e5U]=32U;
    plain=observed;mysmb_text_observer_enable(&observed,1U);
    mysmb_objects_step_star_flags_slot(&observed,0U);
    mysmb_objects_step_star_flags_slot(&plain,0U);
    CHECK(memcmp(&observed,&plain,offsetof(struct mysmb_game,text_observer))==0);
    CHECK(observed.text_observer.producer.count==1U);
    CHECK(observed.text_observer.producer.items[0].family==MYSMB_TEXT_OBSERVE_STAR_FLAG);
    CHECK(observed.text_observer.producer.items[0].oam==32U);
    mysmb_game_submit_oam(&observed);
    CHECK(mysmb_text_observer_visible_mask(&observed,0U)==15U);
    CHECK(mysmb_text_elements_build(0,0U,9U,&text));before=observed;
    CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,0,&text,&receipt));
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    CHECK(text.cells[24U*80U+27U].character=='*');
    CHECK(memcmp(&before,&observed,sizeof(observed))==0);
    CHECK(mysmb_text_observer_snapshot_capture(&observed,snapshot_wire));
    restored=observed;mysmb_text_observer_invalidate(&restored);
    mysmb_text_observer_snapshot_restore(&restored,snapshot_wire);
    CHECK(memcmp(&observed.text_observer,&restored.text_observer,
        sizeof(observed.text_observer))==0);
    return 0;
}

#ifdef MYSMB_LOCAL_TITLE
/* Read the admitted local original resource declarations;do not reproduce
 * palette tables or synthesize a second animation clock in presentation. */
static int palette_animation_case(void)
{
    unsigned short i,j,col,row,base,a,found_question,found_coin,colors;
    unsigned char previous,expected;
    bind(&observed);observed.ppu.visible_ppu_mask=0x1eU;
    observed.ram[0x0779U]=0x1eU;observed.ram[0x0773U]=0U;
    observed.ppu.palette[0U]=0x22U;observed.ppu.palette[13U]=0x0fU;
    memset(observed.ppu.name_table,0x24,sizeof(observed.ppu.name_table));
    memset(observed.ppu.name_table[0]+0x3c0U,0,64U);
    memset(observed.ppu.name_table[1]+0x3c0U,0,64U);
    base=(unsigned short)((observed.area_prg[0x0b0bU]|
        ((unsigned short)observed.area_prg[0x0b0fU]<<8U))-0x8000U);
    for(j=0U;j<2U;++j) {
        col=(unsigned short)(j==0U?10U:16U);row=12U;a=(unsigned short)(row*32U+col);
        observed.ppu.name_table[0][a]=observed.area_prg[base+j*8U];
        observed.ppu.name_table[0][a+32U]=observed.area_prg[base+j*8U+1U];
        observed.ppu.name_table[0][a+1U]=observed.area_prg[base+j*8U+2U];
        observed.ppu.name_table[0][a+33U]=observed.area_prg[base+j*8U+3U];
        observed.ppu.name_table[0][0x3c0U+(row/4U)*8U+col/4U]|=
            (unsigned char)(3U<<(((row&2U)<<1U)+(col&2U)));
    }
    observed.ram[0x074eU]=1U;plain=observed;colors=0U;
    mysmb_text_observer_enable(&observed,1U);
    for(i=0U;i<12U;++i) {
        observed.ram[0x0009U]=plain.ram[0x0009U]=(unsigned char)(i*8U);
        previous=observed.ppu.palette[13U];
        mysmb_area_step_palette_rotation(&observed);
        mysmb_area_step_palette_rotation(&plain);
        CHECK(observed.ppu.palette[13U]==previous);
        mysmb_game_commit_vram_buffer(&observed);mysmb_game_commit_vram_buffer(&plain);
        CHECK(memcmp(&observed,&plain,offsetof(struct mysmb_game,text_observer))==0);
        CHECK(observed.ppu.palette[13U]==observed.area_prg[0x09c3U+i%6U]);
        before=observed;
        CHECK(mysmb_text_background_scene_build(&observed,&background,&text,&caption_receipt));
        expected=mysmb_io_color_text16(observed.ppu.palette[13U]);
        colors|=(unsigned short)(1U<<expected);found_question=found_coin=0U;
        for(j=0U;j<4000U;++j)if(text.cells[j].character=='?' || text.cells[j].character=='$') {
            CHECK(text.cells[j].background==expected);
            CHECK(text.cells[j].foreground!=expected);
            if(text.cells[j].character=='?')++found_question;else ++found_coin;
        }
        if(found_question==0U || found_coin==0U)
            fprintf(stderr,"palette fixture phase=%u question=%u coin=%u unsupported=%u ambiguous=%u objects=%u\n",
                i,found_question,found_coin,caption_receipt.unsupported,
                caption_receipt.ambiguous,caption_receipt.objects);
        CHECK(found_question!=0U && found_coin!=0U);
        CHECK(memcmp(&before,&observed,sizeof(observed))==0);
    }
    CHECK((colors&(colors-1U))!=0U);
    printf("question/coin palette:12original queue/commit phases,shared animated colors passed\n");
    return 0;
}
#endif

/* Complete actual flag writer,not just a fabricated score observation. */
static int flag_words_case(void)
{
    static const char *labels[5]={"5000","2000","800","400","100"};
    struct mysmb_text_actor_receipt receipt;
    unsigned short score,dx,dy,bg,j,x,y,first,row,index,cases;
    cases=0U;
    for(score=0U;score<5U;++score)for(dx=0U;dx<8U;++dx)
        for(dy=0U;dy<8U;++dy)for(bg=0U;bg<16U;++bg) {
            mysmb_game_initialize(&observed);observed.ppu.visible_ppu_mask=0x1eU;
            for(j=0U;j<64U;++j)observed.ram[0x0200U+j*4U]=0xf8U;
            observed.ppu.palette[0x16U]=0x30U;
            observed.ram[0x06e5U]=32U;observed.ram[0x00cfU]=159U;
            observed.ram[0x03aeU]=(unsigned char)(80U+dx);
            observed.ram[0x010dU]=(unsigned char)(95U+dy);
            observed.ram[0x010fU]=(unsigned char)score;observed.ram[0x070fU]=1U;
            plain=observed;mysmb_text_observer_enable(&observed,1U);
            mysmb_objects_draw_flagpole_graphics(&observed);
            mysmb_objects_draw_flagpole_graphics(&plain);
            CHECK(memcmp(&observed,&plain,offsetof(struct mysmb_game,text_observer))==0);
            mysmb_game_submit_oam(&observed);before=observed;
            x=observed.ppu.visible_oam[47U];y=(unsigned short)(observed.ppu.visible_oam[44U]+1U);
            first=(unsigned short)(((unsigned long)x*80UL+127UL)/256UL);
            row=(unsigned short)(((unsigned long)y*50UL+119UL)/240UL);
            CHECK(mysmb_text_elements_build(0,0U,(mysmb_io_u8)bg,&text));
            CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,0,&text,&receipt));
            CHECK(receipt.drawn==1U && receipt.unsupported==0U);
            for(j=0U;labels[score][j]!='\0';++j) {
                index=(unsigned short)(row*80U+first+j);
                CHECK(text.cells[index].character==(unsigned char)labels[score][j]);
                CHECK(text.cells[index].background==bg && text.cells[index].foreground!=bg);
            }
            CHECK(memcmp(&before,&observed,sizeof(observed))==0);
            CHECK(mysmb_text_observer_snapshot_capture(&observed,snapshot_wire));
            restored=observed;mysmb_text_observer_invalidate(&restored);
            mysmb_text_observer_snapshot_restore(&restored,snapshot_wire);
            CHECK(mysmb_text_elements_build(0,0U,(mysmb_io_u8)bg,&loaded_text));
            CHECK(mysmb_text_actor_scene_draw(&restored,&actor_workspace,0,&loaded_text,&receipt));
            CHECK(memcmp(&text,&loaded_text,sizeof(text))==0);++cases;
        }
    printf("original flag score writer: %u whole-word/color/position/restored cases passed\n",cases);
    return 0;
}

static int misc_case(unsigned char score,unsigned char phase)
{
    static const char *labels[11]={"100","200","400","500","800",
        "1000","2000","4000","5000","8000","1UP"};
    struct mysmb_text_actor_receipt receipt;
    unsigned short i;
    unsigned char family,control;
    mysmb_game_initialize(&observed);
    observed.ppu.visible_ppu_mask=0x1eU;observed.ppu.palette[0x1aU]=0x27U;
    observed.ram[0x06f3U]=32U;observed.ram[0x06e5U]=32U;
    observed.ram[0x002aU]=phase;observed.ram[0x0009U]=(unsigned char)(phase*2U);
    observed.ram[0x03b3U]=80U;observed.ram[0x00dbU]=95U;
    observed.ram[0x0110U]=score;observed.ram[0x012cU]=0x20U;
    observed.ram[0x0117U]=80U;observed.ram[0x011eU]=104U;
    observed.ram[0x0016U]=18U;
    plain=observed;mysmb_text_observer_enable(&observed,1U);
    if(score!=0U) {
        mysmb_objects_step_floatey_number(&observed,0U);
        mysmb_objects_step_floatey_number(&plain,0U);
    } else {
        /* Keep all four coin phases in state one;state>=2 owns the200 stage. */
        if(phase<4U)observed.ram[0x002aU]=plain.ram[0x002aU]=1U;
        mysmb_objects_draw_jump_coin(&observed,0U);
        mysmb_objects_draw_jump_coin(&plain,0U);
    }
    CHECK(memcmp(&observed,&plain,offsetof(struct mysmb_game,text_observer))==0);
    CHECK(observed.text_observer.producer.count==1U);
    family=score!=0U || phase>=4U?MYSMB_TEXT_OBSERVE_SCORE:MYSMB_TEXT_OBSERVE_COIN;
    control=score!=0U?score:2U;
    CHECK(observed.text_observer.producer.items[0].family==family);
    CHECK(observed.text_observer.producer.items[0].graphics==
        (family==MYSMB_TEXT_OBSERVE_SCORE?control:0x60U+phase));
    mysmb_game_submit_oam(&observed);
    CHECK(mysmb_text_elements_build(0,0U,9U,&text));before=observed;
    CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,0,&text,&receipt));
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    CHECK(memcmp(&before,&observed,sizeof(observed))==0);
    if(family==MYSMB_TEXT_OBSERVE_SCORE)
        for(i=0U;labels[control-1U][i]!='\0';++i)
            CHECK(text.cells[20U*80U+25U+i].character==labels[control-1U][i]);
    else CHECK(text.cells[21U*80U+25U+(phase==1U?1U:0U)].character==
        (phase==0U?'$':'|'));
    if(family==MYSMB_TEXT_OBSERVE_SCORE) {
        observed.ppu.palette[0x1aU]=0x30U;before=observed;
        for(phase=0U;phase<16U;++phase) {
            CHECK(mysmb_text_elements_build(0,0U,phase,&text));
            CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,0,&text,&receipt));
            for(i=0U;labels[control-1U][i]!='\0';++i) {
                CHECK(text.cells[20U*80U+25U+i].character==labels[control-1U][i]);
                CHECK(text.cells[20U*80U+25U+i].foreground!=phase);
                CHECK(text.cells[20U*80U+25U+i].background==phase);
            }
            CHECK(memcmp(&before,&observed,sizeof(observed))==0);
        }
    }
    CHECK(mysmb_text_observer_snapshot_capture(&observed,snapshot_wire));
    CHECK(mysmb_text_observer_snapshot_valid(snapshot_wire));
    restored=observed;mysmb_text_observer_invalidate(&restored);
    mysmb_text_observer_snapshot_restore(&restored,snapshot_wire);
    CHECK(memcmp(&restored.text_observer,&observed.text_observer,
        sizeof(observed.text_observer))==0);
    if(family==MYSMB_TEXT_OBSERVE_SCORE) {
        CHECK(mysmb_text_elements_build(0,0U,15U,&loaded_text));
        CHECK(mysmb_text_actor_scene_draw(&restored,&actor_workspace,0,&loaded_text,&receipt));
        CHECK(memcmp(&text,&loaded_text,sizeof(text))==0);
    }
    return 0;
}

static int mixed_player_case(unsigned char moving,unsigned char swimming,
    unsigned char frame_counter)
{
    bind(&plain);
    if(plain.area_prg==0)return 0;
    plain.ram[0x000eU]=8U;plain.ram[0x06e4U]=32U;
    plain.ram[0x03adU]=80U;plain.ram[0x03b8U]=64U;plain.ram[0x0033U]=1U;
    plain.ram[0x0057U]=moving;plain.ram[0x000cU]=moving;
    plain.ram[0x001dU]=swimming;plain.ram[0x0704U]=swimming;
    plain.ram[0x0711U]=swimming==0U?10U:0U;plain.ram[0x0781U]=1U;
    plain.ram[0x0754U]=0U;plain.ram[0x0009U]=frame_counter;
    observed=plain;mysmb_text_observer_enable(&observed,1U);
    mysmb_oam_render_player(&plain);mysmb_oam_render_player(&observed);
    CHECK(memcmp(&plain,&observed,offsetof(struct mysmb_game,text_observer))==0);
    CHECK(observed.text_observer.producer.count==1U);
    if(swimming!=0U)CHECK(((observed.text_observer.producer.items[0].identity&
        MYSMB_TEXT_PLAYER_KICK_FLAG)!=0U)==((frame_counter&4U)==0U));
    else {
        CHECK((observed.text_observer.producer.items[0].identity&
            MYSMB_TEXT_PLAYER_THROW_FLAG)!=0U);
        CHECK(((observed.text_observer.producer.items[0].identity&
            MYSMB_TEXT_PLAYER_MIXED_FLAG)!=0U)==(moving!=0U));
    }
    return 0;
}

static int compare_draw(void (*draw)(struct mysmb_game *,mysmb_u8),
    unsigned char family)
{
    unsigned int i;
    mysmb_game_initialize(&observed);
    observed.ram[8U]=0U; observed.ram[0x06f1U]=64U;
    observed.ram[0x06f3U]=64U; observed.ram[0x06ecU]=64U;
    observed.ram[0x03baU]=80U; observed.ram[0x03afU]=80U;
    observed.ram[0x03bcU]=80U; observed.ram[0x03b1U]=80U;
    observed.ram[0x03beU]=80U; observed.ram[0x03b3U]=80U;
    observed.ram[0x03f1U]=80U; observed.ram[0x002aU]=1U;
    observed.ram[0x074eU]=1U;
    plain=observed;
    mysmb_text_observer_enable(&observed,1U);
    draw(&observed,0U);draw(&plain,0U);
    CHECK(memcmp(observed.ram,plain.ram,sizeof(plain.ram))==0);
    CHECK(observed.text_observer.producer.overflow==0U);
    mysmb_game_submit_oam(&observed);
    for(i=0U;i<observed.text_observer.visible.count;++i)
        if(observed.text_observer.visible.items[i].family==family &&
            mysmb_text_observer_visible_mask(&observed,(unsigned char)i)!=0U)
            return 0;
    return 1;
}

static void enemy_draw(struct mysmb_game *g,unsigned char id)
{
    switch(id) {
    case 0U:case 2U:case 3U:(void)mysmb_objects_draw_koopa_buzzy(g,0U);break;
    case 5U:(void)mysmb_objects_draw_hammer_bro(g,0U);break;
    case 6U:mysmb_objects_draw_goomba(g,0U);break;
    case 7U:(void)mysmb_objects_draw_bloober(g,0U);break;
    case 8U:mysmb_objects_draw_bullet_bill(g,0U);break;
    case 10U:case 11U:(void)mysmb_objects_draw_cheep_cheep(g,0U);break;
    case 12U:(void)mysmb_objects_draw_podoboo(g,0U);break;
    case 13U:mysmb_objects_draw_piranha(g,0U);break;
    case 18U:(void)mysmb_objects_draw_spiny(g,0U);break;
    default:(void)mysmb_objects_draw_normal_enemy_graphics(g,0U);break;
    }
}

static int enemy_case(unsigned char id,unsigned char state,unsigned char phase)
{
    struct mysmb_text_actor_receipt receipt;
    unsigned short i;
    mysmb_game_initialize(&plain);
    for(i=0U;i<64U;++i)plain.ram[0x0200U+i*4U]=0xf8U;
    plain.ram[8U]=0U;plain.ram[0x000fU]=1U;plain.ram[0x0016U]=id;
    plain.ram[0x001eU]=state;plain.ram[9U]=phase;
    plain.ram[0x0046U]=1U;plain.ram[0x0087U]=80U;
    plain.ram[0x00cfU]=96U;plain.ram[0x00b6U]=1U;
    plain.ram[0x00a0U]=0x80U;plain.ram[0x06e5U]=64U;
    plain.ram[0x071aU]=0U;plain.ram[0x071bU]=0U;
    plain.ram[0x071cU]=0U;plain.ram[0x071dU]=255U;
    plain.ram[0x03aeU]=80U;plain.ram[0x03b9U]=96U;
    plain.ram[0x036aU]=id==45U?(phase==0U?1U:2U):0U;
    plain.ram[0x070eU]=id==50U?(unsigned char)(phase/4U):0U;
    plain.ppu.visible_ppu_mask=0x1eU;
    observed=plain;mysmb_text_observer_enable(&observed,1U);
    enemy_draw(&observed,id);enemy_draw(&plain,id);
    CHECK(memcmp(&observed,&plain,offsetof(struct mysmb_game,text_observer))==0);
    CHECK(observed.text_observer.producer.count==1U);
    mysmb_game_submit_oam(&observed);before=observed;
    CHECK(mysmb_text_elements_build(0,0U,9U,&text));
    CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,0,&text,&receipt));
    if(receipt.drawn!=1U || receipt.unsupported!=0U)
        fprintf(stderr,"enemy fixture id=%u state=%u phase=%u drawn=%u unsupported=%u\n",
            id,state,phase,receipt.drawn,receipt.unsupported);
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    CHECK(memcmp(&observed,&before,sizeof(observed))==0);
    return 0;
}

int main(int argc,char **argv)
{
    struct mysmb_input input;
    struct mysmb_frame frame1,frame2;
    struct mysmb_text_actor_receipt actor_receipt;
    struct mysmb_text_background_receipt background_receipt;
    unsigned char fingerprint[16];
    unsigned int i,j,player,enemy,running,text_actors,title_frames;
    unsigned int natural_lives_frames=0U;
    unsigned long background_objects,background_unknown,visible_unknown_running;
    unsigned long unsupported_actors,unowned_running_sprites;
    short scene_x,scene_y;
    FILE *preview,*save_file;
    static const unsigned char enemy_ids[17]={0U,2U,3U,5U,6U,7U,8U,10U,11U,
        12U,13U,18U,17U,45U,50U,51U,53U};

    memset(&observed,0,sizeof(observed));
    observed.ram[0x0200U]=100U; observed.ram[0x0201U]=1U;
    observed.ram[0x0203U]=50U;
    mysmb_text_observer_record(&observed,1U,0U,0U,7U,1U,0U,1U,1U);
    CHECK(observed.text_observer.producer.count==0U);
    mysmb_text_observer_enable(&observed,1U);
    mysmb_text_observer_record(&observed,1U,0U,0U,7U,1U,0U,1U,1U);
    CHECK(observed.text_observer.producer.count==1U);
    CHECK(observed.text_observer.visible.count==0U);
    mysmb_game_submit_oam(&observed);
    CHECK(observed.text_observer.visible.count==1U);
    CHECK(mysmb_text_observer_visible_mask(&observed,0U)==1U);
    observed.ram[0x0201U]=2U;
    CHECK(mysmb_text_observer_visible_mask(&observed,0U)==1U);
    mysmb_game_submit_oam(&observed);
    CHECK(mysmb_text_observer_visible_mask(&observed,0U)==0U);
    mysmb_text_observer_record(&observed,2U,6U,0U,8U,1U,0U,1U,0U);
    mysmb_game_submit_oam(&observed);
    CHECK(observed.text_observer.visible.count==1U);
    CHECK(observed.text_observer.visible.items[0].family==2U);
    CHECK(mysmb_text_observer_visible_mask(&observed,0U)==1U);
    observed.ram[0x0200U]=0xf8U;
    mysmb_text_observer_record(&observed,2U,6U,0U,8U,1U,0U,1U,0U);
    mysmb_game_submit_oam(&observed);
    CHECK(mysmb_text_observer_visible_mask(&observed,0U)==0U);
    mysmb_text_observer_record(&observed,1U,0U,0U,0U,1U,252U,8U,0U);
    CHECK(observed.text_observer.producer.overflow==1U);
    mysmb_game_move_sprites_offscreen(&observed);
    CHECK(observed.text_observer.producer.count==0U);
    CHECK(observed.text_observer.visible.count==1U);
    mysmb_game_submit_oam(&observed);
    CHECK(observed.text_observer.visible.count==0U);

    for(i=0U;i<MYSMB_TEXT_OBSERVATION_CAPACITY+1U;++i)
        mysmb_text_observer_record(&observed,1U,0U,(unsigned char)i,
            0U,1U,(unsigned char)(i*4U),1U,0U);
    CHECK(observed.text_observer.producer.count==MYSMB_TEXT_OBSERVATION_CAPACITY);
    CHECK(observed.text_observer.producer.overflow==0U);
    mysmb_text_observer_record(&observed,1U,0U,0U,0U,1U,0U,9U,0U);
    CHECK(observed.text_observer.producer.overflow==1U);
    mysmb_text_observer_enable(&observed,0U);
    CHECK(observed.text_observer.producer.count==0U);

    for(i=0U;i<4U;++i) {
        mysmb_game_initialize(&observed);
        observed.ram[0x0039U]=(unsigned char)i;
        observed.ram[0x06eaU]=64U;
        observed.ram[0x03aeU]=80U;observed.ram[0x03b9U]=60U;
        plain=observed;
        mysmb_text_observer_enable(&observed,1U);
        mysmb_objects_draw_power_up(&observed);
        mysmb_objects_draw_power_up(&plain);
        CHECK(memcmp(observed.ram,plain.ram,sizeof(plain.ram))==0);
        CHECK(observed.text_observer.producer.count==1U);
        CHECK(observed.text_observer.producer.items[0].identity==i);
        mysmb_game_submit_oam(&observed);
        CHECK(mysmb_text_observer_visible_mask(&observed,0U)==15U);
    }

    CHECK(compare_draw(mysmb_oam_draw_fireball,MYSMB_TEXT_OBSERVE_FIREBALL)==0);
    CHECK(compare_draw(mysmb_oam_draw_fireball_explosion,MYSMB_TEXT_OBSERVE_EXPLOSION)==0);
    CHECK(compare_draw(mysmb_objects_draw_hammer,MYSMB_TEXT_OBSERVE_HAMMER)==0);
    CHECK(compare_draw(mysmb_objects_draw_bouncing_block,MYSMB_TEXT_OBSERVE_BLOCK)==0);
    CHECK(compare_draw(mysmb_objects_draw_brick_chunks,MYSMB_TEXT_OBSERVE_CHUNKS)==0);
    for(i=0U;i<17U;++i)for(j=0U;j<3U;++j)
        CHECK(enemy_case(enemy_ids[i],j==0U?0U:j==1U?4U:5U,
            (unsigned char)(j*4U))==0);
    CHECK(snapshot_case()==0);
    CHECK(star_flag_case()==0);
    CHECK(flag_words_case()==0);
    for(i=0U;i<5U;++i)CHECK(misc_case(0U,(unsigned char)i)==0);
    for(i=1U;i<=11U;++i)CHECK(misc_case((unsigned char)i,0U)==0);
    CHECK(mixed_player_case(1U,0U,0U)==0);
    CHECK(mixed_player_case(0U,0U,0U)==0);
    CHECK(mixed_player_case(0U,1U,0U)==0);
    CHECK(mixed_player_case(0U,1U,4U)==0);
#ifdef MYSMB_LOCAL_TITLE
    CHECK(palette_animation_case()==0);
    CHECK(caption_routes()==0);
    CHECK(player_phase_routes()==0);
#endif
    bind(&observed);bind(&plain);bind(&restored);
    mysmb_text_observer_enable(&observed,1U);
    mysmb_game_snapshot_fingerprint(&observed,fingerprint);
    memset(&frame1,0,sizeof(frame1));memset(&frame2,0,sizeof(frame2));
    input.buttons2=0U;player=0U;enemy=0U;running=0U;text_actors=0U;title_frames=0U;
    background_objects=background_unknown=visible_unknown_running=0UL;
    unsupported_actors=unowned_running_sprites=0UL;
    preview=argc>=2?fopen(argv[1],"wb"):0;
    CHECK(argc<2 || preview!=0);
    for(i=0U;i<1000U;++i) {
        CHECK(mysmb_game_startup_step(&observed,1U)==
            mysmb_game_startup_step(&plain,1U));
        if(observed.startup_phase!=4U)continue;
        input.buttons=(unsigned char)(i==100U?MYSMB_BUTTON_START:
            i>200U?(MYSMB_BUTTON_RIGHT|MYSMB_BUTTON_B|
            (i%40U<8U?MYSMB_BUTTON_A:0U)):0U);
        mysmb_game_tick(&observed,&input,&frame1);
        mysmb_game_tick(&plain,&input,&frame2);
        CHECK(mysmb_game_snapshot_capture(&observed,&first,fingerprint));
        CHECK(mysmb_game_snapshot_capture(&plain,&second,fingerprint));
        CHECK(memcmp(first.payload,second.payload,MYSMB_SNAPSHOT_CORE_BYTES)==0);
        CHECK(memcmp(&frame1,&frame2,sizeof(frame1))==0);
        mysmb_ppu_frame_build(&observed.ppu,&pixels1);
        mysmb_ppu_frame_build(&plain.ppu,&pixels2);
        CHECK(memcmp(pixels1.pixels,pixels2.pixels,sizeof(pixels1.pixels))==0);
        before=observed;
        CHECK(mysmb_text_elements_build(0,0U,9U,&text));
#ifdef MYSMB_LOCAL_TITLE
        CHECK(mysmb_text_background_scene_build(&observed,&background,&text,&background_receipt));
        for(j=0U;j<3995U;++j)if(text.cells[j].character=='S' &&
            text.cells[j+1U].character=='U' && text.cells[j+2U].character=='P' &&
            text.cells[j+3U].character=='E' && text.cells[j+4U].character=='R') {
            ++title_frames;break;
        }
        background_objects+=background_receipt.objects;
        background_unknown+=background_receipt.unsupported;
        /* Separate unsupported HUD/title/offscreen tuples from visible
         * running-area gaps. This finite route is not a world census. */
        if((observed.ppu.visible_ppu_mask&8U)!=0U &&
            mysmb_game_snapshot_running(&observed,&frame1))
            for(j=0U;j<480U;++j) {
                scene_x=(short)((j%32U)*16U)-(short)observed.ppu.visible_scroll_x;
                scene_y=(short)((j/32U)*16U)-(short)observed.ppu.visible_scroll_y;
                if(scene_x<256 && scene_x+16>0 && scene_y<240 && scene_y+16>32 &&
                    background.kinds[j]==0U) {
                    visible_unknown_running++;
                }
            }
#else
        (void)background_receipt;(void)background;(void)scene_x;(void)scene_y;
#endif
        CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,background.opaque,&text,&actor_receipt));
#ifdef MYSMB_LOCAL_TITLE
        if(observed.ram[0x0770U]==1U && !observed.ppu.visible_sprite0_split &&
            observed.ppu.visible_scroll_x==0U && observed.ppu.visible_scroll_y==0U &&
            (observed.ppu.visible_ppu_mask&8U)!=0U &&
            observed.ppu.name_table[0U][10U*32U+11U]==32U &&
            observed.ppu.name_table[0U][14U*32U+15U]==0x29U) {
            char world[10]="WORLD 0-0",life[2];
            world[6]=(char)('0'+observed.ppu.name_table[0U][10U*32U+17U]);
            world[8]=(char)('0'+observed.ppu.name_table[0U][10U*32U+19U]);
            life[0]=(char)('0'+observed.ppu.name_table[0U][14U*32U+18U]);life[1]='\0';
            CHECK(caption_word(10U,11U,world));
            CHECK(caption_word(14U,15U,"x"));
            CHECK(caption_word(14U,18U,life));
            ++natural_lives_frames;
        }
#endif
        unsupported_actors+=actor_receipt.unsupported;
        if((observed.ppu.visible_ppu_mask&0x10U)!=0U &&
            mysmb_game_snapshot_running(&observed,&frame1))
            for(j=1U;j<64U;++j)
                if(observed.ppu.visible_oam[j*4U]<239U &&
                    observed.ppu.visible_oam[j*4U+1U]!=0xfcU &&
                    observed.text_observer.visible.owners[j]==0U)
                    unowned_running_sprites++;
        if(preview!=0) {
            CHECK(fwrite(&text,1U,sizeof(text),preview)==sizeof(text));
        }
        CHECK(memcmp(&observed,&before,sizeof(observed))==0);
        if(i==300U) {
            CHECK(mysmb_snapshot_encode(&first,snapshot_wire,sizeof(snapshot_wire))==0);
            if(argc==3) {
                save_file=fopen(argv[2],"wb");CHECK(save_file!=0);
                CHECK(fwrite(snapshot_wire,1U,sizeof(snapshot_wire),save_file)==sizeof(snapshot_wire));
                CHECK(fclose(save_file)==0);
            }
            CHECK(mysmb_snapshot_decode(snapshot_wire,sizeof(snapshot_wire),fingerprint,&second)==0);
            CHECK(mysmb_game_snapshot_restore(&restored,&second));
        } else if(i>300U && i<=540U) {
            mysmb_game_tick(&restored,&input,&frame2);
            CHECK(memcmp(&observed,&restored,sizeof(observed))==0);
        }
        if(i>=300U && i<=540U) {
            CHECK(mysmb_text_elements_build(0,0U,9U,&loaded_text));
#ifdef MYSMB_LOCAL_TITLE
            CHECK(mysmb_text_background_scene_build(&restored,&background,&loaded_text,&background_receipt));
#endif
            CHECK(mysmb_text_actor_scene_draw(&restored,&actor_workspace,background.opaque,&loaded_text,&actor_receipt));
            CHECK(memcmp(&text,&loaded_text,sizeof(text))==0);
        }
        text_actors+=actor_receipt.drawn;
        CHECK(observed.text_observer.producer.overflow==0U);
        if(mysmb_game_snapshot_running(&observed,&frame1))running++;
        for(j=0U;j<observed.text_observer.visible.count;++j) {
            if(!mysmb_text_observer_visible_mask(&observed,(unsigned char)j))continue;
            if(observed.text_observer.visible.items[j].family==1U)player++;
            if(observed.text_observer.visible.items[j].family==2U)enemy++;
        }
    }
    if(preview!=0)CHECK(fclose(preview)==0);
#ifdef MYSMB_LOCAL_TITLE
    CHECK(running>100U && player>100U && enemy>0U);
    CHECK(text_actors>100U);
    CHECK(title_frames>0U);
#endif
    before=observed;first.payload[4428U]=65U;
    CHECK(!mysmb_game_snapshot_restore(&observed,&first));
    CHECK(memcmp(&observed,&before,sizeof(observed))==0);
    CHECK(mysmb_game_snapshot_restore(&observed,&second));
    CHECK(observed.text_observer.enabled==1U);
    CHECK(observed.text_observer.producer.count==0U &&
        observed.text_observer.visible.count==0U);
    printf("1000-step twin route: zero core/frame/pixel differences; "
        "running=%u player=%u enemy=%u observer_bytes=%u\n",
        running,player,enemy,(unsigned int)sizeof(struct mysmb_text_observer));
    printf("authored actor layer: %u draws; game and observer unchanged\n",text_actors);
    printf("committed authored title sign: %u frames\n",title_frames);
#ifdef MYSMB_LOCAL_TITLE
    CHECK(natural_lives_frames!=0U);
    printf("natural startup final-composed world/lives captions: %u frames\n",natural_lives_frames);
#else
    (void)natural_lives_frames;
#endif
    printf("snapshot: immediate authored frame and 240 future ticks identical; malformed receipts rejected atomically\n");
    printf("semantic background: %lu objects, %lu unknown metatiles; no game mutation\n",
        background_objects,background_unknown);
    printf("finite route visible running-area unsupported metatiles: %lu\n",
        visible_unknown_running);
    printf("finite route unsupported actors=%lu unowned running sprites excluding sprite0=%lu\n",
        unsupported_actors,unowned_running_sprites);
    return 0;
}
