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
mysmb_u8 mysmb_world_boxes_collide(struct mysmb_game *g,mysmb_u16 a,mysmb_u16 b)
{
    if(a!=0x4acU+(mysmb_u8)(g->ram[1U]*4U+4U) ||
       b!=0x4acU+(mysmb_u8)(root_slot*4U+0x1cU)) ++failures;
    return child((struct mysmb_game *)g,1U,0U);
}
void mysmb_world_handle_fireball_enemy_hit(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,2U,s); }
static int run_case(const char *snapshot_path,const char *calls_path)
{
    static struct mysmb_game g;static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    count=0U;calls=0U;failures=0U;
    f=fopen(calls_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSwC\1",5) || h[5]>16U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count || fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(snapshot_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSwP\1",5) ||
        fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF)return 66;
    fclose(f);root_slot=h[6];mysmb_world_fireball_enemy_collision(&g,h[6]);compare(g.ram,expected);
    if(calls!=count)++failures;
    return failures?1:0;
}
int main(int argc,char **argv)
{
    FILE *f;char snapshot[1024],child[1024];unsigned int cases,failed;
    if(argc!=3)return 64;
    if(strcmp(argv[1],"--manifest")!=0)return run_case(argv[1],argv[2]);
    f=fopen(argv[2],"rb");if(!f)return 65;
    cases=0U;failed=0U;
    while(fscanf(f,"%1023s %1023s",snapshot,child)==2) {
        ++cases;if(run_case(snapshot,child)!=0)++failed;
    }
    if(ferror(f)) { fclose(f);return 66; }
    fclose(f);printf("fireball scan manifest: %u cases, %u failures\n",cases,failed);
    return failed?1:0;
}
