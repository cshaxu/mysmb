#include "core/game.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>
static unsigned char rec[28736];
static unsigned int failures,calls,current;
static void compare(const mysmb_u8 *actual,const unsigned char *expected,const char *phase)
{
    unsigned int i;
    for(i=0U;i<2048U;++i){
        if(i>=0x100U&&i<0x200U&&!(i>=0x109U&&i<=0x139U))continue;
        if(actual[i]!=expected[i]){if(failures<24U)printf("case=%u %s ram=%04x ROM=%02x C=%02x\n",current,phase,i,expected[i],actual[i]);++failures;}
    }
}
#ifdef MYSMB_LARGE_PLATFORM_CHILD_CHECK
static mysmb_u8 child(struct mysmb_game *game,unsigned int id,mysmb_u8 a,mysmb_u8 x,mysmb_u8 y,unsigned int use_a,unsigned int use_y)
{
    unsigned int position;
    if(calls>=rec[3]){++failures;return 0U;}
    position=4112U+calls*4104U;++calls;
    if(rec[position]!=id||(use_a&&rec[position+1U]!=a)||rec[position+2U]!=x||(use_y&&rec[position+3U]!=y))++failures;
    compare(game->ram,rec+position+8U,"child-input");
    memcpy(game->ram,rec+position+2056U,2048U);return rec[position+4U];
}
void mysmb_oam_stack_six_sprite_data(struct mysmb_game *g,mysmb_u8 v,mysmb_u8 o){(void)child(g,1U,v,rec[0],o,1U,1U);}
void mysmb_oam_dump_four_sprites(struct mysmb_game *g,mysmb_u8 v,mysmb_u8 o){(void)child(g,2U,v,rec[0],o,1U,1U);}
void mysmb_oam_dump_six_sprites(struct mysmb_game *g,mysmb_u8 v,mysmb_u8 o){(void)child(g,calls+1U,v,rec[0],o,1U,1U);}
mysmb_u8 mysmb_oam_get_x_offscreen_bits(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 p,mysmb_u8 x)
{
    if(p!=g->ram[0x006dU+s]||x!=g->ram[0x0086U+s])++failures;
    return child(g,5U,0U,s,0U,0U,0U);
}
void mysmb_oam_move_six_sprites_offscreen(struct mysmb_game *g,mysmb_u8 o){(void)child(g,6U,0U,rec[0],o,0U,1U);}
void mysmb_oam_dump_two_sprites(struct mysmb_game *g,mysmb_u8 v,mysmb_u8 o){(void)g;(void)v;(void)o;++failures;}
/* Only DrawSmallPlatform uses this dependency in the linked owner unit. */
void mysmb_oam_dump_three_sprites(struct mysmb_game *g,mysmb_u8 v,mysmb_u8 o){(void)g;(void)v;(void)o;++failures;}
#endif
int main(int argc,char **argv)
{
    static struct mysmb_game game;unsigned char h[12];FILE *f;
    if(argc!=2)return 64;f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1U,12U,f)!=12U||memcmp(h,"MSLP\1\0\0\0\0\030\0\0",12U)!=0)return 66;
    for(current=0U;current<6144U;++current){
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec)||rec[0]!=current/1024U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,rec+16U,2048U);calls=0U;
        mysmb_objects_draw_large_platform(&game,rec[0]);
#ifdef MYSMB_LARGE_PLATFORM_CHILD_CHECK
        if(calls!=rec[3])++failures;
#endif
        compare(game.ram,rec+2064U,"root-output");
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);
    printf("checked=6144 compared-bytes=1841 failures=%u\n",failures);return failures!=0U;
}
