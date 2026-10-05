#include "core/enemy/platform.h"
#include "core/world/world.h"
#include "core/player.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>
static unsigned char records[16][4098];
static unsigned int count,calls,failures;
static void compare(const unsigned char *a,const unsigned char *z)
{
    unsigned int i;
    for(i=0U;i<2048U;++i) {
        if(i>=0x100U&&i<0x200U&&(i<0x109U||i>0x139U))continue;
        if(a[i]!=z[i]) {
            printf("%04x original=%02x native=%02x\n",i,(unsigned int)z[i],(unsigned int)a[i]);
            ++failures;
        }
    }
}
static mysmb_u8 child(struct mysmb_game *g,unsigned int id,mysmb_u8 arg,mysmb_u8 *mask)
{
    unsigned char *r;
    if(calls>=count){++failures;return 0U;}
    r=records[calls++];
    if((r[0]&15U)!=id)++failures;
    if(id!=1U && arg!=r[1])++failures;
    compare(g->ram,r+2U);
    memcpy(g->ram,r+2050U,2048U);
    if(id==2U){*mask=(mysmb_u8)(r[0]>>4U);return (mysmb_u8)(r[1]*4U+4U);}
    return id==3U?(mysmb_u8)((r[0]>>7U)&1U):r[1];
}
mysmb_u8 mysmb_world_player_vertical_carry(struct mysmb_game *g)
{ return child(g,1U,0U,0); }
mysmb_u8 mysmb_world_enemy_box_offset_arg(struct mysmb_game *g,mysmb_u8 slot,mysmb_u8 *mask)
{ return child(g,2U,slot,mask); }
mysmb_u8 mysmb_world_boxes_collide(struct mysmb_game *g,mysmb_u16 first,mysmb_u16 second)
{
    if(first!=0x4acU || second<0x4acU || second>0x5abU)++failures;
    return child((struct mysmb_game *)g,3U,(mysmb_u8)(second-0x4acU),0);
}
void mysmb_player_impede_move(struct mysmb_game *g,mysmb_u8 side)
{ (void)child(g,4U,side,0); }
int main(int argc,char **argv)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    if(argc!=3)return 64;
    f=fopen(argv[2],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8||memcmp(h,"MS@C\1",5)||h[5]>16U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count||fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8||memcmp(h,"MS@P\1",5)||
        fread(g.ram,1,2048,f)!=2048||fread(expected,1,2048,f)!=2048||fgetc(f)!=EOF)return 66;
    fclose(f);g.area_prg=mysmb_local_prg;g.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    if(h[5]==1U)mysmb_platform_collision_large(&g,h[6]);
    else mysmb_platform_collision_small(&g,h[6]);
    compare(g.ram,expected);if(calls!=count)++failures;
    return failures?1:0;
}
