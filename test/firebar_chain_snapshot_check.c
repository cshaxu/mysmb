#include "game/enemy/core.h"
#include "game/enemy/firebar.h"
#include "smb1_local_rom.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include "game/enemy/x_counter.h"
#include "game/enemy/distance.h"
#include "game/world/world.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Caller-only proof. Compare the entire original child input before using
 * its recorded return. Actual child execution is a separate diagnostic. */
static unsigned char records[64][4098];
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
    if (r[0]!=id || (id==4U ? slot!=r[1] : (id!=5U && slot!=game->ram[8U]))) ++failures;
    compare(game->ram,r+2U);
    memcpy(game->ram,r+2050U,2048U);
    return r[1];
}
void mysmb_firebar_offscreen(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,1U,s); }
mysmb_u8 mysmb_firebar_spin(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 speed)
{ if(speed!=g->ram[0x388U+s]) ++failures; return child(g,2U,s); }
mysmb_u8 mysmb_firebar_relative(struct mysmb_game *g,mysmb_u8 s)
{ return child(g,3U,s); }
mysmb_u8 mysmb_oam_draw_firebar(struct mysmb_game *g,mysmb_u8 oam)
{ return child(g,4U,oam); }
void mysmb_objects_force_injury(struct mysmb_game *g)
{ (void)child(g,5U,0U); }

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char h[8];
    FILE *f;
    if (argc!=3) return 64;
    f=fopen(argv[2],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MShC\1",5)!=0 || h[5]>64U) return 66;
    count=h[5];
    if (fread(records,4098,count,f)!=count || fgetc(f)!=EOF) return 66;
    fclose(f);f=fopen(argv[1],"rb");if (!f) return 65;
    if (fread(h,1,8,f)!=8 || memcmp(h,"MShP\1",5)!=0 ||
        fread(game.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF) return 66;
    fclose(f);
    game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    (void)mysmb_enemy_proc_firebar(&game,h[6]);
    compare(game.ram,expected);
    if (calls!=count) ++failures;
    return failures?1:0;
}
