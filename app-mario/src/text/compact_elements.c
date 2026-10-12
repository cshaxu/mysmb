#include "text/compact_elements.h"
#include "text/layout.h"
#include "io/text_glyph.h"

/* Project-authored semantic half-cell art;digits select source palette roles.
 * This bank is independent of the retained50-row templates. */
struct compact_art {const char *cells;unsigned char width,height;};
static const struct compact_art goomba={"03330""33333""02220""11011",5U,2U};
static const struct compact_art flat={"33333""01110",5U,1U};
static const struct compact_art koopa={"00330""00333""01110""11211""03030""33033",5U,3U};
static const struct compact_art winged={"20332""20232""21112""11211""03030""33033",5U,3U};
static const struct compact_art shell={"01110""11211""11111""02220",5U,2U};
static const struct compact_art beetle={"01110""11111""02020""11011",5U,2U};
static const struct compact_art bloober={"02220""22222""02020""20202",5U,2U};
static const struct compact_art fish={"00110""21131""02120""00110",5U,2U};
static const struct compact_art bullet={"01110""12111""11111""01110",5U,2U};
static const struct compact_art plant={"01110""12121""01010""00300""03330""00300",5U,3U};
static const struct compact_art bro={"01130""00333""01110""11213""03030""33033",5U,3U};
static const struct compact_art lakitu={"01330""01323""22222""02220",5U,2U};
static const struct compact_art spiny={"01010""11111""01110""33033",5U,2U};
static const struct compact_art egg={"01010""11111""12221""01110",5U,2U};
static const struct compact_art podoboo={"00100""01110""13131""01110",5U,2U};
static const struct compact_art toad={"01211""21212""03330""03330""02220""02020",5U,3U};
static const struct compact_art princess={"01010""01330""01330""12331""02220""22122",5U,3U};
static const struct compact_art spring={"11111""03030""32023""32023""03030""11111",5U,3U};
static const struct compact_art bowserfront={"01010""11333""11303""12111""03030""33033",5U,3U};
static const struct compact_art bowserrear={"01110""11211""11211""11113""03030""33033",5U,3U};
static const struct compact_art fireball={"010""131",3U,1U};
static const struct compact_art explosion={"01010""10301""01301""01010",5U,2U};
static const struct compact_art hammer={"111""030""030""030",3U,2U};
static const struct compact_art flame={"011111100""113311111",9U,1U};
static const struct compact_art vine={"00100""01100""00110""00100""01100""00110""00100""01100""00110""00100",5U,5U};
static const struct compact_art platform={"33333333""22222222",8U,1U};
static const struct compact_art brick={"33333""33333""33333""33333",5U,2U};
static const struct compact_art chunk={"03030""30003",5U,1U};
static const struct compact_art firebar={"121212121212""111111111111",12U,1U};
static const struct compact_art player_5={"01110""01111""03323""03322""03130""21112""01010""33033",5U,4U};
static const struct compact_art player_6={"01110""01111""03322""02322""03113""01103""01000""33000",5U,4U};
static const struct compact_art player_7={"01102""01112""03322""03221""03113""01103""01000""33000",5U,4U};
static const struct compact_art small={"01122""03122""11221""33033",5U,2U};
static const struct compact_art mushroom={"03330""31313""13331""02220",5U,2U};
static const struct compact_art flower={"02220""23132""01110""00100",5U,2U};
static const struct compact_art star={"00300""33333""03330""30003",5U,2U};
static const struct compact_art coin={"23""32",2U,1U};
static const struct compact_art score={"111""111",3U,1U};
static const struct compact_art flag={"22220""22200""22000""20000",5U,2U};
static const struct compact_art spring_middle={"11111""32023""32023""11111",5U,2U};
static const struct compact_art spring_flat={"11111""32323",5U,1U};
static const struct compact_art vine_cap={"010""110",3U,1U};
static const struct compact_art vine_leaf={"011""010",3U,1U};
static const struct compact_art bubble={"2""2",1U,1U};
static const struct compact_art empty={"33333""33333""33333""33333",5U,2U};
static const struct compact_art pipe={"1111111111""1111111111""0111111110""0111111110",10U,2U};
static const struct compact_art platform_part={"333""222",3U,1U};
static const struct compact_art player_crouch={"01110""03222""11221""33033",5U,2U};
static const struct compact_art player_climb={"01130""03230""11330""33030""01330""03030""01330""03030",5U,4U};
static const struct compact_art player_swim={"01110""03222""11123""03330""03033""33000",5U,3U};
static const struct compact_art player_skid={"01110""03222""03130""31110""03130""03330""33000""00330",5U,4U};
static const struct compact_art player_dead={"00100""03230""11111""03030",5U,2U};
static const struct compact_art player_throw={"01112""03222""11332""03130""03030""33033""03030""33033",5U,4U};
static const struct compact_art small_run={"01122""03122""11221""33003",5U,2U};
static const struct compact_art small_run_second={"01122""03122""21121""30330",5U,2U};
static const struct compact_art small_run_third={"01122""03122""12112""03303",5U,2U};
static const struct compact_art large_run_second={"01110""01111""03322""22320""33010""33011""00010""00033",5U,4U};
static const struct compact_art large_run_third={"01110""01111""03322""02322""03130""21112""01010""03330",5U,4U};
static const struct compact_art small_jump={"01122""03122""11223""30303",5U,2U};
static const struct compact_art small_swim={"01122""03122""11123""33003",5U,2U};
static const struct compact_art small_climb={"01130""03230""11330""33030",5U,2U};
static const struct compact_art small_skid={"01110""03222""31110""03330",5U,2U};
static const struct compact_art coin_edge={"3""3",1U,1U};
static const struct compact_art burst_small={"010""131",3U,1U};
static const struct compact_art burst_middle={"00100""01310""00100""00000",5U,2U};
static const struct compact_art hammer_horizontal={"11133""11133",5U,1U};
static const struct compact_art hammer_horizontal_reverse={"33111""33111",5U,1U};
static const struct compact_art hammer_vertical_reverse={"030""030""030""111",3U,2U};

static const char *const words[11]={"100","200","400","500","800","1000",
    "2000","4000","5000","8000","1UP"};
static const char *const flag_words[5]={"5000","2000","800","400","100"};
static const struct compact_art *choose_art(const struct mysmb_text_element *e)
{
    switch(e->kind) {
    case MYSMB_TEXT_PLAYER_SMALL:case MYSMB_TEXT_LUIGI_SMALL:
        if(e->pose==MYSMB_TEXT_DEAD)return &player_dead;
        if(e->pose==MYSMB_TEXT_JUMP || e->pose==MYSMB_TEXT_THROW)return &small_jump;
        if(e->pose==MYSMB_TEXT_SKID)return &small_skid;
        if(e->pose==MYSMB_TEXT_CLIMB || e->pose==MYSMB_TEXT_CLIMB_SECOND)return &small_climb;
        if(e->pose==MYSMB_TEXT_SWIM || e->pose>=MYSMB_TEXT_SWIM_SECOND)return &small_swim;
        if(e->pose==MYSMB_TEXT_RUN)return &small_run;
        if(e->pose==MYSMB_TEXT_RUN_SECOND)return &small_run_second;
        if(e->pose==MYSMB_TEXT_RUN_THIRD)return &small_run_third;
        return &small;
    case MYSMB_TEXT_PLAYER_LARGE:case MYSMB_TEXT_LUIGI_LARGE:
        if(e->pose==MYSMB_TEXT_DEAD)return &player_dead;
        if(e->pose==MYSMB_TEXT_CROUCH)return &player_crouch;
        if(e->pose==MYSMB_TEXT_THROW)return &player_throw;
        if(e->pose==MYSMB_TEXT_SKID)return &player_skid;
        if(e->pose==MYSMB_TEXT_CLIMB || e->pose==MYSMB_TEXT_CLIMB_SECOND)return &player_climb;
        if(e->pose==MYSMB_TEXT_SWIM || e->pose>=MYSMB_TEXT_SWIM_SECOND)
            return &player_swim;
        if(e->pose==MYSMB_TEXT_JUMP)return &player_7;
        if(e->pose==MYSMB_TEXT_RUN)return &player_6;
        if(e->pose==MYSMB_TEXT_RUN_SECOND)return &large_run_second;
        if(e->pose==MYSMB_TEXT_RUN_THIRD)return &large_run_third;
        return &player_5;
    case MYSMB_TEXT_GOOMBA:return &goomba;
    case MYSMB_TEXT_GOOMBA_FLAT:return &flat;
    case MYSMB_TEXT_MUSHROOM:return &mushroom;
    case MYSMB_TEXT_BRICK:return &brick;
    case MYSMB_TEXT_EMPTY_BLOCK:return &empty;
    case MYSMB_TEXT_COIN:case MYSMB_TEXT_JUMP_COIN:return (e->pose&1U)!=0U?&coin_edge:&coin;
    case MYSMB_TEXT_PIPE:return &pipe;
    case MYSMB_TEXT_FLOWER:return &flower;
    case MYSMB_TEXT_STAR:return &star;
    case MYSMB_TEXT_FIREBALL:return &fireball;
    case MYSMB_TEXT_EXPLOSION:return e->pose==0U?&burst_small:e->pose==1U?&burst_middle:&explosion;
    case MYSMB_TEXT_HAMMER:return e->pose==1U?&hammer_horizontal:e->pose==3U?&hammer_horizontal_reverse:e->pose==2U?&hammer_vertical_reverse:&hammer;
    case MYSMB_TEXT_CHUNK:return &chunk;
    case MYSMB_TEXT_VINE:return &vine;
    case MYSMB_TEXT_VINE_CAP:return &vine_cap;
    case MYSMB_TEXT_VINE_LEAF:return &vine_leaf;
    case MYSMB_TEXT_PLATFORM:return &platform;
    case MYSMB_TEXT_PLATFORM_PART:return &platform_part;
    case MYSMB_TEXT_FLAG:case MYSMB_TEXT_STAR_FLAG:return &flag;
    case MYSMB_TEXT_BUBBLE:return &bubble;
    case MYSMB_TEXT_SHELL:return &shell;
    case MYSMB_TEXT_KOOPA:return &koopa;
    case MYSMB_TEXT_WINGED_KOOPA:return &winged;
    case MYSMB_TEXT_BEETLE:return &beetle;
    case MYSMB_TEXT_BLOOBER:return &bloober;
    case MYSMB_TEXT_BULLET:return &bullet;
    case MYSMB_TEXT_FISH:return &fish;
    case MYSMB_TEXT_PODOBOO:return &podoboo;
    case MYSMB_TEXT_PIRANHA:return &plant;
    case MYSMB_TEXT_HAMMER_BRO:return &bro;
    case MYSMB_TEXT_SPINY:return &spiny;
    case MYSMB_TEXT_EGG:return &egg;
    case MYSMB_TEXT_LAKITU:return &lakitu;
    case MYSMB_TEXT_BOWSER_FRONT:return &bowserfront;
    case MYSMB_TEXT_BOWSER_REAR:return &bowserrear;
    case MYSMB_TEXT_FLAME:return &flame;
    case MYSMB_TEXT_RETAINER:return e->pose==1U?&princess:&toad;
    case MYSMB_TEXT_SPRING:return e->pose==0U?&spring:e->pose==1U?&spring_middle:&spring_flat;
    default:return &score;
    }
}
static const char *information(const struct mysmb_text_element *e)
{
    if(e->kind==MYSMB_TEXT_SCORE && e->pose<11U)return words[e->pose];
    if(e->kind==MYSMB_TEXT_FLAG_SCORE && e->pose<5U)return flag_words[e->pose];
    return 0;
}
void mysmb_text_compact_size(const struct mysmb_text_element *e,
    unsigned short *width,unsigned short *height)
{
    const struct compact_art *a;
    const char *text;
    a=choose_art(e);text=information(e);*width=a->width;*height=a->height;
    if(text!=0){*width=0U;while(text[*width]!='\0')++*width;*height=1U;}
}
static long project(short value,long scale,long extent)
{
    long p;
    p=(long)value*scale;return p<0L?-((-p+extent-1L)/extent):p/extent;
}
int mysmb_text_compact_draw(const struct mysmb_text_element *e,
    const mysmb_io_u8 colors[3],struct mysmb_io_text_frame MYSMB_IO_FAR *f,
    mysmb_text_cell_filter filter,const void MYSMB_IO_FAR *context)
{
    const struct compact_art *a;
    const char *text;
    unsigned short width,height,row,col,sx,sy,index,at;
    unsigned char top,bottom,glyph,fg,bg,player,inverted;
    long x,y,dx,dy;
    if(e==0 || f==0 || e->kind>=MYSMB_TEXT_KIND_COUNT)return 0;
    a=choose_art(e);text=information(e);mysmb_text_compact_size(e,&width,&height);
    player=(unsigned char)(e->kind<=1U || e->kind==43U || e->kind==44U);
    inverted=(unsigned char)(!player && e->pose==2U &&
        (e->kind==MYSMB_TEXT_GOOMBA || (e->kind>=18U && e->kind<=31U) || e->kind==45U));
    x=project(e->x,80L,256L);y=project(e->y,25L,240L);
    for(row=0U;row<height;++row)for(col=0U;col<width;++col) {
        dx=x+col;dy=y+row;if(dx<0L || dx>=80L || dy<0L || dy>=25L)continue;
        at=(unsigned short)(dy*80L+dx);bg=f->cells[at].background;
        if(text!=0) {glyph=(unsigned char)text[col];fg=mysmb_text_contrast(f,bg);}
        else {
            sx=e->face_left!=0U?(unsigned short)(width-1U-col):col;
            sy=inverted?(unsigned short)(height-1U-row):row;
            index=(unsigned short)(sy*2U*width+sx);
            top=(unsigned char)(a->cells[index]-'0');bottom=(unsigned char)(a->cells[index+width]-'0');
            if(e->kind==MYSMB_TEXT_GOOMBA && row+1U==height && e->pose<=1U)
                bottom=(unsigned char)(e->pose==0U?(sx<=1U || sx==4U?1U:0U):(sx==0U || sx>=3U?1U:0U));
            if((e->kind==MYSMB_TEXT_KOOPA || e->kind==MYSMB_TEXT_WINGED_KOOPA) && row+1U==height && e->pose<=1U)
                bottom=(unsigned char)(e->pose==0U?(sx<=1U || sx==4U?3U:0U):(sx==0U || sx>=3U?3U:0U));
            if(inverted){glyph=top;top=bottom;bottom=glyph;}
            if(top==0U && bottom==0U)continue;
            fg=bottom==0U?bg:colors[bottom-1U];
            bg=top==0U?bg:colors[top-1U];glyph=top==bottom?' ':MYSMB_IO_GLYPH_LOWER;
            /* Marks inhabit uniform colored cells;the two-color contract
             * never pretends a third ink can overlay a half-block. */
            if(top==bottom && top!=0U) {
                if(player && row==0U && sx==2U) {glyph=e->kind==43U || e->kind==44U?'L':'M';fg=colors[1U];}
                else if(player && top==2U && sx==3U && (row==1U || (height==2U && row==0U))){glyph='o';fg=colors[2U];}
                else if(player && row==0U && sx==4U && top==2U && (e->pose==MYSMB_TEXT_JUMP || e->pose==MYSMB_TEXT_THROW)){glyph=']';fg=colors[2U];}
                else if(player && row==2U && sx==4U && top==3U && (e->pose==MYSMB_TEXT_JUMP || e->pose==MYSMB_TEXT_RUN || e->pose==MYSMB_TEXT_RUN_SECOND || e->pose==MYSMB_TEXT_RUN_THIRD)){glyph='^';fg=colors[1U];}
                else if(player && row==2U && sx==2U){glyph=':';fg=colors[1U];}
                else if(e->kind==MYSMB_TEXT_GOOMBA && row==0U && (sx==1U || sx==3U)){glyph='o';fg=colors[0U];}
                else if((e->kind==MYSMB_TEXT_KOOPA || e->kind==MYSMB_TEXT_WINGED_KOOPA) && row==0U && sx==3U){glyph='o';fg=colors[0U];}
                else if((e->kind==MYSMB_TEXT_KOOPA || e->kind==MYSMB_TEXT_WINGED_KOOPA || e->kind==MYSMB_TEXT_SHELL) && row>0U && sx==1U){glyph='#';fg=colors[2U];}
                else if(e->kind==MYSMB_TEXT_RETAINER && row==0U && sx==1U){glyph=e->pose==1U?'^':'o';fg=colors[2U];}
                else if(e->kind==MYSMB_TEXT_RETAINER && row==1U && top==3U && sx==3U){glyph='o';fg=colors[0U];}
                else if(e->kind==MYSMB_TEXT_RETAINER && row+1U==height && top==2U && (sx==1U || sx==3U)){glyph=sx==1U?'/':'\\';fg=colors[0U];}
                else if(e->kind==MYSMB_TEXT_LAKITU && row==0U && top==3U && sx==2U){glyph='o';fg=colors[0U];}
                else if(e->kind==MYSMB_TEXT_FISH && row==0U && sx==2U){glyph='o';fg=colors[1U];}
                else if((e->kind==MYSMB_TEXT_SPINY || e->kind==MYSMB_TEXT_EGG) && row==0U && sx==1U){glyph='^';fg=colors[1U];}
                else if(e->kind==MYSMB_TEXT_MUSHROOM && row==0U && sx==2U){glyph='.';fg=colors[0U];}
                else if(e->kind==MYSMB_TEXT_SPRING && row>0U && (sx==1U || sx==3U)){glyph=sx==1U?'/':'\\';fg=colors[2U];}
                else if(e->kind==MYSMB_TEXT_BRICK){glyph=(row&1U)!=0U?'|':'-';fg=colors[0U];}
                if(e->face_left!=0U)glyph=mysmb_io_text_glyph_mirror(glyph);
                if(inverted)glyph=mysmb_io_text_glyph_flip(glyph);
            }
        }
        if(filter!=0 && !filter(context,(mysmb_io_u16)dx,(mysmb_io_u16)dy))continue;
        f->cells[at].character=glyph;f->cells[at].foreground=fg;f->cells[at].background=bg;
    }
    return 1;
}
