/* Full helper output and independently intercepted child contracts. */
#include <stdio.h>
#include <string.h>
#include "game/oam/oam.h"
#include "game/objects.h"
#include "game/fireball/fireball.h"
#include "game/area.h"
static struct mysmb_game game;
static unsigned char record[28736],local_prg[32768];
static unsigned int current,mode,calls,failures;
static void compare(const mysmb_u8 *actual,const unsigned char *expected,const char *phase)
{
    unsigned int i;
    for(i=0U;i<2048U;++i){
        if(i>=0x100U&&i<0x200U&&(i<0x109U||i>0x139U))continue;
        if(actual[i]!=expected[i]){
            if(failures<12U)printf("mode=%u root=%u %s RAM=%04x ROM=%02x C=%02x\n",mode,current,phase,i,expected[i],actual[i]);
            ++failures;
        }
    }
}
#ifdef MYSMB_OAM_HELPER_CHILD_CHECK
static unsigned int consume(struct mysmb_game *g,unsigned int kind,mysmb_u8 a,mysmb_u8 x,mysmb_u8 y,unsigned int mask)
{
    unsigned int pos;
    if(calls>=record[3]){++failures;return 4112U;}
    pos=4112U+calls*4104U;++calls;
    if(kind!=record[pos]||((mask&1U)&&a!=record[pos+1U])||
       ((mask&2U)&&x!=record[pos+2U])||((mask&4U)&&y!=record[pos+3U])){
        if(failures<12U)printf("mode=%u root=%u child=%u ROM-kind=%u input mismatch\n",mode,current,kind,record[pos]);
        ++failures;
    }
    compare(g->ram,record+pos+8U,"child-input");
    memcpy(g->ram,record+pos+2056U,2048U);
    return pos;
}
void __real_mysmb_oam_move_enemy_column_offscreen(struct mysmb_game *,mysmb_u8,mysmb_u8);
void __wrap_mysmb_oam_move_enemy_column_offscreen(struct mysmb_game *g,mysmb_u8 x,mysmb_u8 a)
{
    if(mode!=0U){__real_mysmb_oam_move_enemy_column_offscreen(g,x,a);return;}
    (void)consume(g,1U,a,x,0U,3U);
}
void __real_mysmb_oam_move_enemy_row_offscreen(struct mysmb_game *,mysmb_u8,mysmb_u8);
void __wrap_mysmb_oam_move_enemy_row_offscreen(struct mysmb_game *g,mysmb_u8 x,mysmb_u8 a)
{
    if(mode!=0U){__real_mysmb_oam_move_enemy_row_offscreen(g,x,a);return;}
    (void)consume(g,2U,a,x,0U,3U);
}
void __real_mysmb_objects_erase_enemy(struct mysmb_game *,mysmb_u8);
void __wrap_mysmb_objects_erase_enemy(struct mysmb_game *g,mysmb_u8 x)
{
    if(mode!=0U){__real_mysmb_objects_erase_enemy(g,x);return;}
    (void)consume(g,3U,0U,x,0U,2U);
}
mysmb_u8 __real_mysmb_oam_move_column_offscreen(struct mysmb_game *,mysmb_u8);
mysmb_u8 __wrap_mysmb_oam_move_column_offscreen(struct mysmb_game *g,mysmb_u8 y)
{
    if(mode!=1U&&mode!=8U)return __real_mysmb_oam_move_column_offscreen(g,y);
    (void)consume(g,4U,0U,0U,y,4U);return 0xf8U;
}
void __real_mysmb_oam_dump_two_sprites(struct mysmb_game *,mysmb_u8,mysmb_u8);
void __wrap_mysmb_oam_dump_two_sprites(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 y)
{
    if(mode!=2U&&mode!=7U&&mode!=9U&&mode!=19U){__real_mysmb_oam_dump_two_sprites(g,a,y);return;}
    (void)consume(g,5U,a,0U,y,5U);
}
void __real_mysmb_oam_draw_one_sprite_row(struct mysmb_game *,mysmb_u8,mysmb_u8 *,mysmb_u8 *);
void __wrap_mysmb_oam_draw_one_sprite_row(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 *x,mysmb_u8 *y)
{
    unsigned int pos;
    if(mode!=3U&&mode!=6U&&mode!=16U&&mode!=17U){__real_mysmb_oam_draw_one_sprite_row(g,a,x,y);return;}
    pos=consume(g,6U,a,*x,*y,7U);*x=record[pos+4U];*y=record[pos+5U];
}
void __real_mysmb_oam_draw_sprite_object(struct mysmb_game *,mysmb_u8 *,mysmb_u8 *);
void __wrap_mysmb_oam_draw_sprite_object(struct mysmb_game *g,mysmb_u8 *x,mysmb_u8 *y)
{
    unsigned int pos;
    if(mode!=4U){__real_mysmb_oam_draw_sprite_object(g,x,y);return;}
    pos=consume(g,7U,0U,*x,*y,6U);*x=record[pos+4U];*y=record[pos+5U];
}
void __real_mysmb_oam_dump_six_sprites(struct mysmb_game *,mysmb_u8,mysmb_u8);
void __wrap_mysmb_oam_dump_six_sprites(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 y)
{
    if(mode!=5U&&mode!=14U){__real_mysmb_oam_dump_six_sprites(g,a,y);return;}
    (void)consume(g,8U,a,0U,y,5U);
}
void __real_mysmb_oam_dump_four_sprites(struct mysmb_game *,mysmb_u8,mysmb_u8);
void __wrap_mysmb_oam_dump_four_sprites(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 y)
{
    if(mode!=6U&&mode!=7U&&mode!=9U&&mode!=13U){__real_mysmb_oam_dump_four_sprites(g,a,y);return;}
    (void)consume(g,9U,a,0U,y,5U);
}
void __real_mysmb_oam_check_block_left_column(struct mysmb_game *,mysmb_u8,mysmb_u8);
void __wrap_mysmb_oam_check_block_left_column(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 y)
{
    if(mode!=6U&&mode!=7U&&mode!=9U){__real_mysmb_oam_check_block_left_column(g,a,y);return;}
    (void)consume(g,10U,a,0U,y,5U);
}
mysmb_u8 __real_mysmb_oam_draw_firebar(struct mysmb_game *,mysmb_u8);
mysmb_u8 __wrap_mysmb_oam_draw_firebar(struct mysmb_game *g,mysmb_u8 y)
{
    unsigned int pos;
    if(mode!=10U)return __real_mysmb_oam_draw_firebar(g,y);
    pos=consume(g,11U,0U,0U,y,4U);return record[pos+5U];
}
void __real_mysmb_oam_draw_fireworks_explosion(struct mysmb_game *,mysmb_u8,mysmb_u8);
void __wrap_mysmb_oam_draw_fireworks_explosion(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 y)
{
    if(mode!=12U){__real_mysmb_oam_draw_fireworks_explosion(g,a,y);return;}
    (void)consume(g,12U,a,0U,y,5U);
}
void __real_mysmb_oam_dump_three_sprites(struct mysmb_game *,mysmb_u8,mysmb_u8);
void __wrap_mysmb_oam_dump_three_sprites(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 y)
{
    if(mode!=14U){__real_mysmb_oam_dump_three_sprites(g,a,y);return;}
    (void)consume(g,13U,a,0U,y,5U);
}
#endif
static unsigned long read32(const unsigned char *p)
{
    return (unsigned long)p[0]|((unsigned long)p[1]<<8U)|((unsigned long)p[2]<<16U)|((unsigned long)p[3]<<24U);
}
int main(int argc,char **argv)
{
    unsigned char h[16];FILE *f;unsigned int count,i;mysmb_u8 x,y;
    if(argc!=2&&argc!=3)return 64;
    f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1U,16U,f)!=16U||memcmp(h,"MSOH\1",5U))return 66;
    mode=h[5];count=(unsigned int)read32(h+8U);current=(unsigned int)read32(h+12U);
    if(mode>38U||count==0U||count>2048U)return 66;
    if(mode>=16U){
        FILE *rom;
        if(argc!=3)return 64;
        rom=fopen(argv[2],"rb");if(!rom)return 65;
        if(fseek(rom,16L,SEEK_SET)||fread(local_prg,1U,sizeof(local_prg),rom)!=sizeof(local_prg))return 66;
        fclose(rom);
    }
    for(i=0U;i<count;++i,++current){
        if(fread(record,1U,sizeof(record),f)!=sizeof(record))return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+16U,2048U);calls=0U;x=record[1];y=record[2];
        if(mode>=16U)mysmb_game_bind_area_source(&game,local_prg,(mysmb_u16)sizeof(local_prg));
        if(mode==0U)mysmb_oam_sprite_object_offscreen_check(&game,record[2]);
        if(mode==1U)mysmb_oam_move_enemy_column_offscreen(&game,x,record[0]);
        if(mode==2U)mysmb_oam_move_enemy_row_offscreen(&game,x,record[0]);
        if(mode==3U)mysmb_oam_draw_enemy_object_row(&game,&y,&x);
        if(mode==4U)mysmb_oam_draw_one_sprite_row(&game,record[0],&x,&y);
        if(mode==5U)(void)mysmb_objects_draw_normal_enemy_graphics(&game,x);
        if(mode==6U)mysmb_objects_draw_bouncing_block(&game,x);
        if(mode==7U||mode==9U)mysmb_objects_draw_brick_chunks(&game,x);
        if(mode==8U)mysmb_oam_check_block_left_column(&game,record[0],y);
        if(mode==10U)mysmb_oam_draw_fireball(&game,x);
        if(mode==11U){y=mysmb_oam_draw_firebar(&game,y);if(y!=record[5])++failures;}
        if(mode==12U)mysmb_oam_draw_fireball_explosion(&game,x);
        if(mode==13U)mysmb_oam_draw_fireworks_explosion(&game,record[0],y);
        if(mode==14U)mysmb_objects_draw_small_platform(&game,x);
        if(mode==15U)mysmb_fireball_draw_bubble(&game,x);
        if(mode==16U||mode==18U||mode==19U||mode==20U)mysmb_oam_render_player(&game);
        if(mode==17U)mysmb_oam_draw_intermediate_player(&game);
        if(mode==21U)mysmb_oam_relative_player_position(&game);
        if(mode==22U)mysmb_oam_relative_bubble_position(&game,x);
        if(mode==23U)mysmb_oam_relative_fireball_position(&game,x);
        if(mode==24U)mysmb_oam_relative_misc_position(&game,x);
        if(mode==25U)mysmb_oam_relative_enemy_position(&game,x);
        if(mode==26U)mysmb_oam_relative_block_position(&game,x);
        if(mode==27U)mysmb_oam_get_player_offscreen_bits(&game);
        if(mode==28U)mysmb_oam_get_fireball_offscreen_bits(&game,x);
        if(mode==29U)mysmb_oam_get_bubble_offscreen_bits(&game,x);
        if(mode==30U)mysmb_oam_get_misc_offscreen_bits(&game,x);
        if(mode==31U)mysmb_oam_get_enemy_offscreen_bits(&game,x);
        if(mode==32U)mysmb_oam_get_block_offscreen_bits(&game,x);
        if(mode==33U||mode==34U){
            mysmb_u8 bits=mysmb_oam_get_x_offscreen_bits(&game,x,
                game.ram[0x6dU+x],game.ram[0x86U+x]);
            if(bits!=record[6]){
                if(failures<12U)printf("mode=%u root=%u returned-mask ROM=%02x C=%02x\n",mode,current,record[6],bits);
                ++failures;
            }
        }
        if(mode==35U||mode==36U)mysmb_oam_get_offscreen_bits_set(&game,x,y);
        if(mode==37U||mode==38U)mysmb_oam_draw_sprite_object(&game,&x,&y);
        if((mode==3U||mode==4U||mode==37U||mode==38U)&&(x!=record[4]||y!=record[5]))++failures;
#ifdef MYSMB_OAM_HELPER_CHILD_CHECK
        if(calls!=record[3])++failures;
#endif
        compare(game.ram,record+2064U,"root-output");
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);
    printf("oam-helper mode=%u roots=%u compared-bytes=1841 failures=%u\n",mode,count,failures);
    return failures?1:0;
}
