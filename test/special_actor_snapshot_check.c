#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/platform.h"
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
static void child(struct mysmb_game *game, unsigned int id, mysmb_u8 slot)
{
    unsigned char *r;
    if (calls>=count) { ++failures;return; }
    r=records[calls++];
    if (r[0]!=id || r[1]!=slot) ++failures;
    compare(game->ram,r+2U);
    memcpy(game->ram,r+2050U,2048U);
}
#define CHILD(name,id) void name(struct mysmb_game *g,mysmb_u8 s) { child(g,id,s); }
CHILD(mysmb_enemy_proc_bowser_flame,1U)
CHILD(mysmb_oam_relative_enemy_position,4U)
CHILD(mysmb_objects_update_enemy_bounding_box,5U)
CHILD(mysmb_objects_check_enemy_offscreen_bounds,7U)
CHILD(mysmb_platform_box_small,8U)
CHILD(mysmb_platform_collision_small,9U)
CHILD(mysmb_objects_draw_small_platform,10U)
CHILD(mysmb_platform_move_small,11U)
CHILD(mysmb_platform_box_large,12U)
CHILD(mysmb_platform_collision_large,13U)
CHILD(mysmb_objects_draw_large_platform,14U)
CHILD(mysmb_platform_move_balance,15U)
CHILD(mysmb_platform_move_y,16U)
CHILD(mysmb_platform_move_large_lift,17U)
CHILD(mysmb_platform_move_x,18U)
CHILD(mysmb_platform_move_drop,19U)
CHILD(mysmb_platform_move_right,20U)
#undef CHILD
mysmb_u8 mysmb_enemy_proc_firebar(struct mysmb_game *g,mysmb_u8 s)
{ child(g,2U,s);return 0U; }
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *g,mysmb_u8 s)
{ child((struct mysmb_game *)g,3U,s);return g->ram[0x3d1U]; }
void mysmb_objects_player_enemy_current(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 preserve)
{ if(preserve!=1U) ++failures;child(g,6U,s); }

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char h[8];
    FILE *f;
    if (argc!=3) return 64;
    f=fopen(argv[2],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MS9C\1",5)!=0 || h[5]>16U) return 66;
    count=h[5];
    if (fread(records,4098,count,f)!=count || fgetc(f)!=EOF) return 66;
    fclose(f);f=fopen(argv[1],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MS9P\1",5)!=0 ||
        fread(game.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF) return 66;
    fclose(f);
switch(h[5]) {
    case 1U: mysmb_objects_step_bowser_flames_slot(&game,h[6]);break;
    case 2U: (void)mysmb_objects_step_firebars_slot(&game,h[6]);break;
    case 3U: mysmb_enemy_run_small_platform(&game,h[6]);break;
    case 4U: mysmb_enemy_run_large_platform(&game,h[6]);break;
    case 5U: mysmb_platform_movement_dispatch(&game,h[6]);break;
    case 6U: mysmb_objects_erase_enemy(&game,h[6]);break;
    default:return 66;
    }
    compare(game.ram,expected);
    if (calls!=count) ++failures;
    return failures?1:0;
}
