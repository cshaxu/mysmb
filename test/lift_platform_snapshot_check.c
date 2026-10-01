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
    if(r[0]!=id || slot!=r[1]) ++failures;
    compare(g->ram,r+2U);memcpy(g->ram,r+2050U,2048U);return r[1];
}
void mysmb_platform_position_player_vertical(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,1U,s); }
void mysmb_platform_position_player_small(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 c)
{ if(c!=g->ram[0x3a2U+s])++failures;(void)child(g,2U,s); }
void mysmb_enemy_x_counter_platform(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 max) { (void)g;(void)s;(void)max;++failures; }
void mysmb_enemy_move_with_x_counters(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++failures; }
void mysmb_enemy_move_drop_platform(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++failures; }
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++failures;return 0U; }
void mysmb_world_move_platform_vertically(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 up) { (void)g;(void)s;(void)up;++failures; }
static int run_case(const char *snapshot_path,const char *calls_path)
{
    static struct mysmb_game g;static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    count=0U;calls=0U;failures=0U;
    f=fopen(calls_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSuC\1",5) || h[5]>16U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count || fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(snapshot_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSuP\1",5) ||
        fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF)return 66;
    fclose(f);
    if(g.ram[0x16U+h[6]]<43U)mysmb_platform_move_large_lift(&g,h[6]);
    else mysmb_platform_move_small(&g,h[6]);
    compare(g.ram,expected);
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
    fclose(f);printf("platform manifest: %u cases, %u failures\n",cases,failed);
    return failed?1:0;
}
