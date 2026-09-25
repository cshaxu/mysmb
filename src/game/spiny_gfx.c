#include "game/objects.h"

enum {
    F = 0x000fU, I = 0x0016U, S = 0x001eU, D = 0x0046U,
    P = 0x006eU, X = 0x0087U, Y = 0x00cfU, RX = 0x03aeU,
    RY = 0x03b9U, O = 0x03d1U, A = 0x03c5U, SO = 0x06e5U,
    SP = 0x071aU, SX = 0x071cU, TC = 0x0747U, FC = 0x0009U
};

static void hide(struct mysmb_game *g, mysmb_u8 o, mysmb_u8 b)
{
    mysmb_u8 r, q;
    for (r = 0U; r < 3U; ++r) {
        q = (mysmb_u8)(o + r * 8U);
        if ((b & 0x80U) != 0U || ((b & 0x40U) != 0U && r >= 1U) ||
            ((b & 0x20U) != 0U && r == 2U)) {
            g->ram[0x0200U + q] = 0xf8U; g->ram[0x0204U + q] = 0xf8U;
        } else {
            if ((b & 8U) != 0U) g->ram[0x0200U + q] = 0xf8U;
            if ((b & 4U) != 0U) g->ram[0x0204U + q] = 0xf8U;
        }
    }
}

/* ROM EnemyGfxHandler: Spiny offset $24 and egg state $05 offset $30. */
mysmb_u8 mysmb_objects_draw_spiny(struct mysmb_game *g, mysmb_u8 n)
{
    static const mysmb_u8 normal[2][6] = {
        { 0xfcU,0xfcU,0x96U,0x97U,0x98U,0x99U },
        { 0xfcU,0xfcU,0x9aU,0x9bU,0x9cU,0x9dU }
    };
    static const mysmb_u8 eggtiles[2][6] = {
        { 0xfcU,0xfcU,0x8fU,0x8eU,0x8eU,0x8fU },
        { 0xfcU,0xfcU,0x95U,0x94U,0x94U,0x95U }
    };
    const mysmb_u8 *t;
    mysmb_u16 w, z;
    mysmb_u8 st, egg, ani, dir, bits, o, r, q, l, rr;

    if (g->ram[F+n] == 0U || g->ram[I+n] != 18U) return 0U;
    w=(mysmb_u16)(((mysmb_u16)g->ram[P+n]<<8U)|g->ram[X+n]);
    z=(mysmb_u16)(((mysmb_u16)g->ram[SP]<<8U)|g->ram[SX]);
    g->ram[A+n]=0U; g->ram[RX+n]=(mysmb_u8)(w-z); g->ram[RY+n]=g->ram[Y+n];
    bits=mysmb_objects_get_enemy_x_offscreen_bits(g,n); g->ram[O+n]=bits;
    st=g->ram[S+n]; egg=(mysmb_u8)((st&0x1fU)==5U?1U:0U);
    ani=(mysmb_u8)((st&0xa0U)==0U && g->ram[TC]==0U && (g->ram[FC]&8U)==0U?1U:0U);
    t=egg!=0U?eggtiles[ani]:normal[ani]; dir=egg!=0U?2U:g->ram[D+n]; o=g->ram[SO+n];
    for(r=0U;r<3U;++r) {
        q=(mysmb_u8)(o+r*8U); l=t[r*2U]; rr=t[r*2U+1U];
        if((dir&2U)!=0U) { g->ram[0x0201U+q]=rr; g->ram[0x0205U+q]=l; g->ram[0x0202U+q]=0x42U; g->ram[0x0206U+q]=0x42U; }
        else { g->ram[0x0201U+q]=l; g->ram[0x0205U+q]=rr; g->ram[0x0202U+q]=2U; g->ram[0x0206U+q]=2U; }
        g->ram[0x0200U+q]=(mysmb_u8)(g->ram[RY+n]+r*8U); g->ram[0x0204U+q]=g->ram[0x0200U+q];
        g->ram[0x0203U+q]=g->ram[RX+n]; g->ram[0x0207U+q]=(mysmb_u8)(g->ram[RX+n]+8U);
    }
    if(egg!=0U) for(r=0U;r<3U;++r) {
        q=(mysmb_u8)(o+r*8U); l=(mysmb_u8)(g->ram[0x0202U+q]&0xa3U);
        g->ram[0x0202U+q]=l; g->ram[0x0206U+q]=(mysmb_u8)(l|0xc0U);
    }
    hide(g,o,bits); return egg!=0U?2U:1U;
}
