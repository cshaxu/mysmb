#include "text/actor_scene.h"
#include "io/color.h"
#include "text/layout.h"
#include "text/compact_elements.h"

struct actor_clip {
    const struct mysmb_game *game;
    const struct mysmb_text_observation *item;
    unsigned char mask;
    unsigned char behind;
    struct mysmb_text_actor_workspace MYSMB_IO_FAR *workspace;
    const unsigned char MYSMB_IO_FAR *background;
    const struct mysmb_text_element *element;
    unsigned short rows,columns,height,source_width,source_height;
};

/* Place a tiny component on the first cell whose center lies inside its
 * source rectangle. A floor-only anchor can hide a one-row glyph entirely. */
static short component_anchor(unsigned short position,unsigned short scale,
    unsigned short extent)
{
    unsigned long product,cell;
    product=(unsigned long)position*scale;
    cell=product<=extent/2U?0UL:(product-extent/2U+extent-1U)/extent;
    return (short)((cell*extent+scale-1U)/scale);
}

static int visible_cell(const void MYSMB_IO_FAR *context,
    mysmb_io_u16 column,mysmb_io_u16 row)
{
    const struct actor_clip *clip;
    unsigned short x,y,sx,sy,i,cell;
    unsigned char bit;
    clip=(const struct actor_clip *)context;
    x=(unsigned short)(((unsigned long)column*256UL+128UL)/80UL);
    y=(unsigned short)(((unsigned long)row*240UL+120UL)/clip->rows);
    if(clip->rows==25U) {
        long left,top,c,r,px,py;
        px=(long)clip->element->x*80L;
        py=(long)clip->element->y*25L;
        left=px<0L?-((-px+255L)/256L):px/256L;
        top=py<0L?-((-py+239L)/240L):py/240L;
        c=(long)column-left;r=(long)row-top;
        if(c<0L || r<0L || c>=clip->columns || r>=clip->height)return 0;
        px=clip->element->x+(c*clip->source_width+clip->source_width/2U)/clip->columns;
        py=clip->element->y+(r*clip->source_height+clip->source_height/2U)/clip->height;
        if(py<0L || py>=240L)return 0;
        x=(unsigned short)(px&255L);y=(unsigned short)py;
    }
    if(x<8U && (clip->game->ppu.visible_ppu_mask&4U)==0U)return 0;
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
    e->kind=item->source_size!=0U?
        ((item->identity&1U)!=0U?MYSMB_TEXT_LUIGI_SMALL:MYSMB_TEXT_PLAYER_SMALL):
        ((item->identity&1U)!=0U?MYSMB_TEXT_LUIGI_LARGE:MYSMB_TEXT_PLAYER_LARGE);
    if((item->identity&MYSMB_TEXT_PLAYER_DEATH_FLAG)!=0U) {
        e->kind=(item->identity&1U)!=0U?MYSMB_TEXT_LUIGI_SMALL:MYSMB_TEXT_PLAYER_SMALL;
        e->pose=MYSMB_TEXT_DEAD;return 1;
    }
    if((item->identity&MYSMB_TEXT_PLAYER_THROW_FLAG)!=0U) {
        e->pose=MYSMB_TEXT_THROW;return 1;
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
        e->kind=(item->identity&1U)!=0U?MYSMB_TEXT_LUIGI_SMALL:MYSMB_TEXT_PLAYER_SMALL;
        e->pose=MYSMB_TEXT_STAND;return 1;
    }
    return 0;
}

/* One authored platform span across the selected three/six source columns.
 * Fill every covered text cell; repeated tile-sized borders would produce
 * separate boxes and holes instead of a continuous moving platform. */
static void platform_span(const struct mysmb_text_element *element,
    const struct mysmb_text_observation *item,unsigned short entry,
    const struct actor_clip *clip,struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{
    unsigned short first,last,column,row,cell,columns;
    unsigned char c;
    first=(unsigned short)((unsigned long)element->x*80UL/256UL);
    last=(unsigned short)(((unsigned long)(item->entries[entry*4U+3U]+8U)*80UL-129UL)/256UL);
    row=(unsigned short)((unsigned long)element->y*clip->rows/240UL);
    columns=item->identity==0U?3U:6U;
    if(row>=clip->rows)return;
    for(column=first;column<=last && column<80U;++column) {
        if(!visible_cell(clip,column,row))continue;
        c=column==first && entry%columns==0U?'[':
            column==last && entry%columns==columns-1U?']':'=';
        cell=(unsigned short)(row*80U+column);
        frame->cells[cell].character=c;
        frame->cells[cell].foreground=element->foreground;
        frame->cells[cell].background=element->background;
    }
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
    if(e->kind==MYSMB_TEXT_KOOPA && (g==0x18U || g==0x1eU))
        e->kind=MYSMB_TEXT_WINGED_KOOPA;
    e->pose=(item->entries[2U]&0x80U)!=0U?MYSMB_TEXT_INVERTED:
        (g==0x06U || g==0x12U || g==0x1eU || g==0x2aU || g==0x36U ||
         g==0x42U || g==0x4eU || g==0x96U || g==0xaeU || g==0xbaU || g==0xc6U ||
         g==0xdeU || g==0xe4U)?MYSMB_TEXT_SECOND:0U;
    if(e->kind==MYSMB_TEXT_SHELL && (g==0x5aU || g==0x60U ||
        (item->identity==2U && (g==0x7eU || g==0x84U))))
        e->pose=MYSMB_TEXT_INVERTED;
    if(e->kind==MYSMB_TEXT_SHELL && e->pose!=MYSMB_TEXT_INVERTED &&
        g==0x6cU)e->pose=MYSMB_TEXT_SECOND;
    if(e->kind==MYSMB_TEXT_RETAINER && g==0x9cU)e->pose=MYSMB_TEXT_SECOND;
    if(e->kind==MYSMB_TEXT_SPRING)e->pose=(unsigned char)(item->source_size-24U);
    if(e->kind==MYSMB_TEXT_HAMMER_BRO && e->pose!=MYSMB_TEXT_INVERTED) {
        if(g==0xb4U)e->pose=3U;
        if(g==0xbaU)e->pose=4U;
    }
    /* Right-column vertical flip is the egg's authored symmetry,not a
     * vertically inverted whole egg. A flat Goomba stays flat. */
    if(e->kind==MYSMB_TEXT_EGG)e->pose=g==0x36U?MYSMB_TEXT_SECOND:0U;
    if(e->kind==MYSMB_TEXT_GOOMBA_FLAT)e->pose=0U;
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
    case MYSMB_TEXT_OBSERVE_FIREBAR:
        e->kind=MYSMB_TEXT_FIREBALL;e->pose=(unsigned char)(item->graphics&1U);return 1;
    case MYSMB_TEXT_OBSERVE_EXPLOSION:
        e->kind=MYSMB_TEXT_EXPLOSION;e->pose=item->graphics<3U?item->graphics:2U;return 1;
    case MYSMB_TEXT_OBSERVE_HAMMER:
        e->kind=MYSMB_TEXT_HAMMER;e->pose=(unsigned char)(item->graphics&3U);return 1;
    case MYSMB_TEXT_OBSERVE_BLOCK:
        e->kind=item->identity==0xc4U?MYSMB_TEXT_EMPTY_BLOCK:MYSMB_TEXT_BRICK;return 1;
    case MYSMB_TEXT_OBSERVE_FLAME:
        e->kind=MYSMB_TEXT_FLAME;e->pose=(item->graphics&0x80U)!=0U?1U:0U;return 1;
    case MYSMB_TEXT_OBSERVE_CHUNKS: e->kind=MYSMB_TEXT_CHUNK;return 1;
    case MYSMB_TEXT_OBSERVE_VINE: e->kind=MYSMB_TEXT_VINE;return 1;
    case MYSMB_TEXT_OBSERVE_PLATFORM: e->kind=MYSMB_TEXT_PLATFORM;return 1;
    case MYSMB_TEXT_OBSERVE_FLAG: e->kind=MYSMB_TEXT_FLAG;return 1;
    case MYSMB_TEXT_OBSERVE_BUBBLE: e->kind=MYSMB_TEXT_BUBBLE;return 1;
    case MYSMB_TEXT_OBSERVE_COIN:
        if(item->graphics<0x60U || item->graphics>0x63U)return 0;
        e->kind=MYSMB_TEXT_JUMP_COIN;e->pose=(unsigned char)(item->graphics-0x60U);return 1;
    case MYSMB_TEXT_OBSERVE_SCORE:
        if(item->graphics==0U || item->graphics>11U)return 0;
        e->kind=MYSMB_TEXT_SCORE;e->pose=(unsigned char)(item->graphics-1U);return 1;
    case MYSMB_TEXT_OBSERVE_STAR_FLAG:e->kind=MYSMB_TEXT_STAR_FLAG;return 1;
    default: return 0;
    }
}

/* Authored body/detail roles. Source-selected palettes remain per entry;
 * no tile/pixel census or live object selector runs during presentation. */
static void actor_colors(const struct mysmb_game *game,
    const struct mysmb_io_text_frame MYSMB_IO_FAR *frame,unsigned short entry,
    unsigned short palette,struct mysmb_text_element *e)
{
    unsigned char body,detail;
    body=2U;detail=0U;
    switch(e->kind) {
    case MYSMB_TEXT_PLAYER_SMALL:case MYSMB_TEXT_PLAYER_LARGE:
    case MYSMB_TEXT_LUIGI_SMALL:case MYSMB_TEXT_LUIGI_LARGE:
        body=entry<2U?1U:entry<4U?2U:entry<6U?1U:3U;detail=3U;break;
    case MYSMB_TEXT_MUSHROOM:body=entry<2U?3U:2U;detail=1U;break;
    case MYSMB_TEXT_FLOWER:body=entry<2U?2U:1U;detail=3U;break;
    case MYSMB_TEXT_STAR:body=3U;detail=1U;break;
    case MYSMB_TEXT_GOOMBA:body=entry<4U?3U:2U;detail=1U;break;
    case MYSMB_TEXT_GOOMBA_FLAT:body=3U;detail=1U;break;
    case MYSMB_TEXT_KOOPA:case MYSMB_TEXT_WINGED_KOOPA:
        body=entry<4U?3U:1U;detail=2U;break;
    case MYSMB_TEXT_SHELL:
        body=1U;detail=2U;break;
    case MYSMB_TEXT_BEETLE:case MYSMB_TEXT_BULLET:
        body=1U;detail=2U;break;
    case MYSMB_TEXT_PIRANHA:body=entry<4U?1U:3U;detail=2U;break;
    case MYSMB_TEXT_FISH:body=entry<4U?2U:1U;detail=3U;break;
    case MYSMB_TEXT_HAMMER_BRO:case MYSMB_TEXT_SPINY:case MYSMB_TEXT_EGG:
    case MYSMB_TEXT_BOWSER_FRONT:case MYSMB_TEXT_BOWSER_REAR:
        body=1U;detail=3U;break;
    case MYSMB_TEXT_LAKITU:body=entry<4U?1U:2U;detail=3U;break;
    case MYSMB_TEXT_FIREBALL:case MYSMB_TEXT_EXPLOSION:
    case MYSMB_TEXT_PODOBOO:case MYSMB_TEXT_FLAME:
        body=1U;detail=3U;break;
    case MYSMB_TEXT_BRICK:case MYSMB_TEXT_EMPTY_BLOCK:case MYSMB_TEXT_CHUNK:
    case MYSMB_TEXT_HAMMER:case MYSMB_TEXT_PLATFORM:case MYSMB_TEXT_PLATFORM_PART:
        body=3U;detail=1U;break;
    case MYSMB_TEXT_VINE:case MYSMB_TEXT_VINE_CAP:case MYSMB_TEXT_VINE_LEAF:
        body=1U;detail=3U;break;
    case MYSMB_TEXT_SPRING:body=1U;detail=2U;break;
    case MYSMB_TEXT_RETAINER:
        /* Committed castle palette: red hair/cap,skin face,white dress.
         * Both source-selected retainers keep their own authored silhouette. */
        body=entry<2U?1U:entry<4U?3U:2U;detail=entry<2U?3U:1U;break;
    case MYSMB_TEXT_FLAG:case MYSMB_TEXT_STAR_FLAG:body=2U;detail=1U;break;
    default:break;
    }
    e->background=mysmb_text_color(frame,game->ppu.palette[0x10U+palette+body]);
    e->foreground=detail!=0U?
        mysmb_text_color(frame,game->ppu.palette[0x10U+palette+detail]):
        mysmb_text_contrast(frame,e->background);
    if(e->foreground==e->background)e->foreground=mysmb_text_contrast(frame,e->background);
}

/* Completed entries retain X even when a row/column's Y is hidden. Unwrap
 * their narrow object around the first nonblank entry, not numeric minimum
 * X (which relocates a 250,2 pair to 2). Regular two-column writers retain
 * source row indices; blank rows are not part of the authored silhouette. */
static void whole_anchor(const struct mysmb_text_observation *item,
    unsigned short begin,unsigned short end,struct mysmb_text_element *element)
{
    unsigned short j,first;
    short reference,x,y,delta;
    int regular;
    first=end;element->x=256;element->y=240;
    for(j=begin;j<end;++j)
        if(item->entries[j*4U+1U]!=0xfcU) {first=j;break;}
    if(first==end)return;
    reference=item->entries[first*4U+3U];
    regular=item->family==MYSMB_TEXT_OBSERVE_PLAYER ||
        item->family==MYSMB_TEXT_OBSERVE_ENEMY ||
        item->family==MYSMB_TEXT_OBSERVE_POWERUP ||
        item->family==MYSMB_TEXT_OBSERVE_BLOCK;
    for(j=begin;j<end;++j) {
        if(item->entries[j*4U+1U]==0xfcU)continue;
        delta=(short)((short)item->entries[j*4U+3U]-reference);
        if(delta>127)delta-=256;
        if(delta< -128)delta+=256;
        x=(short)(reference+delta);
        if(x<element->x)element->x=x;
        if(item->entries[j*4U]>=239U)continue;
        y=(short)(item->entries[j*4U]+1U);
        if(regular)y=(short)(y-(short)((j/2U-first/2U)*8U));
        if(y<element->y)element->y=y;
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
    struct mysmb_text_observation selected;
    struct actor_clip clip;
    unsigned short priority,i,palette,entry,begin,end,j,bottom,right;
    unsigned char colors[3];
    short anchor_x;
    unsigned char mask,seen[64];
    if(game==0 || workspace==0 || frame==0 || receipt==0 || game->text_observer.enabled!=1U ||
        game->text_observer.visible.count>MYSMB_TEXT_OBSERVATION_CAPACITY)return 0;
    receipt->drawn=receipt->unsupported=receipt->unowned_sprites=0U;
    for(i=0U;i<500U;++i)workspace->claimed[i]=0U;
    for(i=0U;i<64U;++i)seen[i]=0U;
    if((game->ppu.visible_ppu_mask&0x10U)==0U)return 1;
    for(i=0U;i<64U;++i)
        if(game->ppu.visible_oam[i*4U]<239U && game->ppu.visible_oam[i*4U+1U]!=0xfcU &&
            game->text_observer.visible.owners[i]==0U)receipt->unowned_sprites++;
    for(priority=0U;priority<64U;++priority) {
        i=game->text_observer.visible.owners[priority];
        if(i==0U || i>game->text_observer.visible.count)continue;
        --i;
            item=&game->text_observer.visible.items[i];
            mask=mysmb_text_observer_visible_mask(game,(unsigned char)i);
            entry=(unsigned short)(priority-item->oam/4U);
            if(entry>=item->sprites || (mask&(1U<<entry))==0U)continue;
            mask=(unsigned char)(1U<<entry);element.x=256;element.y=240;
            begin=0U;end=item->sprites;
            if(item->family==MYSMB_TEXT_OBSERVE_FLAG) {
                begin=entry>=3U?3U:0U;end=entry>=3U?item->sprites:3U;
            }
            whole_anchor(item,begin,end,&element);
            /* Two horizontal score entries and vertical coin entries share
             * one whole template. Align its top row to a source cell center,
             * retaining the whole anchor after a partial overwrite. */
            if(item->family==MYSMB_TEXT_OBSERVE_COIN ||
                item->family==MYSMB_TEXT_OBSERVE_SCORE ||
                item->family==MYSMB_TEXT_OBSERVE_STAR_FLAG) {
                if(element.x>=0 && element.x<256)
                    element.x=component_anchor((unsigned short)element.x,80U,256U);
                if(element.y>=0 && element.y<240)
                    element.y=component_anchor((unsigned short)element.y,(unsigned short)MYSMB_IO_TEXT_FRAME_ROWS(frame),240U);
            }
            selected=*item;
            if(item->family==MYSMB_TEXT_OBSERVE_PLAYER && entry>=6U &&
                (item->identity&MYSMB_TEXT_PLAYER_MIXED_FLAG)!=0U) {
                selected.graphics=item->slot;
                selected.identity&=(unsigned char)~MYSMB_TEXT_PLAYER_THROW_FLAG;
            }
            if(!choose(game,&selected,&element)) {
                if(seen[i]==0U)receipt->unsupported++;
                seen[i]=1U;continue;
            }
            /* Keep the retainer's crown on a cell center inside its first
             * committed sprite row,including fractional vertical anchors. */
            if(element.kind==MYSMB_TEXT_RETAINER && element.y>=0 && element.y<240)
                element.y=component_anchor((unsigned short)element.y,(unsigned short)MYSMB_IO_TEXT_FRAME_ROWS(frame),240U);
            if(item->family==MYSMB_TEXT_OBSERVE_PLAYER &&
                (item->identity&MYSMB_TEXT_PLAYER_KICK_FLAG)!=0U &&
                entry==6U+((item->facing&1U)==0U?1U:0U))
                element.pose=element.pose==MYSMB_TEXT_SWIM_SECOND?MYSMB_TEXT_SWIM_KICK_SECOND:
                    element.pose==MYSMB_TEXT_SWIM_THIRD?MYSMB_TEXT_SWIM_KICK_THIRD:MYSMB_TEXT_SWIM_KICK;
            if(item->family==MYSMB_TEXT_OBSERVE_FLAG && entry>=3U) {
                if(item->graphics>=5U) {seen[i]=1U;receipt->unsupported++;continue;}
                element.kind=MYSMB_TEXT_FLAG_SCORE;element.pose=item->graphics;
                if(element.x>=0 && element.x<256)
                    element.x=component_anchor((unsigned short)element.x,80U,256U);
                if(element.y>=0 && element.y<240)
                    element.y=component_anchor((unsigned short)element.y,(unsigned short)MYSMB_IO_TEXT_FRAME_ROWS(frame),240U);
            }
            if(item->family==MYSMB_TEXT_OBSERVE_VINE) {
                element.kind=item->entries[entry*4U+1U]==0xe0U?
                    MYSMB_TEXT_VINE_CAP:MYSMB_TEXT_VINE_LEAF;
                element.face_left=(item->entries[entry*4U+2U]&0x40U)!=0U?1U:0U;
            }
            if(item->family==MYSMB_TEXT_OBSERVE_PLATFORM)
                element.kind=MYSMB_TEXT_PLATFORM_PART;
            if(item->family==MYSMB_TEXT_OBSERVE_CHUNKS ||
                item->family==MYSMB_TEXT_OBSERVE_FIREBAR ||
                item->family==MYSMB_TEXT_OBSERVE_FIREBALL ||
                item->family==MYSMB_TEXT_OBSERVE_BUBBLE ||
                item->family==MYSMB_TEXT_OBSERVE_VINE ||
                item->family==MYSMB_TEXT_OBSERVE_PLATFORM) {
                element.x=component_anchor(game->ppu.visible_oam[priority*4U+3U],80U,256U);
                element.y=component_anchor((unsigned short)(game->ppu.visible_oam[priority*4U]+1U),(unsigned short)MYSMB_IO_TEXT_FRAME_ROWS(frame),240U);
            }
            palette=(unsigned short)((game->ppu.visible_oam[priority*4U+2U]&3U)*4U);
            actor_colors(game,frame,entry,palette,&element);
            element.face_left=item->family==MYSMB_TEXT_OBSERVE_VINE?
                (item->entries[entry*4U+2U]&0x40U)!=0U?1U:0U:
                (item->facing&2U)!=0U?1U:0U;
            clip.game=game;clip.item=item;clip.mask=mask;
            clip.rows=(unsigned short)MYSMB_IO_TEXT_FRAME_ROWS(frame);
            clip.element=&element;clip.source_width=8U;clip.source_height=8U;
            mysmb_text_compact_size(&element,&clip.columns,&clip.height);
            if(item->family==MYSMB_TEXT_OBSERVE_PLAYER || item->family==MYSMB_TEXT_OBSERVE_ENEMY ||
                item->family==MYSMB_TEXT_OBSERVE_POWERUP || item->family==MYSMB_TEXT_OBSERVE_BLOCK ||
                item->family==MYSMB_TEXT_OBSERVE_SCORE || item->family==MYSMB_TEXT_OBSERVE_COIN ||
                item->family==MYSMB_TEXT_OBSERVE_FLAG || item->family==MYSMB_TEXT_OBSERVE_EXPLOSION ||
                item->family==MYSMB_TEXT_OBSERVE_HAMMER) {
                bottom=(unsigned short)element.y;right=(unsigned short)element.x;
                for(j=begin;j<end;++j) {
                    if(item->entries[j*4U+1U]==0xfcU || item->entries[j*4U]>=239U)continue;
                    if(item->entries[j*4U]+9U>bottom)bottom=(unsigned short)(item->entries[j*4U]+9U);
                    if(item->entries[j*4U+3U]+8U>right)right=(unsigned short)(item->entries[j*4U+3U]+8U);
                }
                if(bottom>element.y)clip.source_height=(unsigned short)(bottom-element.y);
                if(right>element.x && right-element.x<=32)clip.source_width=(unsigned short)(right-element.x);
                if(item->family==MYSMB_TEXT_OBSERVE_PLAYER || item->family==MYSMB_TEXT_OBSERVE_ENEMY ||
                    item->family==MYSMB_TEXT_OBSERVE_POWERUP || item->family==MYSMB_TEXT_OBSERVE_BLOCK)
                    clip.source_width=16U;
            }
            for(j=0U;j<3U;++j)colors[j]=mysmb_text_color(frame,game->ppu.palette[0x11U+palette+j]);
            clip.workspace=workspace;clip.background=background_opaque;
            clip.behind=(unsigned char)(game->ppu.visible_oam[priority*4U+2U]&0x20U);
            if(item->family==MYSMB_TEXT_OBSERVE_PLATFORM)
                platform_span(&element,item,entry,&clip,frame);
            else {
                if(frame->rows==25U) {
                    if(!mysmb_text_compact_draw(&element,colors,frame,visible_cell,&clip))return 0;
                } else if(!mysmb_text_element_draw(&element,frame,visible_cell,&clip))return 0;
                /* OAM X is byte-wrapped; its completed entries can occupy both
                 * screen edges. Clipping still uses each original entry. */
                anchor_x=element.x;
                if(anchor_x<0 || anchor_x>232) {
                    element.x=(short)(anchor_x+(anchor_x<0?256:-256));
                    if(frame->rows==25U) {
                        if(!mysmb_text_compact_draw(&element,colors,frame,visible_cell,&clip))return 0;
                    } else if(!mysmb_text_element_draw(&element,frame,visible_cell,&clip))return 0;
                }
            }
            if(seen[i]==0U)receipt->drawn++;
            seen[i]=1U;
    }
    return 1;
}
