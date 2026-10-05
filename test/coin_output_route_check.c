#include "core/game.h"
#include "core/objects.h"
#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>
static unsigned char rec[8216];static unsigned int failures,calls,current;
static void compare(const mysmb_u8 *actual,const unsigned char *expected,const char *phase)
{
    unsigned int i;for(i=0U;i<2048U;++i){
        if(i>=0x100U&&i<0x200U&&!(i>=0x109U&&i<=0x139U))continue;
        if(actual[i]!=expected[i]){if(failures<24U)printf("case=%u %s ram=%04x ROM=%02x C=%02x\n",current,phase,i,expected[i],actual[i]);++failures;}
    }
}
#ifdef MYSMB_COIN_CHILD_CHECK
void __wrap_mysmb_oam_dump_two_sprites(struct mysmb_game *g,mysmb_u8 value,mysmb_u8 oam)
{
    mysmb_u8 source_x;
    ++calls;if(calls!=1U){++failures;return;}
    source_x=rec[1]>=2U?rec[0]:(mysmb_u8)((g->ram[9U]>>1U)&3U);
    if(rec[4112U]!=value||rec[4113U]!=source_x||rec[4114U]!=oam)++failures;
    compare(g->ram,rec+4120U,"child-input");memcpy(g->ram,rec+6168U,2048U);
}
#endif
int main(int argc,char **argv)
{
    static struct mysmb_game g;unsigned char h[12];FILE *f;
    if(argc!=2)return 64;f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1U,12U,f)!=12U||memcmp(h,"MSCO\1\0\0\0\0\044\0\0",12U)!=0)return 66;
    for(current=0U;current<9216U;++current){
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec)||rec[0]!=current/1024U)return 66;
        memset(&g,0,sizeof(g));memcpy(g.ram,rec+16U,2048U);calls=0U;
        mysmb_objects_draw_jump_coin(&g,rec[0]);
#ifdef MYSMB_COIN_CHILD_CHECK
        if(calls!=1U)++failures;
#endif
        compare(g.ram,rec+2064U,"root-output");
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);printf("checked=9216 compared-bytes=1841 failures=%u\n",failures);return failures!=0U;
}
