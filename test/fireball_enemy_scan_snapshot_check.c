#include "game/world/world.h"
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
static unsigned char root_slot;
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
    if(r[0]!=id || (id==2U && slot!=r[1])) ++failures;
    compare(g->ram,r+2U);memcpy(g->ram,r+2050U,2048U);return r[1];
}
mysmb_u8 mysmb_world_boxes_collide(const struct mysmb_game *g,mysmb_u16 a,mysmb_u16 b)
{
    if(a!=0x4acU+(mysmb_u8)(g->ram[1U]*4U+4U) ||
       b!=0x4acU+(mysmb_u8)(root_slot*4U+0x1cU)) ++failures;
    return child((struct mysmb_game *)g,1U,0U);
}
void mysmb_world_handle_fireball_enemy_hit(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,2U,s); }
int main(int argc,char **argv)
{
    static struct mysmb_game g;static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    if(argc!=3)return 64;
    f=fopen(argv[2],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSwC\1",5) || h[5]>16U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count || fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(argv[1],"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSwP\1",5) ||
        fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF)return 66;
    fclose(f);root_slot=h[6];mysmb_world_fireball_enemy_collision(&g,h[6]);compare(g.ram,expected);
    if(calls!=count)++failures;
    return failures?1:0;
}
