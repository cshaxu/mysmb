#include "game/enemy/firebar.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;return 0U; }
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s; }
int main(int argc,char **argv)
{
    static struct mysmb_game g;
    static unsigned char record[4098];
    unsigned char header[8];FILE *f;unsigned int n,i,count,failures;
    mysmb_u8 slot,result;
    if(argc!=2)return 64;
    f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(header,1U,8U,f)!=8U || memcmp(header,"MShC\1",5U))return 66;
    count=failures=0U;
    for(n=0U;n<header[5];++n) {
        if(fread(record,1U,4098U,f)!=4098U)return 66;
        if(record[0]!=2U)continue;
        ++count;memcpy(g.ram,record+2U,2048U);slot=g.ram[8U];
        result=mysmb_firebar_spin(&g,slot,g.ram[0x388U+slot]);
        if(result!=record[1])++failures;
        for(i=0U;i<2048U;++i) {
            if(i>=0x100U && i<0x200U && (i<0x109U || i>0x139U))continue;
            if(g.ram[i]!=record[2050U+i])++failures;
        }
    }
    if(fgetc(f)!=EOF)return 66;
    fclose(f);printf("%u %u\n",count,failures);return failures?1:0;
}
