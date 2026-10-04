#include "game/presentation/text/actor_scene.h"
#include "io/color.h"

struct actor_clip {
    const struct mysmb_game *game;
    const struct mysmb_text_observation *item;
    unsigned char mask;
};

static int visible_cell(const void MYSMB_IO_FAR *context,
    mysmb_io_u16 column,mysmb_io_u16 row)
{
    const struct actor_clip *clip;
    unsigned short x,y,sx,sy,i;
    clip=(const struct actor_clip *)context;
    x=(unsigned short)(((unsigned long)column*256UL+128UL)/80UL);
    y=(unsigned short)(((unsigned long)row*240UL+120UL)/50UL);
    if(x<8U && (clip->game->visible_ppu_mask&4U)==0U)return 0;
    for(i=0U;i<clip->item->sprites;++i) {
        if((clip->mask&(1U<<i))==0U)continue;
        sx=clip->item->entries[i*4U+3U];
        sy=(unsigned short)(clip->item->entries[i*4U]+1U);
        if(x>=sx && x<sx+8U && y>=sy && y<sy+8U)return 1;
    }
    return 0;
}

static int player_pose(const struct mysmb_game *game,
    const struct mysmb_text_observation *item,struct mysmb_text_element *e)
{
    unsigned short base;
    unsigned char phase;
    base=(unsigned short)(0x6e07U+(item->source_size!=0U?8U:0U));
    if(game->area_prg==0 || game->area_prg_size<base+8U)return 0;
    e->kind=item->source_size!=0U?MYSMB_TEXT_PLAYER_SMALL:MYSMB_TEXT_PLAYER_LARGE;
    if(item->graphics==game->area_prg[base+2U]) {e->pose=MYSMB_TEXT_STAND;return 1;}
    if(item->graphics==game->area_prg[base]) {e->pose=MYSMB_TEXT_JUMP;return 1;}
    for(phase=0U;phase<3U;++phase)
        if(item->graphics==(unsigned char)(game->area_prg[base+4U]+phase*8U)) {
            e->pose=MYSMB_TEXT_RUN;return 1;
        }
    return 0;
}

static int choose(const struct mysmb_game *game,
    const struct mysmb_text_observation *item,struct mysmb_text_element *e)
{
    e->pose=0U;
    switch(item->family) {
    case MYSMB_TEXT_OBSERVE_PLAYER: return player_pose(game,item,e);
    case MYSMB_TEXT_OBSERVE_ENEMY:
        if(item->identity!=6U ||
            (item->graphics!=0U && item->graphics!=0x54U))return 0;
        /* Defeated/inverted variants need their own authored templates. */
        if((item->entries[2U]&0x80U)!=0U)return 0;
        e->kind=MYSMB_TEXT_GOOMBA;return 1;
    case MYSMB_TEXT_OBSERVE_POWERUP:
        if(item->identity>3U)return 0;
        e->kind=item->identity==1U?MYSMB_TEXT_FLOWER:
            item->identity==2U?MYSMB_TEXT_STAR:MYSMB_TEXT_MUSHROOM;return 1;
    case MYSMB_TEXT_OBSERVE_FIREBALL:
    case MYSMB_TEXT_OBSERVE_FIREBAR: e->kind=MYSMB_TEXT_FIREBALL;return 1;
    case MYSMB_TEXT_OBSERVE_EXPLOSION: e->kind=MYSMB_TEXT_EXPLOSION;return 1;
    case MYSMB_TEXT_OBSERVE_HAMMER: e->kind=MYSMB_TEXT_HAMMER;return 1;
    case MYSMB_TEXT_OBSERVE_BLOCK:
        if(item->identity==0xc4U)return 0;
        e->kind=MYSMB_TEXT_BRICK;return 1;
    case MYSMB_TEXT_OBSERVE_CHUNKS: e->kind=MYSMB_TEXT_CHUNK;return 1;
    case MYSMB_TEXT_OBSERVE_VINE: e->kind=MYSMB_TEXT_VINE;return 1;
    case MYSMB_TEXT_OBSERVE_PLATFORM: e->kind=MYSMB_TEXT_PLATFORM;return 1;
    case MYSMB_TEXT_OBSERVE_FLAG: e->kind=MYSMB_TEXT_FLAG;return 1;
    case MYSMB_TEXT_OBSERVE_BUBBLE: e->kind=MYSMB_TEXT_BUBBLE;return 1;
    default: return 0;
    }
}

int mysmb_text_actor_scene_draw(const struct mysmb_game *game,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    struct mysmb_text_actor_receipt *receipt)
{
    const struct mysmb_text_observation *item;
    struct mysmb_text_element element;
    struct actor_clip clip;
    unsigned short priority,i,j,first,sx,sy,palette;
    unsigned char mask;
    if(game==0 || frame==0 || receipt==0 || game->text_observer.enabled!=1U ||
        game->text_observer.visible.count>MYSMB_TEXT_OBSERVATION_CAPACITY)return 0;
    receipt->drawn=receipt->unsupported=receipt->unowned_sprites=0U;
    if((game->visible_ppu_mask&0x10U)==0U)return 1;
    for(i=0U;i<64U;++i)
        if(game->visible_oam[i*4U]<239U && game->visible_oam[i*4U+1U]!=0xfcU &&
            game->text_observer.visible.owners[i]==0U)receipt->unowned_sprites++;
    for(priority=64U;priority!=0U;) {
        --priority;
        for(i=0U;i<game->text_observer.visible.count;++i) {
            item=&game->text_observer.visible.items[i];
            mask=mysmb_text_observer_visible_mask(game,(unsigned char)i);
            if(mask==0U)continue;
            first=64U;element.x=256;element.y=240;
            for(j=0U;j<item->sprites;++j) {
                if((mask&(1U<<j))!=0U && item->oam/4U+j<first)
                    first=(unsigned short)(item->oam/4U+j);
                /* Ownership clipping must not relocate the whole template. */
                if(item->entries[j*4U]>=239U ||
                    item->entries[j*4U+1U]==0xfcU)continue;
                sx=item->entries[j*4U+3U];sy=(unsigned short)(item->entries[j*4U]+1U);
                if(sx<(unsigned short)element.x)element.x=(short)sx;
                if(sy<(unsigned short)element.y)element.y=(short)sy;
            }
            if(first!=priority)continue;
            if(!choose(game,item,&element)) {receipt->unsupported++;continue;}
            palette=(unsigned short)((game->visible_oam[first*4U+2U]&3U)*4U);
            element.background=mysmb_io_color_text16(game->palette[0x12U+palette]);
            element.foreground=15U;
            element.face_left=(item->facing&2U)!=0U?1U:0U;
            clip.game=game;clip.item=item;clip.mask=mask;
            if(!mysmb_text_element_draw(&element,frame,visible_cell,&clip))return 0;
            receipt->drawn++;
        }
    }
    return 1;
}
