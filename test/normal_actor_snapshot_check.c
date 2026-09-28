#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
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
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *g,mysmb_u8 s)
{ child((struct mysmb_game *)g,1U,s);return g->ram[0x3d1U]; }
#define CHILD(name,id) void name(struct mysmb_game *g,mysmb_u8 s) { child(g,id,s); }
CHILD(mysmb_oam_relative_enemy_position,2U)
CHILD(mysmb_objects_update_enemy_bounding_box,4U)
CHILD(mysmb_objects_enemy_background_current,5U)
CHILD(mysmb_objects_step_enemy_collisions_current,6U)
CHILD(mysmb_objects_check_enemy_offscreen_bounds,8U)
CHILD(mysmb_enemy_move_normal,9U)
CHILD(mysmb_objects_step_hammer_bros_slot,10U)
CHILD(mysmb_objects_step_bloobers_slot,11U)
CHILD(mysmb_objects_step_bullet_bills_slot,12U)
CHILD(mysmb_objects_step_swimming_cheep_cheeps_slot,13U)
CHILD(mysmb_objects_step_podoboos_slot,14U)
CHILD(mysmb_objects_step_piranha_plants_slot,15U)
CHILD(mysmb_enemy_move_jumping,16U)
CHILD(mysmb_objects_step_red_paratroopas_slot,17U)
CHILD(mysmb_objects_step_flying_green_paratroopas_slot,18U)
CHILD(mysmb_enemy_step_lakitus_slot,19U)
CHILD(mysmb_objects_step_flying_cheep_cheeps_slot,20U)
#undef CHILD
mysmb_u8 mysmb_objects_draw_normal_enemy_graphics(struct mysmb_game *g,mysmb_u8 s)
{ child(g,3U,s);return 0U; }
void mysmb_objects_player_enemy_current(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 preserve)
{ if(preserve!=1U) ++failures;child(g,7U,s); }

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char h[8];
    FILE *f;
    if (argc!=3) return 64;
    f=fopen(argv[2],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MS8C\1",5)!=0 || h[5]>16U) return 66;
    count=h[5];
    if (fread(records,4098,count,f)!=count || fgetc(f)!=EOF) return 66;
    fclose(f);f=fopen(argv[1],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MS8P\1",5)!=0 ||
        fread(game.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF) return 66;
    fclose(f);
if (h[5]==1U) mysmb_objects_step_normal_enemy(&game,h[6]);
    else if (h[5]==2U) mysmb_enemy_movement_dispatch(&game,h[6]);
    else return 66;
    compare(game.ram,expected);
    if (calls!=count) ++failures;
    return failures?1:0;
}
