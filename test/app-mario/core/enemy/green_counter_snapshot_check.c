#include "core/enemy/core.h"
#include "core/enemy/actor_slots.h"
#include "core/enemy/movement.h"
#include "core/enemy/x_counter.h"
#include "core/enemy/distance.h"
#include "core/world/world.h"
#include "core/objects.h"
#include "core/oam/oam.h"
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
    if (r[0]!=id || slot!=game->ram[8U]) ++failures;
    compare(game->ram,r+2U);
    memcpy(game->ram,r+2050U,2048U);
    return r[1];
}
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 s)
{ return child(g,1U,s); }

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char h[8];
    FILE *f;
    if (argc!=3) return 64;
    f=fopen(argv[2],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MSdC\1",5)!=0 || h[5]>16U) return 66;
    count=h[5];
    if (fread(records,4098,count,f)!=count || fgetc(f)!=EOF) return 66;
    fclose(f);f=fopen(argv[1],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MSdP\1",5)!=0 ||
        fread(game.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF) return 66;
    fclose(f);
    if(h[5]==1U) mysmb_objects_step_flying_green_paratroopas_slot(&game,h[6]);
    else mysmb_enemy_x_counter_platform(&game,h[6],h[7]);
    compare(game.ram,expected);
    if (calls!=count) ++failures;
    return failures?1:0;
}
