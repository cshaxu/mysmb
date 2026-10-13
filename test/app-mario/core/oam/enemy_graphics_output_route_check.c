/* Whole EnemyGfxHandler result, including real game-owned stack aliases. */
#include <stdio.h>
#include <string.h>
#include "core/oam/oam.h"
static struct mysmb_game game;
static unsigned char record[16424];
static unsigned int current, calls, failures;
static void compare(const mysmb_u8 *actual,const unsigned char *expected,
                    const char *phase)
{
    unsigned int i;
    for(i=0U;i<2048U;++i){
        if(i>=0x100U&&i<0x200U&&(i<0x109U||i>0x139U))continue;
        if(actual[i]!=expected[i]){
            if(failures<12U)printf("root=%u %s RAM=%04x ROM=%02x C=%02x\n",
                current,phase,i,expected[i],actual[i]);
            ++failures;
        }
    }
}
#ifdef MYSMB_ENEMY_GFX_CHILD_CHECK
void __wrap_mysmb_oam_draw_one_sprite_row(struct mysmb_game *g,
    mysmb_u8 right,mysmb_u8 *x,mysmb_u8 *y)
{
    unsigned int pos;
    if(calls>=record[3]){++failures;return;}
    pos=4112U+calls*4104U;++calls;
    if(right!=record[pos]||*x!=record[pos+1U]||*y!=record[pos+2U])++failures;
    compare(g->ram,record+pos+8U,"row-input");
    memcpy(g->ram,record+pos+2056U,2048U);
    *x=record[pos+3U];*y=record[pos+4U];
}
#endif
int main(int argc,char **argv)
{
    unsigned char h[12];FILE *f;
    if(argc!=2)return 64;
    f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1U,12U,f)!=12U||memcmp(h,"MSEG\1",5U))return 66;
    for(current=0U;current<8192U;++current){
        if(fread(record,1U,sizeof(record),f)!=sizeof(record))return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+16U,2048U);
        calls=0U;
        (void)mysmb_objects_draw_normal_enemy_graphics(&game,record[0]);
#ifdef MYSMB_ENEMY_GFX_CHILD_CHECK
        if(calls!=record[3])++failures;
#endif
        compare(game.ram,record+2064U,"root-output");
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);
    printf("enemy-graphics roots=%u compared-bytes=1841 failures=%u\n",current,failures);
    return failures?1:0;
}
