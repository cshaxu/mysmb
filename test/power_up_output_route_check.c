#include "game/game.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>
static unsigned char rec[14368];static unsigned int failures,calls,current,tail;
static void compare(const mysmb_u8 *actual,const unsigned char *expected,const char *phase)
{
    unsigned int i;for(i=0U;i<2048U;++i){if(i>=0x100U&&i<0x200U&&!(i>=0x109U&&i<=0x139U))continue;
        if(actual[i]!=expected[i]){if(failures<24U)printf("case=%u %s ram=%04x ROM=%02x C=%02x\n",current,phase,i,expected[i],actual[i]);++failures;}}
}
#ifdef MYSMB_POWER_UP_CHILD_CHECK
void __wrap_mysmb_oam_draw_one_sprite_row(struct mysmb_game *g,mysmb_u8 right,mysmb_u8 *x,mysmb_u8 *y)
{
    unsigned int pos;if(calls>=2U){++failures;return;}pos=4112U+calls*4104U;++calls;
    if(rec[pos]!=right||rec[pos+1U]!=*x||rec[pos+2U]!=*y)++failures;
    compare(g->ram,rec+pos+8U,"row-input");memcpy(g->ram,rec+pos+2056U,2048U);
    *x=(mysmb_u8)(*x+2U);*y=(mysmb_u8)(*y+8U);
}
void __wrap_mysmb_oam_sprite_object_offscreen_check(struct mysmb_game *g,mysmb_u8 oam)
{
    ++tail;if(tail!=1U||oam!=g->ram[0x06eaU]||calls!=2U)++failures;
    compare(g->ram,rec+12320U,"tail-input");memcpy(g->ram,rec+2064U,2048U);
}
#endif
int main(int argc,char **argv)
{
    static struct mysmb_game g;unsigned char h[12];FILE *f;
    if(argc!=2)return 64;f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1U,12U,f)!=12U||memcmp(h,"MSPU\1\0\0\0\0\040\0\0",12U)!=0)return 66;
    for(current=0U;current<8192U;++current){
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec)||rec[0]!=current/2048U)return 66;
        memset(&g,0,sizeof(g));memcpy(g.ram,rec+16U,2048U);calls=0U;tail=0U;mysmb_objects_draw_power_up(&g);
#ifdef MYSMB_POWER_UP_CHILD_CHECK
        if(calls!=2U||tail!=1U)++failures;
#endif
        compare(g.ram,rec+2064U,"root-output");
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);printf("checked=8192 compared-bytes=1841 failures=%u\n",failures);return failures!=0U;
}
