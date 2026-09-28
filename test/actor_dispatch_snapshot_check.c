#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/loop.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Caller-only proof. Compare the entire original child input before using
 * its recorded return. Actual child execution is a separate diagnostic. */
static unsigned char records[3][4098];
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
#ifdef MYSMB_RETAINER_CALLER
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *game,mysmb_u8 slot)
{ child((struct mysmb_game *)game,1U,slot);return game->ram[0x3d1U]; }
void mysmb_oam_relative_enemy_position(struct mysmb_game *game,mysmb_u8 slot)
{ child(game,2U,slot); }
void mysmb_oam_draw_retainer(struct mysmb_game *game,mysmb_u8 slot)
{ child(game,3U,slot); }
void mysmb_objects_step_platforms_slot(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++failures; }
void mysmb_objects_step_bowsers_slot(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++failures; }
void mysmb_objects_draw_bowsers_slot(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++failures; }
#else
#define CHILD(name,id) void name(struct mysmb_game *g,mysmb_u8 s) { child(g,id,s); }
CHILD(mysmb_objects_step_normal_enemy,1U)
CHILD(mysmb_objects_step_bowser_flames_slot,2U)
CHILD(mysmb_objects_step_fireworks_slot,3U)
CHILD(mysmb_enemy_run_large_platform,5U)
CHILD(mysmb_enemy_run_small_platform,6U)
CHILD(mysmb_enemy_run_bowser,7U)
CHILD(mysmb_objects_step_vine,9U)
CHILD(mysmb_objects_step_star_flags_slot,10U)
CHILD(mysmb_objects_step_jumpspring,11U)
CHILD(mysmb_objects_draw_retainer,12U)
#undef CHILD
mysmb_u8 mysmb_objects_step_firebars_slot(struct mysmb_game *g,mysmb_u8 s)
{ child(g,4U,s);return 0U; }
void mysmb_objects_step_power_up(struct mysmb_game *g)
{ child(g,8U,g->ram[8U]); }
void mysmb_enemy_process_loop_command(struct mysmb_game *g,const struct mysmb_area_source *p,mysmb_u8 s)
{ (void)g;(void)p;(void)s;++failures; }
#endif

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char h[8];
    FILE *f;
    if (argc!=3) return 64;
    f=fopen(argv[2],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MS7C\1",5)!=0 || h[5]>3U) return 66;
    count=h[5];
    if (fread(records,4098,count,f)!=count || fgetc(f)!=EOF) return 66;
    fclose(f);f=fopen(argv[1],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MS7P\1",5)!=0 ||
        fread(game.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF) return 66;
    fclose(f);
#ifdef MYSMB_RETAINER_CALLER
    if (h[5]!=2U) return 66;
    mysmb_objects_draw_retainer(&game,h[6]);
#else
    if (h[5]!=1U) return 66;
    mysmb_enemy_run_objects(&game);
#endif
    compare(game.ram,expected);
    if (calls!=count) ++failures;
    return failures?1:0;
}
