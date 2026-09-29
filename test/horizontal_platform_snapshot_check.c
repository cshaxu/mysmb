#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/distance.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/init.h"
#include "game/enemy/stream.h"
#include "game/enemy/movement.h"
#include "game/objects.h"
#include "game/enemy/platform.h"
#include <stdio.h>
#include <string.h>
static unsigned char records[16][4098];
static unsigned int count,calls,failures;
static void compare(const unsigned char *a,const unsigned char *z)
{
    unsigned int i;
    for(i=0U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U && (i<0x109U || i>0x139U)) continue;
        if(a[i]!=z[i]) {
            printf("%04x original=%02x native=%02x\n",i,(unsigned int)z[i],(unsigned int)a[i]);
            ++failures;
        }
    }
}
static mysmb_u8 child(struct mysmb_game *g,unsigned int id,mysmb_u8 slot)
{
    unsigned char *r;
    if(calls>=count) { ++failures;return 0U; }
    r=records[calls++];
    if(r[0]!=id || slot!=(id==4U?r[2U+8U]:r[1])) ++failures;
    compare(g->ram,r+2U);memcpy(g->ram,r+2050U,2048U);return r[1];
}
void mysmb_platform_position_player_small(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 c)
{ (void)g;(void)s;(void)c;++failures; }
void mysmb_enemy_x_counter_platform(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 max) { if(max!=14U)++failures;(void)child(g,1U,s); }
void mysmb_enemy_move_with_x_counters(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,2U,s); }
void mysmb_enemy_move_drop_platform(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,3U,s); }
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 s) { return child(g,4U,s); }
void mysmb_platform_position_player_vertical(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,5U,s); }
void mysmb_world_move_platform_vertically(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 up) { (void)g;(void)s;(void)up;++failures; }
int main(int argc,char **argv)
{
    static struct mysmb_game g;static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    if(argc!=3)return 64;
    f=fopen(argv[2],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MStC\1",5) || h[5]>16U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count || fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MStP\1",5) ||
        fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF)return 66;
    fclose(f);if(g.ram[0x16U+h[6]]==40U)mysmb_platform_move_x(&g,h[6]);
    else if(g.ram[0x16U+h[6]]==41U)mysmb_platform_move_drop(&g,h[6]);
    else mysmb_platform_move_right(&g,h[6]);
    compare(g.ram,expected);
    if(calls!=count)++failures;
    return failures?1:0;
}
