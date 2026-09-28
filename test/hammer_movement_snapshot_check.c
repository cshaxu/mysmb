#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include "game/enemy/distance.h"
#include "game/world/world.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Caller-only proof. Compare the entire original child input before using
 * its recorded return. Actual child execution is a separate diagnostic. */
static unsigned char records[16][4098];
static unsigned int count, calls, failures;
static void compare(const unsigned char *a, const unsigned char *z)
{
    unsigned int i;
    for (i=0U;i<2048U;++i) {
        if (i>=0x100U && i<0x200U && (i<0x109U || i>0x139U)) continue;
        if (a[i]!=z[i]) {
            printf("%04x original=%02x native=%02x\n",i,(unsigned int)z[i],(unsigned int)a[i]);
            ++failures;
        }
    }
}
static mysmb_u8 child(struct mysmb_game *game, unsigned int id, mysmb_u8 slot)
{
    unsigned char *r;
    if (calls>=count) { ++failures;return 0U; }
    r=records[calls++];
    if (r[0]!=id || (id>2U && r[1]!=slot)) ++failures;
    compare(game->ram,r+2U);
    memcpy(game->ram,r+2050U,2048U);
    return r[1];
}
mysmb_u8 mysmb_objects_spawn_hammer(struct mysmb_game *g)
{ return child(g,1U,g->ram[8U]); }
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *g,mysmb_u8 s)
{ return child(g,2U,s); }
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 f,mysmb_u8 m)
{ if(f!=g->ram[0U] || m!=3U) ++failures; (void)child(g,3U,s); }
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,4U,s);return 0U; }
void mysmb_objects_erase_enemy(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,5U,s); }
void mysmb_world_red_gravity(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 d)
{ (void)g;(void)s;(void)d;++failures; }

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char h[8];
    FILE *f;
    if (argc!=3) return 64;
    f=fopen(argv[2],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MSbC\1",5)!=0 || h[5]>16U) return 66;
    count=h[5];
    if (fread(records,4098,count,f)!=count || fgetc(f)!=EOF) return 66;
    fclose(f);f=fopen(argv[1],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MSbP\1",5)!=0 ||
        fread(game.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF) return 66;
    fclose(f);
    if(h[5]==1U) mysmb_objects_step_hammer_bros_slot(&game,h[6]);
    else mysmb_enemy_move_normal(&game,h[6]);
    compare(game.ram,expected);
    if (calls!=count) ++failures;
    return failures?1:0;
}
