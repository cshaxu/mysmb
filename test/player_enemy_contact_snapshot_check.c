#include "game/objects.h"
#include "game/area.h"
#include "game/world/world.h"
#include "game/enemy/distance.h"
#include "game/enemy/init_targets.h"
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
static mysmb_u8 child(struct mysmb_game *g,unsigned int id,mysmb_u8 argument)
{
    unsigned char *r;
    mysmb_u8 result;
    if(calls>=count){++failures;return 0U;}
    r=records[calls++];
    if((r[0]&0x7fU)!=id)++failures;
    if(id==3U || id==4U || id==5U || id==7U || id==8U || id==10U)
        if(argument!=r[1])++failures;
    if(id==9U && argument!=5U)++failures;
    compare(g->ram,r+2U);
    memcpy(g->ram,r+2050U,2048U);
    result=id==3U?(mysmb_u8)((r[0]>>7U)&1U):r[1];
    return result;
}
mysmb_u8 mysmb_world_player_vertical_carry(struct mysmb_game *g)
{ return child(g,1U,0U); }
mysmb_u8 mysmb_world_enemy_box_offset(struct mysmb_game *g)
{ return child(g,2U,0U); }
mysmb_u8 mysmb_world_boxes_collide(const struct mysmb_game *g,mysmb_u16 first,mysmb_u16 second)
{
    if(first!=0x4acU || second<0x4acU || second>0x5abU)++failures;
    return child((struct mysmb_game *)g,3U,(mysmb_u8)(second-0x4acU));
}
void mysmb_objects_collect_power_up(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,4U,s); }
void mysmb_world_shell_or_block_defeat(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,5U,s); }
mysmb_u8 mysmb_area_queue_player_palette(struct mysmb_game *g)
{ (void)child(g,6U,0U);return 1U; }
void mysmb_world_set_stun(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,7U,s); }
void mysmb_enemy_init_vertical_state(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,8U,s); }
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *g,mysmb_u8 s)
{ return child(g,9U,s); }
void mysmb_objects_turn_enemy(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,10U,s); }
int main(int argc,char **argv)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    if(argc!=3)return 64;
    f=fopen(argv[2],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8||memcmp(h,"MS~C\1",5)||h[5]>16U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count||fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8||memcmp(h,"MS~P\1",5)||
        fread(g.ram,1,2048,f)!=2048||fread(expected,1,2048,f)!=2048||fgetc(f)!=EOF)return 66;
    fclose(f);g.area_prg=mysmb_local_prg;g.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    mysmb_objects_player_enemy_current(&g,h[6],1U);compare(g.ram,expected);
    if(calls!=count)++failures;
    return failures?1:0;
}
