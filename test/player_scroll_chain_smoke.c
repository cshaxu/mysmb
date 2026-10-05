#include "game/player.h"
#include "game/oam/oam.h"
#include <string.h>

static mysmb_u8 returned_bits;
static unsigned int calls;
mysmb_u8 mysmb_oam_get_x_offscreen_bits(struct mysmb_game *game,
                                       mysmb_u8 source_offset,
                                       mysmb_u8 page, mysmb_u8 x)
{
    (void)source_offset;
    if (page != game->ram[0x6dU] || x != game->ram[0x86U]) return 0xffU;
    ++calls;
    return returned_bits;
}

static void seed(struct mysmb_game *game)
{
    memset(game, 0, sizeof(*game));
    memset(game->ram, 0x5a, sizeof(game->ram));
    game->ram[0x723U] = 0U;
    game->ram[0x785U] = 0U;
    game->ram[0x755U] = 0x70U;
    game->ram[0x3a1U] = 0U;
    game->ram[0x778U] = 0xa6U;
    game->ppu.ppu_control_0 = 0x19U; /* RAM mirror must be authoritative. */
    returned_bits = 0U;
    calls = 0U;
}

int main(void)
{
    /* Source outcomes after DEY/BMI and the $50/$70 position gates. */
    static const mysmb_u8 cases[][4] = {
        {0,0,0x70,0}, {1,0,0x70,1}, {2,0,0x50,1},
        {0x7f,0,0x6f,0x7e}, {0x80,0,0x6f,0x7f},
        {0x80,0,0x70,0x80}, {0x81,0,0x70,0}, {0xff,0,0x70,0},
        {0xff,1,0x70,0}, {0xff,2,0x70,1}, {1,0xff,0x70,0},
        {2,0,0x4f,0}, {2,0,0x6f,1}, {2,0,0x70,2}
    };
    static struct mysmb_game game;
    static mysmb_u8 expected[2048];
    unsigned int i,block,page,x,amount,total,bits,buttons,edge,offset;
    for(i=0U;i<sizeof(cases)/sizeof(cases[0]);++i)
    for(block=0U;block<3U;++block) {
        seed(&game);
        game.ram[0x6ffU]=cases[i][0];game.ram[0x3a1U]=cases[i][1];
        game.ram[0x755U]=cases[i][2];
        game.ram[0x723U]=block==1U ? 0xffU:0U;
        game.ram[0x785U]=block==2U ? 0xffU:0U;
        memcpy(expected,game.ram,sizeof(expected));
        amount=block!=0U ? 0U:cases[i][3];
        mysmb_player_update_scroll(&game);
        if(calls!=1U || game.ram[0x775U]!=amount || game.ram[0x3a1U]!=0U ||
           game.ram[0x6ffU]!=(mysmb_u8)(cases[i][0]+cases[i][1])) return 1;
        if(amount==0U) {
            expected[0]=0U;expected[0x775U]=0U;expected[0x3a1U]=0U;
            expected[0x6ffU]=(mysmb_u8)(cases[i][0]+cases[i][1]);
            if(memcmp(expected,game.ram,sizeof(expected))!=0 ||
               game.ppu.ppu_control_0!=0x19U) return 2;
        }
    }
    /* Direct ScrollScreen must run even for amount zero; cover every page,
     * every low coordinate and every scroll amount independently. */
    for(x=0U;x<256U;++x) for(amount=0U;amount<256U;++amount) {
        seed(&game);page=(x+amount)&255U;
        game.ram[0x71aU]=(mysmb_u8)page;game.ram[0x71cU]=(mysmb_u8)x;
        total=page*256U+x+amount;
        mysmb_player_scroll_screen(&game,(mysmb_u8)amount);
        if(calls!=1U || game.ram[0x71aU]!=(mysmb_u8)(total>>8U) ||
           game.ram[0x71cU]!=(mysmb_u8)total ||
           game.ram[0x71bU]!=(mysmb_u8)((total+255U)>>8U) ||
           game.ram[0x71dU]!=(mysmb_u8)(total+255U) ||
           game.ram[0x778U]!=(mysmb_u8)(0xa6U|((total>>8U)&1U)) ||
           game.ram[0x795U]!=8U || game.ram[0x775U]!=amount ||
           game.ram[0x73dU]!=(mysmb_u8)(0x5aU+amount)) return 3;
        if(game.ppu.ppu_control_0!=game.ram[0x778U] ||
           game.ppu.ppu_name_table!=(game.ram[0x778U]&3U) ||
           game.ppu.visible_ppu_control_0!=0U) return 4;
    }
    /* All raw offscreen bytes and controller bytes, including left priority
     * when both sides are indicated; right-edge subtraction must borrow. */
    for(bits=0U;bits<256U;++bits) for(buttons=0U;buttons<256U;++buttons)
    for(x=0U;x<2U;++x) {
        seed(&game);game.ram[0x723U]=1U;returned_bits=(mysmb_u8)bits;
        game.ram[0xcU]=(mysmb_u8)buttons;game.ram[0x71dU]=x!=0U ? 0xffU:0U;
        memcpy(expected,game.ram,sizeof(expected));
        expected[0]=(mysmb_u8)bits;expected[0x775U]=0U;expected[0x3a1U]=0U;
        if((bits&0xa0U)!=0U) {
            edge=(bits&0x80U)!=0U ? 0U:1U;offset=edge*16U;
            total=(unsigned int)expected[0x71aU+edge]*256U+expected[0x71cU+edge]-offset;
            expected[0x86U]=(mysmb_u8)total;expected[0x6dU]=(mysmb_u8)(total>>8U);
            if(buttons!=edge+1U) expected[0x57U]=0U;
        }
        mysmb_player_update_scroll(&game);
        if(calls!=1U || memcmp(expected,game.ram,sizeof(expected))!=0) return 5;
    }
    return 0;
}
