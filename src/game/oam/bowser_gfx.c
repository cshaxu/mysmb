#include "game/oam/oam.h"
#include "game/objects.h"
#include "game/enemy/actor_slots.h"

enum { F=0x000fU,I=0x0016U,S=0x001eU,D=0x0046U,P=0x006eU,X=0x0087U,Y=0x00cfU,
       RX=0x03aeU,RY=0x03b9U,O=0x03d1U,A=0x03c5U,SO=0x06e5U,ASO=0x06ecU,
       SC=0x03eeU,BC=0x0363U,SP=0x071aU,SX=0x071cU };

/* ROM SprObjectOffscrChk, for DrawEnemyObject's six-sprite layout. */
static void hide(struct mysmb_game *g, mysmb_u8 o, mysmb_u8 b)
{
    mysmb_u8 r, q;
    for (r=0U; r<3U; ++r) {
        q=(mysmb_u8)(o+r*8U);
        if ((b&0x80U)!=0U || ((b&0x40U)!=0U && r>=1U) ||
            ((b&0x20U)!=0U && r==2U)) {
            g->ram[0x0200U+q]=0xf8U; g->ram[0x0204U+q]=0xf8U;
        } else {
            if ((b&8U)!=0U) g->ram[0x0200U+q]=0xf8U;
            if ((b&4U)!=0U) g->ram[0x0204U+q]=0xf8U;
        }
    }
}

/* ROM DrawEnemyObject, DrawSpriteObject, and CheckDefeatedState. */
static void draw_half(struct mysmb_game *g, const mysmb_u8 *t, mysmb_u8 o,
                      mysmb_u8 x, mysmb_u8 y, mysmb_u8 d, mysmb_u8 s,
                      mysmb_u8 bits)
{
    mysmb_u8 r,q,l,rr,a,sl,sr;
    for (r=0U; r<3U; ++r) {
        q=(mysmb_u8)(o+r*8U); l=t[r*2U]; rr=t[r*2U+1U]; a=2U;
        if ((d&2U)!=0U) { g->ram[0x0201U+q]=rr; g->ram[0x0205U+q]=l;
            a|=0x40U; } else { g->ram[0x0201U+q]=l; g->ram[0x0205U+q]=rr; }
        g->ram[0x0202U+q]=a; g->ram[0x0206U+q]=a;
        g->ram[0x0200U+q]=(mysmb_u8)(y+r*8U); g->ram[0x0204U+q]=g->ram[0x0200U+q];
        g->ram[0x0203U+q]=x; g->ram[0x0207U+q]=(mysmb_u8)(x+8U);
    }
    if ((s&0x20U)!=0U) {
        for (r=0U; r<3U; ++r) { q=(mysmb_u8)(o+r*8U);
            g->ram[0x0202U+q]|=0x80U; g->ram[0x0206U+q]|=0x80U; }
        sl=g->ram[0x0201U+o]; sr=g->ram[0x0205U+o];
        g->ram[0x0201U+o]=g->ram[0x0211U+o]; g->ram[0x0205U+o]=g->ram[0x0215U+o];
        g->ram[0x0211U+o]=sl; g->ram[0x0215U+o]=sr;
    }
    hide(g,o,bits);
}

/* Existing EnemyGfxHandler Bowser rows. Orchestration owns the two slots;
 * generic graphics scratch/flip semantics retain their separate proof debt. */
void mysmb_oam_draw_bowser_half(struct mysmb_game *g, mysmb_u8 n)
{
    static const mysmb_u8 front[6]={0xbfU,0xbeU,0xc1U,0xc0U,0xc2U,0xfcU};
    static const mysmb_u8 rear[6]={0xc4U,0xc3U,0xc6U,0xc5U,0xc8U,0xc7U};
    static const mysmb_u8 open[6]={0xbfU,0xbeU,0xcaU,0xc9U,0xc2U,0xfcU};
    static const mysmb_u8 step[6]={0xc4U,0xc3U,0xc6U,0xc5U,0xccU,0xcbU};
    const mysmb_u8 *tiles;
    if (g->ram[0x036aU] == 1U)
        tiles = (g->ram[BC] & 0x80U) != 0U ? open : front;
    else tiles = (g->ram[BC] & 1U) != 0U ? step : rear;
    draw_half(g,tiles,g->ram[SO+n],g->ram[RX],g->ram[RY],
              g->ram[D+n],g->ram[S+n],g->ram[O]);
}

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
