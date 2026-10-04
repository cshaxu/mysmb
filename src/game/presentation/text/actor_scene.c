#include "game/presentation/text/actor_scene.h"
#include "io/color.h"

struct actor_clip {
    const struct mysmb_game *game;
    const struct mysmb_text_observation *item;
    unsigned char mask;
    unsigned char behind;
    struct mysmb_text_actor_workspace MYSMB_IO_FAR *workspace;
    const unsigned char MYSMB_IO_FAR *background;
};

static int visible_cell(const void MYSMB_IO_FAR *context,
    mysmb_io_u16 column,mysmb_io_u16 row)
{
    const struct actor_clip *clip;
    unsigned short x,y,sx,sy,i,cell;
    unsigned char bit;
    clip=(const struct actor_clip *)context;
    x=(unsigned short)(((unsigned long)column*256UL+128UL)/80UL);
    y=(unsigned short)(((unsigned long)row*240UL+120UL)/50UL);
    if(x<8U && (clip->game->visible_ppu_mask&4U)==0U)return 0;
    for(i=0U;i<clip->item->sprites;++i) {
        if((clip->mask&(1U<<i))==0U)continue;
        sx=clip->item->entries[i*4U+3U];
        sy=(unsigned short)(clip->item->entries[i*4U]+1U);
        if(x>=sx && x<sx+8U && y>=sy && y<sy+8U) {
            cell=(unsigned short)(row*80U+column);bit=(unsigned char)(1U<<(cell%8U));
            if((clip->workspace->claimed[cell/8U]&bit)!=0U)return 0;
            clip->workspace->claimed[cell/8U]|=bit;
            return clip->behind==0U || clip->background==0 ||
                (clip->background[cell/8U]&bit)==0U;
        }
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
    if((item->identity&MYSMB_TEXT_PLAYER_DEATH_FLAG)!=0U) {
        e->kind=MYSMB_TEXT_PLAYER_SMALL;e->pose=MYSMB_TEXT_DEAD;return 1;
    }
    if(item->graphics==game->area_prg[base+2U]) {e->pose=MYSMB_TEXT_STAND;return 1;}
    if(item->graphics==game->area_prg[base]) {e->pose=MYSMB_TEXT_JUMP;return 1;}
    for(phase=0U;phase<3U;++phase)
        if(item->graphics==(unsigned char)(game->area_prg[base+4U]+phase*8U)) {
            e->pose=phase==0U?MYSMB_TEXT_RUN:phase==1U?
                MYSMB_TEXT_RUN_SECOND:MYSMB_TEXT_RUN_THIRD;return 1;
        }
    if(item->graphics==game->area_prg[base+3U]) {e->pose=MYSMB_TEXT_SKID;return 1;}
    if(item->graphics==game->area_prg[base+6U]) {e->pose=MYSMB_TEXT_CROUCH;return 1;}
    if(item->graphics==game->area_prg[0x6e0eU]) {e->pose=MYSMB_TEXT_THROW;return 1;}
    for(phase=0U;phase<3U;++phase)
        if(item->graphics==(unsigned char)(game->area_prg[base+1U]+phase*8U)) {
            e->pose=phase==0U?MYSMB_TEXT_SWIM:phase==1U?
                MYSMB_TEXT_SWIM_SECOND:MYSMB_TEXT_SWIM_THIRD;return 1;
        }
    for(phase=0U;phase<2U;++phase)
        if(item->graphics==(unsigned char)(game->area_prg[base+5U]+phase*8U)) {
            e->pose=phase==0U?MYSMB_TEXT_CLIMB:MYSMB_TEXT_CLIMB_SECOND;return 1;
        }
    if(item->graphics==0xb8U || item->graphics==0xc0U) {
        e->kind=MYSMB_TEXT_PLAYER_SMALL;e->pose=MYSMB_TEXT_STAND;return 1;
    }
    return 0;
}

static int enemy_pose(const struct mysmb_text_observation *item,
    struct mysmb_text_element *e)
{
    unsigned char g;
    g=item->graphics;
    /* Selected normal-owner graphics code also distinguishes Bowser halves
     * and jumpsprings from their raw object IDs. Dedicated receipts use255. */
    if(item->source_size==22U)e->kind=MYSMB_TEXT_BOWSER_FRONT;
    else if(item->source_size==23U)e->kind=MYSMB_TEXT_BOWSER_REAR;
    else if(item->source_size>=24U && item->source_size<=26U)e->kind=MYSMB_TEXT_SPRING;
    else switch(item->identity) {
    case 0U:case 1U:case 3U:case 4U:case 9U:case 14U:case 15U:case 16U:
        e->kind=(g>=0x5aU && g<=0x78U)?MYSMB_TEXT_SHELL:MYSMB_TEXT_KOOPA;break;
    case 2U:e->kind=(g>=0x5aU && g<=0x84U)?MYSMB_TEXT_SHELL:MYSMB_TEXT_BEETLE;break;
    case 5U:e->kind=MYSMB_TEXT_HAMMER_BRO;break;
    case 6U:e->kind=g==0x8aU?MYSMB_TEXT_GOOMBA_FLAT:MYSMB_TEXT_GOOMBA;break;
    case 7U:e->kind=MYSMB_TEXT_BLOOBER;break;
    case 8U:case 51U:e->kind=MYSMB_TEXT_BULLET;break;
    case 10U:case 11U:case 20U:e->kind=MYSMB_TEXT_FISH;break;
    case 12U:e->kind=MYSMB_TEXT_PODOBOO;break;
    case 13U:e->kind=MYSMB_TEXT_PIRANHA;break;
    case 17U:e->kind=MYSMB_TEXT_LAKITU;break;
    case 18U:e->kind=g==0x30U || g==0x36U?MYSMB_TEXT_EGG:MYSMB_TEXT_SPINY;break;
    case 53U:e->kind=MYSMB_TEXT_RETAINER;break;
    default:return 0;
    }
    e->pose=(item->entries[2U]&0x80U)!=0U?MYSMB_TEXT_INVERTED:
        (g==0x06U || g==0x12U || g==0x1eU || g==0x2aU || g==0x36U ||
         g==0x42U || g==0x4eU || g==0xaeU || g==0xbaU || g==0xc6U ||
         g==0xdeU || g==0xe4U)?MYSMB_TEXT_SECOND:0U;
    if(e->kind==MYSMB_TEXT_SHELL && (g==0x5aU || g==0x60U || g==0x84U))
        e->pose=MYSMB_TEXT_INVERTED;
    if(e->kind==MYSMB_TEXT_RETAINER && g==0xa2U)e->pose=MYSMB_TEXT_SECOND;
    if(e->kind==MYSMB_TEXT_SPRING && item->source_size!=24U)e->pose=MYSMB_TEXT_SECOND;
    /* Right-column vertical flip is the egg's authored symmetry,not a
     * vertically inverted whole egg. A flat Goomba stays flat. */
    if(e->kind==MYSMB_TEXT_EGG || e->kind==MYSMB_TEXT_GOOMBA_FLAT)e->pose=0U;
    return 1;
}

static int choose(const struct mysmb_game *game,
    const struct mysmb_text_observation *item,struct mysmb_text_element *e)
{
    e->pose=0U;
    switch(item->family) {
    case MYSMB_TEXT_OBSERVE_PLAYER: return player_pose(game,item,e);
    case MYSMB_TEXT_OBSERVE_ENEMY:
        return enemy_pose(item,e);
    case MYSMB_TEXT_OBSERVE_POWERUP:
        if(item->identity>3U)return 0;
        e->kind=item->identity==1U?MYSMB_TEXT_FLOWER:
            item->identity==2U?MYSMB_TEXT_STAR:MYSMB_TEXT_MUSHROOM;return 1;
    case MYSMB_TEXT_OBSERVE_FIREBALL:
    case MYSMB_TEXT_OBSERVE_FIREBAR: e->kind=MYSMB_TEXT_FIREBALL;return 1;
    case MYSMB_TEXT_OBSERVE_EXPLOSION: e->kind=MYSMB_TEXT_EXPLOSION;return 1;
    case MYSMB_TEXT_OBSERVE_HAMMER: e->kind=MYSMB_TEXT_HAMMER;return 1;
    case MYSMB_TEXT_OBSERVE_BLOCK:
        e->kind=item->identity==0xc4U?MYSMB_TEXT_EMPTY_BLOCK:MYSMB_TEXT_BRICK;return 1;
    case MYSMB_TEXT_OBSERVE_FLAME:
        e->kind=MYSMB_TEXT_FLAME;e->pose=(item->graphics&0x80U)!=0U?1U:0U;return 1;
    case MYSMB_TEXT_OBSERVE_CHUNKS: e->kind=MYSMB_TEXT_CHUNK;return 1;
    case MYSMB_TEXT_OBSERVE_VINE: e->kind=MYSMB_TEXT_VINE;return 1;
    case MYSMB_TEXT_OBSERVE_PLATFORM: e->kind=MYSMB_TEXT_PLATFORM;return 1;
    case MYSMB_TEXT_OBSERVE_FLAG: e->kind=MYSMB_TEXT_FLAG;return 1;
    case MYSMB_TEXT_OBSERVE_BUBBLE: e->kind=MYSMB_TEXT_BUBBLE;return 1;
    default: return 0;
    }
}

int mysmb_text_actor_scene_draw(const struct mysmb_game *game,
    struct mysmb_text_actor_workspace MYSMB_IO_FAR *workspace,
    const unsigned char MYSMB_IO_FAR *background_opaque,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    struct mysmb_text_actor_receipt *receipt)
{
    const struct mysmb_text_observation *item;
    struct mysmb_text_element element;
    struct actor_clip clip;
    unsigned short priority,i,j,sx,sy,palette;
    unsigned char mask,seen[64];
    if(game==0 || workspace==0 || frame==0 || receipt==0 || game->text_observer.enabled!=1U ||
        game->text_observer.visible.count>MYSMB_TEXT_OBSERVATION_CAPACITY)return 0;
    receipt->drawn=receipt->unsupported=receipt->unowned_sprites=0U;
    for(i=0U;i<500U;++i)workspace->claimed[i]=0U;
    for(i=0U;i<64U;++i)seen[i]=0U;
    if((game->visible_ppu_mask&0x10U)==0U)return 1;
    for(i=0U;i<64U;++i)
        if(game->visible_oam[i*4U]<239U && game->visible_oam[i*4U+1U]!=0xfcU &&
            game->text_observer.visible.owners[i]==0U)receipt->unowned_sprites++;
    for(priority=0U;priority<64U;++priority) {
        i=game->text_observer.visible.owners[priority];
        if(i==0U || i>game->text_observer.visible.count)continue;
        --i;
            item=&game->text_observer.visible.items[i];
            mask=mysmb_text_observer_visible_mask(game,(unsigned char)i);
            j=(unsigned short)(priority-item->oam/4U);
            if(j>=item->sprites || (mask&(1U<<j))==0U)continue;
            mask=(unsigned char)(1U<<j);element.x=256;element.y=240;
            for(j=0U;j<item->sprites;++j) {
                /* Ownership clipping must not relocate the whole template. */
                if(item->entries[j*4U]>=239U ||
                    item->entries[j*4U+1U]==0xfcU)continue;
                sx=item->entries[j*4U+3U];sy=(unsigned short)(item->entries[j*4U]+1U);
                if(sx<(unsigned short)element.x)element.x=(short)sx;
                if(sy<(unsigned short)element.y)element.y=(short)sy;
            }
            if(!choose(game,item,&element)) {
                if(seen[i]==0U)receipt->unsupported++;
                seen[i]=1U;continue;
            }
            if(item->family==MYSMB_TEXT_OBSERVE_CHUNKS ||
                item->family==MYSMB_TEXT_OBSERVE_FIREBAR ||
                item->family==MYSMB_TEXT_OBSERVE_FIREBALL ||
                item->family==MYSMB_TEXT_OBSERVE_BUBBLE) {
                element.x=game->visible_oam[priority*4U+3U];
                element.y=(short)(game->visible_oam[priority*4U]+1U);
            }
            palette=(unsigned short)((game->visible_oam[priority*4U+2U]&3U)*4U);
            element.background=mysmb_io_color_text16(game->palette[0x12U+palette]);
            element.foreground=15U;
            element.face_left=(item->facing&2U)!=0U?1U:0U;
            clip.game=game;clip.item=item;clip.mask=mask;
            clip.workspace=workspace;clip.background=background_opaque;
            clip.behind=(unsigned char)(game->visible_oam[priority*4U+2U]&0x20U);
            if(!mysmb_text_element_draw(&element,frame,visible_cell,&clip))return 0;
            if(seen[i]==0U)receipt->drawn++;
            seen[i]=1U;
    }
    return 1;
}
