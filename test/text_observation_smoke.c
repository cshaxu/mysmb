#include "game/game.h"
#include "game/frame_root.h"
#include "game/ppu_frame.h"
#include "game/oam/oam.h"
#include "game/presentation/text/actor_scene.h"
#include "game/presentation/text/background_scene.h"
#include "app/game_snapshot.h"
#include <stdio.h>
#include <string.h>
#ifdef MYSMB_LOCAL_TITLE
#include "game/area.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

static struct mysmb_game observed,plain,before;
static struct mysmb_io_snapshot first,second;
static struct mysmb_ppu_frame pixels1,pixels2;
static struct mysmb_io_text_frame text;
static struct mysmb_text_background_workspace background;
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

int main(int argc,char **argv)
{
    struct mysmb_input input;
    struct mysmb_frame frame1,frame2;
    struct mysmb_text_actor_receipt actor_receipt;
    struct mysmb_text_background_receipt background_receipt;
    unsigned char fingerprint[16];
    unsigned int i,j,player,enemy,running,text_actors;
    unsigned long background_objects,background_unknown;
    FILE *preview;

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
    bind(&observed);bind(&plain);
    mysmb_text_observer_enable(&observed,1U);
    mysmb_game_snapshot_fingerprint(&observed,fingerprint);
    memset(&frame1,0,sizeof(frame1));memset(&frame2,0,sizeof(frame2));
    input.buttons2=0U;player=0U;enemy=0U;running=0U;text_actors=0U;
    background_objects=background_unknown=0UL;
    preview=argc==2?fopen(argv[1],"wb"):0;
    CHECK(argc!=2 || preview!=0);
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
        mysmb_ppu_frame_build(&observed,&pixels1);
        mysmb_ppu_frame_build(&plain,&pixels2);
        CHECK(memcmp(pixels1.pixels,pixels2.pixels,sizeof(pixels1.pixels))==0);
        before=observed;
        CHECK(mysmb_text_elements_build(0,0U,9U,&text));
#ifdef MYSMB_LOCAL_TITLE
        CHECK(mysmb_text_background_scene_build(&observed,&background,&text,&background_receipt));
        background_objects+=background_receipt.objects;
        background_unknown+=background_receipt.unsupported;
#else
        (void)background_receipt;(void)background;
#endif
        CHECK(mysmb_text_actor_scene_draw(&observed,&text,&actor_receipt));
        if(preview!=0) {
            CHECK(fwrite(&text,1U,sizeof(text),preview)==sizeof(text));
        }
        CHECK(memcmp(&observed,&before,sizeof(observed))==0);
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
    printf("semantic background: %lu objects, %lu unknown metatiles; no game mutation\n",
        background_objects,background_unknown);
    return 0;
}
