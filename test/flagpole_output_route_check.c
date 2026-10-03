#include "game/game.h"
#include "game/oam/oam.h"
#include "game/objects.h"
#include "game/score.h"
#include <stdio.h>
#include <string.h>
static unsigned char record[12312];
static unsigned int failures,child_calls,current_case;
static void compare(const mysmb_u8 *actual,const unsigned char *expected,unsigned int n,const char *phase)
{
    unsigned int a;
    for(a=0U;a<2048U;++a){
        if(a>=0x100U&&a<0x200U&&!(a>=0x109U&&a<=0x139U))continue;
        if(actual[a]!=expected[a]){
            if(failures<24U)printf("case=%u %s ram=%04x ROM=%02x C=%02x\n",n,phase,a,expected[a],actual[a]);++failures;
        }
    }
}
#ifdef MYSMB_FLAGPOLE_CHILD_CHECK
static void child(struct mysmb_game *game,unsigned int id,mysmb_u8 a,mysmb_u8 x,mysmb_u8 y)
{
    unsigned int position;
    if(child_calls>=record[3]){++failures;return;}
    position=4112U+child_calls*4100U;++child_calls;
    if(record[position]!=id||record[position+1U]!=a||record[position+2U]!=x||record[position+3U]!=y)++failures;
    compare(game->ram,record+position+4U,current_case,"child-input");
    memcpy(game->ram,record+position+2052U,2048U);
}
void mysmb_oam_dump_two_sprites(struct mysmb_game *game,mysmb_u8 value,mysmb_u8 oam)
{child(game,1U,value,game->ram[8U],oam);}
void mysmb_oam_draw_one_sprite_row(struct mysmb_game *game,mysmb_u8 right_tile,mysmb_u8 *graphics_index,mysmb_u8 *oam)
{
    child(game,2U,right_tile,*graphics_index,*oam);
    *graphics_index=(mysmb_u8)(*graphics_index+2U);*oam=(mysmb_u8)(*oam+8U);
}
void mysmb_oam_draw_sprite_object(struct mysmb_game *game,mysmb_u8 *graphics_index,mysmb_u8 *oam)
{(void)game;(void)graphics_index;(void)oam;++failures;}
void mysmb_oam_move_six_sprites_offscreen(struct mysmb_game *game,mysmb_u8 oam)
{
    if(oam!=record[1]||(game->ram[0x03d1U]&0x0eU)==0U)++failures;
    /* Full checker independently proves this tail's actual shared C writes. */
    memcpy(game->ram,record+2064U,2048U);
}
mysmb_u8 mysmb_score_add(struct mysmb_game *game){(void)game;++failures;return 0U;}
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *game,mysmb_u8 slot)
{(void)game;(void)slot;++failures;}
void mysmb_oam_relative_enemy_position(struct mysmb_game *game,mysmb_u8 slot)
{(void)game;(void)slot;++failures;}
#endif
int main(int argc,char **argv)
{
    static struct mysmb_game game;unsigned char header[12],dump[4104];unsigned int n;FILE *file;
#ifdef MYSMB_FLAGPOLE_CHILD_CHECK
    if(argc!=2)return 64;
#else
    if(argc!=3)return 64;
#endif
    file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,12U,file)!=12U||memcmp(header,"MSFG\1\0\0\0\0\022\0\0",12U)!=0)return 66;
    for(n=0U;n<4608U;++n){
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||record[0]!=n/768U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+16U,2048U);child_calls=0U;current_case=n;
        mysmb_objects_draw_flagpole_graphics(&game);
#ifdef MYSMB_FLAGPOLE_CHILD_CHECK
        if(child_calls!=record[3]){if(failures<24U)printf("case=%u ROM-calls=%u C-calls=%u\n",n,record[3],child_calls);++failures;}
#endif
        compare(game.ram,record+2064U,n,"root-output");
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("flag-checked=4608 compared-bytes=1841 failures=%u\n",failures);
#ifndef MYSMB_FLAGPOLE_CHILD_CHECK
    file=fopen(argv[2],"rb");if(file==0)return 65;
    if(fread(header,1U,12U,file)!=12U||memcmp(header,"MSDP\1\0\0\0\0\060\0\0",12U)!=0)return 66;
    for(n=0U;n<12288U;++n){
        if(fread(dump,1U,sizeof(dump),file)!=sizeof(dump)||dump[0]!=n/2048U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,dump+8U,2048U);
        switch(dump[0]){
        case 0U:mysmb_oam_move_six_sprites_offscreen(&game,dump[2]);break;
        case 1U:mysmb_oam_dump_six_sprites(&game,dump[1],dump[2]);break;
        case 2U:mysmb_oam_dump_four_sprites(&game,dump[1],dump[2]);break;
        case 3U:mysmb_oam_dump_three_sprites(&game,dump[1],dump[2]);break;
        case 4U:mysmb_oam_dump_two_sprites(&game,dump[1],dump[2]);break;
        case 5U:break; /* Original ExitDumpSpr is a no-write return. */
        }
        compare(game.ram,dump+2056U,n,"dump-output");
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("dump-checked=12288 compared-bytes=1841 total-failures=%u\n",failures);
#endif
    return failures!=0U;
}
