#include "core/game.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>
static unsigned char record[6152];
static unsigned int failures,child_calls;
static void compare(const mysmb_u8 *actual,const unsigned char *expected,unsigned int n,const char *phase)
{
    unsigned int a;
    for(a=0U;a<2048U;++a){
        if(a>=0x100U&&a<0x200U&&!(a>=0x109U&&a<=0x139U))continue;
        if(actual[a]!=expected[a]){
            if(failures<24U)printf("case=%u %s ram=%04x ROM=%02x C=%02x\n",n,phase,a,expected[a],actual[a]);
            ++failures;
        }
    }
}
#ifdef MYSMB_HAMMER_CHILD_CHECK
static unsigned int current_case;
void mysmb_oam_dump_two_sprites(struct mysmb_game *game,mysmb_u8 value,mysmb_u8 oam)
{
    ++child_calls;
    if(record[1]!=1U||child_calls!=1U||value!=record[3]||oam!=record[2])++failures;
    compare(game->ram,record+4104U,current_case,"child-input");
    /* Replay the actual ROM child's RAM effects; full checker tests its C body. */
    memcpy(game->ram,record+2056U,2048U);
}
#endif
int main(int argc,char **argv)
{
    static struct mysmb_game game;unsigned char header[12];unsigned int n;FILE *file;
    if(argc!=2)return 64;
    file=fopen(argv[1],"rb");if(file==0)return 65;
    if(fread(header,1U,12U,file)!=12U||memcmp(header,"MSHG\1\0\0\0\0\066\0\0",12U)!=0)return 66;
    for(n=0U;n<13824U;++n){
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)||record[0]!=n/1536U)return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+8U,2048U);child_calls=0U;
#ifdef MYSMB_HAMMER_CHILD_CHECK
        current_case=n;
#endif
        mysmb_objects_draw_hammer(&game,record[0]);
#ifdef MYSMB_HAMMER_CHILD_CHECK
        if(child_calls!=record[1]){
            if(failures<24U)printf("case=%u ROM-calls=%u C-calls=%u\n",n,record[1],child_calls);
            ++failures;
        }
#endif
        compare(game.ram,record+2056U,n,"root-output");
    }
    if(fgetc(file)!=EOF)return 66;fclose(file);
    printf("checked=13824 compared-bytes=1841 failures=%u\n",failures);return failures!=0U;
}
