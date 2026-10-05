#include "core/oam/oam.h"
#include "core/objects.h"
#include "core/enemy/actor_slots.h"

enum { F=0x000fU,I=0x0016U,S=0x001eU,D=0x0046U,P=0x006eU,X=0x0087U,Y=0x00cfU,
       RX=0x03aeU,RY=0x03b9U,O=0x03d1U,A=0x03c5U,SO=0x06e5U,ASO=0x06ecU,
       SC=0x03eeU,BC=0x0363U,SP=0x071aU,SX=0x071cU };

/* ROM $D1BC ProcessBowserHalf; the source graphics child reloads X from
 * ObjectOffset before returning. Collision is a tail call, not a new rule. */
static mysmb_u8 process_half(struct mysmb_game *g, mysmb_u8 n)
{
    ++g->ram[0x036aU];
    mysmb_objects_draw_retainer(g,n);
    n = g->ram[8U];
    if (g->ram[S+n] == 0U) {
        g->ram[0x049aU+n] = 10U;
        mysmb_objects_update_enemy_bounding_box(g,n);
        n = g->ram[8U];
        mysmb_objects_player_enemy_current(g,n,1U);
        n = g->ram[8U];
    }
    return n;
}

/* ROM $D17B-$D1D0 BowserGfxHandler / CopyFToR / ExBGfxH. */
void mysmb_objects_draw_bowsers_slot(struct mysmb_game *g, mysmb_u8 n)
{
    mysmb_u8 rear, saved, delta;
    n = process_half(g,n);
    delta = (g->ram[D+n] & 1U) != 0U ? 0xf0U : 0x10U;
    rear = g->ram[0x06cfU];
    g->ram[X+rear] = (mysmb_u8)(g->ram[X+n] + delta);
    g->ram[Y+rear] = (mysmb_u8)(g->ram[Y+n] + 8U);
    g->ram[S+rear] = g->ram[S+n];
    g->ram[D+rear] = g->ram[D+n];
    saved = g->ram[8U];
    n = g->ram[0x06cfU];
    g->ram[8U] = n;
    g->ram[I+n] = 45U;
    (void)process_half(g,n);
    g->ram[8U] = saved;
    g->ram[0x036aU] = 0U;
}

void mysmb_objects_draw_bowsers(struct mysmb_game *g)
{
    mysmb_u8 n;
    for (n=0U;n<5U;++n) {
        if (g->ram[F+n]!=0U && g->ram[I+n]==45U) {
            g->ram[8U] = n;
            mysmb_objects_draw_bowsers_slot(g,n);
        }
    }
}
