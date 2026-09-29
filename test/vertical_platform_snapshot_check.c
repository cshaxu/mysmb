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
void mysmb_platform_legacy_position_small(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 c,mysmb_u8 old_y)
{ (void)g;(void)s;(void)c;(void)old_y;++failures; }
void mysmb_enemy_x_counter_platform(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 m)
{ (void)g;(void)s;(void)m;++failures; }
void mysmb_enemy_move_with_x_counters(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures; }
void mysmb_enemy_move_drop_platform(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures; }
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures;return 0U; }
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
    if(r[0]!=id || slot!=r[1]) ++failures;
    compare(g->ram,r+2U);memcpy(g->ram,r+2050U,2048U);return r[1];
}
void mysmb_world_move_platform_vertically(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 up) { (void)child(g,up?2U:3U,s); }
void mysmb_platform_position_player_vertical(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,5U,s); }
int main(int argc,char **argv)
{
    static struct mysmb_game g;static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    if(argc!=3)return 64;
    f=fopen(argv[2],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSsC\1",5) || h[5]>16U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count || fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSsP\1",5) ||
        fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF)return 66;
    fclose(f);mysmb_platform_move_y(&g,h[6]);compare(g.ram,expected);
    if(calls!=count)++failures;
    return failures?1:0;
}
