#include "game/game.h"
#include "game/frame_root.h"
#include "game/ppu_frame.h"
#include "game/oam/oam.h"
#include "game/presentation/text/actor_scene.h"
#include "game/presentation/text/background_scene.h"
#include "app/game_snapshot.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#ifdef MYSMB_LOCAL_TITLE
#include "game/area.h"
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
    plain.visible_ppu_mask=0x1eU;
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
    unsigned int i,j,player,enemy,running,text_actors;
    unsigned long background_objects,background_unknown;
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
    CHECK(mixed_player_case(1U,0U,0U)==0);
    CHECK(mixed_player_case(0U,0U,0U)==0);
    CHECK(mixed_player_case(0U,1U,0U)==0);
    CHECK(mixed_player_case(0U,1U,4U)==0);
    bind(&observed);bind(&plain);bind(&restored);
    mysmb_text_observer_enable(&observed,1U);
    mysmb_game_snapshot_fingerprint(&observed,fingerprint);
    memset(&frame1,0,sizeof(frame1));memset(&frame2,0,sizeof(frame2));
    input.buttons2=0U;player=0U;enemy=0U;running=0U;text_actors=0U;
    background_objects=background_unknown=0UL;
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
        CHECK(mysmb_text_actor_scene_draw(&observed,&actor_workspace,background.opaque,&text,&actor_receipt));
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
    printf("snapshot: immediate authored frame and 240 future ticks identical; malformed receipts rejected atomically\n");
    printf("semantic background: %lu objects, %lu unknown metatiles; no game mutation\n",
        background_objects,background_unknown);
    return 0;
}
